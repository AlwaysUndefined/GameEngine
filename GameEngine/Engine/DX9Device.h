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
		//�����豸--���̣����
		LPDIRECTINPUT8 dxInput = NULL;
		LPDIRECTINPUTDEVICE8 dxKeyBoardDevice = NULL;
		LPDIRECTINPUTDEVICE8 dxMouseDevice = NULL;

		//���뻺����
		char keyStateBuffer[256];//������256��״̬
		DIMOUSESTATE mouseState;
		//
		Point* MousePoint;

		DX9Device();
		DX9Device(HWND hwnd, HINSTANCE hInstance, Size clientSize);
		//���DX����������豸�����Ƿ�ɹ�����
		HRESULT DX9Init();
		HRESULT CreateTexture(LPCTSTR pSrcFile, Size s, LPDIRECT3DTEXTURE9* lppTexture, D3DXIMAGE_INFO* imgInfo);
		HRESULT CreateTexture(LPCTSTR pSrcFile, Size s, LPDIRECT3DTEXTURE9* lppTexture);
		HRESULT CreateDevice();
		HRESULT CreateSprite();
		HRESULT CreateDXFont();
		HRESULT CreateDXInput();
		HRESULT CreateKeyBoardDevice();
		HRESULT CreateMouseDevice();
//*************************������****************************
		//��ȡ������ѯ
		void InputLoop();
		//�����ж�
		bool IsKeyDown(int iKey);
		bool IsMouseButtonDown(int button);
		Point GetMousePosition();
		void CleanUp();
		~DX9Device();
	private:
	};
}
