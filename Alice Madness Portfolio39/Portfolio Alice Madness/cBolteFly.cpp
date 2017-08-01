#include "stdafx.h"
#include "cBolteFly.h"
#include "cSkinnedMesh.h"

cBolteFly::cBolteFly()
{
}


cBolteFly::~cBolteFly()
{
}

void cBolteFly::Setup()
{
	fly = new cSkinnedMesh("Source/Game/Enemy", "Boltefly.x");
	//��ġ �ʱ�ȭ
	m_vPosition = { 0.f,3.f,-0.f };
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//���� �ʱ�ȭ
	nowState = fly_strafe_sprint;
	fly->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
	deg = 0.0f;
	setPos = false;


}

void cBolteFly::Setup(float _x, float _y, float _z)
{
	fly = new cSkinnedMesh("Source/Game/Enemy", "Boltefly.x");
	//��ġ �ʱ�ȭ
	m_vPosition = {_x,_y,_z };
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//���� �ʱ�ȭ
	nowState = fly_strafe_sprint;
	fly->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
	deg = 0.0f;
	setPos = false;
}

void cBolteFly::Update()
{
	AnimationSetting();

	//sprint ������� �ٲ𶧸� ������ġ���� ���������� 6��ŭ ���������� �������� ���Ѵ�.
	if (setPos)
	{
		centerPos.x = m_vPosition.x - cosf(m_fRotY)*6.f;
		centerPos.y = m_vPosition.y;
		centerPos.z = m_vPosition.z + sinf(m_fRotY)*6.f;
		setPos = false;
	}
	

	D3DXMATRIXA16 matS, matT, matR;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 0.02f, 0.02f, 0.02f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = { 0,0,-1 };
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS *matR* matT;

	
}

void cBolteFly::Render()
{
	//�����ȳ��� ����� �Ű��ֱ�
	fly->SetTransform(&m_matWorld);

	//������ �� �׷���
	fly->UpdateAndRender();

}

void cBolteFly::AttackSet(D3DXVECTOR3 & vPosition)
{
	userPos = vPosition;
	saveDir = vPosition - m_vPosition;
	dis = sqrtf((saveDir.x * saveDir.x) + (saveDir.y * saveDir.y) + (saveDir.z * saveDir.z));
}

void cBolteFly::AnimationSetting()
{
	switch (nowState)
	{
	case fly_walk_2:
		m_vPosition = m_vPosition + m_vDirection* FLYSPEED;
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_walk_1:
		m_vPosition = m_vPosition + m_vDirection* FLYSPEED;
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_strafe_r:
		m_vPosition.x = m_vPosition.x + cosf(m_fRotY)*FLYSPEED;
		m_vPosition.z = m_vPosition.z - sinf(m_fRotY)* FLYSPEED;
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_strafe_l:
		m_vPosition.x = m_vPosition.x + cosf(m_fRotY)*FLYSPEED;
		m_vPosition.z = m_vPosition.z + sinf(m_fRotY)* FLYSPEED;
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_strafe_sprint:
		deg += 0.08f;
		m_fRotY += 0.08f;
		m_vPosition.x = centerPos.x + cosf(deg)*6.f;
		m_vPosition.z = centerPos.z - sinf(deg)*6.f;
		if (EndFrame())
				RandomAnimation();
		break;
	case fly_leeching_detach:
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_leeching_attach:
		if (EndFrame())
			ChangeAnimation(fly_leeching_detach);
		break;
	case fly_leeching:
		if (EndFrame())
			ChangeAnimation(fly_leeching_attach);
		break;
	case fly_damage:
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	case fly_attack:
		if (EndFrame())
			ChangeAnimation(fly_strafe_sprint);
		break;
	default:
		break;
	}
	
}

void cBolteFly::RandomAnimation()
{
	int rndNum = rand() % 5;
	switch (rndNum)
	{
	case 0:
		ChangeAnimation(fly_walk_1);
		break;
	case 1:
		ChangeAnimation(fly_walk_2);
		break;
	case 2:
		ChangeAnimation(fly_strafe_l);
		break;
	case 3:
		ChangeAnimation(fly_strafe_r);
		break;
	case 4:
		ChangeAnimation(fly_strafe_sprint);
		break;
	}
}

void cBolteFly::ResetAnimaitionTime()
{
	LPD3DXANIMATIONSET ani;
	fly->GetAniController()->GetAnimationSet(nowState, &ani);
	//���� �ִϸ��̼��� �ٵ��µ� ���� �ɸ��� �ð�(s)
	maxTime = ani->GetPeriod();

	D3DXTRACK_DESC pDesc;
	fly->GetAniController()->GetTrackDesc(0, &pDesc);

	//���� �ִϸ��̼��� ���ư� �ð�
	//1�� �ִϸ��̼��� ����ؼ� ������ �������� 0���� ���ư��� �̽ð��� 0���� ���ư��� �ʱ⶧���� 
	//�ִϸ��̼� �������� ������ IDLE �� ���¸� �ٲ��־���Ѵ�......
	nowTime = pDesc.Position;
}

void cBolteFly::ChangeAnimation(BOLTEFLY_STATE state)
{
	if (state == fly_strafe_sprint)
		setPos = true;


	nowState = state;
	fly->SetAnimationIndexBlend(nowState);
}

bool cBolteFly::EndFrame()
{
	ResetAnimaitionTime();
	//�ִϸ��̼��� �������� �ٵ����� �� Ʈ�縦 �����Ѵ�.
	if (nowTime >= maxTime - 0.032)
	{
		return true;
	}

	return false;
}
