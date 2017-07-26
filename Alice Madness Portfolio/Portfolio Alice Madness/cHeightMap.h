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

	//버텍스 테스트용
	vector<ST_PNT_VERTEX> m_vecPNTVertex;

	D3DMATERIAL9				m_stMtl;
	LPDIRECT3DTEXTURE9			m_pTexture;
	int							m_nTileN;


public:
	// BytePerPixel raw 파일이 1바이트가 아닌 경우가 있다. 
	void Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytePerPixel= 1);
	void Render();
	bool GetHeight(IN float x, OUT float &y, IN float z);
	void Destroy();
};

