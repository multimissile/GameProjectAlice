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
	//위치 초기화
	m_vPosition = { 0.f,3.f,-0.f };
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//상태 초기화
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
	//위치 초기화
	m_vPosition = { _x, _y, _z};
	centerPos.x = m_vPosition.x - cosf(m_fRotY)*0.5f;
	centerPos.y = m_vPosition.y;
	centerPos.z = m_vPosition.z + sinf(m_fRotY)*0.5f;
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//상태 초기화
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
	//생성된놈을 월드로 옮겨주기
	fly->SetTransform(&m_matWorld);

	//생성된 놈 그려줌
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
	//현재 애니메이션이 다도는데 까지 걸리는 시간(s)
	maxTime = ani->GetPeriod();

	D3DXTRACK_DESC pDesc;
	fly->GetAniController()->GetTrackDesc(0, &pDesc);

	//현재 애니메이션이 돌아간 시간
	//1개 애니메이션을 계속해서 돌리면 프레임이 0으로 돌아가도 이시간은 0으로 돌아가지 않기때문에 
	//애니메이션 프레임이 끝나면 IDLE 로 상태를 바꿔주어야한다......
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
	//애니메이션의 프레임이 다돌았을 때 트루를 리턴한다.
	if (nowTime >= maxTime - 0.032)
	{
		return true;
	}

	return false;
}
