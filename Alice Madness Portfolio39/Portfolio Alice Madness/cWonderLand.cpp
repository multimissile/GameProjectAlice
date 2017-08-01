#include "stdafx.h"
#include "cWonderLand.h"
#include "cPlayer.h"

cWonderLand::cWonderLand()
//	m_pPlayer(NULL)	
//초기화
{
//	m_pImage = NULL;
//	m_vEye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_vLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_vRot = D3DXVECTOR3(-0.6f, 0.4f, 0.0f);
//	m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_fCameraDistance = 30.0f;
//	m_pMap = NULL;
//	//m_pMapTest = NULL;
//	m_pCamera = NULL;
//	m_pCameraMesh = NULL;

}


cWonderLand::~cWonderLand()
{
//	SAFE_DELETE(m_pPlayer);
//	//SAFE_DELETE(m_pMapTest);
//	SAFE_DELETE(m_pMap);
//	//SAFE_DELETE(m_pBox);
//	SAFE_DELETE(m_pImage);
//	SAFE_DELETE(m_pCameraMesh);
//	
//	for each(auto p  in vecPchar)
//	{
//		SAFE_DELETE(p);
//	}
	g_pGameManager->DestroyGame();
}

void cWonderLand::Setup()
{
	g_pGameManager->LoadGame(NULL, NULL);
}

//void cWonderLand::Setup(cCamera* pCamera)
//{
//	m_pCameraMesh = g_pMeshGroupManager->GetMeshGroupX("TestFolder", "Camera_view_2.X", MESH_OBJECT);
//
//	m_pCamera = pCamera;
//	
//	RECT rc;
//	GetClientRect(g_hWnd, &rc);
//	rc.left = (rc.right - rc.left) / 2.f;
//	rc.top = (rc.bottom - rc.top) / 2.f;
//
//
//
//	m_pImage = new cSpriteImage("TestFolder", "FriendsAndFoes_I3C_alpha2.tga");
//	//m_pBox = new cBox(m_pImage->GetImageWidth(), m_pImage->GetImageHeight(), rc);
//
//	m_pImage->SetPosSclRect(rc);
//
//	m_pPlayer = new cPlayer;
//	m_pPlayer->Setup();
//	m_pPlayer->SetCamera(m_pCamera);
//
//	
//	vecPchar.push_back(m_pPlayer);
//	
//	cHeightMap* pMap = new cHeightMap;
//	pMap->Setup("TestFolder", "HeightMap.raw", "MossRock_Tile_DM.tga");
//	m_pMap = pMap;
//
//	//카메라가 캐릭터 따라감
//	m_pCamera->Setup(&m_pPlayer->GetPosition());
//}

void cWonderLand::Update()
{
	g_pGameManager->Update();
//	if (!vecPchar.empty()) {
//		for each(auto p  in vecPchar)
//		{
//			p->Update(m_pMap);
//		}
//	}
//	//ControlCamera();
//
//
//	//회전시키고, 거리만큼 이동시킨뒤 ,lookat 에서떨어진위치
//	D3DXMATRIX matRY;
//	D3DXMATRIX matRX;
//	D3DXMatrixRotationX(&matRX, m_vRot.x);
//	D3DXMatrixRotationY(&matRY, m_vRot.y);
//
//	D3DXVec3TransformCoord(&m_vEye, &D3DXVECTOR3(0, 0, 1), &(matRX * matRY));
//
//	m_vEye *= m_fCameraDistance;
//
//	m_vEye += m_vLookAt;		//이것이 눈위치
//
//
//
}

