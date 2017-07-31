#include "stdafx.h"
#include "cMain.h"
#include "cSkinnedMesh.h"
#include "cSpriteImage.h"
#include "cMeshGroup.h"
cMain::cMain()
	:m_pAlice(NULL)
	, m_pMenuLine(NULL)
	,m_pBackGround(NULL)
{
}


cMain::~cMain()
{
	SAFE_DELETE(m_pAlice);
	SAFE_DELETE(m_pMenuLine);
	SAFE_DELETE(m_pBackGround);
}

void cMain::Setup()
{
	//카메라설정해주어야함 


	m_pAlice = new cSkinnedMesh("TestFolder", "alice.X");
	m_pAlice->SetAnimationIndexBlend(22);

	m_pMenuLine = new cSpriteImage("Source/Main", "titlePlayerMenu_I88.tga");
	RECT rc, rc2;
	GetClientRect(g_hWnd, &rc);
	
	rc2.left = (rc.right - rc.left) / 2.f;  //: 가운데
	rc2.top = (rc.bottom - rc.top) / 4.f *1.f; // : 위
	rc2.bottom = (rc.bottom - rc.top) / 4.f *3.f;
	rc2.right = rc2.left + (rc2.left / 7.f);
	m_pMenuLine->SetPosSclRect(rc2);

	//빌
//	m_pBackGround = g_pMeshGroupManager->GetMeshGroupX("Source/Main", "Main_Plane_2.X", MESH_OBJECT);

}

void cMain::Update()
{
	
}

void cMain::Render()
{

	//x축 90도 회전

	D3DXMATRIXA16 matRZ, matRY;
	D3DXMatrixRotationZ(&matRZ, D3DX_PI);
	//D3DXMatrixRotationY(&matRY, D3DX_PI / 2.f);

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pBackGround->Render(&(matRZ));// , matRY));

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	//배경렌더

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -4.f, 0, 0);
	D3DXMATRIXA16 matWorld = matS * matT;
	m_pAlice->SetTransform(&matWorld);
	m_pAlice->UpdateAndRender();




	//, UI 렌더

	m_pMenuLine->Render();



}
