#include "GameHook.hpp"

float GameHook::deltaTime = 0.0f;
float GameHook::deltaSpeed = 0.0f;
float GameHook::deltaSpeed2 = 0.0f;
float GameHook::deltaSpeed3 = 0.0f;
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
utility::Input GameHook::g_input;
std::mt19937 GameHook::rng;

std::vector<std::unique_ptr<utility::Hotkey>> GameHook::g_hotkeys;
utility::Hotkey* GameHook::hk_toggle_menu;
//utility::Hotkey* GameHook::pad_hk_toggle_menu;
utility::Hotkey* GameHook::hk_enemy_no_damage;
utility::Hotkey* GameHook::hk_player_no_damage;
utility::Hotkey* GameHook::hk_enemy_one_hit_kill;
utility::Hotkey* GameHook::hk_inf_jumps;
utility::Hotkey* GameHook::hk_no_clip;
utility::Hotkey* GameHook::hk_force_summoning_clothes;
utility::Hotkey* GameHook::hk_end_current_fight;
int GameHook::current_fight_timer = 0; // set it back to default after toggling it for a sec so we don't end a whole verse of Angel Slayer
utility::Hotkey* GameHook::hk_save_state;
utility::Hotkey* GameHook::hk_load_state;
utility::Hotkey* GameHook::hk_spawn_affinity_spear;
utility::Hotkey* GameHook::hk_spawn_affinity_trumpet;
utility::Hotkey* GameHook::hk_spawn_applaud_spear;
utility::Hotkey* GameHook::hk_spawn_applaud_greatsword;
utility::Hotkey* GameHook::hk_spawn_enchant;
utility::Hotkey* GameHook::hk_spawn_ardor_greatsword;
utility::Hotkey* GameHook::hk_spawn_ardor_axe;
utility::Hotkey* GameHook::hk_spawn_affinity_laser;
utility::Hotkey* GameHook::hk_spawn_fearless;
utility::Hotkey* GameHook::hk_spawn_fairness;
utility::Hotkey* GameHook::hk_spawn_harmony;
utility::Hotkey* GameHook::hk_spawn_brave;
utility::Hotkey* GameHook::hk_spawn_joy;
utility::Hotkey* GameHook::hk_spawn_grace;
utility::Hotkey* GameHook::hk_spawn_glory;
utility::Hotkey* GameHook::hk_spawn_gracious;
utility::Hotkey* GameHook::hk_spawn_glorious;
utility::Hotkey* GameHook::hk_spawn_kinship;
utility::Hotkey* GameHook::hk_spawn_beloved;
utility::Hotkey* GameHook::hk_spawn_golem;
utility::Hotkey* GameHook::hk_spawn_fortitudo;
utility::Hotkey* GameHook::hk_spawn_balder;
utility::Hotkey* GameHook::hk_spawn_jeanne_formal;
utility::Hotkey* GameHook::hk_spawn_bayonetta;

// bool GameHook::forceSaveFile = false;
// int GameHook::forcedFileNum = 99;

bool GameHook::forceCostume = false;
int GameHook::tempCostume = 0;

// update
uintptr_t GameHook::playerPointerAddress = 0xEF5A60;
uintptr_t GameHook::player1PointerAddress = 0x5B6075C;
uintptr_t GameHook::player2PointerAddress = 0xF30190;
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

#endif

// INT64 GameHook::rebase_interval = 60; // constexpr now
static float lastTickMs = 0.0f;
static float tickDeltaMs = 16.68f;

