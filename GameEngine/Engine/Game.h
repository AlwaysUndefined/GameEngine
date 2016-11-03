#pragma once
#include <BasicStructure.h>
#include <DX9Device.h>
#include <Scene.h>
#include <GUI.h>
#include <GameObject.h>
#include <Texture2D.h>
namespace GameEngine
{
	enum GameStatus
	{
		Game_Begin = 1,//标题画面
		Game_Load = 2,//场景加载
		Game_Pause=3,//暂停
		Game_Normal=4,//正常场景
		Game_Lock=5,//屏幕锁定
		Game_Fight=6,//战斗
		Game_Over=7//游戏结束
	};
	/*
	事务层，控制逻辑
	*/
	class EventManager;//前置声明
	class Game
	{
	public:
		//类本身对象
		Game* me;
		//窗体参数
		Size clientSize=Size(800,600);//客户区大小
		HWND hwnd = NULL;
		HINSTANCE hInstance = NULL;

		//属性
		bool gameOver = false;
		GameStatus status = Game_Begin;

		//设备对象
		EventManager* eventManager=NULL;
		DX9Device* dx9Device=NULL;

		Scene* scene;//场景管理类
		GUI* Gui;//GUI管理类

		//渲染贴图列表
		list<Texture2D*> RenderList;

		Game(DX9Device* dx9Device, EventManager* eventManager);
		//窗体绘制前调用初始化函数。加载资源
		int Init(Game* me);
		//窗体绘制完成后第一个调用的函数，初始化逻辑
		int Start();
		int InitGUI();
		//逻辑循环
		int Update(EventArgs e);
		int AnimationFrameUpdate(EventArgs e);
		int Render(EventArgs e);
		void CleanUp();
		~Game();
		//回调函数
		int PlayerMove(EventArgs e);
		int GoodsButtonEventHandler(EventArgs e);
	private:

	};
}
