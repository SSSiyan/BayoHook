#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>
#include <algorithm>

const char* GameHook::weaponNames[19] {
    "Scarborough Fair",     //  0
    "Onyx Roses",           //  1
    "Shuraba",              //  2
    "Kulshedra",            //  3
    "Empty 1",              //  4
    "Empty 2",              //  5
    "Durga",                //  6
    "Lt. Col. Kilgore",     //  7
    "Odette",               //  8
    "Sai Fung",             //  9
    "Handguns Unused",      // 10
    "Handguns",             // 11
    "Empty 3",              // 12
    "Onyx Roses Alt",       // 13
    "Durga Alt",            // 14
    "Lt. Col. Kilgore Alt", // 15
    "Pillowtalk",           // 16
    "Bazillions",           // 17
    "Rodin",                // 18
};

const char* GameHook::weaveNames[37]{
    // Note: LtF=Left to Right, RtL=Right to Left, hk=Hand Knife, T=Tetsuzanko
    "Forward Punch",                     //  0
    "Vertical punch",                    //  1
    "Vertical punch",                    //  2
    "Forward punch",                     //  3
    "Forward punch T",                   //  4
    "Downward punch",                    //  5
    "Saifung forward push",              //  6
    "Saifung forward push",              //  7
    "Whip RtL swipe",                    //  8
    "Whip RtL swipe",                    //  9
    "Whip LtR swipe",                    // 10
    "Whip LtR swipe",                    // 11
    "Whip LtR swipe",                    // 12
    "Fire Durga forward hk punch",       // 13
    "Fire Durga RtL swipe",              // 14
    "Fire Durga LtR swipe",              // 15
    "Fire Durga vertical hk punch",      // 16
    "Fire Durga vertical hk punch",      // 17
    "Fire Durga forward hk punch",       // 18
    "Fire Durga forward hk punch T",     // 19
    "Fire Durga downward hk punch",      // 20
    "Fire Durga downward hk punch",      // 21
    "Electric Durga forward hk punch",   // 22
    "Electric Durga RtL swipe",          // 23
    "Electric Durga LtR swipe",          // 24
    "Electric Durga vertical hk punch",  // 25
    "Electric Durga vertical hk punch",  // 26
    "Electric Durga forward hk punch",   // 27
    "Electric Durga forward hk punch T", // 28
    "Electric Durga downward hk punch",  // 29
    "Electric Durga downward hk punch",  // 30
    "Electric Durga forward punch",      // 31
    "Electric Durga vertical punch",     // 32
    "Electric Durga vertical punch",     // 33
    "Electric Durga forward hk punch",   // 34
    "Electric Durga forward hk punch T", // 35
    "Electric Durga downward punch",     // 36
};

const char* GameHook::costumeNames[32] {
    "Bayonetta Default",          //  0
    "Bayonetta P.E. A",           //  1
    "Bayonetta P.E. B",           //  2
    "Bayonetta P.E. C",           //  3
    "Bayonetta d'Arc",            //  4
    "Bayonetta Old",              //  5
    "Bayonetta Umbra",            //  6
    "Bayonetta Various A",        //  7
    "Bayonetta Various B",        //  8
    "Bayonetta Various C",        //  9
    "Bayonetta Umbran Komachi A", // 10
    "Bayonetta Umbran Komachi B", // 11
    "Bayonetta Umbran Komachi C", // 12
    "Bayonetta Nun",              // 13
    "Bayonetta Queen",            // 14
    "Jeanne Default",             // 15
    "Jeanne P.E. A",              // 16
    "Jeanne P.E. B",              // 17
    "Jeanne P.E. C",              // 18
    "Jeanne Formal B",            // 19
    "Jeanne Formal A",            // 20
    "Jeanne Old",                 // 21
    "Jeanne Umbra",               // 22
    "Jeanne Various A",           // 23
    "Jeanne Various B",           // 24
    "Jeanne Various C",           // 25
    "Jeanne Umbran Komachi A",    // 26
    "Jeanne Umbran Komachi B",    // 27
    "Jeanne Umbran Komachi C",    // 28
    "Jeanne Nun",                 // 29
    "Jeanne Queen",               // 30
    "Little King Zero",           // 31
};

