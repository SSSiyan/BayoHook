#include "gamehook.hpp"

// patches
bool GameHook::takeNoDamage_toggle = false;
void GameHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		GameHook::_nop((char*)(0x9D4329), 6);
	else
		GameHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

bool GameHook::focusPatch_toggle = false;
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

bool GameHook::infJumps_toggle = false;
void GameHook::InfJumps(bool enabled) {
	if (enabled) 
		GameHook::_nop((char*)(0x9E8906), 6);
	else
		GameHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6);
}

bool GameHook::disableClicking_toggle = false;
void GameHook::DisableClicking(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC75747), 3);
	else
		GameHook::_patch((char*)(0xC75747), (char*)"\x89\x70\x04", 3);
}

bool GameHook::noClip_toggle= false;
void GameHook::NoClip(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC13250), 7);
	else
		GameHook::_patch((char*)(0xC13250), (char*)"\xC7\x41\x54\x01\x00\x00\x00", 7);
}

bool GameHook::disableDaze_toggle = false;
void GameHook::DisableDaze(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x430CF4), (char*) "\xEB\x20", 2);
	else
		GameHook::_patch((char*)(0x430CF4), (char*)"\x72\x20", 2);
}

bool GameHook::forceDaze_toggle = false;
void GameHook::ForceDaze(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x65C75C), (char*)"\xF3\x0F\x10\x86\x98\x0C\x00\x00", 8);
	else
		GameHook::_patch((char*)(0x65C75C), (char*)"\xF3\x0F\x10\x86\x9C\x0C\x00\x00", 8);
}

bool GameHook::freezeTimer_toggle = false;
void GameHook::FreezeTimer(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0x620C1D), 8);
	else
		GameHook::_patch((char*)(0x620C1D), (char*)"\xF3\x0F\x5C\x05\xF8\xD6\xD9\x00", 8);
}

// uses GameHook::enemyHP_no_damage_toggle
void GameHook::DisableKilling(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x4572D2), (char*) "\xEB\x0C", 2);
	else
		GameHook::_patch((char*)(0x4572D2), (char*)"\x75\x0C", 2);
}

bool GameHook::disableAfterBurnerBounce_toggle = false;
void GameHook::DisableAfterBurnerBounce(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x959B23), 6); // enemy
		GameHook::_patch((char*)(0x959E2C), (char*)"\xEB\x5E", 2); // wall
	}
	else {
		GameHook::_patch((char*)(0x959B23), (char*)"\x0F\x84\x37\x03\x00\x00", 6); // enemy
		GameHook::_patch((char*)(0x959E2C), (char*)"\x74\x5E", 2); // wall
	}
}

bool GameHook::areaJumpPatch_toggle = false;
void GameHook::AreaJumpPatch(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x4FC2FB), 6); // enemy
	}
	else {
		GameHook::_patch((char*)(0x4FC2FB), (char*)"\x89\x83\x28\x08\x00\x00", 6); // enemy
	}
}

bool GameHook::autoSkipCutscenes_toggle = false;
void GameHook::AutoSkipCutscenes(bool enabled) {
	if (enabled) {
		//GameHook::_patch((char*)(0x54493A), (char*)"\xEB\x0A", 2);
	}
	else {
		//GameHook::_patch((char*)(0x54493A), (char*)"\x75\x0A", 2);
	}
}

bool GameHook::lessClothes_toggle = false;
void GameHook::LessClothes(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x8B6BD2), 2);
	}
	else {
		GameHook::_patch((char*)(0x8B6BD2), (char*)"\x74\x0A", 2); // je 
	}
}

bool GameHook::disableLockOnDodge_toggle = false;
void GameHook::DisableLockOnDodge(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9E87CD), (char*)"\x39\xFF", 2);
	}
	else {
		GameHook::_patch((char*)(0x9E87CD), (char*)"\x39\xDF", 2);
	}
}

bool GameHook::noHoldDodgeOffset_toggle = false;
void GameHook::NoHoldDodgeOffset(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8EF16B), (char*)"\xEB\x11", 2);
	}
	else {
		GameHook::_patch((char*)(0x8EF16B), (char*)"\x74\x11", 2);
	}
}

