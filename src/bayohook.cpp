#include "bayohook.hpp"

// patch toggles
bool BayoHook::takeNoDamage_toggle(false);
bool BayoHook::focusPatch_toggle(false);
bool BayoHook::infJumps_toggle(false);
bool BayoHook::disableClicking_toggle(false);

// update
uintptr_t playerPointerAddress = 0xEF5A60;
uintptr_t halosAddress = 0x5AA74B4;
uintptr_t chaptersPlayedAddress = 0x5AA736C;
uintptr_t playerMagicAddress = 0x5AA74AC;
uintptr_t comboPointsAddress = 0x5BB519C;
uintptr_t currentCharacterAddress = 0x5AA7484;
uintptr_t thirdAccessoryAddress = 0x5AA7468;
uintptr_t hudDisplayAddress = 0xF2B714;

uintptr_t BayoHook::actorPlayable = NULL;
float BayoHook::xyzpos[3]{ 0.0f, 0.0f, 0.0f };
int BayoHook::halos = 0;
int BayoHook::chaptersPlayed = 0;
int BayoHook::playerHealth = 0;
float BayoHook::remainingWitchTimeDuration = 0.0f;
float BayoHook::playerMagic = 0.0f;
int BayoHook::comboPoints = 0;
int BayoHook::currentCharacter = 0;
int BayoHook::thirdAccessory = 0;
bool BayoHook::hudDisplay = 0;

// patches
void BayoHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		BayoHook::_nop((char*)(0x9D4329), 6);
	else
		BayoHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

void BayoHook::FocusPatch(bool enabled) {
	if (enabled) {
		BayoHook::_patch((char*)(0x49E519), (char*)"\xEB\x17", 2); // disable pausing tabbed out
		BayoHook::_patch((char*)(0x411DB8), (char*)"\xE9\x82\x00", 3); // enable inputs tabbed out
	}
	else {
		BayoHook::_patch((char*)(0x49E519), (char*)"\x75\x17", 2); // enable pausing tabbed out
		BayoHook::_patch((char*)(0x411DB8), (char*)"\x0F\x85\x81", 3); // disable inputs tabbed out
	}
}

void BayoHook::InfJumps(bool enabled) {
	if (enabled) 
		BayoHook::_nop((char*)(0x9E8906), 6);
	else
		BayoHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6);
}

void BayoHook::DisableClicking(bool enabled) {
	if (enabled)
		BayoHook::_nop((char*)(0xC75747), 3);
	else
		BayoHook::_patch((char*)(0xC75747), (char*)"\x89\x70\x04", 3);
}

