#include "GameHook.hpp"
#include <base.h> // for Data::ShowMenu

HookContext GameHook::uptimeFix;
HookContext GameHook::inputIcons;
HookContext GameHook::randomizeCostume;

// fps stuff
HookContext GameHook::turbo;
HookContext GameHook::punchBufferFrames;
HookContext GameHook::kickBufferFrames;
HookContext GameHook::dodgeBufferFrames;
HookContext GameHook::gunBufferFrames;
HookContext GameHook::controllerCameraSens;
HookContext GameHook::fpsSkateSpeed1;
HookContext GameHook::fpsSkateSpeed2;
HookContext GameHook::fixIntroMoviesTimer;

#ifndef SPEEDRUN_BUILD
HookContext GameHook::getHitbox;
HookContext GameHook::enemyHP;
HookContext GameHook::witchTimeMultiplier;
HookContext GameHook::infMagic;
HookContext GameHook::damageDealtMultiplier;
HookContext GameHook::damageReceivedMultiplier;
HookContext GameHook::customCameraDistance;
HookContext GameHook::haloDisplay;
HookContext GameHook::moveIDSwap;
HookContext GameHook::punchStringIDSwap;
HookContext GameHook::latePunchStringIDSwap;
HookContext GameHook::kickStringIDSwap;
HookContext GameHook::lateKickStringIDSwap;
HookContext GameHook::easierMash;
HookContext GameHook::initialAngelSlayerFloor;
HookContext GameHook::pvp1;
HookContext GameHook::pvp2;
HookContext GameHook::pvp3;
HookContext GameHook::pvp4;
HookContext GameHook::cameraSelect;
HookContext GameHook::customEffectColours;
HookContext GameHook::cancellableAfterBurner;
HookContext GameHook::cancellableFallingKick;
HookContext GameHook::cancellableFallingKickDurga;
HookContext GameHook::altTeleInput;
HookContext GameHook::tauntWithTimeBraceletA;
HookContext GameHook::tauntWithTimeBraceletB;
HookContext GameHook::disableSlowmo;
HookContext GameHook::lowerDivekick;
HookContext GameHook::dualAfterBurner;
HookContext GameHook::longerPillowTalkCharge;
HookContext GameHook::alwaysWitchTime;
HookContext GameHook::customWeaves;
HookContext GameHook::omnicancelTele;
HookContext GameHook::viewEntitySpawns;
HookContext GameHook::teleportComboAction;
HookContext GameHook::fixThirdAccessory;
HookContext GameHook::thirdAccessoryMenu;
// HookContext GameHook::animationScrub;
HookContext GameHook::pl0012;
HookContext GameHook::pl0031;
HookContext GameHook::pl004c;
#endif

// instead of the mindbend of figuring this out multiple times, just do it once and call refresh() on all of them every time we toggle via load, hotkey and checkbox
void GameHook::UpdateHooks() {
	GameHook::ToggleHook(GameHook::uptimeFix, GameHook::uptimeFix_toggle);
	GameHook::ToggleHook(GameHook::inputIcons, GameHook::inputIcons_toggle);
	GameHook::ToggleHook(GameHook::randomizeCostume, GameHook::randomizeCostume_toggle);

	GameHook::ToggleHook(GameHook::turbo, { GameHook::turbo_toggle, GameHook::openMenuPause_toggle });
	GameHook::ToggleHook(GameHook::punchBufferFrames, { GameHook::linkGameToDelta_toggle, GameHook::longerBufferWindows_toggle });
	GameHook::ToggleHook(GameHook::kickBufferFrames, { GameHook::linkGameToDelta_toggle, GameHook::longerBufferWindows_toggle });
	GameHook::ToggleHook(GameHook::dodgeBufferFrames, { GameHook::linkGameToDelta_toggle, GameHook::longerBufferWindows_toggle });
	GameHook::ToggleHook(GameHook::gunBufferFrames, { GameHook::linkGameToDelta_toggle, GameHook::longerBufferWindows_toggle });
	GameHook::ToggleHook(GameHook::controllerCameraSens, GameHook::linkGameToDelta_toggle);
	GameHook::ToggleHook(GameHook::fpsSkateSpeed1, GameHook::linkGameToDelta_toggle);
	GameHook::ToggleHook(GameHook::fpsSkateSpeed2, GameHook::linkGameToDelta_toggle);
	GameHook::ToggleHook(GameHook::fixIntroMoviesTimer, GameHook::linkGameToDelta_toggle);

#ifndef SPEEDRUN_BUILD
	GameHook::ToggleHook(GameHook::getHitbox, GameHook::drawHitboxes_toggle);

	GameHook::ToggleHook(GameHook::enemyHP, { GameHook::enemyHPNoDamage_toggle, GameHook::enemyHPOneHitKill_toggle });

	GameHook::ToggleHook(GameHook::witchTimeMultiplier, GameHook::witchTimeMultiplier_toggle);
	GameHook::ToggleHook(GameHook::damageDealtMultiplier, GameHook::damageDealtMultiplier_toggle);

	GameHook::ToggleHook(GameHook::damageReceivedMultiplier, {
		GameHook::damageReceivedMultiplier_toggle, 
		GameHook::damageReceivedMultiplierNoDamage_toggle
	});

	GameHook::ToggleHook(GameHook::infMagic, true); // entity spawns are done through this too so lets just leave it enabled
	GameHook::ToggleHook(GameHook::customCameraDistance, GameHook::customCameraDistance_toggle);
	GameHook::ToggleHook(GameHook::haloDisplay, GameHook::haloDisplay_toggle);

	GameHook::ToggleHook(GameHook::moveIDSwap, GameHook::moveIDSwap_toggle);
	GameHook::ToggleHook(GameHook::punchStringIDSwap, GameHook::moveIDSwap_toggle);
	GameHook::ToggleHook(GameHook::latePunchStringIDSwap, GameHook::moveIDSwap_toggle);
	GameHook::ToggleHook(GameHook::kickStringIDSwap, GameHook::moveIDSwap_toggle);
	GameHook::ToggleHook(GameHook::lateKickStringIDSwap, GameHook::moveIDSwap_toggle);

	GameHook::ToggleHook(GameHook::easierMash, GameHook::easierMash_toggle);

	GameHook::ToggleHook(GameHook::initialAngelSlayerFloor, GameHook::initialAngelSlayerFloor_value > 0);

	GameHook::ToggleHook(GameHook::pvp1, GameHook::pvp_toggle);
	GameHook::ToggleHook(GameHook::pvp2, GameHook::pvp_toggle);
	GameHook::ToggleHook(GameHook::pvp3, GameHook::pvp_toggle);
	GameHook::ToggleHook(GameHook::pvp4, GameHook::pvp_toggle);

	GameHook::ToggleHook(GameHook::cameraSelect, GameHook::cameraSelect_toggle);

	GameHook::ToggleHook(GameHook::customEffectColours, {
		GameHook::customEffectColours_toggle,
		GameHook::identifyEffects_toggle
	});

	GameHook::ToggleHook(GameHook::cancellableAfterBurner, GameHook::cancellableAfterBurner_toggle);

	GameHook::ToggleHook(GameHook::cancellableFallingKick, GameHook::cancellableFallingKick_toggle);
	GameHook::ToggleHook(GameHook::cancellableFallingKickDurga, GameHook::cancellableFallingKick_toggle);

	GameHook::ToggleHook(GameHook::altTeleInput, GameHook::altTeleInput_toggle);

	GameHook::ToggleHook(GameHook::tauntWithTimeBraceletA, {
		GameHook::altTeleInput_toggle,
		GameHook::tauntWithTimeBracelet_toggle
	});

	GameHook::ToggleHook(GameHook::tauntWithTimeBraceletB, {
		GameHook::altTeleInput_toggle,
		GameHook::tauntWithTimeBracelet_toggle
	});

	GameHook::ToggleHook(GameHook::disableSlowmo, GameHook::disableSlowmo_toggle);
	GameHook::ToggleHook(GameHook::lowerDivekick, GameHook::lowerDivekick_toggle);
	GameHook::ToggleHook(GameHook::dualAfterBurner, GameHook::dualAfterBurner_toggle);
	GameHook::ToggleHook(GameHook::longerPillowTalkCharge, GameHook::longerPillowTalkCharge_toggle);
	GameHook::ToggleHook(GameHook::alwaysWitchTime, GameHook::alwaysWitchTime_toggle);
	GameHook::ToggleHook(GameHook::customWeaves, GameHook::customWeaves_toggle);
	GameHook::ToggleHook(GameHook::omnicancelTele, GameHook::omnicancelTele_toggle);

	GameHook::ToggleHook(GameHook::viewEntitySpawns, {
		GameHook::randomizeSpawns_toggle,
		GameHook::viewEntitySpawns_toggle,
		GameHook::swapSpawns_toggle
	});

	GameHook::ToggleHook(GameHook::teleportComboAction, GameHook::teleportComboAction_toggle);
	GameHook::ToggleHook(GameHook::fixThirdAccessory, GameHook::thirdAccessoryMenu_toggle);
	GameHook::ToggleHook(GameHook::thirdAccessoryMenu, GameHook::thirdAccessoryMenu_toggle);

	GameHook::ToggleHook(GameHook::pl0012, true);
	GameHook::ToggleHook(GameHook::pl0031, true);
	GameHook::ToggleHook(GameHook::pl004c, true);
#endif
}

bool GameHook::uptimeFix_toggle = false;
static __declspec(naked) void UptimeFixDetour() {
	__asm {
		pushfd
		cmp byte ptr [GameHook::uptimeFix_toggle], 0
		je originalCode

		pushad
		call GameHook::GameTimerRebase
		popad

		originalCode:
		popfd
		sub esp, 8
		lea eax, ds:[esp]
		jmp dword ptr [GameHook::uptimeFix.jmp_ret]
	}
}

bool GameHook::longerBufferWindows_toggle = false;
static __declspec(naked) void PunchBufferFramesDetour(void) {
	_asm {
		pushfd
		// originalcode
		mov ecx, [ebx+0x0009398C]
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		je fpscode
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode

		fpscode:
		cvtsi2ss xmm1, ecx // xmm1 is about to be overwritten
		divss xmm1, [GameHook::deltaSpeed]
		cvttss2si ecx, xmm1
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode
		jmp retcode

		morecode:
		add ecx, ecx
		retcode:
		popfd
		jmp dword ptr [GameHook::punchBufferFrames.jmp_ret]
	}
}

static __declspec(naked) void KickBufferFramesDetour(void) {
	_asm {
		pushfd
		// originalcode
		mov edx, [ebx+0x00093990]
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		je fpscode
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode

		fpscode:
		cvtsi2ss xmm1, edx // xmm1 is about to be overwritten
		divss xmm1, [GameHook::deltaSpeed]
		cvttss2si edx, xmm1
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode
		jmp retcode

		morecode:
		add edx, edx
		retcode:
		popfd
		jmp dword ptr [GameHook::kickBufferFrames.jmp_ret]
	}
}

static __declspec(naked) void DodgeBufferFramesDetour(void) {
	_asm {
		pushfd
		// originalcode
		mov eax, [ebx+0x00093994]
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		je fpscode
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode

		fpscode:
		cvtsi2ss xmm1, eax // xmm1 is about to be overwritten
		divss xmm1, [GameHook::deltaSpeed]
		cvttss2si eax, xmm1
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode
		jmp retcode

		morecode:
		add eax, eax
		retcode:
		popfd
		jmp dword ptr [GameHook::dodgeBufferFrames.jmp_ret]
	}
}

static __declspec(naked) void GunBufferFramesDetour(void) {
	_asm {
		pushfd
		// originalcode
		mov ecx, [ebx+0x0009398C]
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		je fpscode
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode

		fpscode:
		cvtsi2ss xmm0, ecx // xmm0 is about to be overwritten
		divss xmm0, [GameHook::deltaSpeed]
		cvttss2si ecx, xmm0
		cmp byte ptr [GameHook::longerBufferWindows_toggle], 1
		je morecode
		jmp retcode

		morecode:
		add ecx, ecx
		retcode:
		popfd
		jmp dword ptr [GameHook::gunBufferFrames.jmp_ret]
	}
}

static __declspec(naked) void ControllerCameraSensDetour(void) {
	_asm {
		pushfd
		// originalcode
		movss xmm7, ds:[0xDA47F8] // was 0.02
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		jne retcode

		mulss xmm7, [GameHook::deltaSpeed] // mul 0.02
		mulss xmm0, [GameHook::deltaSpeed] // mul cam settings sens

		retcode:
		popfd
		jmp dword ptr [GameHook::controllerCameraSens.jmp_ret]
	}
}

static __declspec(naked) void FpsSkateSpeed1Detour(void) {
	_asm {
		pushfd
		// originalcode
		movss xmm0, ds:[0xDA81C4] // was 0.05
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		jne retcode

		mulss xmm0, [GameHook::deltaSpeed]

		retcode:
		popfd
		jmp dword ptr [GameHook::fpsSkateSpeed1.jmp_ret]
	}
}

