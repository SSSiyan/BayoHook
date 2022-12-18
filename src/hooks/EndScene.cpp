#include <pch.h>
#include <base.h>
#include "gamehook.hpp"
#include <array>
float GameHook::windowHeightHack = 0.0f;
float GameHook::maxWindowHeight = 0.0f;
float GameHook::windowHeightBorder = 0.0f;
float GameHook::windowWidth = 500.0f;
float GameHook::windowScalingFactor = 1.0f;

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui)
	{
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
		cfg.SizePixels = std::roundf(13.0f * y_factor * dpi);
		io.Fonts->AddFontDefault(&cfg);
		ImGui::GetStyle().ScaleAllSizes(y_factor * dpi);

        GameHook::InitializeDetours();
		GameHook::onConfigLoad(GameHook::cfg);
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	GameHook::maxWindowHeight = ImGui::GetIO().DisplaySize.y * 0.9f;
	//GameHook::windowHeightBorder = ImGui::GetIO().DisplaySize.y * 0.08f;
	GameHook::windowHeightBorder = 100.0f;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0)), ImGuiCond_Always;
	ImGui::SetNextWindowSize(ImVec2(400, 500)), ImGuiCond_Always;
	ImGui::Begin("Background window", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground);
	GameHook::BackgroundImGui();
	ImGui::End();

	if (GameHook::showComboUI_toggle) {
		float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
		int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
		if (comboMultiplierValue > 9.9f && comboPointsValue > 0) {
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * GameHook::comboUI_X, ImGui::GetIO().DisplaySize.y * GameHook::comboUI_Y), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(100, 50)), ImGuiCond_Always;
			ImGui::Begin("Combo Multiplier Panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowFontScale(3.0f);
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "%.1f", comboMultiplierValue);
			ImGui::SetWindowFontScale(1.0f);
			ImGui::End();
		}
	}
		
	ImGui::SetNextWindowPos(ImVec2(0, 0)), ImGuiCond_Always;
	//ImGui::SetNextWindowSize(ImVec2(30.0f * ImGui::GetFontSize(), 30.0f * ImGui::GetFontSize())), ImGuiCond_Always; // 450, 500
	ImGui::SetNextWindowSize(ImVec2(40.0f * ImGui::GetFontSize(), GameHook::windowHeightHack)), ImGuiCond_Always; // 450, 500
    static bool HasDoneOnceMenuOn = false;
    static bool HasDoneOnceMenuOff = false;
	if (Data::ShowMenu) {
        HasDoneOnceMenuOff = false;
        if (HasDoneOnceMenuOn == false) {
            ImGui::GetIO().MouseDrawCursor = true;
            GameHook::disableClicking_toggle = true; // bayo
            GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
            HasDoneOnceMenuOn = true;
        }
		ImGui::Begin(GameHook::dllName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        GameHook::GameImGui();
		ImGui::End();
	}
    else {
        HasDoneOnceMenuOn = false;
        if (HasDoneOnceMenuOff == false) {
            ImGui::GetIO().MouseDrawCursor = false;
            GameHook::disableClicking_toggle = false; // bayo
            GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
            HasDoneOnceMenuOff = true;
        }
    }

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	if(Data::ToDetach)
		Base::Detach();
	return pDevice->EndScene();
}
