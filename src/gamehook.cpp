#include "gamehook.hpp"
#include <thread>

// system
float GameHook::windowWidth = 0.0f;
float GameHook::windowHeightHack = 0.0f;
float GameHook::windowHeightBorder = 0.0f;
float GameHook::inputItemWidth = 0.0f;
float GameHook::sameLineWidth = 0.0f;
float GameHook::windowScalingFactor = 1.0f;
float GameHook::maxWindowHeight = 0.0f;
float GameHook::comboUI_X = 0.0f;
float GameHook::comboUI_Y = 0.0f;
bool GameHook::showMessages_toggle = false;
bool GameHook::showComboUI_toggle = false;
int GameHook::showMessageTimerF1 = 0;
int GameHook::showMessageTimerF2 = 0;
int GameHook::showMessageTimerF3 = 0;
int GameHook::showMessageTimerF4 = 0;
int GameHook::showMessageTimerF5 = 0;
int GameHook::showMessageTimerF6 = 0;

// update
uintptr_t GameHook::playerPointerAddress = 0xEF5A60;
uintptr_t GameHook::halosAddress = 0x5AA74B4;
uintptr_t GameHook::chaptersPlayedAddress = 0x5AA736C;
uintptr_t GameHook::playerMagicAddress = 0x5AA74AC;
uintptr_t GameHook::comboPointsAddress = 0x5BB519C;
uintptr_t GameHook::comboMultiplierAddress = 0x5BB51A0;
uintptr_t GameHook::currentCharacterAddress = 0x5AA7484;
uintptr_t GameHook::currentCostumeAddress = 0x5AA747C;
uintptr_t GameHook::thirdAccessoryAddress = 0x5AA7468;
uintptr_t GameHook::hudDisplayAddress = 0xF2B714;
uintptr_t GameHook::enemyLockedOnAddress = 0xF2B744;
uintptr_t GameHook::enemySlotsAddress = 0x5A56A88;
uintptr_t GameHook::angelSlayerFloorAddress = 0x509E87C;
uintptr_t GameHook::difficultyAddress = 0x5A985A0;
uintptr_t GameHook::areaJumpAddress = 0x5A978E8;
uintptr_t GameHook::WeaponA1Address = 0x5AA741C;
uintptr_t GameHook::WeaponA2Address = 0x5AA7420;
uintptr_t GameHook::WeaponB1Address = 0x5AA742C;
uintptr_t GameHook::WeaponB2Address = 0x5AA7430;

bool GameHook::comboMakerToggle = false;
bool GameHook::comboMaker_toggles[maxComboMakers]{};
int  GameHook::comboMakerMoveIDs[maxComboMakers]{};
int  GameHook::comboMakerMoveParts[maxComboMakers]{};
int  GameHook::comboMakerStringIDs[maxComboMakers]{};

int GameHook::desiredThirdAccessory = 0;

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
	if (enabled) {
		GameHook::_nop((char*)(0x9E8906), 6); // jumps
		GameHook::_nop((char*)(0x9A120F), 6); // bird jumps
		GameHook::_nop((char*)(0x9E8D8D), 6); // wall jumps
	}
	else {
		GameHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6); // jumps
		GameHook::_patch((char*)(0x9A120F), (char*)"\xFF\x86\x78\x35\x09\x00", 6); // bird jumps
		GameHook::_patch((char*)(0x9E8D8D), (char*)"\x89\xBE\x90\x35\x09\x00", 6); // wall jumps
	}
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

bool GameHook::easyCutsceneSkip_toggle = false;
void GameHook::EasyCutsceneSkip(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x90\x90", 2);
		GameHook::_patch((char*)(0x48FEC6), (char*)"\xF7\x05\xCC\x93\xA4\x05\x16\x00\x00\x00", 10); // X Pressed
	}
	else {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x74\x10", 2); // R2 Held
		GameHook::_patch((char*)(0x48FEC6), (char*)"\xF7\x05\xCC\x93\xA4\x05\x00\x02\x00\x00", 10); // Select Pressed
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

bool GameHook::alwaysWalkOnWalls_toggle = false;
void GameHook::AlwaysWalkOnWalls(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x520496), 10);
		GameHook::_patch((char*)(0x9CB8C4), (char*)"\x81\x0D\x24\xDE\x1A\x05\x00\x00\x10\x00", 10);
	}
	else {
		GameHook::_patch((char*)(0x520496), (char*)"\x81\x25\x24\xDE\x1A\x05\xFF\xFF\xEF\xFF", 10);
		GameHook::_patch((char*)(0x9CB8C4), (char*)"\xF7\x05\x24\xDE\x1A\x05\x00\x00\x10\x00", 10);
	}
}

bool GameHook::getMoreHalos_toggle = false;
void GameHook::GetMoreHalos (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x49479A), 2);
	}
	else {
		GameHook::_patch((char*)(0x49479A), (char*)"\x76\x0A", 2); // jna
	}
}

bool GameHook::moreEnemyAttacks_toggle = false;
void GameHook::MoreEnemyAttacks (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x65DEC1), 6);
	}
	else {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\x0F\x84\x51\x06\x00\x00", 6); // je
	}
}

bool GameHook::lessEnemyAttacks_toggle = false;
void GameHook::LessEnemyAttacks (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\xE9\x52\x06\x00\x00\x90", 6); // jmp
	}
	else {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\x0F\x84\x51\x06\x00\x00", 6); // je
	}
}

bool GameHook::infBirdTime_toggle = false;
void GameHook::InfBirdTime (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8BDD17), (char*)"\xEB\x1D", 2); // jmp
	}
	else {
		GameHook::_patch((char*)(0x8BDD17), (char*)"\x75\x1D", 2); // jne
	}
}

bool GameHook::weaponSwapOffset_toggle = false;
void GameHook::WeaponSwapOffset (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9EB456), (char*)"\xEB\x1C\x90", 3); // jmp, nop
	}
	else {
		GameHook::_patch((char*)(0x9EB456), (char*)"\x0F\x57\xC0", 3); // xorps xmm0,xmm0
	}
}

