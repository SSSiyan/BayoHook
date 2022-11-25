#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "../utils/config.hpp"
#include "libmem++/libmem.hpp"
#include "MinHook/include/MinHook.h"
#include "../utils/FunctionHook.hpp"

class BayoHook {
public:
	// cheat toggles
	static bool takeNoDamage_toggle;
	static bool focusPatch_toggle;
	static bool infJumps_toggle;
	static bool disableClicking_toggle;
	static bool lessClothes_toggle;
	// cheat functions
	static void TakeNoDamage(bool enabled);
	static void FocusPatch(bool enabled);
	static void InfJumps(bool enabled);
	static void DisableClicking(bool enabled);

	// detour values
	static bool witchTimeMultiplier_toggle;
	static float witchTimeMultiplier;
	static bool enemyHP_no_damage_toggle;
	static bool enemyHP_one_hit_kill_toggle;
	static bool inf_magic_toggle;
	static bool outgoingDamageMultiplier_toggle;
	static float outgoingDamageMultiplierMult;
	static bool customCameraDistance_toggle;
	static float customCameraDistanceMultiplierMult;

	// update
	static void Update(void);
	static uintptr_t actorPlayable;
	static float xyzpos[3];
	static int halos;
	static int chaptersPlayed;
	static int playerHealth;
	static float remainingWitchTimeDuration;
	static float playerMagic;
	static int comboPoints;
	static int currentCharacter;
	static int thirdAccessory;
	static bool hudDisplay;

	// setters
	static void SetXYZPos(float x, float y, float z);
	static void SetHalos(int value);
	static void SetChaptersPlayed(int value);
	static void SetHealth(int value);
	static void SetRemainingWitchTimeDuration(float value);
	static void SetMagic(float value);
	static void SetComboPoints(int value);
	static void SetCurrentCharacter(int value);
	static void SetThirdAccessory(int value);
	static void SetHudDisplay(bool value);

	// dev functions
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void InitializeDetours();
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

private:
};
