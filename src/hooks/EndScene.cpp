#include <pch.h>
#include <base.h>
#include "bayohook.hpp"
#include "LicenseStrings.hpp"
#include <array>

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

inline void under_line(const ImColor& col) {
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    min.y = max.y;
    ImGui::GetWindowDrawList()->AddLine(min, max, col, 1.0f);
}

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL; // disable data/imgui.ini
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

        D3DDEVICE_CREATION_PARAMETERS deviceParams = { 0 };

        pDevice->GetCreationParameters(&deviceParams);

		Data::oWndProc = (WndProc_t)SetWindowLongPtr(deviceParams.hFocusWindow, WNDPROC_INDEX, (LONG_PTR)Hooks::WndProc);

		ImGui_ImplWin32_Init(deviceParams.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;

        BayoHook::InitializeDetours();
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
        ImGui::Begin("BayoHook 0.3", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

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

                ImGui::Checkbox("Outgoing Damage Multiplier ##OutgoingDamageMultiplierToggle", &BayoHook::outgoingDamageMultiplier_toggle);
                //ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##OutgoingDamageMultiplierInputFloat", &BayoHook::outgoingDamageMultiplierMult, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();

                if (ImGui::Checkbox("Deal No Damage ##DealNoDamageToggle", &BayoHook::enemyHP_no_damage_toggle)) {
                    BayoHook::enemyHP_one_hit_kill_toggle = false;
                }

                if (ImGui::Checkbox("One Hit Kill ##OneHitKillToggle", &BayoHook::enemyHP_one_hit_kill_toggle)) {
                    BayoHook::enemyHP_no_damage_toggle = false;
                }

				if (ImGui::Checkbox("Take No Damage", &BayoHook::takeNoDamage_toggle)) {
					BayoHook::TakeNoDamage(BayoHook::takeNoDamage_toggle);
				}

                ImGui::Checkbox("Inf Magic ##InfMagicToggle", &BayoHook::inf_magic_toggle);

				//if (ImGui::Button("Detach"))
				//	Data::ToDetach = true;
				ImGui::EndChild();
				ImGui::EndTabItem();
			}

            if (ImGui::BeginTabItem("Character")) {
                ImGui::BeginChild("CharacterChild");

                if (ImGui::Checkbox("Infinite Jumps ##InfJumpsToggle", &BayoHook::infJumps_toggle)) {
                    BayoHook::InfJumps(BayoHook::infJumps_toggle);
                }

                ImGui::Checkbox("Witch Time Multiplier ##WitchTimeToggle", &BayoHook::witchTimeMultiplier_toggle);
                help_marker("Adjust how long Witch Time lasts");
                //ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##WitchTimeMultiplier", &BayoHook::witchTimeMultiplier, 0, 0, "%.1f");
                ImGui::PopItemWidth();

                ImGui::Text("Third Accessory");
                //ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                if (ImGui::InputInt("##ThirdAccessoryInputInt", &BayoHook::thirdAccessory, 1, 100)) {
                    BayoHook::SetThirdAccessory(BayoHook::thirdAccessory);
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                
                switch (BayoHook::thirdAccessory)
                {
                case 0:
                    ImGui::Text("None");
                    break;
                case 1:
                    ImGui::Text("Sergey's Lover");
                    break;
                case 2:
                    ImGui::Text("Infernal Communicator");
                    break;
                case 3:
                    ImGui::Text("Pulley's Butterfly");
                    break;
                case 4:
                    ImGui::Text("Selene's Light");
                    break;
                case 5:
                    ImGui::Text("Star of Dinéta");
                    break;
                case 6:
                    ImGui::Text("Evil Harvest Rosary");
                    break;
                case 7:
                    ImGui::Text("Gaze of Despair");
                    break;
                case 8:
                    ImGui::Text("Moon of Mahaa-Kalaa");
                    break;
                case 9:
                    ImGui::Text("Eternal Testimony");
                    break;
                case 10:
                    ImGui::Text("Bracelet of Time");
                    break;
                case 11:
                    ImGui::Text("Climax Brace");
                    break;
                case 12:
                    ImGui::Text("Immortal Marionette");
                    break;
                default:
                    ImGui::Text("");
                    break;
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
                if (ImGui::InputFloat("##PlayerMPInputFloat", &BayoHook::playerMagic, 1, 100, "%.0f")) {
                    BayoHook::SetMagic(BayoHook::playerMagic);
                }

                ImGui::Text("Remaining Witch Time Duration");
                if (ImGui::InputFloat("##RemainingWitchTimeDurationInputFloat", &BayoHook::remainingWitchTimeDuration, 10, 100, "%.0f")) {
                    BayoHook::SetRemainingWitchTimeDuration(BayoHook::remainingWitchTimeDuration);
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

                ImGui::Checkbox("Force Input Type", &BayoHook::inputIcons_toggle);
                help_marker("0 keyboard, 1 gamepad");
                if (BayoHook::inputIcons_toggle) {
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##InputIconsInputInt", &BayoHook::inputIconsValue, 1, 100);
                    ImGui::PopItemWidth();
                }

                ImGui::Checkbox("Camera Distance Multiplier ##CameraDistanceMultiplierToggle", &BayoHook::customCameraDistance_toggle);
                //ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceMultiplierInputFloat", &BayoHook::customCameraDistanceMultiplierMult, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();

                ImGui::Text("Character Select");
                help_marker("Set while in costume select\nIf your game freezes at the end of a fight, flick the value back to default");
                //ImGui::SameLine();
                ImGui::PushItemWidth(inputItemWidth);
                if (ImGui::InputInt("##CharacterSelectInputInt", &BayoHook::currentCharacter, 1, 100)) {
                    BayoHook::SetCurrentCharacter(BayoHook::currentCharacter);
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                switch (BayoHook::currentCharacter) {
                case 0:
                    ImGui::Text("Bayonetta");
                    break;
                case 1:
                    ImGui::Text("Jeanne");
                    break;
                default:
                    ImGui::Text("");
                    break;
                }

                if (ImGui::Checkbox("HUD Display", &BayoHook::hudDisplay)) {
                    BayoHook::SetHudDisplay(BayoHook::hudDisplay);
                }

                ImGui::Checkbox("Enemy HP in Halo Display", &BayoHook::haloDisplay_toggle);

                ImGui::Checkbox("Force Summoning Clothes ##LessClothesToggle", &BayoHook::lessClothes_toggle);
                help_marker("Only works on outfits that have this function");

                ImGui::Checkbox("Animation Swap Test ##AnimationSwapTestToggle", &BayoHook::animSwap_toggle);
                help_marker("Do the move you want to see, hit the first button\nDo the move you want to replace, hit the second button");
                if (BayoHook::animSwap_toggle) {
                    ImGui::Text("Current Anim ID");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##CurrentAnimIDInputInt", &BayoHook::animSwapCurrentAnim);
                    ImGui::PopItemWidth();

                    ImGui::Text("Desired Anim ID");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##DesiredAnimID1InputInt", &BayoHook::animSwapDesiredAnim1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Anim ID as desired")) {
                        BayoHook::animSwapDesiredAnim1 = BayoHook::animSwapCurrentAnim;
                    }

                    ImGui::Text("Source Anim ID");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##SourceAnimID1InputInt", &BayoHook::animSwapSourceAnim1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Anim ID as source")) {
                        BayoHook::animSwapSourceAnim1 = BayoHook::animSwapCurrentAnim;
                    }
                }

                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Credits")) {
                ImGui::BeginChild("CreditsChild");

                struct ImGuiURL {
                    std::string text;
                    std::string url;
                    const ImVec4 color_hover{ 0.356f, 0.764f, 0.960f, 1.00f };
                    const ImVec4 color_regular{ 0.950f, 0.960f, 0.980f, 1.00f };

                    void draw() {

                        ImGui::TextColored(color_regular, text.c_str());
                        if (ImGui::IsItemHovered()) {
                            under_line(color_hover);
                        }
                        if (ImGui::IsItemClicked()) {
                            ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
                        }
                    }
                };

                ImGuiURL repo{ "https://github.com/SSSiyan/BayoHook", "https://github.com/SSSiyan/BayoHook" };
                repo.draw();

                ImGui::Separator();

                ImGui::Text("This trainer was made by");
                static std::array<ImGuiURL, 5> links1{
                    ImGuiURL { "SSSiyan", "https://twitter.com/sssiyan" },
                    ImGuiURL { "GarudaKK", "https://www.youtube.com/@GarudaPSN" },
                    ImGuiURL { "CreativeHandle", "https://twitter.com/CreativeHandler" },
                    ImGuiURL { "deepdarkkapustka", "https://www.youtube.com/@mstislavcapusta7573" },
                    ImGuiURL { "TheDarkness", "https://steamcommunity.com/id/TheDarkness704/" },
                };
                for (auto& link : links1) {
                    link.draw();
                }

                ImGui::Separator();

                ImGui::Text("This trainer was made using");
                static std::array<ImGuiURL, 3> links2{
                    ImGuiURL { "Dear ImGui", "https://github.com/ocornut/imgui" },
                    ImGuiURL { "minhook", "https://github.com/TsudaKageyu/minhook" },
                    ImGuiURL { "DX9 BaseHook", "https://github.com/rdbo/DX9-BaseHook" },
                };
                for (auto& link : links2) {
                    link.draw();
                }

                ImGui::Separator();
                ImGui::Text("Licenses");
                struct License {
                    std::string name;
                    std::string text;
                };
                static std::array<License, 2> licenses{
                    License{ "imgui", license::imgui },
                    License{ "minhook", license::minhook },
                };
                for (const auto& license : licenses) {
                    if (ImGui::CollapsingHeader(license.name.c_str())) {
                        ImGui::TextWrapped(license.text.c_str());
                    }
                }

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
