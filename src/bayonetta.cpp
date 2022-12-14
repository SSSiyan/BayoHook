#include "bayonetta.h"
#include "gamehook.hpp"

struct bayoAttachPoint_t {
    int sourceBoneIndex;
    int targetBoneIndex;
    int option;
};

static inline int
bayoActor_loadATT(void* actor, void* attHandle) {
    int numAttachPoints;
    struct bayoAttachPoint_t* pAttachPoints;
    int i;

    if (!attHandle || *(int*)attHandle <= 0)
        return 0;

    numAttachPoints = *(int*)attHandle;
    pAttachPoints = (struct bayoAttachPoint_t*)
        ((int*)attHandle + 1);

    ((int (__thiscall *)(void*, int, uintptr_t))GameHook::bayoActor_allocInitAttachPointsAddress)(
        actor,
        numAttachPoints,
        GameHook::HeapSCNAddress);
    for (i = 0; i < numAttachPoints; i++) {
        ((void (__thiscall*)(void*, int, int, int))GameHook::bayoActor_attachBoneAddress)(
            actor,
            pAttachPoints[i].sourceBoneIndex,
            pAttachPoints[i].targetBoneIndex,
            pAttachPoints[i].option);
    }
    return 1;
}

int __stdcall
bayoPl0012_loadATT(void* actor) {
    void * attHandle = ((void* (__cdecl*)(const char *))GameHook::bayo_getAssetHandleAddress)(
        "pl0012.dat\\pl0012.att");
    return bayoActor_loadATT(actor, attHandle);
}