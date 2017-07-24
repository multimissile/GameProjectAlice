#pragma once

#include "cScene.h"
class cSpriteImage;

class cEntry : public cScene
{
	cSpriteImage* m_pBackGround;
	cSpriteImage* m_pLogo;

public:
	cEntry();
	~cEntry();

	void Setup();
	void Update();
	void Render(LPD3DXSPRITE pSprite);
};

