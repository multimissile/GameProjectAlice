#pragma once


class cScene
{
public:
	cScene();
	virtual ~cScene();
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render(LPD3DXSPRITE pSprite) = 0;
};

