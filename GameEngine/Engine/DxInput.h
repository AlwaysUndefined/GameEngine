#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	class Mouse
	{
	public:
		HWND hwnd=NULL;
		LPDIRECT3DTEXTURE9 mouseIcon = NULL;//鼠标指针
		//鼠标屏幕坐标（相对于屏幕原点）
		POINT mousePos = {0,0};
		//鼠标客户区坐标（相对于客户区原点）
		POINT mouseClinetPos = {0,0};
		//客户区
		RECT clientRect;
		//客户区原点以及最大点的屏幕位置
		POINT p0 = { 0,0 };
		POINT p1 = { 0,0 };
		//鼠标在窗体的绝对位置
		D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
		Mouse(HWND hwnd);
		void MouseInit(LPDIRECT3DTEXTURE9 mouseIcon);
		void MousePosUpdate();
	};
	/*
	从DX9Device获取输入设备
	*/
	class DXInput
	{
	public:
		//窗体信息
		HWND hwnd;
		//输入缓冲区
		char keyStateBuffer[256];//键盘上256键状态
		DIMOUSESTATE mouseState;
		//输入设备
		LPDIRECTINPUT8 dxInput = NULL;
		LPDIRECTINPUTDEVICE8 dxKeyBoardDevice = NULL;
		LPDIRECTINPUTDEVICE8 dxMouseDevice = NULL;
		Point* mousePoint;
		DXInput(
			HWND hwnd,
			LPDIRECTINPUT8 dxInput,
			LPDIRECTINPUTDEVICE8 dxKeyBoardDevice,
			LPDIRECTINPUTDEVICE8 dxMouseDevice);
		//获取输入轮询
		void GetInputLoop();
		//输入判断
		bool IsKeyDown(int iKey);
		bool IsMouseButtonDown(int button);
		Point GetMousePosition();
	private:

	};
}