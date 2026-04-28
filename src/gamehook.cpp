#include "gamehook.hpp"
#include "WorldVisualizer.hpp"

// system
float GameHook::deltaTime = 0.0f;
float GameHook::deltaSpeed = 0.0f;
bool GameHook::enable_scroll_transitions = false;
float GameHook::windowScalingFactor = 1.0f;
float GameHook::bayoHookFontSize = 16.0f;
float GameHook::comboUI_X = 0.0f;
float GameHook::comboUI_Y = 0.0f;
ImFont* GameHook::bayoHookFont = nullptr;
float GameHook::windowWidth = 0.0f;
float GameHook::inputItemWidth = 0.0f;
float GameHook::sameLineWidth = 0.0f;
bool GameHook::showComboUI_toggle = false;
bool GameHook::testComboUI_toggle = false;
bool GameHook::showMessages_toggle = false;
std::mt19937 GameHook::rng;
// bool GameHook::forceSaveFile = false;
// int GameHook::forcedFileNum = 99;

bool GameHook::forceCostume = false;
int GameHook::tempCostume = 0;

// update
uintptr_t GameHook::playerPointerAddress = 0xEF5A60;
uintptr_t GameHook::enemyLockedOnAddress = 0xF2B744;
uintptr_t GameHook::comboPointsAddress = 0x5BB519C;
uintptr_t GameHook::comboMultiplierAddress = 0x5BB51A0;
uintptr_t GameHook::currentCostumeAddress = 0x5AA747C;
uintptr_t GameHook::gameTimeAddress = 0x5BB9528;
uintptr_t GameHook::areaJumpAddress = 0x5A978E8;
#ifndef SPEEDRUN_BUILD
uintptr_t GameHook::angelSlayerFloorAddress = 0x509E87C;
uintptr_t GameHook::halosAddress = 0x5AA74B4;
uintptr_t GameHook::chaptersPlayedAddress = 0x5AA736C;
uintptr_t GameHook::playerMagicAddress = 0x5AA74AC;
uintptr_t GameHook::currentCharacterAddress = 0x5AA7484;
uintptr_t GameHook::thirdAccessoryAddress = 0x5AA7468;
uintptr_t GameHook::hudDisplayAddress = 0xF2B714;
uintptr_t GameHook::enemySlotsAddress = 0x5A56A88;
uintptr_t GameHook::difficultyAddress = 0x5A985A0;
uintptr_t GameHook::WeaponA1Address = 0x5AA741C;
uintptr_t GameHook::WeaponA2Address = 0x5AA7420;
uintptr_t GameHook::WeaponB1Address = 0x5AA742C;
uintptr_t GameHook::WeaponB2Address = 0x5AA7430;

bool GameHook::spawnEntityFromGui = false;
bool GameHook::spawnEntityFromHotkey = false;
EntitySpawn GameHook::guiEntitySpawn;
EntitySpawn GameHook::hotkeyEntitySpawn;

bool GameHook::comboMaker_toggle = false;
bool GameHook::comboMaker_toggles[maxComboMakers]{};
int  GameHook::comboMakerMoveIDs[maxComboMakers]{};
int  GameHook::comboMakerMoveParts[maxComboMakers]{};
int  GameHook::comboMakerStringIDs[maxComboMakers]{};

int GameHook::desiredThirdAccessory = 0;
#endif

// patches
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

bool GameHook::disableClicking_toggle = false;
void GameHook::DisableClicking(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC75747), 3);
	else
		GameHook::_patch((char*)(0xC75747), (char*)"\x89\x70\x04", 3);
}

bool GameHook::disableTutorials_toggle = false;
void GameHook::DisableTutorials(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0xB47532), (char*)"\xEB", 1); // jmp Bayonetta.exe+747532
	}
	else {
		GameHook::_patch((char*)(0xB47532), (char*)"\x75", 1); // jne Bayonetta.exe+747532
	}
}

#ifndef SPEEDRUN_BUILD

bool GameHook::disableFpsLimiter_toggle = false;
void GameHook::DisableFpsLimiter(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0xC54340), (char*)"\xC3", 1); // retn 
		GameHook::_patch((char*)(0xC54430), (char*)"\xC3", 1); // retn 
		GameHook::_patch((char*)(0x49E25D), (char*)"\x90\xE9", 2); // jmp
		// GameHook::_patch((char*)(0xC5450A), (char*)"\x90\x90\x90\x90\x90\x90\x90\x90", 8); // nop
	}
	else {
		GameHook::_patch((char*)(0xC54340), (char*)"\xF3", 1); // movss
		GameHook::_patch((char*)(0xC54430), (char*)"\xF3", 1); // movss
		GameHook::_patch((char*)(0x49E25D), (char*)"\x0F\x84", 2); // jz
		// GameHook::_patch((char*)(0xC5450A), (char*)"\xF3\x0F\x58\x05\xB8\x99\xDA\x00", 8); // addss xmm0,[Bayonetta.exe+9A99B8] (16.68f)
	}
}

static __declspec(naked) void MovDeltaTimePatch(void) {
	_asm {
		mov eax, [GameHook::deltaTime]
	}
}

bool GameHook::linkGameToDelta_toggle;
void GameHook::LinkGameToDelta(bool enabled) {
	if (enabled) {
		//GameHook::_patch((char*)(0x513E73), (char*)MovDeltaTimePatch, 5);
	}
	else {
		//GameHook::_patch((char*)(0x513E73), (char*)"\xB8\x00\x00\x80\x3F", 5); // mov eax, (float)1
		float* gameSpeed = (float*)0xEF6588;
		*gameSpeed = 1.0f;
	}
}

bool GameHook::autoQTE_toggle = false;
void GameHook::AutoQTE(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x41644E), (char*)"\xE9\xCA\x02\x00\x00", 5);		// ch1 bridge, ch14-1, ch14-2 (up+A)
		GameHook::_patch((char*)(0x4A8AAD), (char*)"\x90\x90", 2);					// ch2-1, ch3 (X)
		GameHook::_patch((char*)(0x4A8D75), (char*)"\xEB\x61", 2);					// ch2-2 (spin stick), ch3-2 (mash x)
		GameHook::_patch((char*)(0x41652C), (char*)"\xE9\xEC\x01\x00\x00", 5);		// ch8 1 (A)
		GameHook::_patch((char*)(0x41641A), (char*)"\xE9\xFE\x02\x00\x00\x90", 6);	// ch8 2 (Up+A)
		GameHook::_patch((char*)(0x416492), (char*)"\xE9\x84\x02\x00\x00\x90", 6);	// ch15 elevator (side+jump)

		GameHook::_patch((char*)(0x9CD0AC), (char*)"\x90\x90", 2);					// auto grace torture attack
		// GameHook::_patch((char*)(0x9CD0C9), (char*)"\xC0", 1);					// grace torture attack faster

		GameHook::_patch((char*)(0x8DE5C8), (char*)"\x90\x90", 2);					// beloved grab

		// GameHook::_patch((char*)(0x416585), (char*)"\xE9\x93\x01\x00\x00", 5);	// Y+B but will torture attack every single dude
	}
	else {
		GameHook::_patch((char*)(0x41644E), (char*)"\xE9\xC8\x02\x00\x00", 5);		// ch1 bridge, ch14-1, ch14-2 (up+A)
		GameHook::_patch((char*)(0x4A8AAD), (char*)"\x74\x38", 2);					// ch2-1, ch3 (X)
		GameHook::_patch((char*)(0x4A8D75), (char*)"\x75\x61", 2);					// ch2-2 (spin stick), ch3-2 (mash x)
		GameHook::_patch((char*)(0x41652C), (char*)"\xE9\xEA\x01\x00\x00", 5);		// ch8 1 (A)
		GameHook::_patch((char*)(0x41641A), (char*)"\x0F\x86\x68\x03\x00\x00", 6);	// ch8 2 (Up+A)
		GameHook::_patch((char*)(0x416492), (char*)"\x0F\x86\xF0\x02\x00\x00", 6);	// ch15 elevator (side+jump)

		GameHook::_patch((char*)(0x9CD0AC), (char*)"\x74\x24", 2);					// auto spin stick torture attack
		// GameHook::_patch((char*)(0x9CD0C9), (char*)"\xC1", 1);					// spin stick torture attack faster

		GameHook::_patch((char*)(0x8DE5C8), (char*)"\x74\x3d", 2);					// beloved grab

		// GameHook::_patch((char*)(0x416585), (char*)"\xE9\x91\x01\x00\x00", 5);   // Y+B but will torture attack every single dude
	}
}

