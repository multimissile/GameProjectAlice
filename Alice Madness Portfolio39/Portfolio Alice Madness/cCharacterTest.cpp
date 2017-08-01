#include "stdafx.h"
#include "cCharacterTest.h"
#include "cSkinnedMesh.h"
//바운딩박스로 추가
#include "cBoundingBox.h"


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
void cCharacterTest::Setup( char * szFolder, char * szFile, float fScale)
{
	m_pSkinnedMesh = new cSkinnedMesh(szFolder, szFile,fScale);
	m_pSkinnedMesh->SetAnimationIndexBlend(state);
	
	cBoundingBox* pB = new cBoundingBox;
	pB->Setup(m_pSkinnedMesh->GetMax(), m_pSkinnedMesh->GetMin());
	m_pBounding = pB;



}
void cCharacterTest::Update()
{

	//움직임 테스트와 키 테스트
	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		
		if (state != CHARACTER_Alice_Walk)
		{
			state = CHARACTER_Alice_Walk;
			m_pSkinnedMesh->SetAnimationIndexBlend(state);
		}

		D3DXVECTOR3 vDir(0, 0, -1);
		//앞에 아무것도 없으면 가기
		//if (!g_pGameManager->CheckCollision(m_pBounding, vDir))
		m_vPosition += vDir* 0.09f;
		
		
			//m_vPosition += D3DXVECTOR3(0, 0, -1) *0.09f;


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

		D3DXVECTOR3 vDir(0, 0, +1);
		//앞에 아무것도 없으면 가기
		//if (!g_pGameManager->CheckCollision(m_pBounding, vDir))
			m_vPosition += vDir* 0.09f;
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

	//높이주기
	float height;
	//내 위치에서의 높이 너무 높이있으면 못감, 적당히있으면 감
	//
	//높이차이가 많이나나 적게나나 없나 체크해서 
	//높이 차이가 많이나면 떨어지는 모션 + 높이서 떨어진 소리
	//높이차이가 적게나면 떨어지는 모션 + 떨어진 소리
	//false 면 떨어지다가 죽은모션 

	//if (g_pGameManager->GetHeight(m_vPosition.x, height, m_vPosition.z))
	//{
	//	
	//	m_vPosition.y = height;
	//}
	//
	//else
	//{
	//
	//
	//
	//}





	//if (g_pKeyManager->IsOnceKeyDown('1'))
	//{
	//static int n = 0;	

	//1 indexBlend 사용하기 (다음애니메이션과 이전애니메이션이 부드럽지 않다, 애니메이션 트랙포지션이 그대로유지된다.
	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);

	//2 Index 사용하기 (다음애니메이션과 이전애니메이션 사이의 움직임을 부드럽게 blend 한다. 애니메이션트랙포지션이 0이 된다.
	////m_pSkinnedMesh->SetAnimationIndex(1);
	//}


	//월드매트릭스설정
	D3DXMATRIX matR, matWorld;

	D3DXMatrixTranslation(&matR, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	matWorld = matR;

	m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&matWorld);
	m_pBounding->Update(&matWorld);


}

void cCharacterTest::Render()
{
	//D3DXMATRIX matS, matR;
	//D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matR));
	
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matS * matR));

	m_pSkinnedMesh->UpdateAndRender();

}

D3DXVECTOR3& cCharacterTest::GetMin()
{
	return m_pSkinnedMesh->GetMin();
}

D3DXVECTOR3& cCharacterTest::GetMax()
{
	return m_pSkinnedMesh->GetMax();
}

D3DXMATRIX cCharacterTest::GetWorldTM()
{
	D3DXMATRIX matT;
	return *D3DXMatrixTranslation(&matT, 
		m_vPosition.x, 
		m_vPosition.y, 
		m_vPosition.z); 

}

cSkinnedMesh * cCharacterTest::GetSkinnedMesh()
{
	return m_pSkinnedMesh;
}