void cWonderLand::Render()
{
	g_pGameManager->Render();
	////여기에 뷰행렬을 변환하고, 카메라행렬도 변환한뒤, 애들을 한번더 그려준다.
	//
	////원래의 변환을 얻어놓고
	//D3DVIEWPORT9 orgViewPort;
	//g_pD3DDevice->GetViewport(&orgViewPort);
	//
	//RECT rc = m_pImage->GetPosSclRect();
	//D3DVIEWPORT9 viewPort = { rc.left,rc.top,rc.right - rc.left , rc.bottom - rc.top ,0,1 };
	////새로운변환설정
	//g_pD3DDevice->SetViewport(&viewPort);
	//
	//D3DXMATRIX orgView;
	//D3DXMATRIX view;
	//
	////
	//
	//D3DXMatrixLookAtLH(&view, &m_vEye, &m_vLookAt, &m_vUp);
	//
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &orgView);
	//g_pD3DDevice->SetTransform(D3DTS_VIEW, &view);
	//if (m_pCamera)
	//	RenderCamera();
	//if (!vecPchar.empty()) {
	//	for each(auto p  in vecPchar)
	//	{
	//		p->Render();
	//	}
	//}
	//if (m_pMap)
	//	m_pMap->Render();
	///*if (m_pMapTest)
	//	m_pMapTest->Render();*/
	//
	////복구
	//g_pD3DDevice->SetViewport(&orgViewPort);
	//g_pD3DDevice->SetTransform(D3DTS_VIEW, &orgView);
	////스프라이트가 먼저 그려지면 투명도가 적용되지 않는다 따라서 얘네들은 투명도가 적용되게 그려놓고
	////나머지 애들은 투명도 제한다.
	//m_pImage->Render();
	//
	//
	//if (!vecPchar.empty()) {
	//	for each(auto p  in vecPchar)
	//	{
	//		p->Render();
	//	}
	//}
	//if (m_pMap)
	//	m_pMap->Render();
	///*if (m_pMapTest)
	//	m_pMapTest->Render();*/


}
//
//void cWonderLand::ControlCamera()
//{
//	if (g_pKeyManager->IsStayKeyDown(VK_HOME))
//	{
//		m_fCameraDistance -= 0.2f;
//		if (m_fCameraDistance < 0.1f)
//			m_fCameraDistance = 0.1f;
//	}
//	else if (g_pKeyManager->IsStayKeyDown(VK_END))
//	{
//		m_fCameraDistance += 0.2f;
//		if (m_fCameraDistance > 80.f)
//			m_fCameraDistance = 80.f;
//	}
//	if (g_pKeyManager->IsStayKeyDown(VK_DOWN))
//	{
//		m_vRot.x -= 0.01f;
//		if (m_vRot.x < 0)
//			m_vRot.x += D3DX_PI * 2;
//	}
//	else if (g_pKeyManager->IsStayKeyDown(VK_UP))
//	{
//		m_vRot.x += 0.01f;
//		if (m_vRot.x > D3DX_PI * 2)
//			m_vRot.x -= D3DX_PI * 2;
//	}
//
//	if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
//	{
//		m_vRot.y -= 0.01f;
//		if (m_vRot.y < 0)
//			m_vRot.y += D3DX_PI * 2;
//	}
//	else if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
//	{
//		m_vRot.y += 0.01f;
//		if (m_vRot.y > D3DX_PI * 2)
//			m_vRot.y -= D3DX_PI * 2;
//	}
//
//	if (g_pKeyManager->IsStayKeyDown('P'))
//	{
//		m_vLookAt.y += 0.03f;
//		if (m_vLookAt.y > 20.f)
//			m_vLookAt.y = 20.f;
//	}
//	else if (g_pKeyManager->IsStayKeyDown('L'))
//
//	{
//		m_vLookAt.y -= 0.03f;
//		if (m_vLookAt.y < -10.f)
//			m_vLookAt.y = -10.f;
//	}
//
//
//
//}
//
//void cWonderLand::RenderCamera()
//{
//	if (!m_pCamera)
//		return;
//
//	D3DXMATRIX matS;
//	D3DXMatrixScaling(&matS, 0.8f, 0.8f, 0.8f);
//
//
//
//	m_pCameraMesh->Render(&(matS *m_pCamera->GetMatCameraWorld()));
//
//
//
//}
//