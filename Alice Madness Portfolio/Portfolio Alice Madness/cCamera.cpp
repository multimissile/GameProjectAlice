#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0,0,-1), m_vLookAt(0,2,0), m_vUp(0,1,0), m_pvTarget(NULL),m_fCameraDistance(15.f),
	m_isLButtonDown(false), m_vCamRotAngle(1,1,0), m_isFollowTarget(true)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}


cCamera::~cCamera()
{
	//SAFE_RELEASE(m_pCameraSphere);

}

void cCamera::Setup(D3DXVECTOR3 * pvTarget)
{
	//D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pCameraSphere, NULL);


	m_pvTarget = pvTarget;
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom,
		1.f,
		1000.f
	);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	//카메라의 거리 
	ControlCamDist();
	//ControlRotation();
	ControlFollowTarget();
	
	
	//회전등등 처린
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//Z축회전은 안시킬 예정필요하면 셀프추가
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	//순서에 따라 달라질 수 있다. 
	//다르게 처리하려면 쿼터니온 사용 참고
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matR);

	if (m_isFollowTarget && m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye = m_vEye + *m_pvTarget;
		
	}
	else
	{
		m_vLookAt = D3DXVECTOR3(0, 0, 0);
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		
		if (m_isLButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
	
			float fDeltaX = (float)(ptCurMouse.x - m_ptPrevMouse.x);
			float fDeltaY = (float)(ptCurMouse.y - m_ptPrevMouse.y);
	
			////주의
			m_vCamRotAngle.x += (fDeltaY / 100.f);
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			//각도 넘어갔을 때 처리
			//if (m_vCamRotAngle.x < -D3DX_PI / 2.f + 0.0001F)
			//	m_vCamRotAngle.x = -D3DX_PI / 2.f + 0.0001F;
			//if (m_vCamRotAngle.x > -D3DX_PI / 2.f - 0.0001F)
			//	m_vCamRotAngle.x = -D3DX_PI / 2.f - 0.0001F;

			m_ptPrevMouse = ptCurMouse;
		}

	}break;
	case WM_MOUSEWHEEL:
	{
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 100.f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
	}break;
	
	}



}

void cCamera::ControlRotation()
{

	//마우스를 눌렀다면
	if (m_isLButtonDown)
	{
		//움직인양만큼 회전각에 추가한다.
		if (m_ptMouse.x != m_ptPrevMouse.x)
		{
			if (m_ptMouse.x < m_ptPrevMouse.x)
			{
				m_vCamRotAngle.y -= 0.1f;
			}
			else
				m_vCamRotAngle.y += 0.1f;
		}

		if (m_ptMouse.y != m_ptPrevMouse.y)
		{
			if (m_ptMouse.y < m_ptPrevMouse.y)
			{
				m_vCamRotAngle.x -= 0.1f;
			}
			else
				m_vCamRotAngle.x += 0.1f;
		}


		//m_vCamRotAngle = {};
			//D3DXVECTOR3(D3DXToRadian((m_ptMouse.y - m_ptPrevMouse.y) * 0.1f), D3DXToRadian((m_ptMouse.x - m_ptPrevMouse.x) * 0.1f), /*(m_ptMouse.y - m_ptPrevMouse.y) * 0.1f,*/ 0);

	}
	m_ptMouse = m_ptPrevMouse;
}

void cCamera::ControlFollowTarget()
{


	if (GetKeyState('F') & 0x8000)
	{
		//방금키가 눌렸다.
		if (m_tempKeyUp)
		{
			m_isFollowTarget ? m_isFollowTarget = false : m_isFollowTarget = true;
			m_tempKeyUp = false;
		}
	}
	else
	{
		m_tempKeyUp = true;
	}
}

//거리만 확대축소
void cCamera::ControlCamDist()
{
	if (GetKeyState('Q') & 0x8000)
	{
		m_fCameraDistance += 0.1f;
		
	}
	else if (GetKeyState('E') & 0x8000)
	{
		m_fCameraDistance -= 0.1f;
	}
}
D3DXMATRIX cCamera::GetMatCameraWorld()
{
	D3DXMATRIX matRX, matRY, matT;

	D3DXMatrixRotationX(&matRX,m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	D3DXMatrixTranslation(&matT, m_vEye.x, m_vEye.y, m_vEye.z);
	return matRX * matRY * matT;

}
//
//void cCamera::RenderCamera()
//{
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
//
//	D3DXMATRIX matWorld;
//	D3DXMatrixTranslation(&matWorld, m_vEye.x, m_vEye.y, m_vEye.z);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//	m_pCameraSphere->DrawSubset(0);
//}
//