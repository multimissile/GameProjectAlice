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
	cSkinnedMesh* grunt;		//�� �޽�
	GRUNT_STATE nowState;		//���� �� ����
	//D3DXVECTOR3 m_vPosition;		//�� ��ġ
	//D3DXVECTOR3 m_vDirection;			//�� ����
	D3DXVECTOR3 saveDir;
	D3DXVECTOR3 userPos;
//	D3DXMATRIXA16 m_matWorld;

	//float m_fRotY;
	//double maxTime;		//������ ���� ���µ� �ɸ��� �ð�
	//double nowTime;		//���� �����ӱ��� �ɸ� �ð�

	float dis;
	bool isAtk;


public:
	cGruntMini();
	~cGruntMini();

	void Setup();
	void Setup(float _x, float _y, float _z);
	void Update();
	void Render();

	void AttackSet(D3DXVECTOR3& vPosition);	//������ġ�� �޾Ƽ� �����Ÿ� �ȿ� ������ ���ݸ��
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(GRUNT_STATE state);
	bool EndFrame();
};

