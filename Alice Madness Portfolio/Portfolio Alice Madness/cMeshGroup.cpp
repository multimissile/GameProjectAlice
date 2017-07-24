#include "stdafx.h"
#include "cMeshGroup.h"


cMeshGroup::cMeshGroup()
	:m_pMesh(NULL)
{
}

cMeshGroup::~cMeshGroup()
{
}

void cMeshGroup::Render(D3DXMATRIX * matWorld)
{
	if (!m_pMesh)
		return;

	//월드매트릭스 받아서 그려준다.
	if (matWorld)
		g_pD3DDevice->SetTransform(D3DTS_WORLD, matWorld);
	else
		g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int n = 0; n < m_vecMtlTex.size(); n++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[n].stMtl);
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[n].pTexture);
		m_pMesh->DrawSubset(n);
	}

}

void cMeshGroup::Destroy()
{
	for (int n = 0; n < m_vecMtlTex.size(); n++)
	{
		SAFE_RELEASE(m_vecMtlTex[n].pTexture);
	}
	SAFE_RELEASE(m_pMesh);
}
