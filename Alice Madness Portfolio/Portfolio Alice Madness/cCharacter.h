#pragma once

/* ĳ���͵��� ����Դϴ�. */


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

