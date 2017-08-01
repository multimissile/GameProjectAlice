#pragma once

/* ���� ������ */

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

	bool m_bGame;		//������������ �ƴҶ� game manager���� �ƹ��͵� ���� ���ϵ��� �ϱ�����..

	//1. ĳ����
	cPlayer* m_pPlayer;

	//2. ��
	vector<cEnemy*> m_vecEnemy;
	//3. ������Ʈ
	vector <cTerainObject*> m_vecTerrainObject;
	//4. Ÿ��	
	cTerrain* m_pTerrain;
	//5. ������
	vector <cItemObject*> m_vecItemObject;	//����Ʈ�� �ٲ� ����
	//6. �̺�Ʈ


	

	


public:
	void LoadGame(const char* szFolder, const char* szFile);
	//�ӽÿ�
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

