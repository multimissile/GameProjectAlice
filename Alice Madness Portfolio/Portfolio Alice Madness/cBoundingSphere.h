#pragma once
#include "cBounding.h"
class cBoundingSphere :
	public cBounding
{
public:
	cBoundingSphere();
	~cBoundingSphere();

public:
	enum SPHERE_SIZE
	{
		SPHERE_SIZE_MIN,
		SPHERE_SIZE_MIDDLE,
		SPHERE_SIZE_MAX,
		SPHERE_SIZE_NUM
	};

public:

	float m_fRadius;
	
	LPD3DXMESH m_pSphere;

public:
	void Setup(cSkinnedMesh* pSkinnedMesh, SPHERE_SIZE size = SPHERE_SIZE_MIDDLE);
	
	//이것만 사용할 예정
	void Setup(D3DXVECTOR3& vMax, D3DXVECTOR3& vMin, SPHERE_SIZE size = SPHERE_SIZE_MIDDLE);

	void Update(D3DXMATRIX* pmatWorld);

	void ResetBounding();

	void OBBBox_Render();

};

