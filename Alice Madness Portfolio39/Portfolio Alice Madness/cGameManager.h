#pragma once

/* 게임 관리자 */

#define g_pGameManager cGameManager::GetInstance()

class cTerrain;
class cPlayer;
class cTerainObject;
class cItemObject;
class cBounding;

class cEnemy;



class cGameManager
{
	SINGLETON(cGameManager);
private:

	bool m_bGame;		//게임진행중이 아닐때 game manager에서 아무것도 얻지 못하도록 하기위해..

	//1. 캐릭터
	cPlayer* m_pPlayer;

	//2. 적
	vector<cEnemy*> m_vecEnemy;
	//3. 오브젝트
	vector <cTerainObject*> m_vecTerrainObject;
	//4. 타일	
	cTerrain* m_pTerrain;
	//5. 아이템
	vector <cItemObject*> m_vecItemObject;	//리스트로 바꿀 예정
	//6. 이벤트


	

	


public:
	void LoadGame(const char* szFolder, const char* szFile);
	//임시용
	void DestroyGame();

	void Update();
	void Render();

	bool CheckCollision(cBounding* pB_this, D3DXVECTOR3& vDirection);
	bool GetHeight(IN float& x, _Inout_ float& y, IN float& z);
	void SetupTerrainObject();
	void SetupItemObject();
	void SetupEnemy();

	cBounding* GetPlayerBounding();
	void DeleteItem(cItemObject* pThis);


};

