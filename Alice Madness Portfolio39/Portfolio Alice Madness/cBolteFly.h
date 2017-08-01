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
	cSkinnedMesh* fly;		//�� �޽�

	BOLTEFLY_STATE nowState;		//���� �� ����
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

	void AttackSet(D3DXVECTOR3& vPosition);	//������ġ�� �޾Ƽ� �����Ÿ� �ȿ� ������ ���ݸ��
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(BOLTEFLY_STATE state);
	bool EndFrame();
};