void __cdecl GameHook::GameTimerRebase() {
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

// int GameHook::saveStates_SavedEnemyMovePart = 0;
// float GameHook::saveStates_SavedEnemyAnimFrame = 0.0f;
bool GameHook::saveStatesHotkeys_toggle = false;
int GameHook::saveStates_SavedEnemyMoveID = 0;
float GameHook::saveStates_SavedEnemyXYZPos[3];
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

LocalPlayer* GameHook::GetLocalPlayer() {
	if (LocalPlayer* player = *(LocalPlayer**)GameHook::playerPointerAddress)
		return player;
	else
		return nullptr;
}

LocalPlayer* GameHook::GetPlayer1() {
	if (LocalPlayer* player = *(LocalPlayer**)GameHook::player1PointerAddress)
		return player;
	else
		return nullptr;
}

LocalPlayer* GameHook::GetPlayer2() {
	if (LocalPlayer* player = *(LocalPlayer**)GameHook::player2PointerAddress)
		return player;
	else
		return nullptr;
}

void GameHook::AreaJump(int stage, int part, int spawn) {
	uintptr_t ecx = 0xEF5A50;
	uintptr_t areaJumpAddr = 0x506390;
	AreaJumpFunc areaJump = (AreaJumpFunc)areaJumpAddr;
	areaJump(ecx, stage, part, spawn);
}

#ifndef SPEEDRUN_BUILD

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

#if 0
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
		jmp dword ptr [getMotName.jmp_ret]
	}
}
#endif

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

