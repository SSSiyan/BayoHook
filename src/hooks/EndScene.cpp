#include <pch.h>
#include <base.h>
#include "GameHook.hpp"
#include <array>
#include "misc/FontRoboto.cpp"

#ifndef SPEEDRUN_BUILD
static void UpdateGameSpeed() {
	static LARGE_INTEGER s_lastQPC = {};
	float gameFpsDelta = 16.6667f;
	LARGE_INTEGER now, freq;
	QueryPerformanceCounter(&now);
	QueryPerformanceFrequency(&freq);
	if (s_lastQPC.QuadPart > 0) {
		INT64 elapsed = now.QuadPart - s_lastQPC.QuadPart;
		gameFpsDelta = (float)(elapsed * 1000.0 / (double)freq.QuadPart);
	}
	s_lastQPC = now;
	GameHook::deltaTime = gameFpsDelta;
	GameHook::deltaSpeed = gameFpsDelta / 16.6667f;
	GameHook::deltaSpeed2 = GameHook::deltaSpeed * 2.0f;
	GameHook::deltaSpeed3 = GameHook::deltaSpeed * 3.0f;
}

/*static void SetGameSpeed() {
	float* gameSpeed = (float*)0xEF6588;
	*gameSpeed = GameHook::deltaSpeed;
}*/
#endif

