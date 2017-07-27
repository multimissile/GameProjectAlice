#pragma once

/* ����� �ش� ī�޶� �⺻���� ����մϴ�. */

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
	//D3DXVECTOR3		m_pvDirection;   Eye���� pos ���� ����ϱ�� ��
	D3DXVECTOR3*	m_pvTarget;
	//D3DXVECTOR3*	m_pvDirection;

	POINT			m_ptPrevMouse, m_ptMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;
	D3DXVECTOR3		m_vCamPos;

	bool			m_isFollowTarget;
	bool			m_tempKeyUp;

//	float			m_fEpslnY;	//3��Ī ī�޶� ����

public:
	void Setup(D3DXVECTOR3* pvTarget = NULL);

	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ControlRotation();
	void ControlFollowTarget();
	void ControlCamDist();

	inline void SetPosition(D3DXVECTOR3* pvTarget) { m_pvTarget = pvTarget; }



	//�������� ������
	
	//LPD3DXMESH m_pCameraSphere;
	//inline D3DXVECTOR3 GetCamEye() { return m_vEye; }
	// GetCamLookAt() { return m_vLookAt; }
	D3DXMATRIX GetMatCameraWorld();

	//ī�޶� ���� ����
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

