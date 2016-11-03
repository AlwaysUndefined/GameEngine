#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	class DX9Device
	{
	public:
		HWND hwnd = NULL;
		HINSTANCE hInstance = NULL;
		int vp;
		D3DCAPS9 caps;
		Size clientSize;
		LPDIRECT3DDEVICE9 dxDevice = NULL;
		LPD3DXSPRITE dxSprite = NULL;
		ID3DXFont* dxFont = NULL;
		//输入设备--键盘，鼠标
		LPDIRECTINPUT8 dxInput = NULL;
		LPDIRECTINPUTDEVICE8 dxKeyBoardDevice = NULL;
		LPDIRECTINPUTDEVICE8 dxMouseDevice = NULL;

		//输入缓冲区
		char keyStateBuffer[256];//键盘上256键状态
		DIMOUSESTATE mouseState;
		//
		Point* MousePoint;

		DX9Device();
		DX9Device(HWND hwnd, HINSTANCE hInstance, Size clientSize);
		//检查DX组件（包括设备对象）是否成功创建
		HRESULT DX9Init();
		HRESULT CreateTexture(LPCTSTR pSrcFile, Size s, LPDIRECT3DTEXTURE9* lppTexture, D3DXIMAGE_INFO* imgInfo);
		HRESULT CreateTexture(LPCTSTR pSrcFile, Size s, LPDIRECT3DTEXTURE9* lppTexture);
		HRESULT CreateDevice();
		HRESULT CreateSprite();
		HRESULT CreateDXFont();
		HRESULT CreateDXInput();
		HRESULT CreateKeyBoardDevice();
		HRESULT CreateMouseDevice();
//*************************输入检测****************************
		//获取输入轮询
		void InputLoop();
		//输入判断
		bool IsKeyDown(int iKey);
		bool IsMouseButtonDown(int button);
		Point GetMousePosition();
		void CleanUp();
		~DX9Device();
	private:
	};
}
