#include "stdafx.h"
#include "cMainGame.h"
#include "c170720Test2.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCharacterTest.h"
#include "cUITest.h"

cMainGame::cMainGame()
	:m_pSprite(NULL)
	//,m_pTest(NULL)
	,m_pGrid(NULL)
	,m_pCamera(NULL)
	,m_pCharacterTest(NULL)
	, m_pUITest(NULL)
	, m_enCurrent(SCN_1)
{
}


cMainGame::~cMainGame()
{
	SAFE_RELEASE(m_pSprite);
	//SAFE_DELETE(m_pTest);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCharacterTest);
	SAFE_DELETE(m_pUITest);


	g_pDeviceManager->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
}

void cMainGame::Setup()
{

	//sprite 만들기
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	//조명켜기
	SetLight();

	//m_pTest = new c170720Test2;
	//m_pTest->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pCharacterTest = new cCharacterTest;
	m_pCharacterTest->Setup();

	m_pUITest = new cUITest;
	m_pUITest->Setup();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (g_pKeyManager->IsOnceKeyDown(VK_RETURN))
	{
		m_enCurrent = (SCENE)(m_enCurrent + 1);
		if (m_enCurrent == SCN_NUM)
			m_enCurrent = SCN_1;

	}

	switch (m_enCurrent)
	{
	case SCN_1:
	{
		if (m_pUITest)
			m_pUITest->Update();
	}
		break;
	case SCN_2:
	{
		if (m_pCharacterTest)
			m_pCharacterTest->Update();
	}
		break;
	}

	//if (m_pTest)
	//	m_pTest->Update();




}

void cMainGame::Render()
{
	//채운다
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(255,255,255,255),1.f,0);

	//그리기시작
	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();
	
	//if (m_pTest)
	//	m_pTest->Render();

	switch (m_enCurrent)
	{
	case SCN_1:
	{
		if (m_pUITest)
			m_pUITest->Render(m_pSprite);
	}
	break;
	case SCN_2:
	{
		if (m_pCharacterTest)
			m_pCharacterTest->Render();
	}
	break;
	}

	//D3DXMATRIX matWorld;
	//D3DXMatrixScaling(&matWorld, 0.05f, 0.05f, 0.05f);


	//
	//


	//그리기종료
	g_pD3DDevice->EndScene();

	//후면버퍼와 체인지
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
		
	}

}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);

	stLight.Direction = *D3DXVec3Normalize(&D3DXVECTOR3(), &D3DXVECTOR3(1, -1, 1));

	//라이트 구조체 정의
	g_pD3DDevice->SetLight(0, &stLight);
	//라이트를 사용할 수 있도록 한다.
	g_pD3DDevice->LightEnable(0, true);


}
