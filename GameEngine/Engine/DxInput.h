#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	class Mouse
	{
	public:
		HWND hwnd=NULL;
		LPDIRECT3DTEXTURE9 mouseIcon = NULL;//���ָ��
		//�����Ļ���꣨�������Ļԭ�㣩
		POINT mousePos = {0,0};
		//���ͻ������꣨����ڿͻ���ԭ�㣩
		POINT mouseClinetPos = {0,0};
		//�ͻ���
		RECT clientRect;
		//�ͻ���ԭ���Լ��������Ļλ��
		POINT p0 = { 0,0 };
		POINT p1 = { 0,0 };
		//����ڴ���ľ���λ��
		D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
		Mouse(HWND hwnd);
		void MouseInit(LPDIRECT3DTEXTURE9 mouseIcon);
		void MousePosUpdate();
	};
	/*
	��DX9Device��ȡ�����豸
	*/
	class DXInput
	{
	public:
		//������Ϣ
		HWND hwnd;
		//���뻺����
		char keyStateBuffer[256];//������256��״̬
		DIMOUSESTATE mouseState;
		//�����豸
		LPDIRECTINPUT8 dxInput = NULL;
		LPDIRECTINPUTDEVICE8 dxKeyBoardDevice = NULL;
		LPDIRECTINPUTDEVICE8 dxMouseDevice = NULL;
		Point* mousePoint;
		DXInput(
			HWND hwnd,
			LPDIRECTINPUT8 dxInput,
			LPDIRECTINPUTDEVICE8 dxKeyBoardDevice,
			LPDIRECTINPUTDEVICE8 dxMouseDevice);
		//��ȡ������ѯ
		void GetInputLoop();
		//�����ж�
		bool IsKeyDown(int iKey);
		bool IsMouseButtonDown(int button);
		Point GetMousePosition();
	private:

	};
}