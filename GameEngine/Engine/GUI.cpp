#pragma once
#include <GUI.h>
namespace GameEngine
{
	Label::Label()
	{
	}
	Label::~Label()
	{
	}

	Button::Button(RECT rect, LPCTSTR pSrcFile)
	{
		Button::rect = rect;
		buttonTexture2D = new Texture2D();
	}

	GUI::GUI(DX9Device* device)
		{
			dx9Device = device;
		}
	HRESULT GUI::AddLabel(char* str,
		long x = 0, long y = 0, long width = 32, long height = 32,
		int index = 0,D3DCOLOR color = 0xffffffff)
	{
		Label* label=new Label();
		SetRect(&label->rect, x, y, height, width);
		label->str = CharToWchar(str);
		label->index = index;
		label->color = color;
		labelGroup.push_back(label);
		return S_OK;
	}
	HRESULT GUI::AddTexture2D(Texture2D* t2d)
	{
		texture2DGroup.push_back(t2d);
		return S_OK;
	}
	HRESULT GUI::AddTexture2D(LPDIRECT3DTEXTURE9 texture,
												D3DXVECTOR3* position,
												RECT* rect=NULL,
												D3DXVECTOR3* center = NULL,
												D3DCOLOR color = 0xffffffff)
	{
		Texture2D* texture2D = new Texture2D();
		texture2D->texture = texture;
		texture2D->pRect = rect;
		texture2D->pCenter = center;
		texture2D->pPosition = position;
		texture2D->color = color;
		texture2DGroup.push_back(texture2D);
		return S_OK;
	}
	//Ìí¼ÓÍ¼²ã£¬Î´ÊµÀý»¯Âß¼­²ã
	Button* GUI::AddButton(D3DXVECTOR3 pos,RECT rect, LPCTSTR pSrcFile)
	{
		Button* button = new Button(rect, pSrcFile);
		dx9Device->CreateTexture(pSrcFile, Size(rect.right - rect.left, rect.bottom - rect.top), &button->buttonTexture2D->texture);
		button->buttonTexture2D->pPosition = &pos;
		buttonGroup.push_back(button);
		return S_OK;
	}
	GUI::~GUI()
	{

	}
}
