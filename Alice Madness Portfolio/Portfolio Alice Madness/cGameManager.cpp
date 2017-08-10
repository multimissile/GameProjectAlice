#include "stdafx.h"
#include "cGameManager.h"
#include "cTerrain.h"
#include "cTerainObject.h"
#include "cItemObject.h"
#include "cBounding.h"
#include "cPlayer.h"
#include "cGrub.h"
#include "cBolteFly.h"
#include "cGruntMini.h"
#include "cNoseSwitch.h"


cGameManager::cGameManager()
	:m_pTerrain(NULL)
	//, m_pRootItem(NULL)
	, m_bGame(false)
	, m_pPlayer(NULL)
{
}


cGameManager::~cGameManager()
{


}

void cGameManager::LoadGame(const char * szFolder, const char * szFile)
{

	m_bGame = true;


	//데이터로
	m_pTerrain = new cTerrain;
	m_pTerrain->Setup();


	SetupTerrainObject();
	SetupItemObject();
	SetupEnemy();

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup("TestFolder", "alice_knife.X");

	//g_pCamera->SetPosition(&(m_pPlayer->GetBounding()->GetCenterPosition()));
	g_pCam->SetTarget(&(m_pPlayer->GetBounding()->GetCenterPosition()));
}


void cGameManager::DestroyGame()
{
	m_bGame = false;
	g_pCam->SetTarget(NULL);
	
	SAFE_DELETE(m_pTerrain);

	for (int n = 0; n < m_vecItemObject.size(); n++)
	{
		SAFE_DELETE(m_vecItemObject[n]);
	}


	for (int n = 0; n < m_vecTerrainObject.size(); n++)
	{
		SAFE_DELETE(m_vecTerrainObject[n]);
	}
	for (int n = 0; n < m_vecEnemy.size(); n++)
	{
		SAFE_DELETE(m_vecEnemy[n]);
	}


	SAFE_DELETE(m_pPlayer);

}

void cGameManager::Update()
{
	if (!m_bGame)
		return;


	for (int n = 0; n < m_vecTerrainObject.size(); n++)
	{
		m_vecTerrainObject[n]->Update();
	}
	for (int n = 0; n < m_vecItemObject.size(); n++)
	{
		m_vecItemObject[n]->Update();
	}
	for (int n = 0; n < m_vecEnemy.size(); n++)
	{
		m_vecEnemy[n]->Update();
	}

	m_pTerrain->Update();

	//if(m_pRootItem)
	//	m_pRootItem->Update();

	m_pPlayer->Update();
}

void cGameManager::Render()
{
	if (!m_bGame)
		return;

	m_pTerrain->Render();

	for (int n = 0; n < m_vecTerrainObject.size(); n++)
	{
		//그려야 할 지형인지 체크 필요
		m_vecTerrainObject[n]->Render();
	}
	for (int n = 0; n < m_vecItemObject.size(); n++)
	{
		//그려야 할 지형인지 체크 필요
		m_vecItemObject[n]->Render();
	}

	for (int n = 0; n < m_vecEnemy.size(); n++)
	{
		m_vecEnemy[n]->Render();
	}


	m_pPlayer->Render();


	static bool renderBounding = false;
	if (g_pKeyManager->IsOnceKeyDown('M'))
	{
		renderBounding = !renderBounding;
	}


	//바운딩박스 또는 구 보거나
	if (renderBounding)
	{
		for (int n = 0; n < m_vecTerrainObject.size(); n++)
		{
			//그려야 할 지형인지 체크 필요
			m_vecTerrainObject[n]->GetBounding()->OBBBox_Render();
		}

		m_pPlayer->GetBounding()->OBBBox_Render();
		//m_pRootItem->GetBounding()->OBBBox_Render();
		for (int n = 0; n < m_vecItemObject.size(); n++)
		{
			//그려야 할 지형인지 체크 필요
			m_vecItemObject[n]->GetBounding()->OBBBox_Render();
		}
	}

}


