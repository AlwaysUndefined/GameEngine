#pragma once
#include <BasicStructure.h>
//子系统
#include <DX9Device.h>
#include <EventManager.h>
#include <Game.h>
namespace GameEngine
{
	/*
	驱动层，控制Game对象
	*/
	class Engine
	{
	public:
		//窗体参数
		Size clientSize = Size(800, 600);//客户区大小
		HWND hwnd = NULL;
		HINSTANCE hInstance = NULL;

		DX9Device* dx9Device;//设备管理类
		EventManager* eventManager;//事件管理器

		Game* game;

		/*
		获取初始化参数
		*/
		Engine(HWND hwnd, HINSTANCE hInstance);
		//创建设备，初始化设备
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