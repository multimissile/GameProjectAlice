#pragma once

class cSpriteImage;
class cBox;


class cUITest
{

	//�ڽ��� �̹����� ���ľ� �Ѵ�

public:
	cUITest();
	~cUITest();
private:
	cSpriteImage* m_pSpriteImage;
	cSpriteImage* m_ptitlePlayerMenu_I4A;
	cSpriteImage* m_ptitlePlayerMenu_I4C;
	cSpriteImage* m_ptitlePlayerMenu_I4F;
	cBox*	m_pBox;
	cBox*	m_pBox2;
	cBox*	m_pBox3;
	cBox*	m_pBox4;





public:
	void Setup();
	void Update();
	void Render(LPD3DXSPRITE pSprite);
};

