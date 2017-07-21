#pragma once

/* ĳ���ͷε� �׽�Ʈ �ϴ� Ŭ���� */

class cSkinnedMesh;

enum CHARACTER_STATE
{
	CHARACTER_IDLE,
	CHARACTER_JUMP_FALL,
	CHARACTER_JUMP_LAND,
	CHARACTER_RUN_FALL,
	CHARACTER_ALICE_WALK,
	CHARACTER_STATE_NUM
};

class cCharacterTest
{
	cSkinnedMesh* m_pSkinnedMesh;
	CHARACTER_STATE state;

	D3DXVECTOR3 m_vPosition;


public:
	cCharacterTest();
	~cCharacterTest();

	void Setup();
	void Update();
	void Render();
};

