#pragma once

/*������Ʈ�� x ������ �о�ɴϴ�. cMeshGroup��ü�� �����ݴϴ�. */

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

