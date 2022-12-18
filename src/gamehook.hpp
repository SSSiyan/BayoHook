#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "../utils/config.hpp"
#include "libmem++/libmem.hpp"
#include "MinHook/include/MinHook.h"
#include "../utils/FunctionHook.hpp"

class GameHook {
public:
	// patch toggles
	static bool takeNoDamage_toggle;
	static bool focusPatch_toggle;
	static bool infJumps_toggle;
	static bool disableClicking_toggle;
	static bool noClip_toggle;
	static bool disableDaze_toggle;
	static bool forceDaze_toggle;
	static bool freezeTimer_toggle;
	static bool disableAfterBurnerBounce_toggle;
	static bool areaJumpPatch_toggle;
	static bool easyCutsceneSkip_toggle;
	static bool lessClothes_toggle;
	static bool disableLockOnDodge_toggle;
	static bool noHoldDodgeOffset_toggle;
	static bool jumpOffset_toggle;
	static bool alwaysWalkOnWalls_toggle;
	static bool getMoreHalos_toggle;
	static bool moreEnemyAttacks_toggle;
	static bool lessEnemyAttacks_toggle;
	static bool infBirdTime_toggle;
	static bool weaponSwapOffset_toggle;
	static bool retainPillowTalkCharge_toggle;
	static bool swapMashToHold_toggle;
	// patch functions
	static void TakeNoDamage(bool enabled);
	static void DisableKilling(bool enabled);
	static void FocusPatch(bool enabled);
	static void InfJumps(bool enabled);
	static void DisableClicking(bool enabled);
	static void NoClip(bool enabled);
	static void DisableDaze(bool enabled);
	static void ForceDaze(bool enabled);
	static void FreezeTimer(bool enabled);
	static void DisableAfterBurnerBounce(bool enabled);
	static void AreaJumpPatch(bool enabled);
	static void EasyCutsceneSkip(bool enabled);
	static void LessClothes(bool enabled);
	static void DisableLockOnDodge(bool enabled);
	static void NoHoldDodgeOffset(bool enabled);
	static void JumpOffset(bool enabled);
	static void AlwaysWalkOnWalls(bool enabled);
	static void GetMoreHalos(bool enabled);
	static void MoreEnemyAttacks(bool enabled);
	static void LessEnemyAttacks(bool enabled);
	static void InfBirdTime(bool enabled);
	static void WeaponSwapOffset(bool enabled);
	static void RetainPillowTalkCharge(bool enabled);
	static void SwapMashToHold(bool enabled);

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
	static bool customCameraDistance_toggle;
	static float customCameraDistance;
	static bool inputIcons_toggle;
	static int inputIconsValue;
	static bool haloDisplay_toggle;
	static int haloDisplayValue;
	//
	static bool moveIDSwap_toggle;

	static int moveIDSwapSourceMove1;
	static int moveIDSwapSourceMove2;

	static int moveIDSwapDesiredMove1;
	static int moveIDSwapDesiredMove2;
	//
	static bool stringIDSwap_toggle;

	static int stringIDSwapSourceString1;
	static int stringIDSwapSourceString2;

	static int stringIDSwapDesiredString1;
	static int stringIDSwapDesiredString2;
	//
	static bool easierMash_toggle;
	static int initialAngelSlayerFloor;
	static bool cancellableAfterBurner_toggle;
	static bool cancellableFallingKick_toggle;
	static bool turbo_toggle;
	static float turboValue;
	static bool altTeleInput_toggle;
	static bool disableSlowmo_toggle;
	static bool lowerDivekick_toggle;
	static bool dualAfterBurner_toggle;
	static bool loadReplace_toggle;
	static bool longerPillowTalkCharge_toggle;
	static float longerPillowTalkChargeMult;

	static bool getMotName_toggle;
	static char getMotName_weaponMotString[0x128];
	static char getMotName_playerMotString[0x128];

	// update
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
	static float windowHeightBorder;
	static float windowWidth;
	static float windowScalingFactor;
	static void GameImGui(void);
	static bool showMessages_toggle;
	static bool showComboUI_toggle;
	static float comboUI_X;
	static float comboUI_Y;
	static void BackgroundImGui(void);
	static void ImGuiStyle(void);
	static const char* WeaponNames(int weaponID);
	static const char* CostumeNames(int costumeID);
	static const char* AccessoryNames(int accessoryID);
	static const char* GetInputTypeName(int inputID);
	static int showMessageTimerF1;
	static int showMessageTimerF2;
	static int showMessageTimerF3;
	static int showMessageTimerF4;
	static int showMessageTimerF5;

	// dev functions
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void InitializeDetours();
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

	static inline const char* cfgString{ "../bayo_hook.cfg" };
	static inline utils::Config cfg{ "bayo_hook.cfg" };
	static inline const char* dllName{"BayoHook 1.00"};
	static inline const char* repoUrl{ "https://github.com/SSSiyan/BayoHook" };
private:
};
