#pragma once

/*게임이 실행되는 메인 클래스*/
class cGrid;
class cCamera;

class cCharacterTest;
class c170720Test2;
class cUITest;

enum SCENE
{
	SCN_1,
	SCN_2,
	SCN_NUM
};
class cMainGame
{

public:
	cMainGame();
	~cMainGame();
private:

	//sprite image 그려줄 수 있는애 모든 UI는 얘를 가져다 그립니다
	LPD3DXSPRITE m_pSprite;
	cCamera* m_pCamera;
	cGrid* m_pGrid;

	//c170720Test2* m_pTest;
	cCharacterTest* m_pCharacterTest;
	cUITest* m_pUITest;

	
	SCENE m_enCurrent;
public:

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();

};

