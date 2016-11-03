#pragma once
#include <DX9Device.h>
namespace GameEngine
{
	DX9Device::DX9Device()
		{

		}
	DX9Device::DX9Device(HWND hwnd, HINSTANCE hInstance, Size clientSize)
		{
			DX9Device::hwnd = hwnd;
			DX9Device::hInstance = hInstance;
			DX9Device::clientSize = clientSize;

			MousePoint = new Point(0, 0);
			//初始化输入缓冲区
			ZeroMemory(keyStateBuffer, sizeof(char) * 256);
			ZeroMemory(&mouseState, sizeof(mouseState));
		}
	//检查DX组件（包括设备对象）是否成功创建
	HRESULT DX9Device::DX9Init()
	{
		if (CreateDevice() == E_FAIL)
			return E_FAIL;
		if (CreateSprite() == E_FAIL)
			return E_FAIL;
		if (CreateDXFont() == E_FAIL)
			return E_FAIL;
		if (CreateDXInput() == E_FAIL)
			return E_FAIL;
		if (CreateKeyBoardDevice() == E_FAIL)
			return E_FAIL;
		if (CreateMouseDevice() == E_FAIL)
			return E_FAIL;
		return S_OK;
	}
	HRESULT DX9Device::CreateTexture(LPCTSTR pSrcFile,Size s,LPDIRECT3DTEXTURE9* lppTexture, D3DXIMAGE_INFO* imgInfo)
	{
		if (D3DXCreateTextureFromFileEx(
			dxDevice,//设备
			pSrcFile,//文件路径
			s.width,//图片宽
			s.height,//图片高
			D3DX_DEFAULT,//图片的图层，一般用D3DX_DEFAULT，但也用1的
			0, //一般用的是0，也可以使用 D3DUSAGE_DYNAMIC，这样可以动态改变纹理中的数据。
			D3DFMT_UNKNOWN,//在载入图像文件时定义象素深度
			D3DPOOL_MANAGED, //如何管理这些纹理，一般使用D3DPOOL_MANAGED
			D3DX_FILTER_TRIANGLE,//图像像素的过滤方式
			D3DX_FILTER_TRIANGLE,//MIP的像素过滤方式
			D3DCOLOR_RGBA(255, 255, 255, 255), //透明色，设定这个颜色，在显示时，这图像中的这个颜色将忽略
			imgInfo,
			NULL, 
			lppTexture) != D3D_OK)
		{
			MessageBox(NULL, L"error", L"test", NULL);
			return E_FAIL;
		}
		return S_OK;
	}
	HRESULT DX9Device::CreateTexture(LPCTSTR pSrcFile, Size s, LPDIRECT3DTEXTURE9* lppTexture)
	{
		if (D3DXCreateTextureFromFileEx(
			dxDevice,//设备
			pSrcFile,//文件路径
			s.width,//图片宽
			s.height,//图片高
			D3DX_DEFAULT,//图片的图层，一般用D3DX_DEFAULT，但也用1的
			0, //一般用的是0，也可以使用 D3DUSAGE_DYNAMIC，这样可以动态改变纹理中的数据。
			D3DFMT_UNKNOWN,//在载入图像文件时定义象素深度
			D3DPOOL_MANAGED, //如何管理这些纹理，一般使用D3DPOOL_MANAGED
			D3DX_FILTER_TRIANGLE,//图像像素的过滤方式
			D3DX_FILTER_TRIANGLE,//MIP的像素过滤方式
			D3DCOLOR_RGBA(255, 255, 255, 255), //透明色，设定这个颜色，在显示时，这图像中的这个颜色将忽略
			NULL,
			NULL,
			lppTexture) != D3D_OK)
		{
			MessageBox(NULL, L"error", L"test", NULL);
			return E_FAIL;
		}
		return S_OK;
	}
	HRESULT DX9Device::CreateDevice()
	{
		//创建D3D接口
		LPDIRECT3D9 pD3D = NULL;
		if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			return E_FAIL;
		if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		{
			return E_FAIL;
		}
		//测试显卡是否支持硬件顶点运算
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//硬件顶点运算
		}
		else
		{
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//软件顶点运算
		}
		//填充内容
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = clientSize.width;
		d3dpp.BackBufferHeight = clientSize.height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = true;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		//创建设备
		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &dxDevice)))
			return E_FAIL;
		SAFE_RELEASE(pD3D);
		return S_OK;
	}
	HRESULT DX9Device::CreateSprite()
	{
		if (FAILED(D3DXCreateSprite(dxDevice, &dxSprite)))
		{
			return E_FAIL;
		}
		return S_OK;
	}
	HRESULT DX9Device::CreateDXFont()
	{
		if(FAILED(D3DXCreateFont(dxDevice,0,0,0,0,0,0,0,0,0,L"微软雅黑",&dxFont)))
		{
			return E_FAIL;
		}
		return S_OK;
	}
	HRESULT DX9Device::CreateDXInput()
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dxInput, NULL)))
		{
			return E_FAIL;
		}
		return S_OK;
	}
	HRESULT DX9Device::CreateKeyBoardDevice()
	{
		if (FAILED(dxInput->CreateDevice(GUID_SysKeyboard, &dxKeyBoardDevice, NULL)))
		{
			return E_FAIL;
		}
		//设置设备数据格式和协作格式
		dxKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);
		dxKeyBoardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		dxKeyBoardDevice->Acquire();
		dxKeyBoardDevice->Poll();
	}
	HRESULT DX9Device::CreateMouseDevice()
	{
		if (FAILED(dxInput->CreateDevice(GUID_SysMouse, &dxMouseDevice, NULL)))
		{
			return E_FAIL;
		}
		//设置设备数据格式和协作格式
		dxMouseDevice->SetDataFormat(&c_dfDIMouse);
		dxMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		dxMouseDevice->Acquire();
		dxMouseDevice->Poll();
		return S_OK;
	}
//*************************输入检测****************************
	//获取输入轮询
	void DX9Device::InputLoop()
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
	bool DX9Device::IsKeyDown(int iKey)
	{
		if (keyStateBuffer[iKey] & 0x80)
		{
			return true;
		}
		return false;
	}
	//判断鼠标键是否被按下，同时获取鼠标位置
	bool DX9Device::IsMouseButtonDown(int button)
	{
		GetMousePosition();
		return (mouseState.rgbButtons[button] & 0x80) != 0;
	}
	//获取鼠标坐标，存入MousePoint，返回Point
	Point DX9Device::GetMousePosition()
	{
		POINT mousePOINT;
		GetCursorPos(&mousePOINT);
		ScreenToClient(hwnd, &mousePOINT);
		MousePoint->X = mousePOINT.x;
		MousePoint->Y = mousePOINT.y;
		return Point(mousePOINT.x, mousePOINT.y);
	}
	void DX9Device::CleanUp()
	{
		if (dxSprite)
		{
			SAFE_RELEASE(dxSprite);
		}
		if (dxDevice)
		{
			SAFE_RELEASE(dxDevice);
		}
	}
	DX9Device::~DX9Device()
	{

	}
}
