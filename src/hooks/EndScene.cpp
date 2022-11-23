//#include <pch.h>
#include <base.h>
#include "bayohook.hpp"

utils::Config cfg{ "bayo_hook.cfg" };
static float inputItemWidth = 100.0f;

void help_marker(const char* desc) {
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

        // 4hook styling
        ImGui::GetStyle().FrameRounding = 2.5f;
        ImGui::GetStyle().GrabRounding = 3.0f;
        auto& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(6, 4);
        style.WindowRounding = 6.0f;
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_Button] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.25f, 0.29f, 0.95f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.0078f, 0.53f, 0.8196f, 0.95f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.4588f, 0.45880f, 0.4588f, 0.35f);
		
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;

		// get process ID and module base address
		// BayoHook::_hook(); // I think this isn't needed in a dll?

        BayoHook::InitializeDetours();

		// load settings, must happen after hook
		BayoHook::onConfigLoad(cfg);
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
        ImGui::Begin("BayoHook 0.1", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        BayoHook::Update();
        HasDoneOnceMenuOff = false;
        if (HasDoneOnceMenuOn == false) {
            ImGui::GetIO().MouseDrawCursor = true;
            BayoHook::disableClicking_toggle = true;
            BayoHook::DisableClicking(BayoHook::disableClicking_toggle);
            HasDoneOnceMenuOn = true;
        }

        if (ImGui::Button("Save config")) {
            BayoHook::onConfigSave(cfg);
        }

		if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
			if (ImGui::BeginTabItem("General")) {
				ImGui::BeginChild("GeneralChild");

				if (ImGui::Checkbox("Take No Damage", &BayoHook::takeNoDamage_toggle)) {
					BayoHook::TakeNoDamage(BayoHook::takeNoDamage_toggle);
				}

                if (ImGui::Checkbox("Deal No Damage ##DealNoDamageToggle", &BayoHook::enemyHP_no_damage_toggle)) {
                    BayoHook::enemyHP_one_hit_kill_toggle = false;
                }
                if (ImGui::Checkbox("One Hit Kill ##OneHitKillToggle", &BayoHook::enemyHP_one_hit_kill_toggle)) {
                    BayoHook::enemyHP_no_damage_toggle = false;
                }

                ImGui::Checkbox("Inf Magic ##InfMagicToggle", &BayoHook::inf_magic_toggle);

				//if (ImGui::Button("Detach"))
				//	Data::ToDetach = true;
				ImGui::EndChild();
				ImGui::EndTabItem();
			}

            if (ImGui::BeginTabItem("Character")) {
                ImGui::BeginChild("CharacterChild");
                ImGui::Checkbox("Witch Time Multiplier ##WitchTimeToggle", &BayoHook::witchTimeMultiplier_toggle);
                ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##WitchTimeMultiplier", &BayoHook::witchTimeMultiplier, 0, 0, "%.1f");
                ImGui::PopItemWidth();
                help_marker("Adjust how long Witch Time lasts");
                if (ImGui::Checkbox("Infinite Jumps ##InfJumpsToggle", &BayoHook::infJumps_toggle)) {
                    BayoHook::InfJumps(BayoHook::infJumps_toggle);
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Stats")) {
                ImGui::BeginChild("StatsChild");
                ImGui::Text("Player Position");
                if (ImGui::InputFloat3("##Player Position", BayoHook::xyzpos)) {
                    BayoHook::SetXYZPos(BayoHook::xyzpos[0], BayoHook::xyzpos[1], BayoHook::xyzpos[2]);
                }
                ImGui::Text("Halos");
                if (ImGui::InputInt("##HaloInputInt", &BayoHook::halos, 1, 100)) {
                    BayoHook::SetHalos(BayoHook::halos);
                }
                ImGui::Text("Chapters Played");
                if (ImGui::InputInt("##ChapterInputInt", &BayoHook::chaptersPlayed, 1, 100)) {
                    BayoHook::SetChaptersPlayed(BayoHook::chaptersPlayed);
                }
                ImGui::Text("Player HP");
                if (ImGui::InputInt("##PlayerHPInputInt", &BayoHook::playerHealth, 1, 100)) {
                    BayoHook::SetHealth(BayoHook::playerHealth);
                }
                ImGui::Text("Player MP");
                if (ImGui::InputFloat("##PlayerMPInputFloat", &BayoHook::playerMagic, 1, 100)) {
                    BayoHook::SetMagic(BayoHook::playerMagic);
                }
                ImGui::Text("Combo Points");
                if (ImGui::InputInt("##ComboPointsInputInt", &BayoHook::comboPoints, 1, 100)) {
                    BayoHook::SetComboPoints(BayoHook::comboPoints);
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("System")) {
                ImGui::BeginChild("SystemChild");
                if (ImGui::Checkbox("Focus Patch", &BayoHook::focusPatch_toggle)) {
                    BayoHook::FocusPatch(BayoHook::focusPatch_toggle);
                }
                help_marker("Play while tabbed out");

                ImGui::EndChild();
                ImGui::EndTabItem();
            }

			ImGui::EndTabBar();
		}

		ImGui::End();
	}
    else {
        HasDoneOnceMenuOn = false;
        if (HasDoneOnceMenuOff == false) {
            ImGui::GetIO().MouseDrawCursor = false;
            BayoHook::disableClicking_toggle = false;
            BayoHook::DisableClicking(BayoHook::disableClicking_toggle);
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