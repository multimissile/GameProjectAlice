#pragma once

//지형 예정

class cMeshGroup;

#define MAX_HEIGHT 1000

class cTerrain
{
	cMeshGroup* m_pMeshGroupTerrain;



	vector<D3DXVECTOR3> m_vecVertex;
	
	
	int m_nCol;
	//
	vector<DWORD> m_vecTestIdx;
	LPD3DXMESH m_pTestMesh;

	int m_nInterval;

	LPDIRECT3DTEXTURE9 m_pTexture;

	D3DMATERIAL9 stMtl;


	//cMeshGroup을 쓰지 말까?

public:
	cTerrain();
	~cTerrain();

	void Setup();//const char* szFolder, const char* szFile);
	void Update();
	void Render();

	bool GetHeight(IN float& x, _Inout_ float& y, IN float& z);
	bool GetPlayerCollision(D3DXVECTOR3 vPosition);

//	int testTileX, testTileZ;
//	int testIdx;
//	D3DXVECTOR3 testVertex[4];
//	float testDeltaX, testDeltaZ;


};

