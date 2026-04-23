#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "../utils/config.hpp"
#include "libmem++/libmem.hpp"
#include "MinHook/include/MinHook.h"
#include "../utils/FunctionHook.hpp"
#include "imgui/imgui.h"
#include "sdk/Bayonetta.hpp"
#include <base.h> // for Data::ShowMenu
#include <random> // for random costume
// #include <cstdint> // for forward declaring a struct
#ifndef IM_PI
#define IM_PI 3.14159265358979323846f
#endif

//#define SPEEDRUN_BUILD

#define BAYOHOOK_VERSION "1.16 PRE RELEASE"
#ifndef SPEEDRUN_BUILD
#define BAYOHOOK_EDITION ""
#else
#define BAYOHOOK_EDITION " SPEEDRUN EDITION"
#endif

class GameHook {
public:
	static float deltaTime;
	static float deltaSpeed;
	static std::mt19937 rng;
	// patches
	static bool focusPatch_toggle;
	static void FocusPatch(bool enabled);

	static bool disableClicking_toggle;
	static void DisableClicking(bool enabled);

	static bool disableTutorials_toggle;
	static void DisableTutorials(bool enabled);

	// static bool forceSaveFile;
	// static int forcedFileNum;

#ifndef SPEEDRUN_BUILD
	static bool disableFpsLimiter_toggle;
	static void DisableFpsLimiter(bool enabled);

	static bool linkGameToDelta_toggle;
	static void LinkGameToDelta(bool enabled);

	static bool autoQTE_toggle;
	static void AutoQTE(bool enabled);

	static bool removeVignette_toggle;
	static void RemoveVignette(bool enabled);

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

	static bool lessClothes_toggle;
	static void LessClothes(bool enabled);

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

	static bool tauntWithTimeBracelet_toggle;
	static void TauntWithTimeBracelet(bool enabled);

	static bool hideHalos_toggle;
	static void HideHalos(bool enabled);

	static bool multiplayerPatch_toggle;
	static void MultiplayerPatch(bool enabled);

	static bool noEnragedHitstop_toggle;
	static void NoEnragedHitstop(bool enabled);

	static bool noHitstop_toggle;
	static void NoHitstop(bool enabled);

	static bool unbanClimaxBrace_toggle;
	static void UnbanClimaxBrace(bool enabled);
	
	static void SpawnStuff();
	static bool spawnEnemy;
	static bool spawnWithoutArgs2;
	static int arg1;
	static EntitySpawnArg2 arg2;
	static int arg3;

	static void WeaponSwapCaller(void);
	static void SaveStates_SaveState();
	static void SaveStates_LoadState();
#endif
	// detour values
	static bool uptimeFix_toggle;
	static constexpr INT64 rebase_interval = 60;
	static bool inputIcons_toggle;
	static int inputIconsValue;
	static bool enable_scroll_transitions;
	static float windowScalingFactor;
	static float bayoHookFontSize;
	static bool showComboUI_toggle;
	static bool testComboUI_toggle;
	static float comboUI_X;
	static float comboUI_Y;
	static bool randomizeCostume_toggle;
#ifndef SPEEDRUN_BUILD
	static int initialAngelSlayerFloor;
	static bool openMenuPause_toggle;
	static bool witchTimeMultiplier_toggle;
	static float witchTimeMultiplier;
	static bool enemyHPNoDamage_toggle;
	static bool enemyHPOneHitKill_toggle;
	static bool infMagic_toggle;
	static float infMagic_value;

	static bool damageDealtMultiplier_toggle;
	static float damageDealtMultiplierMult;

	static bool damageReceivedMultiplierNoDamage_toggle;
	static bool damageReceivedMultiplier_toggle;
	static float incoming_damage_mult;

