#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "../utils/config.hpp" // save+load
#include "libmem++/libmem.hpp" // unique_ptr
#include "MinHook/include/MinHook.h"
#include "../utils/FunctionHook.hpp"
#include "../utils/Input.hpp"
#include "imgui/imgui.h"
#include "sdk/Bayonetta.hpp"
#include <random> // for random costume
#ifndef IM_PI
#define IM_PI 3.14159265358979323846f
#endif

// #define SPEEDRUN_BUILD

#define BAYOHOOK_VERSION "2.0.3 PRE RELEASE"
#ifndef SPEEDRUN_BUILD
#define BAYOHOOK_EDITION ""
#else
#define BAYOHOOK_EDITION " SPEEDRUN EDITION"
#endif

class GameHook {
public:
#ifdef SPEEDRUN_BUILD
	static float badgeScaleBase;
	static constexpr float badgeThicknessBase = 2.0f;
	static bool badgeDisplay_toggle;
	static bool badgeLines_toggle;
	static int badgeCorner;
	static void RenderBadge();
#endif
#ifndef SPEEDRUN_BUILD
	static bool drawHitboxes_toggle;
	static HookContext getHitbox;

	static bool enemyHPNoDamage_toggle;
	static bool enemyHPOneHitKill_toggle;
	static HookContext enemyHP;

	static bool witchTimeMultiplier_toggle;
	static float witchTimeMultiplier_value;
	static HookContext witchTimeMultiplier;

	static bool damageDealtMultiplier_toggle;
	static float damageDealtMultiplierMult;
	static HookContext damageDealtMultiplier;

	static bool damageReceivedMultiplierNoDamage_toggle;
	static bool damageReceivedMultiplier_toggle;
	static float incoming_damage_mult;
	static HookContext damageReceivedMultiplier;

	static bool infMagic_toggle;
	static HookContext infMagic;

	static bool customCameraDistance_toggle;
	static float customCameraDistance_value;
	static HookContext customCameraDistance;

	static bool haloDisplay_toggle;
	static int haloDisplayValue;
	static HookContext haloDisplay;

	static bool moveIDSwap_toggle; // if this is true, toggle all 5 hooks
	static const int maxMoveIDSwaps = 5;
	static bool moveIDSwap_toggles[];
	static int moveIDSwapSourceMoves[];
	static int moveIDSwapSwappedMoves[];
	static HookContext moveIDSwap;
	static HookContext punchStringIDSwap;
	static HookContext latePunchStringIDSwap;
	static HookContext kickStringIDSwap;
	static HookContext lateKickStringIDSwap;

	static bool easierMash_toggle;
	static HookContext easierMash;

	static int initialAngelSlayerFloor_value; // if this is >0, enable hook
	static HookContext initialAngelSlayerFloor;

	static bool pvp_toggle; // if this is true, enable all 4 hooks
	static bool pvpDamageRemaps_toggle; // this is used inside hooks, does not toggle hooks
	static int lastSeenAtk;
	static int lastSeenAtkConverted;
	static int atkTest;
	static int atkTestReplacement;
	static HookContext pvp1;
	static HookContext pvp2;
	static HookContext pvp3;
	static HookContext pvp4;

	static bool cameraSelect_toggle;
	static int cameraSelect_newCameraType;
	static HookContext cameraSelect;

	static bool customEffectColours_toggle; // if either of these is true, toggle the hook
	static bool identifyEffects_toggle; // if either of these is true, toggle the hook
	static int customEffectColoursRestrictionID;
	static ImColor effectCol[10];
	static std::vector<int> seenEffectIDs;
	static HookContext customEffectColours;

	static bool cancellableAfterBurner_toggle;
	static HookContext cancellableAfterBurner;

	static bool cancellableFallingKick_toggle; // if this is true, toggle both hooks
	static HookContext cancellableFallingKick;
	static HookContext cancellableFallingKickDurga;

	static bool altTeleInput_toggle; // if this is enabled, enable altTeleInput, tauntWithTimeBraceletA and tauntWithTimeBraceletB
	static HookContext altTeleInput;
	static bool tauntWithTimeBracelet_toggle; // if this is toggled, enable tauntWithTimeBraceletA and tauntWithTimeBraceletB
	static void TauntWithTimeBracelet(bool enabled);
	static HookContext tauntWithTimeBraceletA;
	static HookContext tauntWithTimeBraceletB;

	static bool disableSlowmo_toggle;
	static HookContext disableSlowmo;

	static bool lowerDivekick_toggle;
	static HookContext lowerDivekick;

	static bool dualAfterBurner_toggle;
	static HookContext dualAfterBurner;

	static bool longerPillowTalkCharge_toggle;
	static HookContext longerPillowTalkCharge;

	static bool alwaysWitchTime_toggle;
	static HookContext alwaysWitchTime;

