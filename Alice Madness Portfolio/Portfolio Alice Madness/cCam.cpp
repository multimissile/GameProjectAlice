#include "stdafx.h"
#include "cCam.h"


cCam::cCam()
	: m_vEye(0,0,-m_fCamDistance), m_vLookAt(0,2,0), m_vUp(0,1,0)
	, m_vView(0,0,0), m_vAxisX(0,0,0)
	, m_fCamDistance(0.f), m_pvTarget(NULL)
	, m_fCamRotX(0.f), m_fCamRotY(0.f)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matBill);
	SetView(&m_vEye, &m_vLookAt, &m_vUp);

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}


cCam::~cCam()
{
}

void cCam::SetupCam(float camDst)
{
	// ���� ��� ����
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// �� ����� ����
	D3DXVECTOR3 vEyePt(0.0f, 7.0f, -camDst);
	D3DXVECTOR3 vLookatPt(0.0f, 3.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// �������� ��� ����
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom,
		1.f,
		1000.f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// ī�޶� �ʱ�ȭ
	g_pCam->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

D3DXMATRIXA16 * cCam::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	D3DXVECTOR3 distance = { 0, 0, -m_fCamDistance };
	m_vEye = *pvEye + distance;
	m_vLookAt = *pvLookat;
	m_vUp = *pvUp;

	//ī�޶� ���� ���� ���ϱ�
	m_vView = (m_vLookAt - m_vEye);
	D3DXVec3Normalize(&m_vView, &m_vView);

	//ī�޶� ���� ���� ���ϱ�
	D3DXVec3Cross(&m_vAxisX, &m_vView, &m_vUp);

	//ī�޶� ��� �����
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);

	//ī�޶� ������ ��� �����
	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);

	m_matBill._41 = 0.0f;
	m_matBill._42 = 0.0f;
	m_matBill._43 = 0.0f;

	return &m_matView;
	
}

void cCam::Update()
{
	{

		this->RotateLocalX(m_fCamRotY);
		this->RotateLocalY(m_fCamRotX);

		
	}

	{
		this->ProcessKey();
		this->ProcessMouse();
	}


	//ī�޶� ��� ����
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	
}

D3DXMATRIXA16 * cCam::RotateLocalX(float angle)
{
	//ȸ�� ��� ����
	D3DXMATRIXA16 matRot;
	//ī�޶��� x���� �������� angle��ŭ ȸ����� ����
	D3DXMatrixRotationAxis(&matRot, &m_vAxisX, angle);

	//ī�޶��� ���ο� ��ġ�� ���� ���͸� ����
	D3DXVECTOR3 vNewDst;
	//ȸ�� ��� ����
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);

	//�ش� �Ÿ���ŭ �̵�
	//���� ������ = eye + dst vec
	m_vEye += vNewDst;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::RotateLocalY(float angle)
{
	//ȸ�� ��� ����
	D3DXMATRIXA16 matRot;
	//ī�޶��� x���� �������� angle��ŭ ȸ����� ����
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);

	//ī�޶��� ���ο� ��ġ�� ���� ���͸� ����
	D3DXVECTOR3 vNewDst;
	//ȸ�� ��� ����
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);

	//�ش� �Ÿ���ŭ �̵�
	//���� ������ = eye + dst vec
	m_vEye += vNewDst;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::Rotation()
{
	//ȸ����� ó��
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//Z��ȸ���� �Ƚ�ų �����ʿ��ϸ� �����߰�
	D3DXMATRIXA16 matR, matRX, matRY, matT;
	D3DXMatrixRotationX(&matRX, m_fCamRotX);
	D3DXMatrixRotationY(&matRY, m_fCamRotY);

	matR = matRX * matRY;

	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matR);
	D3DXMatrixTranslation(&matT, m_vEye.x, m_vEye.y, m_vEye.z);

	D3DXMATRIXA16 matView = matRX * matRY * matT;
	return &matView;
	//return SetView(&m_vEye, &m_vLookAt, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveTo(D3DXVECTOR3* pvTarget)
{
	//������ǥ�� Ÿ���� ��ġ�� ī�޶� �̵���Ų��

	//Ÿ���� ������ ���ϰ�
	D3DXVECTOR3 dv = *pvTarget - m_vEye;

	m_vEye = *pvTarget;
	m_vLookAt += dv;
	return SetView(&m_vEye, &m_vLookAt, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//���� ���ؼ�
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vAxisX);

	//dist��ŭ �̵�
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//���� ���ؼ�
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vUp);

	//dist��ŭ �̵�
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//���� ���ؼ�
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vView);

	//dist��ŭ �̵�
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

