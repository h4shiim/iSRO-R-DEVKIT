#ifndef SRO_DEVKIT_VIPFIX_H
#define SRO_DEVKIT_VIPFIX_H

#pragma once
#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
    *(type *) (((uintptr_t) ptr) + offset)



void changeIconPosition();
void SetPositionVipIcon();

#endif // SRO_DEVKIT_VIPFIX_H
