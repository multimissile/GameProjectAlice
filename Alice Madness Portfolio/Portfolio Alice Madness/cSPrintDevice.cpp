#include "stdafx.h"
#include "cSPrintDevice.h"


cSPrintDevice::cSPrintDevice()
{

	m_eFontStyle = FONT_GULIM_25;
	m_dwColor = D3DCOLOR_XRGB(0, 0, 0);
	m_dwDrawTextFormat = DT_CENTER;
}
//포맷 타입
//#define DT_TOP                      0x00000000
//#define DT_LEFT                     0x00000000
//#define DT_CENTER                   0x00000001
//#define DT_RIGHT                    0x00000002
//#define DT_VCENTER                  0x00000004
//#define DT_BOTTOM                   0x00000008
//#define DT_WORDBREAK                0x00000010
//#define DT_SINGLELINE               0x00000020
//#define DT_EXPANDTABS               0x00000040
//#define DT_TABSTOP                  0x00000080
//#define DT_NOCLIP                   0x00000100
//#define DT_EXTERNALLEADING          0x00000200
//#define DT_CALCRECT                 0x00000400
//#define DT_NOPREFIX                 0x00000800
//#define DT_INTERNAL                 0x00001000
//
//#if(WINVER >= 0x0400)
//#define DT_EDITCONTROL              0x00002000
//#define DT_PATH_ELLIPSIS            0x00004000
//#define DT_END_ELLIPSIS             0x00008000
//#define DT_MODIFYSTRING             0x00010000
//#define DT_RTLREADING               0x00020000
//#define DT_WORD_ELLIPSIS            0x00040000
//#if(WINVER >= 0x0500)
//#define DT_NOFULLWIDTHCHARBREAK     0x00080000
//#if(_WIN32_WINNT >= 0x0500)
//#define DT_HIDEPREFIX               0x00100000
//#define DT_PREFIXONLY               0x00200000
//#endif /* _WIN32_WINNT >= 0x0500 */
//#endif /* WINVER >= 0x0500 */
//


cSPrintDevice::~cSPrintDevice()
{
	
}

void cSPrintDevice::PrintStr(LPD3DXSPRITE& pSprite, string& str, RECT& rc)
{
	PrintStr(pSprite, str.c_str(),rc);


}

void cSPrintDevice::PrintStr(LPD3DXSPRITE& pSprite, const char * str, RECT& rc)
{

	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontStyle);

	pFont->DrawText(NULL,
		str,
		strlen(str),
		&rc,
		m_dwDrawTextFormat,
		m_dwColor);
}

void cSPrintDevice::PrintStr(LPD3DXSPRITE& pSprite, const char * str, float x, float y, float width, float height)
{
	RECT rc = { x , y, x + width,y + height };

	PrintStr(pSprite, str, rc);
}

void cSPrintDevice::PrintStr(LPD3DXSPRITE& pSprite, string& str, float x, float y, float width, float height)
{
	RECT rc = { x , y, x + width,y + height };
	PrintStr(pSprite, str.c_str(), rc);
}
