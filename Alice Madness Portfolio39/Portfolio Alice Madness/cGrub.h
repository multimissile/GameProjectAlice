#pragma once
#include "cEnemy.h"

class cSkinnedMesh;
//애니메이션 컨트롤러에 저장된 인덱스 순서대로 스테이트 설정해놓은것
enum GRUB_STATE
{
	grub_walk,grub_turn_rgt45,grub_turn_rgt, grub_turn_lft45,grub_turn_lft,
	grub_spawn, grub_jump, grub_idle_dead_2, grub_idle_dead_1, grub_idle,
	grub_falling, grub_attack_setal, grub_attack
};
class cGrub : public cEnemy
{
private:
	cSkinnedMesh* grub;		//적 메쉬
	GRUB_STATE nowState;		//현재 적 상태
	D3DXVECTOR3 saveDir;
	D3DXVECTOR3 userPos;

	float dis;
	bool isAtk;
public:
	cGrub();
	~cGrub();

	
	void Setup();
	void Setup(float _x, float _y, float _z);
	void Update();
	void Render();

	void AttackSet(D3DXVECTOR3& vPosition);	//유저위치를 받아서 일정거리 안에 들어오면 공격모션
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(GRUB_STATE state);
	bool EndFrame();
};

