#pragma once
/*
ī�޶� ���� Ŭ����
*/


#define g_pCam cCam::GetInstance()


enum eCAMTYPE
{
	CAM_NORMAL,		// ǥ�� ī�޶�
	CAM_MINIMIZE,	// ����ȭ ī�޶�
	CAM_CLOSE,		// Ȯ�� ī�޶�(���� �����)
	CAM_TITLE,		// Ÿ��Ʋ ī�޶�
	CAM_ROCKON		// ���� ķ : ���� �޴������� �� ���͸������� ���͸� ���� �� ����
					// ������ �÷��̾�� ���� ����� ������ ���½�Ű�� ���� ������ ��ȯ����
					// ���� �ÿ��� ��

};

class cCam
{
	SINGLETON(cCam);

private:
	DWORD g_MouseX;
	DWORD g_MouseY;
	D3DXVECTOR3 m_vEye;				//ī�޶��� ���� ��ǥ���� ��ġ
	D3DXVECTOR3 m_vLookAt;			//ī�޶��� �ٶ󺸴� ����
	D3DXVECTOR3 m_vUp;				//ī�޶� ��� ����

	D3DXVECTOR3 m_vView;			//ī�޶� ���ϴ� ���� ����(�������� �������� z��)
	D3DXVECTOR3 m_vAxisX;			//ī�޶��� ���� ����(�������� �������� x��)
									// y���� ��ǻ� m_vUp�� �ȴ�.

	D3DXMATRIXA16 m_matView;		//ī�޶� ��� �����ž�
	D3DXMATRIXA16 m_matBill;		//ī�޶��� �����(������ ���)
									//�޽ð� �׻� ������ ���ϰ� �ϱ����ؼ��� �ʿ��Ҽ��� ����

	float m_fCamDistance;			//ī�޶�� Ÿ�ٰ��� �Ÿ�
	float m_fCamRotX;
	float m_fCamRotY;				//���콺 ȸ�� ����

	D3DXVECTOR3 * m_pvTarget;			//Ÿ�� ��ġ


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

	//ī�޶� ��� ����
	void SetupCam(float camDst);
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);



	//ī�޶� ������Ʈ
	void Update();

 public:
	 D3DXMATRIXA16* RotateLocal(float angleX, float angleY);	//�¿� ȸ��

	 //���� ��ǥ���� Ÿ���� �ִ� ������ �̵��Ѵ�
	 D3DXMATRIXA16* MoveTo(D3DXVECTOR3* pvTarget);

	 //ī�޶� ��ǥ���� �� ���� �������� dist��ŭ �̵��Ѵ�
	 D3DXMATRIXA16* MoveLocalX(float dist);
	 D3DXMATRIXA16* MoveLocalY(float dist);
	 D3DXMATRIXA16* MoveLocalZ(float dist);

public:
	void ControlRotation();
	void ProcessMouse();
	void ProcessKey();


};