bool GameHook::jumpOffset_toggle = false;
void GameHook::JumpOffset(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9E894F), (char*)"\xEB\x17", 2);
	}
	else {
		GameHook::_patch((char*)(0x9E894F), (char*)"\x74\x0F", 2);
	}
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
		// this hides test eax,eax in CE but it is still there
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
		cmp byte ptr [GameHook::damageDealtMultiplier_toggle], 0
		je originalcode

		movss [damageDealtMultiplierXmm0Backup], xmm0 // xmm0 backup
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [GameHook::damageDealtMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0,[damageDealtMultiplierXmm0Backup] // restore xmm0

		originalcode:
		sub eax,edi
		mov [GameHook::haloDisplayValue], eax // after damage subtraction
		jmp dword ptr [damageDealtMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> customCameraDistanceHook;
uintptr_t customCameraDistance_jmp_ret{ NULL };
bool GameHook::customCameraDistance_toggle = false;
float GameHook::customCameraDistance = 10.0f;
static __declspec(naked) void CustomCameraDistanceDetour(void) {
	_asm {
		cmp byte ptr [GameHook::customCameraDistance_toggle], 0
		je originalcode

		fld dword ptr [GameHook::customCameraDistance]
		jmp dword ptr [customCameraDistance_jmp_ret]

		originalcode:
		fld dword ptr [edi+0x00000B50]
		jmp dword ptr [customCameraDistance_jmp_ret]
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

std::unique_ptr<FunctionHook> initialAngelSlayerFloorHook;
uintptr_t initialAngelSlayerFloor_jmp_ret{ NULL };
int GameHook::initialAngelSlayerFloor = 0;
static __declspec(naked) void InitialAngelSlayerFloorDetour(void) {
	_asm {
		push eax
		push esi
		mov eax, [GameHook::angelSlayerFloorAddress]
		mov esi, [GameHook::initialAngelSlayerFloor]
		mov [eax], esi
		pop esi
		pop eax
		jmp dword ptr [initialAngelSlayerFloor_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> cancellableAfterBurnerHook;
uintptr_t cancellableAfterBurner_jmp_ret{ NULL };
bool GameHook::cancellableAfterBurner_toggle = false;
uintptr_t cancellableMovesCall = 0x9E85E0;
static __declspec(naked) void CancellableAfterBurnerDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableAfterBurner_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		cmp [esi+0x00000350], ebx
		jmp dword ptr [cancellableAfterBurner_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> cancellableFallingKickHook;
uintptr_t cancellableFallingKick_jmp_ret{ NULL };
bool GameHook::cancellableFallingKick_toggle = false;
uintptr_t CancellableFallingKickDefaultCall = 0x433220;
static __declspec(naked) void CancellableFallingKickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableFallingKick_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		call dword ptr [CancellableFallingKickDefaultCall]
		jmp dword ptr [cancellableFallingKick_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> turboHook;
uintptr_t turbo_jmp_ret{ NULL };
bool GameHook::turbo_toggle = false;
float GameHook::turboValue = 1.0f;
static __declspec(naked) void TurboHookDetour(void) {
	_asm {
		cmp byte ptr [GameHook::turbo_toggle], 0
		je originalcode

		movss xmm0, [GameHook::turboValue]

		originalcode:
		movss [edi+0x44], xmm0
		jmp dword ptr [turbo_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> altTeleInputHook;
uintptr_t altTeleInput_jmp_ret{ NULL };
uintptr_t altTeleInput_jmp_je = 0x8BE5B6;
bool GameHook::altTeleInput_toggle = false;
static int altTeleInput = 0x400; // dpad down = 0x4, taunt = 0x400
static __declspec(naked) void AltTeleInputDetour(void) {
	_asm {
		cmp byte ptr [GameHook::altTeleInput_toggle], 0
		je originalcode

		push eax
		mov eax, [altTeleInput]
		test [ebx+0x00094B48], eax
		pop eax
		jmp dword ptr [altTeleInput_jmp_ret]

		originalcode:
		test [ebx+0x00094B48], eax
		je jmp_je //Bayonetta.exe+4BE5B6
		cmp [ebx+0x000939A0], esi
		jmp dword ptr [altTeleInput_jmp_ret]

		jmp_je:
		jmp dword ptr [altTeleInput_jmp_je]
	}
}

std::unique_ptr<FunctionHook> altTauntInputHook;
uintptr_t altTauntInput_jmp_ret{ NULL };
static int altTauntInputTauntRemap = 4;
static __declspec(naked) void AltTauntInputDetour(void) {
	_asm {
		cmp byte ptr [GameHook::altTeleInput_toggle], 0
		je originalcode

		mov eax,[ecx+eax*4+0x2C]
		test eax, 0x400
		jz retcode
		mov eax, [altTauntInputTauntRemap]
		jmp retcode

		originalcode:
		mov eax,[ecx+eax*4+0x2C]

		retcode:
		ret 0004
	}
}

std::unique_ptr<FunctionHook> disableSlowmoHook;
uintptr_t disableSlowmo_jmp_ret{ NULL };
static float disableSlowmoDefaultSpeed = 1.0f;
bool GameHook::disableSlowmo_toggle = false;
static __declspec(naked) void DisableSlowmoDetour(void) {
	_asm {
		cmp byte ptr [GameHook::disableSlowmo_toggle], 0
		je originalcode

		movss xmm0, [disableSlowmoDefaultSpeed]
		jmp dword ptr [disableSlowmo_jmp_ret]

		originalcode:
		movss xmm0, [ecx+0x38]
		jmp dword ptr [disableSlowmo_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lowerDivekickHook;
uintptr_t lowerDivekick_jmp_ret{ NULL };
static float lowerDivekickTime = 7.0f;
bool GameHook::lowerDivekick_toggle = false;
static __declspec(naked) void LowerDivekickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::lowerDivekick_toggle], 0
		je originalcode

		movss xmm0, [lowerDivekickTime]
		comiss xmm0,[esi+0x00093594]
		xorps xmm0,xmm0 // restore xmm0
		jmp dword ptr [lowerDivekick_jmp_ret]

		originalcode:
		comiss xmm0, [esi+0x00093594]
		jmp dword ptr [lowerDivekick_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> dualAfterBurnerHook;
uintptr_t dualAfterBurner_jmp_ret{ NULL };
bool GameHook::dualAfterBurner_toggle = false;
uintptr_t dualAfterBurnerCall = 0x9E33D0;
static __declspec(naked) void DualAfterBurnerDetour(void) {
	_asm {
		call dword ptr [dualAfterBurnerCall]
		cmp byte ptr [GameHook::dualAfterBurner_toggle], 0
		je jmpcode

		// reuse stack
		// movss xmm0,[Bayonetta.exe+9A0DD4]
		sub esp, 0x14
		// movss [esp+10],xmm0
		// movss xmm0,[Bayonetta.exe+A280B0]
		// movss [esp+0C],xmm0
		// movss xmm0,[Bayonetta.exe+A2718C]
		// movss [esp+08],xmm0
		// xorps xmm0,xmm0
		// movss [esp+04],xmm0
		// movss xmm0,[Bayonetta.exe+99D79C]
		// movss [esp],xmm0
		push 0x03
		mov ecx,esi
		call dword ptr [dualAfterBurnerCall]

		jmpcode:
		jmp dword ptr [dualAfterBurner_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> getMotNameHook;
uintptr_t getMotName_jmp_ret{ NULL };
bool GameHook::getMotName_toggle = false;
uintptr_t getMotName_playerTestAddress = NULL;
uintptr_t getMotName_weaponTestAddress = NULL;
char GameHook::getMotName_playerMotString[0x128]{};
char GameHook::getMotName_weaponMotString[0x128]{};
static __declspec(naked) void GetMotNameDetour(void) {
	_asm {
		cmp byte ptr [GameHook::getMotName_toggle], 0
		je originalcode

		push eax
		cmp word ptr [edi], 0x6C70 // 'pl'
		je writeplayermotname
		cmp word ptr [edi], 0x7077 // 'wp'
		je writeweaponmotname
		jmp originalcodepop

		writeplayermotname:
		cmp [getMotName_playerTestAddress], edi
		mov [getMotName_playerTestAddress], edi
		je originalcodepop
		mov eax, [edi]
		mov dword ptr [GameHook::getMotName_playerMotString], eax
		mov eax, [edi+0x04]
		mov dword ptr [GameHook::getMotName_playerMotString+0x04], eax
		mov eax, [edi+0x08]
		mov dword ptr [GameHook::getMotName_playerMotString+0x08], eax
		mov eax, [edi+0x0C]
		mov dword ptr [GameHook::getMotName_playerMotString+0x0C], eax
		mov eax, [edi+0x10]
		mov dword ptr [GameHook::getMotName_playerMotString+0x10], eax
		mov eax, [edi+0x14]
		mov dword ptr [GameHook::getMotName_playerMotString+0x14], eax
		mov eax, [edi+0x18]
		mov dword ptr [GameHook::getMotName_playerMotString+0x18], eax
		mov eax, [edi+0x1C]
		mov dword ptr [GameHook::getMotName_playerMotString+0x1C], eax
		jmp originalcodepop

		writeweaponmotname:
		cmp [getMotName_weaponTestAddress], edi
		mov [getMotName_weaponTestAddress], edi
		je originalcodepop
		mov eax, [edi]
		mov dword ptr [GameHook::getMotName_weaponMotString], eax
		mov eax, [edi+0x04]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x04], eax
		mov eax, [edi+0x08]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x08], eax
		mov eax, [edi+0x0C]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x0C], eax
		mov eax, [edi+0x10]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x10], eax
		mov eax, [edi+0x14]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x14], eax
		mov eax, [edi+0x18]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x18], eax
		mov eax, [edi+0x1C]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x1C], eax
		jmp originalcodepop

		originalcodepop:
		pop eax

		originalcode:
		mov al, [edi]
		xor esi, esi
		mov ebp, ecx
		jmp dword ptr [getMotName_jmp_ret]
	}
}

// int GameHook::saveStates_SavedEnemyMovePart = 0;
// float GameHook::saveStates_SavedEnemyAnimFrame = 0.0f;
bool GameHook::saveStatesHotkeys_toggle = false;
int GameHook::saveStates_SavedEnemyMoveID = 0;
float GameHook::saveStates_SavedEnemyXYZPos[3]{0, 0, 0};
int GameHook::saveStates_SavedPlayerMoveID = 0;
float GameHook::saveStates_SavedPlayerXYZPos[3];
void GameHook::SaveStates_SaveState() {
	if (GameHook::saveStatesHotkeys_toggle) {
		uintptr_t* enemy_ptr = (uintptr_t*)GameHook::enemyLockedOnAddress;
		uintptr_t enemy_base = *enemy_ptr;
		if (enemy_base) {
			// GameHook::saveStates_SavedEnemyAnimFrame = *(float*)(enemy_base + 0x3E4);
			GameHook::saveStates_SavedEnemyMoveID = *(int*)(enemy_base + 0x34C);
			// GameHook::saveStates_SavedEnemyMovePart = *(int*)(enemy_base + 0x350);
			GameHook::saveStates_SavedEnemyXYZPos[0] = *(float*)(enemy_base + 0xD0);
			GameHook::saveStates_SavedEnemyXYZPos[1] = *(float*)(enemy_base + 0xD4);
			GameHook::saveStates_SavedEnemyXYZPos[2] = *(float*)(enemy_base + 0xD8);
		}
	}
}
void GameHook::SaveStates_LoadState() {
	if (GameHook::saveStatesHotkeys_toggle) {
		uintptr_t* enemy_ptr = (uintptr_t*)GameHook::enemyLockedOnAddress;
		uintptr_t enemy_base = *enemy_ptr;
		if (enemy_base) {
			// *(float*)(enemy_base + 0x3E4) = GameHook::saveStates_SavedEnemyAnimFrame;
			*(int*)(enemy_base + 0x34C) = GameHook::saveStates_SavedEnemyMoveID;
			*(int*)(enemy_base + 0x350) = 0; // cancel current anim
			*(float*)(enemy_base + 0xD0) = GameHook::saveStates_SavedEnemyXYZPos[0];
			*(float*)(enemy_base + 0xD4) = GameHook::saveStates_SavedEnemyXYZPos[1];
			*(float*)(enemy_base + 0xD8) = GameHook::saveStates_SavedEnemyXYZPos[2];
		}
	}
}

void GameHook::WeaponSwapCaller(void) {
	uintptr_t weaponSwapCallAddress = 0x00C43FE1;
	__asm {
		pusha
		pushf
		call weaponSwapCallAddress
		popf
		popa
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
	install_hook_absolute(0xA941FA, customCameraDistanceHook, &CustomCameraDistanceDetour, &customCameraDistance_jmp_ret, 6);
	install_hook_absolute(0x4250F7, haloDisplayHook, &HaloDisplayDetour, &haloDisplay_jmp_ret, 5);
	install_hook_absolute(0x4BD053, animSwapHook, &AnimSwapDetour, &animSwap_jmp_ret, 6);
	install_hook_absolute(0x411CD4, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 13);
	install_hook_absolute(0x4A8EFF, easierMashHook, &EasierMashDetour, &easierMash_jmp_ret, 5);
	install_hook_absolute(0x41C8B5, initialAngelSlayerFloorHook, &InitialAngelSlayerFloorDetour, &initialAngelSlayerFloor_jmp_ret, 10);
	install_hook_absolute(0x95ABD3, cancellableAfterBurnerHook, &CancellableAfterBurnerDetour, &cancellableAfterBurner_jmp_ret, 6);
	install_hook_absolute(0x952142, cancellableFallingKickHook, &CancellableFallingKickDetour, &cancellableFallingKick_jmp_ret, 5);
	install_hook_absolute(0x513FC7, turboHook, &TurboHookDetour, &turbo_jmp_ret, 5);
	install_hook_absolute(0x8BE592, altTeleInputHook, &AltTeleInputDetour, &altTeleInput_jmp_ret, 14);
	install_hook_absolute(0x50137D, altTauntInputHook, &AltTauntInputDetour, &altTauntInput_jmp_ret, 7);
	install_hook_absolute(0x513C1E, disableSlowmoHook, &DisableSlowmoDetour, &disableSlowmo_jmp_ret, 5);
	install_hook_absolute(0x9E93B9, lowerDivekickHook, &LowerDivekickDetour, &lowerDivekick_jmp_ret, 7);
	install_hook_absolute(0x94CAAF, dualAfterBurnerHook, &DualAfterBurnerDetour, &dualAfterBurner_jmp_ret, 5);
	install_hook_absolute(0xC798A7, getMotNameHook, &GetMotNameDetour, &getMotName_jmp_ret, 6);
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
	forceDaze_toggle = cfg.get<bool>("ForceDazeToggle").value_or(false);
	ForceDaze(forceDaze_toggle);
	freezeTimer_toggle = cfg.get<bool>("FreezeTimerToggle").value_or(false);
	FreezeTimer(freezeTimer_toggle);
	showMessages_toggle = cfg.get<bool>("ShowMessagesToggle").value_or(true);
	disableAfterBurnerBounce_toggle = cfg.get<bool>("DisableAfterBurnerBounceToggle").value_or(false);
	DisableAfterBurnerBounce(disableAfterBurnerBounce_toggle);
	autoSkipCutscenes_toggle = cfg.get<bool>("AutoSkipCutscenesToggle").value_or(false);
	AutoSkipCutscenes(autoSkipCutscenes_toggle);
	disableLockOnDodge_toggle = cfg.get<bool>("DisableLockOnDodgeToggle").value_or(false);
	DisableLockOnDodge(disableLockOnDodge_toggle);
	noHoldDodgeOffset_toggle = cfg.get<bool>("NoHoldDodgeOffsetToggle").value_or(false);
	NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
	jumpOffset_toggle = cfg.get<bool>("JumpOffsetToggle").value_or(false);
	JumpOffset(jumpOffset_toggle);
	//areaJumpPatch_toggle = cfg.get<bool>("AreaJumpPatchToggle").value_or(false);
	//AreaJumpPatch(areaJumpPatch_toggle);

	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	DisableKilling(enemyHP_no_damage_toggle);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
	damageDealtMultiplier_toggle = cfg.get<bool>("DamageDealtMultiplierToggle").value_or(false);
	damageDealtMultiplierMult = cfg.get<float>("DamageDealtMultiplierMult").value_or(1.0f);
	customCameraDistance_toggle = cfg.get<bool>("CustomCameraDistanceToggle").value_or(false);
	customCameraDistance = cfg.get<float>("CustomCameraDistance").value_or(10.0f);
	lessClothes_toggle = cfg.get<bool>("LessClothesToggle").value_or(false);
	haloDisplay_toggle = cfg.get<bool>("HaloDisplayToggle").value_or(false);
	inputIcons_toggle = cfg.get<bool>("InputIconsToggle").value_or(false);
	inputIconsValue = cfg.get<int>("InputIconsValue").value_or(0);
	easierMash_toggle = cfg.get<bool>("EasierMashToggle").value_or(false);
	showComboUI_toggle = cfg.get<bool>("ShowComboUIToggle").value_or(false);
	comboUI_X = cfg.get<float>("ComboUI_X").value_or(0.875f);
	comboUI_Y = cfg.get<float>("ComboUI_Y").value_or(0.215f);
	initialAngelSlayerFloor = cfg.get<int>("InitialAngelSlayerFloor").value_or(0);
	cancellableAfterBurner_toggle = cfg.get<bool>("CancellableAfterBurner").value_or(false);
	cancellableFallingKick_toggle = cfg.get<bool>("CancellableFallingKick").value_or(false);
	turbo_toggle = cfg.get<bool>("TurboToggle").value_or(false);
	turboValue = cfg.get<float>("TurboValue").value_or(1.0f);
	altTeleInput_toggle = cfg.get<bool>("AltTeleInputToggle").value_or(false);
	disableSlowmo_toggle = cfg.get<bool>("DisableSlowmoToggle").value_or(false);
	lowerDivekick_toggle = cfg.get<bool>("LowerDivekickToggle").value_or(false);
	dualAfterBurner_toggle = cfg.get<bool>("DualAfterBurnerToggle").value_or(false);
	saveStatesHotkeys_toggle = cfg.get<bool>("SaveStatesHotkeysToggle").value_or(false);
}

void GameHook::onConfigSave(utils::Config& cfg) {
	// patches
	cfg.set<bool>("TakeNoDamageToggle", takeNoDamage_toggle);
	cfg.set<bool>("FocusPatchToggle", focusPatch_toggle);
	cfg.set<bool>("InfJumpsToggle", infJumps_toggle);
	cfg.set<bool>("DisableDazeToggle", disableDaze_toggle);
	cfg.set<bool>("ForceDazeToggle", forceDaze_toggle);
	cfg.set<bool>("FreezeTimerToggle", freezeTimer_toggle);
	cfg.set<bool>("ShowMessagesToggle", showMessages_toggle);
	cfg.set<bool>("DisableAfterBurnerBounceToggle", disableAfterBurnerBounce_toggle);
	cfg.set<bool>("AutoSkipCutscenesToggle", autoSkipCutscenes_toggle);
	cfg.set<bool>("DisableLockOnDodgeToggle", disableLockOnDodge_toggle);
	cfg.set<bool>("NoHoldDodgeOffsetToggle", noHoldDodgeOffset_toggle);
	cfg.set<bool>("JumpOffsetToggle", jumpOffset_toggle);
	//cfg.set<bool>("AreaJumpPatchToggle", areaJumpPatch_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);
	cfg.set<bool>("DamageDealtMultiplierToggle", damageDealtMultiplier_toggle);
	cfg.set<float>("DamageDealtMultiplierMult", damageDealtMultiplierMult);
	cfg.set<bool>("CustomCameraDistanceToggle", customCameraDistance_toggle);
	cfg.set<float>("CustomCameraDistance", customCameraDistance);
	cfg.set<bool>("LessClothesToggle", lessClothes_toggle);
	cfg.set<bool>("HaloDisplayToggle", haloDisplay_toggle);
	cfg.set<bool>("InputIconsToggle", inputIcons_toggle);
	cfg.set<int>("InputIconsValue", inputIconsValue);
	cfg.set<bool>("EasierMashToggle", easierMash_toggle);
	cfg.set<bool>("ShowComboUIToggle", showComboUI_toggle);
	cfg.set<float>("ComboUI_X", comboUI_X);
	cfg.set<float>("ComboUI_Y", comboUI_Y);
	cfg.set<int>("InitialAngelSlayerFloor", initialAngelSlayerFloor);
	cfg.set<bool>("CancellableAfterBurner", cancellableAfterBurner_toggle);
	cfg.set<bool>("CancellableFallingKick", cancellableFallingKick_toggle);
	cfg.set<bool>("TurboToggle", turbo_toggle);
	cfg.set<float>("TurboValue", turboValue);
	cfg.set<bool>("AltTeleInputToggle", altTeleInput_toggle);
	cfg.set<bool>("DisableSlowmoToggle", disableSlowmo_toggle);
	cfg.set<bool>("LowerDivekickToggle", lowerDivekick_toggle);
	cfg.set<bool>("DualAfterBurnerToggle", dualAfterBurner_toggle);
	cfg.set<bool>("SaveStatesHotkeysToggle", saveStatesHotkeys_toggle);

	cfg.save(GameHook::cfgString);
}
