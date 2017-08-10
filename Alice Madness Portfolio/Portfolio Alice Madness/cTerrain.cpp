#include "stdafx.h"
#include "cTerrain.h"
#include "cMeshGroup.h"
#include "cRawLoader.h"

cTerrain::cTerrain()
	:m_pMeshGroupTerrain(NULL)
	, m_nCol(0)
	, m_pTestMesh(NULL)
	, m_nInterval(1)
{
}


cTerrain::~cTerrain()
{
	SAFE_DELETE(m_pMeshGroupTerrain);
	SAFE_DELETE(m_pTestMesh);
}

void cTerrain::Setup()//const char* szFolder, const char* szFile)
{
	m_nInterval = 2;

	cRawLoader rl;
	rl.Load("TestFolder", "HeightMap.raw", m_nInterval, m_pTestMesh, m_vecVertex);
	
	m_nCol = (int)sqrt(m_vecVertex.size() + EPSILON);

	 m_pTexture=  g_pTextureManager->GetTexture("TestFolder", "MossRock_Tile_DM.tga");

	//m_pTestMesh


	////일단은height map 으로
	////("TestFolder","MossRock_Tile_DM.tga")
	//
	//
	////1.f 필수 데이터로드로 정보얻어오기
	////m_pMeshGroupTerrain = new cMeshGroup(szFolder, szFile, 1.f);
	////m_pMeshGroupTerrain->GetVertex(m_vecVertex);
	//
	//m_nCol = 101;
	////m_nCol = 11;
	//
	////첫번째는 홀수버텍스를 사용하지도 않고 2로 함부로 나눈것
	//
	//
	//
	////임시용
	//m_vecVertex.resize(m_nCol * m_nCol);
	//
	////m_vecVertex.resize()
	////	if (x <)
	//
	//
	////250 250
	//
	//m_nInterval = 8;
	//
	//for (int n = 0; n < m_nCol; n++)
	//{
	//	for (int m = 0; m < m_nCol; m++)
	//	{
	//		int idx =n * m_nCol + m;
	//		m_vecVertex[idx] = D3DXVECTOR3(-((m_nCol-1) * m_nInterval) / 2 + m * m_nInterval, 0, -((m_nCol-1)* m_nInterval) / 2 + n * m_nInterval);
	//	}
	//}
	//
	////int nIdxNum = (m_nCol - 1)*(m_nCol - 1) * 2 * 3;
	//int nFaceNum = m_nCol - 1;
	//
	//
	//
	//for (int n = 0; n < nFaceNum; n++)
	//{
	//	for (int m = 0; m < nFaceNum; m++)
	//	{
	//		int faceVertexNum = n * m_nCol + m;
	//		m_vecTestIdx.push_back(faceVertexNum);
	//		m_vecTestIdx.push_back(faceVertexNum + m_nCol);
	//		m_vecTestIdx.push_back(faceVertexNum + 1);
	//
	//		m_vecTestIdx.push_back(faceVertexNum + 1);
	//		m_vecTestIdx.push_back(faceVertexNum + m_nCol);
	//		m_vecTestIdx.push_back(faceVertexNum + 1 + m_nCol);
	//	}
	//}
	//
	////m_vecVertex[55].y = 3;
	//
	//
//	//
//	//
//	//for (int n = 0; n < 3; n++)
//	//{
//	//	for (int m = 0; m < 3; m++)
//	//	{
//	//		m_vecVertex[4080 + n*m_nCol + m].y = 3;
//	//
//	//	}
//	//}
//	//
	//
	//
	////m_vecVertex[450].y = 3;
	////m_vecVertex[3000].y = 3;
	////m_vecVertex[3001].y = 3;
	////m_vecVertex[3002].y = 3;

	 ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
	 stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	 stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	 stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);

}

void cTerrain::Update()
{

}

void cTerrain::Render()
{
//	vector<D3DXVECTOR3> v;
//	for (int n = 0; n < m_vecTestIdx.size(); n++)
//	{
//		v.push_back(m_vecVertex[m_vecTestIdx[n]]);
//	}
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//	
//	D3DMATERIAL9 stMtl;
//	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
//	stMtl.Ambient = D3DXCOLOR(0.4f, 0.3f, 0.8f, 1.f);
//	stMtl.Diffuse = D3DXCOLOR(0.4f, 0.3f, 0.8f, 1.f);
//	stMtl.Specular = D3DXCOLOR(0.4f, 0.3f, 0.8f, 1.f);
//
//	//g_pD3DDevice->SetMaterial(&stMtl);
//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("Source", "SampleTexture_Green.png"));
//	//g_pD3DDevice->SetTexture(0, NULL);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, v.size() / 3,&v[0], sizeof(D3DXVECTOR3));
//
//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//
//	//m_pMeshGroupTerrain->Render(D3DXMatrixIdentity(&D3DXMATRIX()));

	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	g_pD3DDevice->SetMaterial(&stMtl);
	g_pD3DDevice->SetTexture(0,m_pTexture);
	//g_pD3DDevice->SetTexture(0, NULL);

	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pTestMesh->DrawSubset(0);

}



bool cTerrain::GetHeight(IN float & x, float & y, IN float& z)
{
	int edge = ((m_nCol-1) * m_nInterval) / 2;	//면만큼 움직여야 한다.


	//해당 vertex 점을 찾아서 해당 위치의 삼각형과 비교 후 높이를 돌려준다.

	//타일 밖으로 나갔을 때
	if (x < -edge || z < -edge || x >= edge || z >= edge)
	{
		y = 0;
		return false;
	}
	
	//x, y 가 타일위에서 실제 위치한 x, z 버텍스 번호
	int tileX = (edge + x)/ m_nInterval;
	int tileZ = (edge + z) / m_nInterval;

	int idx = tileZ * m_nCol + tileX;
	float fDeltaX = (x - m_vecVertex[idx].x)/(float)m_nInterval;
	float fDeltaZ = (z - m_vecVertex[idx].z )/ (float)m_nInterval;


	D3DXVECTOR3 v0 = m_vecVertex[idx];
	D3DXVECTOR3 v1 = m_vecVertex[idx + m_nCol];
	D3DXVECTOR3 v2 = m_vecVertex[idx + 1];
	D3DXVECTOR3 v3 = m_vecVertex[idx + m_nCol +1];


	if (fDeltaX + fDeltaZ < 1.f)
	{

		D3DXVECTOR3 v01 = v1 - v0 ;
		D3DXVECTOR3 v02 = v2 - v0 ;

		y = v0.y + (v01 * fDeltaZ + v02 * fDeltaX).y;
		return true;
	}
	else
	{
		fDeltaX = 1.f - fDeltaX;
		fDeltaZ = 1.f - fDeltaZ;
		D3DXVECTOR3 v31 = v1 - v3;
		D3DXVECTOR3 v32 = v2 - v3;
		y = v3.y + (v31 *fDeltaX + v32 * fDeltaZ).y;
		return true;
	}

	y = 0.f;
	return false;
}


bool cTerrain::GetPlayerCollision(D3DXVECTOR3 vPosition)
{
	float fX = vPosition.x;
	float fY;
	float fZ = vPosition.z;
	this->GetHeight(fX, fY, fZ);
	if (fY < vPosition.y) {
		return false;
	}
	else {
		return true;
	}
}
