#pragma once
#include <cstdint> // uintptr_t

#pragma pack(push, 1)
enum PlayerForm {
    Player = 0,
    Panther = 1,
    FirstPerson = 2,
    Bird = 3,
};
#pragma pack(pop)

struct Vec3 {
    float x; // 0x0
    float y; // 0x4
    float z; // 0x8
}; // Size: 0xc

#pragma pack(push, 1)
struct LaserSword {
    char pad_0[0x6cc];
    float buffDrainRate; // 0x6cc
    char pad_6d0[0x2c5c];
    float buffRemainingDuration; // 0x332c
    float length; // 0x3330
}; // Size: 0x3334
#pragma pack(pop)

#pragma pack(push, 1)
struct WickedWeave {
    char pad_0[0xf0];
    Vec3 scale; // 0xf0
}; // Size: 0xfc
#pragma pack(pop)

#pragma pack(push, 1)
struct BayoLimb {
    char pad_0[0x74];
    bool isShooting; // 0x74
    char pad_75[0x11a];
    bool endOfStruct; // 0x18f
}; // Size: 0x190
#pragma pack(pop)


#pragma pack(push, 1)
struct LocalPlayer {
    uintptr_t vtable; // 0x0
    char pad_4[0xcc];
    Vec3 pos; // 0xd0
    char pad_dc[0x14];
    Vec3 scale; // 0xf0
    char pad_fc[0x218];
    float camHeight; // 0x314
    char pad_318[0xc];
    float alpha; // 0x324
    char pad_328[0x24];
    int moveID; // 0x34c
    int movePart; // 0x350
    int invincibility; // 0x354
    int summoningSomething; // 0x358
    char pad_35c[0x88];
    float animFrame; // 0x3e4
    char pad_3e8[0x2b4];
    int aerial; // 0x69c
    char pad_6a0[0x14];
    int hpDamage; // 0x6b4
    char pad_6b8[0x14];
    float speed; // 0x6cc
    char pad_6d0[0x60];
    float iFramesRemaining; // 0x730
    char pad_734[0x58c];
    Vec3 colouredHairDurationRGB; // 0xcc0
    float colouredHairTimer; // 0xccc
    char pad_cd0[0x4ef0];
    LaserSword* laserSword; // 0x5bc0
    char pad_5bc4[0x8c688];
    uintptr_t bayoSkeleton; // 0x9224c
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
    char pad_6b8[0x5dc];
    float daze; // 0xc94
    float dazeMax; // 0xc98
    float dazeCurrentDuration; // 0xc9c
    float dazeMaxDurationProbably; // 0xca0
}; // Size: 0xca4
#pragma pack(pop)