static __declspec(naked) void FpsSkateSpeed2Detour(void) {
	_asm {
		pushfd
		// originalcode
		movss xmm0, ds:[0xDA81C4] // was 0.05
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 1
		jne retcode

		mulss xmm0, [GameHook::deltaSpeed]

		retcode:
		popfd
		jmp dword ptr [GameHook::fpsSkateSpeed2.jmp_ret]
	}
}

bool GameHook::inputIcons_toggle = false;
int GameHook::inputIconsValue = 0; // 0 keyboard, 1 gamepad
static __declspec(naked) void InputIconsDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::inputIcons_toggle], 0
		je originalcode

		mov eax, [GameHook::inputIconsValue]

		originalcode:
		popfd
		cmp dword ptr [ebx+0x000003E8], 00
		mov [ebx+0x00000CA8], eax
		jmp dword ptr [GameHook::inputIcons.jmp_ret]
	}
}

int RandomizeCostume(int currentCostume) {
	int minCostume = (currentCostume <= 14) ? 0 : 15;
	int maxCostume = (currentCostume <= 14) ? 14 : 30;
	std::uniform_int_distribution<int> dist(minCostume, maxCostume);
	return dist(GameHook::rng);
}

bool GameHook::randomizeCostume_toggle = false;
static __declspec(naked) void RandomizeCostumeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::randomizeCostume_toggle], 0
		je originalcode

		pushad
		push dword ptr ds:[0x5AA747C]
		call RandomizeCostume
		mov ds:[0x5AA747C], eax
		add esp, 4
		popad

		originalcode:
		mov eax, 00000001
		jmp dword ptr [GameHook::randomizeCostume.jmp_ret]
	}
}

bool GameHook::turbo_toggle = false;
bool GameHook::openMenuPause_toggle = false;
float GameHook::turboZero = 0.0f;
float GameHook::turboValue = 1.0f;
static __declspec(naked) void TurboHookDetour(void) {
	_asm {
		pushfd
#ifndef SPEEDRUN_BUILD
		cmp byte ptr [GameHook::openMenuPause_toggle], 1
		je zerospeed
		jmp turbocheck

		zerospeed:
		cmp byte ptr [Base::Data::ShowMenu], 0
		je turbocheck
		movss xmm0, [GameHook::turboZero]
		jmp originalcode

		turbocheck:
		cmp byte ptr [GameHook::turbo_toggle], 0
		je fpscheck
		mulss xmm0, [GameHook::turboValue]
		jmp fpscheck

		fpscheck:
#endif
		cmp byte ptr [GameHook::linkGameToDelta_toggle], 0
		je originalcode
		mulss xmm0, [GameHook::deltaSpeed]
		jmp originalcode

		//popcode:
		//pop eax
		originalcode:
		popfd
		movss [edi+0x44], xmm0
		jmp dword ptr [GameHook::turbo.jmp_ret]
	}
}

// Bayonetta.exe + 1A1DE5 - 01 5E 20 - add[esi + 20], ebx
// Bayonetta.exe+1A1DE8 - 81 7E 20 66 03 00 00 - cmp[esi+20],00000366 { 870 }
// Intro Movies Timer - scales the increment with deltaSpeed so the timer doesn't run too fast at higher framerates
static float introTimerAccumulator = 0.0f;

static int __stdcall GetFramerateCorrectedIncrement(
    float* accumulator,
    int originalIncrement)
{
    *accumulator += originalIncrement * GameHook::deltaSpeed;

    int increment = (int)(*accumulator);

    *accumulator -= increment;

    return increment;
}

static __declspec(naked) void FixIntroMoviesTimerDetour(void) {
	_asm {
		push eax
		push ecx
		push edx

		push ebx                               // originalIncrement (2nd arg, pushed first)
		push offset introTimerAccumulator      // accumulator ptr   (1st arg, pushed last)
		call GetFramerateCorrectedIncrement
		// __stdcall: ret 8 cleans both args

		pop edx
		pop ecx

		mov ebx, eax // store the corrected increment in ebx for the original code to use
		pop eax

		// original instructions
		add [esi + 0x20], ebx
		cmp dword ptr [esi + 0x20], 870
		jmp dword ptr [GameHook::fixIntroMoviesTimer.jmp_ret]
	}
}

#ifndef SPEEDRUN_BUILD
#include <mutex>
static std::mutex g_EffectIDsMutex;
std::vector<int> GameHook::seenEffectIDs;
static void RegisterEffectID(int id) {
	std::lock_guard<std::mutex> lock(g_EffectIDsMutex);
	if (std::find(GameHook::seenEffectIDs.begin(), GameHook::seenEffectIDs.end(), id) == GameHook::seenEffectIDs.end()) {
		GameHook::seenEffectIDs.push_back(id);
	}
}

static ImColor* GetAppropriateEffectColour(int id) {
#if 0
	switch (id)
	{
	case 0x1e: // attack streaks
		return &GameHook::effectCol[0];
	case 0x6: // streaks that follow the char when you attack
	    return &GameHook::effectCol[1];
	}
#endif
	if (GameHook::customEffectColoursRestrictionID == -1) {
		return &GameHook::effectCol[0];
	}
	if (id == GameHook::customEffectColoursRestrictionID) {
		return &GameHook::effectCol[0];
	}
	return nullptr;
}

bool GameHook::identifyEffects_toggle = false;
bool GameHook::customEffectColours_toggle = false;
ImColor GameHook::effectCol[10]{ ImColor(0.0f, 0.6f, 1.0f, 1.0f), ImColor(1.0f, 1.0f, 1.0f, 1.0f) };
int GameHook::customEffectColoursRestrictionID = 0x1e;
static __declspec(naked) void CustomEffectColoursDetour() {
	_asm {
		cmp byte ptr [GameHook::identifyEffects_toggle], 0
		je applyeffects

		pushad
		push edx
		call RegisterEffectID
		add esp, 4
		popad

		applyeffects:
		cmp byte ptr [GameHook::customEffectColours_toggle], 0
		je original_code
		pushad
		push edx
		call GetAppropriateEffectColour
		add esp, 4
		test eax, eax
		jz no_custom_colour
		mov ecx, dword ptr [eax]
		mov dword ptr [esi+0x318], ecx
		mov ecx, dword ptr [eax+0x4]
		mov dword ptr [esi+0x31C], ecx
		mov ecx, dword ptr [eax+0x8]
		mov dword ptr [esi+0x320], ecx
		mov ecx, dword ptr [eax+0xC]
		mov dword ptr [esi+0x324], ecx
		popad
		jmp dword ptr [GameHook::customEffectColours.jmp_ret]

	no_custom_colour:
		popad

	original_code:
		mov eax, dword ptr [edi+0xC8]
		mov dword ptr [esi+0x318], eax
		mov eax, dword ptr [edi+0xCC]
		mov dword ptr [esi+0x31C], eax
		mov eax, dword ptr [edi+0xD0]
		mov dword ptr [esi+0x320], eax
		mov eax, dword ptr [edi+0xD4]
		mov dword ptr [esi+0x324], eax
		jmp dword ptr [GameHook::customEffectColours.jmp_ret]
	}
}

#if 0
float GameHook::currentAnimationScrub = 0.0f;
float GameHook::currentAnimationEndFrame = 0.0f;
static __declspec(naked) void AnimationScrubDetour(void) {
	_asm {
		cmp byte ptr [GameHook::animationScrub_toggle], 0
		je originalcode

		// only edit player anim frame
		push eax
		push ebx
		mov eax, 0xEF5A60
		mov eax, [eax]
		lea ebx,[esi-0x3d0]
		cmp ebx, eax
		pop ebx
		pop eax
		jne originalcode

		movss xmm1, [esi+0x54]
		movss [GameHook::currentAnimationEndFrame], xmm1
		xorps xmm1, xmm1 // leave xmm1 in the state we found it
		movss xmm0, [GameHook::currentAnimationScrub]
		jmp contcode

		originalcode:
		addss xmm0, xmm3
		contcode:
		movss [esi+0x14], xmm0
		jmp dword ptr [GameHook::animationScrub.jmp_ret]
	}
}
#endif

