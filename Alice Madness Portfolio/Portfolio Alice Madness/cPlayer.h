#pragma once
#include "cCharacter.h"

class cSkinnedMesh;
class cCamera;
enum CHARACTER_DIR {
	dir8,
	dir7,
	dir9,
	dir1,
	dir2,
	dir3,
	dir4,
	dir6
};

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



class cPlayer
	:public cCharacter
{
public:
	cPlayer();
	~cPlayer();

private:
	CHARACTER_DIR CHAR_DIR;
	bool isAttack;
	bool isDash;
	bool isJump;
	bool isUp1;
	float fRunSpeed;
	float fJumpStr;
	CHARACTER_STATE state;
	//cCamera* m_pCamera;

	cBounding* m_pAttackBound;

public:
	//void Setup();
	//void SetCamera(cCamera* pCamera);
	//	void Update(iMap* pMap);

	void Setup(char* szFolder, char* szFile, float fScale = 0.03f);

	void Update();
	void Render();
	virtual D3DXVECTOR3& GetPosition();
	void ChangeState(CHARACTER_STATE ALICE_STATE);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	cBounding * GetAttackBound();
};

