#pragma once

/* 캐릭터들의 노드입니다. */


class cCharacter
{
public:
	cCharacter();
	virtual ~cCharacter();

private:
	int m_nHP;

	virtual void Dead();
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();

	//지형알기 위한 변수 추가 예정
	

};

