#pragma once
#include "iMap.h"

class cHeightMap:
	public iMap
{
	//MTL TEXTURE TILE INFO
	//VERTEX....

public:
	cHeightMap();
	virtual ~cHeightMap();

private:

	LPD3DXMESH	m_pMesh;
	std::vector<D3DXVECTOR3>	m_vecVertex;

	//���ؽ� �׽�Ʈ��
	vector<ST_PNT_VERTEX> m_vecPNTVertex;

	D3DMATERIAL9				m_stMtl;
	LPDIRECT3DTEXTURE9			m_pTexture;
	int							m_nTileN;


public:
	// BytePerPixel raw ������ 1����Ʈ�� �ƴ� ��찡 �ִ�. 
	void Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytePerPixel= 1);
	void Render();
	bool GetHeight(IN float x, OUT float &y, IN float z);
	void Destroy();
};