// detours
std::unique_ptr<FunctionHook> enemyHPHook;
uintptr_t enemyHP_jmp_ret{ NULL };
bool BayoHook::enemyHP_no_damage_toggle = false;
bool BayoHook::enemyHP_one_hit_kill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::enemyHP_no_damage_toggle], 1
		je no_damage
		jmp check2

		check2:
			cmp byte ptr [BayoHook::enemyHP_one_hit_kill_toggle], 1
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
bool BayoHook::witchTimeMultiplier_toggle = false;
float BayoHook::witchTimeMultiplier = 1.0;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fmul dword ptr [esi+0x00095D68] // might be game speed or something? 1 by default
		fdiv dword ptr [BayoHook::witchTimeMultiplier]
		jmp dword ptr [witchTimeMultiplier_jmp_ret]

		originalcode:
			fmul dword ptr [esi+0x00095D68]
			jmp dword ptr [witchTimeMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> infMagicHook;
uintptr_t infMagic_jmp_ret{ NULL };
bool BayoHook::inf_magic_toggle = false;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		push eax
		cmp byte ptr [BayoHook::inf_magic_toggle], 0
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
bool BayoHook::outgoingDamageMultiplier_toggle = false;
float outgoingDamageMultiplierXmm0Backup = 0.0f;
float BayoHook::outgoingDamageMultiplierMult = 1.0f;
static __declspec(naked) void OutgoingDamageMultiplierDetour(void) {
	_asm {
		mov [esi+0x000006B8], eax // originalcode, early bytes to avoid EnemyHPDetour
		mov [BayoHook::haloDisplayValue], eax
		cmp byte ptr [BayoHook::outgoingDamageMultiplier_toggle], 0
		je originalcode

		movss [outgoingDamageMultiplierXmm0Backup], xmm0 // xmm0 backup
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [BayoHook::outgoingDamageMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0,[outgoingDamageMultiplierXmm0Backup] // restore xmm0

		originalcode:
		sub eax,edi
		jmp dword ptr [outgoingDamageMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> customCameraDistanceHook;
uintptr_t customCameraDistance_jmp_ret{ NULL };
bool BayoHook::customCameraDistance_toggle = false;
float BayoHook::customCameraDistanceMultiplierMult = 0.0f;
static __declspec(naked) void CustomCameraDistanceDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::customCameraDistance_toggle], 0
		je originalcode

		cmp eax, 0xF2E630 // only change this value
		jne originalcode
		mulss xmm0,[BayoHook::customCameraDistanceMultiplierMult]

		originalcode:
		movss [eax],xmm0
		pop esi
		jmp dword ptr [customCameraDistance_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lessClothesHook;
uintptr_t lessClothes_jmp_ret{ NULL };
bool BayoHook::lessClothes_toggle = false;
static __declspec(naked) void LessClothesDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::lessClothes_toggle], 0
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
bool BayoHook::haloDisplay_toggle = false;
int BayoHook::haloDisplayValue = 0;
uintptr_t haloAddress = 0x5BB57B0;
static __declspec(naked) void HaloDisplayDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::haloDisplay_toggle], 0
		je originalcode

		cmp dword ptr [BayoHook::haloDisplayValue], 1
		jle originalcode
		mov eax, [BayoHook::haloDisplayValue]	

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
bool BayoHook::animSwap_toggle = false;
int BayoHook::animSwapCurrentAnim = 0;
int BayoHook::animSwapSourceAnim1 = -1;
int BayoHook::animSwapDesiredAnim1 = 0;
static __declspec(naked) void AnimSwapDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::animSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [animSwapCharacterAddress] // only edit player anim
		cmp [eax], ecx
		pop eax
		jne originalcode

		mov [BayoHook::animSwapCurrentAnim], edx
		cmp edx, [BayoHook::animSwapSourceAnim1]
		je newMove1
		jmp originalcode

		newMove1:
		mov edx, [BayoHook::animSwapDesiredAnim1]
		jmp originalcode


		originalcode:
		mov [ecx+0x0000034C], edx
		jmp dword ptr [animSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> inputIconsHook;
uintptr_t inputIcons_jmp_ret{ NULL };
bool BayoHook::inputIcons_toggle = false;
int BayoHook::inputIconsValue = 1; // 0 keyboard, 1 gamepad
static __declspec(naked) void InputIconsDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::inputIcons_toggle], 0
		je originalcode

		mov eax, [BayoHook::inputIconsValue]

		originalcode:
		mov [ebx+0x00000CA8], eax
		jmp dword ptr [inputIcons_jmp_ret]
	}
}

// update
void BayoHook::Update() {
	BayoHook::actorPlayable = (*(uintptr_t*)playerPointerAddress);
	BayoHook::halos = (*(int*)halosAddress);
	if (BayoHook::actorPlayable != NULL) {
		BayoHook::xyzpos[0] = (*(float*)(BayoHook::actorPlayable + 0xD0));
		BayoHook::xyzpos[1] = (*(float*)(BayoHook::actorPlayable + 0xD4));
		BayoHook::xyzpos[2] = (*(float*)(BayoHook::actorPlayable + 0xD8));
		BayoHook::playerHealth = (*(int*)(BayoHook::actorPlayable + 0x93508));
		BayoHook::remainingWitchTimeDuration = (*(float*)(BayoHook::actorPlayable + 0x95D5C));
	}
	BayoHook::chaptersPlayed = (*(int*)chaptersPlayedAddress);
	BayoHook::playerMagic = (*(float*)playerMagicAddress);
	BayoHook::comboPoints = (*(int*)comboPointsAddress);
	BayoHook::currentCharacter = (*(int*)currentCharacterAddress);
	BayoHook::thirdAccessory = (*(int*)thirdAccessoryAddress);
	BayoHook::hudDisplay = (*(bool*)hudDisplayAddress);
	//BayoHook::zone = (const char*)_baseAddress + 0x4374A24;
}

// setters
void BayoHook::SetXYZPos(float x, float y, float z) {
	(*(float*)(BayoHook::actorPlayable + 0xD0)) = x;
	(*(float*)(BayoHook::actorPlayable + 0xD4)) = y;
	(*(float*)(BayoHook::actorPlayable + 0xD8)) = z;
}

void BayoHook::SetHalos(int value) {
	(*(int*)halosAddress) = value;
}

void BayoHook::SetChaptersPlayed(int value) {
	(*(int*)chaptersPlayedAddress) = value;
}

void BayoHook::SetHealth(int value) {
	(*(int*)(BayoHook::actorPlayable + 0x93508)) = value;
}

void BayoHook::SetRemainingWitchTimeDuration(float value) {
	(*(float*)(BayoHook::actorPlayable + 0x95D5C)) = value;
}

void BayoHook::SetMagic(float value) {
	(*(float*)playerMagicAddress) = value;
}

void BayoHook::SetComboPoints(int value) {
	(*(int*)comboPointsAddress) = value;
}

void BayoHook::SetCurrentCharacter(int value) {
	(*(int*)currentCharacterAddress) = value;
}

void BayoHook::SetThirdAccessory(int value) {
	(*(int*)thirdAccessoryAddress) = value;
}

void BayoHook::SetHudDisplay(bool value) {
	(*(bool*)hudDisplayAddress) = value;
}

// dev functions
void BayoHook::_patch(char* dst, char* src, int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void BayoHook::_nop(char* dst, unsigned int size) {
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

void BayoHook::InitializeDetours(void) {
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

void BayoHook::onConfigLoad(const utils::Config& cfg) {
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

void BayoHook::onConfigSave(utils::Config& cfg) {
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
