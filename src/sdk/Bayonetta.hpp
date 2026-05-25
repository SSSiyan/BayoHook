#pragma once
#include <cstdint> // uintptr_t

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
    char pad_35c[0x88];
    float animFrame; // 0x3E4
    char pad_3e8[0x3C];
    float animFrameMax; // 0x424
    char pad_428[0x9C];
    float speed; // 0x4C4
    char pad_4c8[0x1D4];   // 0x4C8
    int aerial;            // 0x69C
    char pad_6a0[0x14];
    int hpDamage; // 0x6b4
    char pad_6b8[0x14];
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
    int hp; // 0x93508
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
    char pad_937d4[0x230];
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
    int stringID; // 0x95c64
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

#pragma pack(push, 1)
struct Enemy {
    char pad_0[0xd0];
    Vec3 pos; // 0xd0
    char pad_dc[0x270];
    int moveID; // 0x34c
    char pad_350[0x94];
    float animFrame; // 0x3e4
    char pad_3e8[0x2cc];
    int hp; // 0x6b4
    int hpMax; // 0x6b8
    char pad_6bc[0x5d8];
    float daze; // 0xc94
    float dazeMax; // 0xc98
    float dazeCurrentDuration; // 0xc9c
    float dazeMaxDurationProbably; // 0xca0
}; // Size: 0xca4
#pragma pack(pop)
static_assert(sizeof(Enemy) == 0xca4);

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

static const char* moveIDNames[350]{
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

struct EntityInfo {
    const char* name;
    int id;
};

static const EntityInfo knownEntities[] = {
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
    {"Lustitia", 0x200D0},
    {"Lustitia Head", 0x200D1},
    {"Lustitia grower thing", 0x200D2},
    {"Lustitia Tentacle", 0x200D3},
    {"Lustitia Head w/Halo", 0x200D5},
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
    {"Angel Axe", 0x30108},
    {"Angel Shield", 0x3010A},
    {"Angel Flail", 0x3010D},
    {"Angel Clothes", 0x30110},
    {"Angel Mask", 0x30120},
    {"Grave & Glory Claws", 0x30126},
    {"Angel Scythe", 0x30150},
    {"Glory Claws", 0x30127},
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
    {"Lamp Post Weapon", 0x50189},
    {"Low-poly Angel Hitting the Floor", 0x501C4},
    {"Crystal Witch Statue Reforming", 0x50228},
    {"Crystal Sage Statue", 0x50229},
    {"R666 Bridge", 0x50340},
    {"R666 Road", 0x50388},
    {"Father Rodin Floor", 0x5F000},
    {"White Triangle", 0x60000},
    {"Unknown", 0x60001},
    {"Summon Hair Hell Hand", 0x60007},
    {"Portal VFX", 0x6000C},
    {"I didn't see anything spawn", 0x60011},
    {"Pulley's Butterfly Spawn", 0x60015},
    {"Queen Sheba Hair", 0x60069},
    {"Skybox maybe?", 0x600F4},
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
    {"Barrel", 0xC0301},
};

static const char* GetEntityName(int id) {
    for (const auto& e : knownEntities) {
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
    // {"Lustitia", 0x200D0, 0, 0},
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
    {{"Lustitia", 0x200D0, 0, 0}, SpawnCategory::EnemyBigBoss},
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

#endif
