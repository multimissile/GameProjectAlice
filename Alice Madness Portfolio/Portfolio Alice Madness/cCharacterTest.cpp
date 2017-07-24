#include "stdafx.h"
#include "cCharacterTest.h"
#include "cSkinnedMesh.h"

cCharacterTest::cCharacterTest()
	:m_pSkinnedMesh(NULL)
	, m_vPosition(0.f, 0.f, 0.f)
	, state(CHARACTER_Idle)
{

}

cCharacterTest::~cCharacterTest()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cCharacterTest::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("TestFolder", "alice_knife.X");
	m_pSkinnedMesh->SetAnimationIndexBlend(state);
}
void cCharacterTest::Update()
{

	//������ �׽�Ʈ�� Ű �׽�Ʈ
	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		
		if (state != CHARACTER_Alice_Walk)
		{
			state = CHARACTER_Alice_Walk;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}
		m_vPosition += D3DXVECTOR3(0, 0, -1) * 0.09f;



		////�ִ� �ִϸ��̼����� ���� �������� �ѱ��.
		////�ִϸ��̼� ������ 
		//if(m_pSkinnedMesh->GetCurrentAnimationEnd())
		//	m_pSkinnedMesh->SetAnimationIndexBlend(28);


	}

	else if (g_pKeyManager->IsStayKeyDown('S'))
	{

		if (state != (CHARACTER_STATE)10)
		{
			state = (CHARACTER_STATE)10;

			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}

		m_vPosition += D3DXVECTOR3(0, 0, +1) * 0.09f;
	}

	else if (state != CHARACTER_Idle)
	{
		{
			state = CHARACTER_Idle;
			//Ʈ���������� 0 ���� �����ؾ��ϹǷ� SetAnimationIndexBlend �� ����Ͽ� Ʈ���������� 0���� ����� ���ÿ�
			// ���� �ִϸ��̼ǿ��� ����ִϸ��̼����� �Ѿ���°��� ������� �ʵ��� blend
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}

	}


	//if (g_pKeyManager->IsOnceKeyDown('1'))
	//{
	//static int n = 0;	

	//1 indexBlend ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼��� �ε巴�� �ʴ�, �ִϸ��̼� Ʈ���������� �״�������ȴ�.
	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);

	//2 Index ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼� ������ �������� �ε巴�� blend �Ѵ�. �ִϸ��̼�Ʈ���������� 0�� �ȴ�.
	////m_pSkinnedMesh->SetAnimationIndex(1);
	//}


}

void cCharacterTest::Render()
{
	D3DXMATRIX matS, matR;
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMatrixTranslation(&matR, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matR));

	m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matS * matR));
	m_pSkinnedMesh->UpdateAndRender();

}
