#include "stdafx.h"
#include "cPlayer.h"
#include "cAllocateHierarchy.h"
//#include "iMap.h"
//#include "cCamera.h"

//바운딩박스로 추가
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

#define FLOAT_JUMPSTR 1.75
#define FLOAT_GRAVITY 0.1
#define FLOAT_MOVESPEED 0.2f

cPlayer::cPlayer() :state(CHARACTER_Idle), m_pAttackBound(NULL), CHAR_DIR(dir8)//, m_pCamera(NULL)
{
	m_fRotationY = 0.0f;
	m_pSkinnedMesh = NULL;
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vDirection = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	fJumpStr = FLOAT_JUMPSTR;
	D3DXMatrixIdentity(&m_matWorld);
	isDash = false;
	isJump = false;
	isAttack = false;
	isUp1 = false;
	fRunSpeed = FLOAT_MOVESPEED;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pAttackBound);
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
//	//선회용으로 필요
//	D3DXMATRIXA16 matR, matT;
//
//	m_pMap = pMap;
//	float fmoveSpeed = 0.5f;
//	D3DXVECTOR3 vPosition = m_vPosition;
//
//	//카메라 돌면 캐릭터도 돌게 설정
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
//	//움직임 테스트와 키 테스트
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
//		////최대 애니메이션으로 가면 다음으로 넘긴다.
//		////애니메이션 끝나면 
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
//			//트랙포지션이 0 부터 시작해야하므로 SetAnimationIndexBlend 를 사용하여 트랙포지션을 0으로 만듦과 동시에
//			// 이전 애니메이션에서 현재애니메이션으로 넘어오는것이 어색하지 않도록 blend
//			m_pSkinnedMesh->SetAnimationIndexBlend(state);
//		}
//
//	}
//
//	//이동
//	if (pMap) {
//		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z)) {
//			m_vPosition = vPosition;
//		}
//	}
//
//	//선회
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
//	//1 indexBlend 사용하기 (다음애니메이션과 이전애니메이션이 부드럽지 않다, 애니메이션 트랙포지션이 그대로유지된다.
//	//m_pSkinnedMesh->SetAnimationIndexBlend(n++);
//
//	//2 Index 사용하기 (다음애니메이션과 이전애니메이션 사이의 움직임을 부드럽게 blend 한다. 애니메이션트랙포지션이 0이 된다.
//	////m_pSkinnedMesh->SetAnimationIndex(1);
//	//}
//
//
//}

void cPlayer::Setup(char * szFolder, char * szFile, float fScale)
{
	m_pSkinnedMesh = new cSkinnedMesh(szFolder, szFile, fScale);
	m_pSkinnedMesh->SetAnimationIndexBlend(state);

	//앨리스 나이프 본으로 지정
	m_pSkinnedMesh->SetAttackBone(0);

	cBoundingBox* pB = new cBoundingBox;
	pB->Setup(m_pSkinnedMesh->GetMax(), m_pSkinnedMesh->GetMin());
	m_pBounding = pB;

	/*cBoundingBox* pS = new cBoundingBox;
	D3DXMATRIX* pWorkPalette =  m_pSkinnedMesh->GetWorkPalette();
	pS->Setup(
		D3DXVECTOR3(pWorkPalette->_41, pWorkPalette->_42, pWorkPalette->_43),
		D3DXVECTOR3(pWorkPalette->_41 + 10.0, pWorkPalette->_42 + 10.0, pWorkPalette->_43 + 10.0)
	);*/
	/*ST_BONE* pBone = m_pSkinnedMesh->GetAttackBone();
	pS->Setup(
		D3DXVECTOR3(pBone->TransformationMatrix._41, pBone->TransformationMatrix._42, pBone->TransformationMatrix._43),
		D3DXVECTOR3(pBone->TransformationMatrix._41 + 10.0, pBone->TransformationMatrix._42 + 10.0, pBone->TransformationMatrix._43 + 10.0)
	);*/
	//m_pAttackBound = pS;
	cBoundingSphere* pBS = new cBoundingSphere;
	pBS->Setup(D3DXVECTOR3(10, 10, 10), D3DXVECTOR3(-10, -10, -10));
	m_pAttackBound = pBS;
}

