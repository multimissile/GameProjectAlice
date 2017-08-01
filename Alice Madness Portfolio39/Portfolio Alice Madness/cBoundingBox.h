#pragma once
#include "cBounding.h"

class cBoundingBox :
	public cBounding
{

public:
	cBoundingBox();
	~cBoundingBox();

	D3DXVECTOR3 m_vOrgAxisDir[3];	//축이3개이므로 이렇게	
	//float m_fAXisLen[3];			//


									
	D3DXVECTOR3 m_vAxisDir[3];		//	D3DXVECTOR3 m_vCenterPos;
	float		m_fAxisLen[3];
	float		m_fAxisHalfLen[3];

	vector<D3DXVECTOR3> m_vecVertex;	//

public:
	//void Setup(cSkinnedMesh* pSkinnedMesh, float scaling = 1.f);
	void Setup(cSkinnedMesh* pSkinnedMesh);

	//이것만 사용할 예정
	void Setup(D3DXVECTOR3& vMax, D3DXVECTOR3& vMin);

	void Update(D3DXMATRIX* pmatWorld);

	void ResetBounding();
	
	void OBBBox_Render();

};

