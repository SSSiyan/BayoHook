#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>
#include <chrono>

bool GameHook::drawStats_toggle = false;
void GameHook::DrawStats() {
    if (pvp_toggle) {
        LocalPlayer* player1 = GameHook::GetPlayer1();
        LocalPlayer* player2 = GameHook::GetPlayer2();
        if (player1 && player2) {
            auto io = ImGui::GetIO();
            float fontSize = ImGui::GetFontSize();

            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.0f, io.DisplaySize.y * 1.0f), ImGuiCond_Once, ImVec2(0.0f, 1.0f));
            ImGui::Begin("Player 1##NotFlyingPlayerBegin", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
            ImGui::PushItemWidth(fontSize * 12.0f);
            ImGui::SliderInt("HP##NotFlyingPlayer1HPInputInt", &player1->hp, 0, player1->hpMax);
            ImGui::PopItemWidth();
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 1.0f, io.DisplaySize.y * 1.0f), ImGuiCond_Once, ImVec2(1.0f, 1.0f));
            ImGui::Begin("Player 2##NotFlyingPlayerBegin", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
            ImGui::PushItemWidth(fontSize * 12.0f);
            ImGui::SliderInt("HP##NotFlyingPlayer2HPInputInt", &player2->hp, 0, player2->hpMax);
            ImGui::PopItemWidth();
            ImGui::End();
        }
    }
    else {
        LocalPlayer* player = GameHook::GetLocalPlayer();
        if (player) {
            auto io = ImGui::GetIO();
            float fontSize = ImGui::GetFontSize();
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.0f, io.DisplaySize.y * 1.0f), ImGuiCond_Once, ImVec2(0.0f, 1.0f));
            ImGui::Begin("Player##NotFlyingPlayerBegin", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
            ImGui::PushItemWidth(fontSize * 9.0f);
            ImGui::DragFloat3("Pos##NotFlyingPlayerXYZPosInputFloat", &player->pos.x, 0.5f, 0.0f, 0.0f, "%.1f");
            ImGui::SliderInt("HP##NotFlyingEnemyHPInputInt", &player->hp, 0, player->hpMax);
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(fontSize * 3.0f);
            ImGui::SliderFloat("AnimFrame##NotFlyingPlayerAnimationFrameSliderFloat", &player->animFrame, 0.0f, player->animFrameMax, "%.0f");
            ImGui::InputInt("Move ID##NotFlyingPlayerMoveIDInputInt", &player->moveID, NULL, NULL);
            ImGui::InputInt("String ID##NotFlyingPlayerStringIDInputInt", &player->stringID, NULL, NULL);
            ImGui::PopItemWidth();
            ImGui::End();

            Enemy* enemy = player->softLockEnemy;
            if (enemy) {
                // static ImVec2 enemyScreenPos;
                ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 1.0f, io.DisplaySize.y * 1.0f), ImGuiCond_Once, ImVec2(1.0f, 1.0f));
                ImGui::Begin("Locked On Entity##NotFlyingEnemyBegin", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
                ImGui::PushItemWidth(fontSize * 9.0f);
                ImGui::DragFloat3("Pos##NotFlyingEnemyXYZPosInputFloat", &enemy->pos.x, 0.5f, 0.0f, 0.0f, "%.1f");
                ImGui::SliderInt("HP##NotFlyingEnemyHPInputInt", &enemy->hp, 0, enemy->hpMax);
                ImGui::InputScalar("ID##NotFlyingEnemyIDInputInt", ImGuiDataType_S32, &enemy->id, 0, 0, "%x", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::PopItemWidth();
                ImGui::PushItemWidth(fontSize * 3.0f);
                ImGui::InputInt("Move ID##NotFlyingEnemyMoveIDInputInt", &enemy->moveID, 0, 0);
                if (enemy->dazeCurrentDuration > 0.0f) {
                    ImGui::SliderFloat("Daze##NotFlyingEnemyDazeSliderFloat", &enemy->daze, 0.0f, enemy->dazeMax, "%.1f");
                    ImGui::SameLine();
                    ImGui::Text("/ %.1f", enemy->dazeMax);
                }
                else {
                    ImGui::InputFloat("Daze Timer##NotFlyingEnemyDazeTimerInputFloat", &enemy->dazeCurrentDuration, 0.0f, 0.0f, "%.1f");
                }
                ImGui::PopItemWidth();
                // FlagCheckbox("BE_TRANS", enemy->eBeFlag, BE_TRANS);
                // FlagCheckbox("BE_OBA_HIT", enemy->eBeFlag, BE_OBA_HIT);
                // FlagCheckbox("BE_SCA_HIT", enemy->eBeFlag, BE_SCA_HIT);
                // FlagCheckbox("BE_LOCKENABLE", enemy->eBeFlag, BE_LOCKENABLE);
                // FlagCheckbox("BE_GAMEOBJ", enemy->eBeFlag, BE_GAMEOBJ);
                // FlagCheckbox("BE_EM", enemy->eBeFlag, BE_EM);
                // FlagCheckbox("BE_WEPGET", enemy->eBeFlag, BE_WEPGET);
                // FlagCheckbox("BE_SUSPEND", enemy->eBeFlag, BE_SUSPEND);
                // FlagCheckbox("BE_BREAK", enemy->eBeFlag, BE_BREAK);
                // FlagCheckbox("BE_INSCREEN_OUT", enemy->eBeFlag, BE_INSCREEN_OUT);
                // FlagCheckbox("BE_ALPHA_CHECK", enemy->eBeFlag, BE_ALPHA_CHECK);
                // FlagCheckbox("BE_SUSPEND_AT_EVENT", enemy->eBeFlag, BE_SUSPEND_AT_EVENT);
                // FlagCheckbox("BE_ROOMOBJ", enemy->eBeFlag, BE_ROOMOBJ);
                // FlagCheckbox("BE_CHANGE_PRIO", enemy->eBeFlag, BE_CHANGE_PRIO);
                // FlagCheckbox("BE_EVENT_CONTROL", enemy->eBeFlag, BE_EVENT_CONTROL);
                // FlagCheckbox("BE_TRANS_IN_SCENARIO", enemy->eBeFlag, BE_TRANS_IN_SCENARIO);
                // FlagCheckbox("BE_NO_REPLAY", enemy->eBeFlag, BE_NO_REPLAY);
                // FlagCheckbox("BE_CAM_NO_LOCKON", enemy->eBeFlag, BE_CAM_NO_LOCKON);
                // FlagCheckbox("BE_ENEMY_OBJ", enemy->eBeFlag, BE_ENEMY_OBJ);
                // FlagCheckbox("BE_ACCESSORYMODEL", enemy->eBeFlag, BE_ACCESSORYMODEL);
                // FlagCheckbox("BE_ITEM", enemy->eBeFlag, BE_ITEM);
                // FlagCheckbox("BE_BLOCK_CLOTH_RATE", enemy->eBeFlag, BE_BLOCK_CLOTH_RATE);
                // FlagCheckbox("BE_FACEOBJ", enemy->eBeFlag, BE_FACEOBJ);
                // FlagCheckbox("BE_INSCREEN_NO_CHECK", enemy->eBeFlag, BE_INSCREEN_NO_CHECK);
                ImGui::End();
            }
        }
    }
}