bool GameHook::retainPillowTalkCharge_toggle = false;
void GameHook::RetainPillowTalkCharge (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0xA2B491), 8);
	}
	else {
		GameHook::_patch((char*)(0xA2B491), (char*)"\xF3\x0F\x11\x86\x2C\x33\x00\x00", 8);
	}
}

bool GameHook::swapMashToHold_toggle = false;
void GameHook::SwapMashToHold (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9D80DA), 2);
	}
	else {
		GameHook::_patch((char*)(0x9D80DA), (char*)"\x74\x4E", 2);
	}
}

bool GameHook::sixtyFpsCutscenes_toggle = true;
void GameHook::SixtyFpsCutscenes(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x45B4A7), 2);
		GameHook::_patch((char*)(0x45B4BA), (char*)"\xEB", 1); // jmp
	}
	else {
		GameHook::_patch((char*)(0x45B4A7), (char*)"\x74\x28", 2); // jz
		GameHook::_patch((char*)(0x45B4BA), (char*)"\x74", 1); // jz
	}
}

bool GameHook::disableFpsLimiter_toggle = false;
void GameHook::DisableFpsLimiter(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0xC54340), (char*)"\xC3", 1); // retn 
		GameHook::_patch((char*)(0xC54430), (char*)"\xC3", 1); // retn 
		GameHook::_patch((char*)(0x49E25D), (char*)"\x90\xE9", 2); // jmp
	}
	else {
		GameHook::_patch((char*)(0xC54340), (char*)"\xF3", 1); // movss
		GameHook::_patch((char*)(0xC54430), (char*)"\xF3", 1); // movss
		GameHook::_patch((char*)(0x49E25D), (char*)"\x0F\x84", 2); // jz
	}
}

bool GameHook::jeanneBayoWT_toggle = true;
void GameHook::JeanneBayoWT(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8EF3B8), (char*)"\xEB\x0C", 2); // jmp
	}
	else {
		GameHook::_patch((char*)(0x8EF3B8), (char*)"\x75\x0C", 2); // jne
	}
}

bool GameHook::infDivekick_toggle = true;
void GameHook::InfDivekick(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9E93F5), 2);
	}
	else {
		GameHook::_patch((char*)(0x9E93F5), (char*)"\x73\x24", 2); // jae
	}
}

bool GameHook::tauntWithTimeBracelet_toggle = false;
void GameHook::TauntWithTimeBracelet(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9E74CF), 2);
	}
	else {
		GameHook::_patch((char*)(0x9E74CF), (char*)"\x75\x69", 2); // jne
	}
}

bool GameHook::hideHalos_toggle = false;
void GameHook::HideHalos(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0xC28AA2), 5);
	}
	else {
		GameHook::_patch((char*)(0xC28AA2), (char*)"\xE8\x89\x35\x00\x00", 5); // call Bayonetta.exe+82C030
	}
}

bool GameHook::multiplayerPatch_toggle = false;
void GameHook::MultiplayerPatch(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8BD007), (char*)"\xEB", 1); // jmp Bayonetta.exe+4BD00F
	}
	else {
		GameHook::_patch((char*)(0x8BD007), (char*)"\x74", 1); // je Bayonetta.exe+4BD00F
	}
}

bool GameHook::noEnragedHitstop_toggle = false;
void GameHook::NoEnragedHitstop(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x62AD50), (char*)"\xEB", 1); // jmp Bayonetta.exe+22AD6B
	}
	else {
		GameHook::_patch((char*)(0x62AD50), (char*)"\x74", 1); // je Bayonetta.exe+22AD6B
	}
}

bool GameHook::noHitstop_toggle = false;
void GameHook::NoHitstop(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x452445), 2);
	}
	else {
		GameHook::_patch((char*)(0x452445), (char*)"\x72\x1B", 2); // jb Bayonetta.exe+52462
	}
}

bool GameHook::unbanClimaxBrace_toggle = false;
void GameHook::UnbanClimaxBrace(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9E2116), (char*)"\x00", 1); // mov [ecx+00096BA0],00000000
	}
	else {
		GameHook::_patch((char*)(0x9E2116), (char*)"\x01", 1); // mov [ecx+00096BA0],00000001
	}
}

bool GameHook::parryOffset_toggle = false;
void GameHook::ParryOffset(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8F0CA6), (char*)"\x83\xC4\x04\x90\x90", 5); // add esp,4 nop nop // Parry
		GameHook::_patch((char*)(0x8F0D45), (char*)"\x83\xC4\x04\x90\x90", 5); // add esp,4 nop nop // Perfect Parry
	}
	else {
		GameHook::_patch((char*)(0x8F0CA6), (char*)"\xE8\xF5\x1B\xFE\xFF", 5); // call Bayonetta.exe+4D28A0 // Parry
		GameHook::_patch((char*)(0x8F0D45), (char*)"\xE8\x56\x1B\xFE\xFF", 5); // call Bayonetta.exe+4D28A0 // Perfect Parry
	}
}

bool GameHook::removeVignette_toggle = false;
void GameHook::RemoveVignette(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x43B06F), (char*)"\x90\x90\x90\x90", 4); // nop 4 
	}
	else {
		GameHook::_patch((char*)(0x43B06F), (char*)"\xF3\x0F\x58\xD3", 4); // addss xmm2,xmm3
	}
}

bool GameHook::disableDoubleTapHeelKick_toggle = false;
void GameHook::DisableDoubleTapHeelKick(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9CE1CC), 8);
	}
	else {
		GameHook::_patch((char*)(0x9CE1CC), (char*)"\xF3\x0F\x11\x86\x18\x36\x09\x00", 8); // puts 10 into doubletap timer
	}
}

