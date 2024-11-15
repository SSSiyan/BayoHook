#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>
#include <algorithm>

const char* GameHook::weaponNames[16] {
    "Scarborough Fair",
    "Onyx Roses",
    "Shuraba",
    "Kulshedra",
    "Durga",
    "Lt. Col. Kilgore",
    "Odette",
    "Sai Fung",
    "Handguns",
    "Handguns",
    "Onyx Roses Alt",
    "Durga Alt",
    "Lt. Col. Kilgore Alt",
    "Pillowtalk",
    "Bazillions",
    "Rodin",
};

const char* GameHook::costumeNames[32] {
    "Bayonetta Default",
    "Bayonetta P.E. A",
    "Bayonetta P.E. B",
    "Bayonetta P.E. C",
    "Bayonetta d'Arc",
    "Bayonetta Old",
    "Bayonetta Umbra",
    "Bayonetta Various A",
    "Bayonetta Various B",
    "Bayonetta Various C",
    "Bayonetta Umbran Komachi A",
    "Bayonetta Umbran Komachi B",
    "Bayonetta Umbran Komachi C",
    "Bayonetta Nun",
    "Bayonetta Queen",
    "Jeanne Default",
    "Jeanne P.E. A",
    "Jeanne P.E. B",
    "Jeanne P.E. C",
    "Jeanne Formal B",
    "Jeanne Formal A",
    "Jeanne Old",
    "Jeanne Umbra",
    "Jeanne Various A",
    "Jeanne Various B",
    "Jeanne Various C",
    "Jeanne Umbran Komachi A",
    "Jeanne Umbran Komachi B",
    "Jeanne Umbran Komachi C",
    "Jeanne Nun",
    "Jeanne Queen",
    "Little King Zero",
};

const char* GameHook::accessoryNames[13] {
    "None",
    "Sergey's Lover",
    "Infernal Communicator",
    "Pulley's Butterfly",
    "Selene's Light",
    "Star of Dinéta",
    "Evil Harvest Rosary",
    "Gaze of Despair",
    "Moon of Mahaa - Kalaa",
    "Eternal Testimony",
    "Bracelet of Time",
    "Climax Brace",
    "Immortal Marionette",
};

void GameHook::GameTick(void) { // also called while the menu isn't open
    static bool isFirstFrame = true;
    localPlayer* player = GetLocalPlayer();
    isFirstFrame = false;
    if (player) {
        for (int i = 0; i < maxComboMakers; ++i) {
            if (comboMaker_toggles[i]) {
                if (player->moveID == comboMakerMoveIDs[i] && player->attackCount == comboMakerMoveParts[i]) {
                    player->stringID = comboMakerStringIDs[i];
                }
            }
        }
    }
}

