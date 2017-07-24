#include "stdafx.h"
#include "cPlayer.h"


/*cPlayer::cPlayer():state(CHARACTER_Idle)
{
	SetMesh(NULL);
	SetvPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
void cPlayer::Update()
{

	//움직임 테스트와 키 테스트
	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		
		if (state != CHARACTER_Alice_Walk)
		{
			state = CHARACTER_Alice_Walk;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}
		m_vPosition += D3DXVECTOR3(0, 0, -1) * 0.09f;



		////최대 애니메이션으로 가면 다음으로 넘긴다.
		////애니메이션 끝나면 
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
			//트랙포지션이 0 부터 시작해야하므로 SetAnimationIndexBlend 를 사용하여 트랙포지션을 0으로 만듦과 동시에
			// 이전 애니메이션에서 현재애니메이션으로 넘어오는것이 어색하지 않도록 blend
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}

	}


	//if (g_pKeyManager->IsOnceKeyDown('1'))
	//{
	//static int n = 0;	

	//1 indexBlend 사용하기 (다음애니메이션과 이전애니메이션이 부드럽지 않다, 애니메이션 트랙포지션이 그대로유지된다.
	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);

	//2 Index 사용하기 (다음애니메이션과 이전애니메이션 사이의 움직임을 부드럽게 blend 한다. 애니메이션트랙포지션이 0이 된다.
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

	m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matS * matR));
	m_pSkinnedMesh->UpdateAndRender();

}

*/