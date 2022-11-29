#include "gamehook.hpp"

// patch toggles
bool GameHook::takeNoDamage_toggle(false);
bool GameHook::focusPatch_toggle(false);
bool GameHook::infJumps_toggle(false);
bool GameHook::disableClicking_toggle(false);
bool GameHook::noClip_toggle(false);
bool GameHook::disableDaze_toggle(false);
bool GameHook::freezeTimer_toggle(false);

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
		GameHook::_patch((char*)(0x49E519), (char*)"\x75\x17", 2);
		GameHook::_patch((char*)(0x411DB8), (char*)"\x0F\x85\x81", 3);
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

void GameHook::NoClip(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC13250), 7);
	else
		GameHook::_patch((char*)(0xC13250), (char*)"\xC7\x41\x54\x01\x00\x00\x00", 7);
}

void GameHook::DisableDaze(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x430CF4), (char*) "\xEB\x20", 2);
	else
		GameHook::_patch((char*)(0x430CF4), (char*)"\x72\x20", 2);
}

void GameHook::FreezeTimer(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0x620C1D), 8);
	else
		GameHook::_patch((char*)(0x620C1D), (char*)"\xF3\x0F\x5C\x05\xF8\xD6\xD9\x00", 8);
}

// detours
std::unique_ptr<FunctionHook> enemyHPHook;
uintptr_t enemyHP_jmp_ret{ NULL };
bool GameHook::enemyHP_no_damage_toggle = false;
bool GameHook::enemyHP_one_hit_kill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [GameHook::enemyHP_one_hit_kill_toggle], 1
		je one_hit_kill
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::enemyHP_no_damage_toggle], 1
		je no_damage
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

		mov eax, [GameHook::playerMagicAddress]
		mov dword ptr [eax], 0x44fa0000 // 2000

		originalcode:
		mov eax, [GameHook::playerMagicAddress] // i hate that i have to do this
		movss xmm0, [eax]
		pop eax
		jmp dword ptr [infMagic_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> damageDealtMultiplierHook;
uintptr_t damageDealtMultiplier_jmp_ret{ NULL };
bool GameHook::damageDealtMultiplier_toggle = false;
float damageDealtMultiplierXmm0Backup = 0.0f;
float GameHook::damageDealtMultiplierMult = 1.0f;
static __declspec(naked) void DamageDealtMultiplierDetour(void) {
	_asm {
		mov [esi+0x000006B8], eax // originalcode, early bytes to avoid EnemyHPDetour
		mov [GameHook::haloDisplayValue], eax
		cmp byte ptr [GameHook::damageDealtMultiplier_toggle], 0
		je originalcode

		movss [damageDealtMultiplierXmm0Backup], xmm0 // xmm0 backup
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [GameHook::damageDealtMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0,[damageDealtMultiplierXmm0Backup] // restore xmm0

		originalcode:
		sub eax,edi
		jmp dword ptr [damageDealtMultiplier_jmp_ret]
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
uintptr_t haloDisplayAddress = 0x5BB57B0;
static __declspec(naked) void HaloDisplayDetour(void) {
	_asm {
		cmp byte ptr [GameHook::haloDisplay_toggle], 0
		je originalcode

		cmp dword ptr [GameHook::haloDisplayValue], 1
		jle originalcode
		mov eax, [GameHook::haloDisplayValue]	

		originalcode:
		push esi
		mov esi,[haloDisplayAddress] // i still hate this
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
		cmp dword ptr [ebx+0x000003E8], 00
		mov [ebx+0x00000CA8], eax
		jmp dword ptr [inputIcons_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> easierMashHook;
uintptr_t easierMash_jmp_ret{ NULL };
bool GameHook::easierMash_toggle = false;
static __declspec(naked) void EasierMashDetour(void) {
	_asm {
		cmp byte ptr [GameHook::easierMash_toggle], 0
		je originalcode

		mov dword ptr [esi+0x30], 0x3fc00000 // 1.5f

		originalcode:
		divss xmm0, [esi+0x30]
		jmp dword ptr [easierMash_jmp_ret]
	}
}

int GameHook::saveStates_CurrentEnemy = 1;
int GameHook::saveStates_SavedEnemyMoveID = 0;
float GameHook::saveStates_SavedEnemyAnimFrame = 0.0f;
float GameHook::saveStates_SavedEnemyXYZPos[3]{};
int GameHook::saveStates_SavedPlayerMoveID;
float GameHook::saveStates_SavedPlayerXYZPos[3];
void GameHook::SaveStates_SaveState() {
	uintptr_t* enemy_ptr = (uintptr_t*)((uintptr_t)enemySlotsAddress + saveStates_CurrentEnemy * 4); // 0x5A56A8C
	uintptr_t enemy_base = *enemy_ptr; 
	if (enemy_base) {
		GameHook::saveStates_SavedEnemyMoveID = *(int*)(enemy_base + 0x34C);
		GameHook::saveStates_SavedEnemyAnimFrame = *(float*)(enemy_base + 0x3E4);
		GameHook::saveStates_SavedEnemyXYZPos[0] = *(float*)(enemy_base + 0xD0);
		GameHook::saveStates_SavedEnemyXYZPos[1] = *(float*)(enemy_base + 0xD4);
		GameHook::saveStates_SavedEnemyXYZPos[2] = *(float*)(enemy_base + 0xD8);
	}
}
void GameHook::SaveStates_LoadState() {
	uintptr_t* enemy_ptr = (uintptr_t*)((uintptr_t)enemySlotsAddress + saveStates_CurrentEnemy * 4); // 0x5A56A8C
	uintptr_t enemy_base = *enemy_ptr;
	if (enemy_base) {
		*(int*)(enemy_base + 0x34C) = GameHook::saveStates_SavedEnemyMoveID;
		*(int*)(enemy_base + 0x350) = 0; // cancel current anim
		*(float*)(enemy_base + 0x3E4) = GameHook::saveStates_SavedEnemyAnimFrame;
		*(float*)(enemy_base + 0xD0) = GameHook::saveStates_SavedEnemyXYZPos[0];
		*(float*)(enemy_base + 0xD4) = GameHook::saveStates_SavedEnemyXYZPos[1];
		*(float*)(enemy_base + 0xD8) = GameHook::saveStates_SavedEnemyXYZPos[2];
	}
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
	install_hook_absolute(0x4572B2, damageDealtMultiplierHook, &DamageDealtMultiplierDetour, &damageDealtMultiplier_jmp_ret, 8);
	install_hook_absolute(0xC52491, customCameraDistanceHook, &CustomCameraDistanceDetour, &customCameraDistance_jmp_ret, 5);
	install_hook_absolute(0x8B6C55, lessClothesHook, &LessClothesDetour, &lessClothes_jmp_ret, 6);
	install_hook_absolute(0x4250F7, haloDisplayHook, &HaloDisplayDetour, &haloDisplay_jmp_ret, 5);
	install_hook_absolute(0x4BD053, animSwapHook, &AnimSwapDetour, &animSwap_jmp_ret, 6);
	install_hook_absolute(0x411CD4, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 13);
	install_hook_absolute(0x4A8EFF, easierMashHook, &EasierMashDetour, &easierMash_jmp_ret, 5);
}

void GameHook::onConfigLoad(const utils::Config& cfg) {
	// patches
	takeNoDamage_toggle = cfg.get<bool>("TakeNoDamageToggle").value_or(false);
	TakeNoDamage(takeNoDamage_toggle);
	focusPatch_toggle = cfg.get<bool>("FocusPatchToggle").value_or(false);
	FocusPatch(focusPatch_toggle);
	infJumps_toggle = cfg.get<bool>("InfJumpsToggle").value_or(false);
	InfJumps(infJumps_toggle);
	disableDaze_toggle = cfg.get<bool>("DisableDazeToggle").value_or(false);
	DisableDaze(disableDaze_toggle);
	freezeTimer_toggle = cfg.get<bool>("FreezeTimerToggle").value_or(false);
	FreezeTimer(freezeTimer_toggle);
	showMessages_toggle = cfg.get<bool>("ShowMessagesToggle").value_or(true);
	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
	damageDealtMultiplier_toggle = cfg.get<bool>("DamageDealtMultiplierToggle").value_or(false);
	damageDealtMultiplierMult = cfg.get<float>("DamageDealtMultiplierMult").value_or(1.0f);
	customCameraDistance_toggle = cfg.get<bool>("CustomCameraDistanceToggle").value_or(false);
	customCameraDistanceMultiplierMult = cfg.get<float>("CustomCameraDistanceMultiplier").value_or(1.0f);
	lessClothes_toggle = cfg.get<bool>("LessClothesToggle").value_or(false);
	haloDisplay_toggle = cfg.get<bool>("HaloDisplayToggle").value_or(false);
	inputIcons_toggle = cfg.get<bool>("InputIconsToggle").value_or(false);
	inputIconsValue = cfg.get<int>("InputIconsValue").value_or(false);
	easierMash_toggle = cfg.get<bool>("EasierMashToggle").value_or(false);
	showComboUI_toggle = cfg.get<bool>("ShowComboUIToggle").value_or(false);
	comboUI_X = cfg.get<float>("ComboUI_X").value_or(0.875f);
	comboUI_Y = cfg.get<float>("ComboUI_Y").value_or(0.215f);
}

void GameHook::onConfigSave(utils::Config& cfg) {
	// patches
	cfg.set<bool>("TakeNoDamageToggle", takeNoDamage_toggle);
	cfg.set<bool>("FocusPatchToggle", focusPatch_toggle);
	cfg.set<bool>("InfJumpsToggle", infJumps_toggle);
	cfg.set<bool>("DisableDazeToggle", disableDaze_toggle);
	cfg.set<bool>("FreezeTimerToggle", freezeTimer_toggle);
	cfg.set<bool>("ShowMessagesToggle", showMessages_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);
	cfg.set<bool>("DamageDealtMultiplierToggle", damageDealtMultiplier_toggle);
	cfg.set<float>("DamageDealtMultiplierMult", damageDealtMultiplierMult);
	cfg.set<bool>("CustomCameraDistanceToggle", customCameraDistance_toggle);
	cfg.set<float>("CustomCameraDistanceMultiplier", customCameraDistanceMultiplierMult);
	cfg.set<bool>("LessClothesToggle", lessClothes_toggle);
	cfg.set<bool>("HaloDisplayToggle", haloDisplay_toggle);
	cfg.set<bool>("InputIconsToggle", inputIcons_toggle);
	cfg.set<int>("InputIconsValue", inputIconsValue);
	cfg.set<bool>("EasierMashToggle", easierMash_toggle);
	cfg.set<bool>("ShowComboUIToggle", showComboUI_toggle);
	cfg.set<float>("ComboUI_X", comboUI_X);
	cfg.set<float>("ComboUI_Y", comboUI_Y);

	cfg.save(GameHook::cfgString);
}