int GameHook::atkTest = -1;
int GameHook::atkTestReplacement = 0;
static int GetPvpReaction(int atkType) {
	if (atkType == GameHook::atkTest) {
		return GameHook::atkTestReplacement;
	}
	switch (atkType) {
	// HEAVY
	case ATHIT_TYPE_PL_BLOWPUNCH:
	case ATHIT_TYPE_PL_BLOWPUNCH2:
	case ATHIT_TYPE_PL_BLOWKICK:
	case ATHIT_TYPE_PL_BLOWKICK2:
	case ATHIT_TYPE_PL_S_BLOWKICK:
	case ATHIT_TYPE_PL_BIGFALLKICK:
	case ATHIT_TYPE_PL_BLOWBLADE:
	case ATHIT_TYPE_PL_CLAWCOMBO_FINISH:
	case ATHIT_TYPE_PL_F_CLAW_KICK_BIG:
	case ATHIT_TYPE_PL_F_CLAW_BLOWKICK:
	case ATHIT_TYPE_PL_F_CLAW_BIGFALLKICK:
	case ATHIT_TYPE_PL_E_CLAW_KICK_BIG:
	case ATHIT_TYPE_PL_E_CLAW_BLOWKICK:
	case ATHIT_TYPE_PL_E_CLAW_BIGFALLKICK:
	case ATHIT_TYPE_PL_SKATES_KICK_BIG:
	case ATHIT_TYPE_PL_SKATES_BLOWKICK:
	case ATHIT_TYPE_PL_SKATES_BIGFALLKICK:
	case ATHIT_TYPE_PL_EM_BLOW:
	case ATHIT_TYPE_PL_EM_BIGBLOW:
	case ATHIT_TYPE_PL_BIGLANDING:
	case ATHIT_TYPE_PL_BIGFALL:
	case ATHIT_TYPE_PL_GW_THROW:
	case ATHIT_TYPE_PL_THROWED_CAR:
	case ATHIT_TYPE_PL_ROCK:
	case ATHIT_TYPE_PL_BIKE:
	case ATHIT_TYPE_PL_DEVIL_BLADESTAMP:
	case ATHIT_TYPE_PL_DEVIL_FIRE_CLAWSTAMP:
	case ATHIT_TYPE_PL_DEVIL_ELEC_CLAWSTAMP:
	case ATHIT_TYPE_PL_DEVIL_ICE_STAMP:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADESTAMP:
	case ATHIT_TYPE_PL_STAMPKICK:
	case ATHIT_TYPE_PL_FALLKICK:
	case ATHIT_TYPE_PL_STAMPBLADE:
	case ATHIT_TYPE_PL_STAMPBLADE_F:
	case ATHIT_TYPE_PL_LB_STAMPBLADE:
	case ATHIT_TYPE_PL_LB_STAMPBLADE_F:
	case ATHIT_TYPE_PL_F_CLAW_STAMP:
	case ATHIT_TYPE_PL_F_CLAW_FALLKICK:
	case ATHIT_TYPE_PL_E_CLAW_STAMP:
	case ATHIT_TYPE_PL_E_CLAW_FALLKICK:
	case ATHIT_TYPE_PL_NUNCHUKSTAMP:
	case ATHIT_TYPE_PL_TRUMPET:
	case ATHIT_TYPE_PL_S_TRUMPET:
	case ATHIT_TYPE_PL_HORN:
	case ATHIT_TYPE_PL_S_HORN:
	case ATHIT_TYPE_PL_DEVIL_PUNCH:
	case ATHIT_TYPE_PL_DEVIL_KICK:
	case ATHIT_TYPE_PL_DEVIL_STAMP:
		return PVP_HEAVY;

	// LAUNCHER
	case ATHIT_TYPE_PL_UPPER:
	case ATHIT_TYPE_PL_KICKUPPER:
	case ATHIT_TYPE_PL_UPPERBLADE:
	case ATHIT_TYPE_PL_AIRUPPERBLADE:
	case ATHIT_TYPE_PL_LB_UPPERBLADE:
	case ATHIT_TYPE_PL_LB_AIRUPPERBLADE:
	case ATHIT_TYPE_PL_WHIPUPPER:
	case ATHIT_TYPE_PL_UPPERCLAW:
	case ATHIT_TYPE_PL_F_CLAW_KICKUPPER:
	case ATHIT_TYPE_PL_ELEC_UPPERCLAW:
	case ATHIT_TYPE_PL_E_CLAW_KICKUPPER:
	case ATHIT_TYPE_PL_UPPERTONFA:
	case ATHIT_TYPE_PL_SKATES_KICKUPPER:
	case ATHIT_TYPE_PL_NUNCHUK_UPPER:
	case ATHIT_TYPE_PL_GW_BOWBLADEUPPER:
	case ATHIT_TYPE_PL_DEVIL_UPPER:
	case ATHIT_TYPE_PL_DEVIL_BLADEUPPER:
	case ATHIT_TYPE_PL_DEVIL_FIRE_CLAWUPPER:
	case ATHIT_TYPE_PL_DEVIL_ELEC_CLAWUPPER:
	case ATHIT_TYPE_PL_DEVIL_ICE_UPPER:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADEUPPER:
		return PVP_LAUNCHER;

	// BLUE ELECTRIC NORMAL
	case ATHIT_TYPE_PL_CLAWELECBOMB:
	case ATHIT_TYPE_PL_ELEC_CLAW1:
	case ATHIT_TYPE_PL_ELEC_CLAW2:
	case ATHIT_TYPE_PL_ELEC_CLAW3:
	case ATHIT_TYPE_PL_ELEC_CLAW4:
	case ATHIT_TYPE_PL_ELEC_DASHCLAW:
	case ATHIT_TYPE_PL_ELEC_CLAWKICK1:
	case ATHIT_TYPE_PL_ELEC_CLAWKICK2:
	case ATHIT_TYPE_PL_ELEC_CLAWKICK3:
	case ATHIT_TYPE_PL_ELEC_CHANGECLAW:
	case ATHIT_TYPE_PL_ELEC_SPINKICKCLAW:
	case ATHIT_TYPE_PL_ELEC_SPINPUNCHCLAW:
	case ATHIT_TYPE_PL_ELEC_CLAWCOMBO:
	case ATHIT_TYPE_PL_VARIANT_CLAW_ELEC:
	case ATHIT_TYPE_PL_GW_CLAW_ELEC:
	case ATHIT_TYPE_PL_DEVIL_ELEC_CLAW:
	case ATHIT_TYPE_PL_DEVIL_ELEC_CLAW_RU:
	case ATHIT_TYPE_PL_DEVIL_ELEC_CLAW_LU:
	case ATHIT_TYPE_PL_DEVIL_ELEC_MDL_CLAW:
		return PVP_BLUE_ELECTRIC_NORMAL;

	// BLUE ELECTRIC AIR
	case ATHIT_TYPE_PL_ELEC_AIRCLAW1:
	case ATHIT_TYPE_PL_ELEC_AIRCLAW2:
	case ATHIT_TYPE_PL_ELEC_AIRCLAW3:
	case ATHIT_TYPE_PL_ELEC_AIRCLAW4:
		return PVP_BLUE_ELECTRIC_AIR;

	// YELLOW ELECTRIC
	case ATHIT_TYPE_PL_KAMEHAMEHA:
	case ATHIT_TYPE_PL_LASER_BEAM:
	case ATHIT_TYPE_PL_NUNCHUK_BEAM:
		return PVP_YELLOW_ELECTRIC;

		// LIGHT
	case ATHIT_TYPE_PL_HANDGUN:
	case ATHIT_TYPE_PL_HANDGUN_SML:
	case ATHIT_TYPE_PL_S_HANDGUN:
	case ATHIT_TYPE_PL_M_HANDGUN:
	case ATHIT_TYPE_PL_HANDGUN_REFLECT:
	case ATHIT_TYPE_PL_SHOTGUN_SML:
	case ATHIT_TYPE_PL_SHOOTING_HANDGUN:
	case ATHIT_TYPE_PL_STAMP: // falling
	case ATHIT_TYPE_PL_NUNCHUK_BEAM_SML:
	case ATHIT_TYPE_PL_VARIANT_ARROW:
	case ATHIT_TYPE_PL_VARIANT_TRUMPET:
	case ATHIT_TYPE_PL_VARIANT_S_TRUMPET:
	case ATHIT_TYPE_PL_LASER_SHOT:
	case ATHIT_TYPE_PL_LASER_FOOTSHOT:
	case ATHIT_TYPE_PL_LASER_S_BEAM:
	case ATHIT_TYPE_PL_GW_ARROW:
	case ATHIT_TYPE_PL_FIREBALL:
	case ATHIT_TYPE_PL_KISSMARK:
	case ATHIT_TYPE_PL_MACHINEGUN:
		//return PVP_LIGHT; // not usable on anything fast, the stun is so quick and you can be hit immediately after
							// so lets roll this into normal

	// NORMAL
	case ATHIT_TYPE_PL_SHOTGUN:
	case ATHIT_TYPE_PL_S_SHOTGUN:
	case ATHIT_TYPE_PL_TONFA_ROCKET:
	case ATHIT_TYPE_PL_TONFA_G_ROCKET:
	case ATHIT_TYPE_PL_PUNCH:
	case ATHIT_TYPE_PL_PUNCH2:
	case ATHIT_TYPE_PL_DASHPUNCH:
	case ATHIT_TYPE_PL_SPINPUNCH:
	case ATHIT_TYPE_PL_COMBOATK:
	case ATHIT_TYPE_PL_COMBOATK_E:
	case ATHIT_TYPE_PL_100PUNCH:
	case ATHIT_TYPE_PL_100PUNCH_E:
	case ATHIT_TYPE_PL_KICK:
	case ATHIT_TYPE_PL_KICK2:
	case ATHIT_TYPE_PL_JUMPKICKUPPER:
	case ATHIT_TYPE_PL_DASHKICK:
	case ATHIT_TYPE_PL_SPINKICK:
	case ATHIT_TYPE_PL_JUMPKICK:
	case ATHIT_TYPE_PL_100KICK:
	case ATHIT_TYPE_PL_100KICK_E:
	case ATHIT_TYPE_PL_HEELKICK:
	case ATHIT_TYPE_PL_LOWSPINKICK_L:
	case ATHIT_TYPE_PL_LOWSPINKICK_R:
	case ATHIT_TYPE_PL_AIRSPINKICK_L:
	case ATHIT_TYPE_PL_AIRSPINKICK_R:
	case ATHIT_TYPE_PL_LOWSPINKICK_L_E:
	case ATHIT_TYPE_PL_LOWSPINKICK_R_E:
	case ATHIT_TYPE_PL_AIRSPINKICK_L_E:
	case ATHIT_TYPE_PL_AIRSPINKICK_R_E:
	case ATHIT_TYPE_PL_BLADE1:
	case ATHIT_TYPE_PL_BLADE2:
	case ATHIT_TYPE_PL_BLADE3:
	case ATHIT_TYPE_PL_BLADE4:
	case ATHIT_TYPE_PL_BLADE_AIR1:
	case ATHIT_TYPE_PL_BLADE_AIR2:
	case ATHIT_TYPE_PL_BLADE_AIR3:
	case ATHIT_TYPE_PL_BLADE_AIR4:
	case ATHIT_TYPE_PL_DELAYBLADE_A1:
	case ATHIT_TYPE_PL_DELAYBLADE_A2:
	case ATHIT_TYPE_PL_DELAYBLADE_A3:
	case ATHIT_TYPE_PL_DELAYBLADE_B1:
	case ATHIT_TYPE_PL_DELAYBLADE_B2:
	case ATHIT_TYPE_PL_DELAYBLADE_B3:
	case ATHIT_TYPE_PL_DELAYBLADE_C:
	case ATHIT_TYPE_PL_BLADE:
	case ATHIT_TYPE_PL_BLADE_SIDE:
	case ATHIT_TYPE_PL_BLADE_IAI:
	case ATHIT_TYPE_PL_BLADE_IAI_MAX:
	case ATHIT_TYPE_PL_COMBOBLADE:
	case ATHIT_TYPE_PL_COMBOBLADE_SIDE:
	case ATHIT_TYPE_PL_COMBOBLADE_E:
	case ATHIT_TYPE_PL_DASHBLADE:
	case ATHIT_TYPE_PL_SPINPBLADE:
	case ATHIT_TYPE_PL_SPINPBLADE2:
	case ATHIT_TYPE_PL_SPINPBLADE3:
	case ATHIT_TYPE_PL_BLADEWAVE:
	case ATHIT_TYPE_PL_BLADEWAVE_MAX:
	case ATHIT_TYPE_PL_LB_BLADE1:
	case ATHIT_TYPE_PL_LB_BLADE2:
	case ATHIT_TYPE_PL_LB_BLADE3:
	case ATHIT_TYPE_PL_LB_BLADE4:
	case ATHIT_TYPE_PL_LB_BLADE_AIR1:
	case ATHIT_TYPE_PL_LB_BLADE_AIR2:
	case ATHIT_TYPE_PL_LB_BLADE_AIR3:
	case ATHIT_TYPE_PL_LB_BLADE_AIR4:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_A1:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_A2:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_A3:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_B1:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_B2:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_B3:
	case ATHIT_TYPE_PL_LB_DELAYBLADE_C:
	case ATHIT_TYPE_PL_LB_BLADE:
	case ATHIT_TYPE_PL_LB_BLADE_SIDE:
	case ATHIT_TYPE_PL_LB_BLADE_IAI:
	case ATHIT_TYPE_PL_LB_BLADE_IAI_MAX:
	case ATHIT_TYPE_PL_LB_COMBOBLADE:
	case ATHIT_TYPE_PL_LB_COMBOBLADE_SIDE:
	case ATHIT_TYPE_PL_LB_COMBOBLADE_E:
	case ATHIT_TYPE_PL_LB_DASHBLADE:
	case ATHIT_TYPE_PL_LB_SPINPBLADE:
	case ATHIT_TYPE_PL_LB_SPINPBLADE2:
	case ATHIT_TYPE_PL_LB_SPINPBLADE3:
	case ATHIT_TYPE_PL_LB_BLOWBLADE:
	case ATHIT_TYPE_PL_LB_BLADEWAVE:
	case ATHIT_TYPE_PL_LB_BLADEWAVE_MAX:
	case ATHIT_TYPE_PL_WHIP:
	case ATHIT_TYPE_PL_WHIPSPIN:
	case ATHIT_TYPE_PL_CLAW1:
	case ATHIT_TYPE_PL_CLAW2:
	case ATHIT_TYPE_PL_CLAW3:
	case ATHIT_TYPE_PL_AIRCLAW1:
	case ATHIT_TYPE_PL_AIRCLAW2:
	case ATHIT_TYPE_PL_AIRCLAW3:
	case ATHIT_TYPE_PL_DASHCLAW:
	case ATHIT_TYPE_PL_CLAWFIREBOMB_LV1:
	case ATHIT_TYPE_PL_CLAWFIREBOMB_LV2:
	case ATHIT_TYPE_PL_CLAWFIREBOMB_LV3:
	case ATHIT_TYPE_PL_CLAWKICK1:
	case ATHIT_TYPE_PL_CLAWKICK2:
	case ATHIT_TYPE_PL_CLAWKICK3:
	case ATHIT_TYPE_PL_CHANGECLAW:
	case ATHIT_TYPE_PL_SPINKICKCLAW:
	case ATHIT_TYPE_PL_SPINPUNCHCLAW:
	case ATHIT_TYPE_PL_CLAWCOMBO:
	case ATHIT_TYPE_PL_F_CLAW_100KICK_E:
	case ATHIT_TYPE_PL_F_CLAW_HEELKICK:
	case ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_L:
	case ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_R:
	case ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_L:
	case ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_R:
	case ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_L_E:
	case ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_R_E:
	case ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_L_E:
	case ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_R_E:
	case ATHIT_TYPE_PL_TONFA1:
	case ATHIT_TYPE_PL_TONFA2:
	case ATHIT_TYPE_PL_TONFA3:
	case ATHIT_TYPE_PL_DASHTONFA:
	case ATHIT_TYPE_PL_DASHTONFA_E:
	case ATHIT_TYPE_PL_TONFAKICK:
	case ATHIT_TYPE_PL_TONFASPIN:
	case ATHIT_TYPE_PL_SKATES_KICK1:
	case ATHIT_TYPE_PL_SKATES_KICK2:
	case ATHIT_TYPE_PL_SKATES_KICK3:
	case ATHIT_TYPE_PL_SKATES_KICK4:
	case ATHIT_TYPE_PL_SKATES_100:
	case ATHIT_TYPE_PL_SKATES_100KICK_E:
	case ATHIT_TYPE_PL_SKATES_HEELKICK:
	case ATHIT_TYPE_PL_SKATES_LOWSPINKICK_L:
	case ATHIT_TYPE_PL_SKATES_LOWSPINKICK_R:
	case ATHIT_TYPE_PL_SKATES_AIRSPINKICK_L:
	case ATHIT_TYPE_PL_SKATES_AIRSPINKICK_R:
	case ATHIT_TYPE_PL_SKATES_LOWSPINKICK_L_E:
	case ATHIT_TYPE_PL_SKATES_LOWSPINKICK_R_E:
	case ATHIT_TYPE_PL_SKATES_AIRSPINKICK_L_E:
	case ATHIT_TYPE_PL_SKATES_AIRSPINKICK_R_E:
	case ATHIT_TYPE_PL_NUNCHUK1:
	case ATHIT_TYPE_PL_NUNCHUK_CHOP:
	case ATHIT_TYPE_PL_GW_BLADE:
	case ATHIT_TYPE_PL_GW_BLADE_SIDE:
	case ATHIT_TYPE_PL_GW_DASHBLADE:
	case ATHIT_TYPE_PL_GW_AXE:
	case ATHIT_TYPE_PL_GW_AXE_SIDE:
	case ATHIT_TYPE_PL_GW_CLAW:
	case ATHIT_TYPE_PL_GW_CLAW_SIDE:
	case ATHIT_TYPE_PL_GW_CLAW_FIRESPIN:
	case ATHIT_TYPE_PL_GW_MSTAR:
	case ATHIT_TYPE_PL_GW_MSTAR_MDL:
	case ATHIT_TYPE_PL_GW_MSTAR_BIG:
	case ATHIT_TYPE_PL_GW_BOWBLADE1:
	case ATHIT_TYPE_PL_GW_BOWBLADE2:
	case ATHIT_TYPE_PL_GW_BOWBLADE3:
	case ATHIT_TYPE_PL_GW_BOWBLADE_FIN:
	case ATHIT_TYPE_PL_GW_LAMPPOST1:
	case ATHIT_TYPE_PL_GW_LAMPPOST2:
	case ATHIT_TYPE_PL_GW_LAMPPOST3:
	case ATHIT_TYPE_PL_GW_POLESPINKICK:
	case ATHIT_TYPE_PL_GW_CHAINSAW1:
	case ATHIT_TYPE_PL_GW_CHAINSAW2:
	case ATHIT_TYPE_PL_GW_CHAINSAW3:
	case ATHIT_TYPE_PL_GW_CHAINSAW:
	case ATHIT_TYPE_PL_GW_CHAINSAW_SIDE:
	case ATHIT_TYPE_PL_CROW_WING:
	case ATHIT_TYPE_PL_GUARDIAN_BLOOD:
	case ATHIT_TYPE_PL_PANTHERDASH:
	case ATHIT_TYPE_PL_PANTHERCHARGE:
	case ATHIT_TYPE_PL_SLAP:
	case ATHIT_TYPE_PL_SLAP_E:
	case ATHIT_TYPE_PL_LAVA:
	case ATHIT_TYPE_PL_DMG_COUNTER:
	case ATHIT_TYPE_PL_DEVIL_MDL_PUNCH:
	case ATHIT_TYPE_PL_DEVIL_MDL_KICK:
	case ATHIT_TYPE_PL_DEVIL_BLADE:
	case ATHIT_TYPE_PL_DEVIL_BLADE_R:
	case ATHIT_TYPE_PL_DEVIL_BLADE_RU:
	case ATHIT_TYPE_PL_DEVIL_BLADE_LU:
	case ATHIT_TYPE_PL_DEVIL_BLADESTING:
	case ATHIT_TYPE_PL_DEVIL_BLADECHOP:
	case ATHIT_TYPE_PL_DEVIL_MDL_WHIP:
	case ATHIT_TYPE_PL_DEVIL_WHIP:
	case ATHIT_TYPE_PL_DEVIL_FIRE_CLAW:
	case ATHIT_TYPE_PL_DEVIL_FIRE_CLAW_RU:
	case ATHIT_TYPE_PL_DEVIL_FIRE_CLAW_LU:
	case ATHIT_TYPE_PL_DEVIL_FIRE_MDL_CLAW:
	case ATHIT_TYPE_PL_DEVIL_ICE_KICK:
	case ATHIT_TYPE_PL_DEVIL_ICE_MDL_KICK:
	case ATHIT_TYPE_PL_DEVIL_ICE_MINI_KICK:
	case ATHIT_TYPE_PL_DEVIL_MINI_PUNCH:
	case ATHIT_TYPE_PL_DEVIL_MINI_KICK:
	case ATHIT_TYPE_PL_DEVIL_ROCKETPUNCH:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADE_L:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADE_R:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADE_RU:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADE_LU:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADESTING:
	case ATHIT_TYPE_PL_DEVIL_MINI_BLADECHOP:
	case ATHIT_TYPE_PL_SHOOTING_DEVILPUNCH:
	case ATHIT_TYPE_PL_HIGHWAYBIKE:
	case ATHIT_TYPE_PL_ITEMBOMB:
	case ATHIT_TYPE_PL_BIKESLIDING:
	case ATHIT_TYPE_PL_BIKERUN:
	case ATHIT_TYPE_PL_BONUS_GAME:
		return PVP_NORMAL;

	default:
		return PVP_NORMAL;
	}
}