bool GameHook::freezeDifficulty_toggle = false;
void GameHook::FreezeDifficulty(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x5018C4), 6);
	}
	else {
		GameHook::_patch((char*)(0x5018C4), (char*)"\x89\x81\xD0\x06\x00\x00", 6); // mov [ecx+000006D0],eax
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
float GameHook::witchTimeMultiplier = 1.0f;
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
float GameHook::inf_magic_value = 1200.0f;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		push eax
		mov eax, [GameHook::playerMagicAddress]
		cmp byte ptr [GameHook::inf_magic_toggle], 0
		je originalcode

		movss xmm0, [GameHook::inf_magic_value]
		movss [eax], xmm0

		originalcode:
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
		sub eax, edi
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
		mov esi, [haloDisplayAddress] // i still hate this
		mov [esi], eax
		pop esi
		jmp dword ptr [haloDisplay_jmp_ret]
	}
}

bool GameHook::moveIDSwapsToggle = false;
bool GameHook::moveIDSwap_toggles[maxMoveIDSwaps]{};
int GameHook::moveIDSwapSourceMoves[maxMoveIDSwaps]{};
int GameHook::moveIDSwapSwappedMoves[maxMoveIDSwaps]{};
int __stdcall GetSwappedMoveID(int nextMoveID) {
    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
		if (GameHook::moveIDSwap_toggles[i] && GameHook::moveIDSwapSourceMoves[i] == nextMoveID) {
            return GameHook::moveIDSwapSwappedMoves[i];
        }
    }
    return -1;
}

std::unique_ptr<FunctionHook> moveIDSwapHook;
uintptr_t moveIDSwap_jmp_ret{ NULL };
static __declspec(naked) void MoveIDSwapDetour(void) { // player in ecx
	_asm {
		cmp byte ptr [GameHook::moveIDSwapsToggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], ecx
		pop eax
		jne originalcode

		push eax // +4
		push ecx // +8
		push edx // +C
		push edx // nextMoveID
		call dword ptr GetSwappedMoveID
		cmp eax, -1
		je dontReplace
		pop edx
		pop ecx
		mov [ecx+0x0000034C], eax
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [ecx+0x0000034C], edx
		retcode:
		jmp dword ptr [moveIDSwap_jmp_ret]
	}
}

bool GameHook::stringSwapsToggle = false;
bool GameHook::stringIDSwap_toggles[maxStringSwaps];
int  GameHook::stringIDSwapSourceStrings[maxStringSwaps];
int  GameHook::stringIDSwapDesiredStrings[maxStringSwaps];
int __stdcall GetSwappedStringID(int nextStringID) {
    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
		if (GameHook::stringIDSwap_toggles[i] && GameHook::stringIDSwapSourceStrings[i] == nextStringID) {
            return GameHook::stringIDSwapDesiredStrings[i];
        }
    }
    return -1;
}