	static bool customWeaves_toggle; // only use this toggle for customWeaves
	static const int customWeaveCount = 20;
	static bool customWeave_toggles[];
	static int customWeaveArray[];
	static int customWeaveMoveIDArray[];
	static HookContext customWeaves;

	static bool omnicancelTele_toggle;
	static HookContext omnicancelTele;

	static bool randomizeSpawns_toggle; // if any of these 3 are true, toggle the hook
	static bool viewEntitySpawns_toggle;
	static bool swapSpawns_toggle;
	static HookContext viewEntitySpawns;

	static bool teleportComboAction_toggle;
	static HookContext teleportComboAction;

	static HookContext fixThirdAccessory;

	static bool thirdAccessoryMenu_toggle;
	static HookContext thirdAccessoryMenu;

	// static HookContext animationScrub; // unused

	// these have no toggle and are always enabled
	static HookContext pl0012;
	static HookContext pl0031;
	static HookContext pl004c;

	//static utility::Hotkey* pad_hk_toggle_menu;
	static utility::Hotkey* hk_enemy_no_damage;
	static utility::Hotkey* hk_player_no_damage;
	static utility::Hotkey* hk_enemy_one_hit_kill;
	static utility::Hotkey* hk_inf_jumps;
	static utility::Hotkey* hk_no_clip;
	static utility::Hotkey* hk_force_summoning_clothes;
	static utility::Hotkey* hk_end_current_fight;
	static int current_fight_timer;
	static utility::Hotkey* hk_save_state;
	static utility::Hotkey* hk_load_state;

	static utility::Hotkey* hk_spawn_affinity_spear;
	static utility::Hotkey* hk_spawn_affinity_trumpet;
	static utility::Hotkey* hk_spawn_applaud_spear;
	static utility::Hotkey* hk_spawn_applaud_greatsword;
	static utility::Hotkey* hk_spawn_enchant;
	static utility::Hotkey* hk_spawn_ardor_greatsword;
	static utility::Hotkey* hk_spawn_ardor_axe;
	static utility::Hotkey* hk_spawn_affinity_laser;
	static utility::Hotkey* hk_spawn_fearless;
	static utility::Hotkey* hk_spawn_fairness;
	static utility::Hotkey* hk_spawn_harmony;
	static utility::Hotkey* hk_spawn_brave;
	static utility::Hotkey* hk_spawn_joy;
	static utility::Hotkey* hk_spawn_grace;
	static utility::Hotkey* hk_spawn_glory;
	static utility::Hotkey* hk_spawn_gracious;
	static utility::Hotkey* hk_spawn_glorious;
	static utility::Hotkey* hk_spawn_kinship;
	static utility::Hotkey* hk_spawn_beloved;
	static utility::Hotkey* hk_spawn_golem;
	static utility::Hotkey* hk_spawn_fortitudo;
	static utility::Hotkey* hk_spawn_balder;
	static utility::Hotkey* hk_spawn_jeanne_formal;
	static utility::Hotkey* hk_spawn_bayonetta;

	// patches (non-speedrun)
	static bool forceCutsceneFace_toggle;
	static void ForceCutsceneFace(bool enabled);

	static bool runWithGuns_toggle;
	static void RunWithGuns(bool enabled);

	static bool autoQTE_toggle;
	static void AutoQTE(bool enabled);

	static bool disableGradient_toggle;
	static void DisableGradient(bool enabled);

	static bool sixtyFpsCutscenes_toggle;
	static void SixtyFpsCutscenes(bool enabled);

	/*static bool memPatch_toggle;
	static void MemPatch(bool enabled);*/

	static void DisableKilling(bool enabled);

	static bool infJumps_toggle;
	static void InfJumps(bool enabled);

	static bool noClip_toggle;
	static void NoClip(bool enabled);

	static bool disableDaze_toggle;
	static void DisableDaze(bool enabled);

	static bool forceDaze_toggle;
	static void ForceDaze(bool enabled);

	static bool freezeTimer_toggle;
	static void FreezeTimer(bool enabled);

	static bool disableAfterBurnerBounce_toggle;
	static void DisableAfterBurnerBounce(bool enabled);

	static bool easyCutsceneSkip_toggle;
	static void EasyCutsceneSkip(bool enabled);

	static bool forceSummoningClothes_toggle;
	static void ForceSummoningClothes(bool enabled);

	static bool disableLockOnDodge_toggle;
	static void DisableLockOnDodge(bool enabled);

	static bool noHoldDodgeOffset_toggle;
	static void NoHoldDodgeOffset(bool enabled);

	static bool jumpOffset_toggle;
	static void JumpOffset(bool enabled);

	static bool alwaysWalkOnWalls_toggle;
	static void AlwaysWalkOnWalls(bool enabled);

	static bool getMoreHalos_toggle;
	static void GetMoreHalos(bool enabled);