// change players to be able to damage both players and enemies via forcing enum ATHIT_TARGET to ATHIT_TARGET_PLEM
// you could also just patch the push @ 009D13EF
bool GameHook::pvp_toggle = false;
static __declspec(naked) void PvpDetour1(void) {
	_asm {
		cmp byte ptr [GameHook::pvp_toggle], 0
		je originalcode
		jmp newcode
#if 0
	// this was only true for a frame and its called like 10 times lmao
	// checkplayer1:
		push ebx
		mov ebx, [GameHook::player1PointerAddress]
		mov ebx, [ebx]
		cmp eax, ebx
		pop ebx
		je isplayer1
		jmp checkplayer2

	isplayer1:
		push ebx
		mov ebx, [GameHook::player2PointerAddress]
		mov ebx, [ebx]
		cmp ebx, [esi+0x28]
		pop ebx
		je newcode
		jmp originalcode

	checkplayer2:
		push ebx
		mov ebx, [GameHook::player2PointerAddress]
		mov ebx, [ebx]
		cmp eax, ebx
		pop ebx
		je isplayer2
		jmp originalcode

	isplayer2:
		push ebx
		mov ebx, [GameHook::player1PointerAddress]
		mov ebx, [ebx]
		cmp ebx, [esi+0x28]
		pop ebx
		je newcode
		jmp originalcode
#endif
	newcode:
		mov eax, 4 // ATHIT_TARGET_PLEM
		jmp cont

	originalcode:
		mov eax, [esi+0x10]
	cont:
		cmp eax, 4
		jmp dword ptr [GameHook::pvp1.jmp_ret]
	}
}

int GameHook::lastSeenAtk = 0;
int GameHook::lastSeenAtkConverted = 0;
bool GameHook::pvpDamageRemaps_toggle = true;
// change damage reactions for pvp
static __declspec(naked) void PvpDetour2(void) { // func is only called when a player is hit
	_asm { // p2 hit = p2 in edi+60, esi, 
		// ebx+28 = attacker
		// originalcode
		pushfd
		mov eax, [edi+0x14]
		mov [GameHook::lastSeenAtk], eax

		cmp byte ptr [GameHook::pvp_toggle], 0
		je cont

		push eax // check p2 exists in case pvp is enabled pointlessly
		mov eax, [GameHook::player2PointerAddress]
		mov eax, [eax]
		test eax, eax
		pop eax
		je cont

		push eax
		mov eax, [GameHook::player1PointerAddress]
		mov eax, [eax]
		cmp eax, [ebx+0x28]
		pop eax
		je pvpcode
		jmp checkplayer2

		checkplayer2:
		push eax
		mov eax, [GameHook::player2PointerAddress]
		mov eax, [eax]
		cmp eax, [ebx+0x28]
		pop eax
		je pvpcode
		jmp cont
		
		pvpcode:
		cmp byte ptr [GameHook::pvpDamageRemaps_toggle], 0
		je simpleSwap
		push eax
		call GetPvpReaction
		add esp, 4 // keep new eax
		jmp retcode

		simpleSwap:
		sub eax, 8
		jmp retcode

		cont:
		add eax, 0xFFFFFEB5 // 0x14b
		retcode:
		popfd
		jmp dword ptr [GameHook::pvp2.jmp_ret]
	}
}

static constexpr uintptr_t pvp_jmp_out3 = 0x49A65B;
// exclude locking on to self with lock on
static __declspec(naked) void PvpDetour3(void) {
	_asm {
		pushfd // add 4 to esp
		cmp byte ptr [GameHook::pvp_toggle], 0
		je originalcode

		cmp ecx, [esp+0x8] // exclude self
		je jmpout

		originalcode:
		mov edx, [ecx+0x00000378]
		// retcode:
		popfd
		jmp dword ptr [GameHook::pvp3.jmp_ret]

		jmpout:
		popfd
		jmp dword ptr [pvp_jmp_out3]
	}
}

static constexpr uintptr_t pvp_jmp_out4 = 0x49A998;
// exclude locking on to self with movement or attacks
static __declspec(naked) void PvpDetour4(void) {
	_asm {
		pushfd // add 4 to esp
		cmp byte ptr [GameHook::pvp_toggle], 0
		je originalcode

		cmp ecx, [esp+0x8] // exclude self
		je jmpout

		originalcode:
		mov edx, [ecx+0x00000378]
		// retcode:
		popfd
		jmp dword ptr [GameHook::pvp4.jmp_ret]

		jmpout:
		popfd
		jmp dword ptr [pvp_jmp_out4]
	}
}

bool GameHook::cameraSelect_toggle = false;
int GameHook::cameraSelect_newCameraType = 0;
// exclude locking on to self with movement or attacks
static __declspec(naked) void CameraSelectDetour(void) {
	_asm {
		pushfd // add 4 to esp
		cmp byte ptr [GameHook::cameraSelect_toggle], 0
		je originalcode

		mov eax, [GameHook::cameraSelect_newCameraType]
		jmp retcode

		originalcode:
		mov eax, [ebx+0x00000CF0]
		retcode:
		popfd
		jmp dword ptr [GameHook::cameraSelect.jmp_ret]
	}
}

int GameHook::initialAngelSlayerFloor_value = 0;
static __declspec(naked) void InitialAngelSlayerFloorDetour(void) {
	_asm {
		push eax
		push esi
		mov eax, [GameHook::angelSlayerFloorAddress]
		mov esi, [GameHook::initialAngelSlayerFloor_value]
		mov [eax], esi
		pop esi
		pop eax
		jmp dword ptr[GameHook::initialAngelSlayerFloor.jmp_ret]
	}
}


std::vector<HitboxSnapshot> GameHook::hitDataList;
static void AddHitDataPtr(void* ptr) {
	auto* hitData = (hitbox*)(ptr);
	GameHook::hitDataList.push_back({ hitData->pos, hitData->scale });
}

static __declspec(naked) void GetHitboxDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::drawHitboxes_toggle], 0
		je originalcode

		sub esp, 4
		movss [esp], xmm0 // backup xmm0
		pushad
		add ebx, 0xD0 // old offset was +0x30
		push ebx
		call AddHitDataPtr
		add esp, 4
		popad
		add esp, 4
		movss xmm0, [esp] // restore xmm0
		originalcode:
		popfd
		addss xmm0, [ebx+0x00000100]
		jmp dword ptr [GameHook::getHitbox.jmp_ret]
	}
}

bool GameHook::enemyHPNoDamage_toggle = false;
bool GameHook::enemyHPOneHitKill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::enemyHPOneHitKill_toggle], 1
		je one_hit_kill
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::enemyHPNoDamage_toggle], 1
		je no_damage
		jmp originalcode

		no_damage:
		jmp retcode

		one_hit_kill:
		mov dword ptr [esi+0x000006B4], 0
		jmp retcode

		originalcode:
		mov [esi+0x000006B4], eax
		retcode:
		popfd
		jmp dword ptr [GameHook::enemyHP.jmp_ret]
		// this hides test eax,eax in CE but it is still there
	}
}

bool GameHook::witchTimeMultiplier_toggle = false;
float GameHook::witchTimeMultiplier_value = 1.0f;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fmul dword ptr [esi+0x00095D68] // might be game speed or something? 1 by default
		fdiv dword ptr [GameHook::witchTimeMultiplier_value]
		jmp retcode

		originalcode:
		fmul dword ptr [esi+0x00095D68]
		retcode:
		popfd
		jmp dword ptr [GameHook::witchTimeMultiplier.jmp_ret]
	}
}

void GameHook::CallFromGameThread() {
	if (GameHook::spawnEntityFromGui) {
		GameHook::spawnEntityFromGui = false;
		GameHook::SpawnEntity(guiEntitySpawn);
	}
	if (GameHook::spawnEntityFromHotkey) {
		GameHook::spawnEntityFromHotkey = false;
		GameHook::SpawnEntity(hotkeyEntitySpawn);
	}
}

bool GameHook::infMagic_toggle = false;
float GameHook::infMagic_value = 1200.0f;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		pushfd
		pushad
		call GameHook::CallFromGameThread
		popad

		push eax
		mov eax, [GameHook::playerMagicAddress]
		cmp byte ptr [GameHook::infMagic_toggle], 0
		je originalcode

		movss xmm0, [GameHook::infMagic_value]
		movss [eax], xmm0

		originalcode:
		movss xmm0, [eax]
		pop eax
		popfd
		jmp dword ptr [GameHook::infMagic.jmp_ret]
	}
}

bool GameHook::damageDealtMultiplier_toggle = false;
float GameHook::damageDealtMultiplierMult = 1.0f;
static __declspec(naked) void DamageDealtMultiplierDetour(void) {
	_asm {
		pushfd
		mov [esi+0x000006B8], eax // originalcode, early bytes to avoid EnemyHPDetour
		cmp byte ptr [GameHook::damageDealtMultiplier_toggle], 0
		je originalcode

		sub esp, 4
		movss [esp], xmm0 // backup xmm0
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [GameHook::damageDealtMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0, [esp] // restore xmm0
		add esp, 4

		originalcode:
		sub eax, edi
		mov [GameHook::haloDisplayValue], eax // after damage subtraction
		popfd
		jmp dword ptr [GameHook::damageDealtMultiplier.jmp_ret]
	}
}

bool GameHook::damageReceivedMultiplierNoDamage_toggle = false;
bool GameHook::damageReceivedMultiplier_toggle = false;
float GameHook::incoming_damage_mult = 1.0f;
static __declspec(naked) void DamageReceivedMultiplierDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::damageReceivedMultiplierNoDamage_toggle], 1
		je no_damage
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::damageReceivedMultiplier_toggle], 1
		je damage_mult
		jmp originalcode

		no_damage:
		jmp retcode

		damage_mult:
		sub esp, 4
		movss [esp], xmm0 // backup xmm0
		movd xmm0, ecx
		cvtdq2ps xmm0, xmm0
		mulss xmm0, [GameHook::incoming_damage_mult]
		cvttss2si ecx, xmm0
		movss xmm0, [esp] // restore xmm0
		add esp, 4

		originalcode:
		sub eax, ecx
		mov [esi+0x00093508], eax
		retcode:
		popfd
		jmp dword ptr [GameHook::damageReceivedMultiplier.jmp_ret]
	}
}

