#pragma once

/* ĳ���͵��� ����Դϴ�. */


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

	//�����˱� ���� ���� �߰� ����
	

};