void cCam::ControlRotation()
{
	//���콺�� �����ٸ�
	//if (m_isLButtonDown)
	{
		//�����ξ縸ŭ ȸ������ �߰��Ѵ�.

		//�¿�
		if (m_ptMouse.x != m_ptPrevMouse.x)
		{
			if (m_ptMouse.x < m_ptPrevMouse.x)
			{
				m_fCamRotY += 0.025f;
			}
			else
			{
				m_fCamRotY -= 0.0025f;
			}
		}

		//����
		if (m_ptMouse.y != m_ptPrevMouse.y)
		{
			if (m_ptMouse.y < m_ptPrevMouse.y)
			{
				m_fCamRotX += 0.05f;

				if (m_fCamRotX > 1.0f) m_fCamRotX = 1.0f;
			}
			else
			{
				m_fCamRotX -= 0.05f;

				if (m_fCamRotX < 0.0f) m_fCamRotX = 0.f;
			}
		}


		//m_vCamRotAngle = {};
		//D3DXVECTOR3(D3DXToRadian((m_ptMouse.y - m_ptPrevMouse.y) * 0.1f), D3DXToRadian((m_ptMouse.x - m_ptPrevMouse.x) * 0.1f), /*(m_ptMouse.y - m_ptPrevMouse.y) * 0.1f,*/ 0);

	}
	m_ptMouse = m_ptPrevMouse;
}

void cCam::ProcessMouse()
{
	//���콺�� �����ٸ�
	if (m_isLButtonDown)
	{
		//�����ξ縸ŭ ȸ������ �߰��Ѵ�.
		if (m_ptMouse.x != m_ptPrevMouse.x)
		{
			if (m_ptMouse.x < m_ptPrevMouse.x)
			{
				m_fCamRotY -= 0.1f;
			}
			else
				m_fCamRotY += 0.1f;
		}

		if (m_ptMouse.y != m_ptPrevMouse.y)
		{
			if (m_ptMouse.y < m_ptPrevMouse.y)
			{
				m_fCamRotX -= 0.1f;
			}
			else
				m_fCamRotX += 0.1f;
		}


		//m_vCamRotAngle = {};
		//D3DXVECTOR3(D3DXToRadian((m_ptMouse.y - m_ptPrevMouse.y) * 0.1f), D3DXToRadian((m_ptMouse.x - m_ptPrevMouse.x) * 0.1f), /*(m_ptMouse.y - m_ptPrevMouse.y) * 0.1f,*/ 0);

	}
	m_ptMouse = m_ptPrevMouse;
}

void cCam::ProcessKey()
{
	if (GetAsyncKeyState('W')) g_pCam->MoveLocalZ(0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState('S')) g_pCam->MoveLocalZ(-0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState('A')) g_pCam->MoveLocalX(0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState('D')) g_pCam->MoveLocalX(-0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState(VK_ESCAPE)) PostMessage(g_hWnd, WM_DESTROY, 0, 0L);

	if (GetKeyState('Q') & 0x8000) m_fCamDistance += 0.1f;
	else if (GetKeyState('E') & 0x8000) m_fCamDistance -= 0.1f;
	
}

void cCam::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//// : LBUTTONDOWN, LBUTTONUP, MOUSEMOVE, MOUEWHELL	// Ȯ�� ��� .. 
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (!m_isLButtonDown)
		{
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
		}

		m_isLButtonDown = true;
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);

	}break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}break;
	case WM_MOUSEMOVE:
	{

		//if (m_isLButtonDown)
		//{
		POINT ptCurMouse;
		ptCurMouse.x = LOWORD(lParam);
		ptCurMouse.y = HIWORD(lParam);

		float fDeltaX = (float)(ptCurMouse.x - m_ptPrevMouse.x);
		float fDeltaY = (float)(ptCurMouse.y - m_ptPrevMouse.y);

		////����
		m_fCamRotY += (fDeltaY / 100.f);
		m_fCamRotX += (fDeltaX / 100.f);
		//���� �Ѿ�� �� ó��
		//if (m_vCamRotAngle.x < -D3DX_PI / 2.f + 0.0001F)
		//	m_vCamRotAngle.x = -D3DX_PI / 2.f + 0.0001F;
		//if (m_vCamRotAngle.x > -D3DX_PI / 2.f - 0.0001F)
		//	m_vCamRotAngle.x = -D3DX_PI / 2.f - 0.0001F;

		m_ptPrevMouse = ptCurMouse;
		//}

	}break;
	case WM_MOUSEWHEEL:
	{
		m_fCamDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 100.f);
		if (m_fCamDistance < 0.0001f)
			m_fCamDistance = 0.0001f;
	}break;

	}

}


