#pragma once

#define g_pSPrintDevice cSPrintDevice::GetInstance()



class cSPrintDevice
{
	SINGLETON(cSPrintDevice);
	
	SYNTHESIZE(FONT_STYLE, m_eFontStyle, FontStyle);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwColor, Color);

public:

	//void SetColor(D3DCOLOR c);
	////void Set
	//
	void PrintStr(LPD3DXSPRITE& pSprite,string& str, RECT& rc);
	void PrintStr(LPD3DXSPRITE& pSprite, const char* str, RECT& rc);
	void PrintStr(LPD3DXSPRITE& pSprite, const char* str, float x, float y, float width, float height);
	void PrintStr(LPD3DXSPRITE& pSprite, string& str, float x, float y, float width, float height);



};

