#pragma once

/*오브젝트용 x 파일을 읽어옵니다. cMeshGroup객체를 돌려줍니다. */

struct stMtlTex;

class cXLoader
{
public:
	cXLoader();
	~cXLoader();
	void Load(const char* szFolder, const char* szFile, MESH_OPTION option,
		OUT LPD3DXMESH&  pMesh,
		vector<stMtlTex>& vecMtlTex);

};