void GameHook::GameImGui(void) {
    int& halosValue = *(int*)GameHook::halosAddress;
    int& chaptersPlayedValue = *(int*)GameHook::chaptersPlayedAddress;
    int& comboPointsValue = *(int*)GameHook::comboPointsAddress;
    float& comboMultiplierValue = *(float*)GameHook::comboMultiplierAddress;
    int& currentCharacterValue = *(int*)GameHook::currentCharacterAddress;
    int& currentCostumeValue = *(int*)GameHook::currentCostumeAddress;
    int& thirdAccessoryValue = *(int*)GameHook::thirdAccessoryAddress;
    bool& hudDisplayValue = *(bool*)GameHook::hudDisplayAddress;
    int& angelSlayerFloorValue = *(int*)GameHook::angelSlayerFloorAddress;
    int& difficultyValue = *(int*)GameHook::difficultyAddress;
    int& areaJumpValue = *(int*)GameHook::areaJumpAddress;
    int& weaponA1Value = *(int*)GameHook::WeaponA1Address;
    int& weaponA2Value = *(int*)GameHook::WeaponA2Address;
    int& weaponB1Value = *(int*)GameHook::WeaponB1Address;
    int& weaponB2Value = *(int*)GameHook::WeaponB2Address;

    GameHook::windowWidth = 40.0f * ImGui::GetFontSize();
    GameHook::sameLineWidth = windowWidth * 0.5f;
    GameHook::inputItemWidth = windowWidth * 0.2f;
    GameHook::maxWindowHeight = ImGui::GetIO().DisplaySize.y * 0.9f;
    GameHook::windowHeightBorder = ImGui::GetFontSize() * 6.0f;

    if (ImGui::Button("Save config")) {
        GameHook::onConfigSave(GameHook::cfg);
    }

    if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("General")) {
            ImGui::BeginChild("GeneralChild");

            if (ImGui::Checkbox("Deal No Damage (F1) ##DealNoDamageToggle", &GameHook::enemyHP_no_damage_toggle)) {
                GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
                if (GameHook::enemyHP_no_damage_toggle)
                    GameHook::enemyHP_one_hit_kill_toggle = false;
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Take No Damage (F2)", &GameHook::takeNoDamage_toggle)) {
                GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
            }

            if (ImGui::Checkbox("One Hit Kill (F3) ##OneHitKillToggle", &GameHook::enemyHP_one_hit_kill_toggle)) {
                if (GameHook::enemyHP_one_hit_kill_toggle) {
                    GameHook::enemyHP_no_damage_toggle = false;
                    GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
                }
            }
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Disable Slow Motion", &GameHook::disableSlowmo_toggle);

            if (ImGui::Checkbox("Disable Enemy Daze", &GameHook::disableDaze_toggle)) {
                GameHook::DisableDaze(GameHook::disableDaze_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Force Enemy Daze", &GameHook::forceDaze_toggle)) {
                GameHook::ForceDaze(GameHook::forceDaze_toggle);
            }
            help_marker("Daze every loaded enemy");

            if (ImGui::Checkbox("More Enemy Attacks", &GameHook::moreEnemyAttacks_toggle)) {
                GameHook::lessEnemyAttacks_toggle = false;
                GameHook::LessEnemyAttacks(GameHook::lessEnemyAttacks_toggle);
                GameHook::MoreEnemyAttacks(GameHook::moreEnemyAttacks_toggle);
            }
            help_marker("Remove the cooldown that starts when an enemy attacks");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Less Enemy Attacks", &GameHook::lessEnemyAttacks_toggle)) {
                GameHook::moreEnemyAttacks_toggle = false;
                GameHook::MoreEnemyAttacks(GameHook::moreEnemyAttacks_toggle);
                GameHook::LessEnemyAttacks(GameHook::lessEnemyAttacks_toggle);
            }
            help_marker("Freeze the cooldown that starts when an enemy attacks");

            ImGui::Separator();

            ImGui::Checkbox("Freeze Magic ##InfMagicToggle", &GameHook::inf_magic_toggle);
            if (GameHook::inf_magic_toggle)
                ImGui::SliderFloat("##InfiniteMagicValue", &GameHook::inf_magic_value, 0, 1200);

            ImGui::Separator();

            ImGui::Checkbox("Turbo", &GameHook::turbo_toggle);
            if (GameHook::turbo_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##TurboInputFloat", &GameHook::turboValue, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Damage Dealt Multiplier ##DamageDealtMultiplierToggle", &GameHook::damageDealtMultiplier_toggle);
            if (GameHook::damageDealtMultiplier_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##DamageDealtMultiplierrInputFloat", &GameHook::damageDealtMultiplierMult, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            ImGui::Separator();
            
            ImGui::Text("Third Accessory");
            ImGui::Combo("##ThirdAccessoryCombo", &GameHook::desiredThirdAccessory, GameHook::accessoryNames, IM_ARRAYSIZE(GameHook::accessoryNames));

            thirdAccessoryValue = GameHook::desiredThirdAccessory;

            ImGui::Separator();

            ImGui::Text("Difficulty");
            ImGui::Combo("##DifficultyInputInt", &difficultyValue, "Very Easy\0Easy\0Normal\0Hard\0Non-Stop Infinite Climax\0");

            ImGui::Separator();

            ImGui::Text("Character");
            help_marker("Set while in costume select\nIf your game freezes at the end of a fight, flick the value back to default");
            ImGui::Combo("##CharacterSelectInputInt", &currentCharacterValue, "Bayonetta\0Jeanne\0Little King Zero\0");

            ImGui::Text("Costume");
            help_marker("Set while in mission select");
            ImGui::Combo("##CostumeSelectInputInt", &currentCostumeValue, GameHook::costumeNames, IM_ARRAYSIZE(GameHook::costumeNames));

            ImGui::Separator();

            ImGui::Text("Initial Angel Slayer Floor");
            help_marker("Set before starting Angel Slayer.");
            ImGui::PushItemWidth(inputItemWidth);
            int displayInitialAngelSlayerFloor = GameHook::initialAngelSlayerFloor + 1;
            if (ImGui::InputInt("##InitialAngelSlayerFloorInputInt", &displayInitialAngelSlayerFloor)) {
                GameHook::initialAngelSlayerFloor = displayInitialAngelSlayerFloor - 1;
            }
            ImGui::PopItemWidth();

            ImGui::Text("Current Angel Slayer Floor");
            help_marker("Set before entering a portal.");
            ImGui::PushItemWidth(inputItemWidth);
            int displayAngelSlayerFloorValue = angelSlayerFloorValue + 1;
            if (ImGui::InputInt("##AngelSlayerFloorInputInt", &displayAngelSlayerFloorValue)) {
                angelSlayerFloorValue = displayAngelSlayerFloorValue - 1;
            }
            ImGui::PopItemWidth();

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Character")) {
            ImGui::BeginChild("CharacterChild");

            if (ImGui::Checkbox("Infinite Jumps (F4) ##InfJumpsToggle", &GameHook::infJumps_toggle)) {
                GameHook::InfJumps(GameHook::infJumps_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Disable After Burner Bounce", &GameHook::disableAfterBurnerBounce_toggle)) {
                DisableAfterBurnerBounce(GameHook::disableAfterBurnerBounce_toggle);
            }

            ImGui::Checkbox("Cancellable After Burner", &GameHook::cancellableAfterBurner_toggle);
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Cancellable Falling Kick", &GameHook::cancellableFallingKick_toggle);

            ImGui::Checkbox("Alt Teleport Input", &GameHook::altTeleInput_toggle);
            help_marker("Teleport = Lockon + Taunt\nTaunt = Dpad Down");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Taunt With Time Bracelet", &GameHook::tauntWithTimeBracelet_toggle)) {
                TauntWithTimeBracelet(GameHook::tauntWithTimeBracelet_toggle);
            }
            help_marker("Taunt = Dpad Down");

            ImGui::Checkbox("Lower Divekick Requirement", &GameHook::lowerDivekick_toggle);
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Dual Gun After Burner", &GameHook::dualAfterBurner_toggle);

            if (ImGui::Checkbox("No Hold Dodge Offset", &GameHook::noHoldDodgeOffset_toggle)) {
                NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Jump Offset", &GameHook::jumpOffset_toggle)) {
                JumpOffset(jumpOffset_toggle);
            }

            if (ImGui::Checkbox("Weapon Swap Offset", &GameHook::weaponSwapOffset_toggle)) {
                WeaponSwapOffset(weaponSwapOffset_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Parry Offset", &GameHook::parryOffset_toggle)) {
                ParryOffset(parryOffset_toggle);
            }

            ImGui::Checkbox("Longer Pillow Talk Charge", &longerPillowTalkCharge_toggle);
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Retain Pillow Talk Charge", &GameHook::retainPillowTalkCharge_toggle)) {
                RetainPillowTalkCharge(retainPillowTalkCharge_toggle);
            }
            help_marker("When swapping weaponset, remember pillow talk charge");

            if (ImGui::Checkbox("Swap Mashes To Holds", &GameHook::swapMashToHold_toggle)) {
                SwapMashToHold(swapMashToHold_toggle);
            }
            help_marker("Swap mash inputs such as those used on Odette to hold inputs");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Always Walk On Walls", &GameHook::alwaysWalkOnWalls_toggle)) {
                AlwaysWalkOnWalls(alwaysWalkOnWalls_toggle);
            }

            ImGui::Checkbox("Always Witch Time", &GameHook::alwaysWitchTime_toggle);
            help_marker("Activate Witch Time even with a mistimed dodge");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Standardized Witch Time", &GameHook::jeanneBayoWT_toggle)) {
                GameHook::JeanneBayoWT(GameHook::jeanneBayoWT_toggle);
            }
            help_marker("Give Jeanne Bayonetta's Witch Time activation leniency");

            if (ImGui::Checkbox("Infinite Divekicks", &GameHook::infDivekick_toggle)) {
                InfDivekick(infDivekick_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Disable Lockon Jump Dodge", &GameHook::disableLockOnDodge_toggle)) {
                GameHook::DisableLockOnDodge(GameHook::disableLockOnDodge_toggle);
            }

            if (ImGui::Checkbox("Infinite Crow Within", &GameHook::infBirdTime_toggle)) {
                InfBirdTime(infBirdTime_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Disable Double Tap Inputs", &GameHook::disableDoubleTapHeelKick_toggle)) {
                GameHook::DisableDoubleTapHeelKick(disableDoubleTapHeelKick_toggle);
            }
            ImGui::SameLine();
            help_marker("Stiletto, Heel Slide etc");

            ImGui::Separator();

            ImGui::Checkbox("Witch Time Multiplier ##WitchTimeToggle", &GameHook::witchTimeMultiplier_toggle);
            help_marker("Adjust how long Witch Time lasts");
            if (GameHook::witchTimeMultiplier_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##WitchTimeMultiplier", &GameHook::witchTimeMultiplier, 0, 0, "%.1f");
                ImGui::PopItemWidth();
            }

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("System")) {
            ImGui::BeginChild("SystemChild");

            ImGui::Checkbox("Show Hotkey Messages", &GameHook::showMessages_toggle);
            help_marker("Show text in the corner of the screen when a hotkey is activated");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Focus Patch", &GameHook::focusPatch_toggle)) {
                GameHook::FocusPatch(GameHook::focusPatch_toggle);
            }
            help_marker("Play while tabbed out\nUse with Force Input Type to disable keyboard button prompts");

            ImGui::Checkbox("Enemy HP in Halo Display", &GameHook::haloDisplay_toggle);
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("NoClip (F5)", &GameHook::noClip_toggle)) {
                GameHook::NoClip(GameHook::noClip_toggle);
            }

            if (ImGui::Checkbox("Freeze Timer", &GameHook::freezeTimer_toggle)) {
                GameHook::FreezeTimer(GameHook::freezeTimer_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Easier Mashing ##EasierMashToggle", &GameHook::easierMash_toggle);

            if (ImGui::Checkbox("Force Summoning Clothes ##LessClothesToggle", &GameHook::lessClothes_toggle)) {
                GameHook::LessClothes(GameHook::lessClothes_toggle);
            }
            help_marker("Only works on outfits that have this function");
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Save/Load Animation Hotkeys", &GameHook::saveStatesHotkeys_toggle);

            if (ImGui::Checkbox("Easy Cutscene Skip", &GameHook::easyCutsceneSkip_toggle)) {
                GameHook::EasyCutsceneSkip(GameHook::easyCutsceneSkip_toggle);
            }
            help_marker("Move cutscene skip (R2+Select) to X");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Get More Halos", &GameHook::getMoreHalos_toggle)) {
                GameHook::GetMoreHalos(GameHook::getMoreHalos_toggle);
            }
            help_marker("Pick up Halos from further away");

            ImGui::Checkbox("Skip Angel Attack", &GameHook::loadReplace_toggle);
            help_marker("Load Mission Select instead of Angel Attack");

            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("60 FPS Cutscenes", &GameHook::sixtyFpsCutscenes_toggle)) {
                GameHook::SixtyFpsCutscenes(GameHook::sixtyFpsCutscenes_toggle);
            }

            if (ImGui::Checkbox("Disable FPS Limiter", &GameHook::disableFpsLimiter_toggle)) {
                GameHook::DisableFpsLimiter(GameHook::disableFpsLimiter_toggle);
            }

            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Pause When Opening BayoHook", &GameHook::openMenuPause_toggle);

            if (ImGui::Checkbox("Remove Vignette", &GameHook::removeVignette_toggle)) {
                GameHook::RemoveVignette(GameHook::removeVignette_toggle);
            }

            ImGui::Separator();

            ImGui::Checkbox("Force Input Type", &GameHook::inputIcons_toggle);
            if (GameHook::inputIcons_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::Combo("##InputTypeCombo", &GameHook::inputIconsValue, "Keyboard\0Gamepad\0");
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Show 9.9+ Combo Multiplier UI", &GameHook::showComboUI_toggle);
            help_marker("Open a window that shows your current combo multiplier when passing 9.9x");
            if (GameHook::showComboUI_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("X Position ##ComboUIXInputFloat", &comboUI_X, 0.001f, 0.01f);
                ImGui::InputFloat("Y Position ##ComboUIYInputFloat", &comboUI_Y, 0.001f, 0.01f);
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Custom Camera Distance ##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            if (GameHook::customCameraDistance_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceInputFloat", &GameHook::customCameraDistance, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            localPlayer* player = GetLocalPlayer();
            if (player) {
                ImGui::Separator();
                ImGui::Text("Player Position");
                ImGui::InputFloat3("##PlayerPositionInputFloat3", &player->pos.x);
                if (ImGui::Button("Teleport to 0, 0, 0")) {
                    player->pos = { 0.0f, 0.0f, 0.0f };
                }
            }

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Stats")) {
            ImGui::BeginChild("StatsChild");

            if (ImGui::CollapsingHeader("Stats")) {
                ImGui::TreePush("StatsTree");
                ImGui::Checkbox("HUD Display", &hudDisplayValue);
                help_marker("Show HP etc");

                ImGui::Text("Halos");
                ImGui::PushItemWidth(inputItemWidth * 2);
                ImGui::InputInt("##HaloInputInt", &halosValue, 1, 100);
                ImGui::PopItemWidth();

                ImGui::Text("Chapters Played");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##ChapterInputInt", &chaptersPlayedValue, 1, 100);
                ImGui::PopItemWidth();

                ImGui::Text("Combo Points");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##ComboPointsInputInt", &comboPointsValue, 10, 100);
                ImGui::PopItemWidth();

                ImGui::Text("Combo Multiplier");
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##ComboMultiplierInputFloat", &comboMultiplierValue, 1, 10, "%.1f");
                ImGui::PopItemWidth();

                ImGui::Text("Weapon Set A:");
                help_marker("WIP, requires entering and exiting the weapon select menu to apply");
                ImGui::Combo("##WeaponA1InputInt", &weaponA1Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Combo("##WeaponA2InputInt", &weaponA2Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Text("Weapon Set B:");
                ImGui::Combo("##WeaponB1InputInt", &weaponB1Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Combo("##WeaponB2InputInt", &weaponB2Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
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
                localPlayer* player = GetLocalPlayer();
                if (player) {
                    float& playerMagicValue = *(float*)GameHook::playerMagicAddress; // not player offset but keeping it here anyway
                    static Vec3 playerTempHairColour{ 1.0f, 1.0f, 1.0f };

                    ImGui::Separator();
                    ImGui::InputFloat3("Position##PlayerPositionInputFloat3", &player->pos.x);
                    if (ImGui::Button("Teleport to 0, 0, 0")) {
                        player->pos = { 0.0f, 0.0f, 0.0f };
                    }
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("Player HP##PlayerHPInputInt", &player->hp, 1, 100);
                    ImGui::InputFloat("Player MP##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");
                    ImGui::InputFloat("Remaining Witch Time Duration##PlayerRemainingWitchTimeDurationInputFloat", &player->witchTimeDuration, 10, 100, "%.0f");
                    ImGui::InputFloat("Remaining Invinciblity##PlayerRemainingInvinciblityInputFloat", &player->iFramesRemaining, 10, 100, "%.0f");
                    ImGui::InputFloat("Animation Frame##PlayerAnimationFrameInputFloat", &player->animFrame, 1, 10, "%.0f");
                    ImGui::InputInt("Move ID##PlayerMoveIDInputInt", &player->moveID);
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
                uintptr_t* enemy_ptr = (uintptr_t*)GameHook::enemyLockedOnAddress;
                uintptr_t enemy_base = *enemy_ptr;
                if (enemy_base) {
                    float* enemyXYZPos[3];
                    enemyXYZPos[0] = (float*)(enemy_base + 0xD0);
                    enemyXYZPos[1] = (float*)(enemy_base + 0xD4);
                    enemyXYZPos[2] = (float*)(enemy_base + 0xD8);
                    int& enemyHPValue = *(int*)(enemy_base + 0x6B4);
                    int& enemyMoveIDValue = *(int*)(enemy_base + 0x34C);
                    float& enemyAnimFrameValue = *(float*)(enemy_base + 0x3E4);
                    float& enemyDazeBuildupValue = *(float*)(enemy_base + 0xC94);
                    float& enemyDazeDurationValue = *(float*)(enemy_base + 0xC9C);

                    uintptr_t enemyHPPtr = *(uintptr_t*)(enemy_base + 0xA00);
                    int& enemyBossHPValue = *(int*)(enemyHPPtr + 0x6B4);

                    ImGui::Separator();

                    ImGui::Text("Enemy Position");
                    ImGui::InputFloat3("##EnemyXYZPosInputFloat", *enemyXYZPos);
                    ImGui::Text("Enemy HP");
                    ImGui::InputInt("##EnemyHPInputInt", &enemyHPValue);
                    ImGui::Text("Enemy Move ID");
                    ImGui::InputInt("##EnemyMoveIDInputInt", &enemyMoveIDValue);
                    ImGui::Text("Enemy Daze Buildup");
                    ImGui::InputFloat("##EnemyDazeBuildupInputFloat", &enemyDazeBuildupValue, 10, 100, "%.0f");
                    ImGui::Text("Enemy Daze Duration");
                    ImGui::InputFloat("##EnemyDazeDurationInputFloat", &enemyDazeDurationValue, 10, 100, "%.0f");
                    if (enemyHPPtr) {
                        ImGui::Text("Enemy Boss HP");
                        ImGui::InputInt("##EnemyBossHPInputInt", &enemyBossHPValue);
                    }

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

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Extra")) {
            ImGui::BeginChild("ExtraChild");

            ImGui::Checkbox("Move ID Swaps", &moveIDSwapsToggle);
            if (GameHook::moveIDSwapsToggle) {
                for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
                    ImGui::Checkbox(("Move Swap[" + std::to_string(i + 1) + "]").c_str(), &moveIDSwap_toggles[i]);
                    GameHook::help_marker("Do the move you want to see, pause mid anim, type your current moveID in the first box\n"
                        "Do the move you want to replace, pause mid anim, type your current moveID in the second box");
                    if (GameHook::moveIDSwap_toggles[i]) {
                        localPlayer* player = GetLocalPlayer();
                        if (player) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("Current Move ID: %i", player->moveID);
                            ImGui::Text("Replace moveID:");
                            ImGui::SameLine();
                            ImGui::InputInt(("##CurrentStringIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSourceMoves[i], 0, 0);
                            ImGui::SameLine();
                            ImGui::Text("With:");
                            ImGui::SameLine(); ImGui::InputInt(("##DesiredMoveIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSwappedMoves[i]);
                            ImGui::PopItemWidth();
                        }
                        else
                            ImGui::Text("Load in to a stage to see these stats");
                    }
                }
            }

            ImGui::Separator();

            ImGui::Checkbox("Combo Maker", &GameHook::comboMakerToggle);
            if (GameHook::comboMakerToggle) {
                for (int i = 0; i < maxComboMakers; ++i) {
                    ImGui::Checkbox(("Combo Maker[" + std::to_string(i + 1) + "]").c_str(), &comboMaker_toggles[i]);
                    if (comboMaker_toggles[i]) {
                        localPlayer* player = GetLocalPlayer();
                        if (player) {
                            ImGui::Text("Current MoveID: %i", player->moveID);
                            ImGui::Text("Current Number In String: %i", player->attackCount);
                            ImGui::Text("Current String ID: %i", player->stringID);

                            ImGui::Text("if MoveID ==");
                            ImGui::SameLine();
                            std::string moveIDLabel = "##ComboMakerMoveID" + std::to_string(i) + "InputInt";
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::InputInt(moveIDLabel.c_str(), &comboMakerMoveIDs[i]);
                            ImGui::PopItemWidth();

                            ImGui::Text("and current attack number in string ==");
                            ImGui::SameLine();

                            std::string movePartLabel = "##ComboMakerMovePart" + std::to_string(i) + "InputInt";
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::InputInt(movePartLabel.c_str(), &comboMakerMoveParts[i]);
                            ImGui::PopItemWidth();

                            ImGui::Text("then StringID =");
                            ImGui::SameLine();

                            std::string stringIDLabel = "##ComboMakerStringID" + std::to_string(i);
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::InputInt(stringIDLabel.c_str(), &comboMakerStringIDs[i]);
                            ImGui::PopItemWidth();
                        }
                        else
                            ImGui::Text("Load in to a stage to see these stats");
                    }
                }
            }

            ImGui::Separator();

            ImGui::Checkbox("Custom Weaves", &GameHook::customWeaveToggle);
            if (GameHook::customWeaveToggle) {
                for (int i = 0; i < customWeaveCount; ++i) {
                    ImGui::Checkbox(("Custom Weave[" + std::to_string(i + 1) + "]").c_str(), &customWeaves_toggles[i]);
                    if (customWeaves_toggles[i]) {
                        localPlayer* player = GetLocalPlayer();
                        if (player) {
                            ImGui::Text("Current MoveID: %i", player->moveID);
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("If moveID ==    ");
                            ImGui::SameLine();
                            ImGui::InputInt(("##customWeaveMoveIDArray" + std::to_string(i)).c_str(), &customWeaveMoveIDArray[i]);
                            ImGui::SameLine();
                            ImGui::Text("Then weaveID == ");
                            ImGui::SameLine();
                            ImGui::InputInt(("##customWeaveArray" + std::to_string(i)).c_str(), &customWeaveArray[i]);
                            ImGui::PopItemWidth();
                            ImGui::Separator();
                        }
                        else
                            ImGui::Text("Load in to a stage to see these stats");
                    }
                }
            }

            ImGui::Separator();

            ImGui::Checkbox("String Swaps", &GameHook::stringSwapsToggle);
            if (GameHook::stringSwapsToggle) {
                for (int i = 0; i < GameHook::maxStringSwaps; ++i) {
                    ImGui::Checkbox(("String Swap[" + std::to_string(i + 1) + "]").c_str(), &stringIDSwap_toggles[i]);
                    GameHook::help_marker("Do the string you want to replace, pause mid anim, type the string ID in the first field\n"
                        "Do the string you want to see, pause mid anim, type the string ID in the second field");
                    if (GameHook::stringIDSwap_toggles[i]) {
                        localPlayer* player = GetLocalPlayer();
                        if (player) {
                            ImGui::Text("Current String ID");
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::InputInt(("##CurrentStringIDInputInt" + std::to_string(i)).c_str(), &player->stringID, 0, 0);

                            ImGui::Separator();

                            ImGui::Text("Source String ID:");
                            ImGui::SameLine();
                            ImGui::InputInt(("##SourceStringIDInputInt" + std::to_string(i)).c_str(), &GameHook::stringIDSwapSourceStrings[i]);
                            ImGui::Text("Desired String ID:");
                            ImGui::SameLine();
                            ImGui::InputInt(("##DesiredStringIDInputInt" + std::to_string(i)).c_str(), &GameHook::stringIDSwapDesiredStrings[i]);
                            ImGui::PopItemWidth();
                        }
                        else
                            ImGui::Text("Load in to a stage to see these stats");
                    }

                    ImGui::Separator();
                }
            }

            ImGui::Separator();

            ImGui::Text("Area Jump Test");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##AreaIDInputInt", &areaJumpValue, ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopItemWidth();
            help_marker("VERY CRASHY BE WARNED\n2576 = mission select\n528 = proving grounds\n2816 = angel slayer\n276 = train station");
            if (ImGui::Button("Jump to mission select")) {
                areaJumpValue = 2576;
            }
            help_marker("Depending on when this is pressed it could crash. Haven't tested it much gl");
            if (ImGui::Checkbox("Patch Area Jump Correction", &GameHook::areaJumpPatch_toggle)) {
                GameHook::AreaJumpPatch(GameHook::areaJumpPatch_toggle);
            }
            help_marker("Sometimes the area jump ID gets reset, presumably to correct it if you input something out of bounds. This removes that.");

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Info")) {
            ImGui::BeginChild("InfoChild");

            ImGui::Text("Hotkeys:");
            ImGui::Text("F1 = Deal No Damage");
            ImGui::Text("F2 = Take No Damage");
            ImGui::Text("F3 = One Hit Kill");
            ImGui::Text("F4 = Infinite Jumps");
            ImGui::Text("F5 = NoClip");
            ImGui::Text("F6 = Summoning Outfit");
            ImGui::Text("Home = Save Locked On Enemy Anim");
            help_marker("if enabled in System");
            ImGui::Text("End = Load Locked On Enemy Anim");
            help_marker("if enabled in System");
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
            static std::array<ImGuiURL, 8> links1{
                ImGuiURL { "SSSiyan", "https://twitter.com/sssiyan" },
                ImGuiURL { "GarudaKK", "https://www.youtube.com/@GarudaPSN" },
                ImGuiURL { "Kerilk", "https://github.com/Kerilk" },
                ImGuiURL { "CreativeHandle", "https://twitter.com/CreativeHandler" },
                ImGuiURL { "Skyth", "https://github.com/blueskythlikesclouds" },
                ImGuiURL { "deepdarkkapustka", "https://www.youtube.com/@mstislavcapusta7573" },
                ImGuiURL { "TheDarkness", "https://steamcommunity.com/id/TheDarkness704/" },
                ImGuiURL { "Jan Schatter", "https://www.flickr.com/people/116494253@N05/" },
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

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
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

void GameHook::under_line(const ImColor& col) {
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    min.y = max.y;
    ImGui::GetWindowDrawList()->AddLine(min, max, col, 1.0f);
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
        if (GameHook::showMessageTimerF4 > 0) {
            if (GameHook::infJumps_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "Infinite Jumps ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "Infinite Jumps OFF");
            GameHook::showMessageTimerF4--;
        }
        if (GameHook::showMessageTimerF5 > 0) {
            if (GameHook::noClip_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "NoClip ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "NoClip OFF");
            GameHook::showMessageTimerF5--;
        }
        if (GameHook::showMessageTimerF6 > 0) {
            if (GameHook::lessClothes_toggle)
                ImGui::TextColored(ImVec4(0,1,0,1), "Summoning Clothes ON");
            else
                ImGui::TextColored(ImVec4(0,1,0,1), "Summoning Clothes OFF");
            GameHook::showMessageTimerF6--;
        }
    }
}
