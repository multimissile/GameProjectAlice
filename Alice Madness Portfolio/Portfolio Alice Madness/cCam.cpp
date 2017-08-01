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
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
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
	m_vEye = *pvEye;
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
		this->RotateLocal(m_fCamRotX, m_fCamRotY);
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

D3DXMATRIXA16 * cCam::RotateLocal(float angleX, float angleY)
{
	//ȸ�� ��� ����
	D3DXMATRIXA16 matRot;

	matRot = *D3DXMatrixRotationX(&D3DXMATRIXA16(), angleX) *
		*D3DXMatrixRotationY(&D3DXMATRIXA16(), angleY);

	//���� ����
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRot);

	m_vEye *= m_fCamDistance;
	m_vEye += m_vLookAt;

	return SetView(&m_vEye, &m_vLookAt, &m_vUp);
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
	//������ ���콺 ��ǥ�� �޾Ƽ�
	POINT ptCurMouse;
	GetCursorPos(&ptCurMouse);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	int fDeltaX = (ptCurMouse.x - (rc.right - rc.left) / 2);
	int fDeltaY = (ptCurMouse.y - (rc.bottom - rc.top) / 2);

	////����
	m_fCamRotY += (fDeltaY / 100.f);
	m_fCamRotX += (fDeltaX / 100.f);

	//���콺 ������ �ٽ� �߾�����
	SetCursorPos((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);

	m_ptPrevMouse = ptCurMouse;


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

	m_ptMouse = m_ptPrevMouse;
}

void cCam::ProcessKey()
{
	//if (GetAsyncKeyState('W')) g_pCam->MoveLocalZ(0.5f);	// ī�޶� ����!
	//if (GetAsyncKeyState('S')) g_pCam->MoveLocalZ(-0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState('A')) g_pCam->MoveLocalX(0.5f);	// ī�޶� ����!
	if (GetAsyncKeyState('D')) g_pCam->MoveLocalX(-0.5f);	// ī�޶� ����!
}


