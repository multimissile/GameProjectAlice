#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
//#include "cCameraTest.h"
#include "cWonderLand.h"
#include "cEntry.h"
#include "cMain.h"


cMainGame::cMainGame()
	:m_pSprite(NULL)
	,m_pGrid(NULL)
	,m_pCamera(NULL)
	//,m_pCameraTest(NULL)
	,m_pWonderLand(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	//SAFE_DELETE(m_pCameraTest);

	for each(auto p  in m_vecScene)
	{
		SAFE_DELETE(p);
	}


	g_pDeviceManager->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pMeshGroupManager->Destroy();
	g_pFontManager->Destroy();


}

void cMainGame::Setup()
{
	g_pSPrintDevice->SetFontStyle(FONT_DAEHAN_40_B);
	//sprite 만들기
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	//조명켜기
	SetLight();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	/*m_pCameraTest = new cCameraTest;
	m_pCameraTest->Setup(m_pCamera);*/

	

	m_vecScene.push_back(new cEntry);
	m_vecScene.back()->Setup();
	m_vecScene.push_back(new cMain);
	m_vecScene.back()->Setup();
	m_vecScene.push_back(new cWonderLand);
	m_vecScene.back()->Setup();

	m_pWonderLand = new cWonderLand;
	m_pWonderLand->Setup(m_pCamera);

	nCur = 0;
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (g_pKeyManager->IsOnceKeyDown(VK_RETURN))
		nCur == m_vecScene.size() - 1 ? nCur = 0 : nCur++;


	//m_pCameraTest->Update();
	m_pWonderLand->Update();
	//m_vecScene[nCur]->Update();
}

void cMainGame::Render()
{
	//채운다
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(255,255,255,255),1.f,0);

	//그리기시작
	g_pD3DDevice->BeginScene();
	


	//m_pCameraTest->Render(m_pSprite);
	m_pWonderLand->Render(m_pSprite);
	
	
	//if (m_pGrid)
	//	m_pGrid->Render();

//	m_vecScene[nCur]->Render(m_pSprite);


	g_pSPrintDevice->SetColor(D3DCOLOR_XRGB(20, 255, 29));
	char str[100];
	sprintf(str, "%d", g_pTimeManager->GetFPS());
	g_pSPrintDevice->PrintStr(m_pSprite, str, 100, 100, 100, 100);

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