static void HotkeyStuff() {
	if (GameHook::hk_toggle_menu->check(GameHook::g_input)/* || GameHook::pad_hk_toggle_menu->check(GameHook::g_input)*/) {
		Base::Data::ShowMenu = !Base::Data::ShowMenu;
		ImGui::GetIO().MouseDrawCursor = Base::Data::ShowMenu;
		GameHook::disableClicking_toggle = Base::Data::ShowMenu;
		GameHook::DisableClicking(GameHook::disableClicking_toggle);
	}

	if (GameHook::hk_enemy_no_damage->check(GameHook::g_input)) {
		GameHook::enemyHPNoDamage_toggle = !GameHook::enemyHPNoDamage_toggle;
		GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
		if (GameHook::enemyHPNoDamage_toggle && GameHook::enemyHPOneHitKill_toggle) {
			GameHook::enemyHPOneHitKill_toggle = false;
			GameHook::DisplayMessageText("Enemy One Hit Kill", false);
		}
		GameHook::DisplayMessageText("Enemy Takes No Damage", GameHook::enemyHPNoDamage_toggle);
	}
	if (GameHook::hk_player_no_damage->check(GameHook::g_input)) {
		GameHook::damageReceivedMultiplierNoDamage_toggle = !GameHook::damageReceivedMultiplierNoDamage_toggle;
		GameHook::DisplayMessageText("Player Takes No Damage", GameHook::damageReceivedMultiplierNoDamage_toggle);
	}
	if (GameHook::hk_enemy_one_hit_kill->check(GameHook::g_input)) {
		GameHook::enemyHPOneHitKill_toggle = !GameHook::enemyHPOneHitKill_toggle;
		if (GameHook::enemyHPOneHitKill_toggle && GameHook::enemyHPNoDamage_toggle) {
			GameHook::enemyHPNoDamage_toggle = false;
			GameHook::DisableKilling(false);
			GameHook::DisplayMessageText("Enemy Takes No Damage", false);
		}
		GameHook::DisplayMessageText("Enemy One Hit Kill", GameHook::enemyHPOneHitKill_toggle);
	}
	if (GameHook::hk_inf_jumps->check(GameHook::g_input)) {
		GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
		GameHook::InfJumps(GameHook::infJumps_toggle);
		GameHook::DisplayMessageText("Infinite Jumps", GameHook::infJumps_toggle);
	}
	if (GameHook::hk_no_clip->check(GameHook::g_input)) {
		GameHook::noClip_toggle = !GameHook::noClip_toggle;
		GameHook::NoClip(GameHook::noClip_toggle);
		GameHook::DisplayMessageText("No Clip", GameHook::noClip_toggle);
	}
	if (GameHook::hk_force_summoning_clothes->check(GameHook::g_input)) {
		GameHook::forceSummoningClothes_toggle = !GameHook::forceSummoningClothes_toggle;
		GameHook::ForceSummoningClothes(GameHook::forceSummoningClothes_toggle);
		GameHook::DisplayMessageText("Force Summoning Clothes", GameHook::forceSummoningClothes_toggle);
	}
	if (GameHook::hk_end_current_fight->check(GameHook::g_input)) {
		if (GameHook::GetLocalPlayer()) {
			*(int*)0x51ADE44 = 0x10000000;
			GameHook::DisplayMessageText("End Current Fight");
			GameHook::current_fight_timer = 5;
		}
	}
	if (GameHook::current_fight_timer > 0) {
		GameHook::current_fight_timer--;
		if (GameHook::current_fight_timer <= 0) {
			GameHook::current_fight_timer = 0;
			*(int*)0x51ADE44 = 0;
		}
	}

	DWORD foregroundPid = 0;
	HWND hwnd = GetForegroundWindow();
	GetWindowThreadProcessId(hwnd, &foregroundPid);
	if (foregroundPid == GetCurrentProcessId()) {
		if (GameHook::hk_save_state->check(GameHook::g_input) && GameHook::saveStatesHotkeys_toggle) GameHook::SaveStates_SaveState();
		if (GameHook::hk_load_state->check(GameHook::g_input) && GameHook::saveStatesHotkeys_toggle) GameHook::SaveStates_LoadState();
		if (GameHook::hk_spawn_affinity_spear->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20000, 1, 0);
		if (GameHook::hk_spawn_affinity_trumpet->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20000, 2, 0);
		if (GameHook::hk_spawn_applaud_spear->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20000, 4, 0);
		if (GameHook::hk_spawn_applaud_greatsword->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20000, 5, 0);
		if (GameHook::hk_spawn_enchant->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20030, 0, 0);
		if (GameHook::hk_spawn_ardor_greatsword->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20004, 0, 0);
		if (GameHook::hk_spawn_ardor_axe->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20004, 1, 0);
		if (GameHook::hk_spawn_affinity_laser->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20002, 0, 0);
		if (GameHook::hk_spawn_fearless->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20050, 0, 0);
		if (GameHook::hk_spawn_fairness->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20051, 0, 0);
		if (GameHook::hk_spawn_harmony->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20060, 0, 0);
		if (GameHook::hk_spawn_brave->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20073, 0, 0);
		if (GameHook::hk_spawn_joy->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20080, 0, 0);
		if (GameHook::hk_spawn_grace->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20040, 0, 0);
		if (GameHook::hk_spawn_glory->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20041, 0, 0);
		if (GameHook::hk_spawn_gracious->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20042, 0, 0);
		if (GameHook::hk_spawn_glorious->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20043, 0, 0);
		if (GameHook::hk_spawn_kinship->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x200A0, 0, 0);
		if (GameHook::hk_spawn_beloved->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20074, 0, 0);
		if (GameHook::hk_spawn_golem->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20090, 0, 0);
		if (GameHook::hk_spawn_fortitudo->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x200B0, 0, 0);
		if (GameHook::hk_spawn_balder->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x20500, 0, 0);
		if (GameHook::hk_spawn_jeanne_formal->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x21002, 0, 0);
		if (GameHook::hk_spawn_bayonetta->check(GameHook::g_input))GameHook::EasySpawnEntityFromHotkey(0x21003, 0, 0);
		GameHook::g_input.update();
	}
}

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice) {
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui) {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

        io.IniFilename = NULL; // disable imgui.ini
		GameHook::ImGuiStyle();
		
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

        D3DDEVICE_CREATION_PARAMETERS deviceParams = { 0 };

        pDevice->GetCreationParameters(&deviceParams);

		Data::oWndProc = (WndProc_t)SetWindowLongPtr(deviceParams.hFocusWindow, WNDPROC_INDEX, (LONG_PTR)Hooks::WndProc);
		
		RECT rect;
		::GetClientRect(deviceParams.hFocusWindow, &rect);
		int height = rect.bottom - rect.top;

		ImGui_ImplWin32_Init(deviceParams.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;
		float y_factor = ((float)height/720.0f) * GameHook::windowScalingFactor;
		float dpi = ImGui_ImplWin32_GetDpiScaleForHwnd(deviceParams.hFocusWindow);
		
		static ImFontConfig cfg;
		cfg.OversampleH = 2;
		cfg.OversampleV = 1;
		cfg.SizePixels = std::roundf(16.0f * y_factor * dpi);
		io.Fonts->AddFontDefault(&cfg);
		GameHook::bayoHookFont = io.Fonts->AddFontFromMemoryCompressedBase85TTF(roboto_medium_compressed_data_base85);
		ImGui::GetStyle().ScaleAllSizes(y_factor * dpi);

        GameHook::InitializeDetours();
		GameHook::LoadPatches(GameHook::cfg);
		GameHook::LoadDetours(GameHook::cfg);
		GameHook::LoadSystem(GameHook::cfg);
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::PushFont(GameHook::bayoHookFont, GameHook::bayoHookFontSize);

	ImGui::SetNextWindowPos(ImVec2(0, 0)), ImGuiCond_Always;
	ImGui::SetNextWindowSize(ImVec2(400, 500)), ImGuiCond_Always;
	ImGui::Begin("Background window", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground);

#ifndef SPEEDRUN_BUILD
	HotkeyStuff();
	UpdateGameSpeed();
	/*if (GameHook::linkGameToDelta_toggle) {
		SetGameSpeed();
	}*/
#endif

	GameHook::BackgroundImGui();
	ImGui::End();

	if (GameHook::showComboUI_toggle) {
		float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
		int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
		if ((comboMultiplierValue > 9.9f && comboPointsValue > 0) || GameHook::testComboUI_toggle && Data::ShowMenu) {
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * GameHook::comboUI_X, ImGui::GetIO().DisplaySize.y * GameHook::comboUI_Y), ImGuiCond_Always);
			ImGui::Begin("Combo Multiplier Panel", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
			auto style = ImGui::GetStyle();
			ImGui::PushFont(NULL, 36.0f);
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "%.1f", comboMultiplierValue);
			ImGui::PopFont();
			ImGui::End();
		}
	}
	GameHook::GameTick();
	ImGui::SetNextWindowPos(ImVec2(0, 0)), ImGuiCond_Always;
	// ImGui::SetNextWindowSize(ImVec2(GameHook::windowWidth, GameHook::windowHeightHack)), ImGuiCond_Always;
	if (Data::ShowMenu) {
		ImGui::Begin(GameHook::dllName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        GameHook::GameImGui();
		ImGui::End();
	}

	ImGui::PopFont();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	if(Data::ToDetach)
		Base::Detach();
	return pDevice->EndScene();
}
