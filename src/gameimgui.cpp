#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>
#include <algorithm>

// system
float GameHook::windowWidth = 0.0f;
float GameHook::windowHeightHack = 0.0f;
float GameHook::windowHeightBorder = 0.0f;
float GameHook::inputItemWidth = 0.0f;
float GameHook::sameLineWidth = 0.0f;
float GameHook::windowScalingFactor = 1.0f;
float GameHook::maxWindowHeight = 0.0f;
float GameHook::comboUI_X = 0.0f;
float GameHook::comboUI_Y = 0.0f;
bool GameHook::showMessages_toggle = false;
bool GameHook::showComboUI_toggle = false;
int GameHook::showMessageTimerF1 = 0;
int GameHook::showMessageTimerF2 = 0;
int GameHook::showMessageTimerF3 = 0;
int GameHook::showMessageTimerF4 = 0;
int GameHook::showMessageTimerF5 = 0;

// update
uintptr_t GameHook::playerPointerAddress = 0xEF5A60;
uintptr_t GameHook::halosAddress = 0x5AA74B4;
uintptr_t GameHook::chaptersPlayedAddress = 0x5AA736C;
uintptr_t GameHook::playerMagicAddress = 0x5AA74AC;
uintptr_t GameHook::comboPointsAddress = 0x5BB519C;
uintptr_t GameHook::comboMultiplierAddress = 0x5BB51A0;
uintptr_t GameHook::currentCharacterAddress = 0x5AA7484;
uintptr_t GameHook::currentCostumeAddress = 0x5AA747C;
uintptr_t GameHook::thirdAccessoryAddress = 0x5AA7468;
uintptr_t GameHook::hudDisplayAddress = 0xF2B714;
uintptr_t GameHook::enemyLockedOnAddress = 0xF2B744;
uintptr_t GameHook::enemySlotsAddress = 0x5A56A88;
uintptr_t GameHook::angelSlayerFloorAddress = 0x509E87C;
uintptr_t GameHook::difficultyAddress = 0x5A985A0;
uintptr_t GameHook::areaJumpAddress = 0x5A978E8;
uintptr_t GameHook::WeaponA1Address = 0x5AA741C;
uintptr_t GameHook::WeaponA2Address = 0x5AA7420;
uintptr_t GameHook::WeaponB1Address = 0x5AA742C;
uintptr_t GameHook::WeaponB2Address = 0x5AA7430;

// tick
bool GameHook::comboMakerTest1 = false;
int GameHook::comboMakerMoveID1 = 0;
int GameHook::comboMakerMovePart1 = 0;
int GameHook::comboMakerStringID1 = 0;
bool GameHook::comboMakerTest2 = false;
int GameHook::comboMakerMoveID2 = 0;
int GameHook::comboMakerMovePart2 = 0;
int GameHook::comboMakerStringID2 = 0;