	static bool customCameraDistance_toggle;
	static float customCameraDistance;
	static bool haloDisplay_toggle;
	static int haloDisplayValue;
	//
	static bool moveIDSwaps_toggle;
	static const int maxMoveIDSwaps = 5;
	static bool moveIDSwap_toggles[];
	static int moveIDSwapSourceMoves[];
	static int moveIDSwapSwappedMoves[];
	//
	static bool stringSwaps_toggle;
	static const int maxStringSwaps = 5;
	static bool stringIDSwap_toggles[];
	static int stringIDSwapSourceStrings[];
	static int stringIDSwapDesiredStrings[];
	//
	static bool comboMaker_toggle;
    static const int maxComboMakers = 5;
    static bool comboMaker_toggles[];
    static int comboMakerMoveIDs[];
    static int comboMakerMoveParts[];
    static int comboMakerStringIDs[];
	//
	static bool customWeave_toggle;
	static const int customWeaveCount = 20;
	static bool customWeaves_toggles[];
	static int customWeaveArray[];
	static int customWeaveMoveIDArray[];
	//
	static int desiredThirdAccessory;
	//
	static bool easierMash_toggle;
	static bool cancellableAfterBurner_toggle;
	static bool cancellableFallingKick_toggle;
	static bool turbo_toggle;
	static float turboValue;
	static float turboZero;
	static bool altTeleInput_toggle;
	static bool teleportComboAction_toggle;
	static bool disableSlowmo_toggle;
	static bool lowerDivekick_toggle;
	static bool dualAfterBurner_toggle;
	static bool loadReplace_toggle;
	static bool longerPillowTalkCharge_toggle;
	static bool alwaysWitchTime_toggle;
	static bool omnicancelTele_toggle;
	//
	static bool getMotName_toggle;
	static char getMotName_weaponMotString[0x128];
	static char getMotName_playerMotString[0x128];
	//
	static bool saveStatesHotkeys_toggle;
	static int saveStates_SavedEnemyMoveID;
	static float saveStates_SavedEnemyXYZPos[3];
	static int saveStates_SavedPlayerMoveID;
	static float saveStates_SavedPlayerXYZPos[3];
#endif
	// addresses
	static uintptr_t playerPointerAddress;
	static uintptr_t enemyLockedOnAddress;
	static uintptr_t comboMultiplierAddress;
	static uintptr_t comboPointsAddress;
	static uintptr_t currentCostumeAddress;
	static uintptr_t gameTimeAddress;
	static uintptr_t areaJumpAddress;
#ifndef SPEEDRUN_BUILD
	static uintptr_t angelSlayerFloorAddress;
	static uintptr_t halosAddress;
	static uintptr_t chaptersPlayedAddress;
	static uintptr_t playerMagicAddress;
	static uintptr_t currentCharacterAddress;
	static uintptr_t thirdAccessoryAddress;
	static uintptr_t hudDisplayAddress;
	static uintptr_t enemySlotsAddress;
	static uintptr_t difficultyAddress;
	static uintptr_t WeaponA1Address;
	static uintptr_t WeaponA2Address;
	static uintptr_t WeaponB1Address;
	static uintptr_t WeaponB2Address;
#endif
	// imgui
	static void GameImGui(void);
	static void GameTick(void);
	static void ImGuiStyle(void);
	static void help_marker(const char* desc);
	static inline void under_line(const ImColor& col);
	static ImFont* bayoHookFont;
	static float windowWidth;
	static float inputItemWidth;
	static float sameLineWidth;
	static bool forceHairColour_toggle;
	static Vec3 desiredHairColourRGB;
	static float desiredHairColourMult;
	static void BackgroundImGui(void);
	static bool showMessages_toggle;
#ifdef SPEEDRUN_BUILD
	static float badgeScaleBase;
	static constexpr float badgeThicknessBase = 2.0f;
	static bool badgeDisplay_toggle;
	static bool badgeLines_toggle;
	static int badgeCorner;
	static void RenderBadge();
#endif
	static const char* costumeNames[32];
	static bool forceCostume;
	static int tempCostume;
#ifndef SPEEDRUN_BUILD
	static bool drawHitboxes_toggle;
	static bool drawPlayerBones_toggle;
	static void Draw3dShapes();
	static bool drawFlyingStats_toggle;
	static void DrawFlyingStats();
	static const char* weaponNames[19];
	static const char* weaveNames[37];
	static const char* accessoryNames[13];
	static const char* moveIDNames[350];
#endif

	// dev functions
	static LocalPlayer* GetLocalPlayer();;

	struct HotkeyMessage {
		std::string text;
		bool enabled;
		float timeRemaining;
	};

	static void DisplayMessageText(const char* text, bool enabled, float duration = 2.0f);
	static void RenderMessages(float deltaTime);
	static std::vector<GameHook::HotkeyMessage> activeMessages;

	typedef void(__thiscall* AreaJumpFunc)(uintptr_t ecx, int stage, int part, int spawn);
	static void AreaJump(int stage, int part, int spawn);

#ifndef SPEEDRUN_BUILD
	static void Setup3dShapes();
	static void SpawnEntity(int entityID, EntitySpawnArg2* a2, int a3);
#endif
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void InitializeDetours();
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

	static inline const char* cfgString{ "../bayo_hook.cfg" };
	static inline utils::Config cfg{ "bayo_hook.cfg" };
	static inline const char* dllName = "BayoHook " BAYOHOOK_VERSION BAYOHOOK_EDITION;
	static inline const char* repoUrl{ "https://github.com/SSSiyan/BayoHook" };

private:
};
