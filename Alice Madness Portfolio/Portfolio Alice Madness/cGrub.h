#pragma once
#include "cEnemy.h"

class cSkinnedMesh;
//�ִϸ��̼� ��Ʈ�ѷ��� ����� �ε��� ������� ������Ʈ �����س�����
enum GRUB_STATE
{
	grub_walk,grub_turn_rgt45,grub_turn_rgt, grub_turn_lft45,grub_turn_lft,
	grub_spawn, grub_jump, grub_idle_dead_2, grub_idle_dead_1, grub_idle,
	grub_falling, grub_attack_setal, grub_attack
};
class cGrub : public cEnemy
{
private:
	cSkinnedMesh* grub;		//�� �޽�
	GRUB_STATE nowState;		//���� �� ����
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

	void AttackSet(D3DXVECTOR3& vPosition);	//������ġ�� �޾Ƽ� �����Ÿ� �ȿ� ������ ���ݸ��
	void AnimationSetting();
	void RandomAnimation();
	void ResetAnimaitionTime();
	void ChangeAnimation(GRUB_STATE state);
	bool EndFrame();
};

