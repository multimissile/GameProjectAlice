#include "stdafx.h"
#include "cGruntMini.h"
#include "cSkinnedMesh.h"

cGruntMini::cGruntMini()
{
}


cGruntMini::~cGruntMini()
{
	SAFE_DELETE(grunt);
}

void cGruntMini::Setup()
{
	grunt = new cSkinnedMesh("Source/Game/Enemy", "Grunt_Mini.x");
	//위치 초기화
	m_vPosition = { 0.f,0,0.f };
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//상태 초기화
	nowState = grunt_strafe_walk_r;
	grunt->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
}

void cGruntMini::Setup(float _x, float _y, float _z)
{
	grunt = new cSkinnedMesh("Source/Game/Enemy", "Grunt_Mini.x");
	//위치 초기화
	m_vPosition = { _x, _y, _z };
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//상태 초기화
	nowState = grunt_spawn_3;
	grunt->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
}

void cGruntMini::Update()
{
		AnimationSetting();

	D3DXMATRIXA16 matS, matT, matR;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = { 0,0,-1 };
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS *matR* matT;
}

void cGruntMini::Render()
{
	grunt->SetTransform(&m_matWorld);

	grunt->UpdateAndRender();
}

void cGruntMini::AttackSet(D3DXVECTOR3 & vPosition)
{
	userPos = vPosition;
	saveDir = vPosition - m_vPosition;
	dis = sqrtf((saveDir.x * saveDir.x) + (saveDir.y * saveDir.y) + (saveDir.z * saveDir.z));
}

void cGruntMini::AnimationSetting()
{
	switch (nowState)
	{
	case grunt_damage_l_3:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_damage_l_2:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_damage_l_1:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_warn:
		break;
	case grunt_taunt_3:
		break;
	case grunt_taunt_2:
		break;
	case grunt_taunt_1:
		break;
	case grunt_strafe_walk_r:
		m_vPosition.x = m_vPosition.x - cosf(m_fRotY)*WALKSPEED;
		m_vPosition.z = m_vPosition.z + sinf(m_fRotY)*WALKSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_walk_l:
		m_vPosition.x = m_vPosition.x + cosf(m_fRotY)*WALKSPEED;
		m_vPosition.z = m_vPosition.z + sinf(m_fRotY)*WALKSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_walk_f:
		m_vPosition = m_vPosition + m_vDirection*WALKSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_walk_b:
		m_vPosition = m_vPosition - m_vDirection*WALKSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_run_r:
		m_vPosition.x = m_vPosition.x - cosf(m_fRotY)*RUNSPEED;
		m_vPosition.z = m_vPosition.z + sinf(m_fRotY)*RUNSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_run_l:
		m_vPosition.x = m_vPosition.x + cosf(m_fRotY)*RUNSPEED;
		m_vPosition.z = m_vPosition.z + sinf(m_fRotY)*RUNSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_run_f:
		m_vPosition = m_vPosition + m_vDirection*RUNSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_strafe_run_b:
		m_vPosition = m_vPosition - m_vDirection*RUNSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_spawn_4:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_spawn_3:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_spawn_2:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_spawn_1:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_falling:
		break;
	case grunt_die_3:
		break;
	case grunt_die_2:
		break;
	case grunt_die_1:
		break;
	case grunt_damage_h_2:
		m_vPosition = m_vPosition - m_vDirection*WALKSPEED*0.5f;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_damage_h_1:
		m_vPosition = m_vPosition - m_vDirection*WALKSPEED*0.5f;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_idle:
		if (EndFrame())
			RandomAnimation();
		break;
	case grunt_rotation_attack_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_rotation_attack_start:
		m_vPosition = m_vPosition + m_vDirection*RUNSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_rotation_attack_end);
		break;
	case grunt_smash_attack_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_smash_attack_start:
		m_vPosition = m_vPosition + m_vDirection*WALKSPEED*2;
		if (EndFrame())
			ChangeAnimation(grunt_smash_attack_end);
		break;
	case grunt_stand_attack_2_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_stand_attack_2_start:
		if (EndFrame())
			ChangeAnimation(grunt_stand_attack_2_end);
		break;
	case grunt_stand_attack_1_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_stand_attack_1_start:
		if (EndFrame())
			ChangeAnimation(grunt_stand_attack_1_end);
		break;
	case grunt_head_attack:
		m_vPosition = m_vPosition + m_vDirection*WALKSPEED;
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_move_attack_2_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_move_attack_2_start:
		m_vPosition = m_vPosition + m_vDirection*RUNSPEED*1.5;
		if (EndFrame())
			ChangeAnimation(grunt_move_attack_2_end);
		break;
	case grunt_move_attack_1_end:
		if (EndFrame())
			ChangeAnimation(grunt_idle);
		break;
	case grunt_move_attack_1_start:
		m_vPosition = m_vPosition + m_vDirection*RUNSPEED*1.5;
		if (EndFrame())
			ChangeAnimation(grunt_move_attack_1_end);
		break;
	default:
		break;
	}
}

void cGruntMini::RandomAnimation()
{
	int rndNum = rand() % 15;

	switch (rndNum)
	{
	case 0:
		ChangeAnimation(grunt_move_attack_1_start);
		break;
	case 1: 
		ChangeAnimation(grunt_move_attack_2_start);
		break;
	case 2:
		ChangeAnimation(grunt_stand_attack_1_start);
		break;
	case 3:
		ChangeAnimation(grunt_stand_attack_2_start);
		break;
	case 4:
		ChangeAnimation(grunt_head_attack);
		break;
	case 5:
		ChangeAnimation(grunt_strafe_run_b);
		break;
	case 6:
		ChangeAnimation(grunt_strafe_run_f);
		break;
	case 7:
		ChangeAnimation(grunt_strafe_run_r);
		break;
	case 8:
		ChangeAnimation(grunt_strafe_run_l);
		break;
	case 9:
		ChangeAnimation(grunt_strafe_walk_b);
		break;
	case 10:
		ChangeAnimation(grunt_strafe_walk_f);
		break;
	case 11:
		ChangeAnimation(grunt_strafe_walk_l);
		break;
	case 12:
		ChangeAnimation(grunt_strafe_walk_r);
		break;
	case 13:
		ChangeAnimation(grunt_rotation_attack_start);
		break;
	case 14:
		ChangeAnimation(grunt_smash_attack_start);
		break;
	}
}

void cGruntMini::ResetAnimaitionTime()
{
	LPD3DXANIMATIONSET ani;
	grunt->GetAniController()->GetAnimationSet(nowState, &ani);
	maxTime = ani->GetPeriod();

	D3DXTRACK_DESC pDesc;
	grunt->GetAniController()->GetTrackDesc(0, &pDesc);
	nowTime = pDesc.Position;
}

void cGruntMini::ChangeAnimation(GRUNT_STATE state)
{
	nowState = state;
	grunt->SetAnimationIndexBlend(nowState);
}

bool cGruntMini::EndFrame()
{
	ResetAnimaitionTime();

	//애니메이션의 프레임이 다돌았을 때 트루를 리턴한다.
	if (nowTime >= maxTime - 0.032)
		return true;

	return false;
}
