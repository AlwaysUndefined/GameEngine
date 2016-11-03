#include <windows.h>
#include <Engine.h>
#include <Game.h>
using namespace std;
using namespace GameEngine;


//�����
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"Game"
#define WNDCLASS_NAME L"main"
#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}	//�ͷ�COM���õĺ�

Engine* engine;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//�������
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = WNDCLASS_NAME;

	//����ע��
	if (!RegisterClassEx(&wndClass)) return -1;
	//���崴��
	HWND hwnd = CreateWindow(WNDCLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL
		);
	/*
	********************************������Ϸ����*****************************
	*/
	engine = new Engine(hwnd,hInstance);
	engine->Init();
	/*
	********************************������Ϸ����*****************************
	*/
	//�����ƶ���ʾ����
	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
	
	/*
	********************************��ʽ������ �ͻ�����С********************************
	*/
	engine->SetClientSize();
	/*
	********************************��ʽ������ �ͻ�����С********************************
	*/
	//��ʾ���壬���潫����WM_PAINT�¼�
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	/*
	********************************������������********************************
	*/
	engine->Start();
	/*
	********************************������������********************************
	*/
	//��Ϣѭ��
	MSG msg = { 0 };
	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->EventLoop();
		}
	}
	UnregisterClass(WNDCLASS_NAME, wndClass.hInstance);
	return 0;
}

//��Ϣ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		engine->DefaultRender();
		ValidateRect(hwnd, NULL);
		break;
	case WM_DESTROY:
		engine->CleanUp();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	return 0;
}