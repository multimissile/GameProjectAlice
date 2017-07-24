#include "stdafx.h"
#include "cXLoader.h"
#include "cMeshGroup.h"

cXLoader::cXLoader()
{
}


cXLoader::~cXLoader()
{
}

void cXLoader::Load(const char * szFolder, const char * szFile, MESH_OPTION option, OUT LPD3DXMESH& pMesh, vector<stMtlTex>& vecMtlTex)
{
	LPD3DXBUFFER pMtlBuffer = NULL;
	DWORD nNumMtl;

	string sFullName = szFolder + string("/") + szFile;

	//���� �ɼ� ����
	DWORD options;
	switch (option)
	{
	case MESH_TERRAIN:
		options = D3DXMESH_MANAGED | D3DXMESH_32BIT;
		break;
	case MESH_OBJECT:
		options = D3DXMESH_DYNAMIC;
		break;
	}


	//xFile�� ������ �޽� ������ �о���̱�
	D3DXLoadMeshFromX(
		sFullName.c_str(),	//���ϸ�
		option,				//�÷��� ����
		g_pD3DDevice,		//��ġ
		0,					//�޽� ���� ���� ���� dword�迭
		&pMtlBuffer,		//�Ž� ���� ����
		0,					//D3DXEFFECTINSTANCE ����ü �迭 ���� (����� 0)
		&nNumMtl,			//�޽� ���� ��
		&pMesh
	);


	if (!pMtlBuffer || !nNumMtl)
		return;

	D3DXMATERIAL* mtl = (D3DXMATERIAL*)pMtlBuffer->GetBufferPointer();

	for (int n = 0; n < nNumMtl; n++, mtl++)
	{
		mtl->MatD3D.Ambient = mtl->MatD3D.Diffuse;

		stMtlTex mtlTex;
		mtlTex.stMtl = mtl->MatD3D;

		if (mtl->pTextureFilename)
		{
			mtlTex.pTexture = g_pTextureManager->GetTexture(szFolder, mtl->pTextureFilename);
		}
		else
		{
			mtlTex.pTexture = 0;
		}
		vecMtlTex.push_back(mtlTex);
	}
	//}
	SAFE_RELEASE(pMtlBuffer);
}
