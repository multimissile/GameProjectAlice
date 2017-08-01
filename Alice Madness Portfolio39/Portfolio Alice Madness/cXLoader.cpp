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

	//버퍼 옵션 설정
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


	//xFile에 보관된 메쉬 데이터 읽어들이기
	D3DXLoadMeshFromX(
		sFullName.c_str(),	//파일명
		option,				//플래그 지정
		g_pD3DDevice,		//장치
		0,					//메쉬 접근 정보 위한 dword배열
		&pMtlBuffer,		//매쉬 재질 정보
		0,					//D3DXEFFECTINSTANCE 구조체 배열 위한 (현재는 0)
		&nNumMtl,			//메쉬 재질 수
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
