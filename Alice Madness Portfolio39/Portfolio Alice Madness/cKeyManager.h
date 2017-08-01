#pragma once

/* Ű�������� ������ ���� ��� ���� Ŭ�����Դϴ�. */

#define g_pKeyManager cKeyManager::GetInstance()

#define KEYMAX 256

class cKeyManager
{
	SINGLETON(cKeyManager);

	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp;

public:
	bool IsOnceKeyDown(int key);	//Ű��1�� ���ȴ���
	bool IsOnceKeyUp(int key);		//��� Ű�� ���ȴٶ���������
	bool IsStayKeyDown(int key);	//Ű�� ���� ��������
	bool IsToggleKey(int key);		//��ۻ�������
	
private:

	inline bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	inline bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	inline void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	inline void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }

};