bool GameHook::customCameraDistance_toggle = false;
float GameHook::customCameraDistance_value = 10.0f;
static __declspec(naked) void CustomCameraDistanceDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::customCameraDistance_toggle], 0
		je originalcode

		fld dword ptr [GameHook::customCameraDistance_value]
		jmp retcode

		originalcode:
		fld dword ptr [edi+0x00000B50]
		retcode:
		popfd
		jmp dword ptr [GameHook::customCameraDistance.jmp_ret]
	}
}

bool GameHook::haloDisplay_toggle = false;
int GameHook::haloDisplayValue = 0;
uintptr_t haloDisplayAddress = 0x5BB57B0;
static __declspec(naked) void HaloDisplayDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::haloDisplay_toggle], 0
		je originalcode

		cmp dword ptr [GameHook::haloDisplayValue], 1
		jle originalcode
		mov eax, [GameHook::haloDisplayValue]	

		originalcode:
		push esi
		mov esi, [haloDisplayAddress] // i still hate this
		mov [esi], eax
		pop esi
		popfd
		jmp dword ptr [GameHook::haloDisplay.jmp_ret]
	}
}

bool GameHook::moveIDSwap_toggle = false;
bool GameHook::moveIDSwap_toggles[maxMoveIDSwaps]{};
int GameHook::moveIDSwapSourceMoves[maxMoveIDSwaps]{};
int GameHook::moveIDSwapSwappedMoves[maxMoveIDSwaps]{};
int __stdcall GetSwappedMoveID(int nextMoveID) {
    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
		if (GameHook::moveIDSwap_toggles[i] && GameHook::moveIDSwapSourceMoves[i] == nextMoveID) {
            return GameHook::moveIDSwapSwappedMoves[i];
        }
    }
    return -1;
}

static __declspec(naked) void MoveIDSwapDetour(void) { // player in ecx
	_asm {
		pushfd
		cmp byte ptr [GameHook::moveIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], ecx
		pop eax
		jne originalcode

		push eax // +4
		push ecx // +8
		push edx // +C
		push edx // nextMoveID
		call dword ptr GetSwappedMoveID
		cmp eax, -1
		je dontReplace
		pop edx
		pop ecx
		mov [ecx+0x0000034C], eax
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [ecx+0x0000034C], edx
		retcode:
		popfd
		jmp dword ptr [GameHook::moveIDSwap.jmp_ret]
	}
}

bool GameHook::stringSwap_toggle = false;
bool GameHook::stringIDSwap_toggles[maxStringSwaps];
int  GameHook::stringIDSwapSourceStrings[maxStringSwaps];
int  GameHook::stringIDSwapDesiredStrings[maxStringSwaps];
int __stdcall GetSwappedStringID(int nextStringID) {
    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
		if (GameHook::stringIDSwap_toggles[i] && GameHook::stringIDSwapSourceStrings[i] == nextStringID) {
            return GameHook::stringIDSwapDesiredStrings[i];
        }
    }
    return -1;
}

static __declspec(naked) void PunchStringIDSwapDetour(void) {
	_asm {
		pushfd
		cmp byte ptr [GameHook::stringSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push edx // nextStringID
		call dword ptr GetSwappedStringID

		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], edx
		retcode:
		popfd
		jmp dword ptr [GameHook::punchStringIDSwap.jmp_ret]
	}
}

static __declspec(naked) void LatePunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push eax // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], eax
		retcode:
		jmp dword ptr [GameHook::latePunchStringIDSwap.jmp_ret]
	}
}

static __declspec(naked) void KickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push edx // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], edx
		retcode:
		jmp dword ptr [GameHook::kickStringIDSwap.jmp_ret]
	}
}

static __declspec(naked) void LateKickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		push eax
		push ecx
		push edx
		push ecx // nextStringID
		call dword ptr GetSwappedStringID
		cmp eax, -1
		je dontReplace
		mov [esi+0x00095C64], eax
		pop edx
		pop ecx
		pop eax
		jmp retcode

		dontReplace:
		pop edx
		pop ecx
		pop eax
		originalcode:
		mov [esi+0x00095C64], ecx
		retcode:
		jmp dword ptr [GameHook::lateKickStringIDSwap.jmp_ret]
	}
}

bool GameHook::easierMash_toggle = false;
static __declspec(naked) void EasierMashDetour(void) {
	_asm {
		cmp byte ptr [GameHook::easierMash_toggle], 0
		je originalcode

		mov dword ptr [esi+0x30], 0x3fc00000 // 1.5f

		originalcode:
		divss xmm0, [esi+0x30]
		jmp dword ptr [GameHook::easierMash.jmp_ret]
	}
}

bool GameHook::cancellableAfterBurner_toggle = false;
static uintptr_t cancellableMovesCall = 0x9E85E0;
static __declspec(naked) void CancellableAfterBurnerDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableAfterBurner_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		cmp [esi+0x00000350], ebx
		jmp dword ptr [GameHook::cancellableAfterBurner.jmp_ret]
	}
}

bool GameHook::cancellableFallingKick_toggle = false;
static uintptr_t CancellableFallingKickDefaultCall = 0x433220;
static __declspec(naked) void CancellableFallingKickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableFallingKick_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		call dword ptr [CancellableFallingKickDefaultCall]
		jmp dword ptr [GameHook::cancellableFallingKick.jmp_ret]
	}
}

static __declspec(naked) void CancellableFallingKickDurgaDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableFallingKick_toggle], 0
		je originalcode

		cmp dword ptr [esi+0x350], 4 // only before landing
		ja originalcode
		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		movss xmm0, [esi+0x000006F4]
		jmp dword ptr [GameHook::cancellableFallingKickDurga.jmp_ret]
	}
}

bool GameHook::altTeleInput_toggle = false;
static uintptr_t altTeleInput_jmp_jle = 0x8BE5AC;
static uintptr_t altTeleInput_jmp_je = 0x8BE5B6;
static int altTeleInput = 0x400; // dpad down = 0x4, taunt = 0x400
static __declspec(naked) void AltTeleInputDetour(void) {
	_asm {
		cmp byte ptr [GameHook::altTeleInput_toggle], 0
		je originalcode

		push eax
		mov eax, [altTeleInput]
		test [ebx+0x00094B48], eax
		pop eax
		jnz teleport
		jmp jmp_je

		teleport:
		mov dword ptr [ebx+0x0009399C], 0x00000001
		jmp dword ptr [GameHook::altTeleInput.jmp_ret]

		originalcode:
		test [ebx+0x00094B48], eax
		je jmp_je
		cmp [ebx+0x000939A0], esi
		jle jmp_jle
		cmp byte ptr [GameHook::omnicancelTele_toggle], 1 // don't take 4 orbs if omnicancel is active!
		je teleport
		mov dword ptr [ebx+0x0009399C], 0x0000000A // frames mashed
		jmp dword ptr [GameHook::altTeleInput.jmp_ret] // Bayonetta.exe+4BE5A2, accept teleport

		jmp_jle:
		jmp dword ptr [altTeleInput_jmp_jle]

		jmp_je:
		jmp dword ptr [altTeleInput_jmp_je] // Bayonetta.exe+4BE5B6, deny teleport
	}
}

bool GameHook::tauntWithTimeBracelet_toggle = false;
static __declspec(naked) void TauntWithTimeBraceletADetour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax, 4

		originalcode:
		test [esi+0x00094B4C], eax
		jmp dword ptr [GameHook::tauntWithTimeBraceletA.jmp_ret]
	}
}

static __declspec(naked) void TauntWithTimeBraceletBDetour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax, 4

		originalcode:
		test [ebx+0x00094B44], eax
		jmp dword ptr [GameHook::tauntWithTimeBraceletB.jmp_ret]
	}
}

bool GameHook::disableSlowmo_toggle = false;
static float disableSlowmoDefaultSpeed = 1.0f;
static __declspec(naked) void DisableSlowmoDetour(void) {
	_asm {
		cmp byte ptr [GameHook::disableSlowmo_toggle], 0
		je originalcode

		movss xmm0, [disableSlowmoDefaultSpeed]
		jmp dword ptr [GameHook::disableSlowmo.jmp_ret]

		originalcode:
		movss xmm0, [ecx+0x38]
		jmp dword ptr [GameHook::disableSlowmo.jmp_ret]
	}
}

bool GameHook::lowerDivekick_toggle = false;
static float lowerDivekickTime = 7.0f;
static __declspec(naked) void LowerDivekickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::lowerDivekick_toggle], 0
		je originalcode

		movss xmm0, [lowerDivekickTime]
		comiss xmm0, [esi+0x00093594]
		xorps xmm0, xmm0 // restore xmm0
		jmp dword ptr [GameHook::lowerDivekick.jmp_ret]

		originalcode:
		comiss xmm0, [esi+0x00093594]
		jmp dword ptr [GameHook::lowerDivekick.jmp_ret]
	}
}

bool GameHook::dualAfterBurner_toggle = false;
static uintptr_t dualAfterBurnerCall = 0x9E33D0;
static __declspec(naked) void DualAfterBurnerDetour(void) {
	_asm {
		call dword ptr [dualAfterBurnerCall]
		cmp byte ptr [GameHook::dualAfterBurner_toggle], 0
		je jmpcode

		// reuse stack
		// movss xmm0,[Bayonetta.exe+9A0DD4]
		sub esp, 0x14
		// movss [esp+10],xmm0
		// movss xmm0,[Bayonetta.exe+A280B0]
		// movss [esp+0C],xmm0
		// movss xmm0,[Bayonetta.exe+A2718C]
		// movss [esp+08],xmm0
		// xorps xmm0,xmm0
		// movss [esp+04],xmm0
		// movss xmm0,[Bayonetta.exe+99D79C]
		// movss [esp],xmm0
		push 0x03
		mov ecx, esi
		call dword ptr [dualAfterBurnerCall]

		jmpcode:
		jmp dword ptr [GameHook::dualAfterBurner.jmp_ret]
	}
}

/*
bool GameHook::loadReplace_toggle = false;
static __declspec(naked) void LoadReplaceDetour(void) {
	_asm {
		push ecx
		cmp byte ptr [GameHook::loadReplace_toggle], 0
		je originalcode

		cmp edx, 0x622180 // AA
		je angelattack
		jmp originalcode

		angelattack:
		mov edx, 0x00619DD0 // stage select
		jmp originalcode

		originalcode:
		mov ecx, [eax+0x08]
		call edx
		jmp dword ptr [GameHook::loadReplace.jmp_ret]
	}
}*/

bool GameHook::longerPillowTalkCharge_toggle = false;
static float longerPillowTalkChargeMult = 2.0f;
static __declspec(naked) void LongerPillowTalkChargeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::longerPillowTalkCharge_toggle], 0
		je originalcode

		movss xmm0, [esp+0x04]
		mulss xmm0, [longerPillowTalkChargeMult]
		jmp dword ptr [GameHook::longerPillowTalkCharge.jmp_ret]

		originalcode:
		movss xmm0, [esp+0x04] // from [00DA0DE8]
		jmp dword ptr [GameHook::longerPillowTalkCharge.jmp_ret]
	}
}

bool GameHook::alwaysWitchTime_toggle = false;
float alwaysWitchTimeTimer = 120.0f;
static __declspec(naked) void AlwaysWitchTimeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::alwaysWitchTime_toggle], 0
		je originalcode

		movss xmm1, [alwaysWitchTimeTimer]
		jmp dword ptr [GameHook::alwaysWitchTime.jmp_ret]

		originalcode:
		movss xmm1, [esi+0x00000704]
		jmp dword ptr [GameHook::alwaysWitchTime.jmp_ret]
	}
}

int __stdcall GetCustomWeave(LocalPlayer* player) {
    int moveID = player->moveID;
    for (int i = 0; i < GameHook::customWeaveCount; ++i) {
        if (GameHook::customWeave_toggles[i] && GameHook::customWeaveMoveIDArray[i] == moveID) {
            return GameHook::customWeaveArray[i];
        }
    }
    return -1;
}

bool GameHook::customWeaves_toggle = false;
bool GameHook::customWeave_toggles[customWeaveCount]{};
int GameHook::customWeaveArray[customWeaveCount]{};
int GameHook::customWeaveMoveIDArray[customWeaveCount]{};
static __declspec(naked) void CustomWeavesDetour(void) { // player in esi
	_asm {
		cmp byte ptr [GameHook::customWeaves_toggle], 0
		je originalcode

		push eax // +4
		push ecx // +8
		push edx // +C
		push esi // player
		call dword ptr GetCustomWeave
		cmp eax, -1
		je dontReplace
		mov [esp+0xC+8], eax
		dontReplace:
		pop edx
		pop ecx
		pop eax

	originalcode:
		push ebx
		push ebp
		mov ebp, [esp+0x0C]
		jmp dword ptr [GameHook::customWeaves.jmp_ret]
	}
}