const char* GameHook::accessoryNames[13] {
    "None",                  //  0
    "Sergey's Lover",        //  1
    "Infernal Communicator", //  2
    "Pulley's Butterfly",    //  3
    "Selene's Light",        //  4
    "Star of Dinéta",        //  5
    "Evil Harvest Rosary",   //  6
    "Gaze of Despair",       //  7
    "Moon of Mahaa - Kalaa", //  8
    "Eternal Testimony",     //  9
    "Bracelet of Time",      // 10
    "Climax Brace",          // 11
    "Immortal Marionette",   // 12
};

const char* GameHook::moveIDNames[350] {
"0: Handguns Idle",
"1: Handguns Lock On Stance",
"2: Handguns Aim",
"3: Handguns Slightly move forward",
"4: Handguns Slightly move forward",
"5: Handguns Slightly move forward",
"6: Handguns Move",
"7: Handguns Move backward",
"8: Handguns Short Taunt",
"9: Eyerape landing",
"10: Landing",
"11: Jump",
"12: Landing animation after jump",
"13: Latch Landing",
"14: Latch and Roll Over",
"15: Beast Within Jump QTE",
"16: Landing",
"17: Backward Dodge",
"18: Dodge limit jump",
"19: Unused Umbran Spear Stiletto",
"20: Momk (Double tap to perfect parry)",
"21: Momk but nothing",
"22: Falling due to the wind",
"23: Damaged bounce",
"24: Landing",
"25: Jump with Screen shaking effect",
"26: Landing",
"27: Beast Within Activation",
"28: Beast Within Deactivation",
"29: Beast Within Jump",
"30: Beast Within with slightly move forward",
"31: Crow Within Jump",
"32: Crow Within Landing",
"33: Umbran Spear",
"34: Beast Within but with a delay",
"35: Beast Within Deactivation but Sliding forward",
"36: Beast Within Deactivation in a frame",
"37: Beast Within Deactivation but Sliding forward",
"38: Beast Within Deactivation",
"39: Bat Within",
"40: Crow Within Activation",
"41: Crow Within Deactivation in a frame",
"42: Crow Within Punch Feather Summon",
"43: Crow Within Kick Feather Summon",
"44: Unknown",
"45: Unknown",
"46: Unknown",
"47: Unknown",
"48: Unknown",
"49: Punch Bullet Climax",
"50: Instant Punch Bullet Climax",
"51: Bullet Climax Reset to Lock On Stance",
"52: Kick Bullet Climax",
"53: Instant Kick Bullet Climax",
"54: Kick Bullet Climax Reset to Lock On Stance",
"55: Punch",
"56: Air Punch",
"57: Uplift Punch",
"58: Uplift Punch with Wicked Weave",
"59: Stiletto",
"60: Tetsuzanko",
"61: PKP Wicked Weave",
"62: PP'P",
"63: PP'P Wicked Weave",
"64: Witch Twist",
"65: Breakdance",
"66: Kinship counter attack while being strangled by a clamp",
"67: PPPPP",
"68: Air PPPPP",
"69: Punch punish attack wicked weave",
"70: Uplift Kick",
"71: Uplift Kick Wicked Weave",
"72: Afterburner Kick",
"73: Dive Kick Bounce",
"74: Heel Slide",
"75: Unused Kick similar to iron maiden TA with wicked weave",
"76: Heel Stomp",
"77: PPKK",
"78: Kick",
"79: PK",
"80: PP'K",
"81: PPKKK",
"82: Air Kick",
"83: PPPPPK",
"84: Air PPPPPK",
"85: Umbran Portal Kick",
"86: Unused Spin Kick similar to 66",
"87: PPP'K/PPPPK",
"88: Spin Kick",
"89: PPPK (Tap more to do the full combo of PPPKKK)",
"90: PPK",
"91: Air PPP'K/PPPPK",
"92: Air PPPKKK (Tap more to do the full combo of PPPKKK)",
"93: Air PPK",
"94: Kick Punish Attack",
"95: Shuraba Punch",
"96: Shuraba Air Punch",
"97: Shuraba PP'P (Tap more to do the full combo of PP'PPP)",
"98: Shuraba Air PP'P (Tap more to do the full combo of PP'PPP)",
"99: Shuraba Charge",
"100: Shuraba Unused PPPPP Charge Animation",
"101: Shuraba Air Unused PPPPP Charge Animation",
"102: Shuraba Uplift Punch",
"103: Shuraba Air Uplift Punch",
"104: Shuraba Stiletto",
"105: Shuraba Tetsuzanko",
"106: Shuraba PKP",
"107: Shuraba Air Charge",
"108: Shuraba PPP'P",
"109: Shuraba Air PPP'P",
"110: Shuraba Spin Punch",
"111: Shuraba Air Spin Punch",
"112: Shuraba Lock On Charge",
"113: Shuraba Short Lock On Charge Attack",
"114: Shuraba Instant Lock On Charge",
"115: Shuraba Punch Punish Attack",
"116: Kulshedra Punch",
"117: Kulshedra Air Punch",
"118: Kulshedra PP'P",
"119: Kulshedra Uplift Punch",
"120: Kulshedra Stiletto",
"121: Kulshedra Tetsuzanko",
"122: Kulshedra Tetsuzanko Wicked Weave",
"123: Kulshedra Spin Punch",
"124: Kulshedra Cowboy Spin",
"125: Kulshedra Unused Launch Forward",
"126: Kulshedra Drag Enemy to Player",
"127: Kulshedra Drag Fail",
"128: Kulshedra Launch Forward",
"129: Kulshedra Slap",
"130: Kulshedra Air Slap",
"131: Kulshedra Punch Punish Attack",
"132: Durga Fire Punch",
"133: Durga Air Fire Punch",
"134: Durga Punch Spin",
"135: Durga Kick Spin",
"136: Durga Electric kick",
"137: Durga Fire Kick",
"138: Durga Electric Punch",
"139: Durga Electric Air Punch",
"140: Durga Fire PPKK Wicked Weave",
"141: Durga Fire PK",
"142: Durga PP'K Wicked Weave",
"143: Durga PPKKK Wicked Weave",
"144: Durga Air Kick",
"145: Durga PPPPPK",
"146: Durga PPPPPK",
"147: Durga PPPPP",
"148: Durga PPPPP",
"149: Durga PPPPK",
"150: Durga PPPK (tap more to do the full combo of PPPKKK)",
"151: Durga PPK",
"152: Durga Air PPP'K/PPPPK",
"153: Durga Air PPPK (tap more to do the full combo of PPPKKK)",
"154: Durga Air PPK",
"155: Durga Uplift Punch",
"156: Durga Stiletto",
"157: Durga Air Stiletto",
"158: Durga Fire PP'P",
"159: Durga Air Fire PP'P",
"160: Durga PKP",
"161: Durga Uplift Punch Wicked Weave",
"162: Durga Heel Slide",
"163: Durga Punch Punish Attack",
"164: Durga PP'P/PPPP'P",
"165: Kilgore Punch",
"166: Kilgore Air Punch",
"167: Kilgore Stiletto",
"168: Kilgore Uplift Punch",
"169: Kilgore Kick",
"170: Kilgore Punch Spin",
"171: Kilgore Air Punch Spin",
"172: Kilgore Kick Spin",
"173: Kilgore Air Kick Spin",
"174: Kilgore PKP",
"175: Kilgore PPK without effect",
"176: Kilgore Air PPK without effect",
"177: Kilgore PPKK Wicked Weave",
"178: Kilgore PPKKK Wicked Weave",
"179: Kilgore PPPK without effect (tap more to do the full combo of PPPKKK)",
"180: Kilgore Air PPPK without effect (tap more to do the full combo of PPPKKK)",
"181: Kilgore Kick Punish Attack",
"182: Kilgore Punch Punish Attack",
"183: Odette Kick",
"184: Odette Spin attack with a small jump",
"185: Odette Joystick Spin",
"186: Odette Charge Kick",
"187: Odette PPK",
"188: Odette PPKK Wicked Weave",
"189: Odette PPKKK Wicked Weave",
"190: Odette PPPK (tap more to do the full combo of PPPKKK)",
"191: Odette Air PPK",
"192: Odette Air PPPK (tap more to do the full combo of PPPKKK)",
"193: Odette PK",
"194: Odette PP'K/PPP'K/PPPPK Wicked Weave",
"195: Saifung Punch",
"196: Saifung Air Punch",
"197: Saifung PPPPP",
"198: Saifung Air PPPPP",
"199: Saifung Punch Bullet Climax",
"200: Saifung Air Punch Bullet Climax",
"201: Saifung Bullet Climax Retrieve",
"202: Saifung Air Bullet Climax Retrieve",
"203: Saifung PP'P",
"204: Saifung Air PP'P",
"205: Saifung PPPP'P",
"206: Saifung Air PPPP'P",
"207: Saifung PKP",
"208: Saifung Stiletto",
"209: Saifung Air Stiletto",
"210: Saifung Uplift Punch",
"211: Saifung Air Uplift Punch",
"212: Saifung Charge",
"213: Saifung Charge",
"214: Saifung Punch Punish Attack",
"215: Rodin/Angel Weapon Angel Pole Attack",
"216: Rodin/Angel Weapon Air Angel Pole Attack",
"217: Rodin/Angel Weapon Angel Pole Spin QTE",
"218: Rodin/Angel Weapon Unknown",
"219: Rodin/Angel Weapon Unknown",
"220: Rodin/Angel Weapon Sword Dash Forward",
"221: Rodin/Angel Weapon Air Sword Dash Forward",
"222: Rodin/Angel Weapon Angel Bow Melee Attack",
"223: Rodin/Angel Weapon Air Angel Bow Melee Attack",
"224: Rodin/Angel Weapon Angel Bow Shooting",
"225: Rodin/Angel Weapon Flail Continuous Attack",
"226: Rodin/Angel Weapon Air Flail Continuous Attack",
"227: Rodin/Angel Weapon Flail Hard Attack",
"228: Rodin/Angel Weapon Air Flail Hard Attack",
"229: Rodin/Angel Weapon Axe Spin Attack",
"230: Rodin/Angel Weapon Air Axe Spin Attack",
"231: Rodin/Angel Weapon Claw Attack",
"232: Rodin/Angel Weapon Unknown",
"233: Rodin/Angel Weapon Electric Claw Charge",
"234: Rodin/Angel Weapon Air Electric Claw Charge",
"235: Rodin/Angel Weapon Fire Claw Charge",
"236: Rodin/Angel Weapon Air Fire Claw Charge",
"237: Rodin/Angel Weapon Trumpet shooting",
"238: Rodin/Angel Weapon Trumpet heavy shooting",
"239: Rodin/Angel Weapon French Horn Shooting",
"240: Rodin/Angel Weapon French Horn Spin",
"241: Rodin/Angel Weapon Uplift Sword",
"242: Rodin/Angel Weapon Uplift Bow",
"243: Rodin/Angel Weapon Chainsaw",
"244: Rodin/Angel Weapon Air Chainsaw",
"245: Rodin/Angel Weapon Pick Up Angel Weapons",
"246: Unknown",
"247: Unknown",
"248: Unknown",
"249: Unknown",
"250: Unknown",
"251: Unknown",
"252: Unknown",
"253: Unknown",
"254: Unknown",
"255: Unknown",
"256: Unknown",
"257: Unknown",
"258: Unknown",
"259: Unknown",
"260: Unknown",
"261: Unknown",
"262: Unknown",
"263: Unknown",
"264: Unknown",
"265: Unknown",
"266: Unknown",
"267: Unknown",
"268: Unknown",
"269: Unknown",
"270: Unknown",
"271: Unknown",
"272: Unknown",
"273: Unknown",
"274: Unknown",
"275: Unknown",
"276: Unknown",
"277: Unknown",
"278: Unknown",
"279: Unknown",
"280: Unknown",
"281: Unknown",
"282: Unknown",
"283: Unknown",
"284: Unknown",
"285: Unknown",
"286: Unknown",
"287: Unknown",
"288: Unknown",
"289: Unknown",
"290: Unknown",
"291: Unknown",
"292: Unknown",
"293: Unknown",
"294: Unknown",
"295: Unknown",
"296: Unknown",
"297: Unknown",
"298: Unknown",
"299: Unknown",
"300: Unknown",
"301: Unknown",
"302: Unknown",
"303: Unknown",
"304: Unknown",
"305: Unknown",
"306: Unknown",
"307: Unknown",
"308: Unknown",
"309: Unknown",
"310: Unknown",
"311: Unknown",
"312: Unknown",
"313: Unknown",
"314: Unknown",
"315: Unknown",
"316: Unknown",
"317: Unknown",
"318: Unknown",
"319: Unknown",
"320: Unknown",
"321: Unknown",
"322: Unknown",
"323: Unknown",
"324: Unknown",
"325: Unknown",
"326: Unknown",
"327: Unknown",
"328: Unknown",
"329: Unknown",
"330: Unknown",
"331: Unknown",
"332: Unknown",
"333: Unknown",
"334: Unknown",
"335: Unknown",
"336: Unknown",
"337: Unknown",
"338: Unknown",
"339: Unknown",
"340: Unknown",
"341: Unknown",
"342: Unknown",
"343: Unknown",
"344: Unknown",
"345: Unknown",
"346: Unknown",
"347: Unknown",
"348: Unknown",
"349: Unknown",
};

