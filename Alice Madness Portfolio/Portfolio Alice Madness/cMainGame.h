#pragma once

/*게임이 실행되는 메인 클래스*/
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

	//sprite image 그려줄 수 있는애 모든 UI는 얘를 가져다 그립니다
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