bool GameHook::omnicancelTele_toggle = false;
static uintptr_t omnicancelTele_call = 0x009E6FA0;
static uintptr_t omnicancelTele_ogcode = 0x05A97ED0;
static __declspec(naked) void OmnicancelTeleDetour(void) { // player in ebx
	_asm {
		pushfd
		cmp byte ptr [GameHook::omnicancelTele_toggle], 0
		je originalcode

		test ebx, ebx // check player exists, probably not necessary
		je originalcode
		cmp dword ptr [ebx+0x0009399C], 00 // extra safety, check if teleport is queued
		je originalcode

		cmp dword ptr [ebx+0x34C], 245
		ja originalcode

		push eax
		push ecx
		push edx
		mov ecx, ebx // player
		call dword ptr omnicancelTele_call
		pop edx
		pop ecx
		pop eax

		originalcode:
		popfd
		push 0x0B
		mov ecx, [omnicancelTele_ogcode]
		// mov ecx, [ecx]
		jmp dword ptr [GameHook::omnicancelTele.jmp_ret]
	}
}

struct SpawnSnapshot {
	int ID;
	int unkn;
	int optionalStructUsed;
	int structUnkn;
	int structVariant;
	int structSpawnModifier;
};

static std::vector<SpawnSnapshot> recentlySpawnedList;
static const size_t MAX_SNAPSHOTS = 10000;

static void LogEntitySpawn(int ID, int unkn, int optionalStructUsed, int structUnkn, int structVariant, int structSpawnModifier) {
	if (recentlySpawnedList.size() >= MAX_SNAPSHOTS)
		recentlySpawnedList.erase(recentlySpawnedList.begin());

	recentlySpawnedList.push_back({
		ID,
		unkn,
		optionalStructUsed,
		structUnkn,
		structVariant,
		structSpawnModifier
	});
}

void GameHook::DisplayRecentlySpawnedEntitiesInImGui() {
	if (ImGui::Button("Clear"))
		recentlySpawnedList.clear();
	ImGui::Text("Count: %d", (int)recentlySpawnedList.size());
	ImGui::Separator();

	for (size_t i = 0; i < recentlySpawnedList.size(); i++) {
		auto& s = recentlySpawnedList[i];

		ImGui::PushID((int)i);
		ImGui::PushItemWidth(inputItemWidth);
		ImGui::InputInt("Has Optional Struct", &s.optionalStructUsed);
		ImGui::InputScalar("ID", ImGuiDataType_S32, &s.ID, NULL, NULL, "%8X");
		const char* name = GetAllKnownEntityName(s.ID);
		if (name) {
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "%s", name);
		}

		ImGui::InputScalar("Unkn", ImGuiDataType_S32, &s.unkn, NULL, NULL, "%8X");
		if (s.optionalStructUsed == 1) {
			ImGui::InputScalar("Struct.int_0_Unkn", ImGuiDataType_S32, &s.structUnkn, NULL, NULL, "%8X");
			ImGui::InputScalar("Struct.int_4_Variant", ImGuiDataType_S32, &s.structVariant,  NULL, NULL, "%8X");
			ImGui::InputScalar("Struct.int_8_SpawnModifier", ImGuiDataType_S32, &s.structSpawnModifier, NULL, NULL, "%8X");
		}
		ImGui::PopItemWidth();
		ImGui::Separator();
		ImGui::PopID();
	}
}

struct SpawnResult {
	int id;
	int variant;
	int spawnModifier;
};

static const std::unordered_map<SpawnCategory, std::vector<SpawnCategory>> spawnCategoryPool = {
	{SpawnCategory::EnemyTier1, {SpawnCategory::EnemyTier1}},
	{SpawnCategory::EnemyTier2, {SpawnCategory::EnemyTier2, SpawnCategory::EnemyTier1}},
	{SpawnCategory::EnemyBoss,  {SpawnCategory::EnemyBoss, SpawnCategory::EnemyTier2}},
};

static SpawnResult GetRandomizedSpawn(int id, int variant, int spawnModifier) {
	const SpawnCategory* category = nullptr;
	for (const auto& entry : spawnTypes) {
		// only search for id because the other values vary so much. Modifier is set to 0 on every spawn, so randomized enemies are probably easy
		if (entry.info.id == id) {
			category = &entry.category;
			break;
		}
	}

	if (!category)
		return { id, variant, spawnModifier };

	std::vector<const SpawnInfo*> pool;
	const auto& allowedCategories = spawnCategoryPool.at(*category);
	for (const auto& entry : spawnTypes) {
		if (std::find(allowedCategories.begin(), allowedCategories.end(), entry.category) != allowedCategories.end())
			pool.push_back(&entry.info);
	}

	if (pool.empty())
		return { id, variant, spawnModifier };

	std::uniform_int_distribution<size_t> dist(0, pool.size() - 1);
	const SpawnInfo* picked = pool[dist(GameHook::rng)];
	return { picked->id, picked->variant, picked->spawnModifier };
}

static SpawnResult randomizer_spawnResult;
static void DoRandomizeSpawn(int id, int variant, int spawnModifier) {
	randomizer_spawnResult = GetRandomizedSpawn(id, variant, spawnModifier);
}

static SpawnResult GetSwappedSpawn(int id, int variant, int spawnModifier) {
	for (const auto& rule : GameHook::swapRules) {
		if (!rule.enabled)
			continue;
		const auto& src = spawnTypes[rule.sourceIndex].info;
		if (src.id == id &&
			src.variant == variant) {
			const auto& dst = spawnTypes[rule.targetIndex].info;
			return {dst.id, dst.variant, rule.spawnModifier == -1 ? dst.spawnModifier : rule.spawnModifier};
		}
	}
	return { id, variant, spawnModifier };
}

static void DoSwapSpawn(int id, int variant, int spawnModifier) {
	randomizer_spawnResult = GetSwappedSpawn(id, variant, spawnModifier);
}

std::vector<SwapRule> GameHook::swapRules;
static void InitSwapRules() {
	GameHook::swapRules.clear();
	GameHook::swapRules.reserve(spawnTypes.size());
	for (int i = 0; i < (int)spawnTypes.size(); i++) {
		GameHook::swapRules.push_back({ i, i, -1, false});
	}
}

bool GameHook::randomizeSpawns_toggle = false;
bool GameHook::swapSpawns_toggle = false;
bool GameHook::viewEntitySpawns_toggle = false;
static __declspec(naked) void ViewEntitySpawnsDetour(void) {
	__asm {
		pushfd
		cmp byte ptr [GameHook::viewEntitySpawns_toggle], 1
		je viewcode
		cmp byte ptr [GameHook::randomizeSpawns_toggle], 1
		je randomcode
		cmp byte ptr [GameHook::swapSpawns_toggle], 1
		je swapcode
		jmp originalcode
 
	swapcode:
		pushad
		mov eax, [esp+0x28] // id
		mov ecx, [esp+0x2C] // optionalSettings
		test ecx, ecx
		je swapNoStruct
		push dword ptr [ecx+0x8] // spawnModifier
		push dword ptr [ecx+0x4] // variant
		push eax // id
		call DoSwapSpawn
		add esp, 12
		mov ecx, [esp+0x2C]
		mov eax, dword ptr [randomizer_spawnResult]
		mov [esp+0x28], eax
		mov eax, dword ptr [randomizer_spawnResult+4]
		mov [ecx+0x4], eax
		mov eax, dword ptr [randomizer_spawnResult+8]
		mov [ecx+0x8], eax
		jmp swapDone
 
	swapNoStruct:
		push 0
		push 0
		push eax
		call DoSwapSpawn
		add esp, 12
		mov eax, dword ptr [randomizer_spawnResult]
		mov [esp+0x28], eax
	swapDone:
		popad
		jmp originalcode
 
	viewcode:
		pushad
		mov edx, [esp+0x28] // entityID
		mov eax, [esp+0x2C] // optionalSettings
		mov ecx, [esp+0x30] // unkn
		test eax, eax
		je dontLogEax
		cmp eax, 0x10000
		jb dontLogEax
		push [eax+0x8] // struct.SpawnModifier
		push [eax+0x4] // struct.Variant
		push [eax+0x0] // struct.Unkn
		push 1 // struct Used
		push ecx
		push edx
		call LogEntitySpawn
		add esp, 24
		jmp popcode

	dontLogEax:
		push 0 // struct.SpawnModifier
		push 0 // struct.Variant
		push 0 // struct.Unkn
		push 0 // struct Used
		push ecx
		push edx
		call LogEntitySpawn
		add esp, 24
		jmp popcode

	randomcode:
		pushad
		mov eax, [esp+0x28] // ID
		mov ecx, [esp+0x2C] // optionalSettings ptr
		test ecx, ecx
		je randNoStruct
		push dword ptr [ecx+0x8] // spawnModifier
		push dword ptr [ecx+0x4] // variant
		push eax // ID
		call DoRandomizeSpawn
		add esp, 12
		cmp byte ptr [GameHook::swapSpawns_toggle], 1
		jne applyRandomResult
		push dword ptr [randomizer_spawnResult+8]
		push dword ptr [randomizer_spawnResult+4]
		push dword ptr [randomizer_spawnResult]
		call DoSwapSpawn
		add esp, 12

	applyRandomResult:
		mov ecx, [esp+0x2C]
		mov eax, dword ptr [randomizer_spawnResult]
		mov [esp+0x28], eax
		mov eax, dword ptr [randomizer_spawnResult+4]
		mov [ecx+0x4], eax
		mov eax, dword ptr [randomizer_spawnResult+8]
		mov [ecx+0x8], eax
		jmp randDone
 
	randNoStruct:
		push 0
		push 0
		push eax
		call DoRandomizeSpawn
		add esp, 12
		cmp byte ptr [GameHook::swapSpawns_toggle], 1
		jne applyRandomNoStruct
		push 0
		push 0
		push dword ptr [randomizer_spawnResult]
		call DoSwapSpawn
		add esp, 12

	applyRandomNoStruct:
		mov eax, dword ptr [randomizer_spawnResult]
		mov [esp+0x28], eax
	randDone:
		popad
		jmp originalcode

	popcode:
		popad
	originalcode:
		popfd
		mov eax, [esp+0x0C]
		mov edx, [esp+0x08]
		jmp dword ptr [GameHook::viewEntitySpawns.jmp_ret]
	}
}

bool GameHook::teleportComboAction_toggle = false;
static __declspec(naked) void TeleportComboActionDetour(void) { // player in ebx
	_asm {
		cmp byte ptr [GameHook::teleportComboAction_toggle], 0
		je originalcode

		mov dword ptr [esi+0x95C80], 0x41700000 // 15f

		originalcode:
		mov eax, [esi+0x00000350]
		jmp dword ptr [GameHook::teleportComboAction.jmp_ret]
	}	
}

bool GameHook::thirdAccessoryMenu_toggle = false;
static uintptr_t thirdAccessoryMenu_jmp_alt = 0xB1E0DC;
static uintptr_t thirdAccessoryMenuRightCall = 0xB28850;
static uintptr_t thirdAccessoryMenuLeftCall = 0xB28880;
static __declspec(naked) void ThirdAccessoryMenuDetour(void) {
	_asm {
		cmp dword ptr [GameHook::thirdAccessoryMenu_toggle], 1
		jne originalcode

		push 01
		mov ecx, esi
		call dword ptr [thirdAccessoryMenuRightCall]
		test eax, eax
		je check_left
		mov eax, [esi+0x00000088]
		cmp eax, 00
		je set_right
		cmp eax, 02
		jne check_left // only 0 and 2 move right
		set_right:
		mov dword ptr [esi+0x00000088], 00000001
		jmp dword ptr [thirdAccessoryMenu_jmp_alt]

		check_left:
		push 01
		mov ecx, esi
		call dword ptr [thirdAccessoryMenuLeftCall]
		test eax, eax
		je check_down
		mov eax, [esi+0x00000088]
		cmp eax, 01
		jne check_down
		mov dword ptr [esi+0x00000088], 00000000
		jmp dword ptr [thirdAccessoryMenu_jmp_alt]

		check_down:
		mov eax, ds:[0x5ACBFD4]
		test al, 04
		jne set_down
		test eax, 0x00040000
		je check_up
		set_down:
		cmp dword ptr [ecx+0x38], 00
		je check_up
		mov dword ptr [esi+0x00000088], 00000002 // 0 and 1 both move down to 2
		jmp dword ptr [thirdAccessoryMenu_jmp_alt]

		check_up:
		mov eax, ds:[0x5ACBFD4] // 0
		test al, 0x08
		jne set_up
		test eax, 0x00080000
		je retcode
		set_up:
		cmp dword ptr [ecx+0x38], 00
		je retcode
		mov eax, [esi+0x00000088]
		cmp eax, 02
		jne retcode // only 2 moves up
		mov dword ptr [esi+0x00000088], 00000000
		retcode:
		jmp dword ptr [thirdAccessoryMenu_jmp_alt]

		originalcode:
		push 01
		mov ecx,esi
		call dword ptr [thirdAccessoryMenuRightCall]
		jmp dword ptr [GameHook::thirdAccessoryMenu.jmp_ret]
	}
}

