#pragma once
#include "cEnemy.h"
class cSkinnedMesh;
enum NOSE_STATE
{
	nose_mount_relax, nose_mount_idle, nose_mount_disappear, nose_mount_charge_5,
	nose_mount_charge_4, nose_mount_charge_3, nose_mount_charge_2, nose_mount_charge_1,
	nose_mount_action, nose_fly_relax, nose_fly_idle_2, nose_fly_idle_1, nose_fly_disappear,
	nose_fly_charge_5, nose_fly_charge_4, nose_fly_charge_3, nose_fly_charge_2, nose_fly_charge_1,
	nose_fly_action
};
class cNoseSwitch :
	public cEnemy
{
private:
	cSkinnedMesh* fly;		//적 메쉬

	NOSE_STATE nowState;		//현재 적 상태
	D3DXVECTOR3 saveDir;
	D3DXVECTOR3 userPos;
	D3DXVECTOR3 centerPos;

	float dis;
	float deg;
	bool setPos;
	bool isAtk;
public:
	cNoseSwitch();
	~cNoseSwitch();

	void Setup();
	void Setup(float _x, float _y, float _z);
	void Update();
	void Render();

	void AttackSet(D3DXVECTOR3& vPosition);	//유저위치를 받아서 일정거리 안에 들어오면 공격모션
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(NOSE_STATE state);
	bool EndFrame();
};

