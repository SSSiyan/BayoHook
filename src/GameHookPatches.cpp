#include "GameHook.hpp"

#ifndef SPEEDRUN_BUILD
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

bool GameHook::forceCutsceneFace_toggle = false;
void GameHook::ForceCutsceneFace(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8B74C4), (char*)"\xB8\x03\x00\x00\x00\x90", 6); // mov eax, 3 nop
	}
	else {
		GameHook::_patch((char*)(0x8B74C4), (char*)"\x8B\x86\xD0\x65\x09\x00", 6); // mov eax, [esi+000965D0]
	}
}

bool GameHook::runWithGuns_toggle = false;
void GameHook::RunWithGuns(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8E9D39), (char*)"\x90\x90\x90\x90\x90\x90", 6); // nop 6
	}
	else {
		GameHook::_patch((char*)(0x8E9D39), (char*)"\x89\xBE\xBC\x6D\x09\x00", 6); // mov [esi+00096DBC],edi
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

bool GameHook::easyCutsceneSkip_toggle = false;
void GameHook::EasyCutsceneSkip(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x48FEC6), (char*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10);
	}
	else {
		GameHook::_patch((char*)(0x48FEC6), (char*)"\xf7\x05\xcc\x93\xa4\x05\x00\x02\x00\x00", 10);
	}
}

bool GameHook::forceSummoningClothes_toggle = false;
void GameHook::ForceSummoningClothes(bool enabled) {
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

// bool GameHook::tauntWithTimeBracelet_toggle = false; // defined in Detours.cpp
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

//bool GameHook::player2Controller2_toggle = false;
void GameHook::Player2Controller(int id) {
	LocalPlayer* player2 = GameHook::GetPlayer2();
	if (player2)
		player2->controllerNum = id;
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

// both speedrun and non speedrun
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

static __declspec(naked) void fldDeltaSpeed1(void) {
	_asm {
		fld dword ptr[GameHook::deltaSpeed]
	}
}
static __declspec(naked) void movssXmm0DeltaSpeed1(void) {
	_asm {
		movss xmm0, [GameHook::deltaSpeed]
	}
}
static __declspec(naked) void movssXmm1DeltaSpeed3(void) {
	_asm {
		movss xmm1, [GameHook::deltaSpeed3]
	}
}
static __declspec(naked) void movssXmm2DeltaSpeed1(void) {
	_asm {
		movss xmm2, [GameHook::deltaSpeed]
	}
}
static __declspec(naked) void movssXmm3DeltaSpeed2(void) {
	_asm {
		movss xmm3, [GameHook::deltaSpeed2]
	}
}

bool GameHook::linkGameToDelta_toggle;
void GameHook::LinkGameToDelta(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x513974), (char*)fldDeltaSpeed1, 6); // Bird (and prob more, verify by noping - bird became invisible)
		GameHook::_patch((char*)(0xA95BD1), (char*)movssXmm0DeltaSpeed1, 8); // Camera
		GameHook::_patch((char*)(0xA9401A), (char*)movssXmm3DeltaSpeed2, 8); // Camera rot
		GameHook::_patch((char*)(0xA9402E), (char*)movssXmm1DeltaSpeed3, 8); // Camera rot panther
		GameHook::_patch((char*)(0xA93FDE), (char*)movssXmm0DeltaSpeed1, 8); // Camera rot jump
		GameHook::_patch((char*)(0x9CDA09), (char*)movssXmm0DeltaSpeed1, 8); // parry
		GameHook::_patch((char*)(0x8BD6BC), (char*)movssXmm2DeltaSpeed1, 8); // bat within / perfect parry / panther + bird double tap timer
		GameHook::_patch((char*)(0x651989), (char*)"\x90\x90", 2); // afterburner kick knockback magnitude check
		// find shooting with legs camera sens
		// find menu speed
		// find whatever's wrong with hitboxes
		// find cutscene speed
	}
	else {
		GameHook::_patch((char*)(0x513974), (char*)"\xD9\x05\x88\x65\xEF\x00", 6); // Bird // fld dword ptr [Bayonetta.exe+AF6588] (1.0f)
		GameHook::_patch((char*)(0xA95BD1), (char*)"\xF3\x0F\x10\x05\x88\x65\xEF\x00", 8); // Camera // movss xmm0,[Bayonetta.exe+AF6588] (1.0f)
		GameHook::_patch((char*)(0xA9401A), (char*)"\xF3\x0F\x10\x1D\xF4\x0B\xDA\x00", 8); // Camera rot // movss xmm3,[Bayonetta.exe+AF6588] (2.0f)
		GameHook::_patch((char*)(0xA9402E), (char*)"\xF3\x0F\x10\x0D\x9C\xD7\xD9\x00", 8); // Camera rot panther // movss xmm1,[Bayonetta.exe+AF6588] (3.0f)
		GameHook::_patch((char*)(0xA93FDE), (char*)"\xF3\x0F\x10\x05\xF8\xD6\xD9\x00", 8); // Camera rot jump // movss xmm0,[Bayonetta.exe+99D6F8] (1.0f)
		GameHook::_patch((char*)(0x9CDA09), (char*)"\xF3\x0F\x10\x05\xF8\xD6\xD9\x00", 8); // parry // movss xmm0,[Bayonetta.exe+99D6F8] (1.0f)
		GameHook::_patch((char*)(0x8BD6BC), (char*)"\xF3\x0F\x10\x15\xF8\xD6\xD9\x00", 8); // bat within / perfect parry / panther + bird double tap timer // movss xmm2,[Bayonetta.exe+99D6F8] (1.0f)
		GameHook::_patch((char*)(0x651989), (char*)"\x76\x48", 2); // afterburner kick knockback magnitude check
	}
}