bool GameHook::install_hook_absolute(uintptr_t location, std::unique_ptr<FunctionHook>& hook, void* detour, uintptr_t* ret, ptrdiff_t next_instruction_offset) {
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

void GameHook::InitHook(const char* name, uintptr_t addr, void* detour, int size, HookContext& ctx) {
	ctx.jmp_ret = size ? addr + size : 0;
	ctx.hook = std::make_unique<FunctionHook>(addr, detour);
}

void GameHook::ToggleHook(HookContext& ctx, bool enabled) {
	if (!ctx.hook || !ctx.hook->is_valid())
		return;

	if (ctx.hook->is_enabled() == enabled)
		return;

	if (enabled)
		ctx.hook->create();
	else
		ctx.hook->disable();
}

void GameHook::ToggleHook(HookContext& ctx, std::initializer_list<bool> conditions) {
	bool enabled = false;
	for (bool condition : conditions) {
		if (condition) {
			enabled = true;
			break;
		}
	}

	ToggleHook(ctx, enabled);
}

void GameHook::SaveSystem(utils::Config& cfg) {
#ifdef SPEEDRUN_BUILD
	cfg.set<int>("badgeCorner", badgeCorner);
	cfg.set<float>("badgeScaleBase", badgeScaleBase);
#endif
#ifndef SPEEDRUN_BUILD 
	cfg.set<bool>("drawStats_toggle", drawStats_toggle);
	cfg.set<bool>("inputIcons_toggle", inputIcons_toggle);
	cfg.set<int>("inputIconsValue", inputIconsValue);
	cfg.set<bool>("drawPlayerBones_toggle", drawPlayerBones_toggle);
	cfg.set<bool>("comboMaker_toggle", comboMaker_toggle);
	for (int i = 0; i < maxComboMakers; ++i) {
		cfg.set<bool>(("comboMaker_toggles[" + std::to_string(i) + "]").c_str(), comboMaker_toggles[i]);
		cfg.set<int>(("comboMakerMoveIDs[" + std::to_string(i) + "]").c_str(), comboMakerMoveIDs[i]);
		cfg.set<int>(("comboMakerMoveParts[" + std::to_string(i) + "]").c_str(), comboMakerMoveParts[i]);
		cfg.set<int>(("comboMakerStringIDs[" + std::to_string(i) + "]").c_str(), comboMakerStringIDs[i]);
	}
#endif
	// both speedrun and non speedrun
	for (auto& hk : GameHook::g_hotkeys)
		hk->on_config_save(cfg);
	cfg.set<bool>("showMessages_toggle", showMessages_toggle);
	cfg.set<bool>("showComboUI_toggle", showComboUI_toggle);
	cfg.set<float>("comboUI_X", comboUI_X);
	cfg.set<float>("comboUI_Y", comboUI_Y);
	cfg.set<bool>("enable_scroll_transitions", enable_scroll_transitions);
	cfg.set<bool>("forceCostume", GameHook::forceCostume);
	cfg.set<int>("tempCostume", GameHook::tempCostume);
	cfg.set<bool>("forceHairColour_toggle", forceHairColour_toggle);
	cfg.set<float>("desiredHairColourRGB_x", desiredHairColourRGB.x);
	cfg.set<float>("desiredHairColourRGB_y", desiredHairColourRGB.y);
	cfg.set<float>("desiredHairColourRGB_z", desiredHairColourRGB.z);
	cfg.set<float>("desiredHairColourMult", desiredHairColourMult);
	cfg.set<float>("bayoHookFontSize", bayoHookFontSize);
	cfg.save(GameHook::cfgString);
}

void GameHook::LoadSystem(const utils::Config& cfg) {
#ifdef SPEEDRUN_BUILD
	badgeCorner = cfg.get<int>("badgeCorner").value_or(0);
	badgeScaleBase = cfg.get<float>("badgeScaleBase").value_or(2.5f);
#endif
#ifndef SPEEDRUN_BUILD 
	drawStats_toggle = cfg.get<bool>("drawStats_toggle").value_or(false);
	inputIcons_toggle = cfg.get<bool>("inputIcons_toggle").value_or(false);
	inputIconsValue = cfg.get<int>("inputIconsValue").value_or(0);
	drawPlayerBones_toggle = cfg.get<bool>("drawPlayerBones_toggle").value_or(false);
	//pad_hk_toggle_menu = g_hotkeys.emplace_back(utility::create_gamepad_hotkey({ LEFT_THUMB, RIGHT_THUMB }, "Toggle Menu", "pad_hk_toggle_menu")).get();
	hk_enemy_no_damage = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F1 }, "Enemy Takes No Damage", "hk_enemy_no_damage")).get();
	hk_player_no_damage = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F2 }, "Player Takes No Damage", "hk_player_no_damage")).get();
	hk_enemy_one_hit_kill = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F3 }, "Enemy One Hit Kill", "hk_enemy_one_hit_kill")).get();
	hk_inf_jumps = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F4 }, "Infinite Jumps", "hk_inf_jumps")).get();
	hk_no_clip = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F5 }, "Noclip", "hk_no_clip")).get();
	hk_force_summoning_clothes = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F6 }, "Force Summoning Clothes", "hk_force_summoning_clothes")).get();
	hk_end_current_fight = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_F11 }, "End Current Fight", "hk_end_current_fight")).get();
	hk_save_state = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_HOME }, "Save State", "hk_save_state")).get();
	hk_load_state = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_END }, "Load State", "hk_load_state")).get();
	hk_spawn_affinity_spear = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F1 }, "Spawn Affinity (Spear)", "hk_spawn_affinity_spear")).get();
	hk_spawn_affinity_trumpet = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F2 }, "Spawn Affinity (Trumpet)", "hk_spawn_affinity_trumpet")).get();
	hk_spawn_applaud_spear = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F3 }, "Spawn Applaud (Spear)", "hk_spawn_applaud_spear")).get();
	hk_spawn_applaud_greatsword = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F4 }, "Spawn Applaud (Greatsword)", "hk_spawn_applaud_greatsword")).get();
	hk_spawn_enchant = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F5 }, "Spawn Enchant", "hk_spawn_enchant")).get();
	hk_spawn_ardor_greatsword = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F6 }, "Spawn Ardor (Greatsword)", "hk_spawn_ardor_greatsword")).get();
	hk_spawn_ardor_axe = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F7 }, "Spawn Ardor (Axe)", "hk_spawn_ardor_axe")).get();
	hk_spawn_affinity_laser = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F8 }, "Spawn Affinity (Laser)", "hk_spawn_affinity_laser")).get();
	hk_spawn_fearless = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F9 }, "Spawn Fearless", "hk_spawn_fearless")).get();
	hk_spawn_fairness = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F10 }, "Spawn Fairness", "hk_spawn_fairness")).get();
	hk_spawn_harmony = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F11 }, "Spawn Harmony", "hk_spawn_harmony")).get();
	hk_spawn_brave = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LCONTROL, VK_F12 }, "Spawn Brave", "hk_spawn_brave")).get();
	hk_spawn_joy = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F1 }, "Spawn Joy", "hk_spawn_joy")).get();
	hk_spawn_grace = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F2 }, "Spawn Grace", "hk_spawn_grace")).get();
	hk_spawn_glory = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F3 }, "Spawn Glory", "hk_spawn_glory")).get();
	hk_spawn_gracious = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F4 }, "Spawn Gracious", "hk_spawn_gracious")).get();
	hk_spawn_glorious = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F5 }, "Spawn Glorious", "hk_spawn_glorious")).get();
	hk_spawn_kinship = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F6 }, "Spawn Kinship", "hk_spawn_kinship")).get();
	hk_spawn_beloved = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F7 }, "Spawn Beloved", "hk_spawn_beloved")).get();
	hk_spawn_golem = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F8 }, "Spawn Golem", "hk_spawn_golem")).get();
	hk_spawn_fortitudo = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F9 }, "Spawn Fortitudo", "hk_spawn_fortitudo")).get();
	hk_spawn_balder = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F10 }, "Spawn Balder", "hk_spawn_balder")).get();
	hk_spawn_jeanne_formal = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F11 }, "Spawn Jeanne", "hk_spawn_jeanne")).get();
	hk_spawn_bayonetta = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_LSHIFT, VK_F12 }, "Spawn Bayonetta", "hk_spawn_bayonetta")).get();

	comboMaker_toggle = cfg.get<bool>("comboMaker_toggle").value_or(false);
	for (int i = 0; i < maxComboMakers; ++i) {
		comboMaker_toggles[i] = cfg.get<bool>(std::string("comboMaker_toggles[") + std::to_string(i) + "]").value_or(false);
		comboMakerMoveIDs[i] = cfg.get<int>(std::string("comboMakerMoveIDs[") + std::to_string(i) + "]").value_or(-1);
		comboMakerMoveParts[i] = cfg.get<int>(std::string("comboMakerMoveParts[") + std::to_string(i) + "]").value_or(-1);
		comboMakerStringIDs[i] = cfg.get<int>(std::string("comboMakerStringIDs[") + std::to_string(i) + "]").value_or(-1);
	}

