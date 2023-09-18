#include "IFVipFix.h"
#include "GFX3DFunction/GFontTexture.h"
#include "ICUser.h"



double result = 0.0;
CICUser *m_pUser = NULL;
const DWORD jmpAddress = 0x00B43112;

void changeIconPosition() {

    if (m_pUser != NULL && (*(CGFontTexture *) ((int) m_pUser + 0x1D4)).GetDimensions().width > 0) {
        BYTE hwanTitleLength = MEMUTIL_READ_BY_PTR_OFFSET(m_pUser, 0x258, BYTE);
        BYTE achievementTitleId = MEMUTIL_READ_BY_PTR_OFFSET(m_pUser, 0x95C, BYTE);

        result = m_pUser->m_renderY + (*(CGFontTexture *) ((int) m_pUser + 0x1D4)).GetDimensions().width * 0.5;//width offset is 0x54

        if (m_pUser->GetJobType() && hwanTitleLength > 0 && achievementTitleId > 0) {          //GetJobType() is 50 at vtable
            result += (*(CGFontTexture *) ((int) m_pUser + 0x260)).GetDimensions().width * 0.5;//width offset is 0x54
        }

        if (achievementTitleId > 0) {
            result += (*(CGFontTexture *) ((int) m_pUser + 0x164)).GetDimensions().width * 0.5;//width offset is 0x54
        } else if (hwanTitleLength > 0) {
            result += (*(CGFontTexture *) ((int) m_pUser + 0x260)).GetDimensions().width * 0.5;//width offset is 0x54
        }

        result += 3.0;
    }
}


void __declspec(naked) SetPositionVipIcon() {
    __asm {
        // Store st(0) in the memory location specified by the stack pointer + 0xF0
        fstp result;
        mov m_pUser, ESI

        pushad;
        pushfd;
        call changeIconPosition;
        popfd;
        popad;

        // Load the double value from the memory location specified by the stack pointer + 0xF0
        fld result
        fstp dword ptr ss:[esp+0xF0]
        jmp jmpAddress
    }
}


