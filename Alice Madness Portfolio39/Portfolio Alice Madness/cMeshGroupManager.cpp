#include "stdafx.h"
#include "cMeshGroupManager.h"
#include "cMeshGroup.h"	
#include "cXLoader.h"
#include "cObjLoader.h"

cMeshGroupManager::cMeshGroupManager()
{
}

cMeshGroupManager::~cMeshGroupManager()
{
}
//
//cMeshGroup * cMeshGroupManager::GetMeshGroupObj(char * szFolder, char * szFile, MESH_OPTION option)
//{
//	string sFullPath = szFolder + string("/") + szFile;
//
//	//없다면
//	if (m_mapMeshGroup.find(sFullPath) == m_mapMeshGroup.end())
//	{
//		cMeshGroup* meshGroup = new cMeshGroup;
//		cObjLoader o;
//		o.Load(szFolder, szFile, option, meshGroup->m_pMesh, meshGroup->m_vecMtlTex);
//
//		m_mapMeshGroup[sFullPath] = meshGroup;
//	}
//
//	return m_mapMeshGroup[sFullPath];
//
//}
//
//
//cMeshGroup * cMeshGroupManager::GetMeshGroupObj(string szFolder, string szFile, MESH_OPTION option)
//{
//	return GetMeshGroupObj(szFolder.c_str(), szFile.c_str(), option);
//}
//
//cMeshGroup * cMeshGroupManager::GetMeshGroupX(char * szFolder, char * szFile, MESH_OPTION option)
//{
//
//	string sFullPath = szFolder + string("/") + szFile;
//
//	//없다면
//	if (m_mapMeshGroup.find(sFullPath) == m_mapMeshGroup.end())
//	{
//		cMeshGroup* meshGroup = new cMeshGroup;
//		//새로 로드하고
//		cXLoader x;
//		x.Load(szFolder, szFile, option, meshGroup->m_pMesh, meshGroup->m_vecMtlTex);
//
//		m_mapMeshGroup[sFullPath] = meshGroup;
//
//	}
//
//	return m_mapMeshGroup[sFullPath];
//
//}
//
//cMeshGroup * cMeshGroupManager::GetMeshGroupX(string szFolder, string szFile, MESH_OPTION option)
//{
//	return GetMeshGroupX(szFolder.c_str(), szFile.c_str(), option);
//}


void cMeshGroupManager::GetMeshGroupX(string & szFolder, string & szFile, LPD3DXMESH & pMesh, vector<stMtlTex>& vMtlTex, MESH_OPTION option)
{
	GetMeshGroupX(szFolder.c_str(), szFile.c_str(), pMesh, vMtlTex, option);
}

void cMeshGroupManager::GetMeshGroupX(const char * szFolder, const char * szFile, LPD3DXMESH & pMesh, vector<stMtlTex>& vMtlTex, MESH_OPTION option)
{

	string sFullPath = szFolder + string("/") + szFile;

	//없다면
	if (m_mapMeshGroup.find(sFullPath) == m_mapMeshGroup.end())
	{
		cMeshGroup* meshGroup = new cMeshGroup;
		//새로 로드하고
		cXLoader x;
		x.Load(szFolder, szFile, option, meshGroup->m_pMesh, meshGroup->m_vecMtlTex);

		m_mapMeshGroup[sFullPath] = meshGroup;

	}
	pMesh = m_mapMeshGroup[sFullPath]->m_pMesh;
	vMtlTex = m_mapMeshGroup[sFullPath]->m_vecMtlTex;

}




void cMeshGroupManager::Destroy()
{
	for each(auto it in m_mapMeshGroup)
	{
		if (it.second)
			it.second->Destroy();
	}
}
