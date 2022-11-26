#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>

//utils::Config GameHook::cfg{ "bayo_hook.cfg" };
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

void GameHook::ImGuiStyle(void) {
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
}

void GameHook::GameImGui(void) {
    ImGui::Begin("BayoHook 0.3", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    GameHook::Update(); // update value displays

    if (ImGui::Button("Save config")) {
        GameHook::onConfigSave(GameHook::cfg);
    }

    if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("General")) {
            ImGui::BeginChild("GeneralChild");

            ImGui::Checkbox("Outgoing Damage Multiplier ##OutgoingDamageMultiplierToggle", &GameHook::outgoingDamageMultiplier_toggle);
            //ImGui::SameLine();
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputFloat("##OutgoingDamageMultiplierInputFloat", &GameHook::outgoingDamageMultiplierMult, 0.1f, 1, "%.1f");
            ImGui::PopItemWidth();

            if (ImGui::Checkbox("Deal No Damage ##DealNoDamageToggle", &GameHook::enemyHP_no_damage_toggle)) {
                GameHook::enemyHP_one_hit_kill_toggle = false;
            }

            if (ImGui::Checkbox("One Hit Kill ##OneHitKillToggle", &GameHook::enemyHP_one_hit_kill_toggle)) {
                GameHook::enemyHP_no_damage_toggle = false;
            }

            if (ImGui::Checkbox("Take No Damage", &GameHook::takeNoDamage_toggle)) {
                GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
            }

            ImGui::Checkbox("Inf Magic ##InfMagicToggle", &GameHook::inf_magic_toggle);

            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Character")) {
            ImGui::BeginChild("CharacterChild");

            if (ImGui::Checkbox("Infinite Jumps ##InfJumpsToggle", &GameHook::infJumps_toggle)) {
                GameHook::InfJumps(GameHook::infJumps_toggle);
            }

            ImGui::Checkbox("Witch Time Multiplier ##WitchTimeToggle", &GameHook::witchTimeMultiplier_toggle);
            help_marker("Adjust how long Witch Time lasts");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputFloat("##WitchTimeMultiplier", &GameHook::witchTimeMultiplier, 0, 0, "%.1f");
            ImGui::PopItemWidth();

            ImGui::Text("Third Accessory");
            ImGui::PushItemWidth(inputItemWidth);
            if (ImGui::InputInt("##ThirdAccessoryInputInt", &GameHook::thirdAccessory, 1, 100)) {
                GameHook::SetThirdAccessory(GameHook::thirdAccessory);
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();

            switch (GameHook::thirdAccessory)
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
            if (ImGui::InputFloat3("##Player Position", GameHook::xyzpos)) {
                GameHook::SetXYZPos(GameHook::xyzpos[0], GameHook::xyzpos[1], GameHook::xyzpos[2]);
            }

            ImGui::Text("Halos");
            if (ImGui::InputInt("##HaloInputInt", &GameHook::halos, 1, 100)) {
                GameHook::SetHalos(GameHook::halos);
            }

            ImGui::Text("Chapters Played");
            if (ImGui::InputInt("##ChapterInputInt", &GameHook::chaptersPlayed, 1, 100)) {
                GameHook::SetChaptersPlayed(GameHook::chaptersPlayed);
            }

            ImGui::Text("Player HP");
            if (ImGui::InputInt("##PlayerHPInputInt", &GameHook::playerHealth, 1, 100)) {
                GameHook::SetHealth(GameHook::playerHealth);
            }

            ImGui::Text("Player MP");
            if (ImGui::InputFloat("##PlayerMPInputFloat", &GameHook::playerMagic, 1, 100, "%.0f")) {
                GameHook::SetMagic(GameHook::playerMagic);
            }

            ImGui::Text("Remaining Witch Time Duration");
            if (ImGui::InputFloat("##RemainingWitchTimeDurationInputFloat", &GameHook::remainingWitchTimeDuration, 10, 100, "%.0f")) {
                GameHook::SetRemainingWitchTimeDuration(GameHook::remainingWitchTimeDuration);
            }

            ImGui::Text("Combo Points");
            if (ImGui::InputInt("##ComboPointsInputInt", &GameHook::comboPoints, 1, 100)) {
                GameHook::SetComboPoints(GameHook::comboPoints);
            }

            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("System")) {
            ImGui::BeginChild("SystemChild");

            if (ImGui::Checkbox("Focus Patch", &GameHook::focusPatch_toggle)) {
                GameHook::FocusPatch(GameHook::focusPatch_toggle);
            }
            help_marker("Play while tabbed out");

            ImGui::Checkbox("Force Input Type", &GameHook::inputIcons_toggle);
            help_marker("0 keyboard, 1 gamepad");
            if (GameHook::inputIcons_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##InputIconsInputInt", &GameHook::inputIconsValue, 1, 100);
                ImGui::PopItemWidth();
            }

            ImGui::Checkbox("Camera Distance Multiplier ##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputFloat("##CustomCameraDistanceMultiplierInputFloat", &GameHook::customCameraDistanceMultiplierMult, 0.1f, 1, "%.1f");
            ImGui::PopItemWidth();

            ImGui::Text("Character Select");
            help_marker("Set while in costume select\nIf your game freezes at the end of a fight, flick the value back to default");
            ImGui::PushItemWidth(inputItemWidth);
            if (ImGui::InputInt("##CharacterSelectInputInt", &GameHook::currentCharacter, 1, 100)) {
                GameHook::SetCurrentCharacter(GameHook::currentCharacter);
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();
            switch (GameHook::currentCharacter) {
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

            if (ImGui::Checkbox("HUD Display", &GameHook::hudDisplay)) {
                GameHook::SetHudDisplay(GameHook::hudDisplay);
            }

            ImGui::Checkbox("Enemy HP in Halo Display", &GameHook::haloDisplay_toggle);

            ImGui::Checkbox("Force Summoning Clothes ##LessClothesToggle", &GameHook::lessClothes_toggle);
            help_marker("Only works on outfits that have this function");

            ImGui::Checkbox("Animation Swap Test ##AnimationSwapTestToggle", &GameHook::animSwap_toggle);
            help_marker("Do the move you want to see, hit the first button\nDo the move you want to replace, hit the second button");
            if (GameHook::animSwap_toggle) {
                ImGui::Text("Current Anim ID");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##CurrentAnimIDInputInt", &GameHook::animSwapCurrentAnim);
                ImGui::PopItemWidth();

                ImGui::Text("Desired Anim ID");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##DesiredAnimID1InputInt", &GameHook::animSwapDesiredAnim1);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("Save Current Anim ID as desired")) {
                    GameHook::animSwapDesiredAnim1 = GameHook::animSwapCurrentAnim;
                }

                ImGui::Text("Source Anim ID");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##SourceAnimID1InputInt", &GameHook::animSwapSourceAnim1);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("Save Current Anim ID as source")) {
                    GameHook::animSwapSourceAnim1 = GameHook::animSwapCurrentAnim;
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

            ImGuiURL repo{ "https://github.com/SSSiyan/GameHook", "https://github.com/SSSiyan/GameHook" };
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
}