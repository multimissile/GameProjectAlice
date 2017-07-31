#include "stdafx.h"
#include "cNoseSwitch.h"
#include "cSkinnedMesh.h"

cNoseSwitch::cNoseSwitch()
{
}


cNoseSwitch::~cNoseSwitch()
{
}

void cNoseSwitch::Setup()
{
	fly = new cSkinnedMesh("Source/Game/Enemy", "NoseSwitch.x");
	//��ġ �ʱ�ȭ
	m_vPosition = { 0.f,3.f,-0.f };
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//���� �ʱ�ȭ
	nowState = nose_fly_idle_1;
	fly->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
	deg = 0.0f;
	setPos = false;
}

void cNoseSwitch::Setup(float _x, float _y, float _z)
{
	fly = new cSkinnedMesh("Source/Game/Enemy", "NoseSwitch.x");
	//��ġ �ʱ�ȭ
	m_vPosition = { _x, _y, _z};
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//���� �ʱ�ȭ
	nowState = nose_fly_idle_1;
	fly->SetAnimationIndexBlend(nowState);
	nowTime = 0;
	maxTime = 0;
	deg = 0.0f;
	setPos = false;


}

void cNoseSwitch::Update()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_RIGHT))
	{
		nowState = (NOSE_STATE)(nowState + 1);
		ChangeAnimation(nowState);
	}
	D3DXMATRIXA16 matS, matT, matR;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = { 0,0,-1 };
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS *matR* matT;
}

void cNoseSwitch::Render()
{
	//�����ȳ��� ����� �Ű��ֱ�
	fly->SetTransform(&m_matWorld);

	//������ �� �׷���
	fly->UpdateAndRender();

}

void cNoseSwitch::AttackSet(D3DXVECTOR3 & vPosition)
{
}

void cNoseSwitch::AnimationSetting()
{
}

void cNoseSwitch::RandomAnimation()
{
}

void cNoseSwitch::ResetAnimaitionTime()
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

void cNoseSwitch::ChangeAnimation(NOSE_STATE state)
{
	nowState = state;
	fly->SetAnimationIndexBlend(nowState);
}

bool cNoseSwitch::EndFrame()
{
	ResetAnimaitionTime();
	//�ִϸ��̼��� �������� �ٵ����� �� Ʈ�縦 �����Ѵ�.
	if (nowTime >= maxTime - 0.032)
	{
		return true;
	}

	return false;
}
