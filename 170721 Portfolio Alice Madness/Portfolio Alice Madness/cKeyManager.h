#pragma once

/* 키눌림등의 정보를 쉽게 얻기 위한 클래스입니다. */

#define g_pKeyManager cKeyManager::GetInstance()

#define KEYMAX 256

class cKeyManager
{
	SINGLETON(cKeyManager);

	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp;

public:
	bool IsOnceKeyDown(int key);	//키가1번 눌렸는지
	bool IsOnceKeyUp(int key);		//방금 키가 눌렸다떨어졌는지
	bool IsStayKeyDown(int key);	//키를 누른 상태인지
	bool IsToggleKey(int key);		//토글상태인지
	
private:

	inline bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	inline bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	inline void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	inline void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }

};

