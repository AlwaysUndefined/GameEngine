#pragma once
#include <Engine.h>
namespace GameEngine
{
	Engine::Engine(HWND hwnd,HINSTANCE hInstance)
		{
			Engine::hwnd = hwnd;
			Engine::hInstance = hInstance;
		}
	//�����豸����ʼ���豸
	int Engine::Init()
	{
		//��ʼ���豸
		dx9Device = new DX9Device(hwnd,hInstance,clientSize);
		dx9Device->DX9Init();
			
		eventManager = new EventManager();
			
		game = new Game(hwnd,hInstance,dx9Device,eventManager);
		game->Init(game);
		game->InitGUI();
		////��Ⱦ��ʱ��
		//renderTimer = new Timer<Game>(20);
		//renderTimer->delegate = new Delegate<Game>(game);
		//renderTimer->delegate->Add(&(Game::Render));
		//eventManager->AddTimer(renderTimer);
		////������ʱ��
		//animationFrameTimer = new Timer<Game>(60);
		//animationFrameTimer->delegate = new Delegate<Game>(game);
		//animationFrameTimer->delegate->Add(&(Game::AnimationFrameUpdate));
		//eventManager->AddTimer(animationFrameTimer);
		////�����bottom���¼�
		//defaultOb = new Observer<Game>();
		//SetRect(&defaultOb->rect, 0, 0, 800, 600);
		//defaultOb->delegate = new Delegate<Game>(game);
		//defaultOb->delegate->Add(&(Game::PlayerMove));
		//eventManager->AddObserver(defaultOb, MouseClickEvent);
		return 0;
	}
	int Engine::Start()
	{
		game->Start();
		return 0;
	}
	void Engine::SetClientSize(Size clientSize=Size(800,600))
	{
		Engine::clientSize = clientSize;
		RECT windowRect;
		RECT clientRect;
		GetWindowRect(hwnd, &windowRect);   //��ó��򴰿�λ����Ļ����
		GetClientRect(hwnd, &clientRect);      //��ÿͻ�������
												//�ǿͻ�����,��
		int nWidth = windowRect.right - windowRect.left - (clientRect.right - clientRect.left);
		int nHeiht = windowRect.bottom - windowRect.top - (clientRect.bottom - clientRect.top);
		nWidth += Engine::clientSize.width;
		nHeiht += Engine::clientSize.height;
		windowRect.right = nWidth;
		windowRect.bottom = nHeiht;
		int showToScreenx = GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2;    //���д���
		int showToScreeny = GetSystemMetrics(SM_CYSCREEN) / 2 - nHeiht / 2;
		MoveWindow(hwnd, showToScreenx, showToScreeny, windowRect.right, windowRect.bottom, false);
	}
	int Engine::EventLoop()
	{
		eventManager->EventLoop();
		return 1;
	}
	int Engine::Render()
	{
		return 1;
	}
	int Engine::CleanUp()
	{
		return 1;
	}
	Engine::~Engine()
	{

	}
}