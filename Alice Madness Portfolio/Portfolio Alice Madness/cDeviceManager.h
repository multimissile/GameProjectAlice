#pragma once

/* D3D�� ���� ��ġ ����, ����, ���� */

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice	 cDeviceManager::GetInstance()->GetDevice()
//#define g_pSprite		 cDeviceManager::GetInstance()->GetSprite()

class cDeviceManager
{
	SINGLETON(cDeviceManager);
private:
	LPDIRECT3D9			m_pD3D;			//�ý��� �ϵ�������� ������, IDirect3DDevice9 �������ִ� ��ü
	LPDIRECT3DDEVICE9	m_pD3DDevice;	//3D �׷����� ���÷��� ���ִ� ��ġ
public:
	//m_pD3DDevice ��ü �ֱ�
	inline LPDIRECT3DDEVICE9	GetDevice() {return m_pD3DDevice;}	

	//����
	void Destroy();						
//	
//private:
//	LPD3DXSPRITE m_pSprite;
//public:
//	inline LPD3DXSPRITE	 GetSprite() { return m_pSprite; }
};

