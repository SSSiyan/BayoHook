#pragma once
#include <cstdint> // uintptr_t
#include "libmem++/libmem.hpp" // unique_ptr
#include "../utils/FunctionHook.hpp"

struct HookContext {
    std::unique_ptr<FunctionHook> hook = nullptr;
    uintptr_t jmp_ret = NULL;
};  

struct Vec3 {
    float x; // 0x0
    float y; // 0x4
    float z; // 0x8

    Vec3 operator+(const Vec3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vec3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }

    Vec3 operator/(float scalar) const {
        return { x / scalar, y / scalar, z / scalar };
    }

    Vec3& operator+=(const Vec3& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vec3& operator*=(float scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vec3& operator/=(float scalar) {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }
};

struct Matrix4x4 {
    float m[4][4];

    Matrix4x4() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
};

struct Matrix3x3 {
    float m[3][3];

    static Matrix3x3 Identity() {
        Matrix3x3 mat = {};
        mat.m[0][0] = 1.0f; mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f;
        mat.m[1][0] = 0.0f; mat.m[1][1] = 1.0f; mat.m[1][2] = 0.0f;
        mat.m[2][0] = 0.0f; mat.m[2][1] = 0.0f; mat.m[2][2] = 1.0f;
        return mat;
    }
};

#pragma pack(push, 1)
enum PlayerForm {
    Player = 0,
    Panther = 1,
    FirstPerson = 2,
    Bird = 3,
};
#pragma pack(pop)

#pragma pack(push, 1)
struct LaserSword {
    char pad_0[0x6cc];
    float buffDrainRate; // 0x6cc
    char pad_6d0[0x2c5c];
    float buffRemainingDuration; // 0x332c
    float length; // 0x3330
}; // Size: 0x3334
#pragma pack(pop)
static_assert(sizeof(LaserSword) == 0x3334);

#pragma pack(push, 1)
struct WickedWeave {
    char pad_0[0xf0];
    Vec3 scale; // 0xf0
}; // Size: 0xfc
#pragma pack(pop)
static_assert(sizeof(WickedWeave) == 0xfc);

#pragma pack(push, 1)
struct BayoLimb {
    char pad_0[0x74];
    bool isShooting; // 0x74
    char pad_75[0x11a];
    bool endOfStruct; // 0x18f
}; // Size: 0x190
#pragma pack(pop)
static_assert(sizeof(BayoLimb) == 0x190);

#pragma pack(push, 1)
struct BayoBone {
    char pad_0[0x30];      // 0x00
    Vec3 pos;              // 0x30
    char pad_3C[0x84];     // 0x3C
    Vec3 offset;           // 0xC0
    char pad_CC[0x14];     // 0xCC
    Vec3 scale;            // 0xE0
    char pad_EC[0x1C];     // 0xEC
    int boneID;            // 0x108
    int unknID;            // 0x10C
    BayoBone* prevBone;    // 0x110
    BayoBone* nextBone;    // 0x114
}; // Size: 0x118
#pragma pack(pop)
static_assert(sizeof(BayoBone) == 0x118);

#pragma pack(push, 1)
struct hitbox { // this is the seq files
    char pad_0x0[0x30];
    Vec3 pos; // 0x30
    // 0x28 = when it starts?
    // 0x2C = when it ends?
    char pad_0x3C[0x4];
    char pad_0x40[0x10];
    float pad_0x50;
    float pad_0x54;
    float scale; // 0x58
    float pad_0x5C;
}; // Size: 0x60
#pragma pack(pop)
static_assert(sizeof(hitbox) == 0x60);

#pragma pack(push, 1)
struct Enemy {
    char pad_0[0xd0];
    Vec3 pos; // 0xd0
    char pad_dc[0x270];
    int moveID; // 0x34c
    char pad_350[0x20];
    int id; // 0x370
    int eBeFlag; // 0x374
    char pad_378[0x6C];
    float animFrame; // 0x3e4
    char pad_3e8[0x2cc];
    int hp; // 0x6b4
    int hpOld; // 0x6b8
    int hpMax; // 0x6bc
    int hpMaxOld; // 0x6c0
    char pad_6c4[0x5d0];
    float daze; // 0xc94
    float dazeMax; // 0xc98
    float dazeCurrentDuration; // 0xc9c
    float dazeMaxDurationProbably; // 0xca0
}; // Size: 0xca4
#pragma pack(pop)
static_assert(sizeof(Enemy) == 0xca4);

#pragma pack(push, 1)
struct LocalPlayer {
    uintptr_t vtable; // 0x0
    char pad_4[0xcc];
    Vec3 pos; // 0xd0
    char pad_dc[0x4];
    Vec3 rot; // 0xe0
    char pad_ec[0x4];
    Vec3 scale; // 0xf0
    char pad_fc[0x218];
    float camHeight; // 0x314
    char pad_318[0xc];
    float alpha; // 0x324
    char pad_328[0x24];
    int moveID; // 0x34c
    int movePart; // 0x350
    int invincibility; // 0x354
    int controllerNum; // 0x358
    char pad_35C[0x14]; // 0x35C
    int entityId; // 0x370
    unsigned int beFlag; // 0x374 
    unsigned int aliveFlag; // 0x378
    char pad_37C[0x68]; // 0x37C
    float animFrame; // 0x3E4
    char pad_3e8[0x3C];
    float animFrameMax; // 0x424
    char pad_428[0x9C];
    float speed; // 0x4C4
    char pad_4c8[0x1D4];   // 0x4C8
    int aerial;            // 0x69C
    char pad_6a0[0x14];
    int hp; // 0x6b4
    int hpOld; // 0x6b8
    int hpMax; // 0x6bc
    char pad_6c0[0xC];
    float slowmo; // 0x6cc
    char pad_6d0[0x60];
    float iFramesRemaining; // 0x730
    char pad_734[0x58c];
    Vec3 colouredHairDurationRGB; // 0xcc0
    float colouredHairTimer; // 0xccc
    char pad_cd0[0x4ef0];
    LaserSword* laserSword; // 0x5bc0
    char pad_5bc4[0x8c688];
    BayoBone* bayoSkeleton; // 0x9224c
    char pad_92250[0xeb4];
    bool clip; // 0x93104
    char pad_93105[0x403];
    int hpUnk; // 0x93508
    char pad_9350c[0x10];
    float birdTimer; // 0x9351c
    char pad_93520[0x58];
    int wallJumpCount; // 0x93578
    char pad_9357c[0x10];
    float divekickCount2; // 0x9358c
    char pad_93590[0x54];
    int m_JoySpinCnt; // 0x935e4
    char pad_935e8[0x128];
    uintptr_t summoningHair; // 0x93710
    uintptr_t summoningBody; // 0x93714
    char pad_93718[0xa8];
    WickedWeave* handWeave; // 0x937c0
    WickedWeave* idkWeave1; // 0x937c4
    WickedWeave* idkWeave2; // 0x937c8
    WickedWeave* idkWeave3; // 0x937cc
    WickedWeave* legWeave; // 0x937d0
    char pad_937d4[0x180];
    Enemy* softLockEnemy; // 0x93954
    char pad_93958[0xAC];
    float m_RhythmTimer; // 0x93a04
    char pad_93a08[0x8];
    int m_bRhythmActionSuccess; // 0x93a10
    char pad_93a14[0x8];
    int m_RapidType; // 0x93a1c
    float m_RapidActRate; // 0x93a20
    float m_RapidActMinusTimer; // 0x93a24
    float m_RapidActMinusWait; // 0x93a28
    float m_RapidActMinusTimer2; // 0x93a2c
    char pad_93a30[0x90];
    BayoLimb rightHand; // 0x93ac0
    BayoLimb leftHand; // 0x93c50
    BayoLimb rightLeg; // 0x93de0
    BayoLimb leftLeg; // 0x93f70
    char pad_94100[0x694];
    int dodgeCount; // 0x94794
    char pad_94798[0xe0];
    float batWithinFrames; // 0x94878
    char pad_9487c[0x214];
    int clothesRelated3; // 0x94a90
    int clothesRelated2; // 0x94a94
    char pad_94a98[0xac];
    int inputsHold; // 0x94b44
    int inputsDown; // 0x94b48
    int inputsUp; // 0x94b4c
    char pad_94b50[0xb0];
    int hideEverythingInCutscene; // 0x94c00
    char pad_94c04[0x1060];
    int stringID; // 0x95c64 // ID_COMBO_TYPE enum
    char pad_95c68[0x18];
    float comboTimer; // 0x95c80
    char pad_95c84[0x8];
    bool isWhipSlap; // 0x95c8c
    char pad_95c8d[0x7];
    int comboHit[7]; // 0x95c94
    char pad_95cb0[0xc];
    int attackCount; // 0x95cbc
    char pad_95cc0[0x9c];
    float witchTimeDuration; // 0x95d5c
    float witchTimeMaxProbably; // 0x95d60
    char pad_95d64[0x24];
    int qteThing; // 0x95d88
    char pad_95d8c[0x148];
    bool walkOnWalls; // 0x95ed4
    char pad_95ed5[0x33];
    int clothesRelated4; // 0x95f08
    char pad_95f0c[0xc];
    int walkOnWallsEffect; // 0x95f18
    char pad_95f1c[0xa8];
    int walkOnWallsRelated; // 0x95fc4
    char pad_95fc8[0x368];
    int clothesTransformation; // 0x96330
    float clothesTransformationTimer; // 0x96334
    int cutsceneToggleMaybe; // 0x96338
    char pad_9633c[0x294];
    int facePlate; // 0x965d0
    char pad_965d4[0x550];
    PlayerForm form; // 0x96b24
    char pad_96b28[0xc];
    int enemyCount; // 0x96b34
    int clothesColourRGB; // 0x96b38
    char pad_96b3c[0xc4];
    Vec3 colouredHairIntensityRGB; // 0x96c00
}; // Size: 0x96c0c
#pragma pack(pop)
static_assert(sizeof(LocalPlayer) == 0x96c0c);

struct EntitySpawnArg2 {
    int int_0 = 0;                // 0x0
    int int_4_Variant = 0;        // 0x4
    int int_8_SpawnModifier = 0;  // 0x8
    int int_C = 0;                // 0xC has been 0x8000
    int int_10 = 0x20000;         // 0x10 has been 1
    float float_14_RotX = 0.0f;   // 0x14
    float float_18_RotY = 0.0f;   // 0x18
    float float_1C_RotZ = 0.0f;   // 0x1C
    int int_20 = -1;              // 0x20
    float float_24 = 1.0f;        // 0x24 CONFIRMED FLOAT
    float float_28 = 1.0f;        // 0x28 CONFIRMED FLOAT
    float float_2C = 1.0f;        // 0x2C CONFIRMED FLOAT
    float float_30_ScaleX = 1.0f; // 0x30
    float float_34 = 0.0f;        // 0x34
    float float_38 = 0.0f;        // 0x38
    float float_3C = 0.0f;        // 0x3C
    float float_40 = 0.0f;        // 0x40
    float float_44_ScaleY = 1.0f; // 0x44
    float float_48 = 0.0f;        // 0x48 scale stuff
    float float_4C = 0.0f;        // 0x4C scale stuff
    float float_50 = 0.0f;        // 0x50 scale stuff
    float float_54 = 0.0f;        // 0x54 some rotation stuff?
    float float_58_ScaleZ = 1.0f; // 0x58
    float float_5C = 0.0f;        // 0x5C some rotation stuff?
    float float_60 = 0.0f;        // 0x60 some rotation stuff?
    float float_64 = 0.0f;        // 0x64 some rotation stuff?
    float float_68 = 0.0f;        // 0x68 some rotation stuff?
    float float_6C = 1.0f;        // 0x6C CONFIRMED FLOAT
    float float_70_X = 0.0f;      // 0x70
    float float_74_Y = 0.0f;      // 0x74
    float float_78_Z = 0.0f;      // 0x78
    float float_7C = 1.0f;        // 0x7C
    int int_80 = 0xFF0000;        // 0x80
    int int_84 = 0x588C0000;      // 0x84
    int int_88 = -1;              // 0x88 // confirmed int
    float float_8C = 0.0f;        // 0x8C
    float float_90 = 0.0f;        // 0x90
    float float_94 = 0.0f;        // 0x94
    char string_98[6] = "e.dat";  // 0x98 // 5 + terminator, sometimes a string. struct has probably ended by here
    char char_9f = 0;             // 0x9F
    float float_A0 = 1.0f;        // 0xA0
    char pad_A4[0x20*4]{};        // 0xA4
};

struct HitboxSnapshot {
    Vec3 pos;
    float radius;
};

struct AreaIDName {
    int ID;
    const char* name;
};

static AreaIDName areaIDNames[] = {
    { 0x0, "Start Screen" },
    { 0xa10, "Chapter Menu" },
    { 0x1a1, "RT - The Witch Hunts" },
    { 0x1c1, "P - Vestibule" },
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
    { 0xB00, "LC - Angel Slayer (Spawn changes Alfheim)" },
    { 0xC00, "Angel Attack" },
    { 0xF01, "The Gates of Hell (Set Spawn to 1/2 for Rodin)" },
};

static const char* costumeNames[32]{
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

static const char* weaponNames[19]{
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

static const char* weaveNames[37]{
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

static const char* accessoryNames[13]{
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

static const char* moveIDNames[466]{
    "0: Handguns Idle",
    "1: Handguns Lock On Stance",
    "2: Handguns Aim",
    "3: Handguns Slightly move forward",
    "4: Handguns Slightly move forward",
    "5: Handguns Slightly move forward",
    "6: Handguns Move",
    "7: Handguns Move backward",
    "8: Handguns Short Taunt",
    "9: Gravity change landing",
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
    "44: Jubileus child transformation (Idle)",
    "45: Jubileus child transformation (Walk)",
    "46: Jubileus child transformation (Run)",
    "47: Jubileus child transformation (Jump)",
    "48: Jubileus child transformation (Stumble)",
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
    "215: Rodin Angel Pole Attack",
    "216: Rodin Air Angel Pole Attack",
    "217: Rodin Angel Pole Spin QTE",
    "218: Rodin Sword",
    "219: Rodin Air Sword",
    "220: Rodin Sword Dash Forward",
    "221: Rodin Air Sword Dash Forward",
    "222: Rodin Angel Bow Melee Attack",
    "223: Rodin Air Angel Bow Melee Attack",
    "224: Rodin Angel Bow Shooting",
    "225: Rodin Flail Continuous Attack",
    "226: Rodin Air Flail Continuous Attack",
    "227: Rodin Flail Hard Attack",
    "228: Rodin Air Flail Hard Attack",
    "229: Rodin Axe Spin Attack",
    "230: Rodin Air Axe Spin Attack",
    "231: Rodin Claw Attack",
    "232: Rodin Claw Throw",
    "233: Rodin Electric Claw Charge",
    "234: Rodin Air Electric Claw Charge",
    "235: Rodin Fire Claw Charge",
    "236: Rodin Air Fire Claw Charge",
    "237: Rodin Trumpet shooting",
    "238: Rodin Trumpet heavy shooting",
    "239: Rodin French Horn Shooting",
    "240: Rodin French Horn Spin",
    "241: Rodin Uplift Sword",
    "242: Rodin Uplift Bow",
    "243: Rodin Chainsaw",
    "244: Rodin Air Chainsaw",
    "245: Angel Arms Pick Up",
    "246: Angel Arms Pole Attack",
    "247: Angel Arms Air Pole Attack",
    "248: Angel Arms Pole Spin",
    "249: Angel Arms Sword / Key",
    "250: Angel Arms Air Sword / Key",
    "251: Angel Arms Sword / Key Dash Forward",
    "252: Angel Arms Sword / Key Air Dash Forward",
    "253: Angel Arms Chainsaw",
    "254: Angel Arms Air Chainsaw",
    "255: Angel Arms Chainsaw Dash Forward",
    "256: Angel Arms Air Chainsaw Dash Forward",
    "257: Angel Arms Bow Melee Attack",
    "258: Angel Arms Air Bow Melee Attack",
    "259: Angel Arms Bow Shooting",
    "260: Angel Arms Flail Continuous Attack",
    "261: Angel Arms Air Flail Continuous Attack",
    "262: Angel Arms Flail Hard Attack",
    "263: Angel Arms Air Flail Hard Attack",
    "264: Angel Arms Axe Swing",
    "265: Angel Arms Air Axe Swing",
    "266: Angel Arms Axe Throw",
    "267: Angel Arms Axe Catch",
    "268: Angel Arms Claw Attack",
    "269: Angel Arms Claw Throw",
    "270: Angel Arms Electric Claw",
    "271: Angel Arms Air Electric Claw",
    "272: Angel Arms Fire Claw Spin",
    "273: Angel Arms Air Fire Claw Spin",
    "274: Angel Arms Steel Beam Throw",
    "275: GW_FIRE",
    "276: Angel Arms Trumpet shooting",
    "277: Angel Arms Trumpet heavy shooting",
    "278: Angel Arms French Horn Shooting",
    "279: Angel Arms French Horn Spin",
    "280: Angel Arms Lamp Post Swing",
    "281: Angel Arms Steel Beam Swing",
    "282: Affinity Air Grab Punish",
    "283: EM0010CATCH",
    "284: Enchant Spin Punish",
    "285: Grace and Glory Counter",
    "286: EM0040CATCHATK",
    "287: EM0050CATCHATK",
    "288: Unused Fairness and Fearless Torture Attack",
    "289: WARPATK",
    "290: COMBOATK",
    "291: COMBOBLADE",
    "292: COMBOKICK",
    "293: Decorations Panther Punt",
    "294: Prototype Affinity Torture Attack",
    "295: Iron Maiden Torture Attack",
    "296: Guillotine Torture Attack",
    "297: Tombstone Torture Attack",
    "298: Pulley Torture Attack",
    "299: EM0020SUMMON_A",
    "300: EM0020SUMMON_B",
    "301: Vice Torture Attack",
    "302: Wheel Torture Attack",
    "303: Chainsaw Torture Attack",
    "304: Gomorrah Beloved summon (Ch.2)",
    "305: EM0070SUMMON_B",
    "306: Wooden Horse Torture Attack",
    "307: Golem Climax Attack",
    "308: Fortitudo Right Head Punish",
    "309: Fortitudo Left Head Punish",
    "310: EM0100SUMMON_RH_MINI",
    "311: EM0100SUMMON_LH_MINI",
    "312: Fortitudo Climax Attack",
    "313: EM0200SUMMON_RH",
    "314: EM0200SUMMON_LH",
    "315: EM0200SUMMON_RH2",
    "316: EM0200SUMMON_LH2",
    "317: Temperantia Climax Attack",
    "318: GM0261TRAINTHROW",
    "319: Unused Affinity Torture Attack",
    "320: Unused Affinity Torture Attack",
    "321: Little Devils/Pulley's Butterfly Summon",
    "322: Affinity Witch Walk Chain Grab",
    "323: Affinity Witch Walk Chain Drop",
    "324: EM00C0ESCAPE",
    "325: EM00C0ESCAPEMISS",
    "326: Iustitia Face Kick",
    "327: Iustitia Tentacle Cut",
    "328: EM0300DROP",
    "329: EM0300COUNTER",
    "330: EM0300COUNTER2ND",
    "331: EM0300DROPHOLE",
    "332: EM0300DOWNWAIT",
    "333: Iustitia Climax Attack",
    "334: EM0400SUMMON_A",
    "335: EM0400SUMMON_B",
    "336: EM0400RIDEON",
    "337: Sapientia Climax Attack",
    "338: EM0600MAKEROAD",
    "339: EM0600MAKEROADSIGN",
    "340: EM0600HAIRBIND",
    "341: Jubileus Knockdown (After Clearing Element Phase)",
    "342: Jubileus Fire Phase",
    "343: Jubileus Water Phase",
    "344: Jubileus Wind Phase",
    "345: EM0600WINDHAZARD2ND",
    "346: EM0600LAVALASERWAIT",
    "347: Jubileus Climax Summon",
    "348: EM1000DEVILCOUNTER",
    "349: EM1000KICKCOUNTER",
    "350: Missile QTE counterattack vs Jeanne",
    "351: EM0500SATELLITELASER",
    "352: EM0500SATELLITEFALL",
    "353: EM0500SATELLITEFALLWAIT",
    "354: EM0500SATELLITECOUNTER",
    "355: EM0500SATELLITECRUSH",
    "356: Damage - Fail Father Balder satellite counter QTE",
    "357: EM0500BUILTHROW",
    "358: EM0500BUILCOUNTER",
    "359: Damage - Fail Father Balder building counter QTE",
    "360: EM0500FINISH",
    "361: Gomorrah summon vs Father Balder",
    "362: Scolopendra summon vs Father Balder",
    "363: EM00D0DROPKICK",
    "364: EM00D0CUT",
    "365: Jubileus rocket head Panther Punt",
    "366: Magic Flute",
    "367: Key turn",
    "368: Lever pull",
    "369: Rotating moon switch in The Lost Holy Grounds",
    "370: OPENDOOR",
    "371: ROCKJUMP",
    "372: ROCKCOUNTER",
    "373: ROCKPUSH",
    "374: POLESPIN",
    "375: Spinning Paradiso Golem gears",
    "376: Spinning Inthavoll Building gears",
    "377: CARCATCH",
    "378: Vigrid car lift",
    "379: Vigrid dumpster lift",
    "380: Frozen enemy lift",
    "381: Dumpster/car throw at Beloved",
    "382: Witch Time statue lift",
    "383: ET0024CATCH",
    "384: GM018DCATCH",
    "385: GM0020CATCH",
    "386: GM0051CATCH",
    "387: GM0139PLAYBACK",
    "388: SURF",
    "389: AIRPLANE",
    "390: Space Harrier missile ride",
    "391: HIGHWAYBIKE",
    "392: Jeanne vaulting off bike",
    "393: Jeanne vaulting off bike QTE fail",
    "394: Sapientia battle surfing idle",
    "395: Sapientia battle surfing",
    "396: EVT_KISS",
    "397: Cereza pickup",
    "398: Cereza put down",
    "399: Out-of-body on",
    "400: Out-of-body off",
    "401: GM022AOFF",
    "402: Guiding Jubileus to sun",
    "403: GOTO_SUN_DIE",
    "404: Ithavoll Building turret",
    "405: Game Over - Ithavoll Building turret death",
    "406: TURNPL0045",
    "407: SPEAKPL0045",
    "408: DM_DODGE",
    "409: DM_CANCELWAIT",
    "410: DM_REFLECT",
    "411: DM_QUAKE",
    "412: DM_GUARDIAN",
    "413: DM_SMALL",
    "414: DM_MIDDLE",
    "415: DM_UPPER",
    "416: DM_AIR",
    "417: DM_BLOW",
    "418: DM_BLOW_E",
    "419: DM_FALL",
    "420: Damage - Rolling Golem",
    "421: Damage - Fire/lava",
    "422: DM_ICE",
    "423: DM_MAGICFLOOR",
    "424: Damage - Bit by Decoration",
    "425: DM_CATCHBITE",
    "426: Damage - Grabbed by Beloved",
    "427: DM_EM00A3CATCH",
    "428: Damage - Father Balder electric sphere",
    "429: Damage - Fortitudo bite QTE fail",
    "430: DM_EM020ACATCH",
    "431: DM_EM0303CATCH",
    "432: DM_EM0400CATCHDIE",
    "433: DM_EM0400CATCH",
    "434: DM_EM1000CATCHKICK",
    "435: Damage - Tornado during Jubileus' wind phase",
    "436: Damage - Jubileus' black hole attack",
    "437: Damage - Jubileus' grab attack during final phase",
    "438: DM_EM0040_CLAW",
    "439: Flattened by Golem",
    "440: Staggered by roar",
    "441: DM_MUCUS",
    "442: DM_EM0200_SHAKE",
    "443: DM_EM0200_BLOW",
    "444: DM_EM0200_FLOOR",
    "445: EM0200BODYLANDING",
    "446: EM0200WEAKJUMP",
    "447: EM0200WEAKLANDING",
    "448: EM0200ON_ARM_LANDING",
    "449: DM_HIGHWAY_DROP",
    "450: DM_EM0510FINAL",
    "451: Game Over - Standard death",
    "452: DIE_DOWN",
    "453: DIE_CURSE",
    "454: Game Over - Lava wall in The Burning Ground",
    "455: DIE_PL0045",
    "456: Game Over - Swallowed by Sapientia",
    "457: Game Over - Iustitia climax QTE fail",
    "458: Game Over - Fall off highway",
    "459: Game Over - Fall off Jubileus rocket",
    "460: Game Over - Frozen in ice during Jubileus' water phase",
    "461: Game Over - Fail rescuing Cereza from impostor Joy",
    "462: Game Over - Dragged to Inferno",
    "463: SCE_RUN",
    "464: SCE_JUMP",
    "465: SCE_NONE",
};

struct EntityInfo {
    const char* name;
    int id;
};

static const EntityInfo allKnownEntities[] = {
	// 0x0 = sc (?) (unused), 0x1 = pl, 0x2 = em, 0x3 = wp, 0x4 = bg, 0x5 = gm, 0x6 = et, 0x7 = ef (unused), 0x8 = rp (?) (unused), 0x9 = it, 0xA = id, 0xB = es, 0xC = bm, 0xD = ic
    {"Player Bayonetta", 0x10000}, // v0 = Moves, v2 = Doesn't Move
    {"Player Bayonetta Panther Within", 0x10001},
    {"Player Bayonetta Crow Within", 0x10002},
    {"Player Jeanne Lynx Within", 0x10005},
    {"Player Jeanne Moth Within (Lesser Moths)", 0x10008},
    {"Player Bayonetta Crow Within Feather (w/Animations)", 0x10010},
    {"Chain VFX", 0x10012},
    {"Summoning Hair", 0x10013},
    {"Hood Hair (pl001a)", 0x1001A},
    {"Player Jeanne", 0x10020},
    {"Bayonetta Climax Weave Hair Spiral", 0x10021},
    {"Nude Bayonetta", 0x10022},
	{"Player Zero", 0x10023},
    {"Untextured Zero", 0x10024},
    {"Player Bayonetta P.E. A", 0x10025},
    {"Player Bayonetta P.E. B", 0x10026},
    {"Player Bayonetta P.E. C", 0x10027},
    {"Player Bayonetta d'Arc", 0x1002b},
    {"Player Bayonetta Umbra", 0x1002c},
    {"Player Bayonetta Various A", 0x1002d},
    {"Player Bayonetta Various B", 0x1002e},
    {"Player Bayonetta Various C", 0x1002f},
    {"Player Bayonetta Old", 0x10030},
    {"Hood Hair (pl0031)", 0x10031},
    {"Baby Bayonetta T-pose", 0x10035},
    {"Baby Jeanne T-pose", 0x10036},
    {"Charles", 0x10037},
    {"Enzo", 0x10040},
    {"Little Cereza", 0x10045},
    {"Dead Bayonetta", 0x10046},
    {"Luka Scarf", 0x10048},
    {"Rodin NPC (T-Pose)", 0x10049},
    {"Jeanne Sleeve Hair", 0x1004C},
    {"Nude Jeanne", 0x1004E},
    {"Detached Spot", 0x200B7},
    {"Player Jeanne P.E. A", 0x10061},
    {"Player Jeanne P.E. B", 0x10061},
    {"Player Jeanne P.E. C", 0x10062},
    {"Player Jeanne Formal B", 0x10064},
    {"Player Jeanne Old", 0x10066},
    {"Player Jeanne Umbra", 0x10067},
    {"Player Jeanne Various A", 0x10068},
    {"Player Jeanne Various B", 0x10069},
    {"Player Jeanne Various C", 0x1006A},
    {"Player Jeanne Komachi A", 0x1006E},
    {"Player Jeanne Komachi B", 0x10070},
    {"Player Jeanne Komachi C", 0x10072},
    {"Player Jeanne Nun", 0x10074},
    {"Player Jeanne Queen", 0x10075},
    {"Player Bayonetta Komachi A", 0x10083},
    {"Player Bayonetta Komachi B", 0x10085},
    {"Player Bayonetta Komachi C", 0x10087},
    {"Player Bayonetta Nun", 0x10089},
    {"Player Bayonetta Witch", 0x1008a},
    {"Vigrid Citizen (w/Resources)", 0x10100},
    {"Male Vigrid Citizen (Purgatorio)", 0x10101},// v0 = Short, v1 = Tall(No Hood), v2 = Tall(w / Hood), v3 = Short(No Hood)
    {"Affinity/Applaud", 0x20000},// Affinity: v1 = Spear, v2 = Trumpet, v8 = Hourglass, v9 = Mace, vA = Spear, vB = Trumpet, Applaud: v4 = Spear, v5 = Greatsword, v6 = Bow, v7 = Key, vC = No weapon / s3 = Lava surf
    {"Affinity (Spear) (Fire) / Ardor (Sword) (Fire)", 0x20001},
    {"Affinity (Laser)", 0x20002},
    {"Ardor", 0x20004}, // 0 = sword, 1 = axe, 2 = key
    {"Affinity/Applaud Invisible Base", 0x20006},
    {"Affinity (Axe) (Fire)", 0x20007},
    {"Affinity (Angel Attack)", 0x20008},
    {"Affinity (T-Pose)", 0x20009},
    {"Affinity Dummy Dat (w/Animations)", 0x2000E},
    {"Decoration", 0x20010},// v2 = Hourglass
    {"Dear", 0x20011},
    {"Dear & Decorations", 0x20012},
    {"Inspired (No HP Bar)", 0x20020},
    {"Inspired (Invisible)", 0x20021},
    {"Inspired (Green)", 0x20022},
    {"Inspired Dummy Dat (w/Animations)", 0x2002F},
    {"Enchant", 0x20030},
    {"Grace", 0x20040},
    {"Glory", 0x20041},
    {"Gracious", 0x20042},
    {"Glorious", 0x20043},
    {"Grace & Glory Dummy Dat (w/Animations)", 0x2004F},
    {"Fearless", 0x20050},
    {"Fairness", 0x20051},
    {"Fearless & Fairness Dummy Dat (w/Animations)", 0x2005F},
    {"Harmony", 0x20060},
    {"Beloved", 0x20070},
    {"Beloved (Larger)", 0x20071},
    {"Beloved (Invisible)", 0x20072},
    {"Brave", 0x20073},
    {"Beloved (Silver)", 0x20074},
    {"Beloved (Silver Invisible?)", 0x20076},
    {"Beloved w/Mask", 0x20078},
    {"Beloved Dummy Dat (w/Animations)", 0x2007C},
    {"Beloved Dummy Dat (w/Animations)", 0x2007D},
    {"Beloved Dummy Dat (w/Animations)", 0x2007E},
    {"Joy", 0x20080},
    {"Joy Dummy Dat (w/Animations)", 0x2008F},
    {"Golem", 0x20090},
    {"Golem Dragon (Vertical)", 0x20091},
    {"Golem Dragon (Horizontal)", 0x20092},
    {"Golem Bird", 0x20093},
    {"Golem Spider", 0x20094},
    {"Golem Centipede", 0x20095},
    {"Kinship", 0x200A0},
    {"Kinship Chain and Claws", 0x200A1},
    {"Kinship Missile", 0x200A2},
    {"Kinship Claw", 0x200A3},
    {"Fortitudo (Green)", 0x200B0},
    {"Fortitudo Face (Green)", 0x200B1},
    {"Fortitudo Head (Green)", 0x200B2},
    {"Fortitudo Head 2 (Green)", 0x200B3},
    {"Fortitudo Wings (Green)", 0x200B4},
    {"Fortitudo WeakSpot (Green)", 0x200B7},
    {"Temperantia", 0x200C0},
    {"Temperantia (Green)", 0x200C1},
    {"Temperantia 2 (Green)", 0x200C2},
    {"Temperantia Head (Green)", 0x200C4},
    {"Temperantia Arms (Green)", 0x200C5},
    {"Iustitia", 0x200D0},
    {"Iustitia Head", 0x200D1},
    {"Iustitia grower thing", 0x200D2},
    {"Iustitia Tentacle", 0x200D3},
    {"Iustitia Head w/Halo", 0x200D5},
    {"Sapentia (Vertical)", 0x200E0},
    {"Fortitudo", 0x20100},
    {"Fortitudo Head", 0x20101},
    {"Fortitudo Dragon Head (Red)", 0x20102},
    {"Fortitudo Dragon Head (Blue)", 0x20103},
    {"Fortitudo Wings", 0x20104},
    {"Fortitudo Dangling Chains", 0x20105},
    {"Fortitudo Tail", 0x20106},
    {"Fortitudo Head Gem", 0x20107},
    {"Temperantia 2", 0x20200},
    {"Temperantia Fingers 1", 0x20201},
    {"Temperantia Fingers 2", 0x20202},
    {"Temperantia Head 2", 0x20204},
    {"Temperantia Arms", 0x20205},
    {"Damaging Wind Serpent", 0x20209},
    {"Blue Electric Strikes", 0x2020B},
    {"Orb that Spawns Blue Electric Strikes", 0x2020C},
    {"Temperantia 3", 0x2020D},
    {"Sapentia", 0x20400},
    {"Balder", 0x20500},
    {"Father Rodin (Unkillable)", 0x20510},
    {"Jeanne Enemy Default", 0x21000},
    {"Jeanne Enemy Old", 0x21001},
    {"Jeanne Enemy Formal A", 0x21002},
    {"Bayo Enemy", 0x21003},
    {"Joy Fake (Unkillable)", 0x21010},
    {"Bayonetta Pistol", 0x30000},
    {"Bayonetta Onyx Rose", 0x30001},
    {"Bayonetta Durga (Fire)", 0x30002},
    {"Bayonetta Sai-Fung", 0x30003},
    {"Bayonetta Lt. Col Kilgore", 0x30004},
    {"Bayonetta Odette", 0x30005},
    {"Bayonetta Shuraba", 0x30009},
    {"Bayonetta Shuraba Sheath", 0x3000A},
    {"Bayonetta Kulshedra (Main)", 0x3000B},
    {"Bayonetta Kulshedra (Effect)", 0x3000C},
    {"Bayonetta Odette Elegance", 0x3000D},
    {"Bayonetta Kulshedra Elegance", 0x3000E},
    {"Bayonettao Durga Elegance", 0x3000F},
    {"Bayonetta Lt. Col Kilgore Elegance", 0x30010},
    {"Bayonetta Sai-Fung Elegance", 0x30011},
    {"Jeanne Pistol", 0x30020},
    {"Jeanne Angel Slayer", 0x30022},
    {"Umbran Sisters", 0x30030},
    {"Bayonetta Onyx Rose", 0x30035},
    {"Angel Wings", 0x30100},
    {"Angel Spear", 0x30101},
    {"Angel Trumpet", 0x30103},
    {"Angel Greatsword", 0x30105},
    {"Angel Bow", 0x30106},
    {"Angel Sword (Unused)", 0x30108},
    {"Angel Axe", 0x30109},
    {"Angel Shield", 0x3010A},
    {"Angel Flail", 0x3010D},
    {"Angel Clothes", 0x30110},
    {"Angel Mask", 0x30120},
    {"Grace & Glory Claws", 0x30126},
    {"Angel Scythe", 0x30150},
    {"Glory Claws", 0x30127},
	{"Key", 0x30128},
	{"Crystal Skull", 0x3012B},
    {"Grace Claws", 0x30160},
    {"Grace Claws", 0x30161},
    {"Grace & Glory Dummy Dat (w/Animations)", 0x30162},
    {"Gracious Claws", 0x30163},
    {"Gracious Claw", 0x30164},
    {"Glorious Claws", 0x30165},
    {"Glorious Claw", 0x30166},
    {"Harmony Chainsaw", 0x30170},
    {"Enemy Halo", 0x30200},
    {"Enemy Halo", 0x30201},
    {"Jeanne Pistol", 0x30130},
    {"Sign Board", 0x4002F},
    {"Prototype motorcycle", 0x50020},
    {"Lamp Post Weapon", 0x50189},
    {"Low-poly Angel Hitting the Floor", 0x501C4},
	{"Fortitudo", 0x501D0},// v1 = Prototype (red), v2 = Prototype (blue) / s1 = Shoots fireballs
    {"Crystal Witch Statue Reforming", 0x50228},
    {"Crystal Sage Statue", 0x50229},
    {"Rodin Drinks Shelf", 0x5022C},
    {"R666 Bridge", 0x50340},
    {"R666 Road", 0x50388},
    {"Ithavoll turret", 0x50580},
    {"Father Rodin Floor", 0x5F000},
    {"White Triangle", 0x60000},
    {"Unknown", 0x60001},
    {"Summon Hair Hell Hand", 0x60007},
    {"Portal VFX", 0x6000C},
    {"I didn't see anything spawn", 0x60011},
    {"Pulley's Butterfly Spawn", 0x60015},
    {"Queen Sheba Hair", 0x60069},
    {"Skybox maybe?", 0x600F4},
	{"Dove", 0x60100},
	{"Cat", 0x60101},// v1 = Black, v2 = White, v3 = Orange
	{"Crow", 0x60104},
	{"Umbran Tears Crow", 0x60106},// v1 = Caged
	{"Rat", 0x60110},
	{"Bat", 0x60120},
    {"Big collision", 0x60206},
    {"Load Screen Collision", 0x61000},
    {"Load Screen (Tracking Spotlight)", 0x61001},
    {"Load Screen", 0x61002},
    {"Load Screen (Red/White if Variant 0/1)", 0x61003},
    {"Spawned With Enemies", 0x70000},
    {"Halo", 0x90000},
    {"Health Pickup", 0x90010},
    {"Bullet Pickup", 0x90250},
    {"Bayonetta Bracelet", 0x90364},
    {"Bayonetta Bracelet", 0x90367},
    {"T-Pose Bayo", 0xA0000},
	{"Blue oil barrel", 0xC000F},
	{"Brown oil barrel", 0xC0010},
	{"Flower patch", 0xC0017},
	{"Gas canister", 0xC001C},
	{"Throwable car", 0xC0022},
	{"Grace and Glory statue", 0xC0040},
	{"Fairness/Fearless statue (Standing)", 0xC0041},
	{"Fairness/Fearless statue (Laying down)", 0xC0042},
	{"Affinity statue", 0xC0043},
    {"Barrel", 0xC0301},
};

static const EntityInfo relevantEntities[] = {
    {"Player Bayonetta", 0x10000}, // v0 = Moves, v2 = Doesn't Move
    {"Player Jeanne", 0x10020},
    {"Player Bayonetta P.E. A", 0x10025},
    {"Player Bayonetta P.E. B", 0x10026},
    {"Player Bayonetta P.E. C", 0x10027},
    {"Player Bayonetta d'Arc", 0x1002b},
    {"Player Bayonetta Umbra", 0x1002c},
    {"Player Bayonetta Various A", 0x1002d},
    {"Player Bayonetta Various B", 0x1002e},
    {"Player Bayonetta Various C", 0x1002f},
    {"Player Bayonetta Old", 0x10030},
    {"Player Jeanne P.E. A", 0x10061},
    {"Player Jeanne P.E. B", 0x10061},
    {"Player Jeanne P.E. C", 0x10062},
    {"Player Jeanne Formal B", 0x10064},
    {"Player Jeanne Old", 0x10066},
    {"Player Jeanne Umbra", 0x10067},
    {"Player Jeanne Various A", 0x10068},
    {"Player Jeanne Various B", 0x10069},
    {"Player Jeanne Various C", 0x1006A},
    {"Player Jeanne Komachi A", 0x1006E},
    {"Player Jeanne Komachi B", 0x10070},
    {"Player Jeanne Komachi C", 0x10072},
    {"Player Jeanne Nun", 0x10074},
    {"Player Jeanne Queen", 0x10075},
    {"Player Bayonetta Komachi A", 0x10083},
    {"Player Bayonetta Komachi B", 0x10085},
    {"Player Bayonetta Komachi C", 0x10087},
    {"Player Bayonetta Nun", 0x10089},
    {"Player Bayonetta Witch", 0x1008a},
    {"Affinity/Applaud", 0x20000},// Affinity: v1 = Spear, v2 = Trumpet, v8 = Hourglass, v9 = Mace, Applaud: v4 = Spear, v5 = Greatsword, v6 = Bow, v7 = Key
    {"Affinity (Spear) (Fire) / Ardor (Sword) (Fire)", 0x20001},
    {"Affinity (Laser)", 0x20002},
    {"Ardor", 0x20004}, // 0 = sword, 1 = axe, 2 = key
    {"Affinity/Applaud Invisible Base", 0x20006},
    {"Affinity (Axe) (Fire)", 0x20007},
    {"Affinity (Angel Attack)", 0x20008},
    {"Affinity (T-Pose)", 0x20009},
    {"Affinity Dummy Dat (w/Animations)", 0x2000E},
    {"Decoration", 0x20010},
    {"Dear", 0x20011},
    {"Dear & Decorations", 0x20012},
    {"Inspired (No HP Bar)", 0x20020},
    {"Inspired (Invisible)", 0x20021},
    {"Inspired (Green)", 0x20022},
    {"Enchant", 0x20030},
    {"Grace", 0x20040},
    {"Glory", 0x20041},
    {"Gracious", 0x20042},
    {"Glorious", 0x20043},
    {"Fearless", 0x20050},
    {"Fairness", 0x20051},
    {"Harmony", 0x20060},
    {"Beloved", 0x20070},
    {"Beloved (Larger)", 0x20071},
    {"Beloved (Invisible)", 0x20072},
    {"Brave", 0x20073},
    {"Beloved (Silver)", 0x20074},
    {"Beloved (Silver Invisible?)", 0x20076},
    {"Beloved w/Mask", 0x20078},
    {"Joy", 0x20080},
    {"Golem", 0x20090},
    {"Kinship", 0x200A0},
    {"Fortitudo (Green)", 0x200B0},
    {"Temperantia", 0x200C0},
    {"Iustitia", 0x200D0},
    {"Sapentia (Vertical)", 0x200E0},
    {"Fortitudo", 0x20100},
    {"Temperantia 2", 0x20200},
    {"Temperantia 3", 0x2020D},
    {"Sapentia", 0x20400},
    {"Balder", 0x20500},
    {"Father Rodin (Unkillable)", 0x20510},
    {"Jeanne Enemy Default", 0x21000},
    {"Jeanne Enemy Old", 0x21001},
    {"Jeanne Enemy Formal A", 0x21002},
    {"Bayo Enemy", 0x21003},
    {"Joy Fake (Unkillable)", 0x21010},
};

static const char* GetAllKnownEntityName(int id) {
    for (const auto& e : allKnownEntities) {
        if (e.id == id)
            return e.name;
    }
    return nullptr;
}

struct EntitySpawn {
    int entityID = 0x20000;
    EntitySpawnArg2 settings{};
    int unkn = -1;
};

struct SpawnInfo {
    const char* name;
    int id;
    int variant;
    int spawnModifier;
};

static const SpawnInfo spawnList[] = {
    // {"Player Bayonetta", 0x10000, 0, 0}, // v0 = Moves, v2 = Doesn't Move
    // {"Player Jeanne", 0x10020, 0, 0},
    // {"Player Bayonetta P.E. A", 0x10025, 0, 0},
    // {"Player Bayonetta P.E. B", 0x10026, 0, 0},
    // {"Player Bayonetta P.E. C", 0x10027, 0, 0},
    // {"Player Bayonetta d'Arc maybe", 0x1002b, 0, 0},
    // {"Player Bayonetta Umbra", 0x1002c, 0, 0},
    // {"Player Bayonetta Various A", 0x1002d, 0, 0},
    // {"Player Bayonetta Various B", 0x1002e, 0, 0},
    // {"Player Bayonetta Various C", 0x1002f, 0, 0},
    // {"Player Bayonetta Old", 0x10030, 0, 0},
    // {"Player Jeanne P.E. A", 0x10061, 0, 0},
    // {"Player Jeanne P.E. B", 0x10061, 0, 0},
    // {"Player Jeanne P.E. C", 0x10062, 0, 0},
    // {"Player Jeanne Formal B", 0x10064, 0, 0},
    // {"Player Jeanne Old", 0x10066, 0, 0},
    // {"Player Jeanne Umbra", 0x10067, 0, 0},
    // {"Player Jeanne Various A", 0x10068, 0, 0},
    // {"Player Jeanne Various B", 0x10069, 0, 0},
    // {"Player Jeanne Various C", 0x1006A, 0, 0},
    // {"Player Jeanne Komachi A", 0x1006E, 0, 0},
    // {"Player Jeanne Komachi B", 0x10070, 0, 0},
    // {"Player Jeanne Komachi C", 0x10072, 0, 0},
    // {"Player Jeanne Nun", 0x10074, 0, 0},
    // {"Player Jeanne Queen", 0x10075, 0, 0},
    // {"Player Bayonetta Komachi A", 0x10083, 0, 0},
    // {"Player Bayonetta Komachi B", 0x10085, 0, 0},
    // {"Player Bayonetta Komachi C", 0x10087, 0, 0},
    // {"Player Bayonetta Nun", 0x10089, 0, 0},
    // {"Player Bayonetta Witch", 0x1008a, 0, 0},
    {"Affinity (Spear)", 0x20000, 1, 0},
    {"Affinity (Trumpet)", 0x20000, 2, 0},
    {"Affinity (Mace)", 0x20000, 9, 0},
    {"Applaud (Spear)", 0x20000, 4, 0},
    {"Applaud (Greatsword)", 0x20000, 5, 0},
    {"Applaud (Bow)", 0x20000, 6, 0},
    {"Ardor (Fire) (Sword)", 0x20001, 0, 0},
    {"Affinity (Spear) (Fire)", 0x20001, 1, 0},
    {"Affinity (Laser)", 0x20002, 0, 0},
    {"Ardor (Sword)", 0x20004, 0, 0},
    {"Ardor (Axe)", 0x20004, 1, 0},
    {"Affinity (Axe) (Fire)", 0x20007, 0, 0},
    {"Decoration", 0x20010, 0, 0},
    {"Dear", 0x20011, 0, 0},
    {"Dear & Decorations", 0x20012, 0, 0},
    // {"Inspired (No HP Bar)", 0x20020},
    // {"Inspired (Green)", 0x20022},
    {"Enchant", 0x20030, 0, 0},
    {"Grace", 0x20040, 0, 0},
    {"Glory", 0x20041, 0, 0},
    {"Gracious", 0x20042, 0, 0},
    {"Glorious", 0x20043, 0, 0},
    {"Fearless", 0x20050, 0, 0},
    {"Fairness", 0x20051, 0, 0},
    {"Harmony", 0x20060, 0, 0},
    {"Beloved", 0x20070, 0, 0},
    {"Beloved (Larger)", 0x20071, 0, 0},
    {"Brave", 0x20073, 0, 0},
    {"Beloved (Silver)", 0x20074, 0, 0},
    {"Joy", 0x20080, 0, 0},
    {"Golem", 0x20090, 0, 0},
    {"Kinship", 0x200A0, 0, 0},
    {"Fortitudo (Green)", 0x200B0, 0, 0},
    // {"Temperantia", 0x200C0, 0, 0},
    // {"Iustitia", 0x200D0, 0, 0},
    // {"Fortitudo", 0x20100, 0, 0},
    // {"Temperantia 2", 0x20200, 0, 0},
    // {"Temperantia 3", 0x2020D, 0, 0},
    // {"Sapentia", 0x20400, 0, 0},
    {"Balder", 0x20500, 0, 0},
    // {"Father Rodin (Unkillable)", 0x20510, 0, 0},
    {"Jeanne Enemy Default", 0x21000, 0, 0},
    {"Jeanne Enemy Old", 0x21001, 0, 0},
    {"Jeanne Enemy Formal A", 0x21002, 0, 0},
    {"Bayo Enemy Default", 0x21003, 0, 0},
    // {"Joy Twin (Unkillable)", 0x21010, 0, 0},
};

enum class SpawnCategory {
    EnemyTier1,
    EnemyTier2,
    EnemyBoss,
    EnemyBigBoss,
};

struct SpawnEntry {
    SpawnInfo info;
    SpawnCategory category;
};

// break possible swaps into types, so enemies can only be swapped with enemies etc
// this is also used for enemy swapper, but tier is ignored
/*  
    const char* name;
    int id;
    int variant;
    int spawnModifier;
    int tier
*/
static const std::vector<SpawnEntry> spawnTypes = {
    {{"Affinity (Spear)", 0x20000, 1, 0}, SpawnCategory::EnemyTier1},
    {{"Affinity (Trumpet)", 0x20000, 2, 0}, SpawnCategory::EnemyTier1},
    {{"Affinity (Mace)", 0x20000, 9, 0}, SpawnCategory::EnemyTier1},
    {{"Applaud (Spear)", 0x20000, 4, 0}, SpawnCategory::EnemyTier1},
    {{"Applaud (Greatsword)", 0x20000, 5, 0}, SpawnCategory::EnemyTier1},
    {{"Applaud (Bow)", 0x20000, 6, 0}, SpawnCategory::EnemyTier1},
    {{"Ardor (Fire) (Sword)", 0x20001, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Affinity (Spear) (Fire)", 0x20001, 1, 0}, SpawnCategory::EnemyTier1},
    {{"Affinity (Laser)", 0x20002, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Affinity (Axe) (Fire)", 0x20007, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Decoration", 0x20010, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Dear", 0x20011, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Enchant", 0x20030, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Harmony", 0x20060, 0, 0}, SpawnCategory::EnemyTier1},

    {{"Ardor (Sword)", 0x20004, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Ardor (Axe)", 0x20004, 1, 0}, SpawnCategory::EnemyTier2},
    {{"Dear & Decorations", 0x20012, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Grace", 0x20040, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Glory", 0x20041, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Gracious", 0x20042, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Glorious", 0x20043, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Fearless", 0x20050, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Fairness", 0x20051, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Beloved", 0x20070, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Beloved (Larger)", 0x20071, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Brave", 0x20073, 0, 0}, SpawnCategory::EnemyTier1},
    {{"Beloved (Silver)", 0x20074, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Joy", 0x20080, 0, 0}, SpawnCategory::EnemyTier2},
    {{"Kinship", 0x200A0, 0, 0}, SpawnCategory::EnemyTier2},

    {{"Golem", 0x20090, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Fortitudo (Green)", 0x200B0, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Balder", 0x20500, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Father Rodin (Unkillable)", 0x20510, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Jeanne Enemy Default", 0x21000, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Jeanne Enemy Old", 0x21001, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Jeanne Enemy Formal A", 0x21002, 0, 0}, SpawnCategory::EnemyBoss},
    {{"Bayo Enemy Default", 0x21003, 0, 0}, SpawnCategory::EnemyBoss},
    //{{"Joy Twin (Unkillable)", 0x21010, 0, 0}, SpawnCategory::EnemyBoss},

    // these are currently not randomized because most of them would just instantly fall into the void
    // {{"Inspired (No HP Bar)", 0x20020}, SpawnCategory::EnemyBigBoss},
    // {{"Inspired (Green)", 0x20022}, SpawnCategory::EnemyBigBoss},
    {{"Temperantia", 0x200C0, 0, 0}, SpawnCategory::EnemyBigBoss},
    {{"Iustitia", 0x200D0, 0, 0}, SpawnCategory::EnemyBigBoss},
    {{"Fortitudo", 0x20100, 0, 0}, SpawnCategory::EnemyBigBoss},
    {{"Temperantia 2", 0x20200, 0, 0}, SpawnCategory::EnemyBigBoss},
    {{"Temperantia 3", 0x2020D, 0, 0}, SpawnCategory::EnemyBigBoss},
    {{"Sapentia", 0x20400, 0, 0}, SpawnCategory::EnemyBigBoss},
};

struct SwapRule {
    int sourceIndex;
    int targetIndex;
    int spawnModifier;
    bool enabled;
};

struct PlayerCharacterSpawn {
    const char* name;
    int id;
};

static PlayerCharacterSpawn coop_characters[] = {
    { "Bayonetta", 0x10000 },
    { "Bayonetta (d'Arc)", 0x1002b },
    { "Bayonetta (Nun)", 0x10089 },
    { "Bayonetta (Queen)", 0x1008a },
    { "Bayonetta (Old)", 0x10030 },
    { "Bayonetta (Umbra)", 0x1002c },
    { "Bayonetta (P.E. A)", 0x10025 },
    { "Bayonetta (P.E. B)", 0x10026 },
    { "Bayonetta (P.E. C)", 0x10027 },
    { "Bayonetta (Various A)", 0x1002d },
    { "Bayonetta (Various B)", 0x1002e },
    { "Bayonetta (Various C)", 0x1002f },
    { "Bayonetta (Komachi) A", 0x10083 },
    { "Bayonetta (Komachi) B", 0x10085 },
    { "Bayonetta (Komachi) C", 0x10087 },

    { "Jeanne (Formal)", 0x10020 },
    { "Jeanne (Formal) B", 0x10064 },
    { "Jeanne (Nun)", 0x10074 },
    { "Jeanne (Queen)", 0x10075 },
    { "Jeanne (Old)", 0x10066 },
    { "Jeanne (Umbra)", 0x10067 },
    { "Jeanne (P.E.) A", 0x10061 },
    { "Jeanne (P.E.) B", 0x10061 },
    { "Jeanne (P.E.) C", 0x10062 },
    { "Jeanne (Various) A", 0x10068 },
    { "Jeanne (Various) B", 0x10069 },
    { "Jeanne (Various) C", 0x1006A },
    { "Jeanne (Komachi) A", 0x1006E },
    { "Jeanne (Komachi) B", 0x10070 },
    { "Jeanne (Komachi) C", 0x10072 },
};

// 

enum PVP_ATHIT_TYPE {
    PVP_NORMAL = 0x3,
    PVP_HEAVY = 0x4, // in the air you are knocked diagonally up
    PVP_LAUNCHER = 0x5,
    PVP_DIAG_DOWN = 0x6,
    PVP_STAGGER_BACK_THEN_FORWARD = 0x18,
    PVP_ICECUBE = 0x1b,
    PVP_LIGHT = 0x24,
    PVP_BLUE_ELECTRIC_NORMAL = 0x28,
    PVP_BLUE_ELECTRIC_AIR = 0x29,
    PVP_YELLOW_ELECTRIC = 0x2b,
    PVP_FLATTEN = 0x4d, // cartoon flatten
};
    // PVP_OBLIVION 0x39, // knock them away into oblivion wtf
    // PVP_DIE = 0x3b,
    // PVP_CHILD = 0x3c // TEMPORARILY TURN THEM INTO A CHILD THAT IS STUCK BETWEEN YOUR LEGS
    // PVP_DIE_KB = 0x41, // knocked back into death

enum ATHIT_TYPE /* int */ {
    ATHIT_TYPE_PL_HANDGUN = 0x0,
    ATHIT_TYPE_PL_HANDGUN_SML = 0x1,
    ATHIT_TYPE_PL_S_HANDGUN = 0x2,
    ATHIT_TYPE_PL_M_HANDGUN = 0x3,
    ATHIT_TYPE_PL_HANDGUN_REFLECT = 0x4,
    ATHIT_TYPE_PL_SHOTGUN = 0x5,
    ATHIT_TYPE_PL_SHOTGUN_SML = 0x6,
    ATHIT_TYPE_PL_S_SHOTGUN = 0x7,
    ATHIT_TYPE_PL_TONFA_ROCKET = 0x8,
    ATHIT_TYPE_PL_TONFA_G_ROCKET = 0x9,
    ATHIT_TYPE_PL_SHOOTING_HANDGUN = 0xa,
    ATHIT_TYPE_PL_PUNCH = 0xb,
    ATHIT_TYPE_PL_PUNCH2 = 0xc,
    ATHIT_TYPE_PL_UPPER = 0xd,
    ATHIT_TYPE_PL_DASHPUNCH = 0xe,
    ATHIT_TYPE_PL_SPINPUNCH = 0xf,
    ATHIT_TYPE_PL_BLOWPUNCH = 0x10,
    ATHIT_TYPE_PL_BLOWPUNCH2 = 0x11,
    ATHIT_TYPE_PL_COMBOATK = 0x12,
    ATHIT_TYPE_PL_COMBOATK_E = 0x13,
    ATHIT_TYPE_PL_100PUNCH = 0x14,
    ATHIT_TYPE_PL_100PUNCH_E = 0x15,
    ATHIT_TYPE_PL_KICK = 0x16,
    ATHIT_TYPE_PL_KICK2 = 0x17,
    ATHIT_TYPE_PL_KICKUPPER = 0x18,
    ATHIT_TYPE_PL_JUMPKICKUPPER = 0x19,
    ATHIT_TYPE_PL_DASHKICK = 0x1a,
    ATHIT_TYPE_PL_SPINKICK = 0x1b,
    ATHIT_TYPE_PL_BLOWKICK = 0x1c,
    ATHIT_TYPE_PL_BLOWKICK2 = 0x1d,
    ATHIT_TYPE_PL_S_BLOWKICK = 0x1e,
    ATHIT_TYPE_PL_JUMPKICK = 0x1f,
    ATHIT_TYPE_PL_STAMPKICK = 0x20,
    ATHIT_TYPE_PL_100KICK = 0x21,
    ATHIT_TYPE_PL_100KICK_E = 0x22,
    ATHIT_TYPE_PL_STAMP = 0x23, // landing from a high fall
    ATHIT_TYPE_PL_HEELKICK = 0x24,
    ATHIT_TYPE_PL_FALLKICK = 0x25,
    ATHIT_TYPE_PL_LOWSPINKICK_L = 0x26,
    ATHIT_TYPE_PL_LOWSPINKICK_R = 0x27,
    ATHIT_TYPE_PL_AIRSPINKICK_L = 0x28,
    ATHIT_TYPE_PL_AIRSPINKICK_R = 0x29,
    ATHIT_TYPE_PL_LOWSPINKICK_L_E = 0x2a,
    ATHIT_TYPE_PL_LOWSPINKICK_R_E = 0x2b,
    ATHIT_TYPE_PL_AIRSPINKICK_L_E = 0x2c,
    ATHIT_TYPE_PL_AIRSPINKICK_R_E = 0x2d,
    ATHIT_TYPE_PL_BIGFALLKICK = 0x2e,
    ATHIT_TYPE_PL_BLADE1 = 0x2f,
    ATHIT_TYPE_PL_BLADE2 = 0x30,
    ATHIT_TYPE_PL_BLADE3 = 0x31,
    ATHIT_TYPE_PL_BLADE4 = 0x32,
    ATHIT_TYPE_PL_BLADE_AIR1 = 0x33,
    ATHIT_TYPE_PL_BLADE_AIR2 = 0x34,
    ATHIT_TYPE_PL_BLADE_AIR3 = 0x35,
    ATHIT_TYPE_PL_BLADE_AIR4 = 0x36,
    ATHIT_TYPE_PL_DELAYBLADE_A1 = 0x37,
    ATHIT_TYPE_PL_DELAYBLADE_A2 = 0x38,
    ATHIT_TYPE_PL_DELAYBLADE_A3 = 0x39,
    ATHIT_TYPE_PL_DELAYBLADE_B1 = 0x3a,
    ATHIT_TYPE_PL_DELAYBLADE_B2 = 0x3b,
    ATHIT_TYPE_PL_DELAYBLADE_B3 = 0x3c,
    ATHIT_TYPE_PL_DELAYBLADE_C = 0x3d,
    ATHIT_TYPE_PL_BLADE = 0x3e,
    ATHIT_TYPE_PL_BLADE_SIDE = 0x3f,
    ATHIT_TYPE_PL_BLADE_IAI = 0x40,
    ATHIT_TYPE_PL_BLADE_IAI_MAX = 0x41,
    ATHIT_TYPE_PL_COMBOBLADE = 0x42,
    ATHIT_TYPE_PL_COMBOBLADE_SIDE = 0x43,
    ATHIT_TYPE_PL_COMBOBLADE_E = 0x44,
    ATHIT_TYPE_PL_UPPERBLADE = 0x45,
    ATHIT_TYPE_PL_AIRUPPERBLADE = 0x46,
    ATHIT_TYPE_PL_DASHBLADE = 0x47,
    ATHIT_TYPE_PL_SPINPBLADE = 0x48,
    ATHIT_TYPE_PL_SPINPBLADE2 = 0x49,
    ATHIT_TYPE_PL_SPINPBLADE3 = 0x4a,
    ATHIT_TYPE_PL_BLOWBLADE = 0x4b,
    ATHIT_TYPE_PL_BLADEWAVE = 0x4c,
    ATHIT_TYPE_PL_BLADEWAVE_MAX = 0x4d,
    ATHIT_TYPE_PL_STAMPBLADE = 0x4e,
    ATHIT_TYPE_PL_STAMPBLADE_F = 0x4f,
    ATHIT_TYPE_PL_LB_BLADE1 = 0x50,
    ATHIT_TYPE_PL_LB_BLADE2 = 0x51,
    ATHIT_TYPE_PL_LB_BLADE3 = 0x52,
    ATHIT_TYPE_PL_LB_BLADE4 = 0x53,
    ATHIT_TYPE_PL_LB_BLADE_AIR1 = 0x54,
    ATHIT_TYPE_PL_LB_BLADE_AIR2 = 0x55,
    ATHIT_TYPE_PL_LB_BLADE_AIR3 = 0x56,
    ATHIT_TYPE_PL_LB_BLADE_AIR4 = 0x57,
    ATHIT_TYPE_PL_LB_DELAYBLADE_A1 = 0x58,
    ATHIT_TYPE_PL_LB_DELAYBLADE_A2 = 0x59,
    ATHIT_TYPE_PL_LB_DELAYBLADE_A3 = 0x5a,
    ATHIT_TYPE_PL_LB_DELAYBLADE_B1 = 0x5b,
    ATHIT_TYPE_PL_LB_DELAYBLADE_B2 = 0x5c,
    ATHIT_TYPE_PL_LB_DELAYBLADE_B3 = 0x5d,
    ATHIT_TYPE_PL_LB_DELAYBLADE_C = 0x5e,
    ATHIT_TYPE_PL_LB_BLADE = 0x5f,
    ATHIT_TYPE_PL_LB_BLADE_SIDE = 0x60,
    ATHIT_TYPE_PL_LB_BLADE_IAI = 0x61,
    ATHIT_TYPE_PL_LB_BLADE_IAI_MAX = 0x62,
    ATHIT_TYPE_PL_LB_COMBOBLADE = 0x63,
    ATHIT_TYPE_PL_LB_COMBOBLADE_SIDE = 0x64,
    ATHIT_TYPE_PL_LB_COMBOBLADE_E = 0x65,
    ATHIT_TYPE_PL_LB_UPPERBLADE = 0x66,
    ATHIT_TYPE_PL_LB_AIRUPPERBLADE = 0x67,
    ATHIT_TYPE_PL_LB_DASHBLADE = 0x68,
    ATHIT_TYPE_PL_LB_SPINPBLADE = 0x69,
    ATHIT_TYPE_PL_LB_SPINPBLADE2 = 0x6a,
    ATHIT_TYPE_PL_LB_SPINPBLADE3 = 0x6b,
    ATHIT_TYPE_PL_LB_BLOWBLADE = 0x6c,
    ATHIT_TYPE_PL_LB_BLADEWAVE = 0x6d,
    ATHIT_TYPE_PL_LB_BLADEWAVE_MAX = 0x6e,
    ATHIT_TYPE_PL_LB_STAMPBLADE = 0x6f,
    ATHIT_TYPE_PL_LB_STAMPBLADE_F = 0x70,
    ATHIT_TYPE_PL_WHIP = 0x71,
    ATHIT_TYPE_PL_WHIPUPPER = 0x72,
    ATHIT_TYPE_PL_WHIPSPIN = 0x73,
    ATHIT_TYPE_PL_CLAW1 = 0x74,
    ATHIT_TYPE_PL_CLAW2 = 0x75,
    ATHIT_TYPE_PL_CLAW3 = 0x76,
    ATHIT_TYPE_PL_AIRCLAW1 = 0x77,
    ATHIT_TYPE_PL_AIRCLAW2 = 0x78,
    ATHIT_TYPE_PL_AIRCLAW3 = 0x79,
    ATHIT_TYPE_PL_DASHCLAW = 0x7a,
    ATHIT_TYPE_PL_UPPERCLAW = 0x7b,
    ATHIT_TYPE_PL_CLAWFIREBOMB_LV1 = 0x7c,
    ATHIT_TYPE_PL_CLAWFIREBOMB_LV2 = 0x7d,
    ATHIT_TYPE_PL_CLAWFIREBOMB_LV3 = 0x7e,
    ATHIT_TYPE_PL_CLAWELECBOMB = 0x7f,
    ATHIT_TYPE_PL_CLAWKICK1 = 0x80,
    ATHIT_TYPE_PL_CLAWKICK2 = 0x81,
    ATHIT_TYPE_PL_CLAWKICK3 = 0x82,
    ATHIT_TYPE_PL_CHANGECLAW = 0x83,
    ATHIT_TYPE_PL_SPINKICKCLAW = 0x84,
    ATHIT_TYPE_PL_SPINPUNCHCLAW = 0x85,
    ATHIT_TYPE_PL_CLAWCOMBO = 0x86,
    ATHIT_TYPE_PL_CLAWCOMBO_FINISH = 0x87,
    ATHIT_TYPE_PL_F_CLAW_100KICK_E = 0x88,
    ATHIT_TYPE_PL_F_CLAW_KICK_BIG = 0x89,
    ATHIT_TYPE_PL_F_CLAW_HEELKICK = 0x8a,
    ATHIT_TYPE_PL_F_CLAW_STAMP = 0x8b,
    ATHIT_TYPE_PL_F_CLAW_BLOWKICK = 0x8c,
    ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_L = 0x8d,
    ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_R = 0x8e,
    ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_L = 0x8f,
    ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_R = 0x90,
    ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_L_E = 0x91,
    ATHIT_TYPE_PL_F_CLAW_LOWSPINKICK_R_E = 0x92,
    ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_L_E = 0x93,
    ATHIT_TYPE_PL_F_CLAW_AIRSPINKICK_R_E = 0x94,
    ATHIT_TYPE_PL_F_CLAW_FALLKICK = 0x95,
    ATHIT_TYPE_PL_F_CLAW_BIGFALLKICK = 0x96,
    ATHIT_TYPE_PL_F_CLAW_KICKUPPER = 0x97,
    ATHIT_TYPE_PL_ELEC_CLAW1 = 0x98,
    ATHIT_TYPE_PL_ELEC_CLAW2 = 0x99,
    ATHIT_TYPE_PL_ELEC_CLAW3 = 0x9a,
    ATHIT_TYPE_PL_ELEC_CLAW4 = 0x9b,
    ATHIT_TYPE_PL_ELEC_AIRCLAW1 = 0x9c,
    ATHIT_TYPE_PL_ELEC_AIRCLAW2 = 0x9d,
    ATHIT_TYPE_PL_ELEC_AIRCLAW3 = 0x9e,
    ATHIT_TYPE_PL_ELEC_AIRCLAW4 = 0x9f,
    ATHIT_TYPE_PL_ELEC_DASHCLAW = 0xa0,
    ATHIT_TYPE_PL_ELEC_UPPERCLAW = 0xa1,
    ATHIT_TYPE_PL_ELEC_CLAWKICK1 = 0xa2,
    ATHIT_TYPE_PL_ELEC_CLAWKICK2 = 0xa3,
    ATHIT_TYPE_PL_ELEC_CLAWKICK3 = 0xa4,
    ATHIT_TYPE_PL_ELEC_CHANGECLAW = 0xa5,
    ATHIT_TYPE_PL_ELEC_SPINKICKCLAW = 0xa6,
    ATHIT_TYPE_PL_ELEC_SPINPUNCHCLAW = 0xa7,
    ATHIT_TYPE_PL_ELEC_CLAWCOMBO = 0xa8,
    ATHIT_TYPE_PL_ELEC_CLAWCOMBO_FINISH = 0xa9,
    ATHIT_TYPE_PL_E_CLAW_100KICK_E = 0xaa,
    ATHIT_TYPE_PL_E_CLAW_KICK_BIG = 0xab,
    ATHIT_TYPE_PL_E_CLAW_HEELKICK = 0xac,
    ATHIT_TYPE_PL_E_CLAW_STAMP = 0xad,
    ATHIT_TYPE_PL_E_CLAW_BLOWKICK = 0xae,
    ATHIT_TYPE_PL_E_CLAW_LOWSPINKICK_L = 0xaf,
    ATHIT_TYPE_PL_E_CLAW_LOWSPINKICK_R = 0xb0,
    ATHIT_TYPE_PL_E_CLAW_AIRSPINKICK_L = 0xb1,
    ATHIT_TYPE_PL_E_CLAW_AIRSPINKICK_R = 0xb2,
    ATHIT_TYPE_PL_E_CLAW_LOWSPINKICK_L_E = 0xb3,
    ATHIT_TYPE_PL_E_CLAW_LOWSPINKICK_R_E = 0xb4,
    ATHIT_TYPE_PL_E_CLAW_AIRSPINKICK_L_E = 0xb5,
    ATHIT_TYPE_PL_E_CLAW_AIRSPINKICK_R_E = 0xb6,
    ATHIT_TYPE_PL_E_CLAW_FALLKICK = 0xb7,
    ATHIT_TYPE_PL_E_CLAW_BIGFALLKICK = 0xb8,
    ATHIT_TYPE_PL_E_CLAW_KICKUPPER = 0xb9,
    ATHIT_TYPE_PL_TONFA1 = 0xba,
    ATHIT_TYPE_PL_TONFA2 = 0xbb,
    ATHIT_TYPE_PL_TONFA3 = 0xbc,
    ATHIT_TYPE_PL_DASHTONFA = 0xbd,
    ATHIT_TYPE_PL_DASHTONFA_E = 0xbe,
    ATHIT_TYPE_PL_UPPERTONFA = 0xbf,
    ATHIT_TYPE_PL_TONFAKICK = 0xc0,
    ATHIT_TYPE_PL_TONFASPIN = 0xc1,
    ATHIT_TYPE_PL_SKATES_KICK1 = 0xc2,
    ATHIT_TYPE_PL_SKATES_KICK2 = 0xc3,
    ATHIT_TYPE_PL_SKATES_KICK3 = 0xc4,
    ATHIT_TYPE_PL_SKATES_KICK4 = 0xc5,
    ATHIT_TYPE_PL_SKATES_100 = 0xc6,
    ATHIT_TYPE_PL_SKATES_100KICK_E = 0xc7,
    ATHIT_TYPE_PL_SKATES_KICK_BIG = 0xc8,
    ATHIT_TYPE_PL_SKATES_HEELKICK = 0xc9,
    ATHIT_TYPE_PL_SKATES_STAMP = 0xca,
    ATHIT_TYPE_PL_SKATES_BLOWKICK = 0xcb,
    ATHIT_TYPE_PL_SKATES_LOWSPINKICK_L = 0xcc,
    ATHIT_TYPE_PL_SKATES_LOWSPINKICK_R = 0xcd,
    ATHIT_TYPE_PL_SKATES_AIRSPINKICK_L = 0xce,
    ATHIT_TYPE_PL_SKATES_AIRSPINKICK_R = 0xcf,
    ATHIT_TYPE_PL_SKATES_LOWSPINKICK_L_E = 0xd0,
    ATHIT_TYPE_PL_SKATES_LOWSPINKICK_R_E = 0xd1,
    ATHIT_TYPE_PL_SKATES_AIRSPINKICK_L_E = 0xd2,
    ATHIT_TYPE_PL_SKATES_AIRSPINKICK_R_E = 0xd3,
    ATHIT_TYPE_PL_SKATES_FALLKICK = 0xd4,
    ATHIT_TYPE_PL_SKATES_BIGFALLKICK = 0xd5,
    ATHIT_TYPE_PL_SKATES_KICKUPPER = 0xd6,
    ATHIT_TYPE_PL_NUNCHUK1 = 0xd7,
    ATHIT_TYPE_PL_NUNCHUK_CHOP = 0xd8,
    ATHIT_TYPE_PL_NUNCHUK_BEAM = 0xd9,
    ATHIT_TYPE_PL_NUNCHUK_BEAM_SML = 0xda,
    ATHIT_TYPE_PL_NUNCHUK_UPPER = 0xdb,
    ATHIT_TYPE_PL_NUNCHUKSTAMP = 0xdc,
    ATHIT_TYPE_PL_VARIANT_ARROW = 0xdd,
    ATHIT_TYPE_PL_VARIANT_TRUMPET = 0xde,
    ATHIT_TYPE_PL_VARIANT_S_TRUMPET = 0xdf,
    ATHIT_TYPE_PL_VARIANT_CLAW_ELEC = 0xe0,
    ATHIT_TYPE_PL_LASER_SHOT = 0xe1,
    ATHIT_TYPE_PL_LASER_FOOTSHOT = 0xe2,
    ATHIT_TYPE_PL_LASER_BEAM = 0xe3,
    ATHIT_TYPE_PL_LASER_S_BEAM = 0xe4,
    ATHIT_TYPE_PL_GW_BLADE = 0xe5,
    ATHIT_TYPE_PL_GW_BLADE_SIDE = 0xe6,
    ATHIT_TYPE_PL_GW_DASHBLADE = 0xe7,
    ATHIT_TYPE_PL_GW_AXE = 0xe8,
    ATHIT_TYPE_PL_GW_AXE_SIDE = 0xe9,
    ATHIT_TYPE_PL_GW_CLAW = 0xea,
    ATHIT_TYPE_PL_GW_CLAW_SIDE = 0xeb,
    ATHIT_TYPE_PL_GW_CLAW_FIRESPIN = 0xec,
    ATHIT_TYPE_PL_GW_MSTAR = 0xed,
    ATHIT_TYPE_PL_GW_MSTAR_MDL = 0xee,
    ATHIT_TYPE_PL_GW_MSTAR_BIG = 0xef,
    ATHIT_TYPE_PL_GW_BOWBLADE1 = 0xf0,
    ATHIT_TYPE_PL_GW_BOWBLADE2 = 0xf1,
    ATHIT_TYPE_PL_GW_BOWBLADE3 = 0xf2,
    ATHIT_TYPE_PL_GW_BOWBLADE_FIN = 0xf3,
    ATHIT_TYPE_PL_GW_LAMPPOST1 = 0xf4,
    ATHIT_TYPE_PL_GW_LAMPPOST2 = 0xf5,
    ATHIT_TYPE_PL_GW_LAMPPOST3 = 0xf6,
    ATHIT_TYPE_PL_GW_POLESPINKICK = 0xf7,
    ATHIT_TYPE_PL_GW_ARROW = 0xf8,
    ATHIT_TYPE_PL_GW_CHAINSAW1 = 0xf9,
    ATHIT_TYPE_PL_GW_CHAINSAW2 = 0xfa,
    ATHIT_TYPE_PL_GW_CHAINSAW3 = 0xfb,
    ATHIT_TYPE_PL_GW_CHAINSAW = 0xfc,
    ATHIT_TYPE_PL_GW_CHAINSAW_SIDE = 0xfd,
    ATHIT_TYPE_PL_GW_BOWBLADEUPPER = 0xfe,
    ATHIT_TYPE_PL_GW_CLAW_ELEC = 0xff,
    ATHIT_TYPE_PL_CROW_WING = 0x100,
    ATHIT_TYPE_PL_GUARDIAN_BLOOD = 0x101,
    ATHIT_TYPE_PL_BIGLANDING = 0x102,
    ATHIT_TYPE_PL_BIGFALL = 0x103,
    ATHIT_TYPE_PL_PANTHERDASH = 0x104,
    ATHIT_TYPE_PL_PANTHERCHARGE = 0x105,
    ATHIT_TYPE_PL_KAMEHAMEHA = 0x106,
    ATHIT_TYPE_PL_FIREBALL = 0x107,
    ATHIT_TYPE_PL_SLAP = 0x108,
    ATHIT_TYPE_PL_SLAP_E = 0x109,
    ATHIT_TYPE_PL_EM_BLOW = 0x10a,
    ATHIT_TYPE_PL_EM_BIGBLOW = 0x10b,
    ATHIT_TYPE_PL_GW_THROW = 0x10c,
    ATHIT_TYPE_PL_THROWED_CAR = 0x10d,
    ATHIT_TYPE_PL_ROCK = 0x10e,
    ATHIT_TYPE_PL_BIKE = 0x10f,
    ATHIT_TYPE_PL_LAVA = 0x110,
    ATHIT_TYPE_PL_TRUMPET = 0x111,
    ATHIT_TYPE_PL_S_TRUMPET = 0x112,
    ATHIT_TYPE_PL_HORN = 0x113,
    ATHIT_TYPE_PL_S_HORN = 0x114,
    ATHIT_TYPE_PL_KISSMARK = 0x115,
    ATHIT_TYPE_PL_DMG_COUNTER = 0x116,
    ATHIT_TYPE_PL_DEVIL_MDL_PUNCH = 0x117,
    ATHIT_TYPE_PL_DEVIL_PUNCH = 0x118,
    ATHIT_TYPE_PL_DEVIL_KICK = 0x119,
    ATHIT_TYPE_PL_DEVIL_MDL_KICK = 0x11a,
    ATHIT_TYPE_PL_DEVIL_UPPER = 0x11b,
    ATHIT_TYPE_PL_DEVIL_STAMP = 0x11c,
    ATHIT_TYPE_PL_DEVIL_BLADE = 0x11d,
    ATHIT_TYPE_PL_DEVIL_BLADE_R = 0x11e,
    ATHIT_TYPE_PL_DEVIL_BLADE_RU = 0x11f,
    ATHIT_TYPE_PL_DEVIL_BLADE_LU = 0x120,
    ATHIT_TYPE_PL_DEVIL_BLADEUPPER = 0x121,
    ATHIT_TYPE_PL_DEVIL_BLADESTING = 0x122,
    ATHIT_TYPE_PL_DEVIL_BLADESTAMP = 0x123,
    ATHIT_TYPE_PL_DEVIL_BLADECHOP = 0x124,
    ATHIT_TYPE_PL_DEVIL_MDL_WHIP = 0x125,
    ATHIT_TYPE_PL_DEVIL_WHIP = 0x126,
    ATHIT_TYPE_PL_DEVIL_FIRE_CLAW = 0x127,
    ATHIT_TYPE_PL_DEVIL_FIRE_CLAW_RU = 0x128,
    ATHIT_TYPE_PL_DEVIL_FIRE_CLAW_LU = 0x129,
    ATHIT_TYPE_PL_DEVIL_FIRE_MDL_CLAW = 0x12a,
    ATHIT_TYPE_PL_DEVIL_FIRE_CLAWUPPER = 0x12b,
    ATHIT_TYPE_PL_DEVIL_FIRE_CLAWSTAMP = 0x12c,
    ATHIT_TYPE_PL_DEVIL_ELEC_CLAW = 0x12d,
    ATHIT_TYPE_PL_DEVIL_ELEC_CLAW_RU = 0x12e,
    ATHIT_TYPE_PL_DEVIL_ELEC_CLAW_LU = 0x12f,
    ATHIT_TYPE_PL_DEVIL_ELEC_MDL_CLAW = 0x130,
    ATHIT_TYPE_PL_DEVIL_ELEC_CLAWUPPER = 0x131,
    ATHIT_TYPE_PL_DEVIL_ELEC_CLAWSTAMP = 0x132,
    ATHIT_TYPE_PL_DEVIL_ICE_KICK = 0x133,
    ATHIT_TYPE_PL_DEVIL_ICE_MDL_KICK = 0x134,
    ATHIT_TYPE_PL_DEVIL_ICE_MINI_KICK = 0x135,
    ATHIT_TYPE_PL_DEVIL_ICE_STAMP = 0x136,
    ATHIT_TYPE_PL_DEVIL_ICE_UPPER = 0x137,
    ATHIT_TYPE_PL_DEVIL_MINI_PUNCH = 0x138,
    ATHIT_TYPE_PL_DEVIL_MINI_KICK = 0x139,
    ATHIT_TYPE_PL_DEVIL_ROCKETPUNCH = 0x13a,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADE_L = 0x13b,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADE_R = 0x13c,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADE_RU = 0x13d,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADE_LU = 0x13e,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADEUPPER = 0x13f,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADESTING = 0x140,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADESTAMP = 0x141,
    ATHIT_TYPE_PL_DEVIL_MINI_BLADECHOP = 0x142,
    ATHIT_TYPE_PL_SHOOTING_DEVILPUNCH = 0x143,
    ATHIT_TYPE_PL_HIGHWAYBIKE = 0x144,
    ATHIT_TYPE_PL_ITEMBOMB = 0x145,
    ATHIT_TYPE_PL_MACHINEGUN = 0x146,
    ATHIT_TYPE_PL_BIKESLIDING = 0x147,
    ATHIT_TYPE_PL_BIKERUN = 0x148,
    ATHIT_TYPE_PL_BONUS_GAME = 0x149,
    ATHIT_TYPE_EM_NORMAL = 0x14a,
    ATHIT_TYPE_EM_BLOW = 0x14b,
    ATHIT_TYPE_EM_UPPER = 0x14c,
    ATHIT_TYPE_EM_DOWN = 0x14d,
    ATHIT_TYPE_EM_METAL = 0x14e,
    ATHIT_TYPE_EM_METAL_BLOW = 0x14f,
    ATHIT_TYPE_EM_METAL_UPPER = 0x150,
    ATHIT_TYPE_EM_METAL_DOWN = 0x151,
    ATHIT_TYPE_EM_GUN = 0x152,
    ATHIT_TYPE_EM_GUN_BLOW = 0x153,
    ATHIT_TYPE_EM_GUN_UPPER = 0x154,
    ATHIT_TYPE_EM_GUN_DOWN = 0x155,
    ATHIT_TYPE_EM_BLADE = 0x156,
    ATHIT_TYPE_EM_BLADE_BLOW = 0x157,
    ATHIT_TYPE_EM_BLADE_BLOW2 = 0x158,
    ATHIT_TYPE_EM_BLADE_UPPER = 0x159,
    ATHIT_TYPE_EM_BLADE_DOWN = 0x15a,
    ATHIT_TYPE_EM_EM0510_NORMAL = 0x15b,
    ATHIT_TYPE_EM_EM0510_BLOW = 0x15c,
    ATHIT_TYPE_EM_EM0510_UPPER = 0x15d,
    ATHIT_TYPE_EM_EM0510_DOWN = 0x15e,
    ATHIT_TYPE_EM_STICK = 0x15f,
    ATHIT_TYPE_EM_STICK2 = 0x160,
    ATHIT_TYPE_EM_STICK_BLOW = 0x161,
    ATHIT_TYPE_EM_KAMEHAMEHA = 0x162,
    ATHIT_TYPE_EM_EM0040_CLAW = 0x163,
    ATHIT_TYPE_EM_FIREBALL = 0x164,
    ATHIT_TYPE_EM_MINI_FIREBALL = 0x165,
    ATHIT_TYPE_EM_ICEBALL = 0x166,
    ATHIT_TYPE_EM_CATCHBITE = 0x167,
    ATHIT_TYPE_EM_EM0070CATCH = 0x168,
    ATHIT_TYPE_EM_EM00A3CATCH = 0x169,
    ATHIT_TYPE_EM_EM0100CATCH = 0x16a,
    ATHIT_TYPE_EM_EM020ACATCH = 0x16b,
    ATHIT_TYPE_EM_EM0303CATCH = 0x16c,
    ATHIT_TYPE_EM_EM0400CATCHDIE = 0x16d,
    ATHIT_TYPE_EM_EM0400CATCH = 0x16e,
    ATHIT_TYPE_EM_EM1000CATCHKICK = 0x16f,
    ATHIT_TYPE_EM_EM0500CATCHBALL = 0x170,
    ATHIT_TYPE_EM_EM0510FINAL = 0x171,
    ATHIT_TYPE_EM_EM0600CATCH = 0x172,
    ATHIT_TYPE_EM_ELEC = 0x173,
    ATHIT_TYPE_EM_ELEC_IN = 0x174,
    ATHIT_TYPE_EM_ELEC_BEAM = 0x175,
    ATHIT_TYPE_EM_MAGIC_STRING = 0x176,
    ATHIT_TYPE_EM_FLASH = 0x177,
    ATHIT_TYPE_EM_WITCHOBJATK = 0x178,
    ATHIT_TYPE_EM_DEVILPUNCH = 0x179,
    ATHIT_TYPE_EM_DEVILUPPER = 0x17a,
    ATHIT_TYPE_EM_DEVILKICK = 0x17b,
    ATHIT_TYPE_EM_DEVILKICKUPPER = 0x17c,
    ATHIT_TYPE_EM_DEVIL_STAMP = 0x17d,
    ATHIT_TYPE_EM_DEVIL_DRAGON = 0x17e,
    ATHIT_TYPE_EM_DEVIL_BLADE = 0x17f,
    ATHIT_TYPE_EM_MUCUS = 0x180,
    ATHIT_TYPE_EM_GLASS_BREAK = 0x181,
    ATHIT_TYPE_EM_GLASS_FRAME_BREAK = 0x182,
    ATHIT_TYPE_EM_PLANET = 0x183,
    ATHIT_TYPE_EM_EM0600_TORNADE = 0x184,
    ATHIT_TYPE_EM_EM0600_TORNADE2 = 0x185,
    ATHIT_TYPE_EM_EM0600_BLACKHOLE = 0x186,
    ATHIT_TYPE_EM_EM060A_GALAXY = 0x187,
    ATHIT_TYPE_EM_EM0300_ACID = 0x188,
    ATHIT_TYPE_PLEM_BARRIER = 0x189,
    ATHIT_TYPE_PLEM_DIE_BARRIER = 0x18a,
    ATHIT_TYPE_PLEM_TRAIN = 0x18b,
    ATHIT_TYPE_PLEM_BIGBALL = 0x18c,
    ATHIT_TYPE_PLEM_WATERPILLAR = 0x18d,
    ATHIT_TYPE_PLEM_WATERPILLARTOP = 0x18e,
    ATHIT_TYPE_PLEM_AXE = 0x18f,
    ATHIT_TYPE_PLEM_LASER = 0x190,
    ATHIT_TYPE_PLEM_QUAKE = 0x191,
    ATHIT_TYPE_PLEM_EM0070_BREAK = 0x192,
    ATHIT_TYPE_PLEM_EM0070_BIGBREAK = 0x193,
    ATHIT_TYPE_PLEM_DRAGON_ATK = 0x194,
    ATHIT_TYPE_PLEM_FAN = 0x195,
    ATHIT_TYPE_PLEM_METEOR = 0x196,
    ATHIT_TYPE_PLEM_PROMINENCE = 0x197,
    ATHIT_TYPE_PLEM_TRANSFORM_BALL = 0x198,
    ATHIT_TYPE_PLEM_EM00C0_PUNCH = 0x199,
    ATHIT_TYPE_PLEM_SHUTTER = 0x19a,
    ATHIT_TYPE_PLEM_EXPLOSION = 0x19b,
    ATHIT_TYPE_PLEM_FIREPILLAR = 0x19c,
    ATHIT_TYPE_PLEM_FIREPILLAR_BIG = 0x19d,
    ATHIT_TYPE_MAX = 0x19e,
};

enum /*cObj::*/eBeFlag {
    BE_TRANS = 0x1,
    BE_OBA_HIT = 0x2,
    BE_SCA_HIT = 0x4,
    BE_LOCKENABLE = 0x8,
    BE_GAMEOBJ = 0x10,
    BE_EM = 0x20,
    BE_WEPGET = 0x40,
    BE_SUSPEND = 0x80,
    BE_BREAK = 0x100,
    BE_INSCREEN_OUT = 0x200,
    BE_ALPHA_CHECK = 0x400,
    BE_SUSPEND_AT_EVENT = 0x800,
    BE_ROOMOBJ = 0x1000,
    BE_CHANGE_PRIO = 0x2000,
    BE_EVENT_CONTROL = 0x4000,
    BE_TRANS_IN_SCENARIO = 0x8000,
    BE_NO_REPLAY = 0x10000,
    BE_CAM_NO_LOCKON = 0x20000,
    BE_ENEMY_OBJ = 0x40000,
    BE_ACCESSORYMODEL = 0x80000,
    BE_ITEM = 0x100000,
    BE_BLOCK_CLOTH_RATE = 0x200000,
    BE_FACEOBJ = 0x400000,
    BE_INSCREEN_NO_CHECK = 0x800000,
};

enum ATHIT_TARGET /* int */
{
    ATHIT_TARGET_PL = 0x0,
    ATHIT_TARGET_EM = 0x1,
    ATHIT_TARGET_BM = 0x2,
    ATHIT_TARGET_BM_STRONG = 0x3,
    ATHIT_TARGET_PLEM = 0x4,
};

enum ID_COMBO_TYPE /* int */
{
    ID_COMBO_P = 0x0,
    ID_COMBO_PP = 0x1,
    ID_COMBO_PPP = 0x2,
    ID_COMBO_PPPP = 0x3,
    ID_COMBO_PPPPP = 0x4,
    ID_COMBO_PPPPPP = 0x5,
    ID_COMBO_KP = 0x6,
    ID_COMBO_KKP = 0x7,
    ID_COMBO_KKKP = 0x8,
    ID_COMBO_PKP = 0x9,
    ID_COMBO_PPKP = 0xa,
    ID_COMBO_PPKKP = 0xb,
    ID_COMBO_PPPKP = 0xc,
    ID_COMBO_PPPKKP = 0xd,
    ID_COMBO_PP_DPP = 0xe,
    ID_COMBO_PP_DPPP = 0xf,
    ID_COMBO_DP = 0x10,
    ID_COMBO_P_DP = 0x11,
    ID_COMBO_PP_DP = 0x12,
    ID_COMBO_PPP_DP = 0x13,
    ID_COMBO_PPPP_DP = 0x14,
    ID_COMBO_PPPPP_DP = 0x15,
    ID_COMBO_K_DP = 0x16,
    ID_COMBO_KK_DP = 0x17,
    ID_COMBO_KKK_DP = 0x18,
    ID_COMBO_PK_DP = 0x19,
    ID_COMBO_PPK_DP = 0x1a,
    ID_COMBO_PPKK_DP = 0x1b,
    ID_COMBO_PPPK_DP = 0x1c,
    ID_COMBO_PPPKK_DP = 0x1d,
    ID_COMBO_PP_DP_DP = 0x1e,
    ID_COMBO_PP_DPP_DP = 0x1f,
    ID_COMBO_K = 0x20,
    ID_COMBO_PK = 0x21,
    ID_COMBO_PPK = 0x22,
    ID_COMBO_PPPK = 0x23,
    ID_COMBO_PPPPK = 0x24,
    ID_COMBO_PPPPPK = 0x25,
    ID_COMBO_KK = 0x26,
    ID_COMBO_KKK = 0x27,
    ID_COMBO_KKKK = 0x28,
    ID_COMBO_PKK = 0x29,
    ID_COMBO_PPKK = 0x2a,
    ID_COMBO_PPKKK = 0x2b,
    ID_COMBO_PPPKK = 0x2c,
    ID_COMBO_PPPKKK = 0x2d,
    ID_COMBO_PP_DPK = 0x2e,
    ID_COMBO_PP_DPPK = 0x2f,
    ID_COMBO_DK = 0x30,
    ID_COMBO_P_DK = 0x31,
    ID_COMBO_PP_DK = 0x32,
    ID_COMBO_PPP_DK = 0x33,
    ID_COMBO_PPPP_DK = 0x34,
    ID_COMBO_PPPPP_DK = 0x35,
    ID_COMBO_K_DK = 0x36,
    ID_COMBO_KK_DK = 0x37,
    ID_COMBO_KKK_DK = 0x38,
    ID_COMBO_PK_DK = 0x39,
    ID_COMBO_PPK_DK = 0x3a,
    ID_COMBO_PPKK_DK = 0x3b,
    ID_COMBO_PPPK_DK = 0x3c,
    ID_COMBO_PPPKK_DK = 0x3d,
    ID_COMBO_PP_DP_DK = 0x3e,
    ID_COMBO_PP_DPP_DK = 0x3f,
    ID_COMBO_AIR_P = 0x40,
    ID_COMBO_AIR_PP = 0x41,
    ID_COMBO_AIR_PPP = 0x42,
    ID_COMBO_AIR_PPPP = 0x43,
    ID_COMBO_AIR_PPPPP = 0x44,
    ID_COMBO_AIR_PPPPPP = 0x45,
    ID_COMBO_AIR_KP = 0x46,
    ID_COMBO_AIR_KKP = 0x47,
    ID_COMBO_AIR_KKKP = 0x48,
    ID_COMBO_AIR_PKP = 0x49,
    ID_COMBO_AIR_PPKP = 0x4a,
    ID_COMBO_AIR_PPKKP = 0x4b,
    ID_COMBO_AIR_PPPKP = 0x4c,
    ID_COMBO_AIR_PPPKKP = 0x4d,
    ID_COMBO_AIR_PP_DPP = 0x4e,
    ID_COMBO_AIR_PP_DPPP = 0x4f,
    ID_COMBO_AIR_DP = 0x50,
    ID_COMBO_AIR_P_DP = 0x51,
    ID_COMBO_AIR_PP_DP = 0x52,
    ID_COMBO_AIR_PPP_DP = 0x53,
    ID_COMBO_AIR_PPPP_DP = 0x54,
    ID_COMBO_AIR_PPPPP_DP = 0x55,
    ID_COMBO_AIR_K_DP = 0x56,
    ID_COMBO_AIR_KK_DP = 0x57,
    ID_COMBO_AIR_KKK_DP = 0x58,
    ID_COMBO_AIR_PK_DP = 0x59,
    ID_COMBO_AIR_PPK_DP = 0x5a,
    ID_COMBO_AIR_PPKK_DP = 0x5b,
    ID_COMBO_AIR_PPPK_DP = 0x5c,
    ID_COMBO_AIR_PPPKK_DP = 0x5d,
    ID_COMBO_AIR_PP_DP_DP = 0x5e,
    ID_COMBO_AIR_PP_DPP_DP = 0x5f,
    ID_COMBO_AIR_K = 0x60,
    ID_COMBO_AIR_PK = 0x61,
    ID_COMBO_AIR_PPK = 0x62,
    ID_COMBO_AIR_PPPK = 0x63,
    ID_COMBO_AIR_PPPPK = 0x64,
    ID_COMBO_AIR_PPPPPK = 0x65,
    ID_COMBO_AIR_KK = 0x66,
    ID_COMBO_AIR_KKK = 0x67,
    ID_COMBO_AIR_KKKK = 0x68,
    ID_COMBO_AIR_PKK = 0x69,
    ID_COMBO_AIR_PPKK = 0x6a,
    ID_COMBO_AIR_PPKKK = 0x6b,
    ID_COMBO_AIR_PPPKK = 0x6c,
    ID_COMBO_AIR_PPPKKK = 0x6d,
    ID_COMBO_AIR_PP_DPK = 0x6e,
    ID_COMBO_AIR_PP_DPPK = 0x6f,
    ID_COMBO_AIR_DK = 0x70,
    ID_COMBO_AIR_P_DK = 0x71,
    ID_COMBO_AIR_PP_DK = 0x72,
    ID_COMBO_AIR_PPP_DK = 0x73,
    ID_COMBO_AIR_PPPP_DK = 0x74,
    ID_COMBO_AIR_PPPPP_DK = 0x75,
    ID_COMBO_AIR_K_DK = 0x76,
    ID_COMBO_AIR_KK_DK = 0x77,
    ID_COMBO_AIR_KKK_DK = 0x78,
    ID_COMBO_AIR_PK_DK = 0x79,
    ID_COMBO_AIR_PPK_DK = 0x7a,
    ID_COMBO_AIR_PPKK_DK = 0x7b,
    ID_COMBO_AIR_PPPK_DK = 0x7c,
    ID_COMBO_AIR_PPPKK_DK = 0x7d,
    ID_COMBO_AIR_PP_DP_DK = 0x7e,
    ID_COMBO_AIR_PP_DPP_DK = 0x7f,
    ID_COMBO_RP = 0x80,
    ID_COMBO_RK = 0x81,
    ID_COMBO_AIR_RP = 0x82,
    ID_COMBO_AIR_RK = 0x83,
    ID_COMBO_RB_P = 0x84,
    ID_COMBO_RB_K = 0x85,
    ID_COMBO_AIR_RB_P = 0x86,
    ID_COMBO_AIR_RB_K = 0x87,
    ID_COMBO_EX1 = 0x88,
    ID_COMBO_AIR_EX1 = 0x89,
    ID_COMBO_EX2 = 0x8a,
    ID_COMBO_EX3 = 0x8b,
    ID_COMBO_AIR_EX3 = 0x8c,
    ID_COMBO_EX4 = 0x8d,
    ID_COMBO_AIR_EX4 = 0x8e,
    ID_COMBO_EX5 = 0x8f,
    ID_COMBO_EX6 = 0x90,
    ID_COMBO_EX7 = 0x91,
    ID_COMBO_EX8 = 0x92,
    ID_COMBO_EX9 = 0x93,
    ID_COMBO_NUM = 0x94,
    ID_COMBO_INVALID = 0xffffffff,
};

#endif
