#pragma once

/*������ ����Ǵ� ���� Ŭ����*/
class cGrid;
class cCamera;

class cCameraTest;
class cEntry;

class cScene;

class cMainGame
{

public:
	cMainGame();
	~cMainGame();
private:

	//sprite image �׷��� �� �ִ¾� ��� UI�� �긦 ������ �׸��ϴ�
	LPD3DXSPRITE m_pSprite;
	cCamera* m_pCamera;
	cGrid* m_pGrid;

	cCameraTest* m_pCameraTest;

	vector<cScene*> m_vecScene;
	int nCur;

public:

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

};

