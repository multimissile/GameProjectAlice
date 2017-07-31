#include "stdafx.h"
#include "cItemObject.h"
#include "cMeshGroup.h"

#include "cBoundingSphere.h"
#include "cGlobalData.h"

cItemObject::cItemObject()
	:m_pMeshGroup(NULL)
	, m_pNext(NULL)
	, m_enState(ITEM_STAY)
{
}


cItemObject::~cItemObject()
{
	SAFE_DELETE(m_pMeshGroup);

}


void cItemObject::AddGlobalAndDelete()
{

	g_pGlobalData->AddTooth();
	g_pGameManager->DeleteItem(this);

}

void cItemObject::Setup(char * szFolder, char * szFile, float scale)
{
	m_pMeshGroup = new cMeshGroup(szFolder, szFile, scale);

	cBoundingSphere* pB = new cBoundingSphere;
	pB->Setup(m_pMeshGroup->GetMax(), m_pMeshGroup->GetMin(), cBoundingSphere::SPHERE_SIZE_MAX);
	m_pBounding = pB;
}

void cItemObject::Update()
{

	D3DXMATRIX matT, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotationY);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matRY * matT;
	m_pBounding->Update(&m_matWorld);


	//�÷��̾�� ��������÷��̾ ���󰡴ٰ� ���� sphere�ȿ� �÷��̾� center�� �������� 
	//global data�� 1�� �߰��� �� �Ҹ�

	//�Ծ��� 
	if ( m_enState != ITEM_END &&
		D3DXVec3Length(&(g_pGameManager->GetPlayerBounding()->GetCenterPosition() 
			- m_pBounding->GetCenterPosition())) <
			g_pGameManager->GetPlayerBounding()->GetBoundingRadius() + m_pBounding->GetBoundingRadius())
	{
		//�÷��̾� ���󰡱�
		m_enState = ITEM_END;
	}

	if (m_enState == ITEM_END)
	{
		//���󰣴�.
		D3DXVECTOR3 vDir = g_pGameManager->GetPlayerBounding()->GetCenterPosition()
			- m_pBounding->GetCenterPosition();
		m_vPosition += *D3DXVec3Normalize(&D3DXVECTOR3(), &vDir) * 0.7f;

		if (D3DXVec3Length(&(g_pGameManager->GetPlayerBounding()->GetCenterPosition()
			- m_pBounding->GetCenterPosition())) < m_pBounding->GetBoundingRadius())
		{
			AddGlobalAndDelete();
		}


	}


}

void cItemObject::Render()
{
	m_pMeshGroup->Render(&m_matWorld);

}