static void DrawEnemySwapper() {
    ImGui::Checkbox("Enemy Swapper", &GameHook::swapSpawns_toggle);
    GameHook::help_marker("If you find an enemy that does not swap, its because the game used a variant I don't have listed here. Let me know and I'll add it."
        "\nIf you want to help, spawn the enemy again and check \"Log Spawns\" on the \"Extras\" tab and let me know what the variant was\n\n"
        "\"Spawn Modifier\" seems to be able to mean a few different things - sometimes spawn animation, sometimes difficulty.\n"
        "Setting \"Original\" will keep whatever the game originally used, which may not work on your new enemy\n"
        "If we can identify these properly I can probably just roll this into enemy selection?? But maybe there's too many, idk\n\n"
        "You can use this on top of enemy randomizer to ensure certain enemies are what you want them to be");

    if (GameHook::swapSpawns_toggle) {
        static int setAllTargetIndex = 0;
        static int setAllSpawnModifier = -1;
        if (ImGui::Button("Reset All")) {
            for (int i = 0; i < (int)GameHook::swapRules.size(); i++) {
                auto& rule = GameHook::swapRules[i];
                rule.targetIndex = rule.sourceIndex;
                rule.spawnModifier = -1;
                rule.enabled = false;
            }
        }

        if (ImGui::Button("Set All To:")) {
            for (int i = 0; i < (int)GameHook::swapRules.size(); i++) {
                auto& rule = GameHook::swapRules[i];

                rule.targetIndex = setAllTargetIndex;
                rule.spawnModifier = setAllSpawnModifier;
                rule.enabled = true;
            }
        }
        ImGui::SameLine();
        char setAllPreview[128];
        snprintf(setAllPreview, sizeof(setAllPreview), "%s (v%d)", spawnTypes[setAllTargetIndex].info.name, spawnTypes[setAllTargetIndex].info.variant);
        ImGui::SetNextItemWidth(GameHook::inputItemWidth * 2.0f);
        if (ImGui::BeginCombo("##SetAllEnemyTarget", setAllPreview)) {
            for (int i = 0; i < (int)spawnTypes.size(); i++) {
                const auto& entry = spawnTypes[i];
                char label[128];
                snprintf(label, sizeof(label), "%s (0x%05X, v%d)", entry.info.name, entry.info.id, entry.info.variant);
                bool selected = (i == setAllTargetIndex);
                if (ImGui::Selectable(label, selected))
                    setAllTargetIndex = i;
                if (selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(GameHook::inputItemWidth);
        if (setAllSpawnModifier == -1) {
            if (ImGui::BeginCombo("##SetAllSpawnModifier", "Original")) {
                if (ImGui::Selectable("Original", true))
                    setAllSpawnModifier = -1;
                for (int mod = 0; mod <= 32; mod++) {
                    char label[32];
                    snprintf(label, sizeof(label), "%d", mod);

                    if (ImGui::Selectable(label, false))
                        setAllSpawnModifier = mod;
                }
                ImGui::EndCombo();
            }
        }
        else {
            char currentLabel[32];
            snprintf(currentLabel, sizeof(currentLabel), "%d", setAllSpawnModifier);
            if (ImGui::BeginCombo("##SetAllSpawnModifier", currentLabel)) {
                if (ImGui::Selectable("Original", false))
                    setAllSpawnModifier = -1;
                for (int mod = 0; mod <= 32; mod++) {
                    char label[32];
                    snprintf(label, sizeof(label), "%d", mod);
                    bool selected = (mod == setAllSpawnModifier);
                    if (ImGui::Selectable(label, selected))
                        setAllSpawnModifier = mod;
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }

        ImGui::Separator();

        if (ImGui::BeginTable("enemy_swapper_table", 5, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Enabled##EnemySwapper", ImGuiTableColumnFlags_WidthFixed, 30.0f);
            ImGui::TableSetupColumn("Original Spawn##EnemySwapper", ImGuiTableColumnFlags_WidthStretch, 0.35f);
            ImGui::TableSetupColumn("Replace With##EnemySwapper", ImGuiTableColumnFlags_WidthStretch, 0.45f);
            ImGui::TableSetupColumn("Spawn Modifier##EnemySwapper", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableSetupColumn("Reset##EnemySwapper", ImGuiTableColumnFlags_WidthFixed, 70.0f);
            ImGui::TableHeadersRow();

            for (int i = 0; i < (int)GameHook::swapRules.size(); i++) {
                auto& rule = GameHook::swapRules[i];
                const auto& source = spawnTypes[rule.sourceIndex];
                const auto& target = spawnTypes[rule.targetIndex];
                ImGui::PushID(i);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Checkbox("##EnemySwapEnabledEnemySwapper", &rule.enabled);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", source.info.name);
                ImGui::TextDisabled("ID 0x%05X, Variant %d", source.info.id, source.info.variant);

                ImGui::TableSetColumnIndex(2);
                char comboPreview[64];
                snprintf(comboPreview, sizeof(comboPreview), "%s (v%d)", target.info.name, target.info.variant);
                ImGui::SetNextItemWidth(-FLT_MIN);
                if (ImGui::BeginCombo("##target", comboPreview)) {
                    for (int j = 0; j < (int)spawnTypes.size(); j++) {
                        const auto& entry = spawnTypes[j];
                        char label[128];
                        snprintf(label, sizeof(label), "%s (0x%05X, v%d)", entry.info.name, entry.info.id, entry.info.variant);
                        bool selected = (j == rule.targetIndex);
                        if (ImGui::Selectable(label, selected)) {
                            rule.targetIndex = j;
                            rule.enabled = true;
                        }
                        if (selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                ImGui::TableSetColumnIndex(3);
                ImGui::SetNextItemWidth(-FLT_MIN);
                if (rule.spawnModifier == -1) {
                    char defaultLabel[64];
                    snprintf(defaultLabel, sizeof(defaultLabel), "Original");
                    if (ImGui::BeginCombo("##spawnModifier", defaultLabel)) {
                        if (ImGui::Selectable("Original", true))
                            rule.spawnModifier = -1;
                        for (int mod = 0; mod <= 10; mod++) {
                            char label[32];
                            snprintf(label, sizeof(label), "%d", mod);

                            if (ImGui::Selectable(label, false))
                                rule.spawnModifier = mod;
                        }
                        ImGui::EndCombo();
                    }
                }
                else {
                    char currentLabel[32];
                    snprintf(currentLabel, sizeof(currentLabel), "%d", rule.spawnModifier);
                    if (ImGui::BeginCombo("##spawnModifier", currentLabel)) {
                        if (ImGui::Selectable("Original", false))
                            rule.spawnModifier = -1;

                        for (int mod = 0; mod <= 32; mod++) {
                            char label[32];
                            snprintf(label, sizeof(label), "%d", mod);
                            bool selected = mod == rule.spawnModifier;
                            if (ImGui::Selectable(label, selected))
                                rule.spawnModifier = mod;
                            if (selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                }

                ImGui::TableSetColumnIndex(4);
                bool isDefault = rule.targetIndex == rule.sourceIndex && rule.spawnModifier == -1 && !rule.enabled;
                if (isDefault)
                    ImGui::BeginDisabled();

                if (ImGui::Button("Reset")) {
                    rule.targetIndex = rule.sourceIndex;
                    rule.spawnModifier = -1;
                    rule.enabled = false;
                }
                if (isDefault)
                    ImGui::EndDisabled();
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }
}

bool GameHook::forceHairColour_toggle = false;
Vec3 GameHook::desiredHairColourRGB = { 1.0f, 1.0f, 1.0f };
float GameHook::desiredHairColourMult = 1.0f;
static void ApplyHairColour(LocalPlayer* player) {
    if (!player) { return; }
    player->colouredHairIntensityRGB = {
        GameHook::desiredHairColourRGB.x * GameHook::desiredHairColourMult,
        GameHook::desiredHairColourRGB.y * GameHook::desiredHairColourMult,
        GameHook::desiredHairColourRGB.z * GameHook::desiredHairColourMult
    };
}

void GameHook::GameTick(void) { // also called while the menu isn't open
    static bool isFirstFrame = true;
    LocalPlayer* player = GetLocalPlayer();
    isFirstFrame = false;
    if (player) {
        if (GameHook::forceCostume) {
            *(int*)GameHook::currentCostumeAddress = tempCostume;
        }
#ifndef SPEEDRUN_BUILD
        if (comboMaker_toggle) {
            for (int i = 0; i < maxComboMakers; ++i) {
                if (comboMaker_toggles[i]) {
                    if (player->moveID == comboMakerMoveIDs[i] && player->attackCount == comboMakerMoveParts[i]) {
                        player->stringID = comboMakerStringIDs[i];
                    }
                }
            }
        }
        if (GameHook::drawStats_toggle || GameHook::pvp_toggle || GameHook::drawPlayerBones_toggle || GameHook::drawHitboxes_toggle) {
            Setup3dShapes();
        }
        if (GameHook::drawPlayerBones_toggle || GameHook::drawHitboxes_toggle) {
            Draw3dShapes();
        }
        if (GameHook::drawStats_toggle || GameHook::pvp_toggle) {
            DrawStats();
        }
#endif
        if (forceHairColour_toggle) {
            ApplyHairColour(player);
        }
    }
#if 0
    if (GameHook::forceSaveFile) {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02d", GameHook::forcedFileNum);
        GameHook::_patch((char*)(GameHook::sav99Address), buf, 2);
    }
#endif
}
static float maxUIHeight             = 0.0f;
static float uiHeight                = 0.0f;
static float tabHeight               = 0.0f;
static float endHeight               = 0.0f;
static float gameWindowHeight        = 0.0f;

void GameHook::under_line(const ImColor& col) {
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    min.y = max.y;
    ImGui::GetWindowDrawList()->AddLine(min, max, col, 1.0f);
}

void GameHook::help_marker(const char* desc) {
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

// display flags as checkboxes e.g. FlagCheckbox("BE_EM", enemy->eBeFlag, BE_EM);
// player1->beFlag |= BE_EM;    // Set
// player1->beFlag &= ~BE_EM;   // Clear
// player1->beFlag ^= BE_EM;    // Toggle
// if (player1->beFlag & BE_EM) // Check
void GameHook::FlagCheckbox(const char* label, uint32_t& flags, uint32_t flag) {
    bool enabled = (flags & flag) != 0;
    if (ImGui::Checkbox(label, &enabled)) {
        if (enabled)
            flags |= flag;
        else
            flags &= ~flag;
    }
}

static void DrawCredits() {
    ImGui::SeparatorText("Updates");
    struct ImGuiURL {
        std::string text;
        std::string url;
        const ImVec4 color_hover{ 0.356f, 0.764f, 0.960f, 1.00f };
        const ImVec4 color_regular{ 0.950f, 0.960f, 0.980f, 1.00f };

        void draw() {
            ImGui::TextColored(color_regular, text.c_str());
            if (ImGui::IsItemHovered()) {
                GameHook::under_line(color_hover);
            }
            if (ImGui::IsItemClicked()) {
                ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
        }
    };

    ImGuiURL repo{ GameHook::repoUrl, GameHook::repoUrl };
    repo.draw();

    ImGui::SeparatorText("Made By");

    static std::array<ImGuiURL, 13> links1{
        ImGuiURL { "SSSiyan", "https://twitter.com/sssiyan" },
        ImGuiURL { "GarudaKK", "https://www.youtube.com/@GarudaPSN" },
        ImGuiURL { "Kerilk", "https://github.com/Kerilk" },
        ImGuiURL { "CreativeHandle", "https://twitter.com/CreativeHandler" },
        ImGuiURL { "Skyth", "https://github.com/blueskythlikesclouds" },
        ImGuiURL { "deepdarkkapustka", "https://www.youtube.com/@mstislavcapusta7573" },
        ImGuiURL { "TheDarkness", "https://steamcommunity.com/id/TheDarkness704/" },
        ImGuiURL { "Jan Schatter", "https://www.flickr.com/people/116494253@N05/" },
        ImGuiURL { "Reclaimer", "https://www.speedrun.com/users/Reclaimer" },
        ImGuiURL { "Joy Laguna", "https://www.youtube.com/channel/UCAM-7bYxvPbfhOU7TEw4idQ" },
        ImGuiURL { "Fool Arcana", "https://gamebanana.com/members/2795442" },
        ImGuiURL { "DniweTamp", "https://github.com/DniweTamp" },
        ImGuiURL { "Frouk", "https://github.com/Frouk3" },
    };
    for (auto& link : links1) {
        link.draw();
    }

    ImGui::SeparatorText("Made Possible Using");

    static std::array<ImGuiURL, 3> links2{
        ImGuiURL { "Dear ImGui", "https://github.com/ocornut/imgui" },
        ImGuiURL { "minhook", "https://github.com/TsudaKageyu/minhook" },
        ImGuiURL { "DX9 BaseHook", "https://github.com/rdbo/DX9-BaseHook" },
    };
    for (auto& link : links2) {
        link.draw();
    }

    ImGui::SeparatorText("Licenses");

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
}

static void DrawBayoHookSettings() {
#ifndef SPEEDRUN_BUILD
    ImGui::Checkbox("Pause When Opening BayoHook", &GameHook::openMenuPause_toggle);
    GameHook::help_marker("Pause the game whenever BayoHook's main UI is opened");
#endif
    ImGui::SetNextItemWidth(GameHook::inputItemWidth);
    ImGui::InputFloat("Font Size", &GameHook::bayoHookFontSize, 1.0f, 10.0f, "%.0f");
    GameHook::help_marker("Set BayoHook's font size");
    ImGui::Checkbox("Scroll Transitions", &GameHook::enable_scroll_transitions);
    GameHook::help_marker("Toggle the sliding animations that play when BayoHook changes size");

    ImGui::Checkbox("Show 9.9+ Combo Multiplier UI", &GameHook::showComboUI_toggle);
    GameHook::help_marker("Open a window that shows your current combo multiplier when passing 9.9x");
    if (GameHook::showComboUI_toggle) {
        ImGui::Indent();
        ImGui::PushItemWidth(GameHook::inputItemWidth);
        ImGui::InputFloat("X Position##ComboUIXInputFloat", &GameHook::comboUI_X, 0.001f, 0.01f);
        ImGui::InputFloat("Y Position##ComboUIYInputFloat", &GameHook::comboUI_Y, 0.001f, 0.01f);
        ImGui::PopItemWidth();
        ImGui::Checkbox("Test", &GameHook::testComboUI_toggle);
        ImGui::SameLine();
        if (ImGui::Button("Reset##ResetComboUIPositionButton")) {
            GameHook::comboUI_X = 0.880f;
            GameHook::comboUI_Y = 0.218f;
        }
        ImGui::Unindent();
    }
}

static void DrawAreaJump() {
    static int stageID = 0x114;
    static int stagePart = 0;
    static int spawn = -1;
    static constexpr int step = 1;
    ImGui::SeparatorText("Area Jump");
    ImGui::SetNextItemWidth(GameHook::inputItemWidth);
    ImGui::InputScalar("Current Stage ID ##CurrentStageIDAreaJumpInputScalar", ImGuiDataType_S32, (int*)GameHook::areaJumpAddress, NULL, NULL, "%8X", ImGuiInputTextFlags_ReadOnly);
    static int selectedIndex = 4;
    for (int i = 0; i < IM_ARRAYSIZE(areaIDNames); i++) {
        if (areaIDNames[i].ID == stageID) {
            selectedIndex = i;
            break;
        }
    }
    const char* preview = areaIDNames[selectedIndex].name;
    ImGui::PushItemWidth(GameHook::inputItemWidth*3);
    if (ImGui::BeginCombo("##AreaDropdown", preview)) {
        for (int i = 0; i < IM_ARRAYSIZE(areaIDNames); i++) {
            bool isSelected = (selectedIndex == i);
            if (ImGui::Selectable(areaIDNames[i].name, isSelected)) {
                selectedIndex = i;
                stageID = areaIDNames[i].ID;
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::PushItemWidth(GameHook::inputItemWidth);
    ImGui::InputScalar("stage ID##ManualStageIDInputScalar", ImGuiDataType_S32, &stageID, &step, NULL, "%8X");
    GameHook::help_marker("There are likely missing entries here - some chapters have multiple stages and I only quickly loaded into each. For that reason I've left this manual input box for now.");

    int displayStagePart = stagePart + 1;
    if (ImGui::InputInt("Part", &displayStagePart, step)) {
        if (displayStagePart < 1) { displayStagePart = 1; };
        stagePart = displayStagePart - 1;
    }
    ImGui::InputInt("Spawn", &spawn, step);
    ImGui::PopItemWidth();
    GameHook::help_marker("Mostly unused, will change which Alfheim you get in Angel Slayer (B00) and whether to fight Rodin in the shop");
    if (ImGui::Button("Teleport")) {
        GameHook::AreaJump(stageID, stagePart, spawn);
    }
}

static void DrawUptimeFix() {
#ifdef SPEEDRUN_BUILD
    ImGui::BeginDisabled();
#endif
    ImGui::Checkbox("Uptime Fix", &GameHook::uptimeFix_toggle);
#ifdef SPEEDRUN_BUILD
    ImGui::EndDisabled();
#endif
    GameHook::help_marker("Bayonetta's internal timer continuously increases from launch, and over time this causes float precision loss. "
        "This results in unstable frame timing and stutter during long play sessions. "
        "This option rebases the game timer every 60 seconds, keeping values small and precise without affecting gameplay. "
#ifdef SPEEDRUN_BUILD
        );
#endif
#ifndef SPEEDRUN_BUILD
        "For the sake of seeing if these rebases are causing lag spikes, I've exposed the timer here too so you can see if spikes coincide with the reset.");
    float* gameTimerMs = (float*)GameHook::gameTimeAddress;
    ImGui::SameLine();
    ImGui::Text("%f", *gameTimerMs);
#endif

// #ifdef SPEEDRUN_BUILD
    // ImGui::SetNextItemWidth(GameHook::inputItemWidth);
    // ImGui::SliderInt("How Often To Rebase (seconds)", (int*)&GameHook::rebase_interval, 1, 60);
// #endif
}

#ifndef SPEEDRUN_BUILD
static void DrawAngelSlayer() {
    ImGui::SeparatorText("Angel Slayer");
    ImGui::SetNextItemWidth(GameHook::inputItemWidth);
    int displayInitialAngelSlayerFloor = GameHook::initialAngelSlayerFloor + 1;
    if (ImGui::InputInt("Initial Floor##InputInt", &displayInitialAngelSlayerFloor, 1, 10)) {
        if (displayInitialAngelSlayerFloor < 1) { displayInitialAngelSlayerFloor = 1; };
        GameHook::initialAngelSlayerFloor = displayInitialAngelSlayerFloor - 1;
    }
    GameHook::help_marker("Set before starting Angel Slayer");
    ImGui::SameLine(GameHook::sameLineWidth);
    ImGui::SetNextItemWidth(GameHook::inputItemWidth);
    int displayAngelSlayerFloorValue = *(int*)GameHook::angelSlayerFloorAddress + 1;
    if (ImGui::InputInt("Current Floor##InputInt", &displayAngelSlayerFloorValue, 1, 10)) {
        if (displayAngelSlayerFloorValue < 1) { displayAngelSlayerFloorValue = 1; };
        *(int*)GameHook::angelSlayerFloorAddress = displayAngelSlayerFloorValue - 1;
    }
    GameHook::help_marker("Set before entering a portal");
}

#endif

static void DrawFPSUnlock() {
#ifndef SPEEDRUN_BUILD
    if (ImGui::Checkbox("Unlock FPS", &GameHook::disableFpsLimiter_toggle)) {
        GameHook::DisableFpsLimiter(GameHook::disableFpsLimiter_toggle);
    }
    GameHook::help_marker("If Bayonetta has been open for a long time you will experience small stutters. This option disables the built in FPS limiter so you can use an external limiter instead, which circumvents the issue");

    if (ImGui::Checkbox("Link Game Logic To Delta Time", &GameHook::linkGameToDelta_toggle)) {
        GameHook::LinkGameToDelta(GameHook::linkGameToDelta_toggle);
    }
    GameHook::help_marker("This is broken atm but when I figure this out we'll all be playing Bayo at 244hz without breaking everything, surely");
#endif
}

static void DrawGlamour() {
    ImGui::SeparatorText("Glamour");
    ImGui::BeginGroup();
    if (ImGui::Checkbox("Force Costume##Glamour", &GameHook::forceCostume)) {
        GameHook::randomizeCostume_toggle = false;
    }
    if (GameHook::forceCostume) {
        ImGui::Indent();
        ImGui::SetNextItemWidth(GameHook::inputItemWidth);
        if (ImGui::Combo("Costume##GlamourCombo", &GameHook::tempCostume, costumeNames, IM_ARRAYSIZE(costumeNames))) {
            *(int*)GameHook::currentCostumeAddress = GameHook::tempCostume;
        }
        ImGui::Unindent();
    }
    ImGui::EndGroup();
    ImGui::SameLine(GameHook::sameLineWidth);
    if (ImGui::Checkbox("Randomize Costume", &GameHook::randomizeCostume_toggle)) {
        GameHook::forceCostume = false;
    }
    GameHook::help_marker("Randomize the player's costume every load screen");

    ImGui::BeginGroup();
    if (ImGui::Checkbox("Force Hair Colour", &GameHook::forceHairColour_toggle)) {
        if (!GameHook::forceHairColour_toggle) {
            LocalPlayer* player = GameHook::GetLocalPlayer();
            if (player) {
                player->colouredHairIntensityRGB = { 1.0f, 1.0f, 1.0f };
            }
        }
    }
    if (GameHook::forceHairColour_toggle) {
        ImGui::Indent();
        ImGui::SetNextItemWidth(GameHook::inputItemWidth);
        ImGui::ColorEdit3("Hair Colour##PlayerHairColourEdit3", &GameHook::desiredHairColourRGB.x);
        ImGui::SetNextItemWidth(GameHook::inputItemWidth);
        ImGui::SliderFloat("Hair Colour Intensity##desiredHairColourIntensitySliderFloat", &GameHook::desiredHairColourMult, 1.0f, 10.0f);
        if (ImGui::Button("Reset##ResetHairColourButton")) {
            GameHook::desiredHairColourMult = 1.0f;
            GameHook::desiredHairColourRGB = { 1.0f, 1.0f, 1.0f };
        }
        ImGui::Unindent();
    }
    ImGui::EndGroup();
#ifndef SPEEDRUN_BUILD
    ImGui::SameLine(GameHook::sameLineWidth);
    if (ImGui::Checkbox("Force Summoning Clothes##SummoningClothesToggle", &GameHook::forceSummoningClothes_toggle)) {
        GameHook::ForceSummoningClothes(GameHook::forceSummoningClothes_toggle);
    }
    GameHook::help_marker("Only works on outfits that have this function");
#endif
}

void GameHook::GameImGui(void) {
#ifndef SPEEDRUN_BUILD
    int& halosValue = *(int*)GameHook::halosAddress;
    int& chaptersPlayedValue = *(int*)GameHook::chaptersPlayedAddress;
    float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
    int& currentCharacterValue = *(int*)GameHook::currentCharacterAddress;
    bool& hudDisplayValue = *(bool*)GameHook::hudDisplayAddress;
    int& difficultyValue = *(int*)GameHook::difficultyAddress;
    int& areaJumpValue = *(int*)GameHook::areaJumpAddress;
    int& weaponA1Value = *(int*)GameHook::WeaponA1Address;
    int& weaponA2Value = *(int*)GameHook::WeaponA2Address;
    int& weaponB1Value = *(int*)GameHook::WeaponB1Address;
    int& weaponB2Value = *(int*)GameHook::WeaponB2Address;
#endif
    int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
    GameHook::windowWidth = 40.0f * ImGui::GetFontSize();
    GameHook::sameLineWidth = windowWidth * 0.5f;
    GameHook::inputItemWidth = windowWidth * 0.2f;

    tabHeight = 0.0f;
    maxUIHeight = ImGui::GetIO().DisplaySize.y * 0.9f;

    if (ImGui::Button("Save Config")) {
        GameHook::onConfigSave(GameHook::cfg);
    }

    ImGui::SameLine();
    float fps = ImGui::GetIO().Framerate;
    ImGui::Text("FPS: %.1f", fps);

    if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
        uiHeight = ImGui::GetCursorPosY();
#ifndef SPEEDRUN_BUILD
        if (ImGui::BeginTabItem("General")) {
            ImGui::BeginChild("GeneralChild");

            // ImGui::Checkbox("4GB Patch", &GameHook::memPatch_toggle);
            // help_marker("DOES NOT WORK, WE DO NOT HOOK FAST ENOUGH");

            /*static void* DidItWork[8]{};
            if (ImGui::Button("Try alloc a few gb")) {
                for (int i = 0; i < 8; i++) {
                    DidItWork[i] = VirtualAlloc(NULL, 0x10000000, MEM_RESERVE, PAGE_READWRITE);
                }
            }
            for (int i = 0; i < 8; i++) {
                ImGui::Text("Did It Work = %d", DidItWork[i]);
            }*/

            ImGui::SeparatorText("Damage");

            if (ImGui::Checkbox("Deal No Damage##DealNoDamageToggle", &GameHook::enemyHPNoDamage_toggle)) {
                GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
                if (GameHook::enemyHPNoDamage_toggle) {
                    GameHook::enemyHPOneHitKill_toggle = false;
                }
            }
            help_marker("Deal no damage to enemies");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Take No Damage", &GameHook::damageReceivedMultiplierNoDamage_toggle);
            help_marker("Take no damage from enemies");

            ImGui::BeginGroup();
            ImGui::Checkbox("Damage Dealt Multiplier##DamageDealtMultiplierToggle", &GameHook::damageDealtMultiplier_toggle);
            help_marker("Ctrl + Click to type a value higher than 5.0");
            if (GameHook::damageDealtMultiplier_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::SliderFloat("##DamageDealtMultiplierInputFloat", &GameHook::damageDealtMultiplierMult, 0.0f, 5.0f, "%.1f");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            ImGui::SameLine(sameLineWidth);

            ImGui::BeginGroup();
            ImGui::Checkbox("Damage Received Multiplier##DamageReceivedMultiplierToggle", &GameHook::damageReceivedMultiplier_toggle);
            help_marker("Ctrl + Click to type a value higher than 5.0");
            if (GameHook::damageReceivedMultiplier_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::SliderFloat("##DamageReceivedMultiplierInputFloat", &GameHook::incoming_damage_mult, 0.0f, 5.0f, "%.1f");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            if (ImGui::Checkbox("One Hit Kill##OneHitKillToggle", &GameHook::enemyHPOneHitKill_toggle)) {
                if (GameHook::enemyHPOneHitKill_toggle) {
                    GameHook::enemyHPNoDamage_toggle = false;
                    GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
                }
            }
            help_marker("Kill enemies in one hit");

            ImGui::SeparatorText("Difficulty");

            ImGui::BeginGroup();
            ImGui::SetNextItemWidth(inputItemWidth*2);
            ImGui::Combo("##DifficultyCombo", &difficultyValue, "Very Easy\0Easy\0Normal\0Hard\0Non-Stop Infinite Climax\0");
            help_marker("Override the difficulty set ingame");

			ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Freeze Difficulty", &freezeDifficulty_toggle)) {
                GameHook::FreezeDifficulty(freezeDifficulty_toggle);
            }
            help_marker("Force your custom difficulty, Ensuring it overrides the game trying to set it each load screen");
            ImGui::EndGroup();

            if (ImGui::Checkbox("Disable Enemy Daze", &GameHook::disableDaze_toggle)) {
                GameHook::forceDaze_toggle = false;
                GameHook::ForceDaze(GameHook::forceDaze_toggle);

                GameHook::DisableDaze(GameHook::disableDaze_toggle);
            }
            help_marker("Stop enemies from ever being dazed");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Force Enemy Daze", &GameHook::forceDaze_toggle)) {
                GameHook::disableDaze_toggle = false;
                GameHook::DisableDaze(GameHook::disableDaze_toggle);

                GameHook::ForceDaze(GameHook::forceDaze_toggle);
            }
            help_marker("Daze all enemies");

            if (ImGui::Checkbox("More Enemy Attacks", &GameHook::moreEnemyAttacks_toggle)) {
                GameHook::lessEnemyAttacks_toggle = false;
                GameHook::LessEnemyAttacks(GameHook::lessEnemyAttacks_toggle);
                GameHook::MoreEnemyAttacks(GameHook::moreEnemyAttacks_toggle);
            }
            help_marker("Remove the timer that starts when an enemy attacks, allowing any enemy to attack at any time");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Less Enemy Attacks", &GameHook::lessEnemyAttacks_toggle)) {
                GameHook::moreEnemyAttacks_toggle = false;
                GameHook::MoreEnemyAttacks(GameHook::moreEnemyAttacks_toggle);
                GameHook::LessEnemyAttacks(GameHook::lessEnemyAttacks_toggle);
            }
            help_marker("Freeze the timer that starts when an enemy attacks, usually disallowing attacks");

            ImGui::SeparatorText("Misc");

            ImGui::Checkbox("Disable Slow Motion", &GameHook::disableSlowmo_toggle);
            help_marker("Disable slow motion when dodging etc");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("NoClip", &GameHook::noClip_toggle)) {
                GameHook::NoClip(GameHook::noClip_toggle);
            }
            help_marker("Allow every entity to ignore walls and floors");

            if (ImGui::Checkbox("Disable Enraged Hitstop", &GameHook::noEnragedHitstop_toggle)) {
                GameHook::NoEnragedHitstop(noEnragedHitstop_toggle);
            }
            ImGui::SameLine();
            help_marker("Disable only the extra hitstop you get when attacking an enraged enemy");

			ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Disable All Hitstop", &GameHook::noHitstop_toggle)) {
                GameHook::NoHitstop(noHitstop_toggle);
            }
            help_marker("Disable the game pausing for a few frames when hits connect");

            ImGui::BeginGroup();
            ImGui::Checkbox("Turbo", &GameHook::turbo_toggle);
            help_marker("Set a custom game speed");
            if (GameHook::turbo_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##TurboInputFloat", &GameHook::turboValue, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
				ImGui::Unindent();
            }
            ImGui::EndGroup();

			ImGui::SameLine(sameLineWidth);

            ImGui::BeginGroup();
            ImGui::Checkbox("Custom Camera Distance##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            help_marker("Replace the vanilla camera distance with a custom value");
            if (GameHook::customCameraDistance_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceInputFloat", &GameHook::customCameraDistance, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Character")) {
            ImGui::BeginChild("CharacterChild");

            ImGui::SeparatorText("Abilities");

            if (ImGui::Checkbox("Disable After Burner Bounce", &GameHook::disableAfterBurnerBounce_toggle)) {
                DisableAfterBurnerBounce(GameHook::disableAfterBurnerBounce_toggle);
            }
            help_marker("Disable the bounce that happens when you divekick into a wall or enemy while not holding kick");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Cancellable After Burner", &GameHook::cancellableAfterBurner_toggle);
            help_marker("Allow actions during After Burner such as dodge or jump");

            ImGui::Checkbox("Cancellable Falling Kick", &GameHook::cancellableFallingKick_toggle);
            help_marker("Allow actions during Falling Kick such as dodge or jump");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Taunt With Time Bracelet", &GameHook::tauntWithTimeBracelet_toggle)) {
                TauntWithTimeBracelet(GameHook::tauntWithTimeBracelet_toggle);
            }
            help_marker("Map Taunt to Dpad Down");

            ImGui::Checkbox("Lower Divekick Requirement", &GameHook::lowerDivekick_toggle);
            help_marker("Half the height requirement for Divekick");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Dual Gun After Burner", &GameHook::dualAfterBurner_toggle);
            help_marker("Shoot with both legs during After Burner, like in Bayonetta 2");


            if (ImGui::Checkbox("No Hold Dodge Offset", &GameHook::noHoldDodgeOffset_toggle)) {
                NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
            }
            help_marker("Dodge Offset without holding attack buttons");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Jump Offset", &GameHook::jumpOffset_toggle)) {
                JumpOffset(jumpOffset_toggle);
            }
            help_marker("Dodge Offset through jumps");

            if (ImGui::Checkbox("Weapon Swap Offset", &GameHook::weaponSwapOffset_toggle)) {
                WeaponSwapOffset(weaponSwapOffset_toggle);
            }
            help_marker("Offset through weapon swaps");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Parry Offset", &GameHook::parryOffset_toggle)) {
                ParryOffset(parryOffset_toggle);
            }
            help_marker("Offset through parries");

            ImGui::Checkbox("Longer Pillow Talk Charge", &longerPillowTalkCharge_toggle);
            help_marker("Double the charged duration on Pillow Talk");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Retain Pillow Talk Charge", &GameHook::retainPillowTalkCharge_toggle)) {
                RetainPillowTalkCharge(retainPillowTalkCharge_toggle);
            }
            help_marker("Pillow Talk will retain charge through weapon swaps");

            if (ImGui::Checkbox("Swap Mashes To Holds", &GameHook::swapMashToHold_toggle)) {
                SwapMashToHold(swapMashToHold_toggle);
            }
            help_marker("Swap mash inputs such as those used on Odette to hold inputs");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Always Walk On Walls", &GameHook::alwaysWalkOnWalls_toggle)) {
                AlwaysWalkOnWalls(alwaysWalkOnWalls_toggle);
            }
            help_marker("Walk on walls anywhere");

            if (ImGui::Checkbox("Disable Lockon Jump Dodge", &GameHook::disableLockOnDodge_toggle)) {
                GameHook::DisableLockOnDodge(GameHook::disableLockOnDodge_toggle);
            }
            help_marker("Disable the alternate dodge input, allowing you to jump in different directions while locked on");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Disable Double Tap Inputs", &GameHook::disableDoubleTapHeelKick_toggle)) {
                GameHook::DisableDoubleTapHeelKick(disableDoubleTapHeelKick_toggle);
            }
            ImGui::SameLine();
            help_marker("Stiletto, Heel Slide etc");

            if (ImGui::Checkbox("Standardized Witch Time", &GameHook::jeanneBayoWT_toggle)) {
                GameHook::JeanneBayoWT(GameHook::jeanneBayoWT_toggle);
            }
            help_marker("Give Jeanne Bayonetta's Witch Time activation leniency");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Alt Umbran Spear Input", &GameHook::altTeleInput_toggle);
            help_marker("Map Umbran Spear to lockon + L1. Move Taunt to dpad down");

            ImGui::Checkbox("Umbran Spear Omnicancel", &GameHook::omnicancelTele_toggle);
            help_marker("Cancel any animation with Umbral Spear");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Umbran Spear Offset", &GameHook::teleportComboAction_toggle);
            ImGui::SameLine();
            help_marker("Umbran spear will refresh your offset timer");

            ImGui::Checkbox("Longer Buffer Windows", &GameHook::longerBufferWindows_toggle);
            ImGui::SameLine();
            help_marker("Double the number of buffer frames avaialble for punch, kick, dodge, shoot");

            ImGui::SeparatorText("Cheats");

            if (ImGui::Checkbox("Infinite Jumps##InfJumpsToggle", &GameHook::infJumps_toggle)) {
                GameHook::InfJumps(GameHook::infJumps_toggle);
            }
            help_marker("Infinite jumps");

            ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Always Witch Time", &GameHook::alwaysWitchTime_toggle);
            help_marker("Activate Witch Time even with a mistimed dodge");

            if (ImGui::Checkbox("Infinite Divekicks", &GameHook::infDivekick_toggle)) {
                InfDivekick(infDivekick_toggle);
            }
            help_marker("Remove the limit on how many divekicks you can do before enemy stepping or touching the floor");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Infinite Crow Within", &GameHook::infBirdTime_toggle)) {
                InfBirdTime(infBirdTime_toggle);
            }
            help_marker("Freeze the timer on Crow Within");

            ImGui::BeginGroup();
            ImGui::Checkbox("Custom Witch Time Multiplier##WitchTimeToggle", &GameHook::witchTimeMultiplier_toggle);
            help_marker("Adjust how long Witch Time lasts");
            if (GameHook::witchTimeMultiplier_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##WitchTimeMultiplier", &GameHook::witchTimeMultiplier, 0.1f, 1.0f, "%.1f");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            ImGui::SameLine(sameLineWidth);

            ImGui::BeginGroup();
            ImGui::Checkbox("Freeze Magic##InfMagicToggle", &GameHook::infMagic_toggle);
            help_marker("Lock player magic to any value");
            if (GameHook::infMagic_toggle) {
                ImGui::Indent();
                ImGui::SetNextItemWidth(inputItemWidth);
                ImGui::SliderFloat("##InfiniteMagicValue", &GameHook::infMagic_value, 0, 1200);
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            if (ImGui::Checkbox("Unban Climax Brace", &GameHook::unbanClimaxBrace_toggle)) {
                GameHook::UnbanClimaxBrace(unbanClimaxBrace_toggle);
            }
            ImGui::SameLine();
            help_marker("Tick before entering a banned area (such as Angel Slayer)");

            DrawGlamour();

            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Current Character##Combo", &currentCharacterValue, "Bayonetta\0Jeanne\0Little King Zero\0");
            help_marker("Set while in costume select\nSets character specific mechanics, e.g. if you have a dodge cap\n"
                "If your game freezes at the end of a fight, flick the value back to default");

            ImGui::SameLine(sameLineWidth);

            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Current Costume##Combo", (int*)GameHook::currentCostumeAddress, costumeNames, IM_ARRAYSIZE(costumeNames));
            help_marker("Set while in mission select or before an area change\n");

            if (ImGui::Checkbox("Force Cutscene Face", &GameHook::forceCutsceneFace_toggle)) {
                GameHook::ForceCutsceneFace(GameHook::forceCutsceneFace_toggle);
            }

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Run With Guns", &GameHook::runWithGuns_toggle)) {
                GameHook::RunWithGuns(GameHook::runWithGuns_toggle);
            }
            help_marker("Stop your guns disappearing when you run");

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Environment")) {
            ImGui::BeginChild("EnvironmentChild");

            DrawAreaJump();

            DrawAngelSlayer();

            ImGui::SeparatorText("Enemy Spawner");

            static int selectedEnemyListbox = 0;
            if (ImGui::BeginListBox("##Enemy Spawn Listbox", ImVec2(-FLT_MIN, 20 * ImGui::GetTextLineHeightWithSpacing()))) {
                for (int i = 0; i < IM_ARRAYSIZE(spawnList); i++) {
                    const bool isSelected = (selectedEnemyListbox == i);
                    if (ImGui::Selectable(spawnList[i].name, isSelected)) {
                        selectedEnemyListbox = i;
                        const SpawnInfo& selected = spawnList[i];
                        GameHook::EasySpawnEntityFromHotkey(selected.id, selected.variant, selected.spawnModifier); // we use hotkey call to avoid custom settings
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }

            ImGui::Checkbox("Random Enemy Spawns", &GameHook::randomizeSpawns_toggle);
            help_marker("With how often this will crash or soft lock you, I advise using it in Angel Slayer. "
                "It is very funny seeing cutscenes with incorrect enemies in the story, but you will be spending most of your time restarting the game\n"
                "Spawn Modifier is set to 0 on every spawn, so randomized enemies are probably easy (e.g. the last boss in Angel Slayer has the last boss set to 6)\n"
                "Hit F11 (default) to attempt to kill all spawned enemies if you get softlocked");

            DrawEnemySwapper();

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("System")) {
            ImGui::BeginChild("SystemChild");

            ImGui::SeparatorText("Bayonetta");

            if (ImGui::Checkbox("Focus Patch", &GameHook::focusPatch_toggle)) {
                GameHook::FocusPatch(GameHook::focusPatch_toggle);
            }
            help_marker("Play while tabbed out\nUse with Force Input Type to disable keyboard button prompts");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Hide Halos", &GameHook::hideHalos_toggle)) {
                GameHook::HideHalos(GameHook::hideHalos_toggle);
            }
            help_marker("Hide the Halo display");

            ImGui::Checkbox("Enemy HP in Halo Display", &GameHook::haloDisplay_toggle);
            help_marker("Show the last hit enemy's HP in your Halo display. This only edits the display, your Halos are safe");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Disable Gradient", &GameHook::disableGradient_toggle)) {
                GameHook::DisableGradient(GameHook::disableGradient_toggle);
            }
            help_marker("Disable the gradient covering the game");

            if (ImGui::Checkbox("Skip Angel Attack", &GameHook::skipAngelAttack_toggle)) {
                GameHook::SkipAngelAttack(skipAngelAttack_toggle);
            }

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Skip Post-Chapter Map Scene", &GameHook::skipMapScene_toggle)) {
                GameHook::SkipMapScene(skipMapScene_toggle);
            }
            help_marker("Load Mission Select instead of Angel Attack. You will miss out on Halos and items.");

            if (ImGui::Checkbox("60 FPS Cutscenes", &GameHook::sixtyFpsCutscenes_toggle)) {
                GameHook::SixtyFpsCutscenes(GameHook::sixtyFpsCutscenes_toggle);
            }
            help_marker("Cutscenes play at 60fps instead of 30");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Easy Cutscene Skip", &GameHook::easyCutsceneSkip_toggle)) {
                GameHook::EasyCutsceneSkip(GameHook::easyCutsceneSkip_toggle);
            }
            help_marker("Skip skippable cutscenes with r2");

            if (ImGui::Checkbox("Get More Halos", &GameHook::getMoreHalos_toggle)) {
                GameHook::GetMoreHalos(GameHook::getMoreHalos_toggle);
            }
            help_marker("Pick up Halos from further away");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Freeze Timers", &GameHook::freezeTimer_toggle)) {
                GameHook::FreezeTimer(GameHook::freezeTimer_toggle);
            }
            help_marker("Freeze Alfheim timers");

            ImGui::Checkbox("Easier Mashing##EasierMashToggle", &GameHook::easierMash_toggle);
            help_marker("Make mash QTEs more reasonable");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Auto Complete QTEs", &GameHook::autoQTE_toggle)) {
                GameHook::AutoQTE(GameHook::autoQTE_toggle);
            }
            help_marker("Does not auto complete torture attacks (because then you'd do it on every enemy you stand next to)");

            ImGui::BeginGroup();
            ImGui::Checkbox("Force Input Type", &GameHook::inputIcons_toggle);
            help_marker("Force the game to display either keyboard/mouse or gamepad input icons. Disallows certain inputs (such as mouse movement) when forcing gamepad");
            if (GameHook::inputIcons_toggle) {
                ImGui::Indent();
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::Combo("##InputTypeCombo", &GameHook::inputIconsValue, "Keyboard\0Gamepad\0");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            ImGui::EndGroup();

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Disable Tutorials", &disableTutorials_toggle)) {
                GameHook::DisableTutorials(disableTutorials_toggle);
            }

            ImGui::Checkbox("Alow setting third accessory", &allowSettingThirdAccessory_toggle);
            help_marker("When setting an accessory in the menu, press down to access the third slot");

			ImGui::SeparatorText("BayoHook");

            ImGui::Checkbox("Show Hotkey Messages", &GameHook::showMessages_toggle);
            help_marker("Show text in the corner of the screen when a hotkey is activated");

			ImGui::SameLine(sameLineWidth);

            ImGui::Checkbox("Save/Load Animation Hotkeys", &GameHook::saveStatesHotkeys_toggle);
            help_marker("Enable/Disable the HOME and END enemy save state hotkeys");


            DrawBayoHookSettings();

            ImGui::SeparatorText("FPS");

            DrawUptimeFix();
            DrawFPSUnlock();

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Extra")) {
            ImGui::BeginChild("ExtraChild");

            ImGui::SeparatorText("Debug Drawing");

            ImGui::Checkbox("Draw Player Bones (WIP)", &GameHook::drawPlayerBones_toggle);
			ImGui::Checkbox("Draw Stats (WIP)", &GameHook::drawStats_toggle);
            ImGui::Checkbox("Draw Hitboxes (WIP)", &GameHook::drawHitboxes_toggle);

            ImGui::SeparatorText("Custom Combo Routes");

            ImGui::Checkbox("Move ID Swaps", &moveIDSwaps_toggle);
            help_marker("Replace one move with another\n"
                "Do the move you want to replace, pause mid anim, type your current moveID in the first box\n"
                "Do the move you want to see, pause mid anim, type your current moveID in the second box\n"
                "Don't forget to save once you're done for next boot!");
            if (GameHook::moveIDSwaps_toggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInMoveIDSwaps", &player->moveID, moveIDNames, IM_ARRAYSIZE(moveIDNames));
                    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
                        ImGui::Checkbox(("Move Swap[" + std::to_string(i + 1) + "]").c_str(), &moveIDSwap_toggles[i]);
                        if (GameHook::moveIDSwap_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("Replace Move ID");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##CurrentMoveIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSourceMoves[i], 0, 0);
                            ImGui::Combo(("##SourceMoveIDComboInMoveIDSwap" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSourceMoves[i], moveIDNames, IM_ARRAYSIZE(moveIDNames));
                            ImGui::SameLine();
                            ImGui::Text("with");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##DesiredMoveIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSwappedMoves[i]);
                            ImGui::Combo(("##DesiredMoveIDComboInMoveIDSwap" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSwappedMoves[i], moveIDNames, IM_ARRAYSIZE(moveIDNames));
                            ImGui::PopItemWidth();
                        }
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("Combo Maker", &GameHook::comboMaker_toggle);
            help_marker("Compare your moveid and distance into current string to set a new string ID");
            if (GameHook::comboMaker_toggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInComboMaker", &player->moveID, moveIDNames, IM_ARRAYSIZE(moveIDNames));
                    ImGui::Text("Current Number In String: %i", player->attackCount);
                    ImGui::Text("Current String ID: %i", player->stringID);
                    for (int i = 0; i < maxComboMakers; ++i) {
                        ImGui::Checkbox(("Combo Maker[" + std::to_string(i + 1) + "]").c_str(), &comboMaker_toggles[i]);
                        if (comboMaker_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("if Move ID ==");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##ComboMakerMoveID" + std::to_string(i) + "InputInt").c_str(), &comboMakerMoveIDs[i]);
                            ImGui::Combo(("##MoveIDInComboMaker" + std::to_string(i)).c_str(), &GameHook::comboMakerMoveIDs[i], moveIDNames, IM_ARRAYSIZE(moveIDNames));
                            ImGui::Text("and current attack number in string ==");
                            ImGui::SameLine();
                            ImGui::InputInt(("##ComboMakerMovePart" + std::to_string(i) + "InputInt").c_str(), &comboMakerMoveParts[i]);
                            ImGui::Text("then String ID =");
                            ImGui::SameLine();
                            ImGui::InputInt(("##ComboMakerStringID" + std::to_string(i)).c_str(), &comboMakerStringIDs[i]);
                            ImGui::PopItemWidth();
                            ImGui::Separator();
                        }
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("Weave Swaps", &GameHook::customWeave_toggle);
            help_marker("Replace one weave with another");
            if (GameHook::customWeave_toggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInWeaveSwaps", &player->moveID, moveIDNames, IM_ARRAYSIZE(moveIDNames));
                    for (int i = 0; i < customWeaveCount; ++i) {
                        ImGui::Checkbox(("Custom Weave[" + std::to_string(i + 1) + "]").c_str(), &customWeaves_toggles[i]);
                        if (customWeaves_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("If Move ID ==");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##customWeaveMoveIDArray" + std::to_string(i)).c_str(), &customWeaveMoveIDArray[i]);
                            ImGui::Combo(("##customWeaveMoveIDArray" + std::to_string(i)).c_str(), &GameHook::customWeaveMoveIDArray[i], moveIDNames, IM_ARRAYSIZE(moveIDNames));
                            //ImGui::SameLine(); if (ImGui::Button("Clear##customWeaveMoveIDArray")) { GameHook::customWeaveMoveIDArray[i] = -1; }
                            ImGui::PopItemWidth();
                            ImGui::Text("then Weave ID ==");
                            ImGui::SameLine();
                            ImGui::Combo(("##customWeaveArray" + std::to_string(i)).c_str(), &customWeaveArray[i], weaveNames, IM_ARRAYSIZE(weaveNames));
                            //ImGui::SameLine(); if (ImGui::Button("Clear##customWeaveArray")) { GameHook::customWeaveArray[i] = -1; }
                            ImGui::Separator();
                        }
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("String Swaps", &GameHook::stringSwaps_toggle);
            help_marker("Replace one string with another");
            if (GameHook::stringSwaps_toggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current String ID: %i", player->stringID);
                    for (int i = 0; i < GameHook::maxStringSwaps; ++i) {
                        ImGui::Checkbox(("String Swap[" + std::to_string(i + 1) + "]").c_str(), &stringIDSwap_toggles[i]);
                        if (GameHook::stringIDSwap_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("Replace String ID");
                            ImGui::SameLine();
                            ImGui::InputInt(("##SourceStringIDInputInt" + std::to_string(i)).c_str(), &GameHook::stringIDSwapSourceStrings[i]);
                            ImGui::SameLine();
                            ImGui::Text("with");
                            ImGui::SameLine();
                            ImGui::InputInt(("##DesiredStringIDInputInt" + std::to_string(i)).c_str(), &GameHook::stringIDSwapDesiredStrings[i]);
                            ImGui::PopItemWidth();
                            ImGui::Separator();
                        }
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::SeparatorText("Other");

            if (ImGui::Checkbox("Multiplayer Camera Patch", &GameHook::multiplayerPatch_toggle)) {
                GameHook::MultiplayerPatch(GameHook::multiplayerPatch_toggle);
            }
            help_marker("Stops the camera jumping between multiple spawned player characters that are controlled by the same player");

            ImGui::SeparatorText("Co-op");

            static int g_selected_character = 0;
            const char* preview = coop_characters[g_selected_character].name;

            ImGui::SetNextItemWidth(inputItemWidth * 2.0f);
            if (ImGui::BeginCombo("Player 2 Character", preview)) {
                for (int i = 0; i < IM_ARRAYSIZE(coop_characters); i++) {
                    bool selected = (g_selected_character == i);
                    if (ImGui::Selectable(coop_characters[i].name, selected)) {
                        g_selected_character = i;
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button("Spawn Player 2")) {
                int id = coop_characters[g_selected_character].id;
                GameHook::EasySpawnEntityFromHotkey(id, 1, 0);
            }

            LocalPlayer* player1 = GetPlayer1();
            LocalPlayer* player2 = GameHook::GetPlayer2();
            if (player1 && player2) {

                ImGui::SameLine(GameHook::sameLineWidth);

                if (ImGui::Button("Teleport Player 2 to Player 1")) {
                    LocalPlayer* player1 = GetLocalPlayer();
                    LocalPlayer* player2 = GameHook::GetPlayer2();
                    if (player1 && player2)
                        player2->pos = player1->pos;
                }

                ImGui::PushItemWidth(GameHook::inputItemWidth);

                int readablePlayer1Controller = player1->controllerNum + 1;
                int readablePlayer2Controller = player2->controllerNum + 1;

                if (ImGui::SliderInt("Player 1 Controller", &readablePlayer1Controller, 1, 2))
                    player1->controllerNum = readablePlayer1Controller - 1;

                ImGui::SameLine(GameHook::sameLineWidth);

                if (ImGui::SliderInt("Player 2 Controller", &readablePlayer2Controller, 1, 2))
                    player2->controllerNum = readablePlayer2Controller - 1;

                ImGui::PopItemWidth();

                ImGui::BeginGroup();
                if (ImGui::Button("Register player 1 as an enemy")) {
                    using RegisterFn = void(__thiscall*)(void* manager, void* obj);
                    player1->beFlag |= (BE_EM | BE_LOCKENABLE);
                    auto registerFn = (RegisterFn)0x00499FC0;
                    void* enemyList = (void*)0x5A569F0;
                    registerFn(enemyList, player1);
                }
                if (ImGui::Button("Unregister player 1 as an enemy")) {
                    using RegisterFn = void(__thiscall*)(void* manager, void* obj);
                    player1->beFlag &= ~(BE_EM | BE_LOCKENABLE);
                    auto registerFn = (RegisterFn)0x49A050;
                    void* enemyList = (void*)0x5A569F0;
                    registerFn(enemyList, player1);
                }
                ImGui::EndGroup();

                ImGui::SameLine(sameLineWidth);

                ImGui::BeginGroup();
                if (ImGui::Button("Register player 2 as an enemy")) {
                    using RegisterFn = void(__thiscall*)(void* manager, void* obj);
                    player2->beFlag |= (BE_EM | BE_LOCKENABLE);
                    auto registerFn = (RegisterFn)0x00499FC0;
                    void* enemyList = (void*)0x5A569F0;
                    registerFn(enemyList, player2);
                }
                if (ImGui::Button("Unregister player 2 as an enemy")) {
                    using RegisterFn = void(__thiscall*)(void* manager, void* obj);
                    player2->beFlag &= ~(BE_EM | BE_LOCKENABLE);
                    auto registerFn = (RegisterFn)0x49A050;
                    void* enemyList = (void*)0x5A569F0;
                    registerFn(enemyList, player2);
                }
                ImGui::EndGroup();
            }

            ImGui::Checkbox("Friendly Fire", &GameHook::pvp_toggle); // outside of if() so people can still disable it when no p2 spawned
            help_marker("How to PVP:\n- Spawn Player 2\n- Register both players as enemies\n- Tick \"Enable Friendly Fire\"\n"
                "Friendly fire can be used outside of PVP to make co-op a little more entertaining");

            if (ImGui::CollapsingHeader("pvp debug")) {
                ImGui::Checkbox("GameHook::pvpDamageRemaps_toggle", &GameHook::pvpDamageRemaps_toggle);
                ImGui::InputScalar("Last seen atk", ImGuiDataType_U32, &GameHook::lastSeenAtk, NULL, NULL, "%X", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::InputScalar("Last seen atk converted", ImGuiDataType_U32, &GameHook::lastSeenAtkConverted, NULL, NULL, "%X", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::InputScalar("atkTest", ImGuiDataType_U32, &GameHook::atkTest, NULL, NULL, "%X", ImGuiInputTextFlags_CharsHexadecimal);
                help_marker("test a different knockback type on an pvp attack by inserting its ID here");
                ImGui::InputScalar("atkTestReplacement", ImGuiDataType_U32, &GameHook::atkTestReplacement, NULL, NULL, "%X", ImGuiInputTextFlags_CharsHexadecimal);
            }

            // entity spawn stuff
            {
                const int knownEntityCount = sizeof(knownEntities) / sizeof(knownEntities[0]);
                static std::string enemyDisplayNames[knownEntityCount];
                static bool initialized = false;

                if (!initialized) {
                    for (int i = 0; i < knownEntityCount; i++) {
                        char buffer[64];
                        snprintf(buffer, sizeof(buffer), "0x%08X - %s", knownEntities[i].id, knownEntities[i].name);
                        enemyDisplayNames[i] = buffer;
                    }
                    initialized = true;
                }

                const char* displayNames[knownEntityCount];
                for (int i = 0; i < knownEntityCount; i++) {
                    displayNames[i] = enemyDisplayNames[i].c_str();
                }

                const char* enemyNames[knownEntityCount];
                for (int i = 0; i < knownEntityCount; i++) {
                    enemyNames[i] = knownEntities[i].name;
                }

                ImGui::SeparatorText("Entity Spawning");
                static int selectedEnemy = 50;

                if (ImGui::CollapsingHeader("Detailed Custom Spawn Settings")) {
                    static constexpr int step = 1;
                    if (ImGui::Combo("Known Entity IDs", &selectedEnemy, displayNames, knownEntityCount)) {
                        GameHook::guiEntitySpawn.entityID = knownEntities[selectedEnemy].id;
                    }
                    ImGui::SameLine();
                    help_marker("This just autofills the previous field if you want to pick from a dictionary of IDs we already know");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputScalar("ID##EntityIDDetailed", ImGuiDataType_S32, &guiEntitySpawn.entityID, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::SameLine();
                    help_marker("This is for typing in a manual ID. You will crash if you type in an invalid ID");
                    ImGui::InputScalar("arg2.int_0", ImGuiDataType_S32, &guiEntitySpawn.settings.int_0, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    help_marker("Unknown. 1 can break spawns. The game seems to set these properly per enemy");
                    ImGui::InputScalar("arg2.int_4_Variant", ImGuiDataType_S32, &guiEntitySpawn.settings.int_4_Variant, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    help_marker("Some enemies use the same ID but a different variant");
                    ImGui::InputScalar("arg2.int_8_SpawnModifier", ImGuiDataType_S32, &guiEntitySpawn.settings.int_8_SpawnModifier, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    help_marker("Can affect enemy HP and how an enemy acts");
                    ImGui::InputScalar("arg2.int_C", ImGuiDataType_S32, &guiEntitySpawn.settings.int_C, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputScalar("arg2.int_10", ImGuiDataType_S32, &guiEntitySpawn.settings.int_10, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputFloat("arg2.float_14_RotX", &guiEntitySpawn.settings.float_14_RotX);
                    ImGui::InputFloat("arg2.float_18_RotY", &guiEntitySpawn.settings.float_18_RotY);
                    ImGui::InputFloat("arg2.float_1C_RotZ", &guiEntitySpawn.settings.float_1C_RotZ);
                    ImGui::InputScalar("arg2.int_20", ImGuiDataType_S32, &guiEntitySpawn.settings.int_20, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputFloat("arg2.float_24", &guiEntitySpawn.settings.float_24);
                    ImGui::InputFloat("arg2.float_28", &guiEntitySpawn.settings.float_28);
                    ImGui::InputFloat("arg2.float_2C", &guiEntitySpawn.settings.float_2C);
                    ImGui::InputFloat("arg2.float_30_ScaleX", &guiEntitySpawn.settings.float_30_ScaleX);
                    ImGui::InputFloat("arg2.float_34", &guiEntitySpawn.settings.float_34);
                    ImGui::InputFloat("arg2.float_38", &guiEntitySpawn.settings.float_38);
                    ImGui::InputFloat("arg2.float_3C", &guiEntitySpawn.settings.float_3C);
                    ImGui::InputFloat("arg2.float_40", &guiEntitySpawn.settings.float_40);
                    ImGui::InputFloat("arg2.float_44_ScaleY", &guiEntitySpawn.settings.float_44_ScaleY);
                    ImGui::InputFloat("arg2.float_48", &guiEntitySpawn.settings.float_48);
                    ImGui::InputFloat("arg2.float_4C", &guiEntitySpawn.settings.float_4C);
                    ImGui::InputFloat("arg2.float_50", &guiEntitySpawn.settings.float_50);
                    ImGui::InputFloat("arg2.float_54", &guiEntitySpawn.settings.float_54);
                    ImGui::InputFloat("arg2.float_58_ScaleZ", &guiEntitySpawn.settings.float_58_ScaleZ);
                    ImGui::InputFloat("arg2.float_5C", &guiEntitySpawn.settings.float_5C);
                    ImGui::InputFloat("arg2.float_60", &guiEntitySpawn.settings.float_60);
                    ImGui::InputFloat("arg2.float_64", &guiEntitySpawn.settings.float_64);
                    ImGui::InputFloat("arg2.float_68", &guiEntitySpawn.settings.float_68);
                    ImGui::InputFloat("arg2.float_6C", &guiEntitySpawn.settings.float_6C);
                    ImGui::InputFloat3("arg2.float_70_X", &guiEntitySpawn.settings.float_70_X);
                    help_marker("These fields will always autofill with character pos upon pressing spawn");
                    ImGui::InputFloat("arg2.float_7C", &guiEntitySpawn.settings.float_7C);
                    ImGui::InputScalar("arg2.int_80", ImGuiDataType_S32, &guiEntitySpawn.settings.int_80, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputScalar("arg2.int_84", ImGuiDataType_S32, &guiEntitySpawn.settings.int_84, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputScalar("arg2.int_88", ImGuiDataType_S32, &guiEntitySpawn.settings.int_88, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::InputFloat("arg2.float_8C", &guiEntitySpawn.settings.float_8C);
                    ImGui::InputFloat("arg2.float_90", &guiEntitySpawn.settings.float_90);
                    ImGui::InputFloat("arg2.float_94", &guiEntitySpawn.settings.float_94);
                    ImGui::InputText("arg2.string_98", guiEntitySpawn.settings.string_98, sizeof(guiEntitySpawn.settings.string_98));
                    ImGui::InputFloat("arg2.float_A0", &guiEntitySpawn.settings.float_A0);
                    ImGui::PopItemWidth();

                    if (ImGui::Button("Spawn")) {
                        LocalPlayer* player = GetLocalPlayer();
                        if (player) {
                            guiEntitySpawn.settings.float_70_X = player->pos.x;
                            guiEntitySpawn.settings.float_74_Y = player->pos.y + 1.0f;
                            guiEntitySpawn.settings.float_78_Z = player->pos.z;
                        }
                        GameHook::spawnEntityFromGui = true;
                    }
                }

                if (ImGui::CollapsingHeader("Simplified Custom Spawn Settings")) {
                    static constexpr int step = 1;
                    ImGui::SetNextItemWidth(inputItemWidth);
                    ImGui::InputScalar("ID##EntityIDSimplified", ImGuiDataType_S32, &guiEntitySpawn.entityID, &step, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    ImGui::SameLine();
                    if (ImGui::Combo("ID##Easy", &selectedEnemy, displayNames, knownEntityCount)) {
                        GameHook::guiEntitySpawn.entityID = knownEntities[selectedEnemy].id;
                    }

                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputScalar("Variant##Easy", ImGuiDataType_S32, &guiEntitySpawn.settings.int_4_Variant, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    help_marker("Some enemies use the same ID but a different variant");
                    ImGui::InputScalar("Spawn Modifier##Easy", ImGuiDataType_S32, &guiEntitySpawn.settings.int_8_SpawnModifier, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                    help_marker("Can affect enemy HP and how an enemy acts");
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Entity##Easy")) {
                        GameHook::EasySpawnEntityFromGui(guiEntitySpawn.entityID, guiEntitySpawn.settings.int_4_Variant, guiEntitySpawn.settings.int_8_SpawnModifier);
                    }
                }
            }

            ImGui::Checkbox("Log Spawns", &GameHook::viewEntitySpawns_toggle);
            GameHook::help_marker("View the ID/arg combos used by the game to spawn entities to aid learning for our own spawner.\n"
                "This is pretty crashy so be sure to enable/disable it around spawns you wish to observe");
            ImGui::Indent();
            GameHook::DisplayRecentlySpawnedEntitiesInImGui();
            ImGui::Unindent();

            ImGui::Checkbox("List all seen effect IDs", &GameHook::identifyEffects_toggle);
            if (GameHook::identifyEffects_toggle) {
				ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 1.0f, 0.0f), ImGuiCond_Once, ImVec2(1.0f, 0));
				ImGui::SetNextWindowSize(ImVec2(ImGui::GetFontSize() * 8, ImGui::GetIO().DisplaySize.y * 1.0f), ImGuiCond_Once);
                ImGui::Begin("Effect ID Panel");
                ImGui::BeginChild("EffectsChild");
                ImGui::Text("Seen Effect IDs:");
                if (ImGui::Button("Clear##SeenEffectIDsClearButton")) {
                    GameHook::seenEffectIDs.clear();
                }
                for (int id : GameHook::seenEffectIDs) {
                    ImGui::Text("0x%X", id);
                }
                ImGui::EndChild();
                ImGui::End();
            }

            ImGui::Checkbox("Custom Effect Colours", &GameHook::customEffectColours_toggle);
            if (GameHook::customEffectColours_toggle) {
                static int step = 1;
                static int stepBig = 10;
                ImGui::Text("Only edit effects that match this ID");
                ImGui::Text("Set to FFFFFFFF to edit all effects");
                ImGui::InputScalar("##Only edit effects that match this ID InputScalar", ImGuiDataType_U32, &customEffectColoursRestrictionID, &step, &stepBig, "%08X");
				ImGui::ColorPicker4("Colour##EffectColorPicker", &GameHook::effectCol[0].Value.x);
            }

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Stats")) {
            ImGui::BeginChild("StatsChild");

            if (ImGui::CollapsingHeader("Stats")) {
                ImGui::TreePush("StatsTree");
                ImGui::Checkbox("HUD Display", &hudDisplayValue);
                help_marker("Show HP etc");

                ImGui::SetNextItemWidth(inputItemWidth * 2.0f);
                ImGui::InputInt("Halos##HaloInputInt", &halosValue, 1, 100);

                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("Chapters Played##ChapterInputInt", &chaptersPlayedValue, 1, 100);
                ImGui::InputInt("Combo Points##ComboPointsInputInt", &comboPointsValue, 10, 100);
                ImGui::InputFloat("Combo Multiplier##ComboMultiplierInputFloat", &comboMultiplierValue, 1, 10, "%.1f");
                ImGui::PopItemWidth();

                ImGui::Text("Weapon Set A:");
                help_marker("WIP, requires entering and exiting the weapon select menu to apply");
                ImGui::PushItemWidth(inputItemWidth * 2.0f);
                ImGui::Combo("##WeaponA1InputInt", &weaponA1Value, weaponNames, IM_ARRAYSIZE(weaponNames));
                ImGui::Combo("##WeaponA2InputInt", &weaponA2Value, weaponNames, IM_ARRAYSIZE(weaponNames));
                ImGui::Text("Weapon Set B:");
                ImGui::Combo("##WeaponB1InputInt", &weaponB1Value, weaponNames, IM_ARRAYSIZE(weaponNames));
                ImGui::Combo("##WeaponB2InputInt", &weaponB2Value, weaponNames, IM_ARRAYSIZE(weaponNames));
                ImGui::PopItemWidth();
                if (ImGui::Button("Call Weapon Swap")) {
                    GameHook::WeaponSwapCaller();
                }
                help_marker("Attempt to refresh weapons without a pause\nRequires changing a weapon manually in the weapon select menu once to load weapons initially.");

                ImGui::TreePop();
            }

            /*ImGui::Checkbox("Get Mot Names", &GameHook::getMotName_toggle);
            if (GameHook::getMotName_toggle) {
                ImGui::Text("Player Mot");
                if (GameHook::getMotName_playerMotString)
                    ImGui::Text(GameHook::getMotName_playerMotString);
                else
                    ImGui::Text("");
                ImGui::Text("Weapon Mot");
                if (GameHook::getMotName_weaponMotString)
                    ImGui::Text(GameHook::getMotName_weaponMotString);
                else
                    ImGui::Text("");
            }*/

            if (ImGui::CollapsingHeader("Player Stats")) {
                ImGui::TreePush("PlayerStatsTree");
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    float& playerMagicValue = *(float*)GameHook::playerMagicAddress; // not player offset but keeping it here anyway

                    ImGui::Separator();

                    ImGui::InputFloat3("Position##PlayerPositionInputFloat3", &player->pos.x);
                    if (ImGui::Button("Teleport to 0, 0, 0")) {
                        player->pos = { 0.0f, 0.0f, 0.0f };
                    }
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::SliderInt("HP##PlayerHPDamageInputInt", &player->hp, 0, player->hpMax);
                    ImGui::InputFloat("MP##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");
                    ImGui::InputFloat("Remaining Witch Time Duration##PlayerRemainingWitchTimeDurationInputFloat", &player->witchTimeDuration, 10, 100, "%.0f");
                    ImGui::InputFloat("Remaining Invinciblity##PlayerRemainingInvinciblityInputFloat", &player->iFramesRemaining, 10, 100, "%.0f");
                    ImGui::SliderFloat("Animation Frame##PlayerAnimationFrameInputFloat", &player->animFrame, 0, player->animFrameMax, "%.0f");
                    //ImGui::InputInt("Move ID##PlayerMoveIDInputInt", &player->moveID);
                    ImGui::SetNextItemWidth(inputItemWidth * 3.0f);
                    ImGui::Combo("Move ID##PlayerMoveIDCombo", &player->moveID, moveIDNames, IM_ARRAYSIZE(moveIDNames));
                    ImGui::InputInt("Move Part##PlayerMovePartInputInt", &player->movePart);
                    ImGui::InputInt("String ID##PlayerStringIDInputInt", &player->stringID);
                    ImGui::InputInt("Attack Count##PlayerAttackCountInputInt", &player->attackCount);
                    ImGui::PopItemWidth();
                    ImGui::ColorEdit3("Hair Colour##PlayerHairColourEdit3", &player->colouredHairIntensityRGB.x);
                    ImGui::SameLine();
                    if (ImGui::Button("Reset##ResetHairColourButton")) {
                        player->colouredHairIntensityRGB = { 1.0f, 1.0f, 1.0f };
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
                ImGui::TreePop();
            }

            if (ImGui::CollapsingHeader("Locked On Enemy Stats")) {
                ImGui::TreePush("LockedOnEnemyStatsTree");
                Enemy* enemy = *(Enemy**)GameHook::enemyLockedOnAddress;
                if (enemy) {
                    ImGui::Separator();
                    ImGui::InputFloat3("Position##EnemyXYZPosInputFloat", &enemy->pos.x);
                    ImGui::InputInt("HP##EnemyHPInputInt", &enemy->hp, 10, 100);
                    ImGui::InputInt("Move ID##EnemyMoveIDInputInt", &enemy->moveID);
                    ImGui::InputFloat("Daze##EnemyDazeBuildupInputFloat", &enemy->daze, 10, 100, "%.0f");
                    ImGui::InputFloat("Daze Duration##EnemyDazeDurationInputFloat", &enemy->dazeCurrentDuration, 10, 100, "%.0f");

                    ImGui::Checkbox("Enable Save/Load Hotkeys", &GameHook::saveStatesHotkeys_toggle);
                    help_marker("Home = Save\nEnd = Load");
                    ImGui::Text("SaveState");
                    help_marker("Save and load an enemy's position and animation");
                    if (ImGui::Button("Save State")) {
                        GameHook::SaveStates_SaveState();
                    }
                    if (ImGui::Button("Load State")) {
                        GameHook::SaveStates_LoadState();
                    }
                }
                else
                    ImGui::Text("Lock on to an enemy to see these stats");
                ImGui::TreePop();
            }

            if (ImGui::CollapsingHeader("PlayerTracker")) {
                ImGui::TreePush("PlayerStatsTree");
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Player Structure Data");
                    ImGui::Text("+0 vtable: 0x%p", (void*)player->vtable);
                    ImGui::InputFloat3("+D0 pos", &player->pos.x);
                    ImGui::InputFloat3("+F0 scale", &player->scale.x);
                    ImGui::InputFloat("+314 camHeight", &player->camHeight);
                    ImGui::InputFloat("+324 alpha", &player->alpha);
                    // ImGui::InputInt("+34C moveID", &player->moveID);
                    ImGui::Combo("+34C moveID", &player->moveID, moveIDNames, IM_ARRAYSIZE(moveIDNames));
                    ImGui::InputInt("+350 movePart", &player->movePart);
                    ImGui::InputInt("+354 invincibility", &player->invincibility);
                    ImGui::InputInt("+358 controllerNum", &player->controllerNum);
                    ImGui::InputFloat("+3E4 animFrame", &player->animFrame);
                    ImGui::InputFloat("+4C4 speed", &player->speed);
                    ImGui::InputInt("+69C aerial", &player->aerial);
                    ImGui::InputInt("+6B4 hp", &player->hp, 10, player->hpMax);
                    ImGui::InputFloat("+6CC slowmo", &player->speed);
                    ImGui::InputFloat("+730 iFramesRemaining", &player->iFramesRemaining);
                    ImGui::InputFloat3("+CC0 colouredHairDurationRGB", &player->colouredHairDurationRGB.x);
                    ImGui::InputFloat("+CCC colouredHairTimer", &player->colouredHairTimer);
                    ImGui::Text("+5BC0 laserSword: 0x%p", (void*)player->laserSword);
                    ImGui::Indent();
                    ImGui::InputFloat("+6cc buffDrainRate", &player->laserSword->buffDrainRate);
                    ImGui::InputFloat("+332c buffRemainingDuration", &player->laserSword->buffRemainingDuration);
                    ImGui::InputFloat("+3330 length", &player->laserSword->length);
                    ImGui::Unindent();
                    ImGui::Text("+9224C bayoSkeleton: 0x%p", (void*)player->bayoSkeleton);
                    ImGui::Checkbox("+93104 clip", &player->clip);
                    ImGui::InputInt("+93508 hpUnk", &player->hpUnk);
                    ImGui::InputFloat("+9351C birdTimer", &player->birdTimer);
                    ImGui::InputInt("+93578 wallJumpCount", &player->wallJumpCount);
                    ImGui::InputFloat("+9358C divekickCount2", &player->divekickCount2);
                    ImGui::InputInt("+935E4 m_JoySpinCnt", &player->m_JoySpinCnt);
                    ImGui::Text("+93710 summoningHair: 0x%p", (void*)player->summoningHair);
                    ImGui::Text("+93714 summoningBody: 0x%p", (void*)player->summoningBody);
                    ImGui::Text("+937C0 handWeave: 0x%p", (void*)player->handWeave);
                    ImGui::Indent();
                    ImGui::InputFloat3("+F0 scale##handweave", &player->handWeave->scale.x);
                    ImGui::Unindent();
                    ImGui::Text("+937C4 idkWeave1: 0x%p", (void*)player->idkWeave1);
                    ImGui::Indent();
                    ImGui::InputFloat3("+F0 scale##idkweave1", &player->idkWeave1->scale.x);
                    ImGui::Unindent();
                    ImGui::Text("+937C8 idkWeave2: 0x%p", (void*)player->idkWeave2);
                    ImGui::Indent();
                    ImGui::InputFloat3("+F0 scale##idkweave2", &player->idkWeave2->scale.x);
                    ImGui::Unindent();
                    ImGui::Text("+937CC idkWeave3: 0x%p", (void*)player->idkWeave3);
                    ImGui::Indent();
                    ImGui::InputFloat3("+F0 scale##idkweave3", &player->idkWeave3->scale.x);
                    ImGui::Unindent();
                    ImGui::Text("+937D0 legWeave: 0x%p", (void*)player->legWeave);
                    ImGui::Indent();
                    ImGui::InputFloat3("+F0 scale##legweave", &player->legWeave->scale.x);
                    ImGui::Unindent();
                    ImGui::InputFloat("+93A04 m_RhythmTimer", &player->m_RhythmTimer);
                    ImGui::InputInt("+93A10 m_bRhythmActionSuccess", &player->m_bRhythmActionSuccess);
                    ImGui::InputInt("+93A1C m_RapidType", &player->m_RapidType);
                    ImGui::InputFloat("+93A20 m_RapidActRate", &player->m_RapidActRate);
                    ImGui::InputFloat("+93A24 m_RapidActMinusTimer", &player->m_RapidActMinusTimer);
                    ImGui::InputFloat("+93A28 m_RapidActMinusWait", &player->m_RapidActMinusWait);
                    ImGui::InputFloat("+93A2C m_RapidActMinusTimer2", &player->m_RapidActMinusTimer2);
                    ImGui::Text("+93AC0 rightHand: 0x%p", (void*)&player->rightHand);
                    ImGui::Indent();
                    ImGui::Checkbox("+74 isShooting##rightHand", &player->rightHand.isShooting);
                    ImGui::Unindent();
                    ImGui::Text("+93C50 leftHand: 0x%p", (void*)&player->leftHand);
                    ImGui::Indent();
                    ImGui::Checkbox("+74 isShooting##leftHand", &player->leftHand.isShooting);
                    ImGui::Unindent();
                    ImGui::Text("+93DE0 rightLeg: 0x%p", (void*)&player->rightLeg);
                    ImGui::Indent();
                    ImGui::Checkbox("+74 isShooting##rightLeg", &player->rightLeg.isShooting);
                    ImGui::Unindent();
                    ImGui::Text("+93DE0 leftLeg: 0x%p", (void*)&player->leftLeg);
                    ImGui::Indent();
                    ImGui::Checkbox("+74 isShooting##leftLeg", &player->leftLeg.isShooting);
                    ImGui::Unindent();
                    ImGui::InputInt("+94794 dodgeCount", &player->dodgeCount);
                    ImGui::InputFloat("+94878 batWithinFrames", &player->batWithinFrames, 10, 100, "%.0f");
                    ImGui::InputInt("+94A90 clothesRelated3", &player->clothesRelated3);
                    ImGui::InputInt("+94A94 clothesRelated2", &player->clothesRelated2);
                    ImGui::InputInt("+94B44 inputsHold", &player->inputsHold);
                    ImGui::InputInt("+94B48 inputsDown", &player->inputsDown);
                    ImGui::InputInt("+94B4C inputsUp", &player->inputsUp);
                    ImGui::InputInt("+94C00 hideEverythingInCutscene", &player->hideEverythingInCutscene);
                    ImGui::InputInt("+95C64 stringID", &player->stringID);
                    ImGui::InputFloat("+95C80 comboTimer", &player->comboTimer, 10, 100, "%.0f");
                    ImGui::Checkbox("+95C8C isWhipSlap", &player->isWhipSlap);
                    for (int j = 0; j < 7; ++j) {
                        ImGui::Combo(("+95C94 comboHit[" + std::to_string(j) + "]").c_str(), &player->comboHit[j], "None\0Punch\0Kick\0Late Punch\0Late Kick\0");
                    }
                    ImGui::InputInt("+95CBC attackCount", &player->attackCount);
                    ImGui::InputFloat("+95D5C witchTimeDuration", &player->witchTimeDuration, 10, 100, "%.0f");
                    ImGui::InputFloat("+95D60 witchTimeMaxProbably", &player->witchTimeMaxProbably, 10, 100, "%.0f");
                    ImGui::InputInt("+95D88 qteThing", &player->qteThing);
                    ImGui::Checkbox("+95ED4 walkOnWalls", &player->walkOnWalls);
                    ImGui::InputInt("+95F08 clothesRelated4", &player->clothesRelated4);
                    ImGui::InputInt("+95F18 walkOnWallsEffect", &player->walkOnWallsEffect);
                    ImGui::InputInt("+95FC4 walkOnWallsRelated", &player->walkOnWallsRelated);
                    ImGui::InputInt("+96330 clothesTransformation", &player->clothesTransformation);
                    ImGui::InputFloat("+96334 clothesTransformationTimer", &player->clothesTransformationTimer);
                    ImGui::InputInt("+96338 cutsceneToggleMaybe", &player->cutsceneToggleMaybe);
                    ImGui::InputInt("+965D0 facePlate", &player->facePlate);
                    ImGui::Combo("+96B24 form", (int*)&player->form, "Player\0Panther\0FirstPerson\0Bird\0");
                    ImGui::InputInt("+96B34 enemyCount", &player->enemyCount);
                    ImGui::InputInt("+96B38 clothesColourRGB", &player->clothesColourRGB);
                    ImGui::InputFloat3("+96C00 colouredHairIntensityRGB", &player->colouredHairIntensityRGB.x);
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
                ImGui::TreePop();
            }

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Hotkeys")) {
            ImGui::BeginChild("HotkeysChild");

            ImGui::SeparatorText("Don't forget to hit Save Config after setting these!");
            for (auto& hotkey : g_hotkeys)
                hotkey->draw(g_input);

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Info")) {
            ImGui::BeginChild("InfoChild");

            DrawCredits();

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();

        }
#else
        if (ImGui::BeginTabItem("Game Settings")) {
            ImGui::BeginChild("SpeedrunChild");

            ImGui::SeparatorText("Speedrun Settings");
            DrawUptimeFix();

            ImGui::BeginDisabled();
            if (ImGui::Checkbox("Disable Tutorials", &disableTutorials_toggle)) {
				GameHook::DisableTutorials(disableTutorials_toggle);
            }
            ImGui::EndDisabled();

            DrawGlamour();

            /*ImGui::Checkbox("Force Save File", &forceSaveFile);
            if (forceSaveFile) {
                if (ImGui::InputInt("File Number", &GameHook::forcedFileNum)) {
                    forcedFileNum = std::clamp(forcedFileNum, 0, 99);
                }
            }*/

            ImGui::SeparatorText("Other");

            // DrawFPSUnlock();

            if (ImGui::Checkbox("Focus Patch", &GameHook::focusPatch_toggle)) {
                GameHook::FocusPatch(GameHook::focusPatch_toggle);
            }
            help_marker("Play while tabbed out\nUse with Force Input Type to disable keyboard button prompts");

            {
                ImGui::BeginGroup();
                ImGui::Checkbox("Force Input Type", &GameHook::inputIcons_toggle);
                help_marker("Force the game to display either keyboard/mouse or gamepad input icons. Disallows certain inputs (such as mouse movement) when forcing gamepad");
                if (GameHook::inputIcons_toggle) {
                    ImGui::Indent();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::Combo("##InputTypeCombo", &GameHook::inputIconsValue, "Keyboard\0Gamepad\0");
                    ImGui::PopItemWidth();
                    ImGui::Unindent();
                }
                ImGui::EndGroup();
            }

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Practice")) {
            ImGui::BeginChild("PracticeChild");

            DrawAreaJump();
            help_marker("I hope this goes without saying but don't use this in a run");

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
			ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Overlay Settings")) {
            ImGui::BeginChild("OverlayettingsChild");

            DrawBayoHookSettings();

            ImGui::BeginDisabled();
            ImGui::Checkbox("Badge Display", &GameHook::badgeDisplay_toggle);
            ImGui::EndDisabled();
            help_marker("A badge of honesty, proving you're running the speedrun edition of BayoHook.\n"
                "The badge confirms game speed is tied to your run by displaying system time, game time, frame time and player interaction.");
            if (GameHook::badgeDisplay_toggle) {
                ImGui::Indent();
				// ImGui::Checkbox("Show Badge Lines", &GameHook::badgeLines_toggle);
                ImGui::PushItemWidth(GameHook::inputItemWidth);
                ImGui::SliderInt("Badge Corner", &GameHook::badgeCorner, 0, 3, NULL, ImGuiSliderFlags_NoInput);
                ImGui::SliderFloat("Scale", &GameHook::badgeScaleBase, 2.5f, 5.0f, "%.1f", ImGuiSliderFlags_NoInput);
                help_marker("If your stream/vod quality isn't great, please consider increasing the size of the badge for better visibility");
                // ImGui::SliderFloat("Line Thickness", &GameHook::badgeThicknessBase, 0.5f, 5.0f, "%.1f");
                // help_marker("This will not be customizable and should take up the same amount of the screen regardless of resolution");
                ImGui::PopItemWidth();
                ImGui::Unindent();
            }
            // the first value is system time, check 60s lines up with 60s
            // the second value is game time, will speed up if the process is sped up and proves the uptime fix is applied
            // the third value is fps
            // the lolly is character facing, bringing tying everything to your run
            // the squiggles are to make the frame unique.
            // - Red will never have jumps
            // - Purple (the player) may have jumps if the game sets your orientation or despawns you.

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Credits")) {
            ImGui::BeginChild("CreditsChild");

            DrawCredits();

            tabHeight += ImGui::GetCursorPosY();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
#endif
        ImGui::EndTabBar();
    }

    endHeight = (std::min)(uiHeight + tabHeight, maxUIHeight);

    {
        static float currentHeight = 0.0f;
        static float transitionSpeed = 10.0f;
        const float transitionEpsilon = 1.0f;
        if (GameHook::enable_scroll_transitions) {
            float deltaTime = ImGui::GetIO().DeltaTime;
            if (currentHeight == 0.0f)
                currentHeight = uiHeight;
            currentHeight = currentHeight + (deltaTime * transitionSpeed) * (endHeight - currentHeight);

            // if coming from a smaller tab we are slightly short of a full pixel
            if (std::abs(currentHeight - endHeight) < transitionEpsilon) {
                currentHeight = endHeight;
            }

            // tab height is set to 0 when tabbing in. if() will keep old dimensions
            if (tabHeight > 0.0f)
                ImGui::SetWindowSize(ImVec2(windowWidth, currentHeight));
        } else {
            ImGui::SetWindowSize(ImVec2(windowWidth, endHeight));
        }
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

ImVec2 TrailPos(float t, float cx, float cy, float radius) {
    static const float seed = (float)(std::chrono::steady_clock::now().time_since_epoch().count() % 100000);

    auto hash = [](int n) -> float {
        n = (n << 13) ^ n;
        return 1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
    };

    auto noise1D = [&](float x) -> float {
        int xi = (int)floorf(x);
        float xf = x - xi;
        float t = xf * xf * (3.0f - 2.0f * xf);
        return hash(xi) + (hash(xi + 1) - hash(xi)) * t;
    };

    float x = noise1D((t + seed) * 1.0f) * radius;
    float y = noise1D((t + seed) * 1.0f + 31.7f) * radius;
    return { cx + x, cy + y };
}

#ifdef SPEEDRUN_BUILD
bool GameHook::badgeDisplay_toggle = true;
bool GameHook::badgeLines_toggle = true;
int GameHook::badgeCorner = 0;
float GameHook::badgeScaleBase = 3.0f;
//float GameHook::badgeThicknessBase = 2.0f; // constexpr now
void GameHook::RenderBadge() {
    ImDrawList* draw = ImGui::GetForegroundDrawList();
    ImVec2 display = ImGui::GetIO().DisplaySize;

    float dpiScale;
    if (display.y > 0.0f)
        dpiScale = display.y / 1080.0f;
    else
        dpiScale = 1.0f;
    if (badgeScaleBase < 2.5f) badgeScaleBase = 2.5f;
    float scale = badgeScaleBase * dpiScale;
    float thicknessMul = badgeThicknessBase * dpiScale;
    static constexpr int circleResolution = 32;

    auto S = [scale](float v) { return v * scale; };
    auto T = [thicknessMul](float v) { return v * thicknessMul; };

    static constexpr float stickLength = 6.0f;
    static constexpr float trailLength = 6.0f;
    static constexpr float sweetSize = 2.0f;
    static constexpr float sweetRadius = sweetSize / 2.0f;
    static constexpr float baseRadius = stickLength + sweetRadius;

    float radius = S(baseRadius);
    float borderPadding = T(1.0f);
    float margin = radius * 2.0f + borderPadding;
    float cx = 0.0f, cy = 0.0f;

    switch (GameHook::badgeCorner) {
        case 0: cx = margin;             cy = margin;             break;
        case 1: cx = display.x - margin; cy = margin;             break;
        case 2: cx = margin;             cy = display.y - margin; break;
        case 3: cx = display.x - margin; cy = display.y - margin; break;
        default: cx = margin;            cy = display.y - margin; break;
    }

    if (badgeLines_toggle) {
        float realT = (float)ImGui::GetTime();
        static constexpr int numPoints = 32;

        ImVec2 lastTrailPoint;
        for (int i = 0; i < numPoints - 1; i++) {
            float t0 = realT - trailLength * (1.0f - (float)i / (float)(numPoints - 1));
            float t1 = realT - trailLength * (1.0f - (float)(i + 1) / (float)(numPoints - 1));
            ImVec2 p0 = TrailPos(t0, cx, cy, radius);
            ImVec2 p1 = TrailPos(t1, cx, cy, radius);
            lastTrailPoint = p1;
            draw->AddLine(p0, p1, IM_COL32(255, 60, 60, 255), T(1.0f));
        }

        static ImVec2 lollyHistory[512] = {};
        static float  lollyTimes[512] = {};
        static int    lollyHead = 0;
        static float  lastLollyPushTime = 0.0f;

        LocalPlayer* player = GameHook::GetLocalPlayer();
        ImVec2 base = lastTrailPoint;
        float a = 0.0f;
        float cosA = 1.0f, sinA = 0.0f;
        if (player) {
            a = -player->rot.y;
            cosA = cosf(a);
            sinA = sinf(a);
        }

        auto R = [&](float lx, float ly) -> ImVec2 {
            lx *= scale;
            ly *= scale;
            return ImVec2(base.x + lx * cosA - ly * sinA, base.y + lx * sinA + ly * cosA);
        };

        if (player) {
            float pushInterval = trailLength / 512.0f;
            if (realT - lastLollyPushTime >= pushInterval) {
                ImVec2 tipScreen = R(0.0f, stickLength);
                lollyHistory[lollyHead] = ImVec2(tipScreen.x - cx, tipScreen.y - cy);
                lollyTimes[lollyHead] = realT;
                lollyHead = (lollyHead + 1) % 512;
                lastLollyPushTime = realT;
            }

            for (int i = 0; i < 511; i++) {
                int ia = (lollyHead + i) % 512;
                int ib = (lollyHead + i + 1) % 512;
                if (lollyTimes[ia] == 0.0f || lollyTimes[ib] == 0.0f) continue;
                if (realT - lollyTimes[ia] > trailLength) continue;
                ImVec2 pa = ImVec2(cx + lollyHistory[ia].x, cy + lollyHistory[ia].y);
                ImVec2 pb = ImVec2(cx + lollyHistory[ib].x, cy + lollyHistory[ib].y);
                draw->AddLine(pa, pb, IM_COL32(200, 170, 255, 255), T(1.0f));
            }

            ImU32 sweetcol = IM_COL32(255, 60, 60, 255);
            ImU32 stickcol = IM_COL32(200, 200, 200, 255);
            draw->AddLine(R(0.0f, 0.0f), R(0.0f, stickLength), stickcol, T(2.0f));
            draw->AddCircleFilled(R(0.0f, 0.0f), S(sweetRadius), sweetcol, circleResolution / 2);
        }
    }

    float outerRadius = radius + S(stickLength + sweetRadius);
    draw->AddCircleFilled( ImVec2(cx, cy), outerRadius, IM_COL32(0, 0, 0, 50), circleResolution);
    draw->AddCircle( ImVec2(cx, cy), outerRadius, IM_COL32(200, 170, 255, 30), circleResolution, T(1.0f));

    // timers
    {
        std::time_t now = std::time(nullptr);
        std::tm lt{};
        localtime_s(&lt, &now);
        float gameTime = *(float*)GameHook::gameTimeAddress * 0.001f;
        float fps = ImGui::GetIO().Framerate;

        std::string line1 = (lt.tm_min < 10 ? "0" : "") + std::to_string(lt.tm_min) + ":" +
            (lt.tm_sec < 10 ? "0" : "") + std::to_string(lt.tm_sec);

        char buf2[32];
        char buf3[32];

        snprintf(buf2, sizeof(buf2), "%.2f", gameTime);
        snprintf(buf3, sizeof(buf3), "%.1f", fps);

        std::string line2 = buf2;
        std::string line3 = buf3;

        std::string lines[3] = { line1, line2, line3 };

        float fontSize = S(7.0f);
        if (fontSize < 7.0f) fontSize = 7.0f;
        float scale = fontSize / ImGui::GetFontSize();
        float lineHeight = ImGui::GetTextLineHeight() * scale;
        float totalHeight = lineHeight * 3;
        float startY = cy - totalHeight * 0.5f;

        ImU32 shadowCol = IM_COL32(0, 0, 0, 255);
        ImU32 textCol = IM_COL32(255, 255, 255, 255);

        for (int i = 0; i < 3; i++) {
            ImVec2 textSize = ImGui::CalcTextSize(lines[i].c_str());
            textSize.x *= scale;

            float x = cx - textSize.x * 0.5f;
            float y = startY + i * lineHeight;

            // shadow
            draw->AddText(NULL, fontSize,
                ImVec2(x + 1.0f, y + 1.0f),
                shadowCol,
                lines[i].c_str());

            // main
            draw->AddText(NULL, fontSize,
                ImVec2(x, y),
                textCol,
                lines[i].c_str());
        }
    }
}
#endif

void GameHook::BackgroundImGui(void) {
#ifdef SPEEDRUN_BUILD
    if (badgeDisplay_toggle) { RenderBadge(); }
#endif
    if (showMessages_toggle) {
        GameHook::RenderMessages(ImGui::GetIO().DeltaTime);
    }
}
