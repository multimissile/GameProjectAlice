#include "stdafx.h"
#include "cUITest.h"
#include "cSpriteImage.h"
#include "cBox.h"


cUITest::cUITest()
//	:m_pSpriteImage(NULL)
//	,m_ptitlePlayerMenu_I4A(NULL)
//	,m_ptitlePlayerMenu_I4C(NULL)
//	,m_ptitlePlayerMenu_I4F(NULL)
//	,m_pBox(NULL)
//	, m_pBox2(NULL)
//	, m_pBox3(NULL)
{	
}

cUITest::~cUITest()
{
//	SAFE_DELETE(m_pSpriteImage);
//	SAFE_DELETE(m_ptitlePlayerMenu_I4A);
//	SAFE_DELETE(m_ptitlePlayerMenu_I4C);
//	SAFE_DELETE(m_ptitlePlayerMenu_I4F);
//	SAFE_DELETE(m_pBox);
//	SAFE_DELETE(m_pBox2);
//	SAFE_DELETE(m_pBox3);
}

void cUITest::Setup()
{
//	m_pSpriteImage = new cSpriteImage("TestFolder", "titlePlayerMenu_I39_.png");
//	m_ptitlePlayerMenu_I4A = new cSpriteImage("TestFolder", "titlePlayerMenu_I4A.tga");
//	m_ptitlePlayerMenu_I4C = new cSpriteImage("TestFolder", "titlePlayerMenu_I4C.tga");
//	m_ptitlePlayerMenu_I4F = new cSpriteImage("TestFolder", "titlePlayerMenu_I4F.tga");
//
//	RECT rc;
//	GetClientRect(g_hWnd, &rc);
//
//
//	float x, y;
//	x =(rc.right - rc.left) /2.f ;
//	y =((rc.bottom - rc.top)/5.f )* 4.f;
//	//x = ((rc.right - rc.left) / 8.f) *7.f;
//	//y = ((rc.bottom - rc.top) / 5.f)* 1.f;
//
//
//	m_pBox = new cBox((float)m_ptitlePlayerMenu_I4A->GetImageWidth(), (float)m_ptitlePlayerMenu_I4A->GetImageHeight(),
//		D3DXVECTOR3(-7.f, -24.f, 0), D3DXVECTOR3(x, y, 0));
//
//	m_pBox2 = new cBox((float)m_ptitlePlayerMenu_I4C->GetImageWidth(), (float)m_ptitlePlayerMenu_I4C->GetImageHeight(),
//		D3DXVECTOR3(-5.f, -7.f, 0), D3DXVECTOR3(x, y, 0));
//	
//	m_pBox3 = new cBox((float)m_ptitlePlayerMenu_I4F->GetImageWidth(), (float)m_ptitlePlayerMenu_I4F->GetImageHeight(),
//		D3DXVECTOR3(-68.f, -62.f, 0), D3DXVECTOR3(x, y, 0));
//
//
//	m_pBox4 = new cBox((float)m_pSpriteImage->GetImageWidth(), (float)m_pSpriteImage->GetImageHeight(),rc);
//
}



void cUITest::Update()
{
	
}

void cUITest::Render(LPD3DXSPRITE pSprite)
{
//	D3DXMATRIX matWorld;
//	D3DXMatrixIdentity(&matWorld);
//
//	m_pSpriteImage->Render(pSprite, m_pBox4->GetWorldMatrix());
//
//	//D3DXMATRIX matParentWorld;
//	//D3DXMatrixRotationZ(&matParentWorld, 0.8f);
//	//m_pBox->SetParentWorld(&matParentWorld);
//	//matWorld = m_pBox->GetWorldMatrix();
//
//	//RECT rc;
//	//GetClientRect(g_hWnd, &rc);
//	//D3DXMatrixTranslation(&matWorld, (rc.right - rc.left) / 2.f, (rc.bottom - rc.top) / 2.f, 0);
//	static float z = 0.f;
//	z += 0.01f;
//
//	m_pBox->m_fRotationZ = z;
//	m_pBox2->m_fRotationZ = z/100  ;
//
//	m_ptitlePlayerMenu_I4C->Render(pSprite, m_pBox->GetWorldMatrix(),&m_pBox->GetOrgPosition());
//	m_ptitlePlayerMenu_I4F->Render(pSprite, m_pBox2->GetWorldMatrix(), &m_pBox2->GetOrgPosition());
//	m_ptitlePlayerMenu_I4A->Render(pSprite, m_pBox3->GetWorldMatrix(), &m_pBox3->GetOrgPosition());
//	
//
//

}
