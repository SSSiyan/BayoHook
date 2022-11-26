#include "gamehook.hpp"

// patch toggles
bool GameHook::takeNoDamage_toggle(false);
bool GameHook::focusPatch_toggle(false);
bool GameHook::infJumps_toggle(false);
bool GameHook::disableClicking_toggle(false);

// update
uintptr_t playerPointerAddress = 0xEF5A60;
uintptr_t halosAddress = 0x5AA74B4;
uintptr_t chaptersPlayedAddress = 0x5AA736C;
uintptr_t playerMagicAddress = 0x5AA74AC;
uintptr_t comboPointsAddress = 0x5BB519C;
uintptr_t currentCharacterAddress = 0x5AA7484;
uintptr_t thirdAccessoryAddress = 0x5AA7468;
uintptr_t hudDisplayAddress = 0xF2B714;

uintptr_t GameHook::actorPlayable = NULL;
float GameHook::xyzpos[3]{ 0.0f, 0.0f, 0.0f };
int GameHook::halos = 0;
int GameHook::chaptersPlayed = 0;
int GameHook::playerHealth = 0;
float GameHook::remainingWitchTimeDuration = 0.0f;
float GameHook::playerMagic = 0.0f;
int GameHook::comboPoints = 0;
int GameHook::currentCharacter = 0;
int GameHook::thirdAccessory = 0;
bool GameHook::hudDisplay = 0;

// patches
void GameHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		GameHook::_nop((char*)(0x9D4329), 6);
	else
		GameHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

void GameHook::FocusPatch(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x49E519), (char*)"\xEB\x17", 2); // disable pausing tabbed out
		GameHook::_patch((char*)(0x411DB8), (char*)"\xE9\x82\x00", 3); // enable inputs tabbed out
	}
	else {
		GameHook::_patch((char*)(0x49E519), (char*)"\x75\x17", 2); // enable pausing tabbed out
		GameHook::_patch((char*)(0x411DB8), (char*)"\x0F\x85\x81", 3); // disable inputs tabbed out
	}
}

void GameHook::InfJumps(bool enabled) {
	if (enabled) 
		GameHook::_nop((char*)(0x9E8906), 6);
	else
		GameHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6);
}

void GameHook::DisableClicking(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC75747), 3);
	else
		GameHook::_patch((char*)(0xC75747), (char*)"\x89\x70\x04", 3);
}