bool GameHook::disableGradient_toggle = false;
void GameHook::DisableGradient(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x43B06F), (char*)"\xC7\x41\x70\x00\x00\x00\x00\x90\x90", 9); // mov [ecx+70],00000000 nop nop
	}
	else {
		GameHook::_patch((char*)(0x43B06F), (char*)"\xF3\x0F\x58\xD3\xF3\x0F\x11\x51\x70", 9); // addss xmm2,xmm3 movss [ecx+70],xmm2
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

/*bool GameHook::memPatch_toggle = true;
void GameHook::MemPatch(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x40012E), (char*)"\x20", 1); // ntcore (characteristics)
	}
	else {
		GameHook::_patch((char*)(0x40012E), (char*)"\x03", 1); // ntcore (characteristics)
	}
}*/

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

bool GameHook::noClip_toggle = false;
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

// uses GameHook::enemyHPNoDamage_toggle
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

bool GameHook::autoCutsceneSkip_toggle = false;
void GameHook::AutoCutsceneSkip(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x90\x90", 2);
		GameHook::_patch((char*)(0x48FED0), (char*)"\xe9\x3b\xfd\xff\xff\x90", 6);
	}
	else {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x74\x10", 2); // R2 Held
		GameHook::_patch((char*)(0x48FED0), (char*)"\x0f\x85\x3a\xfd\xff\xff", 6); // Select Pressed
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

bool GameHook::skipAngelAttack_toggle = false;
void GameHook::SkipAngelAttack(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x6221C5), (char*)"\x83\xc4\x08\x90\x90", 5); // dont call a func that will get us stuck in AA
		GameHook::_patch((char*)(0x622068), (char*)"\x90\x90", 2); // jump to store menu
		GameHook::_patch((char*)(0x62207C), (char*)"\xeb", 1); // leave store
	}
	else {
		GameHook::_patch((char*)(0x6221C5), (char*)"\xe8\x76\x1f\xee\xff", 5); // dont call a func that will get us stuck in AA
		GameHook::_patch((char*)(0x622068), (char*)"\x75\xe8", 2); // jump to store menu
		GameHook::_patch((char*)(0x62207C), (char*)"\x75", 1); // leave store
	}
}

bool GameHook::skipMapScene_toggle = false;
void GameHook::SkipMapScene(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x619DA7), (char*)"\x90\x90\x90\x90\x90", 5);
	}
	else {
		GameHook::_patch((char*)(0x619DA7), (char*)"\xe8\xd4\x1c\xee\xff", 5); // call Bayonetta.exe+FBA80
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

#endif

// detours

bool GameHook::uptimeFix_toggle = false;
static std::unique_ptr<FunctionHook> uptimeFixHook;
static uintptr_t uptimeFix_jmp_ret{ NULL };
// INT64 GameHook::rebase_interval = 60; // constexpr now
static float lastTickMs = 0.0f;
static float tickDeltaMs = 16.68f;

static void __cdecl GameTimerRebase() {
	INT64* ticksAtStartup = (INT64*)0x5BCFBF8;
	INT64* ticksPerSecond = (INT64*)0x5BCFC00;
	float* gameTimerMs = (float*)GameHook::gameTimeAddress;

	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	INT64 elapsed = now.QuadPart - *ticksAtStartup;
	float currentMs = (float)((double)elapsed * 1000.0 / (double)*ticksPerSecond);

	if (lastTickMs > 0.0f) {
		float delta = currentMs - lastTickMs;
		if (delta > 0.0f && delta < 200.0f)
			tickDeltaMs = delta;
	}
	lastTickMs = currentMs;

	INT64 threshold = (*ticksPerSecond) * GameHook::rebase_interval;
	if (elapsed > threshold) {
		INT64 intervals = elapsed / threshold;
		INT64 ticks_to_drop = intervals * threshold;
		*ticksAtStartup += ticks_to_drop;
		double ms_to_drop = (double)ticks_to_drop * 1000.0 / (double)*ticksPerSecond;
		*gameTimerMs -= (float)ms_to_drop;
		lastTickMs -= (float)ms_to_drop;
	}
}

static __declspec(naked) void UptimeFixDetour() {
	__asm {
		pushfd
		cmp byte ptr [GameHook::uptimeFix_toggle], 0
		je originalCode

		pushad
		call GameTimerRebase
		popad

		originalCode:
		popfd
		sub esp, 8
		lea eax, ds:[esp]
		jmp dword ptr [uptimeFix_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> inputIconsHook;
static uintptr_t inputIcons_jmp_ret{ NULL };
bool GameHook::inputIcons_toggle = false;
int GameHook::inputIconsValue = 0; // 0 keyboard, 1 gamepad
static __declspec(naked) void InputIconsDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::inputIcons_toggle], 0
		je originalcode

		mov eax, [GameHook::inputIconsValue]

		originalcode:
		popfd
		cmp dword ptr [ebx+0x000003E8], 00
		mov [ebx+0x00000CA8], eax
		jmp dword ptr[inputIcons_jmp_ret]
	}
}

int RandomizeCostume(int currentCostume) {
	int minCostume = (currentCostume <= 14) ? 0 : 15;
	int maxCostume = (currentCostume <= 14) ? 14 : 30;
	std::uniform_int_distribution<int> dist(minCostume, maxCostume);
	return dist(GameHook::rng);
}

static std::unique_ptr<FunctionHook> randomizeCostumeHook;
bool GameHook::randomizeCostume_toggle = false;
static uintptr_t randomizeCostume_jmp_ret{ NULL };
static __declspec(naked) void RandomizeCostumeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::randomizeCostume_toggle], 0
		je originalcode

		pushad
		push dword ptr ds:[0x5AA747C]
		call RandomizeCostume
		mov ds:[0x5AA747C], eax
		add esp, 4
		popad

		originalcode:
		mov eax, 00000001
		jmp dword ptr [randomizeCostume_jmp_ret]
	}
}


#ifndef SPEEDRUN_BUILD

static std::unique_ptr<FunctionHook> initialAngelSlayerFloorHook;
static uintptr_t initialAngelSlayerFloor_jmp_ret{ NULL };
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
		jmp dword ptr[initialAngelSlayerFloor_jmp_ret]
	}
}

struct HitboxSnapshot {
	Vec3 pos;
	float radius;
};
static std::vector<HitboxSnapshot> hitDataList;

static void AddHitDataPtr(void* ptr) {
	auto* hitData = (hitbox*)(ptr);
	hitDataList.push_back({ hitData->pos, hitData->scale });
}

