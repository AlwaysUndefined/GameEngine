#include <windows.h>
#include <Engine.h>
#include <Game.h>
using namespace std;
using namespace GameEngine;


//定义宏
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"Game"
#define WNDCLASS_NAME L"main"
#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}	//释放COM引用的宏

Engine* engine;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//窗口设计
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

	//窗口注册
	if (!RegisterClassEx(&wndClass)) return -1;
	//窗体创建
	HWND hwnd = CreateWindow(WNDCLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL
		);
	/*
	********************************创建游戏对象*****************************
	*/
	engine = new Engine(hwnd,hInstance);
	engine->Init();
	/*
	********************************创建游戏对象*****************************
	*/
	//窗体移动显示更新
	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
	
	/*
	********************************格式化窗体 客户区大小********************************
	*/
	engine->SetClientSize();
	/*
	********************************格式化窗体 客户区大小********************************
	*/
	//显示窗体，下面将发生WM_PAINT事件
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	/*
	********************************引擎正常启动********************************
	*/
	engine->Start();
	/*
	********************************引擎正常启动********************************
	*/
	//消息循环
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

//消息处理
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