// accessories that use held y+b break without this
static uintptr_t fixThirdAccessoryCall = 0x4332F0;
static __declspec(naked) void FixThirdAccessoryDetour(void) { // player in ebx
	_asm {
		//
			push eax
			mov eax, [GameHook::thirdAccessoryAddress]
			cmp dword ptr [eax], 0
			pop eax
			je originalcode
		//
			push 2
			call dword ptr [fixThirdAccessoryCall]
			add esp, 4 // pop

		originalcode:
			add esp, 8
			mov ebp, eax
			jmp dword ptr [GameHook::fixThirdAccessory.jmp_ret]
	}
}

static std::unique_ptr<FunctionHook> pl0012Hook;
const char* pl0012att = "pl0012.dat\\pl0012.att";
const char* pl0012flg = "pl0012.dat\\pl0012.flg";
static __declspec(naked) void pl0012Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15139064
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15139040
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		push    [pl0012att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     esi, 12973536
		mov     edi, 12958688
		push    15139396
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139368
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139340
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139312
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		push    [pl0012flg]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L19
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L7
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L7
		add     edi, eax
		xor		ebp, ebp

		L9:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L8:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L9

		L7:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L10
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L10
		xor		edi, edi
		lea     ebp, [esi + eax]

		L12:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L11
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L11:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L12

		L10:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L13
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L13
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L15:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L14
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L14:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L15

		L13:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp		L5

		L19:
		xor		edi, edi
		mov     esi, 4862688

		L6:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L16:
		add     edi, 1
		cmp     edi, 4
		jne		L6
		mov     edi, 8
		mov     esi, 4862688

		L18:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L17
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L17:
		add     edi, 1
		cmp     edi, 12
		jne		L18
		jmp		L13
	}
}

static std::unique_ptr<FunctionHook> pl0031Hook;
const char* pl0031att = "pl0031.dat\\pl0031.att";
const char* pl0031flg = "pl0031.dat\\pl0031.flg";
static __declspec(naked) void pl0031Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15147736
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15147712
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15147684
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147656
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147628
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl0031att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl0031flg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L85
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 2
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    10
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    3
		push    91
		call    esi
		mov     ecx, ebx
		push    0
		push    4
		push    92
		call    esi
		mov     ecx, ebx
		push    0
		push    5
		push    93
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    94
		call    esi
		mov     ecx, ebx
		push    0
		push    7
		push    95
		call    esi
		mov     ecx, ebx
		push    0
		push    8
		push    96
		call    esi
		mov     ecx, ebx
		push    0
		push    9
		push    97
		call    esi
		mov     ecx, ebx
		push    0
		push    13
		push    98
		call    esi
		mov     ecx, ebx
		push    0
		push    14
		push    99
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    100
		call    esi
		add     esp, 20
		jmp		L5

		L85:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    4
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    5
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    6
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    15
		call    eax
		add     esp, 12
		test    eax, eax
		je		L26
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L26:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    16
		call    eax
		add     esp, 12
		test    eax, eax
		je		L27
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L27:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    17
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		sub     esp, 12
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -69
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		mov     eax, 4849216
		mov     DWORD PTR[ecx + 84], 18
		push    1
		call    eax
		add     esp, 12
		jmp		L16
	}
}

static std::unique_ptr<FunctionHook> pl004cHook;
const char* pl004catt = "pl004c.dat\\pl004c.att";
const char* pl004cflg = "pl004c.dat\\pl004c.flg";
static __declspec(naked) void pl004cDetour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15156328
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15156304
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15156276
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156248
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156220
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156192
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl004catt]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl004cflg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L77
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp L5

		L77:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    8
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    9
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    10
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    11
		call    eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		jmp		L16
	}
}

#endif