void GameHook::SavePatches(utils::Config& cfg) {
#ifndef SPEEDRUN_BUILD
	cfg.set<bool>("enemyHPNoDamage_toggle", enemyHPNoDamage_toggle);
	cfg.set<bool>("autoQTE_toggle", autoQTE_toggle);
	cfg.set<bool>("disableGradient_toggle", disableGradient_toggle);
	cfg.set<bool>("sixtyFpsCutscenes_toggle", sixtyFpsCutscenes_toggle);
	// cfg.set<bool>("memPatch_toggle", memPatch_toggle);
	cfg.set<bool>("disableTutorials_toggle", disableTutorials_toggle);
	cfg.set<bool>("infJumps_toggle", infJumps_toggle);
	cfg.set<bool>("disableDaze_toggle", disableDaze_toggle);
	cfg.set<bool>("forceCutsceneFace_toggle", forceCutsceneFace_toggle);
	cfg.set<bool>("runWithGuns_toggle", runWithGuns_toggle);
	// cfg.set<bool>("noClip_toggle", noClip_toggle);
	cfg.set<bool>("forceDaze_toggle", forceDaze_toggle);
	cfg.set<bool>("freezeTimer_toggle", freezeTimer_toggle);
	cfg.set<bool>("disableAfterBurnerBounce_toggle", disableAfterBurnerBounce_toggle);
	cfg.set<bool>("easyCutsceneSkip_toggle", easyCutsceneSkip_toggle);
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
	cfg.set<bool>("tauntWithTimeBracelet_toggle", tauntWithTimeBracelet_toggle);
#endif
	// both speedrun and non speedrun
	cfg.set<bool>("disableFpsLimiter_toggle", disableFpsLimiter_toggle);
	cfg.set<bool>("focusPatch_toggle", focusPatch_toggle);
	cfg.set<bool>("linkGameToDelta_toggle", linkGameToDelta_toggle);
	cfg.save(GameHook::cfgString);
}

void GameHook::LoadPatches(const utils::Config& cfg) {
#ifndef SPEEDRUN_BUILD
	enemyHPNoDamage_toggle = cfg.get<bool>("enemyHPNoDamage_toggle").value_or(false);
	DisableKilling(enemyHPNoDamage_toggle);
	autoQTE_toggle = cfg.get<bool>("autoQTE_toggle").value_or(false);
	AutoQTE(autoQTE_toggle);
	disableGradient_toggle = cfg.get<bool>("disableGradient_toggle").value_or(false);
	DisableGradient(disableGradient_toggle);
	disableTutorials_toggle = cfg.get<bool>("disableTutorials_toggle").value_or(false);
	DisableTutorials(disableTutorials_toggle);
	// patches
	sixtyFpsCutscenes_toggle = cfg.get<bool>("sixtyFpsCutscenes_toggle").value_or(false);
	SixtyFpsCutscenes(sixtyFpsCutscenes_toggle);
	/*memPatch_toggle = cfg.get<bool>("memPatch_toggle").value_or(false);
	MemPatch(memPatch_toggle);*/
	infJumps_toggle = cfg.get<bool>("infJumps_toggle").value_or(false);
	InfJumps(infJumps_toggle);
	disableDaze_toggle = cfg.get<bool>("disableDaze_toggle").value_or(false);
	DisableDaze(disableDaze_toggle);
	forceCutsceneFace_toggle = cfg.get<bool>("forceCutsceneFace_toggle").value_or(false);
	ForceCutsceneFace(forceCutsceneFace_toggle);
	runWithGuns_toggle = cfg.get<bool>("runWithGuns_toggle").value_or(false);
	RunWithGuns(runWithGuns_toggle);
	// noClip_toggle = cfg.get<bool>("noClip_toggle").value_or(false);
	// NoClip(noClip_toggle);
	forceDaze_toggle = cfg.get<bool>("forceDaze_toggle").value_or(false);
	ForceDaze(forceDaze_toggle);
	freezeTimer_toggle = cfg.get<bool>("freezeTimer_toggle").value_or(false);
	FreezeTimer(freezeTimer_toggle);
	disableAfterBurnerBounce_toggle = cfg.get<bool>("disableAfterBurnerBounce_toggle").value_or(false);
	DisableAfterBurnerBounce(disableAfterBurnerBounce_toggle);
	easyCutsceneSkip_toggle = cfg.get<bool>("easyCutsceneSkip_toggle").value_or(false);
	EasyCutsceneSkip(easyCutsceneSkip_toggle);
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
#endif
#ifdef SPEEDRUN_BUILD
	disableTutorials_toggle = true;
	DisableTutorials(disableTutorials_toggle);
#endif
	// both speedrun and non speedrun
	focusPatch_toggle = cfg.get<bool>("focusPatch_toggle").value_or(false);
	FocusPatch(focusPatch_toggle);
	disableFpsLimiter_toggle = cfg.get<bool>("disableFpsLimiter_toggle").value_or(false);
	DisableFpsLimiter(disableFpsLimiter_toggle);
	linkGameToDelta_toggle = cfg.get<bool>("linkGameToDelta_toggle").value_or(false);
	LinkGameToDelta(linkGameToDelta_toggle);

}
