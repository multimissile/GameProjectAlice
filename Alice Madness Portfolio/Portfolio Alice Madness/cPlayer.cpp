#include "stdafx.h"
#include "cPlayer.h"
//#include "iMap.h"
//#include "cCamera.h"

//�ٿ���ڽ��� �߰�
#include "cBoundingBox.h"

#define FLOAT_JUMPSTR 1.0
#define FLOAT_GRAVITY 0.1
#define FLOAT_MOVESPEED 0.2f

cPlayer::cPlayer():state(CHARACTER_Idle)//, m_pCamera(NULL)
{
	m_fRotationY = 0.0f;
	m_pSkinnedMesh = NULL;
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vDirection = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	fJumpStr = FLOAT_JUMPSTR;
	D3DXMatrixIdentity(&m_matWorld);
	isDash = false;
	isJump = false;
	fRunSpeed = FLOAT_MOVESPEED;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

//void cPlayer::Setup()
//{
//	SetMesh(new cSkinnedMesh("TestFolder", "alice_knife.X"));
//	m_pSkinnedMesh->SetAnimationIndexBlend(state);
//}
//void cPlayer::SetCamera(cCamera * pCamera)
//{
//	m_pCamera = pCamera;
//}
//void cPlayer::Update(iMap* pMap)
//{
//	//��ȸ������ �ʿ�
//	D3DXMATRIXA16 matR, matT;
//
//	m_pMap = pMap;
//	float fmoveSpeed = 0.5f;
//	D3DXVECTOR3 vPosition = m_vPosition;
//
//	//ī�޶� ���� ĳ���͵� ���� ����
//	D3DXVECTOR3 CameraDir = this->GetPosition() - g_pCamera->vGetEye();
//	CameraDir.y = 0.0f;
//	D3DXVec3Normalize(&CameraDir, &CameraDir);
//	
//	D3DXMatrixRotationY(&matR, 90);
//	D3DXVECTOR3 LCameraDir;
//	D3DXVec3TransformNormal(&LCameraDir, &CameraDir, &matR);
//
//	D3DXMatrixRotationY(&matR, -90);
//	D3DXVECTOR3 RCameraDir;
//	D3DXVec3TransformNormal(&RCameraDir, &CameraDir, &matR);
//
//	float fDotL= D3DXVec3Dot(&LCameraDir, &m_vDirection);
//	float fDotR= D3DXVec3Dot(&RCameraDir, &m_vDirection);
//
//	if (abs(fDotL - fDotR) > 0.2f) {
//		if (fDotL <= fDotR) {
//			m_fRotY += 0.1f;
//		}
//		else {
//			m_fRotY -= 0.1f;
//		}
//	}
//	
//	/*if (g_pKeyManager->IsStayKeyDown('A'))
//	{
//		//state = CHARACTER_Idle;
//
//		m_fRotY -= 0.1f;
//	}
//	else if (g_pKeyManager->IsStayKeyDown('D'))
//	{
//		//state = CHARACTER_Idle;
//
//		m_fRotY += 0.1f;
//	}*/
//
//	//������ �׽�Ʈ�� Ű �׽�Ʈ
//	if (g_pKeyManager->IsStayKeyDown('W'))
//	{
//		
//		if (state != CHARACTER_Alice_Walk)
//		{
//			state = CHARACTER_Alice_Walk;
//			m_pSkinnedMesh->SetAnimationIndexBlend(state);
//		}
//		vPosition += m_vDirection * fmoveSpeed;
//
//
//
//		////�ִ� �ִϸ��̼����� ���� �������� �ѱ��.
//		////�ִϸ��̼� ������ 
//		//if(m_pSkinnedMesh->GetCurrentAnimationEnd())
//		//	m_pSkinnedMesh->SetAnimationIndexBlend(28);
//
//
//	}
//
//	else if (g_pKeyManager->IsStayKeyDown('S'))
//	{
//
//		if (state != (CHARACTER_STATE)10)
//		{
//			state = (CHARACTER_STATE)10;
//
//			m_pSkinnedMesh->SetAnimationIndexBlend(state);
//		}
//
//		vPosition -= m_vDirection * fmoveSpeed;
//	}
//
//	else if (state != CHARACTER_Idle)
//	{
//		{
//			state = CHARACTER_Idle;
//			//Ʈ���������� 0 ���� �����ؾ��ϹǷ� SetAnimationIndexBlend �� ����Ͽ� Ʈ���������� 0���� ����� ���ÿ�
//			// ���� �ִϸ��̼ǿ��� ����ִϸ��̼����� �Ѿ���°��� ������� �ʵ��� blend
//			m_pSkinnedMesh->SetAnimationIndexBlend(state);
//		}
//
//	}
//
//	//�̵�
//	if (pMap) {
//		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z)) {
//			m_vPosition = vPosition;
//		}
//	}
//
//	//��ȸ
//	
//	D3DXMatrixRotationY(&matR, m_fRotY);
//	m_vDirection = D3DXVECTOR3(0, 0, -1);
//
//	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
//
//	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//	m_matWorld = matR*matT;
//
//	
//
//	//if (g_pKeyManager->IsOnceKeyDown('1'))
//	//{
//	//static int n = 0;	
//
//	//1 indexBlend ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼��� �ε巴�� �ʴ�, �ִϸ��̼� Ʈ���������� �״�������ȴ�.
//	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);
//
//	//2 Index ����ϱ� (�����ִϸ��̼ǰ� �����ִϸ��̼� ������ �������� �ε巴�� blend �Ѵ�. �ִϸ��̼�Ʈ���������� 0�� �ȴ�.
//	////m_pSkinnedMesh->SetAnimationIndex(1);
//	//}
//
//
//}

void cPlayer::Setup(char * szFolder, char * szFile, float fScale)
{
	m_pSkinnedMesh = new cSkinnedMesh(szFolder, szFile, fScale);
	m_pSkinnedMesh->SetAnimationIndexBlend(state);

	cBoundingBox* pB = new cBoundingBox;
	pB->Setup(m_pSkinnedMesh->GetMax(), m_pSkinnedMesh->GetMin());
	m_pBounding = pB;


}

void cPlayer::Update()
{
	//��ȸ������ �ʿ�
	D3DXMATRIXA16 matR, matT;

	//m_pMap = pMap;
	
	D3DXVECTOR3 vPosition = m_vPosition;


//>>:ī�޶� �������� ����
	//ī�޶� ���� ĳ���͵� ���� ����
	D3DXVECTOR3 CameraDir = this->GetPosition() - g_pCamera->vGetEye();
	CameraDir.y = 0.0f;
	D3DXVec3Normalize(&CameraDir, &CameraDir);

	D3DXMatrixRotationY(&matR, 90);
	D3DXVECTOR3 LCameraDir;
	D3DXVec3TransformNormal(&LCameraDir, &CameraDir, &matR);

	D3DXMatrixRotationY(&matR, -90);
	D3DXVECTOR3 RCameraDir;
	D3DXVec3TransformNormal(&RCameraDir, &CameraDir, &matR);

	D3DXMatrixRotationY(&matR, 80);
	D3DXVECTOR3 Direction90;
	D3DXVec3TransformNormal(&Direction90, &m_vDirection, &matR);

	float fDotL = D3DXVec3Dot(&LCameraDir, &m_vDirection);
	float fDotR = D3DXVec3Dot(&RCameraDir, &m_vDirection);

	/*LDirection = (LCameraDir + LDirection) / 2;
	RDirection = (RCameraDir + RDirection) / 2;*/

	if (abs(fDotL - fDotR) > 0.2f) {
		if (fDotL <= fDotR) {
			m_fRotationY += 0.1f;
		}
		else {
			m_fRotationY -= 0.1f;
		}
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_SHIFT)) {
		isDash = true;
	}
	if (g_pKeyManager->IsOnceKeyUp(VK_SHIFT)) {
		isDash = false;
	}
	if (g_pKeyManager->IsStayKeyDown('A'))
	{
		ChangeState(CHARACTER_cStarfL);
		vPosition += Direction90 * FLOAT_MOVESPEED;
	}
	else if (g_pKeyManager->IsStayKeyDown('D'))
	{
		ChangeState(CHARACTER_cStartfR);
		vPosition -= Direction90 * FLOAT_MOVESPEED;
	}

	//������ �׽�Ʈ�� Ű �׽�Ʈ
	else if (g_pKeyManager->IsStayKeyDown('W'))
	{
		float fSpeed;
		CHARACTER_STATE st;
		if (isDash) {
			if (fRunSpeed < FLOAT_MOVESPEED*2) {
				fRunSpeed += 0.01f;
			}
			fSpeed = fRunSpeed;
			st = CHARACTER_Run;
		}
		else {
			fRunSpeed = 0.2f;
			fSpeed = FLOAT_MOVESPEED;
			st = CHARACTER_Alice_Walk;
		}
		ChangeState(st);
		vPosition += m_vDirection * fSpeed;



		////�ִ� �ִϸ��̼����� ���� �������� �ѱ��.
		////�ִϸ��̼� ������ 
		//if(m_pSkinnedMesh->GetCurrentAnimationEnd())
		//	m_pSkinnedMesh->SetAnimationIndexBlend(28);


	}

	else if (g_pKeyManager->IsStayKeyDown('S'))
	{
		ChangeState((CHARACTER_STATE)10);

		vPosition -= m_vDirection * FLOAT_MOVESPEED;
	}

	else if (state != CHARACTER_Idle)
	{
		{
			//state = CHARACTER_Idle;
			//Ʈ���������� 0 ���� �����ؾ��ϹǷ� SetAnimationIndexBlend �� ����Ͽ� Ʈ���������� 0���� ����� ���ÿ�
			// ���� �ִϸ��̼ǿ��� ����ִϸ��̼����� �Ѿ���°��� ������� �ʵ��� blend
			//m_pSkinnedMesh->SetAnimationIndexBlend(state);
			ChangeState(CHARACTER_Idle);
		}

	}

	//���� �κ�
	if (isJump) {
		//��ӿ
		fJumpStr -= FLOAT_GRAVITY;
		if (fJumpStr >= 0) {
			ChangeState(CHARACTER_Jump_Start);
		}
		else {
			ChangeState(CHARACTER_Jump_Fall);
		}

		vPosition += D3DXVECTOR3(0, 1, 0)*fJumpStr;

		//if (g_pGameManager->)
		if (fJumpStr <= -FLOAT_JUMPSTR) {
			isJump = false;
		}
	}
	else {
		fJumpStr = FLOAT_JUMPSTR;
	}


	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE)) {
		isJump = true;
	}