void GameHook::GameTick(void) {
    uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
    if (actorPlayable) {
        if (comboMakerTest1) {
            int& playerMoveIDValue = *(int*)(actorPlayable + 0x34C);
            int& playerAttackCount = *(int*)(actorPlayable + 0x95CBC);
            int& playerStringIDValue = *(int*)(actorPlayable + 0x95C64);
            if (playerMoveIDValue == comboMakerMoveID1 && playerAttackCount == comboMakerMovePart1) {
                playerStringIDValue = comboMakerStringID1;
            }
        }
        if (comboMakerTest2) {
            int& playerMoveIDValue = *(int*)(actorPlayable + 0x34C);
            int& playerAttackCount = *(int*)(actorPlayable + 0x95CBC);
            int& playerStringIDValue = *(int*)(actorPlayable + 0x95C64);
            if (playerMoveIDValue == comboMakerMoveID2 && playerAttackCount == comboMakerMovePart2) {
                playerStringIDValue = comboMakerStringID2;
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

            ImGui::Separator();

            ImGui::Text("Character");
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

            ImGui::Text("Costume");
            help_marker("Set while in mission select");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##CostumeSelectInputInt", &currentCostumeValue, 1, 100);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text(GameHook::CostumeNames(currentCostumeValue));

            ImGui::Separator();

            ImGui::Text("Third Accessory");
            ImGui::PushItemWidth(inputItemWidth);
            ImGui::InputInt("##ThirdAccessoryInputInt", &thirdAccessoryValue, 1, 100);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text(GameHook::AccessoryNames(thirdAccessoryValue));

            ImGui::Separator();

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
            if (ImGui::Checkbox("Disable Lockon Jump Dodge", &GameHook::disableLockOnDodge_toggle)) {
                GameHook::DisableLockOnDodge(GameHook::disableLockOnDodge_toggle);
            }

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
            if (ImGui::Checkbox("Infinite Crow Within", &GameHook::infBirdTime_toggle)) {
                InfBirdTime(infBirdTime_toggle);
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

            ImGui::Checkbox("Pause When Opening BayoHook", &GameHook::openMenuPause_toggle);

            ImGui::Separator();

            ImGui::Checkbox("Force Input Type", &GameHook::inputIcons_toggle);
            if (GameHook::inputIcons_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt(GetInputTypeName(inputIconsValue), &GameHook::inputIconsValue, 1, 100);
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Show 9.9+ Combo Multiplier UI", &GameHook::showComboUI_toggle);
            help_marker("Open a window that shows your current combo multiplier when passing 9.9x");
            if (GameHook::showComboUI_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("X Position ##ComboUIXInputFloat", &comboUI_X);
                ImGui::InputFloat("Y Position ##ComboUIYInputFloat", &comboUI_Y);
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Custom Camera Distance ##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            if (GameHook::customCameraDistance_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceInputFloat", &GameHook::customCameraDistance, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
            if (actorPlayable) {
                float* playerXYZPos[3];
                playerXYZPos[0] = (float*)(actorPlayable + 0xD0);
                playerXYZPos[1] = (float*)(actorPlayable + 0xD4);
                playerXYZPos[2] = (float*)(actorPlayable + 0xD8);

                ImGui::Separator();
                ImGui::Text("Player Position");
                ImGui::InputFloat3("##PlayerPositionInputFloat3", *playerXYZPos);
                if (ImGui::Button("Teleport to 0, 0, 0")) {
                    *playerXYZPos[0] = 0.0f;
                    *playerXYZPos[1] = 0.0f;
                    *playerXYZPos[2] = 0.0f;
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
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("##WeaponA1InputInt", &weaponA1Value, 1, 10);
                ImGui::SameLine();
                ImGui::Text(GameHook::WeaponNames(weaponA1Value));
                ImGui::InputInt("##WeaponA2InputInt", &weaponA2Value, 1, 10);
                ImGui::SameLine();
                ImGui::Text(GameHook::WeaponNames(weaponA2Value));
                ImGui::Text("Weapon Set B:");
                ImGui::InputInt("##WeaponB1InputInt", &weaponB1Value, 1, 10);
                ImGui::SameLine();
                ImGui::Text(GameHook::WeaponNames(weaponB1Value));
                ImGui::InputInt("##WeaponB2InputInt", &weaponB2Value, 1, 10);
                ImGui::SameLine();
                ImGui::Text(GameHook::WeaponNames(weaponB2Value));
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
                uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
                if (actorPlayable) {
                    float& playerMagicValue = *(float*)GameHook::playerMagicAddress; // not player offset but keeping it here anyway
                    float* playerXYZPos[3];
                    playerXYZPos[0] = (float*)(actorPlayable + 0xD0);
                    playerXYZPos[1] = (float*)(actorPlayable + 0xD4);
                    playerXYZPos[2] = (float*)(actorPlayable + 0xD8);
                    int& playerMoveID = *(int*)(actorPlayable + 0x34C);
                    int& playerMovePart = *(int*)(actorPlayable + 0x350);
                    int& playerMoveSomething = *(int*)(actorPlayable + 0x354);
                    float& playerAnimFrame = *(float*)(actorPlayable + 0x3E4);
                    int& playerHealthValue2 = *(int*)(actorPlayable + 0x6B4); // red damage
                    float& playerRemainingInvincibility = *(float*)(actorPlayable + 0x730);
                    int& playerHealthValue = *(int*)(actorPlayable + 0x93508); // health
                    int& playerStringID = *(int*)(actorPlayable + 0x95C64);
                    int& playerAttackCount = *(int*)(actorPlayable + 0x95CBC);
                    float& remainingWitchTimeValue = *(float*)(actorPlayable + 0x95D5C);
                    float* playerHairColour[3];
                    playerHairColour[0] = (float*)(actorPlayable + 0x96C00);
                    playerHairColour[1] = (float*)(actorPlayable + 0x96C04);
                    playerHairColour[2] = (float*)(actorPlayable + 0x96C08);
                    static float playerTempHairColour[3]{ 1.0f, 1.0f, 1.0f };

                    ImGui::Separator();

                    ImGui::Text("Player Position");
                    ImGui::InputFloat3("##PlayerPositionInputFloat3", *playerXYZPos);
                    if (ImGui::Button("Teleport to 0, 0, 0")) {
                        *playerXYZPos[0] = 0.0f;
                        *playerXYZPos[1] = 0.0f;
                        *playerXYZPos[2] = 0.0f;
                    }

                    ImGui::Text("Player HP");
                    if (ImGui::InputInt("##PlayerHPInputInt", &playerHealthValue, 1, 100)) {
                        playerHealthValue2 = playerHealthValue;
                    }

                    ImGui::Text("Player MP");
                    ImGui::InputFloat("##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");

                    ImGui::Text("Player Remaining Witch Time Duration");
                    ImGui::InputFloat("##PlayerRemainingWitchTimeDurationInputFloat", &remainingWitchTimeValue, 10, 100, "%.0f");

                    ImGui::Text("Player Remaining Invinciblity");
                    ImGui::InputFloat("##PlayerRemainingInvinciblityInputFloat", &playerRemainingInvincibility, 10, 100, "%.0f");

                    ImGui::Text("Player Animation Frame");
                    ImGui::InputFloat("##PlayerAnimationFrameInputFloat", &playerAnimFrame, 1, 10, "%.0f");

                    ImGui::Text("Player Move ID");
                    ImGui::InputInt("##PlayerMoveIDInputInt", &playerMoveID);

                    ImGui::Text("Player Move Part");
                    ImGui::InputInt("##PlayerMovePartInputInt", &playerMovePart);

                    ImGui::Text("Player String ID");
                    ImGui::InputInt("##PlayerStringIDInputInt", &playerStringID);

                    ImGui::Text("Player Move Something");
                    ImGui::InputInt("##PlayerMoveSomethingInputInt", &playerMoveSomething);

                    ImGui::Text("Player Attack Count");
                    ImGui::InputInt("##PlayerAttackCountInputInt", &playerAttackCount);

                    ImGui::Text("Player Hair Colour");
                    if (ImGui::ColorEdit3("##PlayerHairColourEdit3", playerTempHairColour)) { // ImGuiColorEditFlags_PickerHueWheel sry che
                        *playerHairColour[0] = playerTempHairColour[0] * 5.0f;
                        *playerHairColour[1] = playerTempHairColour[1] * 5.0f;
                        *playerHairColour[2] = playerTempHairColour[2] * 5.0f;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Reset##ResetHairColourButton")) {
                        playerTempHairColour[0] = 1.0f;
                        playerTempHairColour[1] = 1.0f;
                        playerTempHairColour[2] = 1.0f;
                        *playerHairColour[0] = playerTempHairColour[0];
                        *playerHairColour[1] = playerTempHairColour[1];
                        *playerHairColour[2] = playerTempHairColour[2];
                    }

                    /*static float hairIntensity = 1.0f;
                    if (ImGui::SliderFloat("Intensity", &hairIntensity, 0.0f, 10.0f)) {
                        *playerHairColour[0] = *playerHairColour[0] * hairIntensity;
                        *playerHairColour[1] = *playerHairColour[1] * hairIntensity;
                        *playerHairColour[2] = *playerHairColour[2] * hairIntensity;
                    }*/

                    /*uintptr_t armWeaveOffset = *(uintptr_t*)(actorPlayable + 0x937C0);
                    if (armWeaveOffset) {
                        float* armWeaveScale[3];
                        armWeaveScale[0] = (float*)(armWeaveOffset + 0xF0);
                        armWeaveScale[1] = (float*)(armWeaveOffset + 0xF4);
                        armWeaveScale[2] = (float*)(armWeaveOffset + 0xF8);
                        ImGui::Text("Arm Weave Scale");
                        ImGui::InputFloat3("##ArmWeaveScaleInputFloat3", *armWeaveScale);
                    }
                    uintptr_t legWeaveOffset = *(uintptr_t*)(actorPlayable + 0x937D0);
                    if (legWeaveOffset) {
                        float* legWeaveScale[3];
                        legWeaveScale[0] = (float*)(legWeaveOffset + 0xF0);
                        legWeaveScale[1] = (float*)(legWeaveOffset + 0xF4);
                        legWeaveScale[2] = (float*)(legWeaveOffset + 0xF8);
                        ImGui::Text("Leg Weave Scale");
                        ImGui::InputFloat3("##LegWeaveScaleInputFloat3", *legWeaveScale);
                    }*/
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

            ImGui::Checkbox("Move Swap Test ##MoveSwapTestToggle", &GameHook::moveIDSwap_toggle);
            help_marker("Do the move you want to see, pause mid anim, hit the first button\nDo the move you want to replace, pause mid anim, hit the second button");
            if (GameHook::moveIDSwap_toggle) {
                uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
                if (actorPlayable) {
                    int& playerMoveIDValue = *(int*)(actorPlayable + 0x34C);
                    ImGui::Text("Current Move ID");

                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##CurrentStringIDInputInt", &playerMoveIDValue, 0, 0);
                    ImGui::PopItemWidth();

                    ImGui::Text("Desired Move ID 1");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##DesiredMoveIDInputInt1", &GameHook::moveIDSwapDesiredMove1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Move ID as desired ##1")) {
                        GameHook::moveIDSwapDesiredMove1 = playerMoveIDValue;
                    }
                    ImGui::Text("Source Anim ID 1");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##SourceMoveIDInputInt1", &GameHook::moveIDSwapSourceMove1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Move ID as source ##2")) {
                        GameHook::moveIDSwapSourceMove1 = playerMoveIDValue;
                    }

                    ImGui::Separator();

                    ImGui::Text("Desired Move ID 2");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##DesiredMoveIDInputInt2", &GameHook::moveIDSwapDesiredMove2);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Move ID as desired ##2")) {
                        GameHook::moveIDSwapDesiredMove2 = playerMoveIDValue;
                    }
                    ImGui::Text("Source Anim ID 2");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##SourceMoveIDInputInt2", &GameHook::moveIDSwapSourceMove2);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current Move ID as source ##2")) {
                        GameHook::moveIDSwapSourceMove2 = playerMoveIDValue;
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("String Swap Test ##StringSwapTestToggle", &GameHook::stringIDSwap_toggle);
            help_marker("Do the string you want to see, pause mid anim, hit the first button\nDo the string you want to replace, pause mid anim, hit the second button");
            if (GameHook::stringIDSwap_toggle) {
                uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
                if (actorPlayable) {
                    int& playerStringIDValue = *(int*)(actorPlayable + 0x95C64);
                    ImGui::Text("Current String ID");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##CurrentStringIDInputInt", &playerStringIDValue, 0, 0);
                    ImGui::PopItemWidth();

                    ImGui::Separator();

                    ImGui::Text("Desired String ID 1");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##DesiredStringIDInputInt1", &GameHook::stringIDSwapDesiredString1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current String ID as desired ##1")) {
                        GameHook::stringIDSwapDesiredString1 = playerStringIDValue;
                    }
                    ImGui::Text("Source Anim ID 1");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##SourceStringIDInputInt1", &GameHook::stringIDSwapSourceString1);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current String ID as source ##1")) {
                        GameHook::stringIDSwapSourceString1 = playerStringIDValue;
                    }

                    ImGui::Separator();

                    ImGui::Text("Desired String ID 2");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##DesiredStringIDInputInt2", &GameHook::stringIDSwapDesiredString2);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current String ID as desired ##2")) {
                        GameHook::stringIDSwapDesiredString2 = playerStringIDValue;
                    }
                    ImGui::Text("Source Anim ID 2");
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##SourceStringIDInputInt2", &GameHook::stringIDSwapSourceString2);
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    if (ImGui::Button("Save Current String ID as source ##2")) {
                        GameHook::stringIDSwapSourceString2 = playerStringIDValue;
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("Combo Maker Test 1", &GameHook::comboMakerTest1);
            GameHook::help_marker("Compare to a moveid and number in attack string to swap out specific combo route transitions");
            GameHook::help_marker("Should you want more freedom than this provides,\n"
                "I've included a Cheat Engine table with examples and a script ready for editing in the Github repo's \"extra\" folder\n"
                "(link to repo in the Info tab)");
            if (GameHook::comboMakerTest1) {
                uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
                if (actorPlayable) {
                    int& playerMoveIDValue = *(int*)(actorPlayable + 0x34C);
                    int& playerAttackCount = *(int*)(actorPlayable + 0x95CBC);
                    int& playerStringIDValue = *(int*)(actorPlayable + 0x95C64);
                    ImGui::Text("Current MoveID = %i", playerMoveIDValue);
                    ImGui::Text("Current Number In String = %i", playerAttackCount);
                    ImGui::Text("Current String ID = %i", playerStringIDValue);
                    ImGui::Text("if MoveID ==");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerMoveID1InputInt", &comboMakerMoveID1);
                    ImGui::PopItemWidth();
                    ImGui::Text("and current attack number in string ==");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerMovePart1InputInt", &comboMakerMovePart1);
                    ImGui::PopItemWidth();
                    ImGui::Text("then StringID =");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerStringID1", &comboMakerStringID1);
                    ImGui::PopItemWidth();
                    // written in void GameHook::GameTick(void)
                }
                else 
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("Combo Maker Test 2", &GameHook::comboMakerTest2);
            GameHook::help_marker("The same as 1, but again");
            if (GameHook::comboMakerTest2) {
                uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
                if (actorPlayable) {
                    int& playerMoveIDValue = *(int*)(actorPlayable + 0x34C);
                    int& playerAttackCount = *(int*)(actorPlayable + 0x95CBC);
                    int& playerStringIDValue = *(int*)(actorPlayable + 0x95C64);
                    ImGui::Text("Current MoveID = %i", playerMoveIDValue);
                    ImGui::Text("Current Number In String = %i", playerAttackCount);
                    ImGui::Text("Current String ID = %i", playerStringIDValue);
                    ImGui::Text("if MoveID ==");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerMoveID2InputInt", &comboMakerMoveID2);
                    ImGui::PopItemWidth();
                    ImGui::Text("and current attack number in string ==");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerMovePart2InputInt", &comboMakerMovePart2);
                    ImGui::PopItemWidth();
                    ImGui::Text("then StringID =");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("##ComboMakerStringID2", &comboMakerStringID2);
                    ImGui::PopItemWidth();
                    // written in void GameHook::GameTick(void)
                }
                else 
                    ImGui::Text("Load in to a stage to see these stats");
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
            static std::array<ImGuiURL, 7> links1{
                ImGuiURL { "SSSiyan", "https://twitter.com/sssiyan" },
                ImGuiURL { "GarudaKK", "https://www.youtube.com/@GarudaPSN" },
                ImGuiURL { "Kerilk", "https://github.com/Kerilk" },
                ImGuiURL { "CreativeHandle", "https://twitter.com/CreativeHandler" },
                ImGuiURL { "Skyth", "https://github.com/blueskythlikesclouds" },
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

const char* GameHook::WeaponNames(int weaponID) {
    switch (weaponID) {
    case 0:
        return "Scarborough Fair";
    case 1:
        return "Onyx Roses";
    case 2:
        return "Shuraba";
    case 3:
        return "Kulshedra";
    case 6:
        return "Durga";
    case 7:
        return "Lt. Col. Kilgore";
    case 8:
        return "Odette";
    case 9:
        return "Sai Fung";
    case 10:
        return "Handguns";
    case 11:
        return "Handguns";
    case 13:
        return "Onyx Roses Alt";
    case 14:
        return "Durga Alt";
    case 15:
        return "Lt. Col. Kilgore Alt";
    case 16:
        return "Pillowtalk";
    case 17:
        return "Bazillions";
    case 18:
        return "Rodin";
    default:
        return "";
    }
}

const char* GameHook::CostumeNames(int costumeID) {
    switch (costumeID) {
    case 0:
        return "Bayonetta Default";
    case 1:
        return "Bayonetta P.E. A";
    case 2:
        return "Bayonetta P.E. B";
    case 3:
        return "Bayonetta P.E. C";
    case 4:
        return "Bayonetta d'Arc";
    case 5:
        return "Bayonetta Old";
    case 6:
        return "Bayonetta Umbra";
    case 7:
        return "Bayonetta Various A";
    case 8:
        return "Bayonetta Various B";
    case 9:
        return "Bayonetta Various C";
    case 10:
        return "Bayonetta Umbran Komachi A";
    case 11:
        return "Bayonetta Umbran Komachi B";
    case 12:
        return "Bayonetta Umbran Komachi C";
    case 13:
        return "Bayonetta Nun";
    case 14:
        return "Bayonetta Queen";
    case 15:
        return "Jeanne Default";
    case 16:
        return "Jeanne P.E. A";
    case 17:
        return "Jeanne P.E. B";
    case 18:
        return "Jeanne P.E. C";
    case 19:
        return "Jeanne Formal B";
    case 20:
        return "Jeanne Formal A";
    case 21:
        return "Jeanne Old";
    case 22:
        return "Jeanne Umbra";
    case 23:
        return "Jeanne Various A";
    case 24:
        return "Jeanne Various B";
    case 25:
        return "Jeanne Various C";
    case 26:
        return "Jeanne Umbran Komachi A";
    case 27:
        return "Jeanne Umbran Komachi B";
    case 28:
        return "Jeanne Umbran Komachi C";
    case 29:
        return "Jeanne Nun";
    case 30:
        return "Jeanne Queen";
    case 31:
        return "Little King Zero";
    default:
        return "";
    }
}
const char* GameHook::AccessoryNames(int accessoryID) {
    switch (accessoryID) {
    case 0:
        return "None";
    case 1:
        return "Sergey's Lover";
    case 2:
        return "Infernal Communicator";
    case 3:
        return "Pulley's Butterfly";
    case 4:
        return "Selene's Light";
    case 5:
        return "Star of Dinéta";
    case 6:
        return "Evil Harvest Rosary";
    case 7:
        return "Gaze of Despair";
    case 8:
        return "Moon of Mahaa-Kalaa";
    case 9:
        return "Eternal Testimony";
    case 10:
        return "Bracelet of Time";
    case 11:
        return "Climax Brace";
    case 12:
        return "Immortal Marionette";
    default:
        return "";
    }
}

const char* GameHook::GetInputTypeName(int inputTypeID) {
    switch (inputTypeID) {
    case 0:
        return "Keyboard";
    case 1:
        return "Gamepad";
    default:
        return "";
    }
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
    }
}
