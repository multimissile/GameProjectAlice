#pragma once
#include "cCharacter.h"


class cPlayer :
	public cCharacter
{
public:
	cPlayer();
	~cPlayer();

private:
	void Setup();
	void Update();
	void Render();
};

