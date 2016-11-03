#pragma once
#include <BasicStructure.h>
#include <Observers.h>
#include <DxInput.h>
namespace GameEngine
{
	
	class Game;//ǰ������
	//�¼���
	class EventManager
	{
	public:
		//�����豸
		DXInput* dxInput;
		//�����¼�����������
		Timer<EventManager> timer;
		//��ʱ���¼��۲�����
		list<Timer<Game>*> timer_Game_Group;
		list<Timer<Game>*>::iterator iter_timer;
		//������¼��۲�����
		list<Observer<Game>*> mouseClick_Scene_Group;
		list<Observer<Game>*>::iterator iter_mouseClick;
		EventManager(DXInput* dxInput);
		int AddTimer(Timer<Game>* timer);
		int AddObserver(Observer<Game>* ob, EventType et);
		void EventLoop();
	};
}