#include "stdafx.h"
#include "cMeshGroup.h"


cMeshGroup::cMeshGroup()
	:m_pMesh(NULL)
	, m_fScale(0)
	, m_vMin(0, 0, 0)
	, m_vMax(0, 0, 0)
{
}

cMeshGroup::cMeshGroup(char * szFolder, char * szFile, float fScale)
{
	m_fScale = fScale;



	//파일 명 폴더 명 따라 메쉬 로드
	g_pMeshGroupManager->GetMeshGroupX(szFolder, szFile, m_pMesh, m_vecMtlTex, MESH_OBJECT);

	{
		D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
		//메쉬에서 
		LPVOID pV = NULL;
		m_pMesh->LockVertexBuffer(0, &pV);

		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			m_pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(m_pMesh->GetFVF()),
			&m_vMin,
			&m_vMax);

		m_pMesh->UnlockVertexBuffer();
	} 

}

cMeshGroup::~cMeshGroup()
{
}

void cMeshGroup::Render(D3DXMATRIX * matWorld)
{
	if (!m_pMesh)
		return;
	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS, m_fScale, m_fScale, m_fScale);


	//월드매트릭스 받아서 그려준다.
	if (matWorld)
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &(matS**matWorld));
	else
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matS);
													  
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
