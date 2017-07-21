#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
	:m_pD3D(NULL)
	,m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	D3DCAPS9	stCaps;					//��ġƯ��
	int			nVertexProcessing;

	//��ġƯ���߿����� ���ؽ� ���μ��� �����ϴ��� ����
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps& D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//�ϵ���� ���ؽ� ���μ����� �����ϴ�
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//����Ʈ���� ���ؽ� ���μ��� �̿��ؾ� �Ѵ�.
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//�����Ϸ��� IDirect3DDevice9 ��ü Ư�� �����ϱ����� ����ü
	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;						//���������϶��� TRUE, ��üȭ���϶��� FALSE
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;	//���� �����ϰ��� �ϸ� D32�� �׷�����-

													//���� ������ Ư��, ���� ������ �������� IDirect3DDevice9 ��ü�� �����.
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//���� ���÷��� �����
		D3DDEVTYPE_HAL,							//HAL ��ġ �Ǵ� REF ��ġ�� ������ HAL: �ϵ���� �̿��ϰڴ�.,  REF : ��ġ���� �������� �ʴ� ��ɵ��׽�Ʈ �� �� ����ϴ� ��ġ DirectXSDK���� ����, ���߿�, ����ڿ��� �����Ұ�, ������.
		g_hWnd,									//��ġ�� �������� �������ڵ�(��𿡴� �׸��Ŵ�)
		nVertexProcessing,						//behavior flag ������ �������� 
		&stD3DPP,								//������ ����D3DPRESENT_PARAMETERS����ü
		&m_pD3DDevice);							//IDirect3DDevice9 ��ü
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
