// Portfolio Alice Madness.cpp : 프로그램시작, 끝
//

#include "stdafx.h"
#include "Portfolio Alice Madness.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

///////////////////////////////// 전역 변수
HINSTANCE hInst;                                //현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  //제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            //기본 창 클래스 이름

HWND g_hWnd;									//현재 윈도우 
bool g_bLButtonDown = false;
bool g_bRButtonDown = false;

/////////////////////////////////

/////////////////////////////////주 게임처리 클래스
cMainGame* g_pMainGame;
/////////////////////////////////

/////////////////////////////////API 운영함수
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
/////////////////////////////////시작점

/////////////////////////////////main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PORTFOLIOALICEMADNESS, szWindowClass, MAX_LOADSTRING);

	//윈도우 클래스 정의 및 윈도우 등록
	MyRegisterClass(hInstance);

	//윈도우 생성, 창 표시
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PORTFOLIOALICEMADNESS));

	//생성
	g_pMainGame = new cMainGame;

	//초기화
	if (g_pMainGame)
		g_pMainGame->Setup();
	


    MSG msg;

	/*
	GetMessage: 메세지가 들어올 때까지 블로킹상태 다른애플리케이션이 CPU사용할 수 있도록 해줌
	PeekMessage: 메세지큐에 메세지 있는지만 검사하고 바로 리턴 CPU를 계속해서 사용하면서 While 문 안에서 메세지검사
	*/		
	while (true)
	{
		//메세지가 있다면 메세지를 받고 큐에서제거
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	
		{
			//QUIT 메세지가 들어오면 종료한다. 
			if (msg.message == WM_QUIT)
			{
				exit(0);
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		//메세지가 없다면 처리할 함수를 이곳에서 호출
		else
		{
			if (g_pMainGame)
			{
				g_pMainGame->Update();
				g_pMainGame->Render();
			}
		}
	}

	//삭제
	if (g_pMainGame)
		delete g_pMainGame;


	return (int)msg.wParam;
}

//만들고싶은 윈도우클래스의 특성을 정의하고
//윈도우를 등록한다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ALICE2));
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ALICE2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PORTFOLIOALICEMADNESS);
    wcex.lpszClassName  = szWindowClass;

    return RegisterClassExW(&wcex);
}

//HINSTANCE 핸들 전역, HWND 핸들 전역
//윈도우 생성, 창 만들기 표시하기
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   ////윈도우 창을 생성(기본)
   //g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //윈도우 창을 생성
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WINDSTYLE,
	   WINDSTARTX, WINDSTARTY, WINDSIZEX, WINDSIZEY, nullptr, nullptr, hInstance, nullptr);

   //생성 하지 못하였을 시
   if (!g_hWnd)
   {
	   return FALSE;
   }

   //윈도우창 표시(기본)
   //ShowWindow(g_hWnd, nCmdShow);
   //윈도우 창 표시
   ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);
   UpdateWindow(g_hWnd);

   return TRUE;

   //생성 하지 못하였을 시
   if (!g_hWnd)
   {
      return FALSE;
   }

   //윈도우 창 표시
   //ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);	//전체화면출력 :WINSIZE 는 무시된다.
   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}


//메세지 처리함수
//callback 형태로 메세지함수와 연관
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//메세지를 여기에도 
	if (g_pMainGame)
		g_pMainGame->WndProc(hWnd, message, wParam, lParam);

    switch (message)
    {
	//LBUTTON 
	case WM_LBUTTONDOWN:
	{
		g_bLButtonDown = true;
	} break;
	case WM_LBUTTONUP:
	{
		g_bLButtonDown = false;
	} break;

	case WM_KEYDOWN:
	{
		//DESTROY 와 같다
		switch (wParam)
		{
		case VK_F1:
			PostQuitMessage(0);
			break;
		}
	}break;
	//WM_DESTROY  - 종료 메시지를 게시하고 반환
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}
//
//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
