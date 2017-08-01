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
	//��ġ �ʱ�ȭ
	m_vPosition = { 0.f,0,0.f };
	m_vDirection = { 0,0,-1 };
	m_fRotY = 0.f;
	//���� �ʱ�ȭ
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

// walk  �Ÿ� 0.85
// attack_set �Ÿ� 5.68
// turn_rgt45 or turn_lft45 ���� rotY = 0.8;

// turn_rgt ����...
void cGrub::Update()
{
	//state������ ���ϴ� ��� ��Ƶ�
	if(isAtk ==false)
		AnimationSetting();

	//>>:���̼���
	


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
	//�����ȳ��� ����� �Ű��ֱ�
	grub->SetTransform(&m_matWorld);
	
	//������ �� �׷���
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
			// �Ұ��� Ʈ��� �ؼ� ��ü�����Ȱ��� �Ѱ��ְ� ��ü ����Ʈ
			break;
		case grub_idle_dead_1:
			// �Ұ��� Ʈ��� �ؼ� ��ü�����Ȱ��� �Ѱ��ְ� ��ü ����Ʈ
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

//�������� ��� ��������
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

//�ִϸ��̼� Ÿ���� �ʱ�ȭ �Ѵ�.
void cGrub::ResetAnimaitionTime()
{
	LPD3DXANIMATIONSET ani;
	grub->GetAniController()->GetAnimationSet(nowState, &ani);
	//���� �ִϸ��̼��� �ٵ��µ� ���� �ɸ��� �ð�(s)
	maxTime = ani->GetPeriod();

	D3DXTRACK_DESC pDesc;
	grub->GetAniController()->GetTrackDesc(0, &pDesc);

	//���� �ִϸ��̼��� ���ư� �ð�
	//1�� �ִϸ��̼��� ����ؼ� ������ �������� 0���� ���ư��� �̽ð��� 0���� ���ư��� �ʱ⶧���� 
	//�ִϸ��̼� �������� ������ IDLE �� ���¸� �ٲ��־���Ѵ�......
	nowTime = pDesc.Position;
}

//�ִϸ��̼� �ٲ���
void cGrub::ChangeAnimation(GRUB_STATE state)
{
	nowState = state;
	grub->SetAnimationIndexBlend(nowState);
}

bool cGrub::EndFrame()
{
	ResetAnimaitionTime();

	//�ִϸ��̼��� �������� �ٵ����� �� Ʈ�縦 �����Ѵ�.
	if (nowTime >= maxTime - 0.032)
		return true;

	return false;
}
