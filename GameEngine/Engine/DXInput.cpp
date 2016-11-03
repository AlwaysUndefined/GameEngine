#pragma once
#include <DXInput.h>
namespace GameEngine
{
	Mouse::Mouse(HWND hwnd)
		{
			Mouse::hwnd = hwnd;
			GetClientRect(hwnd, &clientRect);
			p1.x = clientRect.right;
			p1.y = clientRect.bottom;
		}
	void Mouse::MouseInit(LPDIRECT3DTEXTURE9 mouseIcon)
	{
		ClientToScreen(hwnd, &p0);
		ClientToScreen(hwnd, &p1);
		mousePos.x = p0.x + (p1.x - p0.x) / 2;
		mousePos.y = p0.y + (p1.y - p0.y) / 2;
		Mouse::mouseIcon = mouseIcon;
		SetCursorPos(mousePos.x,mousePos.y);
		mouseClinetPos.x = mousePos.x;
		mouseClinetPos.y = mousePos.y;
		ScreenToClient(hwnd, &mouseClinetPos);
		position.x = mouseClinetPos.x;
		position.y = mouseClinetPos.y;
	}
	void Mouse::MousePosUpdate()
	{
		GetCursorPos(&mouseClinetPos);
		ScreenToClient(hwnd, &mouseClinetPos);
		position.x = mouseClinetPos.x;
		position.y = mouseClinetPos.y;
	}
	/*
	从DX9Device获取输入设备
	*/

	DXInput::DXInput(
		HWND hwnd,
		LPDIRECTINPUT8 dxInput,
		LPDIRECTINPUTDEVICE8 dxKeyBoardDevice,
		LPDIRECTINPUTDEVICE8 dxMouseDevice)
	{
		DXInput::hwnd = hwnd;
		DXInput::dxInput = dxInput;
		DXInput::dxKeyBoardDevice = dxKeyBoardDevice;
		DXInput::dxMouseDevice = dxMouseDevice;

		mousePoint = new Point(0, 0);
		//初始化输入缓冲区
		ZeroMemory(keyStateBuffer, sizeof(char) * 256);
		ZeroMemory(&mouseState, sizeof(mouseState));
	}
	//获取输入轮询
	void DXInput::GetInputLoop()
	{
		HRESULT hr;
		hr = dxKeyBoardDevice->GetDeviceState(sizeof(keyStateBuffer), (void**)&keyStateBuffer);
		if (hr)
		{
		dxKeyBoardDevice->Acquire();
		dxKeyBoardDevice->GetDeviceState(sizeof(keyStateBuffer), (LPVOID)&keyStateBuffer);
		}
		hr = dxMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&mouseState);
		if (hr)
		{
		dxMouseDevice->Acquire();
		dxMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&mouseState);
		}
	}
	//输入判断
	bool DXInput::IsKeyDown(int iKey)
	{
		if (keyStateBuffer[iKey] & 0x80)
		{
		return true;
		}
		return false;
		}
	bool DXInput::IsMouseButtonDown(int button)
	{
		GetMousePosition();
		return (mouseState.rgbButtons[button] & 0x80) != 0;
	}
	Point DXInput::GetMousePosition()
	{
		POINT mousePOINT;
		GetCursorPos(&mousePOINT);
		ScreenToClient(hwnd, &mousePOINT);
		mousePoint->X = mousePOINT.x;
		mousePoint->Y = mousePOINT.y;
		return Point(mousePOINT.x, mousePOINT.y);
	}
}