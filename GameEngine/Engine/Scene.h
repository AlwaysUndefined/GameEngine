#pragma once
#include <BasicStructure.h>
#include <GameObject.h>
#include <DX9Device.h>

namespace GameEngine
{
	/*
		Scene场景为引擎基本组件之一，Scene::Render()引擎的主要渲染部分，主要渲染场景（地图+游戏物体）
		ID3DXSprite::Draw()方法中，Position是Center相对绘图区左上角的坐标，Center是相对图片左上角的坐标
	*/
	enum SceneStatus
	{
		Load = 1,
		Normal = 2,
		unLoad=3
	};
	class Scene
	{
	public:
		//文档对象
		tinyxml2::XMLDocument xmlDoc;
		//设备对象
		DX9Device* dx9Device;
		//场景属性
		char* name = "江南野外";
		int sceneId = 1;
		SceneStatus status = Load;
		Size mapSize;
		Texture2D foreGound=Texture2D();
		Texture2D bottomMap= Texture2D();
		Texture2D topMap = Texture2D();
		//网格
		GridMap gridMap = GridMap();
		//主角
		Player* player;
		//游戏物体
		vector<GameObject*> gameObject;
		vector<GameObject*>::iterator goiterator;
		Scene(DX9Device* device);
		HRESULT SceneInit(char* fileName, long playerX = 0, long playerY = 0);
		~Scene();
		HRESULT LoadScene(char* fileName);
		HRESULT LoadPlayer();
		int SetPlayerPosition(Point p);
		Point GetPlayerGridPoint();
		int Render();
	private:
		/*void bubSort(vector<GameObject*>* base)
		{
			int i, j;
			bool f;
			for (i = 0;i < (int)(base->size());i++)
			{
				f = false;
				for (j = 0; j < ((int)(base->size()) - i - 1); j++)
				{
					if ((*base)[j + 1]->pPos.y < (*base)[j]->pPos.y)
					{
						swap((*base)[j + 1], (*base)[j]);
						f = true;
					}
					if (!f)
					{
						break;
					}
				}
			}
		}*/
	};
}
