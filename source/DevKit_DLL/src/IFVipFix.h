#ifndef SRO_DEVKIT_VIPFIX_H
#define SRO_DEVKIT_VIPFIX_H

#pragma once
#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) (*(type*)((char*)(ptr) + (offset)))
#include "ICPlayer.h"
#include "memory/hook.h"
class CharacterIcons {
public:
    CharacterIcons();

    void changeIconPosition();
    void SetPositionVipIcon();
    static void SetupHook();

};

#endif // SRO_DEVKIT_VIPFIX_H
