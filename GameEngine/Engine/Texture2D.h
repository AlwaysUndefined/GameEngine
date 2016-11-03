#pragma once
#include <BasicStructure.h>
namespace GameEngine
{
	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();
		string name = "Sprite";
		LPDIRECT3DTEXTURE9 texture = NULL;
		D3DXIMAGE_INFO imgInfo;
		RECT* pRect = NULL;
		D3DXVECTOR3* pCenter = new D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3* pPosition = new D3DXVECTOR3(0, 0, 0);
		D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255);
		D3DXMATRIX matx2D;
		void Transform(D3DXVECTOR2* scaling, D3DXVECTOR2* rotationCenter, float rotation, D3DXVECTOR2* translation = new D3DXVECTOR2(0, 0));
	private:

	};
}