#pragma once

/* 현재는 해당 카메라를 기본으로 사용합니다. */

//#define g_pCamera cCamera::GetInstance()

class cCamera
{
	//SINGLETON(cCamera);

public:
	cCamera();
	~cCamera();

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	//D3DXVECTOR3		m_pvDirection;   Eye에서 pos 빼서 사용하기로 함
	D3DXVECTOR3*	m_pvTarget;
	//D3DXVECTOR3*	m_pvDirection;

	POINT			m_ptPrevMouse, m_ptMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;
	D3DXVECTOR3		m_vCamPos;

	bool			m_isFollowTarget;
	bool			m_tempKeyUp;

//	float			m_fEpslnY;	//3인칭 카메라를 위한

public:
	void Setup(D3DXVECTOR3* pvTarget = NULL);

	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ControlRotation();
	void ControlFollowTarget();
	void ControlCamDist();

	inline void SetPosition(D3DXVECTOR3* pvTarget) { m_pvTarget = pvTarget; }



	//전역으로 만들자
	
	//LPD3DXMESH m_pCameraSphere;
	//inline D3DXVECTOR3 GetCamEye() { return m_vEye; }
	// GetCamLookAt() { return m_vLookAt; }
	D3DXMATRIX GetMatCameraWorld();

	//카메라 정보 리턴
	D3DXVECTOR3 vGetEye() {
		return m_vEye;
	}
	D3DXVECTOR3 vGetLookAt() {
		return m_vLookAt;
	}
	D3DXVECTOR3 vGetUp() {
		return m_vUp;
	}

};

