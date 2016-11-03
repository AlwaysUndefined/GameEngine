#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	//委托
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
	//观察者
	template<class T>
	class Observer
	{
	public:
		//点击事件的观察者
		RECT rect = { 0,0,0,0 };
		int index = 0;//表示地图bottom层
		Delegate<T>* delegate;
		Observer();
	};
	//继承Observer
	template<class T>
	class Timer
	{
	public:
		bool Enable = false;
		DWORD preTime = 0;
		DWORD nowTime = 0;
		DWORD deltaTime = 40;//默认25FPS
		Delegate<T>* delegate;
		Timer();
		Timer(DWORD deltaTime);
		~Timer();
	private:
	};
}


