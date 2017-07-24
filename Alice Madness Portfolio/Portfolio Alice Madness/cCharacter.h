#pragma once
#include "cSkinnedMesh.h"

/* ĳ���͵��� ����Դϴ�. */


class cCharacter
{
public:
	cCharacter();
	virtual ~cCharacter();
public:
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, Mesh);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPos);
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();

};

