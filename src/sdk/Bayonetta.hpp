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
    private: char pad_0[0x6cc]; public:
    float buffDrainRate; // 0x6cc
    private: char pad_6d0[0x2c5c]; public:
    float buffRemainingDuration; // 0x332c
    float length; // 0x3330
}; // Size: 0x3334
#pragma pack(pop)

#pragma pack(push, 1)
struct WickedWeave {
    private: char pad_0[0xf0]; public:
    Vec3 scale; // 0xf0
}; // Size: 0xfc
#pragma pack(pop)

#pragma pack(push, 1)
struct BayoLimb {
    private: char pad_0[0x74]; public:
    int isShooting; // 0x74
    private: char pad_78[0x117]; public:
    bool endOfStruct; // 0x18f
}; // Size: 0x190
#pragma pack(pop)

#pragma pack(push, 1)
struct localPlayer {
    uintptr_t vtable; // 0x0
    private: char pad_4[0xcc]; public:
    Vec3 pos; // 0xd0
    private: char pad_dc[0x14]; public:
    Vec3 scale; // 0xf0
    private: char pad_fc[0x218]; public:
    float camHeight; // 0x314
    private: char pad_318[0xc]; public:
    float alpha; // 0x324
    private: char pad_328[0x24]; public:
    int moveID; // 0x34c
    int movePart; // 0x350
    int playerInvuln; // 0x354
    int summoningSomething; // 0x358
    private: char pad_35c[0x88]; public:
    float animFrame; // 0x3e4
    private: char pad_3e8[0x2b4]; public:
    int playerAerial; // 0x69c
    private: char pad_6a0[0x14]; public:
    int hp; // 0x6b4
    private: char pad_6b8[0x14]; public:
    float speed; // 0x6cc
    private: char pad_6d0[0x60]; public:
    float iFramesRemaining; // 0x730
    private: char pad_734[0x58c]; public:
    Vec3 colouredHairDurationRGB; // 0xcc0
    float colouredHairTimer; // 0xccc
    private: char pad_cd0[0x4ef0]; public:
    LaserSword* laserSword; // 0x5bc0
    private: char pad_5bc4[0x8c688]; public:
    uintptr_t bayoSkeleton; // 0x9224c
    private: char pad_92250[0xeb4]; public:
    bool noClip; // 0x93104
    private: char pad_93105[0x417]; public:
    float birdTimer; // 0x9351c
    private: char pad_93520[0x58]; public:
    int wallJumpCount; // 0x93578
    private: char pad_9357c[0x10]; public:
    float divekickCount2; // 0x9358c
    private: char pad_93590[0x54]; public:
    int m_JoySpinCnt; // 0x935e4
    private: char pad_935e8[0x128]; public:
    uintptr_t summoningHair; // 0x93710
    uintptr_t summoningBody; // 0x93714
    private: char pad_93718[0xa8]; public:
    WickedWeave* handWeave; // 0x937c0
    WickedWeave* idkWeave1; // 0x937c4
    WickedWeave* idkWeave2; // 0x937c8
    WickedWeave* idkWeave3; // 0x937cc
    WickedWeave* legWeave; // 0x937d0
    private: char pad_937d4[0x230]; public:
    float m_RhythmTimer; // 0x93a04
    private: char pad_93a08[0x8]; public:
    int m_bRhythmActionSuccess; // 0x93a10
    private: char pad_93a14[0x8]; public:
    int m_RapidType; // 0x93a1c
    float m_RapidActRate; // 0x93a20
    float m_RapidActMinusTimer; // 0x93a24
    float m_RapidActMinusWait; // 0x93a28
    float m_RapidActMinusTimer2; // 0x93a2c
    private: char pad_93a30[0x90]; public:
    BayoLimb* rightHand; // 0x93ac0
    private: char pad_93ac4[0x18c]; public:
    BayoLimb* leftHand; // 0x93c50
    private: char pad_93c54[0x18c]; public:
    BayoLimb* leftLeg; // 0x93de0
    private: char pad_93de4[0x9b0]; public:
    int dodgeCount; // 0x94794
    private: char pad_94798[0xe0]; public:
    float batWithinFrames; // 0x94878
    private: char pad_9487c[0x214]; public:
    int clothesRelated3; // 0x94a90
    int clothesRelated2; // 0x94a94
    private: char pad_94a98[0xac]; public:
    int inputsHold; // 0x94b44
    int inputsDown; // 0x94b48
    int inputsUp; // 0x94b4c
    private: char pad_94b50[0xb0]; public:
    int hideEverythingInCutscene; // 0x94c00
    private: char pad_94c04[0x1060]; public:
    int stringID; // 0x95c64
    private: char pad_95c68[0x18]; public:
    float comboTimer; // 0x95c80
    private: char pad_95c84[0x8]; public:
    bool isWhipSlap; // 0x95c8c
    private: char pad_95c8d[0x7]; public:
    int comboHit[7]; // 0x95c94
    private: char pad_95cb0[0xc]; public:
    int playerAttackCount; // 0x95cbc
    private: char pad_95cc0[0x9c]; public:
    float witchTimeDuration; // 0x95d5c
    float witchTimeMaxProbably; // 0x95d60
    private: char pad_95d64[0x24]; public:
    int qteThing; // 0x95d88
    private: char pad_95d8c[0x148]; public:
    bool walkOnWalls; // 0x95ed4
    private: char pad_95ed5[0x33]; public:
    int clothesRelated4; // 0x95f08
    private: char pad_95f0c[0xc]; public:
    int walkOnWallsEffect; // 0x95f18
    private: char pad_95f1c[0xa8]; public:
    int walkOnWallsRelated; // 0x95fc4
    private: char pad_95fc8[0x368]; public:
    int clothesTransformation; // 0x96330
    float clothesTransformationTimer; // 0x96334
    int cutsceneToggleMaybe; // 0x96338
    private: char pad_9633c[0x294]; public:
    int facePlate; // 0x965d0
    private: char pad_965d4[0x550]; public:
    PlayerForm form; // 0x96b24
    private: char pad_96b28[0xc]; public:
    int enemyCount; // 0x96b34
    int clothesColourRGB; // 0x96b38
    private: char pad_96b3c[0xc4]; public:
    Vec3 colouredHairIntensityRGB; // 0x96c00
}; // Size: 0x96c0c
#pragma pack(pop)
