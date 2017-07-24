#pragma once

/* 캐릭터들의 노드입니다. */


class cCharacter
{
public:
	cCharacter();
	virtual ~cCharacter();

private:
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();

};