// detours
std::unique_ptr<FunctionHook> enemyHPHook;
uintptr_t enemyHP_jmp_ret{ NULL };
bool GameHook::enemyHP_no_damage_toggle = false;
bool GameHook::enemyHP_one_hit_kill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [GameHook::enemyHP_no_damage_toggle], 1
		je no_damage
		jmp check2

		check2:
			cmp byte ptr [GameHook::enemyHP_one_hit_kill_toggle], 1
			je one_hit_kill
			jmp originalcode

		no_damage:
			jmp dword ptr [enemyHP_jmp_ret]

		one_hit_kill:
			mov dword ptr [esi+0x000006B4], 0
			jmp dword ptr [enemyHP_jmp_ret]

		originalcode:
			mov [esi+0x000006B4], eax
			jmp dword ptr [enemyHP_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> witchTimeHook;
uintptr_t witchTimeMultiplier_jmp_ret{ NULL };
bool GameHook::witchTimeMultiplier_toggle = false;
float GameHook::witchTimeMultiplier = 1.0;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		cmp byte ptr [GameHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fmul dword ptr [esi+0x00095D68] // might be game speed or something? 1 by default
		fdiv dword ptr [GameHook::witchTimeMultiplier]
		jmp dword ptr [witchTimeMultiplier_jmp_ret]

		originalcode:
			fmul dword ptr [esi+0x00095D68]
			jmp dword ptr [witchTimeMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> infMagicHook;
uintptr_t infMagic_jmp_ret{ NULL };
bool GameHook::inf_magic_toggle = false;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		push eax
		cmp byte ptr [GameHook::inf_magic_toggle], 0
		je originalcode

		mov eax, [playerMagicAddress]
		mov dword ptr [eax], 0x44fa0000 // 2000

		originalcode:
		mov eax, [playerMagicAddress] // i hate that i have to do this
		movss xmm0, [eax]
		pop eax
		jmp dword ptr [infMagic_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> outgoingDamageMultiplierHook;
uintptr_t outgoingDamageMultiplier_jmp_ret{ NULL };
bool GameHook::outgoingDamageMultiplier_toggle = false;
float outgoingDamageMultiplierXmm0Backup = 0.0f;
float GameHook::outgoingDamageMultiplierMult = 1.0f;
static __declspec(naked) void OutgoingDamageMultiplierDetour(void) {
	_asm {
		mov [esi+0x000006B8], eax // originalcode, early bytes to avoid EnemyHPDetour
		mov [GameHook::haloDisplayValue], eax
		cmp byte ptr [GameHook::outgoingDamageMultiplier_toggle], 0
		je originalcode

		movss [outgoingDamageMultiplierXmm0Backup], xmm0 // xmm0 backup
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [GameHook::outgoingDamageMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0,[outgoingDamageMultiplierXmm0Backup] // restore xmm0

		originalcode:
		sub eax,edi
		jmp dword ptr [outgoingDamageMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> customCameraDistanceHook;
uintptr_t customCameraDistance_jmp_ret{ NULL };
bool GameHook::customCameraDistance_toggle = false;
float GameHook::customCameraDistanceMultiplierMult = 0.0f;
static __declspec(naked) void CustomCameraDistanceDetour(void) {
	_asm {
		cmp byte ptr [GameHook::customCameraDistance_toggle], 0
		je originalcode

		cmp eax, 0xF2E630 // only change this value
		jne originalcode
		mulss xmm0,[GameHook::customCameraDistanceMultiplierMult]

		originalcode:
		movss [eax],xmm0
		pop esi
		jmp dword ptr [customCameraDistance_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lessClothesHook;
uintptr_t lessClothes_jmp_ret{ NULL };
bool GameHook::lessClothes_toggle = false;
static __declspec(naked) void LessClothesDetour(void) {
	_asm {
		cmp byte ptr [GameHook::lessClothes_toggle], 0
		je originalcode

		mov byte ptr [esi+0x00096330], 6
		mov byte ptr [esi+0x00096331], 0

		originalcode:
		mov eax,[esi+0x00096330]
		jmp dword ptr [lessClothes_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> haloDisplayHook;
uintptr_t haloDisplay_jmp_ret{ NULL };
bool GameHook::haloDisplay_toggle = false;
int GameHook::haloDisplayValue = 0;
uintptr_t haloAddress = 0x5BB57B0;
static __declspec(naked) void HaloDisplayDetour(void) {
	_asm {
		cmp byte ptr [GameHook::haloDisplay_toggle], 0
		je originalcode

		cmp dword ptr [GameHook::haloDisplayValue], 1
		jle originalcode
		mov eax, [GameHook::haloDisplayValue]	

		originalcode:
		push esi
		mov esi,[haloAddress] // i still hate this
		mov [esi],eax
		pop esi
		jmp dword ptr [haloDisplay_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> animSwapHook;
uintptr_t animSwap_jmp_ret{ NULL };
uintptr_t animSwapCharacterAddress = 0xEF5A60;
bool GameHook::animSwap_toggle = false;
int GameHook::animSwapCurrentAnim = 0;
int GameHook::animSwapSourceAnim1 = -1;
int GameHook::animSwapDesiredAnim1 = 0;
static __declspec(naked) void AnimSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::animSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [animSwapCharacterAddress] // only edit player anim
		cmp [eax], ecx
		pop eax
		jne originalcode

		mov [GameHook::animSwapCurrentAnim], edx
		cmp edx, [GameHook::animSwapSourceAnim1]
		je newMove1
		jmp originalcode

		newMove1:
		mov edx, [GameHook::animSwapDesiredAnim1]
		jmp originalcode


		originalcode:
		mov [ecx+0x0000034C], edx
		jmp dword ptr [animSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> inputIconsHook;
uintptr_t inputIcons_jmp_ret{ NULL };
bool GameHook::inputIcons_toggle = false;
int GameHook::inputIconsValue = 1; // 0 keyboard, 1 gamepad
static __declspec(naked) void InputIconsDetour(void) {
	_asm {
		cmp byte ptr [GameHook::inputIcons_toggle], 0
		je originalcode

		mov eax, [GameHook::inputIconsValue]

		originalcode:
		mov [ebx+0x00000CA8], eax
		jmp dword ptr [inputIcons_jmp_ret]
	}
}

// update
void GameHook::Update() {
	GameHook::actorPlayable = (*(uintptr_t*)playerPointerAddress);
	GameHook::halos = (*(int*)halosAddress);
	if (GameHook::actorPlayable != NULL) {
		GameHook::xyzpos[0] = (*(float*)(GameHook::actorPlayable + 0xD0));
		GameHook::xyzpos[1] = (*(float*)(GameHook::actorPlayable + 0xD4));
		GameHook::xyzpos[2] = (*(float*)(GameHook::actorPlayable + 0xD8));
		GameHook::playerHealth = (*(int*)(GameHook::actorPlayable + 0x93508));
		GameHook::remainingWitchTimeDuration = (*(float*)(GameHook::actorPlayable + 0x95D5C));
	}
	GameHook::chaptersPlayed = (*(int*)chaptersPlayedAddress);
	GameHook::playerMagic = (*(float*)playerMagicAddress);
	GameHook::comboPoints = (*(int*)comboPointsAddress);
	GameHook::currentCharacter = (*(int*)currentCharacterAddress);
	GameHook::thirdAccessory = (*(int*)thirdAccessoryAddress);
	GameHook::hudDisplay = (*(bool*)hudDisplayAddress);
	//GameHook::zone = (const char*)_baseAddress + 0x4374A24;
}

// setters
void GameHook::SetXYZPos(float x, float y, float z) {
	(*(float*)(GameHook::actorPlayable + 0xD0)) = x;
	(*(float*)(GameHook::actorPlayable + 0xD4)) = y;
	(*(float*)(GameHook::actorPlayable + 0xD8)) = z;
}

void GameHook::SetHalos(int value) {
	(*(int*)halosAddress) = value;
}

void GameHook::SetChaptersPlayed(int value) {
	(*(int*)chaptersPlayedAddress) = value;
}

void GameHook::SetHealth(int value) {
	(*(int*)(GameHook::actorPlayable + 0x93508)) = value;
}

void GameHook::SetRemainingWitchTimeDuration(float value) {
	(*(float*)(GameHook::actorPlayable + 0x95D5C)) = value;
}

void GameHook::SetMagic(float value) {
	(*(float*)playerMagicAddress) = value;
}

void GameHook::SetComboPoints(int value) {
	(*(int*)comboPointsAddress) = value;
}

void GameHook::SetCurrentCharacter(int value) {
	(*(int*)currentCharacterAddress) = value;
}

void GameHook::SetThirdAccessory(int value) {
	(*(int*)thirdAccessoryAddress) = value;
}

void GameHook::SetHudDisplay(bool value) {
	(*(bool*)hudDisplayAddress) = value;
}

// dev functions
void GameHook::_patch(char* dst, char* src, int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void GameHook::_nop(char* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

bool install_hook_absolute(uintptr_t location, std::unique_ptr<FunctionHook>& hook, void* detour, uintptr_t* ret, ptrdiff_t next_instruction_offset = 0) {
	//assert(!hook);
	hook = std::make_unique<FunctionHook>(location, detour);
	if (!hook->create()) {
		return false;
	}

	if (next_instruction_offset) {
		if (ret) {
			*ret = location + next_instruction_offset;
		}
	}
	else {
		if (ret) {
			*ret = hook->get_original();
		}
	}
	return true;
}	

void GameHook::InitializeDetours(void) {
	install_hook_absolute(0x4572BA, enemyHPHook, &EnemyHPDetour, &enemyHP_jmp_ret, 6);
	install_hook_absolute(0x9E1808, witchTimeHook, &WitchTimeMultiplierDetour, &witchTimeMultiplier_jmp_ret, 6);
	install_hook_absolute(0x8BCE4C, infMagicHook, &InfMagicDetour, &infMagic_jmp_ret, 8);
	install_hook_absolute(0x4572B2, outgoingDamageMultiplierHook, &OutgoingDamageMultiplierDetour, &outgoingDamageMultiplier_jmp_ret, 8);
	install_hook_absolute(0xC52491, customCameraDistanceHook, &CustomCameraDistanceDetour, &customCameraDistance_jmp_ret, 5);
	install_hook_absolute(0x8B6C55, lessClothesHook, &LessClothesDetour, &lessClothes_jmp_ret, 6);
	install_hook_absolute(0x4250F7, haloDisplayHook, &HaloDisplayDetour, &haloDisplay_jmp_ret, 5);
	install_hook_absolute(0x4BD053, animSwapHook, &AnimSwapDetour, &animSwap_jmp_ret, 6);
	install_hook_absolute(0x411CDB, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 6);
}

void GameHook::onConfigLoad(const utils::Config& cfg) {
	// patches
	takeNoDamage_toggle = cfg.get<bool>("TakeNoDamageToggle").value_or(false);
	TakeNoDamage(takeNoDamage_toggle);
	focusPatch_toggle = cfg.get<bool>("FocusPatchToggle").value_or(false);
	FocusPatch(focusPatch_toggle);
	infJumps_toggle = cfg.get<bool>("InfJumpsToggle").value_or(false);
	InfJumps(infJumps_toggle);
	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
	outgoingDamageMultiplier_toggle = cfg.get<bool>("OutgoingDamageMultiplierToggle").value_or(false);
	outgoingDamageMultiplierMult = cfg.get<float>("OutgoingDamageMultiplierMult").value_or(1.0f);
	customCameraDistance_toggle = cfg.get<bool>("CustomCameraDistanceToggle").value_or(false);
	customCameraDistanceMultiplierMult = cfg.get<float>("CustomCameraDistanceMultiplier").value_or(1.0f);
	lessClothes_toggle = cfg.get<bool>("LessClothesToggle").value_or(false);
	haloDisplay_toggle = cfg.get<bool>("HaloDisplayToggle").value_or(false);
	inputIcons_toggle = cfg.get<bool>("InputIconsToggle").value_or(false);
	inputIconsValue = cfg.get<int>("InputIconsValue").value_or(false);
}

void GameHook::onConfigSave(utils::Config& cfg) {
	// patches
	cfg.set<bool>("TakeNoDamageToggle", takeNoDamage_toggle);
	cfg.set<bool>("FocusPatchToggle", focusPatch_toggle);
	cfg.set<bool>("InfJumpsToggle", infJumps_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);
	cfg.set<bool>("OutgoingDamageMultiplierToggle", outgoingDamageMultiplier_toggle);
	cfg.set<float>("OutgoingDamageMultiplierMult", outgoingDamageMultiplierMult);
	cfg.set<bool>("CustomCameraDistanceToggle", customCameraDistance_toggle);
	cfg.set<float>("CustomCameraDistanceMultiplier", customCameraDistanceMultiplierMult);
	cfg.set<bool>("LessClothesToggle", lessClothes_toggle);
	cfg.set<bool>("HaloDisplayToggle", haloDisplay_toggle);

	cfg.set<bool>("InputIconsToggle", inputIcons_toggle);
	cfg.set<int>("InputIconsValue", inputIconsValue);

	cfg.save("../bayo_hook.cfg");
}
