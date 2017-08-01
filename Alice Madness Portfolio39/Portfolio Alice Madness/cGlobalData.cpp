#include "stdafx.h"
#include "cGlobalData.h"


cGlobalData::cGlobalData()
	:m_nToothNum(0)
{
}


cGlobalData::~cGlobalData()
{
}

void cGlobalData::TestRender()
{
	char str[100];
	sprintf(str, "tooth: %d", m_nToothNum);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	g_pSPrintDevice->PrintStr(str, rc.right - 300, 50, 300, 200);

}