	static bool moreEnemyAttacks_toggle;
	static void MoreEnemyAttacks(bool enabled);

	static bool lessEnemyAttacks_toggle;
	static void LessEnemyAttacks(bool enabled);

	static bool infBirdTime_toggle;
	static void InfBirdTime(bool enabled);

	static bool weaponSwapOffset_toggle;
	static void WeaponSwapOffset(bool enabled);

	static bool retainPillowTalkCharge_toggle;
	static void RetainPillowTalkCharge(bool enabled);

	static bool swapMashToHold_toggle;
	static void SwapMashToHold(bool enabled);

	static bool jeanneBayoWT_toggle;
	static void JeanneBayoWT(bool enabled);

	static bool infDivekick_toggle;
	static void InfDivekick(bool enabled);

	static bool parryOffset_toggle;
	static void ParryOffset(bool enabled);

	static bool disableDoubleTapHeelKick_toggle;
	static void DisableDoubleTapHeelKick(bool enabled);

	static bool freezeDifficulty_toggle;
	static void FreezeDifficulty(bool enabled);

	static bool hideHalos_toggle;
	static void HideHalos(bool enabled);

	static bool multiplayerPatch_toggle;
	static void MultiplayerPatch(bool enabled);

	//static bool player2Controller2_toggle;
	static void Player2Controller(int id);

	static bool noEnragedHitstop_toggle;
	static void NoEnragedHitstop(bool enabled);

	static bool noHitstop_toggle;
	static void NoHitstop(bool enabled);

	static bool skipAngelAttack_toggle;
	static void SkipAngelAttack(bool enabled);

	static bool skipMapScene_toggle;
	static void SkipMapScene(bool enabled);

	static bool unbanClimaxBrace_toggle;
	static void UnbanClimaxBrace(bool enabled);

	// static float currentAnimationScrub;
	// static float currentAnimationEndFrame;

	static float infMagic_value;

	static std::vector<SwapRule> swapRules;
	static void DisplayRecentlySpawnedEntitiesInImGui();

	static bool saveStatesHotkeys_toggle;

	static bool stringSwap_toggle;
	static const int maxStringSwaps = 5;
	static bool stringIDSwap_toggles[];
	static int stringIDSwapSourceStrings[];
	static int stringIDSwapDesiredStrings[];

	static bool comboMaker_toggle;
	static const int maxComboMakers = 5;
	static bool comboMaker_toggles[];
	static int comboMakerMoveIDs[];
	static int comboMakerMoveParts[];
	static int comboMakerStringIDs[];

	static char getMotName_weaponMotString[0x128];
	static char getMotName_playerMotString[0x128];

	static int saveStates_SavedEnemyMoveID;
	static float saveStates_SavedEnemyXYZPos[3];
	static int saveStates_SavedPlayerMoveID;
	static float saveStates_SavedPlayerXYZPos[3];

	static uintptr_t angelSlayerFloorAddress;
	static uintptr_t halosAddress;
	static uintptr_t chaptersPlayedAddress;
	static uintptr_t playerMagicAddress;
	static uintptr_t playerMagicUpgradesAddress;
	static uintptr_t currentCharacterAddress;
	static uintptr_t thirdAccessoryAddress;
	static uintptr_t hudDisplayAddress;
	static uintptr_t enemySlotsAddress;
	static uintptr_t difficultyAddress;
	static uintptr_t WeaponA1Address;
	static uintptr_t WeaponA2Address;
	static uintptr_t WeaponB1Address;
	static uintptr_t WeaponB2Address;

	static std::vector<HitboxSnapshot> hitDataList;
	static bool drawPlayerBones_toggle;
	static BayoBone* selectedBone;
	static int selectedBoneIndex;
	static void Draw3dShapes();

	static bool drawStats_toggle;
	static void DrawStats();

	static Matrix4x4 viewProj;
	static void Setup3dShapes();
	static void SpawnEntity(EntitySpawn&);
	static void EasySpawnEntityFromHotkey(int enemyID, int variant, int spawnModifier);
	static void EasySpawnEntityFromGui(int enemyID, int variant, int spawnModifier);
	static void CallFromGameThread();
	static bool spawnEntityFromGui;
	static bool spawnEntityFromHotkey;
	static EntitySpawn guiEntitySpawn;
	static EntitySpawn hotkeyEntitySpawn;

	static void WeaponSwapCaller(void);
	static void SaveStates_SaveState();
	static void SaveStates_LoadState();
#endif
	// both speedrun and non speedrun
	static void UpdateHooks();
	static std::mt19937 rng;

	static bool disableFpsLimiter_toggle;
	static void DisableFpsLimiter(bool enabled);

	static bool uptimeFix_toggle;
	static HookContext uptimeFix;

	static bool inputIcons_toggle;
	static int inputIconsValue;
	static HookContext inputIcons;

