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

class GameHook {
public:
	// patches
	// enemyHP_no_damage_toggle
	static void DisableKilling(bool enabled);

	static bool focusPatch_toggle;
	static void FocusPatch(bool enabled);

	static bool infJumps_toggle;
	static void InfJumps(bool enabled);

	static bool disableClicking_toggle;
	static void DisableClicking(bool enabled);

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

	static bool areaJumpPatch_toggle;
	static void AreaJumpPatch(bool enabled);

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

	static bool sixtyFpsCutscenes_toggle;
	static void SixtyFpsCutscenes(bool enabled);

	static bool disableFpsLimiter_toggle;
	static void DisableFpsLimiter(bool enabled);

	static bool jeanneBayoWT_toggle;
	static void JeanneBayoWT(bool enabled);

	static bool infDivekick_toggle;
	static void InfDivekick(bool enabled);

	static bool parryOffset_toggle;
	static void ParryOffset(bool enabled);

	static bool removeVignette_toggle;
	static void RemoveVignette(bool enabled);

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

	static void WeaponSwapCaller(void);
	static void SaveStates_SaveState();
	static void SaveStates_LoadState();

	// detour values
	static bool witchTimeMultiplier_toggle;
	static float witchTimeMultiplier;
	static bool enemyHP_no_damage_toggle;
	static bool enemyHP_one_hit_kill_toggle;
	static bool inf_magic_toggle;
	static float inf_magic_value;

	static bool damageDealtMultiplier_toggle;
	static float damageDealtMultiplierMult;

	static bool damageReceivedMultiplier_no_damage_toggle;
	static bool damageReceivedMultiplier_toggle;
	static float incoming_damage_mult;

	static bool customCameraDistance_toggle;
	static float customCameraDistance;
	static bool inputIcons_toggle;
	static int inputIconsValue;
	static bool haloDisplay_toggle;
	static int haloDisplayValue;
	static bool fixThirdAccessory_toggle;
	//
	static bool moveIDSwapsToggle;
	static const int maxMoveIDSwaps = 5;
	static bool moveIDSwap_toggles[];
	static int moveIDSwapSourceMoves[];
	static int moveIDSwapSwappedMoves[];
	//
	static bool stringSwapsToggle;
	static const int maxStringSwaps = 5;
	static bool stringIDSwap_toggles[];
	static int stringIDSwapSourceStrings[];
	static int stringIDSwapDesiredStrings[];
	//
	static bool comboMakerToggle;
    static const int maxComboMakers = 5;
    static bool comboMaker_toggles[];
    static int comboMakerMoveIDs[];
    static int comboMakerMoveParts[];
    static int comboMakerStringIDs[];
	//
	static bool customWeaveToggle;
	static const int customWeaveCount = 20;
	static bool customWeaves_toggles[];
	static int customWeaveArray[];
	static int customWeaveMoveIDArray[];
	//
	static int desiredThirdAccessory;
	//
	static bool easierMash_toggle;
	static int initialAngelSlayerFloor;
	static bool cancellableAfterBurner_toggle;
	static bool cancellableFallingKick_toggle;
	static bool openMenuPause_toggle;
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

	// addresses
	static uintptr_t playerPointerAddress;
	static uintptr_t halosAddress;
	static uintptr_t chaptersPlayedAddress;
	static uintptr_t playerMagicAddress;
	static uintptr_t comboPointsAddress;
	static uintptr_t comboMultiplierAddress;
	static uintptr_t currentCharacterAddress;
	static uintptr_t currentCostumeAddress;
	static uintptr_t thirdAccessoryAddress;
	static uintptr_t hudDisplayAddress;
	static uintptr_t enemySlotsAddress;
	static uintptr_t enemyLockedOnAddress;
	static uintptr_t angelSlayerFloorAddress;
	static uintptr_t difficultyAddress;
	static uintptr_t areaJumpAddress;
	static uintptr_t WeaponA1Address;
	static uintptr_t WeaponA2Address;
	static uintptr_t WeaponB1Address;
	static uintptr_t WeaponB2Address;

	// imgui
	static float windowHeightHack;
	static float maxWindowHeight;
	static float windowWidth;
	static float windowHeightBorder;
	static float inputItemWidth;
	static float sameLineWidth;
	static float windowScalingFactor;
	static void GameTick(void);
	static void GameImGui(void);
	static bool showMessages_toggle;
	static bool showComboUI_toggle;
	static float comboUI_X;
	static float comboUI_Y;
	static void BackgroundImGui(void);
	static void ImGuiStyle(void);
	static void help_marker(const char* desc);
	static inline void under_line(const ImColor& col);
	static const char* weaponNames[19];
	static const char* weaveNames[37];
	static const char* costumeNames[32];
	static const char* accessoryNames[13];
	static const char* moveIDNames[350];
	static int messageTimerFill;
	static int showMessageTimerF1;
	static int showMessageTimerF2;
	static int showMessageTimerF3;
	static int showMessageTimerF4;
	static int showMessageTimerF5;
	static int showMessageTimerF6;

	static LocalPlayer* GetLocalPlayer();

	static bool CheckCanSpawnEntity();
	typedef void(__thiscall* SpawnEntityFunc)(uintptr_t* ecx, int entityID, int a2, int a3);
	static void SpawnEntity(int entityID, int a2, int a3);

	// dev functions
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void InitializeDetours();
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

	static inline const char* cfgString{ "../bayo_hook.cfg" };
	static inline utils::Config cfg{ "bayo_hook.cfg" };
	static inline const char* dllName{"BayoHook 1.15"};
	static inline const char* repoUrl{ "https://github.com/SSSiyan/BayoHook" };
private:
};
