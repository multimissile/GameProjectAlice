#pragma once
/*
카메라 조작 클래스
*/


#define g_pCam cCam::GetInstance()


enum eCAMTYPE
{
	CAM_NORMAL,		// 표준 카메라
	CAM_MINIMIZE,	// 소인화 카메라
	CAM_CLOSE,		// 확대 카메라(후추 기관총)
	CAM_TITLE,		// 타이틀 카메라
	CAM_ROCKON		// 락온 캠 : 게임 메니저에서 적 벡터를가지는 벡터를 얻어올 수 있음
					// 락온은 플레이어와 가장 가까운 적부터 락온시키고 텝을 눌러서 전환가능
					// 락온 시에는 적

};

class cCam
{
	SINGLETON(cCam);

private:
	DWORD g_MouseX;
	DWORD g_MouseY;
	D3DXVECTOR3 m_vEye;				//카메라의 월드 좌표상의 위치
	D3DXVECTOR3 m_vLookAt;			//카메라의 바라보는 방향
	D3DXVECTOR3 m_vUp;				//카메라 상방 벡터

	D3DXVECTOR3 m_vView;			//카메라가 향하는 단위 벡터(직관적인 설명으로 z축)
	D3DXVECTOR3 m_vAxisX;			//카메라의 측면 벡터(직관적인 설명으로 x축)
									// y축은 사실상 m_vUp이 된다.

	D3DXMATRIXA16 m_matView;		//카메라 행렬 담을거야
	D3DXMATRIXA16 m_matBill;		//카메라의 역행렬(빌보드 행렬)
									//메시가 항상 정면을 향하게 하기위해서는 필요할수도 있음

	float m_fCamDistance;			//카메라와 타겟간의 거리
	float m_fCamRotX;
	float m_fCamRotY;				//마우스 회전 각도

	D3DXVECTOR3 * m_pvTarget;			//타겟 위치


private:
	POINT m_ptPrevMouse;
	POINT m_ptMouse;
	bool m_isLButtonDown;
	
public:
	D3DXMATRIXA16* GetMatrixView() { return &m_matView; }
	D3DXMATRIXA16* GetMatrixBill() { return &m_matBill; }

	void SetCamEye(D3DXVECTOR3* pvEye) { m_vEye = *pvEye; }
	D3DXVECTOR3* GetEye() { return &m_vEye; }

	void SetCamLookAt(D3DXVECTOR3* pvLook) { m_vLookAt = *pvLook; }
	D3DXVECTOR3* GetLookAt() { return &m_vEye; }

	void SetCamUp(D3DXVECTOR3* pvUp) { m_vUp = *pvUp; }
	D3DXVECTOR3* GetCamUp() { return &m_vUp; }

	void SetCamDistance(float dist) { m_fCamDistance = dist; }
	float GetCamDistance() { return m_fCamDistance; }

	void SetTarget(D3DXVECTOR3* pvTarget) {  m_pvTarget = pvTarget; }

	//카메라 행렬 생성
	void SetupCam(float camDst);
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);



	//카메라 업데이트
	void Update();

 public:
	 D3DXMATRIXA16* RotateLocal(float angleX, float angleY);	//좌우 회전

	 //월드 좌표계의 타겟이 있는 곳으로 이동한다
	 D3DXMATRIXA16* MoveTo(D3DXVECTOR3* pvTarget);

	 //카메라 좌표계의 각 축의 방향으로 dist만큼 이동한다
	 D3DXMATRIXA16* MoveLocalX(float dist);
	 D3DXMATRIXA16* MoveLocalY(float dist);
	 D3DXMATRIXA16* MoveLocalZ(float dist);

public:
	void ControlRotation();
	void ProcessMouse();
	void ProcessKey();


};

