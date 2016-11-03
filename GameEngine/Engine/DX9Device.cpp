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
			//��ʼ�����뻺����
			ZeroMemory(keyStateBuffer, sizeof(char) * 256);
			ZeroMemory(&mouseState, sizeof(mouseState));
		}
	//���DX����������豸�����Ƿ�ɹ�����
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
			dxDevice,//�豸
			pSrcFile,//�ļ�·��
			s.width,//ͼƬ��
			s.height,//ͼƬ��
			D3DX_DEFAULT,//ͼƬ��ͼ�㣬һ����D3DX_DEFAULT����Ҳ��1��
			0, //һ���õ���0��Ҳ����ʹ�� D3DUSAGE_DYNAMIC���������Զ�̬�ı������е����ݡ�
			D3DFMT_UNKNOWN,//������ͼ���ļ�ʱ�����������
			D3DPOOL_MANAGED, //��ι�����Щ����һ��ʹ��D3DPOOL_MANAGED
			D3DX_FILTER_TRIANGLE,//ͼ�����صĹ��˷�ʽ
			D3DX_FILTER_TRIANGLE,//MIP�����ع��˷�ʽ
			D3DCOLOR_RGBA(255, 255, 255, 255), //͸��ɫ���趨�����ɫ������ʾʱ����ͼ���е������ɫ������
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
			dxDevice,//�豸
			pSrcFile,//�ļ�·��
			s.width,//ͼƬ��
			s.height,//ͼƬ��
			D3DX_DEFAULT,//ͼƬ��ͼ�㣬һ����D3DX_DEFAULT����Ҳ��1��
			0, //һ���õ���0��Ҳ����ʹ�� D3DUSAGE_DYNAMIC���������Զ�̬�ı������е����ݡ�
			D3DFMT_UNKNOWN,//������ͼ���ļ�ʱ�����������
			D3DPOOL_MANAGED, //��ι�����Щ����һ��ʹ��D3DPOOL_MANAGED
			D3DX_FILTER_TRIANGLE,//ͼ�����صĹ��˷�ʽ
			D3DX_FILTER_TRIANGLE,//MIP�����ع��˷�ʽ
			D3DCOLOR_RGBA(255, 255, 255, 255), //͸��ɫ���趨�����ɫ������ʾʱ����ͼ���е������ɫ������
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
		//����D3D�ӿ�
		LPDIRECT3D9 pD3D = NULL;
		if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			return E_FAIL;
		if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		{
			return E_FAIL;
		}
		//�����Կ��Ƿ�֧��Ӳ����������
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//Ӳ����������
		}
		else
		{
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//�����������
		}
		//�������
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
		//�����豸
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
		if(FAILED(D3DXCreateFont(dxDevice,0,0,0,0,0,0,0,0,0,L"΢���ź�",&dxFont)))
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
		//�����豸���ݸ�ʽ��Э����ʽ
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
		//�����豸���ݸ�ʽ��Э����ʽ
		dxMouseDevice->SetDataFormat(&c_dfDIMouse);
		dxMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		dxMouseDevice->Acquire();
		dxMouseDevice->Poll();
		return S_OK;
	}
//*************************������****************************
	//��ȡ������ѯ
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
	//�����ж�
	bool DX9Device::IsKeyDown(int iKey)
	{
		if (keyStateBuffer[iKey] & 0x80)
		{
			return true;
		}
		return false;
	}
	//�ж������Ƿ񱻰��£�ͬʱ��ȡ���λ��
	bool DX9Device::IsMouseButtonDown(int button)
	{
		GetMousePosition();
		return (mouseState.rgbButtons[button] & 0x80) != 0;
	}
	//��ȡ������꣬����MousePoint������Point
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
