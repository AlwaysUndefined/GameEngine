#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	//ί��
	template<class T>
	class Delegate
	{
	public:
		typedef int (T::*EventInvoke)(EventArgs);
		Delegate(T * object);
		void Add(EventInvoke fuc);
		void Remove(EventInvoke fuc);
		void operator()(EventArgs e);
		~Delegate();
	private:
		T * object;
		list<EventInvoke> invokeList;
	};
	//�۲���
	template<class T>
	class Observer
	{
	public:
		//����¼��Ĺ۲���
		RECT rect = { 0,0,0,0 };
		int index = 0;//��ʾ��ͼbottom��
		Delegate<T>* delegate;
		Observer();
	};
	//�̳�Observer
	template<class T>
	class Timer
	{
	public:
		bool Enable = false;
		DWORD preTime = 0;
		DWORD nowTime = 0;
		DWORD deltaTime = 40;//Ĭ��25FPS
		Delegate<T>* delegate;
		Timer();
		Timer(DWORD deltaTime);
		~Timer();
	private:
	};
}