static std::unique_ptr<FunctionHook> getHitboxHook;
static uintptr_t getHitbox_jmp_ret{ NULL };
static float getHitboxXmm0Backup = 0.0f;
static __declspec(naked) void GetHitboxDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::drawHitboxes_toggle], 0
		je originalcode

		movss [getHitboxXmm0Backup], xmm0
		pushad
		add ebx, 0xD0 // old offset was +0x30
		push ebx
		call AddHitDataPtr
		add esp, 4
		popad
		movss xmm0, [getHitboxXmm0Backup]
		originalcode:
		popfd
		addss xmm0, [ebx+0x00000100]
		jmp dword ptr [getHitbox_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> turboHook;
static uintptr_t turbo_jmp_ret{ NULL };
bool GameHook::openMenuPause_toggle = false;
float GameHook::turboZero = 0.0f;
bool GameHook::turbo_toggle = false;
float GameHook::turboValue = 1.0f;
bool GameHook::turboCutscene_toggle = false;
float GameHook::turboCutscene = 5.0f;
static __declspec(naked) void TurboHookDetour(void) {
	_asm {
		cmp byte ptr [GameHook::openMenuPause_toggle], 1
		je zerospeed
		jmp turbocheck

		zerospeed :
		cmp byte ptr [Base::Data::ShowMenu], 0
		je turbocheck
		movss xmm0, [GameHook::turboZero]
		jmp originalcode

		/*cutscenecheck:
		cmp byte ptr [GameHook::turboCutscene_toggle], 1
		jne turbocheck
		push eax
		mov eax, [GameHook::playerPointerAddress]
		mov eax, [eax]
		test eax, eax
		je popcode
		cmp byte ptr [eax+0x?], 1 // inCutscene
		pop eax
		jne turbocheck
		// in cutscene
		mulss xmm0, [GameHook::turboCutscene]*/
		turbocheck:
		cmp byte ptr [GameHook::turbo_toggle], 0
		je originalcode
		mulss xmm0, [GameHook::turboValue]
		jmp originalcode

		//popcode:
		//pop eax
		originalcode:
		movss [edi+0x44], xmm0
		jmp dword ptr[turbo_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> enemyHPHook;
static uintptr_t enemyHP_jmp_ret{ NULL };
bool GameHook::enemyHPNoDamage_toggle = false;
bool GameHook::enemyHPOneHitKill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [GameHook::enemyHPOneHitKill_toggle], 1
		je one_hit_kill
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::enemyHPNoDamage_toggle], 1
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

static std::unique_ptr<FunctionHook> witchTimeHook;
static uintptr_t witchTimeMultiplier_jmp_ret{ NULL };
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

void GameHook::SpawnStuff() {
	if (GameHook::spawnEntityFromGui) {
		GameHook::spawnEntityFromGui = false;
		GameHook::SpawnEntity(guiEntitySpawn);
	}
	if (GameHook::spawnEntityFromHotkey) {
		GameHook::spawnEntityFromHotkey = false;
		GameHook::SpawnEntity(hotkeyEntitySpawn);
	}
}

std::unique_ptr<FunctionHook> infMagicHook;
uintptr_t infMagic_jmp_ret{ NULL };
bool GameHook::infMagic_toggle = false;
float GameHook::infMagic_value = 1200.0f;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		pushad
		call GameHook::SpawnStuff
		popad

		push eax
		mov eax, [GameHook::playerMagicAddress]
		cmp byte ptr [GameHook::infMagic_toggle], 0
		je originalcode

		movss xmm0, [GameHook::infMagic_value]
		movss [eax], xmm0

		originalcode:
		movss xmm0, [eax]
		pop eax
		jmp dword ptr [infMagic_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> damageDealtMultiplierHook;
static uintptr_t damageDealtMultiplier_jmp_ret{ NULL };
bool GameHook::damageDealtMultiplier_toggle = false;
static float damageDealtMultiplierXmm0Backup = 0.0f;
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

static std::unique_ptr<FunctionHook> damageReceivedMultiplierHook;
static uintptr_t damageReceivedMultiplier_jmp_ret{ NULL };
bool GameHook::damageReceivedMultiplierNoDamage_toggle = false;
bool GameHook::damageReceivedMultiplier_toggle = false;
float GameHook::incoming_damage_mult = 1.0f;
static float damageMultXmm0Backup = 0.0f;
static __declspec(naked) void DamageReceivedMultiplierDetour(void) {
	_asm {
		cmp byte ptr [GameHook::damageReceivedMultiplierNoDamage_toggle], 1
		je no_damage
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::damageReceivedMultiplier_toggle], 1
		je damage_mult
		jmp originalcode

		no_damage:
		jmp retcode

		damage_mult:
		movss [damageMultXmm0Backup], xmm0
		movd xmm0, ecx
		cvtdq2ps xmm0, xmm0
		mulss xmm0, [GameHook::incoming_damage_mult]
		cvttss2si ecx, xmm0
		movss xmm0, [damageMultXmm0Backup]

		originalcode:
		sub eax, ecx
		mov [esi+0x00093508], eax
		retcode:
		jmp dword ptr [damageReceivedMultiplier_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> customCameraDistanceHook;
static uintptr_t customCameraDistance_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> haloDisplayHook;
static uintptr_t haloDisplay_jmp_ret{ NULL };
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

bool GameHook::moveIDSwaps_toggle = false;
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

static std::unique_ptr<FunctionHook> moveIDSwapHook;
static uintptr_t moveIDSwap_jmp_ret{ NULL };
static __declspec(naked) void MoveIDSwapDetour(void) { // player in ecx
	_asm {
		cmp byte ptr [GameHook::moveIDSwaps_toggle], 0
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

bool GameHook::stringSwaps_toggle = false;
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

static std::unique_ptr<FunctionHook> punchStringIDSwapHook;
static uintptr_t punchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void PunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwaps_toggle], 0
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

static std::unique_ptr<FunctionHook> latePunchStringIDSwapHook;
static uintptr_t latePunchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LatePunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwaps_toggle], 0
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

static std::unique_ptr<FunctionHook> kickStringIDSwapHook;
static uintptr_t kickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void KickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwaps_toggle], 0
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

static std::unique_ptr<FunctionHook> lateKickStringIDSwapHook;
static uintptr_t lateKickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LateKickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwaps_toggle], 0
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

static std::unique_ptr<FunctionHook> easierMashHook;
static uintptr_t easierMash_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> cancellableAfterBurnerHook;
static uintptr_t cancellableAfterBurner_jmp_ret{ NULL };
bool GameHook::cancellableAfterBurner_toggle = false;
static uintptr_t cancellableMovesCall = 0x9E85E0;
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

static std::unique_ptr<FunctionHook> cancellableFallingKickHook;
static uintptr_t cancellableFallingKick_jmp_ret{ NULL };
bool GameHook::cancellableFallingKick_toggle = false;
static uintptr_t CancellableFallingKickDefaultCall = 0x433220;
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

static std::unique_ptr<FunctionHook> cancellableFallingKickDurgaHook;
static uintptr_t cancellableFallingKickDurga_jmp_ret{ NULL };
static __declspec(naked) void CancellableFallingKickDurgaDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableFallingKick_toggle], 0
		je originalcode

		cmp dword ptr [esi+0x350], 4 // only before landing
		ja originalcode
		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		movss xmm0, [esi+0x000006F4]
		jmp dword ptr [cancellableFallingKickDurga_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> altTeleInputHook;
static uintptr_t altTeleInput_jmp_ret{ NULL };
static uintptr_t altTeleInput_jmp_jle = 0x8BE5AC;
static uintptr_t altTeleInput_jmp_je = 0x8BE5B6;
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

static std::unique_ptr<FunctionHook> tauntWithTimeBracelet2Hook; // tap taunt
static uintptr_t tauntWithTimeBracelet2_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> tauntWithTimeBracelet3Hook; // hold taunt
static uintptr_t tauntWithTimeBracelet3_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> disableSlowmoHook;
static uintptr_t disableSlowmo_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> lowerDivekickHook;
static uintptr_t lowerDivekick_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> dualAfterBurnerHook;
static uintptr_t dualAfterBurner_jmp_ret{ NULL };
bool GameHook::dualAfterBurner_toggle = false;
static uintptr_t dualAfterBurnerCall = 0x9E33D0;
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

static std::unique_ptr<FunctionHook> loadReplaceHook;
static uintptr_t loadReplace_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> longerPillowTalkChargeHook;
static uintptr_t longerPillowTalkCharge_jmp_ret{ NULL };
bool GameHook::longerPillowTalkCharge_toggle = false;
static float longerPillowTalkChargeMult = 2.0f;
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

static std::unique_ptr<FunctionHook> alwaysWitchTimeHook;
static uintptr_t alwaysWitchTime_jmp_ret{ NULL };
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

bool GameHook::customWeave_toggle = false;
bool GameHook::customWeaves_toggles[customWeaveCount]{};
int GameHook::customWeaveArray[customWeaveCount]{};
int GameHook::customWeaveMoveIDArray[customWeaveCount]{};
static std::unique_ptr<FunctionHook> customWeavesHook;
static uintptr_t customWeaves_jmp_ret{ NULL };
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

static std::unique_ptr<FunctionHook> omnicancelTeleHook;
static uintptr_t omnicancelTele_jmp_ret{ NULL };
bool GameHook::omnicancelTele_toggle = false;
static uintptr_t omnicancelTele_call = 0x009E6FA0;
static uintptr_t omnicancelTele_ogcode = 0x05A97ED0;
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

struct SpawnSnapshot {
	int ID;
	int unkn;
	int optionalStructUsed;
	int structUnkn;
	int structVariant;
	int structSpawnModifier;
};

static std::vector<SpawnSnapshot> recentlySpawnedList;
static const size_t MAX_SNAPSHOTS = 10000;

static void LogEntitySpawn(int ID, int unkn, int optionalStructUsed, int structUnkn, int structVariant, int structSpawnModifier) {
	if (recentlySpawnedList.size() >= MAX_SNAPSHOTS)
		recentlySpawnedList.erase(recentlySpawnedList.begin());

	recentlySpawnedList.push_back({
		ID,
		unkn,
		optionalStructUsed,
		structUnkn,
		structVariant,
		structSpawnModifier
	});
}


void GameHook::DisplayRecentlySpawnedEntitiesInImGui() {
	if (ImGui::Button("Clear"))
		recentlySpawnedList.clear();
	ImGui::Text("Count: %d", (int)recentlySpawnedList.size());
	ImGui::Separator();

	for (size_t i = 0; i < recentlySpawnedList.size(); i++) {
		auto& s = recentlySpawnedList[i];

		ImGui::PushID((int)i);
		ImGui::PushItemWidth(inputItemWidth);
		ImGui::InputInt("Has Optional Struct", &s.optionalStructUsed);
		ImGui::InputScalar("ID", ImGuiDataType_S32, &s.ID, NULL, NULL, "%8X");
		const char* name = GetEntityName(s.ID);
		if (name) {
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "%s", name);
		}

		ImGui::InputScalar("Unkn", ImGuiDataType_S32, &s.unkn, NULL, NULL, "%8X");
		if (s.optionalStructUsed == 1) {
			ImGui::InputScalar("Struct.int_0_Unkn", ImGuiDataType_S32, &s.structUnkn, NULL, NULL, "%8X");
			ImGui::InputScalar("Struct.int_4_Variant", ImGuiDataType_S32, &s.structVariant,  NULL, NULL, "%8X");
			ImGui::InputScalar("Struct.int_8_SpawnModifier", ImGuiDataType_S32, &s.structSpawnModifier, NULL, NULL, "%8X");
		}
		ImGui::PopItemWidth();
		ImGui::Separator();
		ImGui::PopID();
	}
}

static std::unique_ptr<FunctionHook> viewEntitySpawnsHook;
static uintptr_t viewEntitySpawns_jmp_ret{ NULL };
bool GameHook::viewEntitySpawns_toggle = false;
static __declspec(naked) void ViewEntitySpawnsDetour(void) {
	__asm {
		pushfd
		cmp byte ptr [GameHook::viewEntitySpawns_toggle], 0
		je originalcode

		pushad
		mov edx, [esp+0x28] // entityID
		mov eax, [esp+0x2C] // optionalSettings
		mov ecx, [esp+0x30] // unkn

		test eax, eax
		je dontLogEax
		cmp eax, 0x10000
		jb dontLogEax

		push [eax+0x8] // struct.SpawnModifier
		push [eax+0x4] // struct.Variant
		push [eax+0x0] // struct.Unkn
		push 1 // struct Used
		push ecx
		push edx
		call LogEntitySpawn
		add esp, 24
		jmp popcode

	dontLogEax:
		push 0 // struct.SpawnModifier
		push 0 // struct.Variant
		push 0 // struct.Unkn
		push 0 // struct Used
		push ecx
		push edx
		call LogEntitySpawn
		add esp, 24

	popcode:
		popad
	originalcode:
		popfd
		mov eax, [esp+0x0C]
		mov edx, [esp+0x08]
		jmp dword ptr [viewEntitySpawns_jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> teleportComboActionHook;
static uintptr_t teleportComboAction_jmp_ret{ NULL };
bool GameHook::teleportComboAction_toggle = false;
static __declspec(naked) void TeleportComboActionDetour(void) { // player in ebx
	_asm {
		cmp byte ptr [GameHook::teleportComboAction_toggle], 0
		je originalcode

		mov dword ptr [esi+0x95C80], 0x41700000 // 15f

		originalcode:
		mov eax, [esi+0x00000350]
		jmp dword ptr [teleportComboAction_jmp_ret]
	}
}


static std::unique_ptr<FunctionHook> fixThirdAccessoryHook;
static uintptr_t fixThirdAccessory_jmp_ret{ NULL };
static uintptr_t fixThirdAccessoryCall = 0x4332F0;
static __declspec(naked) void FixThirdAccessoryDetour(void) { // player in ebx
	_asm {
		//
			cmp byte ptr [GameHook::desiredThirdAccessory], 0
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

static std::unique_ptr<FunctionHook> getMotNameHook;
static uintptr_t getMotName_jmp_ret{ NULL };
bool GameHook::getMotName_toggle = false;
static uintptr_t getMotName_playerTestAddress = NULL;
static uintptr_t getMotName_weaponTestAddress = NULL;
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

static std::unique_ptr<FunctionHook> pl0012Hook;
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

static std::unique_ptr<FunctionHook> pl0031Hook;
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

static std::unique_ptr<FunctionHook> pl004cHook;
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
	static uintptr_t weaponSwapCallAddress = 0xC43ED0;
	__asm {
		pushad
		pushfd
		call weaponSwapCallAddress
		popfd
		popad
	}
}

#endif

LocalPlayer* GameHook::GetLocalPlayer() {
	if (LocalPlayer* player = *(LocalPlayer**)GameHook::playerPointerAddress)
		return player;
	else
		return nullptr;
}

std::vector<GameHook::HotkeyMessage> GameHook::activeMessages;
void GameHook::DisplayMessageText(const char* text, std::optional<bool> enabled) {
	static float duration = 2.0f;
	for (auto& msg : activeMessages) {
		if (msg.text == text) {
			msg.enabled = enabled;
			msg.timeRemaining = duration;
			return;
		}
	}
	activeMessages.push_back({ text, enabled, duration });
}

void GameHook::RenderMessages(float deltaTime) {
    activeMessages.erase(
        std::remove_if(activeMessages.begin(), activeMessages.end(),
            [](const HotkeyMessage& m) { return m.timeRemaining <= 0.0f; }),
        activeMessages.end()
    );

    if (activeMessages.empty()) return;

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 windowPos(io.DisplaySize.x - 20.0f, 20.0f);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.6f);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    static ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_AlwaysAutoResize;

    if (ImGui::Begin("##hotkey_overlay", nullptr, flags)) {
		for (auto& msg : activeMessages) {
			float alpha = (std::min)(1.0f, msg.timeRemaining / 0.5f);

			static ImVec4 color;
			if (!msg.enabled.has_value())
				color = ImVec4(1.0f, 1.0f, 1.0f, alpha); // n/a
			else if (msg.enabled.value())
				color = ImVec4(0.4f, 1.0f, 0.4f, alpha); // green = on
			else
				color = ImVec4(1.0f, 0.4f, 0.4f, alpha); // red = off

			ImGui::PushStyleColor(ImGuiCol_Text, color);

			if (msg.enabled.has_value())
				ImGui::Text("%s %s", msg.text.c_str(), msg.enabled.value() ? " [ON]" : " [OFF]");
			else
				ImGui::Text("%s", msg.text.c_str());

			ImGui::PopStyleColor();

			msg.timeRemaining -= deltaTime;
		}
    }
    ImGui::End();
}

void GameHook::AreaJump(int stage, int part, int spawn) {
	uintptr_t ecx = 0xEF5A50;
	uintptr_t areaJumpAddr = 0x506390;
	AreaJumpFunc areaJump = (AreaJumpFunc)areaJumpAddr;
	areaJump(ecx, stage, part, spawn);
}

#ifndef SPEEDRUN_BUILD
Matrix4x4 viewProj;
void GameHook::Setup3dShapes() {
	static uintptr_t matrixAddress = 0xF2DCE0;
	// ImGui::InputScalar("matrixAddr", ImGuiDataType_U64, &matrixAddress, NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
	viewProj = *(Matrix4x4*)matrixAddress;
}

bool GameHook::drawPlayerBones_toggle = false;
bool GameHook::drawHitboxes_toggle = false;
void GameHook::Draw3dShapes() {
	LocalPlayer* player = GetLocalPlayer();
	if (!player) { return; }

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("WorldViz", nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBringToFrontOnFocus);
	WorldVisualizer::SetDrawList(ImGui::GetWindowDrawList());
	WorldVisualizer::SetViewProjectionMatrix(viewProj);
	if (GameHook::drawPlayerBones_toggle) {
		Vec3 playerPos = player->pos;
		Matrix3x3 playerRot = WorldVisualizer::CreateRotationMatrix(player->rot.x, player->rot.y, player->rot.z);
		// WorldVisualizer::DrawWorldSphere(playerPos, 0.1f, IM_COL32(0, 0, 255, 255), 32, 1.0f, &playerRot);
		// WorldVisualizer::DrawWorldCapsule(player->pos + Vec3(0.0f, 0.25f, 0.0f), player->pos + Vec3(0.0f, 1.5f, 0.0f), 0.25f, IM_COL32(255, 0, 0, 255), 32, 1.0f, &playerRot);

		// WorldVisualizer::DrawWorldSphere(Vec3(-67.0f, 0.0f, -1.0f), 0.5f);
		// WorldVisualizer::DrawWorldCapsule(Vec3(-67.0f, 0.0f, 0.0f), Vec3(-67.0f, 2.0f, 0.0f), 0.5f);
		// WorldVisualizer::DrawWorldSphere(Vec3(-67.0f, 0.0f, 1.0f), 0.5f);
		BayoBone* bone = player->bayoSkeleton;
		// Draw forward
		while (bone) {
			WorldVisualizer::DrawWorldSphere(bone->pos, 0.01f, IM_COL32(0, 0, 255, 255), 32, 1.0f, &playerRot);
			bone = bone->nextBone;
		}
		// Draw backward
		if (player->bayoSkeleton) {
			bone = player->bayoSkeleton->prevBone;
			while (bone) {
				WorldVisualizer::DrawWorldSphere(bone->pos, 0.01f, IM_COL32(0, 0, 255, 255), 32, 1.0f, &playerRot);
				bone = bone->prevBone;
			}
		}
	}
	if (GameHook::drawHitboxes_toggle) {
		for (const HitboxSnapshot& snapshot : hitDataList) {
			WorldVisualizer::DrawWorldSphere(snapshot.pos, snapshot.radius, IM_COL32(255, 0, 0, 255), 32, 1.0f);
		}
		hitDataList.clear();
	}

	ImGui::End();
}

bool GameHook::drawFlyingStats_toggle = false;
void GameHook::DrawFlyingStats() {
	if (!GameHook::drawFlyingStats_toggle) { return; }
	LocalPlayer* player = GameHook::GetLocalPlayer();

	if (player) {
		float fontSize = ImGui::GetFontSize();
		static ImVec2 playerScreenPos;
		WorldVisualizer::WorldToScreen(player->pos, playerScreenPos);
		ImGui::Begin("FlyingPlayerStats", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
		ImGui::SetWindowPos(playerScreenPos);
		ImGui::SetNextItemWidth(fontSize * 9.0f);
		ImGui::InputFloat3("Pos##FlyingPlayerXYZPosInputFloat", &player->pos.x, "%.1f");
		ImGui::PushItemWidth(fontSize * 3.0f);
		ImGui::InputInt("Move ID##FlyingPlayerMoveIDInputInt", &player->moveID, NULL, NULL);
		ImGui::InputInt("String ID##FlyingPlayerStringIDInputInt", &player->stringID, NULL, NULL);
		// ImGui::InputFloat("iframes##FlyingPlayerIframesInputFloat", &player->iFramesRemaining, NULL, NULL, "%.0f");
		ImGui::PopItemWidth();
		ImGui::End();

		Enemy* enemy = *(Enemy**)GameHook::enemyLockedOnAddress;
		if (enemy) {
			static ImVec2 enemyScreenPos;
			WorldVisualizer::WorldToScreen(enemy->pos, enemyScreenPos);
			ImGui::Begin("FlyingEnemyStats", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowPos(enemyScreenPos);
			ImGui::SetNextItemWidth(fontSize * 9.0f);
			ImGui::InputFloat3("Pos##FlyingEnemyXYZPosInputFloat", &enemy->pos.x, "%.1f");
			ImGui::PushItemWidth(fontSize * 3.0f);
			ImGui::SliderInt("HP##FlyingEnemyHPInputInt", &enemy->hp, 0, enemy->hpMax);
			ImGui::InputInt("Move ID##FlyingEnemyMoveIDInputInt", &enemy->moveID, 0, 0);
			ImGui::PopItemWidth();
			ImGui::End();
		}
	}
}

void GameHook::EasySpawnEntityFromHotkey(int enemyID, int variant, int spawnModifier) {
	LocalPlayer* player = GameHook::GetLocalPlayer();
	if (!player) { return; }
	GameHook::hotkeyEntitySpawn.entityID = enemyID;
	GameHook::hotkeyEntitySpawn.settings.int_4_Variant = variant;
	GameHook::hotkeyEntitySpawn.settings.int_8_SpawnModifier = spawnModifier;
	GameHook::hotkeyEntitySpawn.settings.float_70_X = player->pos.x;
	GameHook::hotkeyEntitySpawn.settings.float_74_Y = player->pos.y;
	GameHook::hotkeyEntitySpawn.settings.float_78_Z = player->pos.z;
	GameHook::spawnEntityFromHotkey = true;
	GameHook::DisplayMessageText("Entity Spawned");
}

void GameHook::EasySpawnEntityFromGui(int enemyID, int variant, int spawnModifier) {
	LocalPlayer* player = GameHook::GetLocalPlayer();
	if (!player) { return; }
	GameHook::guiEntitySpawn.entityID = enemyID;
	GameHook::guiEntitySpawn.settings.int_4_Variant = variant;
	GameHook::guiEntitySpawn.settings.int_8_SpawnModifier = spawnModifier;
	GameHook::guiEntitySpawn.settings.float_70_X = player->pos.x;
	GameHook::guiEntitySpawn.settings.float_74_Y = player->pos.y;
	GameHook::guiEntitySpawn.settings.float_78_Z = player->pos.z;
	GameHook::spawnEntityFromGui = true;
}

void GameHook::SpawnEntity(EntitySpawn& entitySpawn) {
    uintptr_t spawnEntityAddr = 0x510450;
    uintptr_t ecxAddr = 0x5ABB860;
	typedef uintptr_t(__thiscall* SpawnEntityFunc)(uintptr_t* ecx, int entityID, EntitySpawnArg2* a2, int a3);
    SpawnEntityFunc spawnEntity = (SpawnEntityFunc)spawnEntityAddr;
    spawnEntity((uintptr_t*)ecxAddr, entitySpawn.entityID, &entitySpawn.settings, entitySpawn.unkn);
}

#endif

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
	std::random_device rd;
	GameHook::rng.seed(rd() ^ (unsigned)time(NULL));
	install_hook_absolute(0xC78100, uptimeFixHook, &UptimeFixDetour, &uptimeFix_jmp_ret, 6);
	install_hook_absolute(0x411CD4, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 13);
	install_hook_absolute(0x4FC4EF, randomizeCostumeHook, &RandomizeCostumeDetour, &randomizeCostume_jmp_ret, 5);
#ifndef SPEEDRUN_BUILD 
	install_hook_absolute(0x41837E, getHitboxHook, &GetHitboxDetour, &getHitbox_jmp_ret, 8);
	install_hook_absolute(0x4572BA, enemyHPHook, &EnemyHPDetour, &enemyHP_jmp_ret, 6);
	install_hook_absolute(0x9E1808, witchTimeHook, &WitchTimeMultiplierDetour, &witchTimeMultiplier_jmp_ret, 6);
	install_hook_absolute(0x8BCE4C, infMagicHook, &InfMagicDetour, &infMagic_jmp_ret, 8);
	install_hook_absolute(0x4572B2, damageDealtMultiplierHook, &DamageDealtMultiplierDetour, &damageDealtMultiplier_jmp_ret, 8);
	install_hook_absolute(0x9D4327, damageReceivedMultiplierHook, &DamageReceivedMultiplierDetour, &damageReceivedMultiplier_jmp_ret, 8);
	install_hook_absolute(0xA941FA, customCameraDistanceHook, &CustomCameraDistanceDetour, &customCameraDistance_jmp_ret, 6);
	install_hook_absolute(0x4250F7, haloDisplayHook, &HaloDisplayDetour, &haloDisplay_jmp_ret, 5);
	install_hook_absolute(0x4BD053, moveIDSwapHook, &MoveIDSwapDetour, &moveIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2A82, punchStringIDSwapHook, &PunchStringIDSwapDetour, &punchStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x8D2AC4, latePunchStringIDSwapHook, &LatePunchStringIDSwapDetour, &latePunchStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AE5, kickStringIDSwapHook, &KickStringIDSwapDetour, &kickStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AA3, lateKickStringIDSwapHook, &LateKickStringIDSwapDetour, &lateKickStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x4A8EFF, easierMashHook, &EasierMashDetour, &easierMash_jmp_ret, 5);
	install_hook_absolute(0x41C8B5, initialAngelSlayerFloorHook, &InitialAngelSlayerFloorDetour, &initialAngelSlayerFloor_jmp_ret, 10);
	install_hook_absolute(0x95ABD3, cancellableAfterBurnerHook, &CancellableAfterBurnerDetour, &cancellableAfterBurner_jmp_ret, 6);
	install_hook_absolute(0x952142, cancellableFallingKickHook, &CancellableFallingKickDetour, &cancellableFallingKick_jmp_ret, 5);
	install_hook_absolute(0x920C44, cancellableFallingKickDurgaHook, &CancellableFallingKickDurgaDetour, &cancellableFallingKickDurga_jmp_ret, 8);
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
	install_hook_absolute(0x510450, viewEntitySpawnsHook, &ViewEntitySpawnsDetour, &viewEntitySpawns_jmp_ret, 8);
	install_hook_absolute(0x9A0020, teleportComboActionHook, &TeleportComboActionDetour, &teleportComboAction_jmp_ret, 6);
	install_hook_absolute(0x97ED07, fixThirdAccessoryHook, &FixThirdAccessoryDetour, &fixThirdAccessory_jmp_ret, 5);
	// int& thirdAccessoryValue = *(int*)GameHook::thirdAccessoryAddress;
	// thirdAccessoryValue = GameHook::desiredThirdAccessory;
	install_hook_absolute(0x9F5AF0, pl0012Hook, &pl0012Detour, NULL, 0);
	install_hook_absolute(0x9FC890, pl0031Hook, &pl0031Detour, NULL, 0);
	install_hook_absolute(0xA17420, pl004cHook, &pl004cDetour, NULL, 0);
#endif
}

void GameHook::onConfigLoad(const utils::Config& cfg) {
	// both speedrun and non speedrun
	focusPatch_toggle = cfg.get<bool>("focusPatch_toggle").value_or(false);
	FocusPatch(focusPatch_toggle);

	inputIcons_toggle = cfg.get<bool>("inputIcons_toggle").value_or(false);
	inputIconsValue = cfg.get<int>("inputIconsValue").value_or(0);
	showComboUI_toggle = cfg.get<bool>("showComboUI_toggle").value_or(false);
	comboUI_X = cfg.get<float>("comboUI_X").value_or(0.880f);
	comboUI_Y = cfg.get<float>("comboUI_Y").value_or(0.190f);
	enable_scroll_transitions = cfg.get<bool>("enable_scroll_transitions").value_or(true);
	forceCostume = cfg.get<bool>("forceCostume").value_or(false);
	tempCostume = cfg.get<int>("tempCostume").value_or(0);
	randomizeCostume_toggle = cfg.get<bool>("randomizeCostume_toggle").value_or(false);

	forceHairColour_toggle = cfg.get<bool>("forceHairColour_toggle").value_or(false);
	desiredHairColourRGB.x = cfg.get<float>("desiredHairColourRGB_x").value_or(1.0f);
	desiredHairColourRGB.y = cfg.get<float>("desiredHairColourRGB_y").value_or(1.0f);
	desiredHairColourRGB.z = cfg.get<float>("desiredHairColourRGB_z").value_or(1.0f);
	desiredHairColourMult = cfg.get<float>("desiredHairColourMult").value_or(1.0f);
	GameHook::bayoHookFontSize = GameHook::cfg.get<float>("bayoHookFontSize").value_or(16.0f);
#ifdef SPEEDRUN_BUILD
	uptimeFix_toggle = true;
	badgeCorner = cfg.get<int>("badgeCorner").value_or(0);
	badgeScaleBase = cfg.get<float>("badgeScaleBase").value_or(2.5f);
	disableTutorials_toggle = true;
	DisableTutorials(disableTutorials_toggle);
#endif
#ifndef SPEEDRUN_BUILD 
	autoQTE_toggle = cfg.get<bool>("autoQTE_toggle").value_or(false);
	AutoQTE(autoQTE_toggle);
	disableGradient_toggle = cfg.get<bool>("disableGradient_toggle").value_or(false);
	DisableGradient(disableGradient_toggle);
	disableFpsLimiter_toggle = cfg.get<bool>("disableFpsLimiter_toggle").value_or(false);
	DisableFpsLimiter(disableFpsLimiter_toggle);
	uptimeFix_toggle = cfg.get<bool>("uptimeFix_toggle").value_or(false);
	disableTutorials_toggle = cfg.get<bool>("disableTutorials_toggle").value_or(false);
	DisableTutorials(disableTutorials_toggle);
	// patches
	sixtyFpsCutscenes_toggle = cfg.get<bool>("sixtyFpsCutscenes_toggle").value_or(false);
	SixtyFpsCutscenes(sixtyFpsCutscenes_toggle);
	/*memPatch_toggle = cfg.get<bool>("memPatch_toggle").value_or(false);
	MemPatch(memPatch_toggle);*/
	drawFlyingStats_toggle = cfg.get<bool>("drawFlyingStats_toggle").value_or(false);
	showMessages_toggle = cfg.get<bool>("showMessages_toggle").value_or(true);
	damageReceivedMultiplierNoDamage_toggle = cfg.get<bool>("damageReceivedMultiplierNoDamage_toggle").value_or(false);
	infJumps_toggle = cfg.get<bool>("infJumps_toggle").value_or(false);
	InfJumps(infJumps_toggle);
	disableDaze_toggle = cfg.get<bool>("disableDaze_toggle").value_or(false);
	DisableDaze(disableDaze_toggle);
	forceDaze_toggle = cfg.get<bool>("forceDaze_toggle").value_or(false);
	ForceDaze(forceDaze_toggle);
	freezeTimer_toggle = cfg.get<bool>("freezeTimer_toggle").value_or(false);
	FreezeTimer(freezeTimer_toggle);
	disableAfterBurnerBounce_toggle = cfg.get<bool>("disableAfterBurnerBounce_toggle").value_or(false);
	DisableAfterBurnerBounce(disableAfterBurnerBounce_toggle);
	autoCutsceneSkip_toggle = cfg.get<bool>("autoCutsceneSkip_toggle").value_or(false);
	AutoCutsceneSkip(autoCutsceneSkip_toggle);
	disableLockOnDodge_toggle = cfg.get<bool>("disableLockOnDodge_toggle").value_or(false);
	DisableLockOnDodge(disableLockOnDodge_toggle);
	noHoldDodgeOffset_toggle = cfg.get<bool>("noHoldDodgeOffset_toggle").value_or(false);
	NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
	jumpOffset_toggle = cfg.get<bool>("jumpOffset_toggle").value_or(false);
	JumpOffset(jumpOffset_toggle);
	alwaysWalkOnWalls_toggle = cfg.get<bool>("alwaysWalkOnWalls_toggle").value_or(false);
	AlwaysWalkOnWalls(alwaysWalkOnWalls_toggle);
	getMoreHalos_toggle = cfg.get<bool>("getMoreHalos_toggle").value_or(false);
	GetMoreHalos(getMoreHalos_toggle);
	moreEnemyAttacks_toggle = cfg.get<bool>("moreEnemyAttacks_toggle").value_or(false);
	MoreEnemyAttacks(moreEnemyAttacks_toggle);
	lessEnemyAttacks_toggle = cfg.get<bool>("lessEnemyAttacks_toggle").value_or(false);
	LessEnemyAttacks(lessEnemyAttacks_toggle);
	infBirdTime_toggle = cfg.get<bool>("infBirdTime_toggle").value_or(false);
	InfBirdTime(infBirdTime_toggle);
	weaponSwapOffset_toggle = cfg.get<bool>("weaponSwapOffset_toggle").value_or(false);
	WeaponSwapOffset(weaponSwapOffset_toggle);
	retainPillowTalkCharge_toggle = cfg.get<bool>("retainPillowTalkCharge_toggle").value_or(false);
	RetainPillowTalkCharge(retainPillowTalkCharge_toggle);
	swapMashToHold_toggle = cfg.get<bool>("swapMashToHold_toggle").value_or(false);
	SwapMashToHold(swapMashToHold_toggle);
	jeanneBayoWT_toggle = cfg.get<bool>("jeanneBayoWT_toggle").value_or(false);
	JeanneBayoWT(jeanneBayoWT_toggle);
	infDivekick_toggle = cfg.get<bool>("infDivekick_toggle").value_or(false);
	InfDivekick(infDivekick_toggle);
	parryOffset_toggle = cfg.get<bool>("parryOffset_toggle").value_or(false);
	ParryOffset(parryOffset_toggle);
	disableDoubleTapHeelKick_toggle = cfg.get<bool>("disableDoubleTapHeelKick_toggle").value_or(false);
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
	skipAngelAttack_toggle = cfg.get<bool>("skipAngelAttack_toggle").value_or(false);
	SkipAngelAttack(skipAngelAttack_toggle);
	skipMapScene_toggle = cfg.get<bool>("skipMapScene_toggle").value_or(false);
	SkipMapScene(skipMapScene_toggle);
	unbanClimaxBrace_toggle = cfg.get<bool>("unbanClimaxBrace_toggle").value_or(false);
	UnbanClimaxBrace(unbanClimaxBrace_toggle);
	tauntWithTimeBracelet_toggle = cfg.get<bool>("tauntWithTimeBracelet_toggle").value_or(false);
	TauntWithTimeBracelet(tauntWithTimeBracelet_toggle);

	// detours
	drawHitboxes_toggle = cfg.get<bool>("drawHitboxes_toggle").value_or(false);
	openMenuPause_toggle = cfg.get<bool>("openMenuPause_toggle").value_or(false);
	enemyHPNoDamage_toggle = cfg.get<bool>("enemyHPNoDamage_toggle").value_or(false);
	DisableKilling(enemyHPNoDamage_toggle);
	enemyHPOneHitKill_toggle = cfg.get<bool>("enemyHPOneHitKill_toggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("witchTimeMultiplier_toggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("witchTimeMultiplier").value_or(1.0f);
	infMagic_toggle = cfg.get<bool>("infMagic_toggle").value_or(false);
	infMagic_value = cfg.get<float>("infMagic_value").value_or(1200.0f);

	damageDealtMultiplier_toggle = cfg.get<bool>("damageDealtMultiplier_toggle").value_or(false);
	damageDealtMultiplierMult = cfg.get<float>("damageDealtMultiplierMult").value_or(1.0f);

	damageReceivedMultiplier_toggle = cfg.get<bool>("damageReceivedMultiplier_toggle").value_or(false);
	incoming_damage_mult = cfg.get<float>("damageReceivedMultiplierMult").value_or(1.0f);

	customCameraDistance_toggle = cfg.get<bool>("customCameraDistance_toggle").value_or(false);
	customCameraDistance = cfg.get<float>("customCameraDistance").value_or(10.0f);
	lessClothes_toggle = cfg.get<bool>("lessClothes_toggle").value_or(false);
	haloDisplay_toggle = cfg.get<bool>("haloDisplay_toggle").value_or(false);
	easierMash_toggle = cfg.get<bool>("easierMash_toggle").value_or(false);
	initialAngelSlayerFloor = cfg.get<int>("initialAngelSlayerFloor").value_or(0);
	cancellableAfterBurner_toggle = cfg.get<bool>("cancellableAfterBurner_toggle").value_or(false);
	cancellableFallingKick_toggle = cfg.get<bool>("cancellableFallingKick_toggle").value_or(false);
	turbo_toggle = cfg.get<bool>("turbo_toggle").value_or(false);
	turboValue = cfg.get<float>("turboValue").value_or(1.0f);
	altTeleInput_toggle = cfg.get<bool>("altTeleInput_toggle").value_or(false);
	teleportComboAction_toggle = cfg.get<bool>("teleportComboAction_toggle").value_or(false);
	disableSlowmo_toggle = cfg.get<bool>("disableSlowmo_toggle").value_or(false);
	lowerDivekick_toggle = cfg.get<bool>("lowerDivekick_toggle").value_or(false);
	dualAfterBurner_toggle = cfg.get<bool>("dualAfterBurner_toggle").value_or(false);
	loadReplace_toggle = cfg.get<bool>("loadReplace_toggle").value_or(false);
	longerPillowTalkCharge_toggle = cfg.get<bool>("longerPillowTalkCharge_toggle").value_or(false);
	alwaysWitchTime_toggle = cfg.get<bool>("alwaysWitchTime_toggle").value_or(false);
	saveStatesHotkeys_toggle = cfg.get<bool>("saveStatesHotkeys_toggle").value_or(false);
	omnicancelTele_toggle = cfg.get<bool>("omnicancelTele_toggle").value_or(false);
	drawPlayerBones_toggle = cfg.get<bool>("drawPlayerBones_toggle").value_or(false);

	moveIDSwaps_toggle = cfg.get<bool>("moveIDSwaps_toggle").value_or(false);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		moveIDSwap_toggles[i] = cfg.get<bool>(std::string("moveIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		moveIDSwapSourceMoves[i] = cfg.get<int>(std::string("moveIDSwapSourceMoves[") + std::to_string(i) + "]").value_or(-1);
		moveIDSwapSwappedMoves[i] = cfg.get<int>(std::string("moveIDSwapSwappedMoves[") + std::to_string(i) + "]").value_or(-1);
	}

	stringSwaps_toggle = cfg.get<bool>("stringSwaps_toggle").value_or(false);
	for (int i = 0; i < maxStringSwaps; ++i) {
		stringIDSwap_toggles[i] = cfg.get<bool>(std::string("stringIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		stringIDSwapSourceStrings[i] = cfg.get<int>(std::string("stringIDSwapSourceStrings[") + std::to_string(i) + "]").value_or(-1);
		stringIDSwapDesiredStrings[i] = cfg.get<int>(std::string("stringIDSwapDesiredStrings[") + std::to_string(i) + "]").value_or(-1);
	}

	comboMaker_toggle = cfg.get<bool>("comboMaker_toggle").value_or(false);
	for (int i = 0; i < maxComboMakers; ++i) {
		comboMaker_toggles[i] = cfg.get<bool>(std::string("ComboMaker_toggles[") + std::to_string(i) + "]").value_or(false);
		comboMakerMoveIDs[i] = cfg.get<int>(std::string("ComboMakerMoveIDs[") + std::to_string(i) + "]").value_or(-1);
		comboMakerMoveParts[i] = cfg.get<int>(std::string("ComboMakerMoveParts[") + std::to_string(i) + "]").value_or(-1);
		comboMakerStringIDs[i] = cfg.get<int>(std::string("ComboMakerStringIDs[") + std::to_string(i) + "]").value_or(-1);
	}

	customWeave_toggle = cfg.get<bool>("customWeave_toggle").value_or(false);
	for (int i = 0; i < customWeaveCount; ++i) {
		customWeaves_toggles[i] = cfg.get<bool>(std::string("CustomWeaves_toggles[") + std::to_string(i) + "]").value_or(false);
		customWeaveMoveIDArray[i] = cfg.get<int>(std::string("CustomWeaveMoveIDArray[") + std::to_string(i) + "]").value_or(-1);
		customWeaveArray[i] = cfg.get<int>(std::string("CustomWeaveArray[") + std::to_string(i) + "]").value_or(-1);
	}

	//tick
	GameHook::desiredThirdAccessory = cfg.get<int>("DesiredThirdAccessoryValue").value_or(0);
#endif
}

void GameHook::onConfigSave(utils::Config& cfg) {
	cfg.set<bool>("uptimeFix_toggle", uptimeFix_toggle);
	cfg.set<bool>("focusPatch_toggle", focusPatch_toggle);
	cfg.set<bool>("inputIcons_toggle", inputIcons_toggle);
	cfg.set<int>("inputIconsValue", inputIconsValue);
	cfg.set<bool>("showComboUI_toggle", showComboUI_toggle);
	cfg.set<float>("comboUI_X", comboUI_X);
	cfg.set<float>("comboUI_Y", comboUI_Y);
	cfg.set<bool>("enable_scroll_transitions", enable_scroll_transitions);
	cfg.set<bool>("forceCostume", GameHook::forceCostume);
	cfg.set<int>("tempCostume", GameHook::tempCostume);
	cfg.set<bool>("disableTutorials_toggle", disableTutorials_toggle);
	cfg.set<bool>("randomizeCostume_toggle", randomizeCostume_toggle);
	cfg.set<bool>("forceHairColour_toggle", forceHairColour_toggle);
	cfg.set<float>("desiredHairColourRGB_x", desiredHairColourRGB.x);
	cfg.set<float>("desiredHairColourRGB_y", desiredHairColourRGB.y);
	cfg.set<float>("desiredHairColourRGB_z", desiredHairColourRGB.z);
	cfg.set<float>("desiredHairColourMult", desiredHairColourMult);
	cfg.set<float>("bayoHookFontSize", bayoHookFontSize);
#ifdef SPEEDRUN_BUILD
	cfg.set<int>("badgeCorner", badgeCorner);
	cfg.set<float>("badgeScaleBase", badgeScaleBase);
#endif
#ifndef SPEEDRUN_BUILD
	// patches
	cfg.set<bool>("autoQTE_toggle", autoQTE_toggle);
	cfg.set<bool>("disableGradient_toggle", disableGradient_toggle);
	cfg.set<bool>("disableFpsLimiter_toggle", disableFpsLimiter_toggle);
	cfg.set<bool>("sixtyFpsCutscenes_toggle", sixtyFpsCutscenes_toggle);
	// cfg.set<bool>("memPatch_toggle", memPatch_toggle);
	cfg.set<bool>("damageReceivedMultiplierNoDamage_toggle", damageReceivedMultiplierNoDamage_toggle);
	cfg.set<bool>("infJumps_toggle", infJumps_toggle);
	cfg.set<bool>("disableDaze_toggle", disableDaze_toggle);
	cfg.set<bool>("forceDaze_toggle", forceDaze_toggle);
	cfg.set<bool>("freezeTimer_toggle", freezeTimer_toggle);
	cfg.set<bool>("showMessages_toggle", showMessages_toggle);
	cfg.set<bool>("disableAfterBurnerBounce_toggle", disableAfterBurnerBounce_toggle);
	cfg.set<bool>("autoCutsceneSkip_toggle", autoCutsceneSkip_toggle);
	cfg.set<bool>("disableLockOnDodge_toggle", disableLockOnDodge_toggle);
	cfg.set<bool>("noHoldDodgeOffset_toggle", noHoldDodgeOffset_toggle);
	cfg.set<bool>("jumpOffset_toggle", jumpOffset_toggle);
	cfg.set<bool>("alwaysWalkOnWalls_toggle", alwaysWalkOnWalls_toggle);
	cfg.set<bool>("getMoreHalos_toggle", getMoreHalos_toggle);
	cfg.set<bool>("moreEnemyAttacks_toggle", moreEnemyAttacks_toggle);
	cfg.set<bool>("lessEnemyAttacks_toggle", lessEnemyAttacks_toggle);
	cfg.set<bool>("infBirdTime_toggle", infBirdTime_toggle);
	cfg.set<bool>("weaponSwapOffset_toggle", weaponSwapOffset_toggle);
	cfg.set<bool>("retainPillowTalkCharge_toggle", retainPillowTalkCharge_toggle);
	cfg.set<bool>("swapMashToHold_toggle", swapMashToHold_toggle);
	cfg.set<bool>("jeanneBayoWT_toggle", jeanneBayoWT_toggle);
	cfg.set<bool>("infDivekick_toggle", infDivekick_toggle);
	cfg.set<bool>("parryOffset_toggle", parryOffset_toggle);
	cfg.set<bool>("disableDoubleTapHeelKick_toggle", disableDoubleTapHeelKick_toggle);
	cfg.set<bool>("freezeDifficulty_toggle", freezeDifficulty_toggle);
	cfg.set<bool>("hideHalos_toggle", hideHalos_toggle);
	cfg.set<bool>("multiplayerPatch_toggle", multiplayerPatch_toggle);
	cfg.set<bool>("noEnragedHitstop_toggle", noEnragedHitstop_toggle);
	cfg.set<bool>("noHitstop_toggle", noHitstop_toggle);
	cfg.set<bool>("skipAngelAttack_toggle", skipAngelAttack_toggle);
	cfg.set<bool>("skipMapScene_toggle", skipMapScene_toggle);
	cfg.set<bool>("unbanClimaxBrace_toggle", unbanClimaxBrace_toggle);

	// detours
	cfg.set<bool>("drawHitboxes_toggle", drawHitboxes_toggle);
	cfg.set<bool>("openMenuPause_toggle", openMenuPause_toggle);
	cfg.set<bool>("enemyHPNoDamage_toggle", enemyHPNoDamage_toggle);
	cfg.set<bool>("enemyHPOneHitKill_toggle", enemyHPOneHitKill_toggle);
	cfg.set<bool>("witchTimeMultiplier_toggle", witchTimeMultiplier_toggle);
	cfg.set<float>("witchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("infMagic_toggle", infMagic_toggle);
	cfg.set<float>("infMagic_value", infMagic_value);
	cfg.set<bool>("damageDealtMultiplier_toggle", damageDealtMultiplier_toggle);
	cfg.set<float>("damageDealtMultiplierMult", damageDealtMultiplierMult);
	cfg.set<bool>("damageReceivedMultiplier_toggle", damageReceivedMultiplier_toggle);
	cfg.set<float>("incoming_damage_mult", incoming_damage_mult);
	cfg.set<bool>("customCameraDistance_toggle", customCameraDistance_toggle);
	cfg.set<float>("customCameraDistance", customCameraDistance);
	cfg.set<bool>("lessClothes_toggle", lessClothes_toggle);
	cfg.set<bool>("haloDisplay_toggle", haloDisplay_toggle);
	cfg.set<bool>("easierMash_toggle", easierMash_toggle);
	cfg.set<int>("initialAngelSlayerFloor", initialAngelSlayerFloor);
	cfg.set<bool>("cancellableAfterBurner_toggle", cancellableAfterBurner_toggle);
	cfg.set<bool>("cancellableFallingKick_toggle", cancellableFallingKick_toggle);
	cfg.set<bool>("turbo_toggle", turbo_toggle);
	cfg.set<float>("turboValue", turboValue);
	cfg.set<bool>("altTeleInput_toggle", altTeleInput_toggle);
	cfg.set<bool>("teleportComboAction_toggle", teleportComboAction_toggle);
	cfg.set<bool>("disableSlowmo_toggle", disableSlowmo_toggle);
	cfg.set<bool>("lowerDivekick_toggle", lowerDivekick_toggle);
	cfg.set<bool>("dualAfterBurner_toggle", dualAfterBurner_toggle);
	cfg.set<bool>("loadReplace_toggle", loadReplace_toggle);
	cfg.set<bool>("longerPillowTalkCharge_toggle", longerPillowTalkCharge_toggle);
	cfg.set<bool>("alwaysWitchTime_toggle", alwaysWitchTime_toggle);
	cfg.set<bool>("saveStatesHotkeys_toggle", saveStatesHotkeys_toggle);
	cfg.set<bool>("tauntWithTimeBracelet_toggle", tauntWithTimeBracelet_toggle);
	cfg.set<bool>("omnicancelTele_toggle", omnicancelTele_toggle);
	cfg.set<bool>("drawPlayerBones_toggle", drawPlayerBones_toggle);
	cfg.set<bool>("drawFlyingStats_toggle", drawFlyingStats_toggle);

	cfg.set<bool>("moveIDSwaps_toggle", moveIDSwaps_toggle);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		cfg.set<bool>(("moveIDSwap_toggles[" + std::to_string(i) + "]").c_str(), moveIDSwap_toggles[i]);
		cfg.set<int>(("moveIDSwapSourceMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSourceMoves[i]);
		cfg.set<int>(("moveIDSwapSwappedMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSwappedMoves[i]);
	}

	cfg.set<bool>("stringSwaps_toggle", stringSwaps_toggle);
	for (int i = 0; i < maxStringSwaps; ++i) {
		cfg.set<bool>(("stringIDSwap_toggles[" + std::to_string(i) + "]").c_str(), stringIDSwap_toggles[i]);
		cfg.set<int>(("stringIDSwapSourceStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapSourceStrings[i]);
		cfg.set<int>(("stringIDSwapDesiredStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapDesiredStrings[i]);
	}

	cfg.set<bool>("comboMaker_toggle", comboMaker_toggle);
	for (int i = 0; i < maxComboMakers; ++i) {
		cfg.set<bool>(("comboMaker_toggles[" + std::to_string(i) + "]").c_str(), comboMaker_toggles[i]);
		cfg.set<int>(("comboMakerMoveIDs[" + std::to_string(i) + "]").c_str(), comboMakerMoveIDs[i]);
		cfg.set<int>(("comboMakerMoveParts[" + std::to_string(i) + "]").c_str(), comboMakerMoveParts[i]);
		cfg.set<int>(("comboMakerStringIDs[" + std::to_string(i) + "]").c_str(), comboMakerStringIDs[i]);
	}

	cfg.set<bool>("customWeaves_toggles", customWeaves_toggles);
	for (int i = 0; i < customWeaveCount; ++i) {
		cfg.set<bool>(("customWeaves_toggles[" + std::to_string(i) + "]").c_str(), customWeaves_toggles[i]);
		cfg.set<int>(("customWeaveMoveIDArray[" + std::to_string(i) + "]").c_str(), customWeaveMoveIDArray[i]);
		cfg.set<int>(("customWeaveArray[" + std::to_string(i) + "]").c_str(), customWeaveArray[i]);
	}

	// tick
	cfg.set<int>("desiredThirdAccessory", desiredThirdAccessory);
#endif
	cfg.save(GameHook::cfgString);
}
