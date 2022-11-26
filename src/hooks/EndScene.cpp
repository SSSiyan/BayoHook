#include <pch.h>
#include <base.h>
#include "gamehook.hpp"
#include <array>

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

		ImGui_ImplWin32_Init(deviceParams.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;

        GameHook::InitializeDetours();
		GameHook::onConfigLoad(GameHook::cfg);
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0)), ImGuiCond_Always;
	ImGui::SetNextWindowSize(ImVec2(400, 500)), ImGuiCond_Always;

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

		ImGui::Begin(GameHook::dllname, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        // GameHook::GameImGui();

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
	return Data::oEndScene(pDevice);
}
