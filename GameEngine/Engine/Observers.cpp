#include <Observers.h>
namespace GameEngine
{
	//ί��
	template<class T>
	Delegate<T>::Delegate(T * object)
	{
		Delegate::object = object;
	}
	template<class T>
	void Delegate<T>::Add(Delegate<T>::EventInvoke fuc)
	{
		Delegate<T>::invokeList.push_back(fuc);
	}
	template<class T>
	void Delegate<T>::Remove(Delegate<T>::EventInvoke fuc)
	{
		Delegate<T>::invokeList.remove(fuc);
	}
	template<class T>
	void Delegate<T>::operator()(EventArgs e)
	{
		list<Delegate<T>::EventInvoke>::iterator iter;
		iter = Delegate<T>::invokeList.begin();
		while (iter != invokeList.end())
		{
			(Delegate<T>::object->*(*iter))(e);
			iter++;
		}
	}
	template<class T>
	Delegate<T>::~Delegate()
	{

	}
	//�۲���
	template<class T>
	Observer<T>::Observer()
	{
	}
	//��ʱ��
	template<class T>
	Timer<T>::Timer()
	{
		Timer<T>::deltaTime = 40;
	}
	template<class T>
	Timer<T>::Timer(DWORD deltaTime=40)
	{
		Timer<T>::deltaTime = deltaTime;
	}
}

