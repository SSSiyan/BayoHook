#include <pch.h>
#include <base.h>
#include "gamehook.hpp"
#include <array>
#include "misc/FontRoboto.cpp"

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
		GameHook::bayoHookFontSize = GameHook::cfg.get<float>("bayoHookFontSize").value_or(16.0f);
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
		GameHook::onConfigLoad(GameHook::cfg);
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
	GameHook::BackgroundImGui();
	ImGui::End();

	if (GameHook::showComboUI_toggle) {
		float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
		int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
		if (comboMultiplierValue > 9.9f && comboPointsValue > 0) {
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
