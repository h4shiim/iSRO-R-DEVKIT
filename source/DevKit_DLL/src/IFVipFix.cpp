#include "IFVipFix.h"
#include "ICharactor.h"
#include "GFX3DFunction/GFontTexture.h"
#include "ICPlayer.h"
#include "ICUser.h"

CICUser* pUser;
CICPlayer* m_pUser = (CICPlayer*)pUser;

float result = 0.0f;
const DWORD jmpAddressvipfix = 0x00b4317f;

void CharacterIcons::changeIconPosition() {

    if (m_pUser != NULL && (*(CGFontTexture*)((int)m_pUser + 0x1D4)).GetDimensions().width > 0) {
        BYTE hwanTitleLength = MEMUTIL_READ_BY_PTR_OFFSET(m_pUser, 0x258, BYTE);
        BYTE achievementTitleId = MEMUTIL_READ_BY_PTR_OFFSET(m_pUser, 0x95C, BYTE);

        result = m_pUser->m_renderY + (*(CGFontTexture*)((int)m_pUser + 0x1D4)).GetDimensions().width * 2.5;//width offset is 0x54

        if (m_pUser->GetJobType() > 0 && hwanTitleLength > 0 && achievementTitleId > 0) { //GetJobType() is 50 at vtable
            result += (*(CGFontTexture*)((int)m_pUser + 0x260)).GetDimensions().width * 1.5;//width offset is 0x54
        }

        if (achievementTitleId > 0) {
            result += (*(CGFontTexture*)((int)m_pUser + 0x164)).GetDimensions().width * 1.5;//width offset is 0x54
        }
        else if (hwanTitleLength > 0) {
            result += (*(CGFontTexture*)((int)m_pUser + 0x260)).GetDimensions().width * 1.5;//width offset is 0x54
        }

        result += 1.0;
    }
}


void CharacterIcons::SetPositionVipIcon() {
    __asm {
        // Store st(0) in the memory location specified by the stack pointer + 0xF0
        fstp result;
        mov ECX, ESI
        pushad;
        pushfd;
        call CharacterIcons::changeIconPosition;
        popfd;
        popad;

        // Load the double value from the memory location specified by the stack pointer + 0xF0
        fld result
            fstp dword ptr ss : [esp + 0xF0]
            jmp jmpAddressvipfix
    }
}



