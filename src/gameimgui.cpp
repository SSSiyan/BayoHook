#include <base.h>
#include "gamehook.hpp"
#include "LicenseStrings.hpp"
#include <array>
#include <algorithm> // Ensure this header is included for std::min
#include <chrono>

const char* GameHook::costumeNames[32]{
    "Bayo Default",          //  0
    "Bayo P.E. A",           //  1
    "Bayo P.E. B",           //  2
    "Bayo P.E. C",           //  3
    "Bayo d'Arc",            //  4
    "Bayo Old",              //  5
    "Bayo Umbra",            //  6
    "Bayo Various A",        //  7
    "Bayo Various B",        //  8
    "Bayo Various C",        //  9
    "Bayo Komachi A",        // 10
    "Bayo Komachi B",        // 11
    "Bayo Komachi C",        // 12
    "Bayo Nun",              // 13
    "Bayo Queen",            // 14
    "Jeanne Default",        // 15
    "Jeanne P.E. A",         // 16
    "Jeanne P.E. B",         // 17
    "Jeanne P.E. C",         // 18
    "Jeanne Formal B",       // 19
    "Jeanne Formal A",       // 20
    "Jeanne Old",            // 21
    "Jeanne Umbra",          // 22
    "Jeanne Various A",      // 23
    "Jeanne Various B",      // 24
    "Jeanne Various C",      // 25
    "Jeanne Komachi A",      // 26
    "Jeanne Komachi B",      // 27
    "Jeanne Komachi C",      // 28
    "Jeanne Nun",            // 29
    "Jeanne Queen",          // 30
    "Little King Zero",      // 31
};

#ifndef SPEEDRUN_BUILD
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

const char* GameHook::accessoryNames[13] {
    "None",                  //  0
    "Sergey's Lover",        //  1
    "Infernal Communicator", //  2
    "Pulley's Butterfly",    //  3
    "Selene's Light",        //  4
    "Star of Dine'ta",       //  5 // é
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
#endif

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
#ifndef SPEEDRUN_BUILD
    *(int*)GameHook::thirdAccessoryAddress = GameHook::desiredThirdAccessory;
#endif
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
        Setup3dShapes();
        Draw3dShapes();
        DrawFlyingStats();
#endif
        if (forceHairColour_toggle) { ApplyHairColour(player); }
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

    static std::array<ImGuiURL, 12> links1{
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

    ImGui::Separator();

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
            GameHook::comboUI_Y = 0.215f;
        }
        ImGui::Unindent();
    }
}

struct AreaIDName {
    int ID;
    const char* name;
};

static AreaIDName areaIDNames[] = {
    { 0x0, "Start Screen" },
    { 0xa10, "Chapter Menu" },
    { 0x1a1, "RT - The Witch Hunts" },
    { 0x1a1, "P - Vestibule" },
    { 0x114, "I - The Angel's Metropolis" },
    { 0x12B, "II - Vigrid, City of Deja Vu" },
    { 0x132, "III - The Burning Ground" },
    { 0x151, "IV - The Cardinal Virtue of Fortitude" },
    { 0x201, "V - The Lost Holy Grounds" },
    { 0x211, "VI - The Gates of Paradise" },
    { 0x214, "VII - The Cardinal Virtue of Temperance" },
    { 0x301, "VIII - Route 666" },
    { 0x311, "IX - Paradiso-A Remembrance of Time" },
    { 0x321, "X - Paradiso-A Sea of Stars" },
    { 0x320, "XI - The Cardinal Virtue of Justice (Set Part to 15)" },
    { 0x402, "XII - The Broken Sky" },
    { 0x421, "XIII - The Cardinal Virtue of Prudence" },
    { 0x501, "XIV - Isla Del Sol" },
    { 0x512, "XIV - Jeanne Fight" },
    { 0x521, "XV - A Tower to Truth" },
    { 0x532, "XVI - The Lumen Sage" },
    { 0x5a1, "E - Requiem" },
    { 0xB00, "LC - Angel Slayer" },
};

