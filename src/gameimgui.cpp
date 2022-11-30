#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>

// system
static float inputItemWidth = 100.0f;
bool GameHook::showMessages_toggle(false);
bool GameHook::showComboUI_toggle(false);
float GameHook::comboUI_X(0.0f);
float GameHook::comboUI_Y(0.0f);
int GameHook::showMessageTimerF1 = 0;
int GameHook::showMessageTimerF2 = 0;
int GameHook::showMessageTimerF3 = 0;
int GameHook::showMessageTimerF5 = 0;

// update
uintptr_t GameHook::playerPointerAddress = 0xEF5A60;
uintptr_t GameHook::halosAddress = 0x5AA74B4;
uintptr_t GameHook::chaptersPlayedAddress = 0x5AA736C;
uintptr_t GameHook::playerMagicAddress = 0x5AA74AC;
uintptr_t GameHook::comboPointsAddress = 0x5BB519C;
uintptr_t GameHook::comboMultiplierAddress = 0x5BB51A0;
uintptr_t GameHook::currentCharacterAddress = 0x5AA7484;
uintptr_t GameHook::thirdAccessoryAddress = 0x5AA7468;
uintptr_t GameHook::hudDisplayAddress = 0xF2B714;
uintptr_t GameHook::enemySlotsAddress = 0x5A56A88;
uintptr_t GameHook::angelSlayerFloorAddress = 0x509E87C;
uintptr_t GameHook::difficultyAddress = 0x5A985A0;
uintptr_t GameHook::areaJumpAddress = 0x05A978E8;