void cPlayer::Update()
{
	//공격 바운딩박스 뼈 이용시
	/*ST_BONE* pBone = m_pSkinnedMesh->GetAttackBone();
	if (pBone != NULL && m_pAttackBound != NULL) {
		D3DXMATRIX* matRT;
		matRT = &pBone->TransformationMatrix;
		m_pAttackBound->Update(matRT);
	}*/
	if (m_pAttackBound != NULL) {
		D3DXMATRIX* matRT;
		matRT = m_pSkinnedMesh->GetWorkPalette();
		m_pAttackBound->Update(matRT);
	}
	
	
	//------------------------------------------------------------

	//선회용으로 필요
	D3DXMATRIXA16 matR, matT;

	//m_pMap = pMap;

	D3DXVECTOR3 vPosition = m_vPosition;


	//캐릭터 스테이트 바뀔때 애니메이션 연결안돼서 따로 지정
	CHARACTER_STATE st = state;

	//>>:카메라 전역으로 수정
	//카메라 돌면 캐릭터도 돌게 설정

	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);
	D3DXVECTOR3 CameraDir = this->GetPosition() - *g_pCam->GetEye();
	CameraDir.y = 0.0f;
	D3DXVec3Normalize(&CameraDir, &CameraDir);

	D3DXVECTOR3 v90;
	D3DXVec3Cross(&v90, &vUp, &CameraDir);
	D3DXVECTOR3 vDirection;

	switch (CHAR_DIR) {
	case dir8: {
		vDirection = CameraDir;
		break;
	}
	case dir7: {
		vDirection = (CameraDir - v90)/2;
		break;
	}
	case dir9: {
		vDirection = (CameraDir + v90) / 2;
		//D3DXVec3TransformCoord(&vDirection, &CameraDir, &matR);
		break;
	}
	case dir4: {
		vDirection = -v90;
		break;
	}
	case dir1: {
		vDirection = (-CameraDir - v90) / 2;
		break;
	}
	case dir3: {
		vDirection = (-CameraDir + v90) / 2;
		break;
	}
	case dir6: {
		vDirection = v90;
		break;
	}
	case dir2: {
		vDirection = -CameraDir;
		break;
	}
	}
	
	D3DXVECTOR3 vLDir;
	D3DXVec3Cross(&vLDir, &vUp, &vDirection);

	D3DXVECTOR3 vRDir = -vLDir;

	float fDotL = D3DXVec3Dot(&vLDir, &m_vDirection);
	float fDotR = D3DXVec3Dot(&vRDir, &m_vDirection);

	

	/*LDirection = (LCameraDir + LDirection) / 2;
	RDirection = (RCameraDir + RDirection) / 2;*/

	if (abs(fDotL - fDotR) > 0.1f) {
		if (fDotL < fDotR) {
			m_fRotationY += 0.05f;
		}
		else {
			m_fRotationY -= 0.05f;
		}
	}


	if (g_pKeyManager->IsOnceKeyDown(VK_SHIFT)) {
		isDash = true;
	}
	if (g_pKeyManager->IsOnceKeyUp(VK_SHIFT)) {
		isDash = false;
	}

	if (isAttack) {
		if (m_pSkinnedMesh->GetCurrentAnimationEnd(state)) {
			switch (state) {
				/*case CHARACTER_attack1: {
				//IsIdle = true;
				ChangeState(CHARACTER_attack1f);
				break;
				}
				case CHARACTER_attack1f: {
				IsIdle = true;
				ChangeState(CHARACTER_attack2);
				break;
				}*/
			case CHARACTER_attack2: {
				st = CHARACTER_attack2f;
				break;
			}
			case CHARACTER_attack2f: {
				isAttack = false;
				//ChangeState(CHARACTER_attack3);
				break;
			}
			}
		}
	}
	//움직임 테스트와 키 테스트
	else {
		float fSpeed;
		if (isDash) {
			if (fRunSpeed < FLOAT_MOVESPEED * 2) {
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
		if (g_pKeyManager->IsStayKeyDown('W'))
		{
			if (g_pKeyManager->IsStayKeyDown('A')) {
				CHAR_DIR = dir7;
			}
			else  if (g_pKeyManager->IsStayKeyDown('D')) {
				CHAR_DIR = dir9;
			}
			else {
				CHAR_DIR = dir8;
			}
			vPosition += vDirection * fSpeed;



			////최대 애니메이션으로 가면 다음으로 넘긴다.
			////애니메이션 끝나면 
			//if(m_pSkinnedMesh->GetCurrentAnimationEnd())
			//	m_pSkinnedMesh->SetAnimationIndexBlend(28);


		}
		else if (g_pKeyManager->IsStayKeyDown('S'))
		{
			if (g_pKeyManager->IsStayKeyDown('A')) {
				CHAR_DIR = dir1;
			}
			else  if (g_pKeyManager->IsStayKeyDown('D')) {
				CHAR_DIR = dir3;
			}
			else {
				CHAR_DIR = dir2;
			}
			vPosition += vDirection * fSpeed;
		}
		else if (g_pKeyManager->IsStayKeyDown('A'))
		{
			CHAR_DIR = dir4;
			vPosition += vDirection * fSpeed;
		}
		else if (g_pKeyManager->IsStayKeyDown('D'))
		{
			CHAR_DIR = dir6;
			vPosition += vDirection * fSpeed;
		}
		/*else if (g_pKeyManager->IsStayKeyDown('S'))
		{
			st = (CHARACTER_STATE)10;
			vPosition -= m_vDirection * FLOAT_MOVESPEED;
		}
		*/
		else 
		{
			//state = CHARACTER_Idle;
			//트랙포지션이 0 부터 시작해야하므로 SetAnimationIndexBlend 를 사용하여 트랙포지션을 0으로 만듦과 동시에
			// 이전 애니메이션에서 현재애니메이션으로 넘어오는것이 어색하지 않도록 blend
			//m_pSkinnedMesh->SetAnimationIndexBlend(state);
			st = CHARACTER_Idle;
		}
		/*else if (state != CHARACTER_Idle)
		{
			//state = CHARACTER_Idle;
			//트랙포지션이 0 부터 시작해야하므로 SetAnimationIndexBlend 를 사용하여 트랙포지션을 0으로 만듦과 동시에
			// 이전 애니메이션에서 현재애니메이션으로 넘어오는것이 어색하지 않도록 blend
			//m_pSkinnedMesh->SetAnimationIndexBlend(state);
			st = CHARACTER_Idle;
		}*/
	}

	//점프 부분
	if (isJump) {
		//등가속운동
		fJumpStr -= FLOAT_GRAVITY;
		if (fJumpStr >= 0) {
			bool IsEnd = m_pSkinnedMesh->GetCurrentAnimationEnd(state);
			if (state == CHARACTER_Jump_Start && m_pSkinnedMesh->GetCurrentAnimationEnd(state)) {
				isUp1 = false;
			}
			if (isUp1) {
				st = CHARACTER_Jump_Start;
			}
			else {
				st = CHARACTER_Idle;
			}

		}
		else {
			st = CHARACTER_Jump_Fall;
			if (state == CHARACTER_Jump_Fall && m_pSkinnedMesh->GetCurrentAnimationEnd(state)) {
				st = CHARACTER_Jump_Land;
			}
		}

		vPosition += D3DXVECTOR3(0, 0.3f, 0)*fJumpStr;

		if (g_pGameManager->GetPlayerColllisionGround(vPosition)) {
			isJump = false;
		}
		/*if (fJumpStr <= -FLOAT_JUMPSTR) {
		isJump = false;
		}*/
	}
	else {
		fJumpStr = FLOAT_JUMPSTR;
	}


	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE) && !isAttack) {
		isJump = true;
		isUp1 = true;
	}

	//>>: 맵높이 gameManager 에서 바로 가져올 수 있도록 수정
	//이동
	if (isJump) {
		m_vPosition = vPosition;
	}
	else {
		if (g_pGameManager->GetHeight(vPosition.x, vPosition.y, vPosition.z)) {
			m_vPosition = vPosition;
		}
	}
	//<<
	//애니메이션 출력
	ChangeState(st);

	//선회

	D3DXMatrixRotationY(&matR, m_fRotationY);
	m_vDirection = D3DXVECTOR3(0, 0, -1);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR*matT;

	//>>:바운딩박스업데이트
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

	//>:scale 값은 skinnedmesh가 알아서 갖고 있도록 수정
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

void cPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (!isJump) {
			isAttack = true;
			//ChangeState(CHARACTER_attack1);
			//ChangeState(CHARACTER_attack1f);
			ChangeState(CHARACTER_attack2);
			//ChangeState(CHARACTER_attack2f);
			//ChangeState(CHARACTER_attack3);
		}
		break;
	}
	}
}

cBounding * cPlayer::GetAttackBound()
{
	return m_pAttackBound;
}

