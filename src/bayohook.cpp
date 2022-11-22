#include "bayohook.hpp"

// cheat toggles
bool BayoHook::takeNoDamage_toggle(false);
bool BayoHook::focusPatch_toggle(false);
bool BayoHook::showCursor_toggle(false);
bool BayoHook::infJumps_toggle(false);

// update
uintptr_t playerPointerAddress = 0xEF5A60;
uintptr_t halosAddress = 0x5AA74B4;
uintptr_t chaptersPlayedAddress = 0x5AA736C;
uintptr_t playerMagicAddress = 0x5AA74AC;
uintptr_t comboPointsAddress = 0x5BB519C;

uintptr_t BayoHook::actorPlayable = NULL;
float BayoHook::xyzpos[3]{ 0.0f, 0.0f, 0.0f };
int BayoHook::halos = 0;
int BayoHook::chaptersPlayed = 0;
int BayoHook::playerHealth = 0;
float BayoHook::playerMagic = 0.0f;
int BayoHook::comboPoints = 0;

// patches
void BayoHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		BayoHook::_nop((char*)(0x9D4329), 6);
	else
		BayoHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

void BayoHook::FocusPatch(bool enabled) {
	if (enabled) {
		BayoHook::_patch((char*)(0x49E519), (char*)"\xEB\x17", 2); // disable pausing tabbed out
		BayoHook::_patch((char*)(0x411DB8), (char*)"\xE9\x82\x00", 3); // enable inputs tabbed out
	}
	else {
		BayoHook::_patch((char*)(0x49E519), (char*)"\x75\x17", 2); // enable pausing tabbed out
		BayoHook::_patch((char*)(0x411DB8), (char*)"\x0F\x85\x81", 3); // disable inputs tabbed out
	}
}

void BayoHook::InfJumps(bool enabled) {
	if (enabled) 
		BayoHook::_nop((char*)(0x9E8906), 6);
	else
		BayoHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6);
}

// detours
std::unique_ptr<FunctionHook> enemyHPHook;
uintptr_t enemyHP_jmp_ret{ NULL };
bool BayoHook::enemyHP_no_damage_toggle = false;
bool BayoHook::enemyHP_one_hit_kill_toggle = false;

static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::enemyHP_no_damage_toggle], 1
		je no_damage
		jmp check2

		check2:
			cmp byte ptr [BayoHook::enemyHP_one_hit_kill_toggle], 1
			je one_hit_kill
			jmp originalcode

		no_damage:
			jmp dword ptr [enemyHP_jmp_ret]

		one_hit_kill:
			mov dword ptr [esi+0x000006B4], 0
			jmp dword ptr [enemyHP_jmp_ret]

		originalcode:
			mov [esi+0x000006B4], eax
			jmp dword ptr [enemyHP_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> witchTimeHook;
uintptr_t witchTimeMultiplier_jmp_ret{ NULL };
bool BayoHook::witchTimeMultiplier_toggle = false;
float BayoHook::witchTimeMultiplier = 1.0;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		cmp byte ptr [BayoHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fmul dword ptr [esi+0x00095D68] // might be game speed or something? 1 by default
		fdiv dword ptr [BayoHook::witchTimeMultiplier]
		jmp dword ptr [witchTimeMultiplier_jmp_ret]

		originalcode:
			fmul dword ptr [esi+0x00095D68]
			jmp dword ptr [witchTimeMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> infMagicHook;
uintptr_t inf_magic_jmp_ret{ NULL };
bool BayoHook::inf_magic_toggle = false;
uintptr_t magicAddress = 0x5AA74AC;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		push eax
		cmp byte ptr [BayoHook::inf_magic_toggle], 0
		je originalcode

		mov eax, [magicAddress]
		mov dword ptr [eax], 0x44fa0000 // 2000

		originalcode:
		mov eax, [magicAddress] // i hate that i have to do this
		movss xmm0, [eax]
		pop eax
		jmp dword ptr [inf_magic_jmp_ret]
	}
}

// update
void BayoHook::Update() {
	BayoHook::actorPlayable = (*(uintptr_t*)playerPointerAddress);
	BayoHook::halos = (*(int*)halosAddress);
	if (BayoHook::actorPlayable != NULL) {
		BayoHook::xyzpos[0] = (*(float*)(BayoHook::actorPlayable + 0xD0));
		BayoHook::xyzpos[1] = (*(float*)(BayoHook::actorPlayable + 0xD4));
		BayoHook::xyzpos[2] = (*(float*)(BayoHook::actorPlayable + 0xD8));
		BayoHook::playerHealth = (*(int*)(BayoHook::actorPlayable + 0x93508));
	}
	BayoHook::chaptersPlayed = (*(int*)chaptersPlayedAddress);
	BayoHook::playerMagic = (*(float*)playerMagicAddress);
	BayoHook::comboPoints = (*(int*)comboPointsAddress);
	//BayoHook::zone = (const char*)_baseAddress + 0x4374A24;
}

// setters
void BayoHook::SetXYZPos(float x, float y, float z) {
	(*(float*)(BayoHook::actorPlayable + 0xD0)) = x;
	(*(float*)(BayoHook::actorPlayable + 0xD4)) = y;
	(*(float*)(BayoHook::actorPlayable + 0xD8)) = z;
}

void BayoHook::SetHalos(int value) {
	(*(int*)halosAddress) = value;
}

void BayoHook::SetChaptersPlayed(int value) {
	(*(int*)chaptersPlayedAddress) = value;
}

void BayoHook::SetHealth(int value) {
	(*(int*)(BayoHook::actorPlayable + 0x93508)) = value;
}

void BayoHook::SetMagic(float value) {
	(*(float*)playerMagicAddress) = value;
}

void BayoHook::SetComboPoints(int value) {
	(*(int*)comboPointsAddress) = value;
}

// dev functions
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

void BayoHook::InitializeDetours(void) {
	install_hook_absolute(0x4572BA, enemyHPHook, &EnemyHPDetour, &enemyHP_jmp_ret, 6);
	install_hook_absolute(0x9E1808, witchTimeHook, &WitchTimeMultiplierDetour, &witchTimeMultiplier_jmp_ret, 6);
	install_hook_absolute(0x8BCE4C, infMagicHook, &InfMagicDetour, &inf_magic_jmp_ret, 8);
}

void BayoHook::onConfigLoad(const utils::Config& cfg) {
	// patches
	takeNoDamage_toggle = cfg.get<bool>("TakeNoDamageToggle").value_or(false);
	TakeNoDamage(takeNoDamage_toggle);
	focusPatch_toggle = cfg.get<bool>("FocusPatchToggle").value_or(false);
	FocusPatch(focusPatch_toggle);
	infJumps_toggle = cfg.get<bool>("InfJumpsToggle").value_or(false);
	InfJumps(infJumps_toggle);
	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
};

void BayoHook::onConfigSave(utils::Config& cfg) {
	// patches
	cfg.set<bool>("TakeNoDamageToggle", takeNoDamage_toggle);
	cfg.set<bool>("FocusPatchToggle", focusPatch_toggle);
	cfg.set<bool>("InfJumpsToggle", infJumps_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);

	cfg.save("../bayo_hook.cfg");
};