void help_marker(const char* desc) {
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
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

void GameHook::GameImGui(void) {
    uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;

    uintptr_t* enemy_ptr = (uintptr_t*)((uintptr_t)GameHook::enemySlotsAddress + GameHook::saveStates_CurrentEnemy * 4); // 0x5A56A8C
    uintptr_t enemy_base = *enemy_ptr;

    int& halosValue = *(int*)GameHook::halosAddress;
    int& chaptersPlayedValue = *(int*)GameHook::chaptersPlayedAddress;
    int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
    float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
    int& currentCharacterValue = *(int*)GameHook::currentCharacterAddress;
    int& thirdAccessoryValue = *(int*)GameHook::thirdAccessoryAddress;
    bool& hudDisplayValue = *(bool*)GameHook::hudDisplayAddress;
    int& angelSlayerFloorValue = *(int*)GameHook::angelSlayerFloorAddress;
    int& difficultyValue = *(int*)GameHook::difficultyAddress;
    int& areaJumpValue = *(int*)GameHook::areaJumpAddress;

    if (ImGui::Button("Save config")) {
        GameHook::onConfigSave(GameHook::cfg);
    }

    if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("General")) {
            ImGui::BeginChild("GeneralChild");

            ImGui::Checkbox("Damage Dealt Multiplier ##DamageDealtMultiplierToggle", &GameHook::damageDealtMultiplier_toggle);
            if (GameHook::damageDealtMultiplier_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##DamageDealtMultiplierrInputFloat", &GameHook::damageDealtMultiplierMult, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            if (ImGui::Checkbox("Deal No Damage (F1) ##DealNoDamageToggle", &GameHook::enemyHP_no_damage_toggle)) {
                GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
                if (GameHook::enemyHP_no_damage_toggle)
                    GameHook::enemyHP_one_hit_kill_toggle = false;
            }

            if (ImGui::Checkbox("Take No Damage (F2)", &GameHook::takeNoDamage_toggle)) {
                GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
            }

            if (ImGui::Checkbox("One Hit Kill (F3) ##OneHitKillToggle", &GameHook::enemyHP_one_hit_kill_toggle)) {
                if (GameHook::enemyHP_one_hit_kill_toggle) {
                    GameHook::enemyHP_no_damage_toggle = false;
                    GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
                }
            }

            ImGui::Checkbox("Inf Magic ##InfMagicToggle", &GameHook::inf_magic_toggle);

            if (ImGui::Checkbox("Disable Enemy Daze", &GameHook::disableDaze_toggle)) {
                GameHook::DisableDaze(GameHook::disableDaze_toggle);
            }

            ImGui::Text("Difficulty");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##DifficultyInputInt", &difficultyValue);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            switch (difficultyValue) {
            case 0:
                ImGui::Text("Very Easy");
                break;
            case 1:
                ImGui::Text("Easy");
                break;
            case 2:
                ImGui::Text("Normal");
                break;
            case 3:
                ImGui::Text("Hard");
                break;
            case 4:
                ImGui::Text("Non-Stop Infinite Climax");
                break;
            default:
                ImGui::Text("");
                break;
            }

            ImGui::Text("Initial Angel Slayer Floor");
            help_marker("0 = floor 1. Set before starting Angel Slayer.");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##InitialAngelSlayerFloorInputInt", &GameHook::initialAngelSlayerFloor);
            ImGui::PopItemWidth();

            ImGui::Text("Current Angel Slayer Floor");
            help_marker("0 = floor 1. Set before entering a portal.");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##AngelSlayerFloorInputInt", &angelSlayerFloorValue);
            ImGui::PopItemWidth();

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
            if (GameHook::witchTimeMultiplier_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##WitchTimeMultiplier", &GameHook::witchTimeMultiplier, 0, 0, "%.1f");
                ImGui::PopItemWidth();
            }

            if (ImGui::Checkbox("Disable After Burner Bounce", &GameHook::disableAfterBurnerBounce_toggle)) {
                DisableAfterBurnerBounce(GameHook::disableAfterBurnerBounce_toggle);
            }

            ImGui::Checkbox("Cancellable After Burner", &GameHook::cancellableAfterBurner_toggle);

            ImGui::Checkbox("Cancellable Falling Kick", &GameHook::cancellableFallingKick_toggle);

            ImGui::Text("Third Accessory");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##ThirdAccessoryInputInt", &thirdAccessoryValue, 1, 100);
            ImGui::PopItemWidth();
            ImGui::SameLine();

            switch (thirdAccessoryValue)
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

            ImGui::Text("Halos");
            ImGui::InputInt("##HaloInputInt", &halosValue, 1, 100);

            ImGui::Text("Chapters Played");
            ImGui::InputInt("##ChapterInputInt", &chaptersPlayedValue, 1, 100);

            ImGui::Text("Combo Points");
            ImGui::InputInt("##ComboPointsInputInt", &comboPointsValue, 10, 100);

            ImGui::Text("Combo Multiplier");
            ImGui::InputFloat("##ComboMultiplierInputFloat", &comboMultiplierValue, 1, 10, "% .1f");

            ImGui::Spacing();
            ImGui::Separator();

            if (actorPlayable) { // != NULL
                float* playerXYZPos[3];
                playerXYZPos[0] = (float*)(actorPlayable + 0xD0);
                playerXYZPos[1] = (float*)(actorPlayable + 0xD4);
                playerXYZPos[2] = (float*)(actorPlayable + 0xD8);
                int& playerHealthValue = *(int*)(actorPlayable + 0x93508);
                int& playerHealthValue2 = *(int*)(actorPlayable + 0x6B4); // red damage
                float& remainingWitchTimeValue = *(float*)(actorPlayable + 0x95D5C);
                float& playerMagicValue = *(float*)GameHook::playerMagicAddress; // not player offset but keeping it here anyway

                ImGui::Text("Player Position");
                ImGui::InputFloat3("##Player Position", *playerXYZPos); // player

                ImGui::Text("Player HP");
                if (ImGui::InputInt("##PlayerHPInputInt", &playerHealthValue, 1, 100)) {
                    playerHealthValue2 = playerHealthValue;
                }

                ImGui::Text("Player MP");
                ImGui::InputFloat("##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");

                ImGui::Text("Remaining Witch Time Duration");
                ImGui::InputFloat("##RemainingWitchTimeDurationInputFloat", &remainingWitchTimeValue, 10, 100, "%.0f");
            }

            ImGui::Spacing();
            ImGui::Separator();

            ImGui::Text("Enemy Slot");
            help_marker("Slide until you find your enemy's XYZ moving similarly to what you see ingame\nNot 100% sure how this works yet so its a lil funky");
            ImGui::SliderInt("##EnemyXYZPosInputInt", &GameHook::saveStates_CurrentEnemy, 1, 10);

            if (enemy_base) {
                float* enemyXYZPos[3];
                enemyXYZPos[0] = (float*)(enemy_base + 0xD0);
                enemyXYZPos[1] = (float*)(enemy_base + 0xD4);
                enemyXYZPos[2] = (float*)(enemy_base + 0xD8);
                int& enemyHPValue = *(int*)(enemy_base + 0x6B4);
                int& enemyMoveIDValue = *(int*)(enemy_base + 0x34C);
                float& enemyAnimFrameValue = *(float*)(enemy_base + 0x3E4);
                float& enemyDazeValue = *(float*)(enemy_base + 0xC94);

                ImGui::Text("Enemy Position");
                ImGui::InputFloat3("##EnemyXYZPosInputFloat", *enemyXYZPos);
                ImGui::Text("Enemy HP");
                ImGui::InputInt("##EnemyHPInputInt", &enemyHPValue);
                ImGui::Text("Enemy Move ID");
                ImGui::InputInt("##EnemyMoveIDInputInt", &enemyMoveIDValue, 1, 100);
                ImGui::Text("Enemy Daze");
                ImGui::InputFloat("##EnemyDazeInputFloat", &enemyDazeValue, 1, 10, "%.0f");

                ImGui::Text("SaveState");
                help_marker("Save and load an enemy's position and animation");
                if (ImGui::Button("Save State")) {
                    GameHook::SaveStates_SaveState();
                }
                if (ImGui::Button("Load State")) {
                    GameHook::SaveStates_LoadState();
                }
            }

            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("System")) {
            ImGui::BeginChild("SystemChild");

            ImGui::Checkbox("Show Hotkey Messages", &GameHook::showMessages_toggle);

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

            ImGui::Checkbox("Show Combo UI", &GameHook::showComboUI_toggle);
            help_marker("Open a window that shows your current combo multiplier when passing 9.9x");
            if (GameHook::showComboUI_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("X Position ##ComboUIXInputFloat", &comboUI_X);
                ImGui::InputFloat("Y Position ##ComboUIYInputFloat", &comboUI_Y);
                ImGui::PopItemWidth();
            }

            ImGui::Checkbox("Camera Distance Multiplier ##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            if (GameHook::customCameraDistance_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceMultiplierInputFloat", &GameHook::customCameraDistanceMultiplierMult, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            ImGui::Text("Character Select");
            help_marker("Set while in costume select\nIf your game freezes at the end of a fight, flick the value back to default");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##CharacterSelectInputInt", &currentCharacterValue, 1, 100);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            switch (currentCharacterValue) {
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

            ImGui::Checkbox("HUD Display", &hudDisplayValue);
            help_marker("Show HP etc");

            ImGui::Checkbox("Enemy HP in Halo Display", &GameHook::haloDisplay_toggle);

            if (ImGui::Checkbox("NoClip (F5)", &GameHook::noClip_toggle)) {
                GameHook::NoClip(GameHook::noClip_toggle);
            }

            if (ImGui::Checkbox("Freeze Timer", &GameHook::freezeTimer_toggle)) {
                GameHook::FreezeTimer(GameHook::freezeTimer_toggle);
            }

            ImGui::Checkbox("Easier Mashing ##EasierMashToggle", &GameHook::easierMash_toggle);

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

            ImGui::Text("Area Jump Test");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##AreaIDInputInt", &areaJumpValue, ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopItemWidth();
            help_marker("Press Enter after typing to teleport.\n2576 = mission select\n528 = proving grounds\n2816 = angel slayer\n276 = train station");
            if (ImGui::Button("Jump to mission select")) {
                areaJumpValue = 2576;
            }
            help_marker("Depending on when this is pressed it could crash. Haven't tested it much gl");
            if (ImGui::Checkbox("Patch Area Jump Correction", &GameHook::areaJumpPatch_toggle)) {
                GameHook::AreaJumpPatch(GameHook::areaJumpPatch_toggle);
            }
            help_marker("Sometimes the area jump ID gets reset, presumably to correct it if you input something out of bounds. This removes that.");

            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Credits")) {
            ImGui::BeginChild("CreditsChild");

            ImGui::Text("Hotkeys:");
            ImGui::Text("F1 = Deal No Damage");
            ImGui::Text("F2 = Take No Damage");
            ImGui::Text("F3 = One Hit Kill");
            ImGui::Text("F5 = NoClip");

            ImGui::Separator();

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

            ImGui::Text("Check for updates here:");
            ImGuiURL repo{ GameHook::repoUrl, GameHook::repoUrl };
            repo.draw();

            ImGui::Separator();

            ImGui::Text("This trainer was made by:");
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

            ImGui::Text("This trainer was made using:");
            static std::array<ImGuiURL, 3> links2{
                ImGuiURL { "Dear ImGui", "https://github.com/ocornut/imgui" },
                ImGuiURL { "minhook", "https://github.com/TsudaKageyu/minhook" },
                ImGuiURL { "DX9 BaseHook", "https://github.com/rdbo/DX9-BaseHook" },
            };
            for (auto& link : links2) {
                link.draw();
            }

            ImGui::Separator();
            ImGui::Text("Licenses:");
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

// 4hook styling
void GameHook::ImGuiStyle(void) {
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

void GameHook::BackgroundImGui(void) {
    if (GameHook::showMessages_toggle) {
        if (GameHook::showMessageTimerF1 > 0) {
            if (GameHook::enemyHP_no_damage_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "Deal No Damage ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "Deal No Damage OFF");
            GameHook::showMessageTimerF1--;
        }
        if (GameHook::showMessageTimerF2 > 0) {
            if (GameHook::takeNoDamage_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "Take No Damage ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "Take No Damage OFF");
            GameHook::showMessageTimerF2--;
        }
        if (GameHook::showMessageTimerF3 > 0) {
            if (GameHook::enemyHP_one_hit_kill_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "One Hit Kill ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "One Hit Kill OFF");
            GameHook::showMessageTimerF3--;
        }
        //
        if (GameHook::showMessageTimerF5 > 0) {
            if (GameHook::noClip_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "NoClip ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "NoClip OFF");
            GameHook::showMessageTimerF5--;
        }
    }
}
