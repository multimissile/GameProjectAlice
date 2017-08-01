#include "stdafx.h"
#include "cGrub.h"
#include "cSkinnedMesh.h"

cGrub::cGrub()
{
	D3DXMatrixIdentity(&m_matWorld);
}


cGrub::~cGrub()
{
	SAFE_DELETE(grub);
}

void cGrub::Setup()
{
	grub = new cSkinnedMesh("Source/Game/Enemy","Grub.x");
	//위치 초기화
	m_vPosition = { 0.f,0,0.f };
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//상태 초기화
	nowState = grub_idle;
	grub->SetAnimationIndexBlend((GRUB_STATE)nowState);
	nowTime = 0;
	maxTime = 0;
}

void cGrub::Setup(float _x, float _y, float _z)
{
	grub = new cSkinnedMesh("Source/Game/Enemy", "Grub.x");
	
	m_vPosition = { _x,_y,_z };
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;

	nowState = grub_spawn;
	grub->SetAnimationIndexBlend((GRUB_STATE)nowState);
	nowTime = 0;
	maxTime = 0;
	isAtk = false;
}

// walk  거리 0.85
// attack_set 거리 5.68
// turn_rgt45 or turn_lft45 각도 rotY = 0.8;

// turn_rgt 생략...
void cGrub::Update()
{
	//state에따라서 변하는 모션 모아둠
	if(isAtk ==false)
		AnimationSetting();

	//>>:높이설정
	


	D3DXMATRIXA16 matS, matT,matR;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = {0,0,-1};
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS *matR* matT;
}

void cGrub::Render()
{
	//생성된놈을 월드로 옮겨주기
	grub->SetTransform(&m_matWorld);
	
	//생성된 놈 그려줌
	grub->UpdateAndRender();
}

void cGrub::AttackSet(D3DXVECTOR3 & vPosition)
{
	userPos = vPosition;
	saveDir= vPosition - m_vPosition;
	dis = sqrtf((saveDir.x * saveDir.x) + (saveDir.y * saveDir.y) + (saveDir.z * saveDir.z));
}

void cGrub::AnimationSetting()
{
		switch (nowState)
		{
		case grub_walk:
			if (EndFrame())
			{
				ChangeAnimation(grub_idle);
				m_vPosition = m_vPosition + m_vDirection*0.85f;
			}
			break;
		case grub_turn_rgt45:
			if (EndFrame())
			{
				ChangeAnimation(grub_idle);
				m_fRotY += 0.8f;
			}
			break;
		case grub_turn_rgt:
			break;
		case grub_turn_lft45:
			if (EndFrame())
			{
				ChangeAnimation(grub_idle);
				m_fRotY -= 0.8f;
			}
			break;
		case grub_turn_lft:
			break;
		case grub_spawn:
			if (EndFrame())
			{
				ChangeAnimation(grub_idle);
			}
			break;
		case grub_jump:
			if (EndFrame())
			{
				ChangeAnimation(grub_idle);
				m_vPosition = m_vPosition + m_vDirection* 1.8f;
			}
			break;
		case grub_attack:
			if (EndFrame())
			{
				ChangeAnimation(grub_attack_setal);
			}
			break;
		case grub_attack_setal:
			if (EndFrame())
			{
				isAtk = false;
				m_vPosition = m_vPosition + m_vDirection* 5.68f;
				ChangeAnimation(grub_idle);
			}
			break;
		case grub_idle_dead_2:
			// 불값을 트루로 해서 객체생성된곳에 넘겨주고 객체 딜리트
			break;
		case grub_idle_dead_1:
			// 불값을 트루로 해서 객체생성된곳에 넘겨주고 객체 딜리트
			break;
		case grub_idle:
			if (EndFrame())
			{
				if (3.f < dis && dis <= 6.f)
				{
					D3DXVECTOR3 v1, v2;
					D3DXVec3Normalize(&v1, &m_vDirection);
					D3DXVec3Normalize(&v2, &saveDir);
					float deg = D3DXVec3Dot(&v1, &v2);
					deg = acosf(deg);
					if (m_vPosition.x < userPos.x && m_vPosition.z > userPos.z)
						m_fRotY -= deg;
					else if (m_vPosition.x > userPos.x && m_vPosition.z > userPos.z)
						m_fRotY += deg;
					else if (m_vPosition.x < userPos.x && m_vPosition.z < userPos.z)
						m_fRotY += deg;
					else if (m_vPosition.x > userPos.x && m_vPosition.z < userPos.z)
						m_fRotY -= deg;
					else
						m_fRotY = deg;

					m_vDirection = saveDir;
					ChangeAnimation(grub_attack);
				}
				else
					RandomAnimation();
			}
			break;
		case grub_falling:
			break;
	
		}
	
	

}

//랜덤으로 모션 설정해줌
void cGrub::RandomAnimation()
{
	int rndNum = rand() % 4;
	switch (rndNum)
	{
	case 0:
		ChangeAnimation(grub_walk);
		break;
	case 1:
		ChangeAnimation(grub_turn_rgt45);
		break;
	case 2:
		ChangeAnimation(grub_turn_lft45);
		break;
	case 3:
		ChangeAnimation(grub_jump);
		break;
	default:
		ChangeAnimation(grub_idle);
		break;
	}
}

//애니메이션 타임을 초기화 한다.
void cGrub::ResetAnimaitionTime()
{
	LPD3DXANIMATIONSET ani;
	grub->GetAniController()->GetAnimationSet(nowState, &ani);
	//현재 애니메이션이 다도는데 까지 걸리는 시간(s)
	maxTime = ani->GetPeriod();

	D3DXTRACK_DESC pDesc;
	grub->GetAniController()->GetTrackDesc(0, &pDesc);

	//현재 애니메이션이 돌아간 시간
	//1개 애니메이션을 계속해서 돌리면 프레임이 0으로 돌아가도 이시간은 0으로 돌아가지 않기때문에 
	//애니메이션 프레임이 끝나면 IDLE 로 상태를 바꿔주어야한다......
	nowTime = pDesc.Position;
}

//애니메이션 바꿔줌
void cGrub::ChangeAnimation(GRUB_STATE state)
{
	nowState = state;
	grub->SetAnimationIndexBlend(nowState);
}

bool cGrub::EndFrame()
{
	ResetAnimaitionTime();

	//애니메이션의 프레임이 다돌았을 때 트루를 리턴한다.
	if (nowTime >= maxTime - 0.032)
		return true;

	return false;
}
