#pragma once

/* ĳ���ͷε� �׽�Ʈ �ϴ� Ŭ���� */

class cSkinnedMesh;

enum CHARACTER_STATE
{
	CHARACTER_cStartfR,
	CHARACTER_cStarfL,
	CHARACTER_cIdle,
	CHARACTER_cForward,
	CHARACTER_cBackward,
	CHARACTER_attack3,
	CHARACTER_attack2f,
	CHARACTER_attack2,
	CHARACTER_attack1f,
	CHARACTER_attack1,
	CHARACTER_Alice_Walk,
	CHARACTER_TurnRight_NoRotation,
	CHARACTER_TurnLeft_NoRotation,
	CHARACTER_RunBreak_R,
	CHARACTER_RunBreak_L,
	CHARACTER_Run,
	CHARACTER_Jump_Start,
	CHARACTER_Run_Start,
	CHARACTER_Run_Land,
	CHARACTER_Run_Fall,
	CHARACTER_Jump_Land,
	CHARACTER_Jump_Fall,
	CHARACTER_Idle,
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

