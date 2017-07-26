#pragma once
#include "cSkinnedMesh.h"

/* ĳ���͵��� ����Դϴ�. */


class cCharacter
{
public:
	cCharacter();
	virtual ~cCharacter();
protected:
	float m_fRotY;
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, Mesh);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPos);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, vDir);
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();

};

