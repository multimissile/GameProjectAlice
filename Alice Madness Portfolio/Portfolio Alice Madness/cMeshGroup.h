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

	////// -
	float m_fScale;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;

public:
	inline D3DXVECTOR3 GetMin() { return *D3DXVec3Scale(&D3DXVECTOR3(), &m_vMin, m_fScale); }
	inline D3DXVECTOR3 GetMax() { return *D3DXVec3Scale(&D3DXVECTOR3(), &m_vMax, m_fScale); }


public:
	//public:
	cMeshGroup();
	cMeshGroup(char* szFolder, char* szFile, float fScale = 0.03f);

	~cMeshGroup();

	void Render(D3DXMATRIX* matWorld);
private:	//private:
	void Destroy();
};

