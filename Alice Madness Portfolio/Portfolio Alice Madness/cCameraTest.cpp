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


	//ȸ����Ű��, �Ÿ���ŭ �̵���Ų�� ,lookat ������������ġ
	D3DXMATRIX matRY;
	D3DXMATRIX matRX;
	D3DXMatrixRotationX(&matRX, m_vRot.x);
	D3DXMatrixRotationY(&matRY, m_vRot.y);
	
	D3DXVec3TransformCoord(&m_vEye, &D3DXVECTOR3(0, 0, 1), &(matRX * matRY));

	m_vEye *= m_fCameraDistance;

	m_vEye += m_vLookAt;		//�̰��� ����ġ



}

void cCameraTest::Render(LPD3DXSPRITE pSprite)
{
	
	//���⿡ ������� ��ȯ�ϰ�, ī�޶���ĵ� ��ȯ�ѵ�, �ֵ��� �ѹ��� �׷��ش�.

	//������ ��ȯ�� ������
	D3DVIEWPORT9 orgViewPort;
	g_pD3DDevice->GetViewport(&orgViewPort);

	RECT rc = m_pImage->GetPosSclRect();
	D3DVIEWPORT9 viewPort = { rc.left,rc.top,rc.right - rc.left , rc.bottom - rc.top ,0,1 };
	//���οȯ����
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

	//����
	g_pD3DDevice->SetViewport(&orgViewPort);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &orgView);
	//��������Ʈ�� ���� �׷����� ������ ������� �ʴ´� ���� ��׵��� ������ ����ǰ� �׷�����
	//������ �ֵ��� ���� ���Ѵ�.
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
