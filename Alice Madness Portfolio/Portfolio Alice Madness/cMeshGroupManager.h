#pragma once

/*mesh group을 만들어 돌려주는역할을 합니다.*/

//미완

#define g_pMeshGroupManager cMeshGroupManager::GetInstance()



class cMeshGroup;
enum MESH_OPTION;

class cMeshGroupManager
{
	SINGLETON(cMeshGroupManager);
	map<string, cMeshGroup*> m_mapMeshGroup;

public:
	cMeshGroup* GetMeshGroupObj(char* szFolder, char* szFile, MESH_OPTION option);
	cMeshGroup* GetMeshGroupObj(string szFolder, string szFile, MESH_OPTION option);
	cMeshGroup* GetMeshGroupX(char* szFolder, char* szFile, MESH_OPTION option);
	cMeshGroup* GetMeshGroupX(string szFolder, string szFile, MESH_OPTION option);

	void Destroy();
};

