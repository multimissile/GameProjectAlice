#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
	:m_pD3D(NULL)
	,m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	D3DCAPS9	stCaps;					//장치특성
	int			nVertexProcessing;

	//장치특성중에서도 버텍스 프로세싱 지원하는지 여부
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps& D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//하드웨어 버텍스 프로세싱이 가능하다
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//소프트웨어 버텍스 프로세싱 이용해야 한다.
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//생성하려는 IDirect3DDevice9 객체 특성 정의하기위한 구조체
	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;						//윈도우모드일때는 TRUE, 전체화면일때는 FALSE
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;	//좀더 세밀하고자 하면 D32로 그렇지만-

													//위에 정의한 특성, 얻어온 정보를 바탕으로 IDirect3DDevice9 객체를 만든다.
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//물리 디스플레이 어댑터
		D3DDEVTYPE_HAL,							//HAL 장치 또는 REF 장치가 있으며 HAL: 하드웨어 이용하겠다.,  REF : 장치에서 지원하지 않는 기능들테스트 할 때 사용하는 장치 DirectXSDK에만 포함, 개발용, 사용자에게 배포불가, 느리다.
		g_hWnd,									//장치와 연결해줄 윈도우핸들(어디에다 그릴거니)
		nVertexProcessing,						//behavior flag 위에서 얻어온정보 
		&stD3DPP,								//위에서 만든D3DPRESENT_PARAMETERS구조체
		&m_pD3DDevice);							//IDirect3DDevice9 객체
}
cDeviceManager::~cDeviceManager()
{
	Destroy();
}

void cDeviceManager::Destroy()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
}
