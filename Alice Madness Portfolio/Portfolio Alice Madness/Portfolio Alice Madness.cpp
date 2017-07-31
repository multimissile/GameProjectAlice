// Portfolio Alice Madness.cpp : ���α׷�����, ��
//

#include "stdafx.h"
#include "Portfolio Alice Madness.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

///////////////////////////////// ���� ����
HINSTANCE hInst;                                //���� �ν��Ͻ�
WCHAR szTitle[MAX_LOADSTRING];                  //���� ǥ���� �ؽ�Ʈ
WCHAR szWindowClass[MAX_LOADSTRING];            //�⺻ â Ŭ���� �̸�

HWND g_hWnd;									//���� ������ 
bool g_bLButtonDown = false;
bool g_bRButtonDown = false;

/////////////////////////////////

/////////////////////////////////�� ����ó�� Ŭ����
cMainGame* g_pMainGame;
/////////////////////////////////

/////////////////////////////////API ��Լ�
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
/////////////////////////////////������

/////////////////////////////////main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PORTFOLIOALICEMADNESS, szWindowClass, MAX_LOADSTRING);

	//������ Ŭ���� ���� �� ������ ���
	MyRegisterClass(hInstance);

	//������ ����, â ǥ��
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PORTFOLIOALICEMADNESS));

	//����
	g_pMainGame = new cMainGame;

	//�ʱ�ȭ
	if (g_pMainGame)
		g_pMainGame->Setup();
	


    MSG msg;

	/*
	GetMessage: �޼����� ���� ������ ���ŷ���� �ٸ����ø����̼��� CPU����� �� �ֵ��� ����
	PeekMessage: �޼���ť�� �޼��� �ִ����� �˻��ϰ� �ٷ� ���� CPU�� ����ؼ� ����ϸ鼭 While �� �ȿ��� �޼����˻�
	*/		
	while (true)
	{
		//�޼����� �ִٸ� �޼����� �ް� ť��������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	
		{
			//QUIT �޼����� ������ �����Ѵ�. 
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
		//�޼����� ���ٸ� ó���� �Լ��� �̰����� ȣ��
		else
		{
			if (g_pMainGame)
			{
				g_pMainGame->Update();
				g_pMainGame->Render();
			}
		}
	}

	//����
	if (g_pMainGame)
		delete g_pMainGame;


	return (int)msg.wParam;
}

//�������� ������Ŭ������ Ư���� �����ϰ�
//�����츦 ����Ѵ�.
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

//HINSTANCE �ڵ� ����, HWND �ڵ� ����
//������ ����, â ����� ǥ���ϱ�
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   ////������ â�� ����(�⺻)
   //g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //������ â�� ����
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WINDSTYLE,
	   WINDSTARTX, WINDSTARTY, WINDSIZEX, WINDSIZEY, nullptr, nullptr, hInstance, nullptr);

   //���� ���� ���Ͽ��� ��
   if (!g_hWnd)
   {
	   return FALSE;
   }

   //������â ǥ��(�⺻)
   //ShowWindow(g_hWnd, nCmdShow);
   //������ â ǥ��
   ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);
   UpdateWindow(g_hWnd);

   return TRUE;

   //���� ���� ���Ͽ��� ��
   if (!g_hWnd)
   {
      return FALSE;
   }

   //������ â ǥ��
   //ShowWindow(g_hWnd, SW_SHOWMAXIMIZED);	//��üȭ����� :WINSIZE �� ���õȴ�.
   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}


//�޼��� ó���Լ�
//callback ���·� �޼����Լ��� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//�޼����� ���⿡�� 
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
		//DESTROY �� ����
		switch (wParam)
		{
		case VK_F1:
			PostQuitMessage(0);
			break;
		}
	}break;
	//WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}
//
//// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
