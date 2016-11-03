#pragma once
#include <BasicStructure.h>
//��ϵͳ
#include <DX9Device.h>
#include <EventManager.h>
#include <Game.h>
namespace GameEngine
{
	/*
	�����㣬����Game����
	*/
	class Engine
	{
	public:
		//�������
		Size clientSize = Size(800, 600);//�ͻ�����С
		HWND hwnd = NULL;
		HINSTANCE hInstance = NULL;

		DX9Device* dx9Device;//�豸������
		EventManager* eventManager;//�¼�������

		Game* game;

		/*
		��ȡ��ʼ������
		*/
		Engine(HWND hwnd, HINSTANCE hInstance);
		//�����豸����ʼ���豸
		int Init();
		int Start();
		void SetClientSize(Size clientSize);
		int EventLoop();
		int Render();
		int CleanUp();
		~Engine();
	private:
	};
}