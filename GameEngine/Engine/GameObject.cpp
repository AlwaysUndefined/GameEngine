#pragma once
#include <GameObject.h>
namespace GameEngine
{
	//游戏物体基类
	GameObject::GameObject()
		{

		}
	void GameObject::SetPosition()
	{

	}
	//更新
	void GameObject::Update()
	{

	}
	//排序
	float GameObject::GetFY()
	{
		return pPosition->y;
	}
	//渲染参数
	LPDIRECT3DTEXTURE9 GameObject::Render()
	{
		return NULL;
	}
	RECT* GameObject::GetpRect()
	{
		return pRect;
	}
	D3DXVECTOR3* GameObject::GetpCenter()
	{
		return pCenter;
	}		
	D3DXVECTOR3* GameObject::GetpPosition()
	{
		return pPosition;
	}
	D3DCOLOR GameObject::GetColor()
	{
		return color;
	}
	GameObject::~GameObject()
	{
	}
	Button::Button()
	{
	}
	Button::~Button()
	{

	}

	//包含四个方向的基本动画
	Animation::Animation(DWORD deltaTime =80)
		{
			Animation::deltaTime = deltaTime;
		}
	HRESULT Animation::AddFrame(LPDIRECT3DTEXTURE9 frameTexture)
	{
		if (frameTexture)
		{
			frameGroup.push_back(frameTexture);
			maxFrame++;
			return S_OK;
		}
		return E_FAIL;
	}
	void Animation::setAnimationFace(int face)
	{
		if (face < 1 || face>4) face = 4;
		if (frameGroup.size() % 4 == 0)
		{
			currentMinFrame = (4- face)*(frameGroup.size() / 4);
			currentMaxFrame = currentMinFrame+frameGroup.size() / 4 - 1;
		}
		else
		{
			lock = true;
		}
			
	}
	void Animation::Update()
	{
		if (play && !lock)
		{
			nowTime = GetTickCount();
			if ((nowTime - preTime) >deltaTime)
			{
				if (currentFrame<currentMaxFrame && currentFrame>= currentMinFrame)
				{
					++currentFrame;
				}
				else
				{
					currentFrame = currentMinFrame;
				}
				preTime = nowTime;
			}
		}
	}
	LPDIRECT3DTEXTURE9 Animation::Render()
	{
		if (lock) return NULL;
		return frameGroup[currentFrame];
	}
	Animation::~Animation()
	{

	}

	//角色
	void Character::SetCenter(long x=0,long y=0)
		{
			pCenter->x=x;
			pCenter->y = y;
		}

	//主角
	Player::Player()
	{
	}
	HRESULT Player::AddAnimation(Animation* ani)
	{
		animationGroup.push_back(ani);
		++maxAnimationId;
		return S_OK;
	}
	//返回游戏物体当前的动画
	Animation* Player::getCurrentAnimation()
	{
		return animationGroup[animationId];
	}
	void Player::ChangeAnimation(int animationId)
	{
		Player::animationId = 0;
		if(animationId>=0 && animationId<maxAnimationId)
		Player::animationId = animationId;
	}
	void Player::SetAnimationFace(int face=4)
	{
		getCurrentAnimation()->setAnimationFace(face);
	}
	void Player::Move(Size* unit,int face)
	{
		Player::face = face;
		moveUnit.width = unit->width;
		moveUnit.height = unit->height;
		status = MOVE;
		SetAnimationFace(face);
		ChangeAnimation(1);
	}
	void Player::MoveInit()
	{
		path.clear();
		step = 0;
	}
	void Player::Update()
	{
		//更新行走
		if (path.size() > 0 && step < path.size() && status==MOVE)
		{
			SetPosition(path[step].X*moveUnit.width,path[step].Y*moveUnit.height);
			step++;
		}
		else
		{
			status = STAND;
			SetAnimationFace(face);
			ChangeAnimation(0);
			path.clear();
			step = 0;
		}
		//更新动画
		getCurrentAnimation()->Update();
	}
	LPDIRECT3DTEXTURE9 Player::Render()
	{
		return getCurrentAnimation()->Render();
	}
	//排序
	float Player::GetFY()
	{
		return pPosition->y;
	}
	//渲染参数
	RECT* Player::GetpRect()
	{
		return pRect;
	}
	D3DXVECTOR3* Player::GetpCenter()
	{
		return pCenter;
	}
	//获取主角位置
	D3DXVECTOR3* Player::GetpPosition()
	{
		return pPosition;
	}
	D3DCOLOR Player::GetColor()
	{
		return color;
	}
	//设置中点
	void Player::SetCenter(long x = 0, long y = 0)
	{
		pCenter->x = x;
		pCenter->y = y;
	}
	//设置主角位置
	void Player::SetPosition(long x=0,long y=0)
	{
		pPosition->x = x;
		pPosition->y = y;
	}
	Player::~Player()
	{

	}

}