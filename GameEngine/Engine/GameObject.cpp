#pragma once
#include <GameObject.h>
namespace GameEngine
{
	//��Ϸ�������
	GameObject::GameObject()
		{

		}
	void GameObject::SetPosition()
	{

	}
	//����
	void GameObject::Update()
	{

	}
	//����
	float GameObject::GetFY()
	{
		return pPosition->y;
	}
	//��Ⱦ����
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

	//�����ĸ�����Ļ�������
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

	//��ɫ
	void Character::SetCenter(long x=0,long y=0)
		{
			pCenter->x=x;
			pCenter->y = y;
		}

	//����
	Player::Player()
	{
	}
	HRESULT Player::AddAnimation(Animation* ani)
	{
		animationGroup.push_back(ani);
		++maxAnimationId;
		return S_OK;
	}
	//������Ϸ���嵱ǰ�Ķ���
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
		//��������
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
		//���¶���
		getCurrentAnimation()->Update();
	}
	LPDIRECT3DTEXTURE9 Player::Render()
	{
		return getCurrentAnimation()->Render();
	}
	//����
	float Player::GetFY()
	{
		return pPosition->y;
	}
	//��Ⱦ����
	RECT* Player::GetpRect()
	{
		return pRect;
	}
	D3DXVECTOR3* Player::GetpCenter()
	{
		return pCenter;
	}
	//��ȡ����λ��
	D3DXVECTOR3* Player::GetpPosition()
	{
		return pPosition;
	}
	D3DCOLOR Player::GetColor()
	{
		return color;
	}
	//�����е�
	void Player::SetCenter(long x = 0, long y = 0)
	{
		pCenter->x = x;
		pCenter->y = y;
	}
	//��������λ��
	void Player::SetPosition(long x=0,long y=0)
	{
		pPosition->x = x;
		pPosition->y = y;
	}
	Player::~Player()
	{

	}

}