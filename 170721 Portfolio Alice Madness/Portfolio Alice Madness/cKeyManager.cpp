#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
	//모든 키눌림정보 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		//맨처음 모든 키는 안눌러져있다고 초기화
		this->GetKeyUp().set(i, false);
		this->GetKeyUp().set(i, false);
	}
}


cKeyManager::~cKeyManager()
{
}

bool cKeyManager::IsOnceKeyDown(int key)
{
	//키가 눌렸는데
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//해당 키가 눌려있지 않다 라고 저장되어있다면
		if (!this->GetKeyDown()[key])
		{
			//눌렸다 저장하고
			SetKeyDown(key, true);
			//true 리턴
			return true;

		}
	}
	//키가 눌리지 않았다면 ( 방금 눌렀다 떨어진 경우까지 포함)
	else 
		SetKeyDown(key, false);

	return false;
}

bool cKeyManager::IsOnceKeyUp(int key)
{
	//방금 키가 눌렸다면
	if (GetAsyncKeyState(key) & 0x8000)
		//키Up 정보를 참으로 바꾸어주고
		SetKeyUp(key, true);
	//눌리지 않았을때
	else
	{
		//해당 키의 눌림Up가 참이라고 저장되어있었다면
		if (GetKeyUp()[key])
		{
			SetKeyUp(key, false);
			return true;
		}

	}

	return false;
}

bool cKeyManager::IsStayKeyDown(int key)
{
	//키가 눌렸는지 아닌지에 대한정보를 리턴
	if (GetAsyncKeyState(key) & 0x8000) 
		return true;

	return false;
}

bool cKeyManager::IsToggleKey(int key)
{
	//토글상태인가에 대한 정보를 리턴
	if (GetKeyState(key) & 0x0001) 
		return true;

	return false;
}
