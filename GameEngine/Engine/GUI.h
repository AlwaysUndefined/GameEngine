#pragma once
#include <BasicStructure.h>
#include <Observers.h>
namespace GameEngine
{
	class Label
	{
	public:
		LPCWSTR str=TEXT("δ����");
		RECT rect;
		D3DCOLOR color = 0xffffffff;
		int index = 0;
		Label();
		~Label();
	};
	class Button:public Observer<Game>
	{
	public:
		Texture2D* buttonTexture2D;
		Button(RECT rect, LPCTSTR pSrcFile);
	};
	class GUI
	{
	public:
		//�ĵ�����
		tinyxml2::XMLDocument xmlDoc;
		//�豸����
		DX9Device* dx9Device;

		LPDIRECT3DTEXTURE9 title = NULL;
		vector<Label*> labelGroup;
		vector<Texture2D*> texture2DGroup;
		vector<Button*> buttonGroup;
		GUI(DX9Device* device);
		HRESULT AddLabel(char* str,
			long x = 0, long y = 0, long width = 32, long height = 32,
			int index = 0, D3DCOLOR color = 0xffffffff);
		HRESULT AddTexture2D(Texture2D* t2d);
		HRESULT AddTexture2D(LPDIRECT3DTEXTURE9 texture,
			D3DXVECTOR3* position,
			RECT* rect = NULL,
			D3DXVECTOR3* center = NULL,
			D3DCOLOR color = 0xffffffff);
		//���ͼ�㣬δʵ�����߼���
		Button* AddButton(D3DXVECTOR3 pos, RECT rect, LPCTSTR pSrcFile);
		~GUI();
	private:
	};
}
