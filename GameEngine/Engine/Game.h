#pragma once
#include <BasicStructure.h>
#include <DX9Device.h>
#include <DXInput.h>
#include <Scene.h>
#include <GUI.h>
#include <GameObject.h>
namespace GameEngine
{
	enum GameStatus
	{
		Game_Begin = 1,//���⻭��
		Game_Load = 2,//��������
		Game_Pause=3,//��ͣ
		Game_Normal=4,//��������
		Game_Lock=5,//��Ļ����
		Game_Fight=6,//ս��
		Game_Over=7//��Ϸ����
	};
	/*
	����㣬�����߼�
	*/
	class EventManager;//ǰ������
	class Game
	{
	public:
		//�౾�����
		Game* me;
		//�������
		Size clientSize=Size(800,600);//�ͻ�����С
		HWND hwnd = NULL;
		HINSTANCE hInstance = NULL;

		//����
		bool gameOver = false;
		GameStatus status = Game_Begin;

		//�豸����
		EventManager* eventManager;
		DX9Device* dx9Device;//���������
		LPDIRECT3DDEVICE9 dxDevice = NULL;//dx����
		DXInput* dxInput;
		LPD3DXSPRITE dxSprite = NULL;
		ID3DXFont* dxFont = NULL;

		Scene* scene;//����������
		GUI* Gui;//GUI������

		Game(HWND hwnd, HINSTANCE hInstance, DX9Device* dx9Device, DXInput* dxInput, EventManager* eventManager);
		//�������ǰ���ó�ʼ��������������Դ
		int Init(Game* mySelf);
		//���������ɺ��һ�����õĺ�������ʼ���߼�
		int Start();
		int InitGUI();
		//�߼�ѭ��
		int Update(EventArgs e);
		int AnimationFrameUpdate(EventArgs e);
		int Render(EventArgs e);
		void CleanUp();
		~Game();
		//�ص�����
		int PlayerMove(EventArgs e);
		int GoodsButtonEventHandler(EventArgs e);
	private:

	};
}
