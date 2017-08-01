#pragma once

#define g_pFontManager cFontManager::GetInstance()

enum FONT_STYLE
{
	FONT_GULIM_25,
	FONT_DAEHAN_40_B,
	FONT_NUM
};

class cFontManager
{
	SINGLETON(cFontManager);
public:

private:
	map<FONT_STYLE, LPD3DXFONT> m_mapFont;

public:

	LPD3DXFONT GetFont(FONT_STYLE style);
	void Destroy();
};