void DrawAreaJump() {
    static int stageID = 0x0;
    static int stagePart = 0x0;
    static int spawn = -1;
    static constexpr int step = 1;
    ImGui::SeparatorText("Area Jump");
    ImGui::PushItemWidth(GameHook::inputItemWidth);
    ImGui::InputScalar("Current Stage ID", ImGuiDataType_S32, (int*)GameHook::areaJumpAddress, NULL, NULL, "%-8X", ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("stageID", ImGuiDataType_S32, &stageID, &step, NULL, "%-8X");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    static int selectedIndex = 0;
    for (int i = 0; i < IM_ARRAYSIZE(areaIDNames); i++) {
        if (areaIDNames[i].ID == stageID) {
            selectedIndex = i;
            break;
        }
    }
    const char* preview = areaIDNames[selectedIndex].name;
    // ImGui::SetNextItemWidth(-FLT_MIN);
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
    GameHook::help_marker("There are missing entries here - some chapters have multiple stages and I only quickly loaded into each. For that reason I've left the manual input box for now.");
    ImGui::PushItemWidth(GameHook::inputItemWidth);

    int displayStagePart = stagePart + 1;
    if (ImGui::InputInt("Part", &displayStagePart, step)) {
        if (displayStagePart < 1) { displayStagePart = 1; };
        stagePart = displayStagePart - 1;
    }

    ImGui::InputInt("Spawn", &spawn, step);
    GameHook::help_marker("Not sure what this does other than change which Alfheim you get in B00");
    ImGui::PopItemWidth();
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
    {
        if (ImGui::Checkbox("Force Costume##Glamour", &GameHook::forceCostume)) {
            GameHook::randomizeCostume_toggle = false;
        }
        if (GameHook::forceCostume) {
            ImGui::Indent();
            ImGui::SetNextItemWidth(GameHook::inputItemWidth);
            if (ImGui::Combo("Costume##GlamourCombo", &GameHook::tempCostume, GameHook::costumeNames, IM_ARRAYSIZE(GameHook::costumeNames))) {
                *(int*)GameHook::currentCostumeAddress = GameHook::tempCostume;
            }
            ImGui::Unindent();
        }
        if (ImGui::Checkbox("Randomize Costume", &GameHook::randomizeCostume_toggle)) {
            GameHook::forceCostume = false;
        }
        GameHook::help_marker("Randomize the player's costume every load screen");
    }

    {
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
    }
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


    if (ImGui::Button("Save config")) {
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

            if (ImGui::Checkbox("Deal No Damage (F1)##DealNoDamageToggle", &GameHook::enemyHPNoDamage_toggle)) {
                GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
                if (GameHook::enemyHPNoDamage_toggle) {
                    GameHook::enemyHPOneHitKill_toggle = false;
                }
            }
            help_marker("Deal no damage to enemies");
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Take No Damage (F2)", &GameHook::damageReceivedMultiplierNoDamage_toggle);
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

            if (ImGui::Checkbox("One Hit Kill (F3)##OneHitKillToggle", &GameHook::enemyHPOneHitKill_toggle)) {
                if (GameHook::enemyHPOneHitKill_toggle) {
                    GameHook::enemyHPNoDamage_toggle = false;
                    GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
                }
            }
            help_marker("Kill enemies in one hit");

            ImGui::SeparatorText("Difficulty");

            ImGui::BeginGroup();
            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Difficulty", &difficultyValue, "Very Easy\0Easy\0Normal\0Hard\0Non-Stop Infinite Climax\0");
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
            if (ImGui::Checkbox("Get More Halos", &GameHook::getMoreHalos_toggle)) {
                GameHook::GetMoreHalos(GameHook::getMoreHalos_toggle);
            }
            help_marker("Pick up Halos from further away");

            if (ImGui::Checkbox("Freeze Timers", &GameHook::freezeTimer_toggle)) {
                GameHook::FreezeTimer(GameHook::freezeTimer_toggle);
            }
            help_marker("Freeze Alfheim timers");
            ImGui::SameLine(sameLineWidth);
            ImGui::Checkbox("Easier Mashing##EasierMashToggle", &GameHook::easierMash_toggle);
            help_marker("Make mash QTEs more reasonable");

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

            ImGui::Checkbox("Skip Angel Attack", &GameHook::loadReplace_toggle);
            help_marker("Load Mission Select instead of Angel Attack");

            ImGui::SameLine(sameLineWidth);

            if (ImGui::Checkbox("Auto Complete QTEs", &GameHook::autoQTE_toggle)) {
                GameHook::AutoQTE(GameHook::autoQTE_toggle);
            }
            help_marker("Does not auto complete torture attacks (because then you'd do it on every enemy you stand next to)");

			//ImGui::SameLine(sameLineWidth);
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
            
            ImGui::SeparatorText("Character");

            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Character##Combo", &currentCharacterValue, "Bayonetta\0Jeanne\0Little King Zero\0");
            help_marker("Set while in costume select\nSets character specific mechanics, e.g. if you have a dodge cap\n"
                "If your game freezes at the end of a fight, flick the value back to default");
            ImGui::SameLine(sameLineWidth);
            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Costume##Combo", (int*)GameHook::currentCostumeAddress, GameHook::costumeNames, IM_ARRAYSIZE(GameHook::costumeNames));
            help_marker("Set while in mission select\n");

            ImGui::SetNextItemWidth(inputItemWidth);
            ImGui::Combo("Third Accessory", &GameHook::desiredThirdAccessory, GameHook::accessoryNames, IM_ARRAYSIZE(GameHook::accessoryNames));
            help_marker("Select your third accessory");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Force Summoning Clothes (F6)##LessClothesToggle", &GameHook::lessClothes_toggle)) {
                GameHook::LessClothes(GameHook::lessClothes_toggle);
            }
            help_marker("Only works on outfits that have this function");

            DrawAreaJump();

            DrawAngelSlayer();

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
            help_marker("Disable the bounce that happens when you divekick into a wall, or into an enemy while not holding kick");
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

            ImGui::SeparatorText("Cheats");

            if (ImGui::Checkbox("Infinite Jumps (F4)##InfJumpsToggle", &GameHook::infJumps_toggle)) {
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
                ImGui::InputFloat("##WitchTimeMultiplier", &GameHook::witchTimeMultiplier, 0, 0, "%.1f");
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
            if (ImGui::Checkbox("NoClip (F5)", &GameHook::noClip_toggle)) {
                GameHook::NoClip(GameHook::noClip_toggle);
            }
            help_marker("Allow every entity to ignore walls and floors");

            ImGui::Checkbox("Save/Load Animation Hotkeys", &GameHook::saveStatesHotkeys_toggle);
            help_marker("Enable/Disable the HOME and END enemy save state hotkeys");
            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Easy Cutscene Skip", &GameHook::easyCutsceneSkip_toggle)) {
                GameHook::EasyCutsceneSkip(GameHook::easyCutsceneSkip_toggle);
            }
            help_marker("Move cutscene skip (R2+Select) to X");

            if (ImGui::Checkbox("60 FPS Cutscenes", &GameHook::sixtyFpsCutscenes_toggle)) {
                GameHook::SixtyFpsCutscenes(GameHook::sixtyFpsCutscenes_toggle);
            }
            help_marker("Cutscenes play at 60fps instead of 30");

            ImGui::SameLine(sameLineWidth);
            if (ImGui::Checkbox("Disable Gradient", &GameHook::disableGradient_toggle)) {
                GameHook::DisableGradient(GameHook::disableGradient_toggle);
            }
            help_marker("Disable the gradient covering the game");

            if (ImGui::Checkbox("Disable Tutorials", &disableTutorials_toggle)) {
                GameHook::DisableTutorials(disableTutorials_toggle);
            }

            ImGui::SameLine(sameLineWidth);

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

			ImGui::SeparatorText("BayoHook");

            ImGui::Checkbox("Show Hotkey Messages", &GameHook::showMessages_toggle);
            help_marker("Show text in the corner of the screen when a hotkey is activated");
			ImGui::SameLine(sameLineWidth);

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
			ImGui::Checkbox("Draw Flying Stats (WIP)", &GameHook::drawFlyingStats_toggle);
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

            ImGui::Checkbox("Combo Maker", &GameHook::comboMaker_toggle);
            help_marker("Compare your moveid and distance into current string to set a new string ID");
            if (GameHook::comboMaker_toggle) {
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

            ImGui::Checkbox("Weave Swaps", &GameHook::customWeave_toggle);
            help_marker("Replace one weave with another");
            if (GameHook::customWeave_toggle) {
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

            if (ImGui::Checkbox("Multiplayer Patch", &GameHook::multiplayerPatch_toggle)) {
                GameHook::MultiplayerPatch(GameHook::multiplayerPatch_toggle);
            }
            help_marker("This is very hacky and probably breaks a lot. This is intended to stop the camera jumping between multiple spawned player characters");

            // entity spawn stuff
            {
                struct EnemyInfo {
                    const char* name;
                    int id;
                };

                static const EnemyInfo knownEntities[] = {
                    {"", 0x0},
                    {"", 0x4},
                    {"", 0x6},
                    {"", 0x12C},
                    {"Bayonetta", 0x10000},
                    {"", 0x10001},
                    {"", 0x10002},
                    {"", 0x10005},
                    {"", 0x10008},
                    {"", 0x10010},
                    {"Chain VFX", 0x10012},
                    {"Summoning Hair", 0x10013},
                    {"Hood Hair", 0x1001A},
                    {"", 0x10021},
                    {"Nude Bayonetta", 0x10022},
                    {"Hood Hair", 0x10031},
                    {"", 0x10033},
                    {"Babynetta T-pose", 0x10035},
                    {"Babyjeanne T-pose", 0x10036},
                    {"Teddy", 0x10037},
                    {"", 0x10043},
                    {"Babynetta", 0x10045},
                    {"Dead Bayonetta", 0x10046},
                    {"Reclaimer Reference", 0x10048},
                    {"Jeanne Arm Hair", 0x1004C},
                    {"Nude Jeanne", 0x1004E},
                    {"", 0x10100},
                    {"Invisible dude", 0x10101},
                    {"Basic enemy dude", 0x20000},
                    {"?", 0x2000E},
                    {"?", 0x20010},
                    {"", 0x20011},
                    {"", 0x20013},
                    {"Snake Enemy", 0x20020},
                    {"Flying Snake Enemy", 0x20022},
                    {"", 0x2002F},
                    {"", 0x2004F},
                    {"", 0x2005F},
                    {"Ray Enemy", 0x20060},
                    {"", 0x20070},
                    {"", 0x20071},
                    {"Big Boss Enemy", 0x20078},
                    {"", 0x2007C},
                    {"", 0x2007D},
                    {"", 0x2007E},
                    {"Joy Enemy", 0x20080},
                    {"", 0x2008F},
                    {"Cube Dragon Prop Vertical", 0x20091},
                    {"Cube Dragon Prop Horizontal", 0x20092},
                    {"", 0x20093},
                    {"Cube Dragon Prop", 0x20094},
                    {"Cube Prop Small", 0x20095},
                    {"Boat Enemy", 0x200A0},
                    {"Boat Grabber Prop", 0x200A1},
                    {"Boat Missile", 0x200A2},
                    {"Boat Grabber", 0x200A3},
                    {"Dragon heads boss", 0x200B0},
                    {"Boss Face prop", 0x200B1},
                    {"Detached Dragon head", 0x200B2},
                    {"Detached Dragon head 2", 0x200B3},
                    {"Detached Wings", 0x200B4},
                    {"Detached Spot", 0x200B7},
                    {"Another Big Boss Enemy", 0x200C0},
                    {"Detached Swinging Something", 0x200C1},
                    {"Detached Swinging Something 2", 0x200C2},
                    {"Detached Boss Head", 0x200C4},
                    {"", 0x200C5},
                    {"Plant", 0x200D1},
                    {"Tentacle grower thing", 0x200D2},
                    {"Tentacle thing", 0x200D3},
                    {"Boss head with halo", 0x200D5},
                    {"Huge flying boss enemy", 0x20100},
                    {"its a head", 0x20101},
                    {"its a dragon head", 0x20102},
                    {"its a different dragon head", 0x20103},
                    {"its a wings", 0x20104},
                    {"", 0x20105},
                    {"single hit from underground", 0x20106},
                    {"its a mine", 0x20107},
                    {"BigBoss", 0x20200},
                    {"its them swinging things again", 0x20201},
                    {"there are so many swinging things", 0x20202},
                    {"and look another head didn't see that coming", 0x20204},
                    {"huge body of a boss", 0x20205},
                    {"", 0x20206},
                    {"", 0x20208},
                    {"Wind that hurts", 0x20209},
                    {"", 0x2020A},
                    {"Single electric stabby attack", 0x2020B},
                    {"Orb that spawns electric stabby attacks that cant be killed", 0x2020C},
                    {"Big huge tentacly boss enemy", 0x2020D},
                    {"Feather man", 0x20500},
                    {"Bayo Pistol", 0x30000},
                    {"Bayo Shotty", 0x30001},
                    {"Bayo Claw", 0x30002},
                    {"", 0x30003},
                    {"Bayo Rocket Launcher", 0x30004},
                    {"Bayo Skates", 0x30005},
                    {"Bayo Sword", 0x30009},
                    {"Bayo Sheath", 0x3000A},
                    {"Bayo Whip", 0x3000B},
                    {"", 0x3000C},
                    {"Bayo Skirt", 0x3000D},
                    {"Bayo Witch Attire", 0x3000E},
                    {"Bayo Devil Cat", 0x3000F},
                    {"Bayo Sunglasses Hat", 0x30010},
                    {"Bayo Sports", 0x30011},
                    {"Jeanne Pistol", 0x30020},
                    {"Jeanne Sword probably", 0x30022},
                    {"Pistol", 0x30030},
                    {"Spear", 0x30101},
                    {"Trumpet", 0x30103},
                    {"Leafy/feathered greatsword", 0x30105},
                    {"Sword whip bow", 0x30106},
                    {"Sword whip", 0x30108},
                    {"Boomerang Scythe", 0x30150},
                    {"Blue Claws", 0x30127},
                    {"Red Claws", 0x30160},
                    {"Red Claws", 0x30161},
                    {"?", 0x30162},
                    {"White Claws", 0x30163},
                    {"White Claw", 0x30164},
                    {"Black Claws", 0x30165},
                    {"Black Claw", 0x30166},
                    {"Enemy Halo", 0x30200},
                    {"Signboard", 0x4002F},
                    {"?", 0x50114},
                    {"Lamppost weapon", 0x50189},
                    {"low poly dude hitting the floor", 0x501C4},
                    {"?", 0x50228},
                    {"?", 0x50229},
                    {"?", 0x60000},
                    {"?", 0x60001},
                    {"Summon Hair Claw", 0x60007},
                    {"I didn't see anything spawn", 0x60011},
                    {"Butterfly", 0x60015},
                    {"?", 0x60017},
                    {"Floor Claw plant thing", 0x60069},
                    {"Skybox maybe?", 0x600F4},
                    {"Big collision", 0x60206},
                    {"?", 0x61000},
                    {"Should be an enemy but nothing spawns in void", 0x70000},
                    {"?", 0x80000},
                    {"Halo", 0x90000},
                    {"Health Pickup", 0x90010},
                    {"Still Crash", 0xA051F},
                    {"Crash still", 0xA0521},
                    {"?", 0xA0523},
                    {"T-Pose Bayo", 0xA0000},
                    {"Barrel", 0xC0301},
                    {"?", 0xF0000},
                };

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
                {
                    static int selectedEnemy = 28;

                    if (ImGui::CollapsingHeader("Manual Spawn Settings")) {

                        if (ImGui::Combo("Known Entity IDs", &selectedEnemy, displayNames, knownEntityCount)) {
                            GameHook::guiEntitySpawn.entityID = knownEntities[selectedEnemy].id;
                        }
                        ImGui::SameLine();
                        help_marker("This just autofills the next field if you want to pick from a dictionary of IDs we already know");
                        ImGui::PushItemWidth(inputItemWidth);
                        ImGui::InputScalar("ID", ImGuiDataType_S32, &guiEntitySpawn.entityID, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::SameLine();
                        help_marker("This is for typing in a manual ID. You will crash if you type in an invalid ID");
                        ImGui::InputScalar("arg2.int_0", ImGuiDataType_S32, &guiEntitySpawn.settings.int_0, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("arg2.int_4_Variant", ImGuiDataType_S32, &guiEntitySpawn.settings.int_4_Variant, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("arg2.int_8_SpawnAnim", ImGuiDataType_S32, &guiEntitySpawn.settings.int_8_SpawnAnim, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("arg2.int_C", ImGuiDataType_S32, &guiEntitySpawn.settings.int_C, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("arg2.int_10", ImGuiDataType_S32, &guiEntitySpawn.settings.int_10, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputFloat("arg2.float_14_RotX", &guiEntitySpawn.settings.float_14_RotX);
                        ImGui::InputFloat("arg2.float_18_RotY", &guiEntitySpawn.settings.float_18_RotY);
                        ImGui::InputFloat("arg2.float_1C_RotZ", &guiEntitySpawn.settings.float_1C_RotZ);
                        ImGui::InputScalar("arg2.int_20", ImGuiDataType_S32, &guiEntitySpawn.settings.int_20, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
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
                        ImGui::InputFloat("arg2.float_70_X", &guiEntitySpawn.settings.float_70_X);
                        ImGui::InputFloat("arg2.float_74_Y", &guiEntitySpawn.settings.float_74_Y);
                        ImGui::InputFloat("arg2.float_78_Z", &guiEntitySpawn.settings.float_78_Z);
                        ImGui::InputFloat("arg2.float_7C", &guiEntitySpawn.settings.float_7C);
                        ImGui::InputInt("arg2.int_80", &guiEntitySpawn.settings.int_80);
                        ImGui::InputScalar("arg2.int_84", ImGuiDataType_S32, &guiEntitySpawn.settings.int_84, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("arg2.int_88", ImGuiDataType_S32, &guiEntitySpawn.settings.int_88, 0, 0, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputFloat("arg2.float_8C", &guiEntitySpawn.settings.float_8C);
                        ImGui::InputFloat("arg2.float_90", &guiEntitySpawn.settings.float_90);
                        ImGui::InputFloat("arg2.float_94", &guiEntitySpawn.settings.float_94);
                        ImGui::InputText("arg2.string_98", guiEntitySpawn.settings.string_98, sizeof(guiEntitySpawn.settings.string_98));
                        ImGui::InputScalar("arg2.char_9f", ImGuiDataType_U8, &guiEntitySpawn.settings.char_9f);
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
                    else {
                        if (ImGui::Combo("ID##Easy", &selectedEnemy, displayNames, knownEntityCount)) {
                            GameHook::guiEntitySpawn.entityID = knownEntities[selectedEnemy].id;
                        }
                        static int step = 1;
                        ImGui::PushItemWidth(inputItemWidth);
                        ImGui::InputScalar("Variant##Easy", ImGuiDataType_S32, &guiEntitySpawn.settings.int_4_Variant, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::InputScalar("Spawn Anim##Easy", ImGuiDataType_S32, &guiEntitySpawn.settings.int_8_SpawnAnim, &step, &step, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
                        ImGui::PopItemWidth();
                        if (ImGui::Button("Easy Spawn##Easy")) {
                            GameHook::EasySpawnEntityFromGui(guiEntitySpawn.entityID, guiEntitySpawn.settings.int_4_Variant, guiEntitySpawn.settings.int_8_SpawnAnim);
                        }
                    }
                }
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
                ImGui::Combo("##WeaponA1InputInt", &weaponA1Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Combo("##WeaponA2InputInt", &weaponA2Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Text("Weapon Set B:");
                ImGui::Combo("##WeaponB1InputInt", &weaponB1Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
                ImGui::Combo("##WeaponB2InputInt", &weaponB2Value, GameHook::weaponNames, IM_ARRAYSIZE(GameHook::weaponNames));
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
                    ImGui::InputInt("HP##PlayerHPInputInt", &player->hp, 10, 100);
                    ImGui::InputInt("HPDamage##PlayerHPDamageInputInt", &player->hpDamage, 10, 100);
                    ImGui::InputFloat("MP##PlayerMPInputFloat", &playerMagicValue, 1, 100, "%.0f");
                    ImGui::InputFloat("Remaining Witch Time Duration##PlayerRemainingWitchTimeDurationInputFloat", &player->witchTimeDuration, 10, 100, "%.0f");
                    ImGui::InputFloat("Remaining Invinciblity##PlayerRemainingInvinciblityInputFloat", &player->iFramesRemaining, 10, 100, "%.0f");
                    ImGui::InputFloat("Animation Frame##PlayerAnimationFrameInputFloat", &player->animFrame, 1, 10, "%.0f");
                    //ImGui::InputInt("Move ID##PlayerMoveIDInputInt", &player->moveID);
                    ImGui::SetNextItemWidth(inputItemWidth * 3.0f);
                    ImGui::Combo("Move ID##PlayerMoveIDCombo", &player->moveID, GameHook::moveIDNames, IM_ARRAYSIZE(GameHook::moveIDNames));
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
                    ImGui::InputFloat("+4C4 speed", &player->speed);
                    ImGui::InputInt("+69C aerial", &player->aerial);
                    ImGui::InputInt("+6B4 hpDamage", &player->hpDamage, 10, 100);
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

        if (ImGui::BeginTabItem("Info")) {
            ImGui::BeginChild("InfoChild");

            ImGui::SeparatorText("Hotkeys");

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

            ImGui::Text("LCtrl+ F1 = Spawn 1");
            ImGui::Text("LCtrl+ F2 = Spawn 2");
            ImGui::Text("LCtrl+ F3 = Spawn 3");
            ImGui::Text("LCtrl+ F4 = Spawn 4");
            ImGui::Text("LCtrl+ F5 = Spawn 5");
            ImGui::Text("LCtrl+ F6 = Spawn 6");
            ImGui::Text("LCtrl+ F7 = Spawn 7");
            ImGui::Text("LCtrl+ F8 = Spawn 8");
            ImGui::Text("LCtrl+ F9 = Spawn 9");
            ImGui::Text("LCtrl+ F10 = Spawn 10");
            ImGui::Text("LCtrl+ F11 = Spawn 11");
            ImGui::Text("LCtrl+ F12 = Spawn 12");

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
