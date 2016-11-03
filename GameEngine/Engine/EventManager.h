#pragma once
#include <BasicStructure.h>
#include <Observers.h>
#include <DxInput.h>
namespace GameEngine
{
	
	class Game;//前置声明
	//事件类
	class EventManager
	{
	public:
		//输入设备
		DX9Device* dx9Device = NULL;
		//调度事件管理器速率
		Timer<EventManager> timer;
		//定时器事件观察者组
		list<Timer<Game>*> timer_Game_Group;
		list<Timer<Game>*>::iterator iter_timer;
		//鼠标点击事件观察者组
		list<Observer<Game>*> mouseClick_Scene_Group;
		list<Observer<Game>*>::iterator iter_mouseClick;
		EventManager(DX9Device* dx9Device);
		int AddTimer(Timer<Game>* timer);
		int AddObserver(Observer<Game>* ob, EventType et);
		void EventLoop();
	};
}