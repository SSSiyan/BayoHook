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
	static bool dealNoDamage_toggle;
	static bool witchTimeMultiplier_toggle;
	static bool showCursor_toggle;

	// cheat values
	static float witchTimeMultiplier;

	// cheat functions
	static void TakeNoDamage(bool enabled);
	static void DealNoDamage(bool enabled);
	static void ShowCursor(bool enabled);

	// dev values
	static DWORD _pID;
	static uintptr_t _baseAddress;
	static uintptr_t actorPlayable;
	static bool _hooked;

	// dev functions
	static DWORD _getProcessID(void);
	static uintptr_t _getModuleBaseAddress(DWORD procId, const char* modName);
	static void _hook(void);
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void InitializeCheats();
	//static void update();
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

private:
};