#endif
	hk_toggle_menu = g_hotkeys.emplace_back(utility::create_keyboard_hotkey({ VK_DELETE }, "Toggle Menu", "hk_toggle_menu")).get();
	for (auto& hk : GameHook::g_hotkeys)
		hk->on_config_load(cfg);

	// both speedrun and non speedrun
	showMessages_toggle = cfg.get<bool>("showMessages_toggle").value_or(false);
	showComboUI_toggle = cfg.get<bool>("showComboUI_toggle").value_or(false);
	comboUI_X = cfg.get<float>("comboUI_X").value_or(0.880f);
	comboUI_Y = cfg.get<float>("comboUI_Y").value_or(0.218f);
	enable_scroll_transitions = cfg.get<bool>("enable_scroll_transitions").value_or(true);
	forceCostume = cfg.get<bool>("forceCostume").value_or(false);
	tempCostume = cfg.get<int>("tempCostume").value_or(0);
	forceHairColour_toggle = cfg.get<bool>("forceHairColour_toggle").value_or(false);
	desiredHairColourRGB.x = cfg.get<float>("desiredHairColourRGB_x").value_or(1.0f);
	desiredHairColourRGB.y = cfg.get<float>("desiredHairColourRGB_y").value_or(1.0f);
	desiredHairColourRGB.z = cfg.get<float>("desiredHairColourRGB_z").value_or(1.0f);
	desiredHairColourMult = cfg.get<float>("desiredHairColourMult").value_or(1.0f);
	bayoHookFontSize = cfg.get<float>("bayoHookFontSize").value_or(16.0f);
}
