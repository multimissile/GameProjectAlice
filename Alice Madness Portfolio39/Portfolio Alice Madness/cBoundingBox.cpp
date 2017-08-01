#include "stdafx.h"
#include "cBoundingBox.h"
#include "cSkinnedMesh.h"

cBoundingBox::cBoundingBox()
{
	ZeroMemory(m_vOrgAxisDir, sizeof(D3DXVECTOR3) * 3);
	ZeroMemory(m_vAxisDir, sizeof(D3DXVECTOR3) * 3);
	ZeroMemory(m_fAxisLen, sizeof(float) * 3);
	ZeroMemory(m_fAxisHalfLen, sizeof(float) * 3);
	m_enType = BOUNDING_BOX;
}


cBoundingBox::~cBoundingBox()
{
	
}

void cBoundingBox::Setup(cSkinnedMesh * pSkinnedMesh)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();

	m_vecVertex.push_back(vMin);
	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMax.y, vMin.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMax.y, vMin.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMin.y, vMin.z));

	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMin.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMax.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMax.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMin.y, vMax.z));


	m_vOrgCenterPos = (vMin + vMax) / 2.f;

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);

	SetBoundingRadius(D3DXVec3Length(&(m_vOrgCenterPos - vMax)));
}

void cBoundingBox::Setup(D3DXVECTOR3 & vMax, D3DXVECTOR3 & vMin)
{

	m_vecVertex.push_back(vMin);
	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMax.y, vMin.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMax.y, vMin.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMin.y, vMin.z));

	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMin.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMin.x, vMax.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMax.y, vMax.z));
	m_vecVertex.push_back(D3DXVECTOR3(vMax.x, vMin.y, vMax.z));


	m_vOrgCenterPos = (vMin + vMax) / 2.f;

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);

	SetBoundingRadius(D3DXVec3Length(&(m_vOrgCenterPos - vMax)));

}

void cBoundingBox::Update(D3DXMATRIX* pmatWorld)
{
	cBounding::Update(pmatWorld);

	if (pmatWorld)
	{
		for (int i = 0; i < 3; ++i)
		{
			D3DXVec3TransformNormal(
				&m_vAxisDir[i],
				&m_vOrgAxisDir[i],
				pmatWorld);
		}
	}
}

void cBoundingBox::ResetBounding()
{
}

void cBoundingBox::OBBBox_Render()
{

	D3DXCOLOR c = D3DCOLOR_XRGB(0, 0, 0);
	
	
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	vector<D3DXVECTOR3> v(m_vecVertex.size());
	for (int n = 0; n < m_vecVertex.size(); n++)
	{
		D3DXVec3TransformCoord(&v[n], &m_vecVertex[n], &m_matWorldTM);
	}

	int index[]
	{
		0,1,2,
		0,2,3,
		4,5,1,
		4,1,0,
		1,5,6,
		1,6,2,
		2,6,7,
		2,7,3,
		4,0,1,
		4,1,7,
		5,4,7,
		5,7,6
	};

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	std::vector<ST_PC_VERTEX> vecVertex;
	for (int n = 0; n < _countof(index); n ++)
	{
		vecVertex.push_back(ST_PC_VERTEX(v[index[n]], c));
	}


	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vecVertex.size() / 3, &vecVertex[0],
		sizeof(ST_PC_VERTEX));


	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
