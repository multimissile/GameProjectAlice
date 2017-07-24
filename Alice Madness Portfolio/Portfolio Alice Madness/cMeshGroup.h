#pragma once


/* 메쉬 재질 텍스쳐를 가진 그룹입니다. */

enum MESH_OPTION
{
	MESH_TERRAIN,
	MESH_OBJECT,
	MESH_NUM
};

struct stMtlTex
{
	D3DMATERIAL9 stMtl;
	LPDIRECT3DTEXTURE9 pTexture;
	int attrID;
	stMtlTex() :attrID(0), pTexture(NULL)
	{ ZeroMemory(&stMtl, sizeof(D3DMATERIAL9)); }
};


class cMeshGroup
{
	friend class cMeshGroupManager;
private:
//private:
	LPD3DXMESH m_pMesh;
	vector<stMtlTex> m_vecMtlTex;
public:
	//public:
	cMeshGroup();
	~cMeshGroup();

	void Render(D3DXMATRIX* matWorld);
private:	//private:
	void Destroy();
};

