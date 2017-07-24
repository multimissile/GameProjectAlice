#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(FONT_STYLE style)
{
	if (m_mapFont.find(style) == m_mapFont.end())
	{

		//폰트 생성
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

		switch (style)
		{
		case FONT_GULIM_25:
		{
			fd.Height = 25;
			fd.Width = 12;
			fd.Weight = FW_BOLD;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "굴림체");	//글꼴 스타일
											//AddFontResource("umberto.ttf");
											//strcpy(fd.FaceName, "umberto");
		}	break;
		case FONT_DAEHAN_40_B:
		{
			fd.Height = 40;
			fd.Width = 18;
			fd.Weight = FW_MEDIUM;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			//strcpy_s(fd.FaceName, "굴림체");	//글꼴 스타일
			AddFontResource("DaehanB.ttf");
			strcpy(fd.FaceName, "DaehanB");
		}	break;
		
		
		}

		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[style]);

	}

	return m_mapFont[style];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}
