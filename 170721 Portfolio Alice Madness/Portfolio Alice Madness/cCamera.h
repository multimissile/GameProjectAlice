//#pragma once

/* 현재는 해당 카메라를 기본으로 사용합니다. */


class cCamera
{

public:
	cCamera();
	~cCamera();

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;
	D3DXVECTOR3*	m_pvDirection;

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

};
