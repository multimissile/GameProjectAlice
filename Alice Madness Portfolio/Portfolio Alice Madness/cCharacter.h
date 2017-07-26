#pragma once
#include "cSkinnedMesh.h"

class iMap;
/* 캐릭터들의 노드입니다. */


class cCharacter
{
public:
	cCharacter();
	virtual ~cCharacter();
protected:
	float m_fRotY;
	iMap* m_pMap;
	D3DXMATRIXA16 m_matWorld;
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, Mesh);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, vPos);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, vDir);
public:
	virtual void Setup();
	virtual void Update(iMap* pMap);
	virtual void Render();

};