void GameHook::GameTick(void) { // also called while the menu isn't open
    static bool isFirstFrame = true;
    LocalPlayer* player = GetLocalPlayer();
    isFirstFrame = false;
    if (player) {
        if (comboMakerToggle) {
            for (int i = 0; i < maxComboMakers; ++i) {
                if (comboMaker_toggles[i]) {
                    if (player->moveID == comboMakerMoveIDs[i] && player->attackCount == comboMakerMoveParts[i]) {
                        player->stringID = comboMakerStringIDs[i];
                    }
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

            if (ImGui::Checkbox("Deal No Damage (F1)##DealNoDamageToggle", &GameHook::enemyHP_no_damage_toggle)) {
                GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
                if (GameHook::enemyHP_no_damage_toggle)
                    GameHook::enemyHP_one_hit_kill_toggle = false;
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Take No Damage (F2)", &GameHook::takeNoDamage_toggle)) {
                GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
            }

            if (ImGui::Checkbox("One Hit Kill (F3)##OneHitKillToggle", &GameHook::enemyHP_one_hit_kill_toggle)) {
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

            ImGui::Checkbox("Freeze Magic##InfMagicToggle", &GameHook::inf_magic_toggle);
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

            ImGui::Checkbox("Damage Dealt Multiplier##DamageDealtMultiplierToggle", &GameHook::damageDealtMultiplier_toggle);
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
            if (ImGui::Checkbox("Freeze Difficulty", &freezeDifficulty_toggle)) {
                GameHook::FreezeDifficulty(freezeDifficulty_toggle);
            }
            help_marker("Stop the difficulty being restored when loading a new stage");

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

            if (ImGui::Checkbox("Infinite Jumps (F4)##InfJumpsToggle", &GameHook::infJumps_toggle)) {
                GameHook::InfJumps(GameHook::infJumps_toggle);
            }
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Disable After Burner Bounce", &GameHook::disableAfterBurnerBounce_toggle)) {
                DisableAfterBurnerBounce(GameHook::disableAfterBurnerBounce_toggle);
            }

            ImGui::Checkbox("Cancellable After Burner", &GameHook::cancellableAfterBurner_toggle);
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Cancellable Falling Kick", &GameHook::cancellableFallingKick_toggle);

            ImGui::Checkbox("Alt Umbran Spear Input", &GameHook::altTeleInput_toggle);
            help_marker("Umbran Spear = Lockon + Taunt\nTaunt = Dpad Down");
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

            ImGui::Checkbox("Omnicancel Umbran Spear", &GameHook::omnicancelTele_toggle);
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Umbran Spear Combo", &GameHook::teleportComboAction_toggle);
            ImGui::SameLine();
            help_marker("Umbran spear will refresh your combo timer");

            ImGui::Separator();

            ImGui::Checkbox("Witch Time Multiplier##WitchTimeToggle", &GameHook::witchTimeMultiplier_toggle);
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
            ImGui::Checkbox("Easier Mashing##EasierMashToggle", &GameHook::easierMash_toggle);

            if (ImGui::Checkbox("Force Summoning Clothes (F6)##LessClothesToggle", &GameHook::lessClothes_toggle)) {
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
                ImGui::InputFloat("X Position##ComboUIXInputFloat", &comboUI_X, 0.001f, 0.01f);
                ImGui::InputFloat("Y Position##ComboUIYInputFloat", &comboUI_Y, 0.001f, 0.01f);
                ImGui::PopItemWidth();
            }

            ImGui::Separator();

            ImGui::Checkbox("Custom Camera Distance##CameraDistanceMultiplierToggle", &GameHook::customCameraDistance_toggle);
            if (GameHook::customCameraDistance_toggle) {
                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputFloat("##CustomCameraDistanceInputFloat", &GameHook::customCameraDistance, 0.1f, 1, "%.1f");
                ImGui::PopItemWidth();
            }

            LocalPlayer* player = GetLocalPlayer();
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

                ImGui::PushItemWidth(inputItemWidth * 2);
                ImGui::InputInt("Halos##HaloInputInt", &halosValue, 1, 100);
                ImGui::PopItemWidth();

                ImGui::PushItemWidth(inputItemWidth);
                ImGui::InputInt("Chapters Played##ChapterInputInt", &chaptersPlayedValue, 1, 100);
                ImGui::InputInt("Combo Points##ComboPointsInputInt", &comboPointsValue, 10, 100);
                ImGui::InputFloat("Combo Multiplier##ComboMultiplierInputFloat", &comboMultiplierValue, 1, 10, "%.1f");
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
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    float& playerMagicValue = *(float*)GameHook::playerMagicAddress; // not player offset but keeping it here anyway

                    ImGui::Separator();

                    ImGui::InputFloat3("Position##PlayerPositionInputFloat3", &player->pos.x);
                    if (ImGui::Button("Teleport to 0, 0, 0")) {
                        player->pos = { 0.0f, 0.0f, 0.0f };
                    }
                    ImGui::PushItemWidth(inputItemWidth);
                    ImGui::InputInt("HP##PlayerHPInputInt", &player->hp, 10, 100);
                    ImGui::InputInt("HPDamage##PlayerHPDamageInputInt", &player->hpDamage, 10, 100);
                    ImGui::InputFloat("MP##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");
                    ImGui::InputFloat("Remaining Witch Time Duration##PlayerRemainingWitchTimeDurationInputFloat", &player->witchTimeDuration, 10, 100, "%.0f");
                    ImGui::InputFloat("Remaining Invinciblity##PlayerRemainingInvinciblityInputFloat", &player->iFramesRemaining, 10, 100, "%.0f");
                    ImGui::InputFloat("Animation Frame##PlayerAnimationFrameInputFloat", &player->animFrame, 1, 10, "%.0f");
                    //ImGui::InputInt("Move ID##PlayerMoveIDInputInt", &player->moveID);
                    ImGui::Combo("##PlayerMoveIDCombo", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
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
                    ImGui::Combo("+34C moveID", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                    ImGui::InputInt("+350 movePart", &player->movePart);
                    ImGui::InputInt("+354 invincibility", &player->invincibility);
                    ImGui::InputInt("+358 summoningSomething", &player->summoningSomething);
                    ImGui::InputFloat("+3E4 animFrame", &player->animFrame);
                    ImGui::InputInt("+69C aerial", &player->aerial);
                    ImGui::InputInt("+6B4 hpDamage", &player->hpDamage, 10, 100);
                    ImGui::InputFloat("+6CC speed", &player->speed);
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
                    ImGui::InputInt("+93508 hp", &player->hp);
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
                    ImGui::InputFloat("+95D60 witchTimeMaxProbably", &player->witchTimeMaxProbably, 10,100, "%.0f");
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

            GameHook::windowHeightHack = std::clamp(ImGui::GetCursorPosY() + GameHook::windowHeightBorder, 0.0f, GameHook::maxWindowHeight);
            ImGui::EndChild();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Extra")) {
            ImGui::BeginChild("ExtraChild");

            ImGui::Checkbox("Move ID Swaps", &moveIDSwapsToggle);
            GameHook::help_marker("Do the move you want to replace, pause mid anim, type your current moveID in the first box\n"
                "Do the move you want to see, pause mid anim, type your current moveID in the second box\n"
                "Don't forget to save once you're done for next boot!");
            if (GameHook::moveIDSwapsToggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInMoveIDSwaps", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                    for (int i = 0; i < GameHook::maxMoveIDSwaps; ++i) {
                        ImGui::Checkbox(("Move Swap[" + std::to_string(i + 1) + "]").c_str(), &moveIDSwap_toggles[i]);
                        if (GameHook::moveIDSwap_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("Replace Move ID");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##CurrentMoveIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSourceMoves[i], 0, 0);
                            ImGui::Combo(("##SourceMoveIDComboInMoveIDSwap" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSourceMoves[i], GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                            ImGui::SameLine();
                            ImGui::Text("with");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##DesiredMoveIDInputInt" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSwappedMoves[i]);
                            ImGui::Combo(("##DesiredMoveIDComboInMoveIDSwap" + std::to_string(i)).c_str(), &GameHook::moveIDSwapSwappedMoves[i], GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                            ImGui::PopItemWidth();
                        }
                    }
                }
                else
                    ImGui::Text("Load in to a stage to see these stats");
            }

            ImGui::Separator();

            ImGui::Checkbox("Combo Maker", &GameHook::comboMakerToggle);
            if (GameHook::comboMakerToggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInComboMaker", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                    ImGui::Text("Current Number In String: %i", player->attackCount);
                    ImGui::Text("Current String ID: %i", player->stringID);
                    for (int i = 0; i < maxComboMakers; ++i) {
                        ImGui::Checkbox(("Combo Maker[" + std::to_string(i + 1) + "]").c_str(), &comboMaker_toggles[i]);
                        if (comboMaker_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("if Move ID ==");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##ComboMakerMoveID" + std::to_string(i) + "InputInt").c_str(), &comboMakerMoveIDs[i]);
                            ImGui::Combo(("##MoveIDInComboMaker" + std::to_string(i)).c_str(), &GameHook::comboMakerMoveIDs[i], GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
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

            ImGui::Checkbox("Weave Swaps", &GameHook::customWeaveToggle);
            if (GameHook::customWeaveToggle) {
                LocalPlayer* player = GetLocalPlayer();
                if (player) {
                    ImGui::Text("Current Move ID:");
                    ImGui::Combo("##PlayerMoveIDComboInWeaveSwaps", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
                    for (int i = 0; i < customWeaveCount; ++i) {
                        ImGui::Checkbox(("Custom Weave[" + std::to_string(i + 1) + "]").c_str(), &customWeaves_toggles[i]);
                        if (customWeaves_toggles[i]) {
                            ImGui::PushItemWidth(inputItemWidth);
                            ImGui::Text("If Move ID ==");
                            ImGui::SameLine();
                            //ImGui::InputInt(("##customWeaveMoveIDArray" + std::to_string(i)).c_str(), &customWeaveMoveIDArray[i]);
                            ImGui::Combo(("##customWeaveMoveIDArray" + std::to_string(i)).c_str(), &GameHook::customWeaveMoveIDArray[i], GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
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

            ImGui::Checkbox("String Swaps", &GameHook::stringSwapsToggle);
            if (GameHook::stringSwapsToggle) {
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
