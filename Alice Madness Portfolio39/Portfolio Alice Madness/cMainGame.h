#pragma once

/*������ ����Ǵ� ���� Ŭ����*/
class cGrid;
//class cCamera;
//class cScene;
//class cCameraTest;
//class cEntry;
class cWonderLand;

//class cCollisionTest;

class cMainGame
{

public:
	cMainGame();
	~cMainGame();
private:

	//sprite image �׷��� �� �ִ¾� ��� UI�� �긦 ������ �׸��ϴ�
	//LPD3DXSPRITE m_pSprite;
	//cCamera* m_pCamera;
	cGrid* m_pGrid;

	//cCameraTest* m_pCameraTest;
	cWonderLand* m_pWonderLand;

	//vector<cScene*> m_vecScene;
	//int nCur;

	//cCollisionTest*m_pCollisionTest;



public:

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

};