std::unique_ptr<FunctionHook> punchStringIDSwapHook;
uintptr_t punchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void PunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwapsToggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push edx // nextStringID
		call dword ptr GetSwappedStringID

		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], edx
		retcode:
		jmp dword ptr [punchStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> latePunchStringIDSwapHook;
uintptr_t latePunchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LatePunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwapsToggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push eax // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], eax
		retcode:
		jmp dword ptr [latePunchStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> kickStringIDSwapHook;
uintptr_t kickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void KickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwapsToggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push edx // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], edx
		retcode:
		jmp dword ptr [kickStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lateKickStringIDSwapHook;
uintptr_t lateKickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LateKickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwapsToggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push ecx // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], ecx
		retcode:
		jmp dword ptr [lateKickStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> inputIconsHook;
uintptr_t inputIcons_jmp_ret{ NULL };
bool GameHook::inputIcons_toggle = false;
int GameHook::inputIconsValue = 0; // 0 keyboard, 1 gamepad
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
bool GameHook::openMenuPause_toggle = false;
bool GameHook::turbo_toggle = false;
float GameHook::turboValue = 1.0f;
float GameHook::turboZero = 0.0f;
static __declspec(naked) void TurboHookDetour(void) {
	_asm {
		cmp byte ptr [GameHook::openMenuPause_toggle], 1
		je zerospeed
		jmp turbocheck

		zerospeed:
		cmp byte ptr [Base::Data::ShowMenu], 0
		je turbocheck
		movss xmm0, [GameHook::turboZero]
		jmp originalcode

		turbocheck:
		cmp byte ptr [GameHook::turbo_toggle], 0
		je originalcode
		movss xmm0, [GameHook::turboValue]
		jmp originalcode

		originalcode:
		movss [edi+0x44], xmm0
		jmp dword ptr [turbo_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> altTeleInputHook;
uintptr_t altTeleInput_jmp_ret{ NULL };
uintptr_t altTeleInput_jmp_jle = 0x8BE5AC;
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
		jnz teleport
		jmp jmp_je

		teleport:
		mov dword ptr [ebx+0x0009399C], 0x00000001
		jmp dword ptr [altTeleInput_jmp_ret]

		originalcode:
		test [ebx+0x00094B48], eax
		je jmp_je
		cmp [ebx+0x000939A0], esi
		jle jmp_jle
		cmp byte ptr [GameHook::omnicancelTele_toggle], 1 // don't take 4 orbs if omnicancel is active!
		je teleport
		mov dword ptr [ebx+0x0009399C], 0x0000000A // frames mashed
		jmp dword ptr [altTeleInput_jmp_ret] // Bayonetta.exe+4BE5A2, accept teleport

		jmp_jle:
		jmp dword ptr [altTeleInput_jmp_jle]

		jmp_je:
		jmp dword ptr [altTeleInput_jmp_je] // Bayonetta.exe+4BE5B6, deny teleport
	}
}

std::unique_ptr<FunctionHook> tauntWithTimeBracelet2Hook; // tap taunt
uintptr_t tauntWithTimeBracelet2_jmp_ret{ NULL };
static __declspec(naked) void TauntWithTimeBracelet2Detour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax, 4

		originalcode:
		test [esi+0x00094B4C], eax
		jmp [tauntWithTimeBracelet2_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> tauntWithTimeBracelet3Hook; // hold taunt
uintptr_t tauntWithTimeBracelet3_jmp_ret{ NULL };
static __declspec(naked) void TauntWithTimeBracelet3Detour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax, 4

		originalcode:
		test [ebx+0x00094B44], eax
		jmp [tauntWithTimeBracelet3_jmp_ret]
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
		comiss xmm0, [esi+0x00093594]
		xorps xmm0, xmm0 // restore xmm0
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
		mov ecx, esi
		call dword ptr [dualAfterBurnerCall]

		jmpcode:
		jmp dword ptr [dualAfterBurner_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> loadReplaceHook;
uintptr_t loadReplace_jmp_ret{ NULL };
bool GameHook::loadReplace_toggle = false;
static __declspec(naked) void LoadReplaceDetour(void) {
	_asm {
		push ecx
		cmp byte ptr [GameHook::loadReplace_toggle], 0
		je originalcode

		cmp edx, 0x622180 // AA
		je angelattack
		jmp originalcode

		angelattack:
		mov edx, 0x00619DD0 // stage select
		jmp originalcode

		originalcode:
		mov ecx, [eax+0x08]
		call edx
		jmp dword ptr [loadReplace_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> longerPillowTalkChargeHook;
uintptr_t longerPillowTalkCharge_jmp_ret{ NULL };
bool GameHook::longerPillowTalkCharge_toggle = false;
float longerPillowTalkChargeMult = 2.0f;
static __declspec(naked) void LongerPillowTalkChargeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::longerPillowTalkCharge_toggle], 0
		je originalcode

		movss xmm0, [esp+0x04]
		mulss xmm0, [longerPillowTalkChargeMult]
		jmp dword ptr [longerPillowTalkCharge_jmp_ret]

		originalcode:
		movss xmm0, [esp+0x04] // from [00DA0DE8]
		jmp dword ptr [longerPillowTalkCharge_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> alwaysWitchTimeHook;
uintptr_t alwaysWitchTime_jmp_ret{ NULL };
bool GameHook::alwaysWitchTime_toggle = false;
float alwaysWitchTimeTimer = 120.0f;
static __declspec(naked) void AlwaysWitchTimeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::alwaysWitchTime_toggle], 0
		je originalcode

		movss xmm1, [alwaysWitchTimeTimer]
		jmp dword ptr [alwaysWitchTime_jmp_ret]

		originalcode:
		movss xmm1, [esi+0x00000704]
		jmp dword ptr [alwaysWitchTime_jmp_ret]
	}
}

int __stdcall GetCustomWeave(LocalPlayer* player) {
    int moveID = player->moveID;
    for (int i = 0; i < GameHook::customWeaveCount; ++i) {
        if (GameHook::customWeaves_toggles[i] && GameHook::customWeaveMoveIDArray[i] == moveID) {
            return GameHook::customWeaveArray[i];
        }
    }
    return -1;
}

bool GameHook::customWeaveToggle = false;
bool GameHook::customWeaves_toggles[customWeaveCount]{};
int GameHook::customWeaveArray[customWeaveCount]{};
int GameHook::customWeaveMoveIDArray[customWeaveCount]{};
std::unique_ptr<FunctionHook> customWeavesHook;
uintptr_t customWeaves_jmp_ret{ NULL };
static __declspec(naked) void CustomWeavesDetour(void) { // player in esi
	_asm {
		// cmp byte ptr [GameHook::customWeaves_toggle], 0
		// je originalcode

		push eax // +4
		push ecx // +8
		push edx // +C
		push esi // player
		call dword ptr GetCustomWeave
		cmp eax, -1
		je dontReplace
		mov [esp+0xC+8], eax
		dontReplace:
		pop edx
		pop ecx
		pop eax

	// originalcode:
		push ebx
		push ebp
		mov ebp, [esp+0x0C]
		jmp dword ptr [customWeaves_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> omnicancelTeleHook;
uintptr_t omnicancelTele_jmp_ret{ NULL };
bool GameHook::omnicancelTele_toggle = false;
uintptr_t omnicancelTele_call = 0x009E6FA0;
uintptr_t omnicancelTele_ogcode = 0x05A97ED0;
static __declspec(naked) void OmnicancelTeleDetour(void) { // player in ebx
	_asm {
		pushfd
		cmp byte ptr [GameHook::omnicancelTele_toggle], 0
		je originalcode

		test ebx, ebx // check player exists, probably not necessary
		je originalcode
		cmp dword ptr [ebx+0x0009399C], 00 // extra safety, check if teleport is queued
		je originalcode

		cmp dword ptr [ebx+0x34C], 245
		ja originalcode

		push eax
		push ecx
		push edx
		mov ecx, ebx // player
		call dword ptr omnicancelTele_call
		pop edx
		pop ecx
		pop eax

		originalcode:
		popfd
		push 0x0B
		mov ecx, [omnicancelTele_ogcode]
		// mov ecx, [ecx]
		jmp dword ptr [omnicancelTele_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> teleportComboActionHook;
uintptr_t teleportComboAction_jmp_ret{ NULL };
bool GameHook::teleportComboAction_toggle = false;
static __declspec(naked) void TeleportComboActionDetour(void) { // player in ebx
	_asm {
		cmp byte ptr[GameHook::teleportComboAction_toggle], 0
		je originalcode

		mov dword ptr [esi+0x95C80], 0x41700000 // 15f

		originalcode:
		mov eax,[esi+0x00000350]
		jmp dword ptr [teleportComboAction_jmp_ret]
	}
}


std::unique_ptr<FunctionHook> fixThirdAccessoryHook;
uintptr_t fixThirdAccessory_jmp_ret{ NULL };
static uintptr_t fixThirdAccessoryCall = 0x4332F0;
bool GameHook::fixThirdAccessory_toggle = false;
static __declspec(naked) void FixThirdAccessoryDetour(void) { // player in ebx
	_asm {
		//
			cmp byte ptr[GameHook::fixThirdAccessory_toggle], 0
			je originalcode
		//
			push 2
			call dword ptr [fixThirdAccessoryCall]
			add esp, 4 // pop

		originalcode:
			add esp, 8
			mov ebp, eax
			jmp dword ptr [fixThirdAccessory_jmp_ret]
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

std::unique_ptr<FunctionHook> pl0012Hook;
const char* pl0012att = "pl0012.dat\\pl0012.att";
const char* pl0012flg = "pl0012.dat\\pl0012.flg";
static __declspec(naked) void pl0012Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15139064
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15139040
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		push    [pl0012att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     esi, 12973536
		mov     edi, 12958688
		push    15139396
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139368
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139340
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139312
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		push    [pl0012flg]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L19
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L7
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L7
		add     edi, eax
		xor		ebp, ebp

		L9:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L8:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L9

		L7:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L10
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L10
		xor		edi, edi
		lea     ebp, [esi + eax]

		L12:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L11
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L11:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L12

		L10:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L13
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L13
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L15:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L14
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L14:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L15

		L13:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp		L5

		L19:
		xor		edi, edi
		mov     esi, 4862688

		L6:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L16:
		add     edi, 1
		cmp     edi, 4
		jne		L6
		mov     edi, 8
		mov     esi, 4862688

		L18:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L17
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L17:
		add     edi, 1
		cmp     edi, 12
		jne		L18
		jmp		L13
	}
}

std::unique_ptr<FunctionHook> pl0031Hook;
const char* pl0031att = "pl0031.dat\\pl0031.att";
const char* pl0031flg = "pl0031.dat\\pl0031.flg";
static __declspec(naked) void pl0031Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15147736
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15147712
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15147684
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147656
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147628
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl0031att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl0031flg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L85
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 2
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    10
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    3
		push    91
		call    esi
		mov     ecx, ebx
		push    0
		push    4
		push    92
		call    esi
		mov     ecx, ebx
		push    0
		push    5
		push    93
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    94
		call    esi
		mov     ecx, ebx
		push    0
		push    7
		push    95
		call    esi
		mov     ecx, ebx
		push    0
		push    8
		push    96
		call    esi
		mov     ecx, ebx
		push    0
		push    9
		push    97
		call    esi
		mov     ecx, ebx
		push    0
		push    13
		push    98
		call    esi
		mov     ecx, ebx
		push    0
		push    14
		push    99
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    100
		call    esi
		add     esp, 20
		jmp		L5

		L85:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    4
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    5
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    6
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    15
		call    eax
		add     esp, 12
		test    eax, eax
		je		L26
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L26:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    16
		call    eax
		add     esp, 12
		test    eax, eax
		je		L27
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L27:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    17
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		sub     esp, 12
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -69
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		mov     eax, 4849216
		mov     DWORD PTR[ecx + 84], 18
		push    1
		call    eax
		add     esp, 12
		jmp		L16
	}
}

std::unique_ptr<FunctionHook> pl004cHook;
const char* pl004catt = "pl004c.dat\\pl004c.att";
const char* pl004cflg = "pl004c.dat\\pl004c.flg";
static __declspec(naked) void pl004cDetour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15156328
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15156304
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15156276
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156248
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156220
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156192
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl004catt]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl004cflg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L77
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp L5

		L77:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    8
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    9
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    10
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    11
		call    eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		jmp		L16
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
void GameHook::SaveStates_LoadState() {
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

void GameHook::WeaponSwapCaller(void) {
	uintptr_t weaponSwapCallAddress = 0xC43ED0;
	__asm {
		pushad
		pushfd
		call weaponSwapCallAddress
		popfd
		popad
	}
}

LocalPlayer* GameHook::GetLocalPlayer() {
	if (LocalPlayer* player = *(LocalPlayer**)GameHook::playerPointerAddress)
		return player;
	else
		return nullptr;
}

bool GameHook::CheckCanSpawnEntity() {
    uintptr_t testAddr = 0x5BBB9EC;
    
    uintptr_t ptr1 = *(uintptr_t*)testAddr;
    if (!ptr1) return false;
    
    uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x10);
    if (!ptr2) return false;
    
    int value = *(int*)(ptr2 + 0x18);
    return value == 4;
}

void GameHook::SpawnEntity(int entityID, int a2, int a3) {
    // yeah
    std::thread([entityID, a2, a3]() {
        // wait
        while (!CheckCanSpawnEntity()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        uintptr_t spawnEntityAddr = 0x510450;
        uintptr_t ecxAddr = 0x5ABB860;
        SpawnEntityFunc spawnEntity = (SpawnEntityFunc)spawnEntityAddr;
        spawnEntity((uintptr_t*)ecxAddr, entityID, a2, a3);
    }).detach();
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
	install_hook_absolute(0x4BD053, moveIDSwapHook, &MoveIDSwapDetour, &moveIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2A82, punchStringIDSwapHook, &PunchStringIDSwapDetour, &punchStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x8D2AC4, latePunchStringIDSwapHook, &LatePunchStringIDSwapDetour, &latePunchStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AE5, kickStringIDSwapHook, &KickStringIDSwapDetour, &kickStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AA3, lateKickStringIDSwapHook, &LateKickStringIDSwapDetour, &lateKickStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x411CD4, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 13);
	install_hook_absolute(0x4A8EFF, easierMashHook, &EasierMashDetour, &easierMash_jmp_ret, 5);
	install_hook_absolute(0x41C8B5, initialAngelSlayerFloorHook, &InitialAngelSlayerFloorDetour, &initialAngelSlayerFloor_jmp_ret, 10);
	install_hook_absolute(0x95ABD3, cancellableAfterBurnerHook, &CancellableAfterBurnerDetour, &cancellableAfterBurner_jmp_ret, 6);
	install_hook_absolute(0x952142, cancellableFallingKickHook, &CancellableFallingKickDetour, &cancellableFallingKick_jmp_ret, 5);
	install_hook_absolute(0x513FC7, turboHook, &TurboHookDetour, &turbo_jmp_ret, 5);
	install_hook_absolute(0x8BE592, altTeleInputHook, &AltTeleInputDetour, &altTeleInput_jmp_ret, 26);
	install_hook_absolute(0x9E751A, tauntWithTimeBracelet2Hook, &TauntWithTimeBracelet2Detour, &tauntWithTimeBracelet2_jmp_ret, 6);
	install_hook_absolute(0x8BE5C2, tauntWithTimeBracelet3Hook, &TauntWithTimeBracelet3Detour, &tauntWithTimeBracelet3_jmp_ret, 6);
	install_hook_absolute(0x513C1E, disableSlowmoHook, &DisableSlowmoDetour, &disableSlowmo_jmp_ret, 5);
	install_hook_absolute(0x9E93B9, lowerDivekickHook, &LowerDivekickDetour, &lowerDivekick_jmp_ret, 7);
	install_hook_absolute(0x94CAAF, dualAfterBurnerHook, &DualAfterBurnerDetour, &dualAfterBurner_jmp_ret, 5);
	// install_hook_absolute(0xC798A7, getMotNameHook, &GetMotNameDetour, &getMotName_jmp_ret, 6);
	install_hook_absolute(0x6222D0, loadReplaceHook, &LoadReplaceDetour, &loadReplace_jmp_ret, 6);
	install_hook_absolute(0x4CCCA0, longerPillowTalkChargeHook, &LongerPillowTalkChargeDetour, &longerPillowTalkCharge_jmp_ret, 6);
	install_hook_absolute(0x8EF527, alwaysWitchTimeHook, &AlwaysWitchTimeDetour, &alwaysWitchTime_jmp_ret, 8);
	install_hook_absolute(0x87F270, customWeavesHook, &CustomWeavesDetour, &customWeaves_jmp_ret, 6);
	install_hook_absolute(0x8BE5B6, omnicancelTeleHook, &OmnicancelTeleDetour, &omnicancelTele_jmp_ret, 7);
	install_hook_absolute(0x9A0020, teleportComboActionHook, &TeleportComboActionDetour, &teleportComboAction_jmp_ret, 6);
	install_hook_absolute(0x97ED07, fixThirdAccessoryHook, &FixThirdAccessoryDetour, &fixThirdAccessory_jmp_ret, 5);
	// int& thirdAccessoryValue = *(int*)GameHook::thirdAccessoryAddress;
	// thirdAccessoryValue = GameHook::desiredThirdAccessory;
	install_hook_absolute(0x9F5AF0, pl0012Hook, &pl0012Detour, NULL, 0);
	install_hook_absolute(0x9FC890, pl0031Hook, &pl0031Detour, NULL, 0);
	install_hook_absolute(0xA17420, pl004cHook, &pl004cDetour, NULL, 0);
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
	easyCutsceneSkip_toggle = cfg.get<bool>("EasyCutsceneSkipToggle").value_or(false);
	EasyCutsceneSkip(easyCutsceneSkip_toggle);
	disableLockOnDodge_toggle = cfg.get<bool>("DisableLockOnDodgeToggle").value_or(false);
	DisableLockOnDodge(disableLockOnDodge_toggle);
	noHoldDodgeOffset_toggle = cfg.get<bool>("NoHoldDodgeOffsetToggle").value_or(false);
	NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
	jumpOffset_toggle = cfg.get<bool>("JumpOffsetToggle").value_or(false);
	JumpOffset(jumpOffset_toggle);
	alwaysWalkOnWalls_toggle = cfg.get<bool>("AlwaysWalkOnWallsToggle").value_or(false);
	AlwaysWalkOnWalls(alwaysWalkOnWalls_toggle);
	getMoreHalos_toggle = cfg.get<bool>("GetMoreHalosToggle").value_or(false);
	GetMoreHalos(getMoreHalos_toggle);
	moreEnemyAttacks_toggle = cfg.get<bool>("MoreEnemyAttacksToggle").value_or(false);
	MoreEnemyAttacks(moreEnemyAttacks_toggle);
	lessEnemyAttacks_toggle = cfg.get<bool>("LessEnemyAttacksToggle").value_or(false);
	LessEnemyAttacks(lessEnemyAttacks_toggle);
	infBirdTime_toggle = cfg.get<bool>("InfBirdTimeToggle").value_or(false);
	InfBirdTime(infBirdTime_toggle);
	weaponSwapOffset_toggle = cfg.get<bool>("WeaponSwapOffsetToggle").value_or(false);
	WeaponSwapOffset(weaponSwapOffset_toggle);
	retainPillowTalkCharge_toggle = cfg.get<bool>("RetainPillowTalkChargeToggle").value_or(false);
	RetainPillowTalkCharge(retainPillowTalkCharge_toggle);
	swapMashToHold_toggle = cfg.get<bool>("SwapMashToHoldToggle").value_or(false);
	SwapMashToHold(swapMashToHold_toggle);
	sixtyFpsCutscenes_toggle = cfg.get<bool>("60FpsCutscenes").value_or(false);
	SixtyFpsCutscenes(sixtyFpsCutscenes_toggle);
	disableFpsLimiter_toggle = cfg.get<bool>("DisableFpsLimiter").value_or(false);
	DisableFpsLimiter(disableFpsLimiter_toggle);
	jeanneBayoWT_toggle = cfg.get<bool>("JeanneBayoWTToggle").value_or(false);
	JeanneBayoWT(jeanneBayoWT_toggle);
	infDivekick_toggle = cfg.get<bool>("InfDivekickToggle").value_or(false);
	InfDivekick(infDivekick_toggle);
	// areaJumpPatch_toggle = cfg.get<bool>("AreaJumpPatchToggle").value_or(false);
	// AreaJumpPatch(areaJumpPatch_toggle);
	parryOffset_toggle = cfg.get<bool>("ParryOffsetToggle").value_or(false);
	ParryOffset(parryOffset_toggle);
	removeVignette_toggle = cfg.get<bool>("RemoveVignetteToggle").value_or(false);
	RemoveVignette(removeVignette_toggle);
	disableDoubleTapHeelKick_toggle = cfg.get<bool>("DisableDoubleTapHeelKickToggle").value_or(false);
	DisableDoubleTapHeelKick(disableDoubleTapHeelKick_toggle);
	freezeDifficulty_toggle = cfg.get<bool>("freezeDifficulty_toggle").value_or(false);
	FreezeDifficulty(freezeDifficulty_toggle);
	hideHalos_toggle = cfg.get<bool>("hideHalos_toggle").value_or(false);
	HideHalos(hideHalos_toggle);
	multiplayerPatch_toggle = cfg.get<bool>("multiplayerPatch_toggle").value_or(false);
	MultiplayerPatch(multiplayerPatch_toggle);
	noEnragedHitstop_toggle = cfg.get<bool>("noEnragedHitstop_toggle").value_or(false);
	NoEnragedHitstop(noEnragedHitstop_toggle);
	noHitstop_toggle = cfg.get<bool>("noHitstop_toggle").value_or(false);
	NoHitstop(noHitstop_toggle);
	unbanClimaxBrace_toggle = cfg.get<bool>("unbanClimaxBrace_toggle").value_or(false);
	UnbanClimaxBrace(unbanClimaxBrace_toggle);
	tauntWithTimeBracelet_toggle = cfg.get<bool>("TauntWithTimeBraceletToggle").value_or(false);
	TauntWithTimeBracelet(tauntWithTimeBracelet_toggle);

	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	DisableKilling(enemyHP_no_damage_toggle);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
	inf_magic_value = cfg.get<float>("InfMagicValue").value_or(1200.0f);
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
	cancellableAfterBurner_toggle = cfg.get<bool>("CancellableAfterBurnerToggle").value_or(false);
	cancellableFallingKick_toggle = cfg.get<bool>("CancellableFallingKickToggle").value_or(false);
	openMenuPause_toggle = cfg.get<bool>("OpenMenuPauseToggle").value_or(false);
	turbo_toggle = cfg.get<bool>("TurboToggle").value_or(false);
	turboValue = cfg.get<float>("TurboValue").value_or(1.0f);
	altTeleInput_toggle = cfg.get<bool>("AltTeleInputToggle").value_or(false);
	teleportComboAction_toggle = cfg.get<bool>("TeleportComboAction_toggle").value_or(false);
	disableSlowmo_toggle = cfg.get<bool>("DisableSlowmoToggle").value_or(false);
	lowerDivekick_toggle = cfg.get<bool>("LowerDivekickToggle").value_or(false);
	dualAfterBurner_toggle = cfg.get<bool>("DualAfterBurnerToggle").value_or(false);
	loadReplace_toggle = cfg.get<bool>("LoadReplaceToggle").value_or(false);
	longerPillowTalkCharge_toggle = cfg.get<bool>("LongerPillowTalkChargeToggle").value_or(false);
	alwaysWitchTime_toggle = cfg.get<bool>("AlwaysWitchTimeToggle").value_or(false);
	saveStatesHotkeys_toggle = cfg.get<bool>("SaveStatesHotkeysToggle").value_or(false);
	omnicancelTele_toggle = cfg.get<bool>("omnicancelTele_toggle").value_or(false);
	fixThirdAccessory_toggle = cfg.get<bool>("fixThirdAccessory_toggle").value_or(false);

	moveIDSwapsToggle = cfg.get<bool>("moveIDSwapsToggle").value_or(false);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		moveIDSwap_toggles[i] = cfg.get<bool>(std::string("MoveIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		moveIDSwapSourceMoves[i] = cfg.get<int>(std::string("MoveIDSwapSourceMoves[") + std::to_string(i) + "]").value_or(-1);
		moveIDSwapSwappedMoves[i] = cfg.get<int>(std::string("MoveIDSwapSwappedMoves[") + std::to_string(i) + "]").value_or(-1);
	}

	stringSwapsToggle = cfg.get<bool>("stringSwapsToggle").value_or(false);
	for (int i = 0; i < maxStringSwaps; ++i) {
		stringIDSwap_toggles[i] = cfg.get<bool>(std::string("stringIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		stringIDSwapSourceStrings[i] = cfg.get<int>(std::string("stringIDSwapSourceStrings[") + std::to_string(i) + "]").value_or(-1);
		stringIDSwapDesiredStrings[i] = cfg.get<int>(std::string("stringIDSwapDesiredStrings[") + std::to_string(i) + "]").value_or(-1);
	}

	comboMakerToggle = cfg.get<bool>("comboMakerToggle").value_or(false);
	for (int i = 0; i < maxComboMakers; ++i) {
		comboMaker_toggles[i] = cfg.get<bool>(std::string("ComboMaker_toggles[") + std::to_string(i) + "]").value_or(false);
		comboMakerMoveIDs[i] = cfg.get<int>(std::string("ComboMakerMoveIDs[") + std::to_string(i) + "]").value_or(-1);
		comboMakerMoveParts[i] = cfg.get<int>(std::string("ComboMakerMoveParts[") + std::to_string(i) + "]").value_or(-1);
		comboMakerStringIDs[i] = cfg.get<int>(std::string("ComboMakerStringIDs[") + std::to_string(i) + "]").value_or(-1);
	}

	customWeaveToggle = cfg.get<bool>("customWeaveToggle").value_or(false);
	for (int i = 0; i < customWeaveCount; ++i) {
		customWeaves_toggles[i] = cfg.get<bool>(std::string("CustomWeaves_toggles[") + std::to_string(i) + "]").value_or(false);
		customWeaveMoveIDArray[i] = cfg.get<int>(std::string("CustomWeaveMoveIDArray[") + std::to_string(i) + "]").value_or(-1);
		customWeaveArray[i] = cfg.get<int>(std::string("CustomWeaveArray[") + std::to_string(i) + "]").value_or(-1);
	}

	//tick
	GameHook::desiredThirdAccessory = cfg.get<int>("DesiredThirdAccessoryValue").value_or(0);
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
	cfg.set<bool>("EasyCutsceneSkipToggle", easyCutsceneSkip_toggle);
	cfg.set<bool>("DisableLockOnDodgeToggle", disableLockOnDodge_toggle);
	cfg.set<bool>("NoHoldDodgeOffsetToggle", noHoldDodgeOffset_toggle);
	cfg.set<bool>("JumpOffsetToggle", jumpOffset_toggle);
	cfg.set<bool>("AlwaysWalkOnWallsToggle", alwaysWalkOnWalls_toggle);
	cfg.set<bool>("GetMoreHalosToggle", getMoreHalos_toggle);
	cfg.set<bool>("MoreEnemyAttacksToggle", moreEnemyAttacks_toggle);
	cfg.set<bool>("LessEnemyAttacksToggle", lessEnemyAttacks_toggle);
	cfg.set<bool>("InfBirdTimeToggle", infBirdTime_toggle);
	cfg.set<bool>("WeaponSwapOffsetToggle", weaponSwapOffset_toggle);
	cfg.set<bool>("RetainPillowTalkChargeToggle", retainPillowTalkCharge_toggle);
	cfg.set<bool>("SwapMashToHoldToggle", swapMashToHold_toggle);
	cfg.set<bool>("60FpsCutscenes", sixtyFpsCutscenes_toggle);
	cfg.set<bool>("DisableFpsLimiter", disableFpsLimiter_toggle);
	cfg.set<bool>("JeanneBayoWTToggle", jeanneBayoWT_toggle);
	cfg.set<bool>("InfDivekickToggle", infDivekick_toggle);
	cfg.set<bool>("ParryOffsetToggle", parryOffset_toggle);
	cfg.set<bool>("RemoveVignetteToggle", removeVignette_toggle);
	cfg.set<bool>("DisableDoubleTapHeelKickToggle", disableDoubleTapHeelKick_toggle);
	cfg.set<bool>("freezeDifficulty_toggle", freezeDifficulty_toggle);
	cfg.set<bool>("hideHalos_toggle", hideHalos_toggle);
	cfg.set<bool>("multiplayerPatch_toggle", multiplayerPatch_toggle);
	cfg.set<bool>("noEnragedHitstop_toggle", noEnragedHitstop_toggle);
	cfg.set<bool>("noHitstop_toggle", noHitstop_toggle);
	cfg.set<bool>("unbanClimaxBrace_toggle", unbanClimaxBrace_toggle);

	//cfg.set<bool>("AreaJumpPatchToggle", areaJumpPatch_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);
	cfg.set<float>("InfMagicValue", inf_magic_value);
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
	cfg.set<bool>("CancellableAfterBurnerToggle", cancellableAfterBurner_toggle);
	cfg.set<bool>("CancellableFallingKickToggle", cancellableFallingKick_toggle);
	cfg.set<bool>("OpenMenuPauseToggle", openMenuPause_toggle);
	cfg.set<bool>("TurboToggle", turbo_toggle);
	cfg.set<float>("TurboValue", turboValue);
	cfg.set<bool>("AltTeleInputToggle", altTeleInput_toggle);
	cfg.set<bool>("TeleportComboAction_toggle", teleportComboAction_toggle);
	cfg.set<bool>("DisableSlowmoToggle", disableSlowmo_toggle);
	cfg.set<bool>("LowerDivekickToggle", lowerDivekick_toggle);
	cfg.set<bool>("DualAfterBurnerToggle", dualAfterBurner_toggle);
	cfg.set<bool>("LoadReplaceToggle", loadReplace_toggle);
	cfg.set<bool>("LongerPillowTalkChargeToggle", longerPillowTalkCharge_toggle);
	cfg.set<bool>("AlwaysWitchTimeToggle", alwaysWitchTime_toggle);
	cfg.set<bool>("SaveStatesHotkeysToggle", saveStatesHotkeys_toggle);
	cfg.set<bool>("TauntWithTimeBraceletToggle", tauntWithTimeBracelet_toggle);
	cfg.set<bool>("omnicancelTele_toggle", omnicancelTele_toggle);
	cfg.set<bool>("fixThirdAccessory_toggle", fixThirdAccessory_toggle);

	cfg.set<bool>("moveIDSwapsToggle", moveIDSwapsToggle);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		cfg.set<bool>(("MoveIDSwap_toggles[" + std::to_string(i) + "]").c_str(), moveIDSwap_toggles[i]);
		cfg.set<int>(("MoveIDSwapSourceMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSourceMoves[i]);
		cfg.set<int>(("MoveIDSwapSwappedMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSwappedMoves[i]);
	}

	cfg.set<bool>("stringSwapsToggle", stringSwapsToggle);
	for (int i = 0; i < maxStringSwaps; ++i) {
		cfg.set<bool>(("stringIDSwap_toggles[" + std::to_string(i) + "]").c_str(), stringIDSwap_toggles[i]);
		cfg.set<int>(("stringIDSwapSourceStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapSourceStrings[i]);
		cfg.set<int>(("stringIDSwapDesiredStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapDesiredStrings[i]);
	}

	cfg.set<bool>("comboMakerToggle", comboMakerToggle);
	for (int i = 0; i < maxComboMakers; ++i) {
		cfg.set<bool>(("ComboMaker_toggles[" + std::to_string(i) + "]").c_str(), comboMaker_toggles[i]);
		cfg.set<int>(("ComboMakerMoveIDs[" + std::to_string(i) + "]").c_str(), comboMakerMoveIDs[i]);
		cfg.set<int>(("ComboMakerMoveParts[" + std::to_string(i) + "]").c_str(), comboMakerMoveParts[i]);
		cfg.set<int>(("ComboMakerStringIDs[" + std::to_string(i) + "]").c_str(), comboMakerStringIDs[i]);
	}

	cfg.set<bool>("CustomWeavesToggle", customWeaves_toggles);
	for (int i = 0; i < customWeaveCount; ++i) {
		cfg.set<bool>(("CustomWeaves_toggles[" + std::to_string(i) + "]").c_str(), customWeaves_toggles[i]);
		cfg.set<int>(("CustomWeaveMoveIDArray[" + std::to_string(i) + "]").c_str(), customWeaveMoveIDArray[i]);
		cfg.set<int>(("CustomWeaveArray[" + std::to_string(i) + "]").c_str(), customWeaveArray[i]);
	}

	// tick
	cfg.set<int>("DesiredThirdAccessoryValue", desiredThirdAccessory);
	cfg.save(GameHook::cfgString);
}
