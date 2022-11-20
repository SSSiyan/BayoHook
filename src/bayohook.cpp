#include "bayohook.hpp"


















// dev values
uintptr_t BayoHook::_baseAddress(NULL);
DWORD BayoHook::_pID(NULL);
uintptr_t BayoHook::actorPlayable(NULL);
bool BayoHook::_hooked(false);

// dev functions
DWORD BayoHook::_getProcessID(void) {
	// search game window
	HWND hwnd = FindWindowA(NULL, "Bayonetta");
	if (hwnd == NULL) {
		// return if game window not found
		return 0;
	}
	DWORD pID;													  // process ID
	GetWindowThreadProcessId(hwnd, &pID);						  // get Process ID
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); // open process
	if (pHandle == INVALID_HANDLE_VALUE) {
		// return if couldn't open the process
		return 0;
	}
	return pID;
}

uintptr_t BayoHook::_getModuleBaseAddress(DWORD procId, const char* modName) {
	return (uintptr_t)GetModuleHandle(NULL);
}

void BayoHook::_hook(void) {
	DWORD ID = BayoHook::_getProcessID();
	if (ID <= 0)
		return;
	BayoHook::_pID = ID;
	BayoHook::_baseAddress = BayoHook::_getModuleBaseAddress(ID, "Bayonetta.exe");
	BayoHook::_hooked = true;
}

void BayoHook::_patch(char* dst, char* src, int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void BayoHook::_nop(char* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void BayoHook::onConfigLoad(const utils::Config& cfg) {
	//takeNoDamage_toggle = cfg.get<bool>("takeNoDamage").value_or(false);
	//takeNoDamage(takeNoDamage_toggle);

	//dealNoDamage_toggle = cfg.get<bool>("dealNoDamage").value_or(false);
	//dealNoDamage(dealNoDamage_toggle);
};

void BayoHook::onConfigSave(utils::Config& cfg) {
	//cfg.set<bool>("takeNoDamage", takeNoDamage_toggle);
	//cfg.set<bool>("dealNoDamage", dealNoDamage_toggle);
	//cfg.save("Bayo_Hook.cfg");
};
