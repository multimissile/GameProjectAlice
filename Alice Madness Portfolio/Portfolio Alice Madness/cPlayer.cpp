#include "stdafx.h"
#include "cPlayer.h"
#include "iMap.h"


cPlayer::cPlayer():state(CHARACTER_Idle)
{
	m_fRotY = 0.0f;
	m_pSkinnedMesh = NULL;
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vDirection = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXMatrixIdentity(&m_matWorld);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cPlayer::Setup()
{
	SetMesh(new cSkinnedMesh("TestFolder", "alice_knife.X"));
	m_pSkinnedMesh->SetAnimationIndexBlend(state);
}
void cPlayer::Update(iMap* pMap)
{
	m_pMap = pMap;
	float fmoveSpeed = 2.5f;
	D3DXVECTOR3 vPosition = m_vPosition;

	//������ �׽�Ʈ�� Ű �׽�Ʈ
	if (g_pKeyManager->IsStayKeyDown('A'))
	{
		state = CHARACTER_Idle;

		m_fRotY -= 0.1f;
	}
	else if (g_pKeyManager->IsStayKeyDown('D'))
	{
		state = CHARACTER_Idle;

		m_fRotY += 0.1f;
	}

	else if (g_pKeyManager->IsStayKeyDown('W'))
	{
		
		if (state != CHARACTER_Alice_Walk)
		{
			state = CHARACTER_Alice_Walk;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}
		vPosition += m_vDirection * fmoveSpeed;



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

		vPosition -= m_vDirection * fmoveSpeed;
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

	//�̵�
	if (pMap) {
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z)) {
			m_vPosition = vPosition;
		}
		else {

		}
	}

	//��ȸ
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, -1);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = (matR*matT)*0.03f;

	

	//if (g_pKeyManager->IsOnceKeyDown('1'))
	//{
	//static int n = 0;	

	//1 indexBlend ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼��� �ε巴�� �ʴ�, �ִϸ��̼� Ʈ���������� �״�������ȴ�.
	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);

	//2 Index ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼� ������ �������� �ε巴�� blend �Ѵ�. �ִϸ��̼�Ʈ���������� 0�� �ȴ�.
	////m_pSkinnedMesh->SetAnimationIndex(1);
	//}


}

void cPlayer::Render()
{
	D3DXMATRIX matS, matR;
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMatrixTranslation(&matR, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matR));

	m_pSkinnedMesh->SetTransform(&m_matWorld);
	m_pSkinnedMesh->UpdateAndRender();

}