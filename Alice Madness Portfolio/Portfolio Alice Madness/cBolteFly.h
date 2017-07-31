#pragma once
#include "cEnemy.h"

class cSkinnedMesh;

#define FLYSPEED 0.2f

enum BOLTEFLY_STATE
{
	fly_walk_2, fly_walk_1, fly_strafe_r, fly_strafe_l, fly_strafe_sprint, fly_leeching_detach,
	fly_leeching_attach, fly_leeching, fly_damage, fly_attack
};

class cBolteFly :
	public cEnemy
{
private:
	cSkinnedMesh* fly;		//적 메쉬

	BOLTEFLY_STATE nowState;		//현재 적 상태
	D3DXVECTOR3 saveDir;
	D3DXVECTOR3 userPos;
	D3DXVECTOR3 centerPos;

	float dis;
	float deg;
	bool setPos;
	bool isAtk;
public:
	cBolteFly();
	~cBolteFly();

	void Setup();
	void Setup(float _x, float _y, float _z);
	void Update();
	void Render();

	void AttackSet(D3DXVECTOR3& vPosition);	//유저위치를 받아서 일정거리 안에 들어오면 공격모션
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(BOLTEFLY_STATE state);
	bool EndFrame();
};