	static bool randomizeCostume_toggle;
	static HookContext randomizeCostume;

	static bool linkGameToDelta_toggle; // if this is true, toggle all 7 hooks
	static bool longerBufferWindows_toggle; // if this is true, toggle punchBufferFrames, kickBufferFrames, dodgeBufferFrames and gunBufferFrames
	static void LinkGameToDelta(bool enabled);
	static HookContext punchBufferFrames;
	static HookContext kickBufferFrames;
	static HookContext dodgeBufferFrames;
	static HookContext gunBufferFrames;
	static HookContext controllerCameraSens;
	static HookContext fpsSkateSpeed1;
	static HookContext fpsSkateSpeed2;
	static HookContext fixIntroMoviesTimer;

	static bool turbo_toggle; // if either of these bools are true, toggle the hook
	static bool openMenuPause_toggle;
	static float turboValue;
	static float turboZero;
	static HookContext turbo;

	static void __cdecl GameTimerRebase();
	static constexpr INT64 rebase_interval = 60;
	static bool enable_scroll_transitions;
	static float windowScalingFactor;
	static float bayoHookFontSize;
	static bool showComboUI_toggle;
	static bool testComboUI_toggle;
	static float comboUI_X;
	static float comboUI_Y;

	// patches
	static bool focusPatch_toggle;
	static void FocusPatch(bool enabled);

	static bool disableClicking_toggle;
	static void DisableClicking(bool enabled);

	static bool disableTutorials_toggle;
	static void DisableTutorials(bool enabled);

	static utility::Input g_input;
	static std::vector<std::unique_ptr<utility::Hotkey>> g_hotkeys;
	static utility::Hotkey* hk_toggle_menu;
	// static bool forceSaveFile;
	// static int forcedFileNum;

	// addresses
	static uintptr_t playerPointerAddress;
	static uintptr_t player1PointerAddress;
	static uintptr_t player2PointerAddress;
	static uintptr_t enemyLockedOnAddress;
	static uintptr_t comboMultiplierAddress;
	static uintptr_t comboPointsAddress;
	static uintptr_t currentCostumeAddress;
	static uintptr_t gameTimeAddress;
	static uintptr_t areaJumpAddress;

	// system
	static float deltaTime;
	static float deltaSpeed;
	static float deltaSpeed2;
	static float deltaSpeed3;

	// imgui
	static void GameImGui(void);
	static void GameTick(void);
	static void ImGuiStyle(void);
	static void help_marker(const char* desc);
	static void FlagCheckbox(const char* label, uint32_t& flags, uint32_t flag);
	static inline void under_line(const ImColor& col);
	static ImFont* bayoHookFont;
	static float windowWidth;
	static float inputItemWidth;
	static float sameLineWidth;
	static void BackgroundImGui(void);

	// tick
	static bool showMessages_toggle;
	static bool forceHairColour_toggle;
	static Vec3 desiredHairColourRGB;
	static float desiredHairColourMult;
	static bool forceCostume;
	static int tempCostume;

	// dev functions
	static LocalPlayer* GetLocalPlayer();
	static LocalPlayer* GetPlayer1();
	static LocalPlayer* GetPlayer2();

	struct HotkeyMessage {
		std::string text;
		std::optional<bool> enabled;
		float timeRemaining;
	};

	static void DisplayMessageText(const char* text, std::optional<bool> enabled = std::nullopt);
	static void RenderMessages(float deltaTime);
	static std::vector<GameHook::HotkeyMessage> activeMessages;

	typedef void(__thiscall* AreaJumpFunc)(uintptr_t ecx, int stage, int part, int spawn);
	static void AreaJump(int stage, int part, int spawn);

	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static bool install_hook_absolute(uintptr_t location, std::unique_ptr<FunctionHook>& hook, void* detour, uintptr_t* ret, ptrdiff_t next_instruction_offset);

	static void InitHook(const char* name, uintptr_t addr, void* detour, int size, HookContext& ctx);

	static void ToggleHook(HookContext& ctx, bool enabled);
	static void ToggleHook(HookContext& ctx, std::initializer_list<bool> conditions);

	static void LoadPatches(const utils::Config& cfg);
	static void LoadDetours(const utils::Config& cfg);
	static void LoadSystem(const utils::Config& cfg);

	static void SavePatches(utils::Config& cfg);
	static void SaveDetours(utils::Config& cfg);
	static void SaveSystem(utils::Config& cfg);

	static inline const char* cfgString{ "../bayo_hook.cfg" };
	static inline utils::Config cfg{ "bayo_hook.cfg" };
	static inline const char* dllName = "BayoHook " BAYOHOOK_VERSION BAYOHOOK_EDITION;
	static inline const char* repoUrl{ "https://github.com/SSSiyan/BayoHook" };

private:
};
