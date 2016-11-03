#pragma once
#include <BasicStructure.h>
#include <Texture2D.h>
namespace GameEngine
{
	//游戏物体基类
	class GameObject
	{
	public:
		//属性
		string name = "GameObject";
		RECT* pRect = NULL;//默认原图
		D3DXVECTOR3* pCenter = new D3DXVECTOR3(0, 0, 0);//默认中心坐标（0,0,0）
		D3DXVECTOR3* pPosition = new D3DXVECTOR3(0, 0, 0);//默认绘制坐标原点
		D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255);
		//控制
		bool visible = true;
		GameObject();
		virtual void SetPosition();
		//更新
		virtual void Update();
		//排序
		virtual float GetFY();
		//渲染参数
		virtual LPDIRECT3DTEXTURE9 Render();
		virtual RECT* GetpRect();
		virtual D3DXVECTOR3* GetpCenter();
		virtual D3DXVECTOR3* GetpPosition();
		virtual D3DCOLOR GetColor();
		~GameObject();
	private:

	};
	class Button
	{
	public:
		long x = 0;
		long y = 0;
		long width = 100;
		long height = 100;
		Texture2D* buttonTexture2D= new Texture2D();
		Button();
		~Button();
	private:

	};
	//包含四个方向的基本动画
	class Animation
	{
	public:
		//描述性的属性
		string name = "ani";
		//控制属性
		bool play = true;
		bool lock = false;

		DWORD preTime = 0;
		DWORD nowTime = 0;

		int minFrame = 0;
		int maxFrame = 0;

		int currentMinFrame = 0;
		int currentMaxFrame = 0;
		int currentFrame = 0;
		DWORD deltaTime;//默认播放动画为12.5帧
		vector<LPDIRECT3DTEXTURE9> frameGroup;
		Animation(DWORD deltaTime = 80);
		HRESULT AddFrame(LPDIRECT3DTEXTURE9 frameTexture);
		void setAnimationFace(int face);
		void Update();
		LPDIRECT3DTEXTURE9 Render();
		~Animation();
	};
	enum CharacterStatus
	{
		STAND=1,
		MOVE=2
	};
	class Character :public GameObject
	{
	public:
		int face = 4;
		CharacterStatus status = CharacterStatus::STAND;
		vector<Point> path;
		int step=0;
		virtual void SetCenter(long x = 0, long y = 0);
	};
	class Player:public Character
	{
	public:
		int minAnimationId = 0;
		int maxAnimationId = 0;
		int animationId = 0;
		Size moveUnit = Size(8, 8);
		vector<Animation*> animationGroup;
		Player();
		HRESULT AddAnimation(Animation* ani);
		//返回游戏物体当前的动画
		Animation* getCurrentAnimation();
		void ChangeAnimation(int animationId);
		void SetAnimationFace(int face = 4);
		void Move(Size* unit, int face);
		void MoveInit();
		void Update();
		LPDIRECT3DTEXTURE9 Render();
		//排序
		float GetFY();
		//渲染参数
		RECT* GetpRect();
		D3DXVECTOR3* GetpCenter();
		//获取主角位置
		D3DXVECTOR3* GetpPosition();
		D3DCOLOR GetColor();
		//设置中点
		void SetCenter(long x = 0, long y = 0);
		//设置主角位置
		void SetPosition(long x = 0, long y = 0);
		~Player();

	private:

	};
}