#pragma once

/* D3D를 위한 장치 세팅, 생성, 관리 */

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice	 cDeviceManager::GetInstance()->GetDevice()
//#define g_pSprite		 cDeviceManager::GetInstance()->GetSprite()

class cDeviceManager
{
	SINGLETON(cDeviceManager);
private:
	LPDIRECT3D9			m_pD3D;			//시스템 하드웨어정보 얻어오고, IDirect3DDevice9 생성해주는 객체
	LPDIRECT3DDEVICE9	m_pD3DDevice;	//3D 그래픽을 디스플레이 해주는 장치
public:
	//m_pD3DDevice 객체 주기
	inline LPDIRECT3DDEVICE9	GetDevice() {return m_pD3DDevice;}	

	//해제
	void Destroy();						
//	
//private:
//	LPD3DXSPRITE m_pSprite;
//public:
//	inline LPD3DXSPRITE	 GetSprite() { return m_pSprite; }
};

