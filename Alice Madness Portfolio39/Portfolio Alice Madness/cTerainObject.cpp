#include "stdafx.h"
#include "cTerainObject.h"
#include "cBoundingBox.h"
#include "cMeshGroup.h"

cTerainObject::cTerainObject()
	:m_pMeshGroup(NULL)
{

}


cTerainObject::~cTerainObject()
{
	SAFE_DELETE(m_pMeshGroup);

}

void cTerainObject::Setup( char* szFolder,  char* szFile, float scale)
{
	m_pMeshGroup = new cMeshGroup(szFolder, szFile, scale);

	cBoundingBox* pB = new cBoundingBox;
	pB->Setup(m_pMeshGroup->GetMax(), m_pMeshGroup->GetMin());
	m_pBounding = pB;
}

void cTerainObject::Update()
{
	D3DXMATRIX matRY;
	D3DXMatrixRotationY(&matRY, m_fRotationY);
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRY * matT;


	m_pBounding->Update(&m_matWorld);

}

void cTerainObject::Render()
{

	m_pMeshGroup->Render(&m_matWorld);

}
