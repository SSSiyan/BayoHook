#include "bayohook.hpp"

// cheat toggles
bool BayoHook::takeNoDamage_toggle(false);
bool BayoHook::dealNoDamage_toggle(false);
bool BayoHook::showCursor_toggle(false);

// cheat values

// dev values
uintptr_t BayoHook::_baseAddress(NULL);
DWORD BayoHook::_pID(NULL);
uintptr_t BayoHook::actorPlayable(NULL);
bool BayoHook::_hooked(false);

// patches
void BayoHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		//BayoHook::dealNoDamage_toggle = false;
		//BayoHook::DealNoDamage(false);
		BayoHook::_nop((char*)(0x9D4329), 6);
	else
		BayoHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

void BayoHook::DealNoDamage(bool enabled) {
	if (enabled)
		//BayoHook::takeNoDamage_toggle = false;
		//BayoHook::TakeNoDamage(false);
		BayoHook::_nop((char*)(0x4572BA), 6);
	else
		BayoHook::_patch((char*)(0x4572BA), (char*)"\x89\x86\xB4\x06\x00\x00", 6);
}

void BayoHook::ShowCursor(bool enabled) {
	/*if (enabled)
		BayoHook::_patch((char*)(0x51ADE27), (char*)"\x04", 1);
	else
		if (*(char*)(0x51ADE27) != 0x4) {
			BayoHook::_patch((char*)(0x51ADE27), (char*)"\x00", 1);
		}*/
}

/*void BayoHook::TakeNoDamage(bool enabled) {
	if (enabled)
		mem::in::set((mem::voidptr_t)(0x9D4329), ((mem::char_t)'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'), 6);
	else
		mem::in::set((mem::voidptr_t)(0x9D4329), (mem::char_t)'\x90', 6);
		//mem::in::set((mem::voidptr_t)(0x9D4329), (mem::char_t)"\x89\x86\x08\x35\x09\x00", 6);
}*/

// detours
std::unique_ptr<FunctionHook> witchTimeHook;
uintptr_t witchTime_jmp_ret{ NULL };
bool BayoHook::witchTimeMultiplier_toggle = false;
float BayoHook::witchTimeMultiplier = 5.0;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fdiv dword ptr [BayoHook::witchTimeMultiplier]
		jmp dword ptr [witchTime_jmp_ret]

		originalcode:
		fmul dword ptr [esi+0x00095D68]
		jmp dword ptr [witchTime_jmp_ret]
	}
}

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

void BayoHook::InitializeCheats(void) {
	install_hook_absolute(0x9E1808, witchTimeHook, &WitchTimeMultiplierDetour, &witchTime_jmp_ret, 6);
}

void BayoHook::onConfigLoad(const utils::Config& cfg) {
	takeNoDamage_toggle = cfg.get<bool>("TakeNoDamage").value_or(false);
	TakeNoDamage(takeNoDamage_toggle);
	dealNoDamage_toggle = cfg.get<bool>("DealNoDamage").value_or(false);
	DealNoDamage(dealNoDamage_toggle);
};

void BayoHook::onConfigSave(utils::Config& cfg) {
	cfg.set<bool>("TakeNoDamage", takeNoDamage_toggle);
	cfg.set<bool>("DealNoDamage", dealNoDamage_toggle);
	cfg.save("../bayo_hook.cfg"); // idk why the ../ is necessary, it saves in /data without it, as does imgui.ini
};
