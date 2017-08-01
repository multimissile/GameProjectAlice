#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
	//��� Ű�������� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		//��ó�� ��� Ű�� �ȴ������ִٰ� �ʱ�ȭ
		this->GetKeyUp().set(i, false);
		this->GetKeyUp().set(i, false);
	}
}


cKeyManager::~cKeyManager()
{
}

bool cKeyManager::IsOnceKeyDown(int key)
{
	//Ű�� ���ȴµ�
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//�ش� Ű�� �������� �ʴ� ��� ����Ǿ��ִٸ�
		if (!this->GetKeyDown()[key])
		{
			//���ȴ� �����ϰ�
			SetKeyDown(key, true);
			//true ����
			return true;

		}
	}
	//Ű�� ������ �ʾҴٸ� ( ��� ������ ������ ������ ����)
	else 
		SetKeyDown(key, false);

	return false;
}

bool cKeyManager::IsOnceKeyUp(int key)
{
	//��� Ű�� ���ȴٸ�
	if (GetAsyncKeyState(key) & 0x8000)
		//ŰUp ������ ������ �ٲپ��ְ�
		SetKeyUp(key, true);
	//������ �ʾ�����
	else
	{
		//�ش� Ű�� ����Up�� ���̶�� ����Ǿ��־��ٸ�
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
	//Ű�� ���ȴ��� �ƴ����� ���������� ����
	if (GetAsyncKeyState(key) & 0x8000) 
		return true;

	return false;
}

bool cKeyManager::IsToggleKey(int key)
{
	//��ۻ����ΰ��� ���� ������ ����
	if (GetKeyState(key) & 0x0001) 
		return true;

	return false;
}
