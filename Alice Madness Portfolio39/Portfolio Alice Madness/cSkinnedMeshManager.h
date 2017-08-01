#pragma once

/* SkinnedMesh객체를 맵에 저장합니다. skinnedmesh가 다른 객체를 필요로할 때 찾아서 포인터를 넘겨주거나 새로만들어서 맵에 등록한 후 넘겨줍니다.*/

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;

public:
	SINGLETON(cSkinnedMeshManager);

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename);
	
	void Destroy();
};

