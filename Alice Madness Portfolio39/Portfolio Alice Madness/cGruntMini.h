#pragma once
#include "cEnemy.h"

#define WALKSPEED 0.02f
#define RUNSPEED 0.05f
class cSkinnedMesh;

enum GRUNT_STATE
{
	grunt_damage_l_3, grunt_damage_l_2, grunt_damage_l_1, grunt_warn, grunt_taunt_3, grunt_taunt_2,
	grunt_taunt_1, grunt_strafe_walk_r, grunt_strafe_walk_l, grunt_strafe_walk_f, grunt_strafe_walk_b,
	grunt_strafe_run_r, grunt_strafe_run_l, grunt_strafe_run_f, grunt_strafe_run_b, grunt_spawn_4,
	grunt_spawn_3, grunt_spawn_2, grunt_spawn_1, grunt_falling, grunt_die_3, grunt_die_2, grunt_die_1,
	grunt_damage_h_2, grunt_damage_h_1, grunt_idle, grunt_rotation_attack_end, 
	grunt_rotation_attack_start, grunt_smash_attack_end, grunt_smash_attack_start, 
	grunt_stand_attack_2_end, grunt_stand_attack_2_start, grunt_stand_attack_1_end, grunt_stand_attack_1_start,
	grunt_head_attack, grunt_move_attack_2_end, grunt_move_attack_2_start, grunt_move_attack_1_end,
	grunt_move_attack_1_start
};

class cGruntMini : public cEnemy
{
private:
	cSkinnedMesh* grunt;		//적 메쉬
	GRUNT_STATE nowState;		//현재 적 상태
	//D3DXVECTOR3 m_vPosition;		//적 위치
	//D3DXVECTOR3 m_vDirection;			//적 방향
	D3DXVECTOR3 saveDir;
	D3DXVECTOR3 userPos;
//	D3DXMATRIXA16 m_matWorld;

	//float m_fRotY;
	//double maxTime;		//프레임 전부 도는데 걸리는 시간
	//double nowTime;		//현재 프레임까지 걸린 시간

	float dis;
	bool isAtk;


public:
	cGruntMini();
	~cGruntMini();

	void Setup();
	void Setup(float _x, float _y, float _z);
	void Update();
	void Render();

	void AttackSet(D3DXVECTOR3& vPosition);	//유저위치를 받아서 일정거리 안에 들어오면 공격모션
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(GRUNT_STATE state);
	bool EndFrame();
};