bool cGameManager::CheckCollision(cBounding * pB_this, D3DXVECTOR3& vDirection)
{
	//충돌체크
	//예정
	return false;
}

bool cGameManager::GetHeight(IN float & x, float & y, IN float& z)
{
	if (!m_bGame)
		return false;

	float fY = y;

	//일단은 terrain의 높이만 얻어오기
	return m_pTerrain->GetHeight(x, y, z);

}

void cGameManager::SetupTerrainObject()
{
	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "MossRockA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(100, 0, 30));

	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "MossRockA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(80, 0, 80));

	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "MossRockA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(80, 40, 80));


	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "MossRockA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(40, -20, -20));





	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "GiantToys_DominoA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(-20, 0, -10));

	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "GiantToys_DominoA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(-30, 0, -15));

	m_vecTerrainObject.push_back(new cTerainObject);
	m_vecTerrainObject.back()->Setup("Source/Game/Object", "GiantToys_DominoA.X");
	m_vecTerrainObject.back()->SetPosition(D3DXVECTOR3(-40, 0, -10));


}

void cGameManager::SetupItemObject()
{

	cItemObject* pItemObject = new cItemObject;
	pItemObject->Setup("Source/Game/Object", "Tooth.X");
	pItemObject->SetPosition(D3DXVECTOR3(-2, 4, 4));
	m_vecItemObject.push_back(pItemObject);

	pItemObject = new cItemObject;
	pItemObject->Setup("Source/Game/Object", "Tooth.X");
	pItemObject->SetPosition(D3DXVECTOR3(-2, 4, 8));
	m_vecItemObject.push_back(pItemObject);

	pItemObject = new cItemObject;
	pItemObject->Setup("Source/Game/Object", "Tooth.X");
	pItemObject->SetPosition(D3DXVECTOR3(-2, 4, 12));
	m_vecItemObject.push_back(pItemObject);



	pItemObject = new cItemObject;
	pItemObject->Setup("Source/Game/Object", "Tooth.X");
	pItemObject->SetPosition(D3DXVECTOR3(-5, 10, -30));
	m_vecItemObject.push_back(pItemObject);
	//NewItem(pItemObject);

	pItemObject = new cItemObject;
	pItemObject->Setup("Source/Game/Object", "Tooth.X");
	pItemObject->SetPosition(D3DXVECTOR3(10, 0, 10));
	m_vecItemObject.push_back(pItemObject);
	//NewItem(pItemObject);


}

void cGameManager::SetupEnemy()
{
	m_vecEnemy.push_back(new cGrub);
	m_vecEnemy.back()->Setup(0.f, 0.f, 3.f);

	m_vecEnemy.push_back(new cBolteFly);
	m_vecEnemy.back()->Setup(2.f, 0.f, 3.f);

	m_vecEnemy.push_back(new cNoseSwitch);
	m_vecEnemy.back()->Setup(-5.f, 0.f, -6.f);

	m_vecEnemy.push_back(new cGruntMini);
	m_vecEnemy.back()->Setup(10.f, 0.f, -4.f);

}

cBounding * cGameManager::GetPlayerBounding()
{
	return m_pPlayer->GetBounding();
}

void cGameManager::DeleteItem(cItemObject* pThis)
{
	vector <cItemObject*>::iterator iter;

	for (iter = m_vecItemObject.begin(); iter != m_vecItemObject.end(); iter++)
	{
		if (*iter == pThis)
			break;
	}

	m_vecItemObject.erase(iter);
	SAFE_DELETE(pThis);

}

bool cGameManager::GetPlayerColllisionGround(D3DXVECTOR3 vPosition)
{
	if (!m_bGame)
		return false;

	//일단은 terrain의 높이만 얻어오기
	return m_pTerrain->GetPlayerCollision(vPosition);

}

void cGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (m_pPlayer)
		m_pPlayer->WndProc(hWnd, message, wParam, lParam);
}