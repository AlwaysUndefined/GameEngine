#pragma once
#include <BasicStructure.h>
#include <Texture2D.h>
namespace GameEngine
{
	//��Ϸ�������
	class GameObject
	{
	public:
		//����
		string name = "GameObject";
		RECT* pRect = NULL;//Ĭ��ԭͼ
		D3DXVECTOR3* pCenter = new D3DXVECTOR3(0, 0, 0);//Ĭ���������꣨0,0,0��
		D3DXVECTOR3* pPosition = new D3DXVECTOR3(0, 0, 0);//Ĭ�ϻ�������ԭ��
		D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255);
		//����
		bool visible = true;
		GameObject();
		virtual void SetPosition();
		//����
		virtual void Update();
		//����
		virtual float GetFY();
		//��Ⱦ����
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
	//�����ĸ�����Ļ�������
	class Animation
	{
	public:
		//�����Ե�����
		string name = "ani";
		//��������
		bool play = true;
		bool lock = false;

		DWORD preTime = 0;
		DWORD nowTime = 0;

		int minFrame = 0;
		int maxFrame = 0;

		int currentMinFrame = 0;
		int currentMaxFrame = 0;
		int currentFrame = 0;
		DWORD deltaTime;//Ĭ�ϲ��Ŷ���Ϊ12.5֡
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
		//������Ϸ���嵱ǰ�Ķ���
		Animation* getCurrentAnimation();
		void ChangeAnimation(int animationId);
		void SetAnimationFace(int face = 4);
		void Move(Size* unit, int face);
		void MoveInit();
		void Update();
		LPDIRECT3DTEXTURE9 Render();
		//����
		float GetFY();
		//��Ⱦ����
		RECT* GetpRect();
		D3DXVECTOR3* GetpCenter();
		//��ȡ����λ��
		D3DXVECTOR3* GetpPosition();
		D3DCOLOR GetColor();
		//�����е�
		void SetCenter(long x = 0, long y = 0);
		//��������λ��
		void SetPosition(long x = 0, long y = 0);
		~Player();

	private:

	};
}