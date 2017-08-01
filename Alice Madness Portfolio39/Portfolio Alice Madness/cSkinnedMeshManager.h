#pragma once

/* SkinnedMesh��ü�� �ʿ� �����մϴ�. skinnedmesh�� �ٸ� ��ü�� �ʿ���� �� ã�Ƽ� �����͸� �Ѱ��ְų� ���θ��� �ʿ� ����� �� �Ѱ��ݴϴ�.*/

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

