#pragma once
#include <BasicStructure.h>
#include <Game.h>
#include <EventManager.h>
namespace GameEngine
{
	//事件类
	EventManager::EventManager(DX9Device* dx9Device)
	{
		timer = Timer<EventManager>(10);
		EventManager::dx9Device = dx9Device;
	}
	int EventManager::AddTimer(Timer<Game>* timer)
	{
		timer_Game_Group.push_back(timer);
		return 0;
	}
	int EventManager::AddObserver(Observer<Game>* ob, EventType et)
	{
		switch (et)
		{
		case GameEngine::MouseClickEvent:
		{
			mouseClick_Scene_Group.push_back(ob);
		}
		break;
		case GameEngine::MouseDoubleClick:
			break;
		case GameEngine::MouseMoveEvent:
			break;
		default:
			break;
		}
		return 0;
	}
	void EventManager::EventLoop()
	{
		timer.nowTime = GetTickCount();
		if (timer.nowTime - timer.preTime <= timer.deltaTime)
			return;
		//处理定时器组
		iter_timer = timer_Game_Group.begin();
		while (iter_timer != timer_Game_Group.end())
		{
			(*iter_timer)->nowTime = GetTickCount();
			if ((*iter_timer)->nowTime - (*iter_timer)->preTime > (*iter_timer)->deltaTime)
			{
				(*(*iter_timer)->delegate)(EventArgs());
				(*iter_timer)->preTime = (*iter_timer)->nowTime;
			}
			iter_timer++;
		}
		//处理键盘鼠标
		dxInput->GetInputLoop();//更新输入
		for (int i = 0;i < 256;i++)
		{
			if (dxInput->IsKeyDown(i))
			{
				MessageBox(IntToChar(i));
			}
		}
		for (int id = 0;id < 3;id++)
		{
			if (dxInput->IsMouseButtonDown(id))
			{
				Point* p = dxInput->mousePoint;
				iter_mouseClick = mouseClick_Scene_Group.begin();
				while (iter_mouseClick != mouseClick_Scene_Group.end())
				{
					if (IsPointInRECT(*p, (*iter_mouseClick)->rect))
					{
						EventArgs e = EventArgs(p->X, p->Y, id);
						(*(*iter_mouseClick)->delegate)(e);
					}
					iter_mouseClick++;
				}
			}
		}
		timer.preTime = timer.nowTime;
	}
}