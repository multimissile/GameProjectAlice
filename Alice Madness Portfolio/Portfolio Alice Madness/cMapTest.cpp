#include "stdafx.h"
#include "cMapTest.h"
#include "cMeshGroup.h"	
#include "cXLoader.h"
#include "cObjLoader.h"
#include "cHeightMap.h"

cMapTest::cMapTest()
{
}


cMapTest::~cMapTest()
{
	//m_pMeshGroup->Destroy();

	//SAFE_DELETE(m_pMeshGroup);
	m_pHeightMap->Destroy();
	SAFE_DELETE(m_pHeightMap);
}

void cMapTest::Setup()
{
	//m_pMeshGroup = g_pMeshGroupManager->GetMeshGroupX("TestFolder", "platformWooden_4.X", MESH_TERRAIN);
	m_pHeightMap = new cHeightMap;
	m_pHeightMap->Setup("TestFolder", "HeightMap.raw", "MossRock_Tile_DM.tga");


}

void cMapTest::Render()
{
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//m_pMeshGroup->Render(NULL);
	m_pHeightMap->Render();

}

void cMapTest::Update()
{
}
