#include "stdafx.h"
#include "cCameraTest.h"
//#include "cBox.h"
#include "cSpriteImage.h"
#include "cCharacterTest.h"
#include "cMapTest.h"
#include "cCamera.h"
#include "cMeshGroup.h"


cCameraTest::cCameraTest()
	:// m_pBox(NULL)
	 m_pImage(NULL)
	, m_vEye(0, 0, 0)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vRot(-0.6f,0.4f,0)
	,m_fCameraDistance(30.f)
	,m_pMapTest(NULL)
	,m_pCharacterTest(NULL)
	, m_pCamera(NULL)
	, m_pCameraMesh(NULL)
{
}


cCameraTest::~cCameraTest()
{
	SAFE_DELETE(m_pCharacterTest);
	SAFE_DELETE(m_pMapTest);
	//SAFE_DELETE(m_pBox);
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pCameraMesh);

}

void cCameraTest::Setup(cCamera* pCamera)
{
	m_pCameraMesh = g_pMeshGroupManager->GetMeshGroupX("TestFolder", "Camera_view_2.X", MESH_OBJECT);

	m_pCamera = pCamera;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	rc.left = (rc.right - rc.left) / 2.f;
	rc.top = (rc.bottom - rc.top) / 2.f;

	

	m_pImage = new cSpriteImage("TestFolder", "FriendsAndFoes_I3C_alpha2.tga");
	//m_pBox = new cBox(m_pImage->GetImageWidth(), m_pImage->GetImageHeight(), rc);

	m_pImage->SetPosSclRect(rc);

	m_pCharacterTest = new cCharacterTest;
	m_pCharacterTest->Setup();

	m_pMapTest = new cMapTest;
	m_pMapTest->Setup();
}

void cCameraTest::Update()
{
	if (m_pCharacterTest)
		m_pCharacterTest->Update();

	ControlTestCamera();


	//회전시키고, 거리만큼 이동시킨뒤 ,lookat 에서떨어진위치
	D3DXMATRIX matRY;
	D3DXMATRIX matRX;
	D3DXMatrixRotationX(&matRX, m_vRot.x);
	D3DXMatrixRotationY(&matRY, m_vRot.y);
	
	D3DXVec3TransformCoord(&m_vEye, &D3DXVECTOR3(0, 0, 1), &(matRX * matRY));

	m_vEye *= m_fCameraDistance;

	m_vEye += m_vLookAt;		//이것이 눈위치



}

void cCameraTest::Render(LPD3DXSPRITE pSprite)
{
	
	//여기에 뷰행렬을 변환하고, 카메라행렬도 변환한뒤, 애들을 한번더 그려준다.

	//원래의 변환을 얻어놓고
	D3DVIEWPORT9 orgViewPort;
	g_pD3DDevice->GetViewport(&orgViewPort);

	RECT rc = m_pImage->GetPosSclRect();
	D3DVIEWPORT9 viewPort = { rc.left,rc.top,rc.right - rc.left , rc.bottom - rc.top ,0,1 };
	//새로운변환설정
	g_pD3DDevice->SetViewport(&viewPort);

	D3DXMATRIX orgView;
	D3DXMATRIX view;

	//

	D3DXMatrixLookAtLH(&view, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &orgView);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &view);

	if (m_pCamera)
		RenderCamera();
	if (m_pCharacterTest)
		m_pCharacterTest->Render();
	if (m_pMapTest)
		m_pMapTest->Render();

	//복구
	g_pD3DDevice->SetViewport(&orgViewPort);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &orgView);
	//스프라이트가 먼저 그려지면 투명도가 적용되지 않는다 따라서 얘네들은 투명도가 적용되게 그려놓고
	//나머지 애들은 투명도 제한다.
	m_pImage->Render(pSprite);


	if (m_pCharacterTest)
		m_pCharacterTest->Render();
	if (m_pMapTest)
		m_pMapTest->Render();


}

void cCameraTest::ControlTestCamera()
{
	if (g_pKeyManager->IsStayKeyDown(VK_HOME))
	{
		m_fCameraDistance -= 0.2f;
		if (m_fCameraDistance < 0.1f)
			m_fCameraDistance = 0.1f;
	}
	else if(g_pKeyManager->IsStayKeyDown(VK_END))
	{
		m_fCameraDistance += 0.2f;
		if (m_fCameraDistance > 80.f)
			m_fCameraDistance = 80.f;
	}
	if (g_pKeyManager->IsStayKeyDown(VK_DOWN))
	{
		m_vRot.x -= 0.01f;
		if (m_vRot.x < 0)
			m_vRot.x += D3DX_PI * 2;
	}
	else if (g_pKeyManager->IsStayKeyDown(VK_UP))
	{
		m_vRot.x += 0.01f;
		if (m_vRot.x > D3DX_PI * 2)
			m_vRot.x -= D3DX_PI * 2;
	}

	if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
	{
		m_vRot.y -= 0.01f;
		if (m_vRot.y < 0)
			m_vRot.y += D3DX_PI * 2;
	}
	else if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
	{
		m_vRot.y += 0.01f;
		if (m_vRot.y > D3DX_PI * 2)
			m_vRot.y -= D3DX_PI * 2;
	}

	if (g_pKeyManager->IsStayKeyDown('P'))
	{
		m_vLookAt.y += 0.03f;
		if (m_vLookAt.y > 20.f)
			m_vLookAt.y = 20.f;
	}
	else if (g_pKeyManager->IsStayKeyDown('L'))

	{
		m_vLookAt.y -= 0.03f;
		if (m_vLookAt.y < -10.f)
			m_vLookAt.y = -10.f;
	}



}

void cCameraTest::RenderCamera()
{
	if (!m_pCamera)
		return;

	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS, 0.8f, 0.8f, 0.8f);



	m_pCameraMesh->Render( &(matS *m_pCamera->GetMatCameraWorld()));



}
