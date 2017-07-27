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
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, Mesh);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Dir);
public:
	virtual void Setup();
	virtual void Update(iMap* pMap);
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();

};

