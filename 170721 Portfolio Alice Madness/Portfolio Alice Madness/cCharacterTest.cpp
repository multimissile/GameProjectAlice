#include "stdafx.h"
#include "cCharacterTest.h"
#include "cSkinnedMesh.h"

cCharacterTest::cCharacterTest()
	:m_pSkinnedMesh(NULL)
	,m_vPosition(0.f,0.f,0.f)
	, state(CHARACTER_IDLE)
{

}

cCharacterTest::~cCharacterTest()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cCharacterTest::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("TestFolder", "Alice_Test_Scale0.04f_TextureNone_3.X");
}

void cCharacterTest::Update()
{

	//움직임 테스트와 키 테스트
	if (g_pKeyManager->IsStayKeyDown('W'))
	{

		if (state != CHARACTER_ALICE_WALK)
		{
			state = CHARACTER_ALICE_WALK;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}
		m_vPosition += D3DXVECTOR3(0, 0, -1) * 0.09f;
	}

	else if (g_pKeyManager->IsStayKeyDown('S'))
	{

		if (state != CHARACTER_ALICE_WALK)
		{
			state = CHARACTER_ALICE_WALK;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}	

		m_vPosition += D3DXVECTOR3(0, 0, +1) * 0.09f;
	}

	else if(state != CHARACTER_IDLE)
	{
		{
			state = CHARACTER_IDLE;
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

void cCharacterTest::Render()
{
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&matWorld);
	m_pSkinnedMesh->UpdateAndRender();

}

