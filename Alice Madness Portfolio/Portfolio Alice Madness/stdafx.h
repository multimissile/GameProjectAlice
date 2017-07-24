// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //������ �ʴ� ���� Windows ������� ����
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//D3D �������
#include <d3dx9.h>
//stl
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include<queue>
#include <assert.h>
#include <bitset>
using namespace std;
//��Ÿ �߰� �������
#include "Util.h"
using namespace Util;



//!�Ŵ����� �ϴܿ� �߰��մϴ�!

//��������
extern HWND g_hWnd;
extern bool g_bLButtonDown;

//������ ��Ÿ������ ��ũ��
#define WINDSTYLE (WS_OVERLAPPED | \
                   WS_CAPTION    | \
                   WS_SYSMENU    | \
                   WS_MINIMIZEBOX)
#define WINDSTARTX 50
#define WINDSTARTY 50
#define WINDSIZEX 1400
#define WINDSIZEY 900


//��ũ��
#define SAFE_RELEASE(p) {if(p){ p->Release(); p = NULL; }}//�������� //Com��ü�� �ڽ��� �޸� ������ ������ �ϵ��� Release �� ȣ���ϱ�
#define SAFE_DELETE(p) {if(p){ delete p; p = NULL; }}	  //��������
#define SAFE_DELETE_ARRAY(p){if(p){delete []p; p = NULL;}}//�迭��������
//varType ��ü1�� , Get / Set
#define SYNTHESIZE(varType, varName, funName)\
protected:	varType varName;\
public: inline varType Get##funName() const{return varName;}\
public: inline void Set##funName(varType var) { varName = var; }

//varType ��ü1�� , ���۷��� Get / Set
#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected:	varType varName;\
public: inline varType& Get##funName() {return varName;}\
public: inline void Set##funName(varType& var) { varName = var; }

//p �� �����ϴ� �ֶ�� AddRef �Լ��� ȣ��
#define SAFE_ADD_REF(p) {if(p)p->AddRef();}

//ref Ÿ���� varType�� ��ü 1�� , Get / Set
#define SYNTHESIZE_ADD_REF(varType, varName,funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const{return varName;}\
public: virtual void Set##funName(varType var){\
		if(varName!= var)\
		{\
		SAFE_ADD_REF(var);\
		SAFE_RELEASE(varName);\
		varName = var;\
		}\
	}

//�̱���
#define SINGLETON(class_name) \
	private:\
		class_name(void);\
		~class_name(void);\
	public:\
static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}
//�̱��� �Ŵ���
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"
#include "cSkinnedMeshManager.h"
#include "cKeyManager.h"
#include "cMeshGroupManager.h"
#include "cFontManager.h"
#include "cSPrintDevice.h"
//#include "cCamera.h"