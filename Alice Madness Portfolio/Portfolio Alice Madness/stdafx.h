// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //사용되지 않는 내용 Windows 헤더에서 제거
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//D3D 헤더파일
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
//기타 추가 헤더파일
#include "Util.h"
using namespace Util;



//!매니저는 하단에 추가합니다!

//전역변수
extern HWND g_hWnd;
extern bool g_bLButtonDown;

//윈도우 스타일정의 매크로
#define WINDSTYLE (WS_OVERLAPPED | \
                   WS_CAPTION    | \
                   WS_SYSMENU    | \
                   WS_MINIMIZEBOX)
#define WINDSTARTX 50
#define WINDSTARTY 50
#define WINDSIZEX 1400
#define WINDSIZEY 900


//매크로
#define SAFE_RELEASE(p) {if(p){ p->Release(); p = NULL; }}//안전해제 //Com객체가 자신의 메모리 관리를 스스로 하도록 Release 만 호출하기
#define SAFE_DELETE(p) {if(p){ delete p; p = NULL; }}	  //안전삭제
#define SAFE_DELETE_ARRAY(p){if(p){delete []p; p = NULL;}}//배열안전삭제
//varType 객체1개 , Get / Set
#define SYNTHESIZE(varType, varName, funName)\
protected:	varType varName;\
public: inline varType Get##funName() const{return varName;}\
public: inline void Set##funName(varType var) { varName = var; }

//varType 객체1개 , 레퍼런스 Get / Set
#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected:	varType varName;\
public: inline varType& Get##funName() {return varName;}\
public: inline void Set##funName(varType& var) { varName = var; }

//p 가 존재하는 애라면 AddRef 함수를 호출
#define SAFE_ADD_REF(p) {if(p)p->AddRef();}

//ref 타입의 varType형 객체 1개 , Get / Set
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

//싱글톤
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
//싱글톤 매니저
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"
#include "cSkinnedMeshManager.h"
#include "cKeyManager.h"
#include "cMeshGroupManager.h"
#include "cFontManager.h"
#include "cSPrintDevice.h"
//#include "cCamera.h"