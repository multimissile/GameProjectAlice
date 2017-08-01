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


//����߰� ( public ���
#include "cObject.h"



class cCharacterTest : public cObject
{
	cSkinnedMesh* m_pSkinnedMesh;
	CHARACTER_STATE state;

	D3DXVECTOR3 m_vPosition;

	
public:
	cCharacterTest();
	~cCharacterTest();

	void Setup();	//���� ����
	//���ϸ����� �ε�ǵ��� ����
	void Setup( char* szFolder,  char* szFile, float scale = 0.03f);
	void Update();
	void Render();

	
public:
	D3DXVECTOR3& GetMin(); 
	D3DXVECTOR3& GetMax(); 
	D3DXMATRIX GetWorldTM();
	cSkinnedMesh* GetSkinnedMesh();
};

