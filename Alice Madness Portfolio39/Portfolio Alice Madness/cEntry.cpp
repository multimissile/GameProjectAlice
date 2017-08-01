#include "stdafx.h"
#include "cEntry.h"
#include "cSpriteImage.h"

cEntry::cEntry()
	:m_pBackGround(NULL)
	,m_pLogo(NULL)
{
}


cEntry::~cEntry()
{
	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pBackGround);
}

void cEntry::Setup()
{
	m_pBackGround = new cSpriteImage("Source/Main", "titlePlayerMenu_I47_.tga");
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pBackGround->SetPosSclRect(rc);


	m_pLogo = new cSpriteImage("Source/Main", "titlePlayerMenu_I53.tga");

	D3DXVECTOR3 v((rc.right - rc.left - m_pLogo->GetImageWidth()) / 2.f, 200.f, 0.f);
	m_pLogo->SetPosition(v);


}

void cEntry::Update()
{


}

void cEntry::Render()
{
	//ui1
	m_pBackGround->Render();
	//ui2
	m_pLogo->Render();

	//ÅØ½ºÆ®·»´õ
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	rc.top = (rc.bottom - rc.top) / 3.f * 2.f;

	g_pSPrintDevice->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	g_pSPrintDevice->PrintStr( "Enter", rc);
}