void GameHook::SaveDetours(utils::Config& cfg) {
#ifndef SPEEDRUN_BUILD
	cfg.set<bool>("uptimeFix_toggle", uptimeFix_toggle);
	cfg.set<bool>("damageReceivedMultiplierNoDamage_toggle", damageReceivedMultiplierNoDamage_toggle);
	cfg.set<bool>("cameraSelect_toggle", cameraSelect_toggle);
	cfg.set<int>("cameraSelect_newCameraType", cameraSelect_newCameraType);
	cfg.set<bool>("drawHitboxes_toggle", drawHitboxes_toggle);
	cfg.set<bool>("openMenuPause_toggle", openMenuPause_toggle);
	cfg.set<bool>("enemyHPNoDamage_toggle", enemyHPNoDamage_toggle);
	cfg.set<bool>("enemyHPOneHitKill_toggle", enemyHPOneHitKill_toggle);
	cfg.set<bool>("witchTimeMultiplier_toggle", witchTimeMultiplier_toggle);
	cfg.set<float>("witchTimeMultiplier_value", witchTimeMultiplier_value);
	cfg.set<bool>("infMagic_toggle", infMagic_toggle);
	cfg.set<float>("infMagic_value", infMagic_value);
	cfg.set<bool>("damageDealtMultiplier_toggle", damageDealtMultiplier_toggle);
	cfg.set<float>("damageDealtMultiplierMult", damageDealtMultiplierMult);
	cfg.set<bool>("damageReceivedMultiplier_toggle", damageReceivedMultiplier_toggle);
	cfg.set<float>("incoming_damage_mult", incoming_damage_mult);
	cfg.set<bool>("customCameraDistance_toggle", customCameraDistance_toggle);
	cfg.set<float>("customCameraDistance_value", customCameraDistance_value);
	cfg.set<bool>("forceSummoningClothes_toggle", forceSummoningClothes_toggle);
	cfg.set<bool>("haloDisplay_toggle", haloDisplay_toggle);
	cfg.set<bool>("easierMash_toggle", easierMash_toggle);
	cfg.set<int>("initialAngelSlayerFloor_value", initialAngelSlayerFloor_value);
	cfg.set<bool>("cancellableAfterBurner_toggle", cancellableAfterBurner_toggle);
	cfg.set<bool>("cancellableFallingKick_toggle", cancellableFallingKick_toggle);
	cfg.set<bool>("turbo_toggle", turbo_toggle);
	cfg.set<float>("turboValue", turboValue);
	cfg.set<bool>("altTeleInput_toggle", altTeleInput_toggle);
	cfg.set<bool>("teleportComboAction_toggle", teleportComboAction_toggle);
	cfg.set<bool>("tauntWithTimeBracelet_toggle", tauntWithTimeBracelet_toggle);
	cfg.set<bool>("disableSlowmo_toggle", disableSlowmo_toggle);
	cfg.set<bool>("lowerDivekick_toggle", lowerDivekick_toggle);
	cfg.set<bool>("dualAfterBurner_toggle", dualAfterBurner_toggle);
	//cfg.set<bool>("loadReplace_toggle", loadReplace_toggle);
	cfg.set<bool>("longerPillowTalkCharge_toggle", longerPillowTalkCharge_toggle);
	cfg.set<bool>("alwaysWitchTime_toggle", alwaysWitchTime_toggle);
	cfg.set<bool>("saveStatesHotkeys_toggle", saveStatesHotkeys_toggle);
	cfg.set<bool>("omnicancelTele_toggle", omnicancelTele_toggle);
	cfg.set<bool>("randomizeSpawns_toggle", randomizeSpawns_toggle);
	cfg.set<bool>("longerBufferWindows_toggle", longerBufferWindows_toggle);

	cfg.set<bool>("swapSpawns_toggle", swapSpawns_toggle);
	for (int i = 0; i < (int)swapRules.size(); i++) {
		const auto& rule = swapRules[i];
		std::string keyEnabled = "swapRule_" + std::to_string(i) + "_enabled";
		std::string keyTarget = "swapRule_" + std::to_string(i) + "_target";
		std::string keyModifier = "swapRule_" + std::to_string(i) + "_modifier";
		cfg.set<bool>(keyEnabled, rule.enabled);
		cfg.set<int>(keyTarget, rule.targetIndex);
		cfg.set<int>(keyModifier, rule.spawnModifier);
	}

	cfg.set<bool>("thirdAccessoryMenu_toggle", thirdAccessoryMenu_toggle);

	cfg.set<bool>("moveIDSwap_toggle", moveIDSwap_toggle);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		cfg.set<bool>(("moveIDSwap_toggles[" + std::to_string(i) + "]").c_str(), moveIDSwap_toggles[i]);
		cfg.set<int>(("moveIDSwapSourceMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSourceMoves[i]);
		cfg.set<int>(("moveIDSwapSwappedMoves[" + std::to_string(i) + "]").c_str(), moveIDSwapSwappedMoves[i]);
	}

	cfg.set<bool>("stringSwap_toggle", stringSwap_toggle);
	for (int i = 0; i < maxStringSwaps; ++i) {
		cfg.set<bool>(("stringIDSwap_toggles[" + std::to_string(i) + "]").c_str(), stringIDSwap_toggles[i]);
		cfg.set<int>(("stringIDSwapSourceStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapSourceStrings[i]);
		cfg.set<int>(("stringIDSwapDesiredStrings[" + std::to_string(i) + "]").c_str(), stringIDSwapDesiredStrings[i]);
	}

	cfg.set<bool>("customWeaves_toggle", customWeaves_toggle);
	for (int i = 0; i < customWeaveCount; ++i) {
		cfg.set<bool>(("customWeave_toggles[" + std::to_string(i) + "]").c_str(), customWeave_toggles[i]);
		cfg.set<int>(("customWeaveMoveIDArray[" + std::to_string(i) + "]").c_str(), customWeaveMoveIDArray[i]);
		cfg.set<int>(("customWeaveArray[" + std::to_string(i) + "]").c_str(), customWeaveArray[i]);
	}

#endif
	// both speedrun and non speedrun
	cfg.set<bool>("linkGameToDelta_toggle", linkGameToDelta_toggle);
	cfg.set<bool>("inputIcons_toggle", inputIcons_toggle);
	cfg.set<int>("inputIconsValue", inputIconsValue);
	cfg.set<bool>("randomizeCostume_toggle", randomizeCostume_toggle);
	cfg.save(GameHook::cfgString);
}

void GameHook::LoadDetours(const utils::Config& cfg) {
#ifdef SPEEDRUN_BUILD
	uptimeFix_toggle = true; // forced
#endif
#ifndef SPEEDRUN_BUILD
	uptimeFix_toggle = cfg.get<bool>("uptimeFix_toggle").value_or(false);
#endif
	// always
	GameHook::InitHook("uptimeFix", 0xC78100, &UptimeFixDetour, 6, GameHook::uptimeFix);

	inputIcons_toggle = cfg.get<bool>("inputIcons_toggle").value_or(false);
	inputIconsValue = cfg.get<int>("inputIconsValue").value_or(0);
	GameHook::InitHook("inputIcons", 0x411CD4, &InputIconsDetour, 13, GameHook::inputIcons);

	randomizeCostume_toggle = cfg.get<bool>("randomizeCostume_toggle").value_or(false);
	GameHook::InitHook("randomizeCostume", 0x4FC4EF, &RandomizeCostumeDetour, 5, GameHook::randomizeCostume);
	
	linkGameToDelta_toggle = cfg.get<bool>("linkGameToDelta_toggle").value_or(false);
	longerBufferWindows_toggle = cfg.get<bool>("longerBufferWindows_toggle").value_or(false);
	GameHook::InitHook("linkGameToDelta_punchBufferFrames", 0x8BE2B6, &PunchBufferFramesDetour, 6, GameHook::punchBufferFrames);
	GameHook::InitHook("linkGameToDelta_kickBufferFrames", 0x8BE387, &KickBufferFramesDetour, 6, GameHook::kickBufferFrames);
	GameHook::InitHook("linkGameToDelta_dodgeBufferFrames", 0x8BE471, &DodgeBufferFramesDetour, 6, GameHook::dodgeBufferFrames);
	GameHook::InitHook("linkGameToDelta_gunBufferFrames", 0x8BE55B, &GunBufferFramesDetour, 6, GameHook::gunBufferFrames);
	GameHook::InitHook("linkGameToDelta_controllerCameraSens", 0xA8FBB1, &ControllerCameraSensDetour, 8, GameHook::controllerCameraSens);
	GameHook::InitHook("linkGameToDelta_fpsSkateSpeed1", 0x8F2EB6, &FpsSkateSpeed1Detour, 8, GameHook::fpsSkateSpeed1);
	GameHook::InitHook("linkGameToDelta_fpsSkateSpeed2", 0x8E72B3, &FpsSkateSpeed2Detour, 8, GameHook::fpsSkateSpeed2);
	GameHook::InitHook("linkGameToDelta_fixIntroMoviesTimer", 0x5A1DE5, &FixIntroMoviesTimerDetour, 10, GameHook::fixIntroMoviesTimer);

	openMenuPause_toggle = cfg.get<bool>("openMenuPause_toggle").value_or(false);
	turbo_toggle = cfg.get<bool>("turbo_toggle").value_or(false);
	turboValue = cfg.get<float>("turboValue").value_or(1.0f);
	GameHook::InitHook("turbo", 0x513FC7, &TurboHookDetour, 5, GameHook::turbo);

	static std::random_device bayoHookRandomDevice;
	GameHook::rng.seed(bayoHookRandomDevice() ^ (unsigned)time(NULL));
#ifndef SPEEDRUN_BUILD
	forceSummoningClothes_toggle = cfg.get<bool>("forceSummoningClothes_toggle").value_or(false);
	saveStatesHotkeys_toggle = cfg.get<bool>("saveStatesHotkeys_toggle").value_or(false);
	//loadReplace_toggle = cfg.get<bool>("loadReplace_toggle").value_or(false);

	drawHitboxes_toggle = cfg.get<bool>("drawHitboxes_toggle").value_or(false);
	GameHook::InitHook("getHitbox", 0x41837E, &GetHitboxDetour, 8, GameHook::getHitbox);

	enemyHPNoDamage_toggle = cfg.get<bool>("enemyHPNoDamage_toggle").value_or(false);
	enemyHPOneHitKill_toggle = cfg.get<bool>("enemyHPOneHitKill_toggle").value_or(false);
	GameHook::InitHook("enemyHP", 0x4572BA, &EnemyHPDetour, 6, GameHook::enemyHP);

	damageDealtMultiplier_toggle = cfg.get<bool>("damageDealtMultiplier_toggle").value_or(false);
	damageDealtMultiplierMult = cfg.get<float>("damageDealtMultiplierMult").value_or(1.0f);
	GameHook::InitHook("damageDealtMultiplier", 0x4572B2, &DamageDealtMultiplierDetour, 8, GameHook::damageDealtMultiplier);

	incoming_damage_mult = cfg.get<float>("incoming_damage_mult").value_or(1.0f);
	damageReceivedMultiplier_toggle = cfg.get<bool>("damageReceivedMultiplier_toggle").value_or(false);
	damageReceivedMultiplierNoDamage_toggle = cfg.get<bool>("damageReceivedMultiplierNoDamage_toggle").value_or(false);
	GameHook::InitHook("damageReceivedMultiplier", 0x9D4327, &DamageReceivedMultiplierDetour, 8, GameHook::damageReceivedMultiplier);

	witchTimeMultiplier_toggle = cfg.get<bool>("witchTimeMultiplier_toggle").value_or(false);
	witchTimeMultiplier_value = cfg.get<float>("witchTimeMultiplier_value").value_or(1.0f);
	GameHook::InitHook("witchTimeMultiplier", 0x9E1808, &WitchTimeMultiplierDetour, 6, GameHook::witchTimeMultiplier);

	infMagic_toggle = cfg.get<bool>("infMagic_toggle").value_or(false);
	infMagic_value = cfg.get<float>("infMagic_value").value_or(1200.0f);
	GameHook::InitHook("infMagic", 0x8BCE4C, &InfMagicDetour, 8, GameHook::infMagic);

	randomizeSpawns_toggle = cfg.get<bool>("randomizeSpawns_toggle").value_or(false);
	swapSpawns_toggle = cfg.get<bool>("swapSpawns_toggle").value_or(false);
	for (int i = 0; i < (int)swapRules.size(); i++) {
		auto& rule = swapRules[i];
		std::string keyEnabled = "swapRule_" + std::to_string(i) + "_enabled";
		std::string keyTarget = "swapRule_" + std::to_string(i) + "_target";
		std::string keyModifier = "swapRule_" + std::to_string(i) + "_modifier";
		rule.enabled = cfg.get<bool>(keyEnabled).value_or(false);
		rule.targetIndex = cfg.get<int>(keyTarget).value_or(rule.sourceIndex);
		rule.spawnModifier = cfg.get<int>(keyModifier).value_or(-1);
		if (rule.targetIndex < 0 || rule.targetIndex >= (int)spawnTypes.size())
			rule.targetIndex = rule.sourceIndex;
	}
	GameHook::InitHook("viewEntitySpawns", 0x510450, &ViewEntitySpawnsDetour, 8, GameHook::viewEntitySpawns);

	customCameraDistance_toggle = cfg.get<bool>("customCameraDistance_toggle").value_or(false);
	customCameraDistance_value = cfg.get<float>("customCameraDistance_value").value_or(10.0f);
	GameHook::InitHook("customCameraDistance", 0xA941FA, &CustomCameraDistanceDetour, 6, GameHook::customCameraDistance);

	haloDisplay_toggle = cfg.get<bool>("haloDisplay_toggle").value_or(false);
	GameHook::InitHook("haloDisplay", 0x4250F7, &HaloDisplayDetour, 5, GameHook::haloDisplay);

	moveIDSwap_toggle = cfg.get<bool>("moveIDSwap_toggle").value_or(false);
	for (int i = 0; i < maxMoveIDSwaps; ++i) {
		moveIDSwap_toggles[i] = cfg.get<bool>(std::string("moveIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		moveIDSwapSourceMoves[i] = cfg.get<int>(std::string("moveIDSwapSourceMoves[") + std::to_string(i) + "]").value_or(-1);
		moveIDSwapSwappedMoves[i] = cfg.get<int>(std::string("moveIDSwapSwappedMoves[") + std::to_string(i) + "]").value_or(-1);
	}
	GameHook::InitHook("moveIDSwap", 0x4BD053, &MoveIDSwapDetour, 6, GameHook::moveIDSwap);

	customWeaves_toggle = cfg.get<bool>("customWeaves_toggle").value_or(false);
	for (int i = 0; i < customWeaveCount; ++i) {
		customWeave_toggles[i] = cfg.get<bool>(std::string("customWeave_toggles[") + std::to_string(i) + "]").value_or(false);
		customWeaveMoveIDArray[i] = cfg.get<int>(std::string("customWeaveMoveIDArray[") + std::to_string(i) + "]").value_or(-1);
		customWeaveArray[i] = cfg.get<int>(std::string("customWeaveArray[") + std::to_string(i) + "]").value_or(-1);
	}
	GameHook::InitHook("customWeaves", 0x87F270, &CustomWeavesDetour, 6, GameHook::customWeaves);

	stringSwap_toggle = cfg.get<bool>("stringSwap_toggle").value_or(false);
	for (int i = 0; i < maxStringSwaps; ++i) {
		stringIDSwap_toggles[i] = cfg.get<bool>(std::string("stringIDSwap_toggles[") + std::to_string(i) + "]").value_or(false);
		stringIDSwapSourceStrings[i] = cfg.get<int>(std::string("stringIDSwapSourceStrings[") + std::to_string(i) + "]").value_or(-1);
		stringIDSwapDesiredStrings[i] = cfg.get<int>(std::string("stringIDSwapDesiredStrings[") + std::to_string(i) + "]").value_or(-1);
	}
	GameHook::InitHook("punchStringIDSwap", 0x8D2A82, &PunchStringIDSwapDetour, 6, GameHook::punchStringIDSwap);
	GameHook::InitHook("latePunchStringIDSwap", 0x8D2AC4, &LatePunchStringIDSwapDetour, 6, GameHook::latePunchStringIDSwap);
	GameHook::InitHook("kickStringIDSwap", 0x8D2AE5, &KickStringIDSwapDetour, 6, GameHook::kickStringIDSwap);
	GameHook::InitHook("lateKickStringIDSwap", 0x8D2AA3, &LateKickStringIDSwapDetour, 6, GameHook::lateKickStringIDSwap);

	easierMash_toggle = cfg.get<bool>("easierMash_toggle").value_or(false);
	GameHook::InitHook("easierMash", 0x4A8EFF, &EasierMashDetour, 5, GameHook::easierMash);

	initialAngelSlayerFloor_value = cfg.get<int>("initialAngelSlayerFloor_value").value_or(0);
	GameHook::InitHook("initialAngelSlayerFloor", 0x41C8B5, &InitialAngelSlayerFloorDetour, 10, GameHook::initialAngelSlayerFloor);

	pvp_toggle = cfg.get<bool>("pvp_toggle").value_or(false);
	GameHook::InitHook("pvp_1", 0x419262, &PvpDetour1, 6, GameHook::pvp1);
	GameHook::InitHook("pvp_2", 0x8BA9C7, &PvpDetour2, 8, GameHook::pvp2);
	GameHook::InitHook("pvp_3", 0x49A47B, &PvpDetour3, 6, GameHook::pvp3);
	GameHook::InitHook("pvp_4", 0x49A7CB, &PvpDetour4, 6, GameHook::pvp4);

	cameraSelect_toggle = cfg.get<bool>("cameraSelect_toggle").value_or(false);
	cameraSelect_newCameraType = cfg.get<int>("cameraSelect_newCameraType").value_or(0);
	GameHook::InitHook("cameraSelect", 0xAA657B, &CameraSelectDetour, 6, GameHook::cameraSelect);

	customEffectColours_toggle = cfg.get<bool>("customEffectColours_toggle").value_or(false);
	GameHook::InitHook("customEffectColours", 0x5819BB, &CustomEffectColoursDetour, 32, GameHook::customEffectColours);

	cancellableAfterBurner_toggle = cfg.get<bool>("cancellableAfterBurner_toggle").value_or(false);
	GameHook::InitHook("cancellableAfterBurner", 0x95ABD3, &CancellableAfterBurnerDetour, 6, GameHook::cancellableAfterBurner);

	cancellableFallingKick_toggle = cfg.get<bool>("cancellableFallingKick_toggle").value_or(false);
	GameHook::InitHook("cancellableFallingKick", 0x952142, &CancellableFallingKickDetour, 5, GameHook::cancellableFallingKick);
	GameHook::InitHook("cancellableFallingKickDurga", 0x920C44, &CancellableFallingKickDurgaDetour, 8, GameHook::cancellableFallingKickDurga);

	altTeleInput_toggle = cfg.get<bool>("altTeleInput_toggle").value_or(false);
	GameHook::InitHook("altTeleInput", 0x8BE592, &AltTeleInputDetour, 26, GameHook::altTeleInput);

	tauntWithTimeBracelet_toggle = cfg.get<bool>("tauntWithTimeBracelet_toggle").value_or(false);
	GameHook::InitHook("tauntWithTimeBraceletA", 0x9E751A, &TauntWithTimeBraceletADetour, 6, GameHook::tauntWithTimeBraceletA);
	GameHook::InitHook("tauntWithTimeBraceletB", 0x8BE5C2, &TauntWithTimeBraceletBDetour, 6, GameHook::tauntWithTimeBraceletB);

	disableSlowmo_toggle = cfg.get<bool>("disableSlowmo_toggle").value_or(false);
	GameHook::InitHook("disableSlowmo", 0x513C1E, &DisableSlowmoDetour, 5, GameHook::disableSlowmo);

	lowerDivekick_toggle = cfg.get<bool>("lowerDivekick_toggle").value_or(false);
	GameHook::InitHook("lowerDivekick", 0x9E93B9, &LowerDivekickDetour, 7, GameHook::lowerDivekick);

	dualAfterBurner_toggle = cfg.get<bool>("dualAfterBurner_toggle").value_or(false);
	GameHook::InitHook("dualAfterBurner", 0x94CAAF, &DualAfterBurnerDetour, 5, GameHook::dualAfterBurner);

	longerPillowTalkCharge_toggle = cfg.get<bool>("longerPillowTalkCharge_toggle").value_or(false);
	GameHook::InitHook("longerPillowTalkCharge", 0x4CCCA0, &LongerPillowTalkChargeDetour, 6, GameHook::longerPillowTalkCharge);

	alwaysWitchTime_toggle = cfg.get<bool>("alwaysWitchTime_toggle").value_or(false);
	GameHook::InitHook("alwaysWitchTime", 0x8EF527, &AlwaysWitchTimeDetour, 8, GameHook::alwaysWitchTime);

	omnicancelTele_toggle = cfg.get<bool>("omnicancelTele_toggle").value_or(false);
	GameHook::InitHook("omnicancelTele", 0x8BE5B6, &OmnicancelTeleDetour, 7, GameHook::omnicancelTele);

	teleportComboAction_toggle = cfg.get<bool>("teleportComboAction_toggle").value_or(false);
	GameHook::InitHook("teleportComboAction", 0x9A0020, &TeleportComboActionDetour, 6, GameHook::teleportComboAction);

	thirdAccessoryMenu_toggle = cfg.get<bool>("thirdAccessoryMenu_toggle").value_or(false);
	GameHook::InitHook("fixThirdAccessory", 0x97ED07, &FixThirdAccessoryDetour, 5, GameHook::fixThirdAccessory);
	GameHook::InitHook("thirdAccessoryMenu", 0xB1E0AC, &ThirdAccessoryMenuDetour, 9, GameHook::thirdAccessoryMenu);

	GameHook::InitHook("pl0012", 0x9F5AF0, &pl0012Detour, 0, GameHook::pl0012);
	GameHook::InitHook("pl0031", 0x9FC890, &pl0031Detour, 0, GameHook::pl0031);
	GameHook::InitHook("pl004c", 0xA17420, &pl004cDetour, 0, GameHook::pl004c);
	InitSwapRules();
#endif
	GameHook::UpdateHooks();
}
