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
	// 월드 행렬 설정
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// 뷰 행렬을 설정
	D3DXVECTOR3 vEyePt(0.0f, 7.0f, -camDst);
	D3DXVECTOR3 vLookatPt(0.0f, 3.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// 프로젝션 행렬 설정
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

	// 카메라 초기화
	g_pCam->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

D3DXMATRIXA16 * cCam::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	D3DXVECTOR3 distance = { 0, 0, -m_fCamDistance };
	m_vEye = *pvEye + distance;
	m_vLookAt = *pvLookat;
	m_vUp = *pvUp;

	//카메라 단위 벡터 구하기
	m_vView = (m_vLookAt - m_vEye);
	D3DXVec3Normalize(&m_vView, &m_vView);

	//카메라 측면 벡터 구하기
	D3DXVec3Cross(&m_vAxisX, &m_vView, &m_vUp);

	//카메라 행렬 만들기
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);

	//카메라 빌보드 행렬 만들기
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


	//카메라 행렬 설정
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	
}

D3DXMATRIXA16 * cCam::RotateLocalX(float angle)
{
	//회전 행렬 생성
	D3DXMATRIXA16 matRot;
	//카메라의 x축을 기준으로 angle만큼 회전행렬 생성
	D3DXMatrixRotationAxis(&matRot, &m_vAxisX, angle);

	//카메라의 새로운 위치를 담을 벡터를 생성
	D3DXVECTOR3 vNewDst;
	//회전 행렬 적용
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);

	//해당 거리만큼 이동
	//실제 포지션 = eye + dst vec
	m_vEye += vNewDst;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::RotateLocalY(float angle)
{
	//회전 행렬 생성
	D3DXMATRIXA16 matRot;
	//카메라의 x축을 기준으로 angle만큼 회전행렬 생성
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);

	//카메라의 새로운 위치를 담을 벡터를 생성
	D3DXVECTOR3 vNewDst;
	//회전 행렬 적용
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);

	//해당 거리만큼 이동
	//실제 포지션 = eye + dst vec
	m_vEye += vNewDst;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::Rotation()
{
	//회전등등 처린
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//Z축회전은 안시킬 예정필요하면 셀프추가
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
	//월드좌표계 타겟의 위치로 카메라를 이동시킨다

	//타겟의 방향을 구하고
	D3DXVECTOR3 dv = *pvTarget - m_vEye;

	m_vEye = *pvTarget;
	m_vLookAt += dv;
	return SetView(&m_vEye, &m_vLookAt, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//방향 구해서
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vAxisX);

	//dist만큼 이동
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//방향 구해서
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vUp);

	//dist만큼 이동
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16 * cCam::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	//방향 구해서
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vView);

	//dist만큼 이동
	vMove = vMove * dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

void cCam::ControlRotation()
{
	//마우스를 눌렀다면
	//if (m_isLButtonDown)
	{
		//움직인양만큼 회전각에 추가한다.

		//좌우
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

		//상하
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
	//마우스를 눌렀다면
	if (m_isLButtonDown)
	{
		//움직인양만큼 회전각에 추가한다.
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
	if (GetAsyncKeyState('W')) g_pCam->MoveLocalZ(0.5f);	// 카메라 전진!
	if (GetAsyncKeyState('S')) g_pCam->MoveLocalZ(-0.5f);	// 카메라 후진!
	if (GetAsyncKeyState('A')) g_pCam->MoveLocalX(0.5f);	// 카메라 전진!
	if (GetAsyncKeyState('D')) g_pCam->MoveLocalX(-0.5f);	// 카메라 후진!
	if (GetAsyncKeyState(VK_ESCAPE)) PostMessage(g_hWnd, WM_DESTROY, 0, 0L);

	if (GetKeyState('Q') & 0x8000) m_fCamDistance += 0.1f;
	else if (GetKeyState('E') & 0x8000) m_fCamDistance -= 0.1f;
	
}

void cCam::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//// : LBUTTONDOWN, LBUTTONUP, MOUSEMOVE, MOUEWHELL	// 확대 축소 .. 
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

		////주의
		m_fCamRotY += (fDeltaY / 100.f);
		m_fCamRotX += (fDeltaX / 100.f);
		//각도 넘어갔을 때 처리
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