//>>: �ʳ��� gameManager ���� �ٷ� ������ �� �ֵ��� ����
	//�̵�
	if (isJump) {
		m_vPosition = vPosition;
	}
	else {
		if (g_pGameManager->GetHeight(vPosition.x, vPosition.y, vPosition.z)) {
			m_vPosition = vPosition;
		}
	}
//<<


	//��ȸ

	D3DXMatrixRotationY(&matR, m_fRotationY);
	m_vDirection = D3DXVECTOR3(0, 0, -1);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR*matT;

//>>:�ٿ���ڽ�������Ʈ
	m_pBounding->Update(&m_matWorld);
}
void cPlayer::Render()
{
	D3DXMATRIX matS, matR;
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMatrixTranslation(&matR, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matR));
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matS * matR));
	//m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&(matS*m_matWorld));

//>:scale ���� skinnedmesh�� �˾Ƽ� ���� �ֵ��� ����
	m_pSkinnedMesh->SetTransform((D3DXMATRIXA16*)&m_matWorld);

	m_pSkinnedMesh->UpdateAndRender();

}

D3DXVECTOR3& cPlayer::GetPosition()
{
	return m_vPosition;
}

void cPlayer::ChangeState(CHARACTER_STATE ALICE_STATE) {
	if (state != ALICE_STATE)
	{
		state = ALICE_STATE;
		m_pSkinnedMesh->SetAnimationIndexBlend(state);
	}
}

