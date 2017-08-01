#pragma once

/*objŸ���� mesh group*/

//�̿�

class cMeshGroup;
struct stMtlTex;


class cObjLoader
{
private:
	map<string, stMtlTex> m_mapMtlTex;

public:
	cObjLoader();
	~cObjLoader();

	void LoadMtlLib(char* szFolder, char* szFile);
	void Load( char* szFolder, char* szFile, MESH_OPTION option,
		OUT LPD3DXMESH&  pMesh,
		vector<stMtlTex>& vecMtlTex);

};

