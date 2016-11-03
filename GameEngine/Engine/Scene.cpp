#pragma once
#include <Scene.h>

namespace GameEngine
{
	Scene::Scene(DX9Device* device)
		{
			Scene::dx9Device = device;
			dx9Device->CreateTexture(L"./Resources/ForeGround/jxk.jpg",Size(800,600), &foreGound.texture,&foreGound.imgInfo);
			//MessageBox(NULL, ToWchar(IntToChar(foreGound.imgInfo.Width)), ToWchar(IntToChar(foreGound.imgInfo.Height)), NULL);
			//foreGound.Transform(&D3DXVECTOR2(0.1f,0.1f),NULL,0.0f);
			//构造时，会加载foreGround
		}
	HRESULT Scene::SceneInit(char* fileName,long playerX=0,long playerY=0)
	{
		player = new Player();
		if (FAILED(LoadScene(fileName)))
		{
			return E_FAIL;
		}
		if (FAILED(LoadPlayer()))
		{
			return E_FAIL;
		}
		gameObject.push_back((GameObject*)player);
		//MessageBox(NULL, ToWchar(IntToChar(playerX)), ToWchar(IntToChar(playerY)), NULL);
		SetPlayerPosition(Point(playerX, playerY));
		return S_OK;
	}
	Scene::~Scene()
	{

	}
	HRESULT Scene::LoadScene(char* fileName)
	{
		//加载地图
		xmlDoc.LoadFile(CharAdd("./Resources/Data/", fileName));
		XMLElement* rootElement = xmlDoc.RootElement();
		//获取sceneInfo
		name =ConstCharToChar(rootElement->Attribute("name"));
		sceneId =CharToInt(rootElement->Attribute("id"));
		//获取Map
		XMLElement* mapElement = rootElement->FirstChildElement("map");
		//获取地图大小
		mapSize.width =CharToInt(mapElement->Attribute("width"));
		mapSize.height = CharToInt(mapElement->Attribute("height"));
		dx9Device->CreateTexture(CharToWchar(mapElement->FirstChildElement("bottom")->GetText()), mapSize,&bottomMap.texture,&bottomMap.imgInfo);
		dx9Device->CreateTexture(CharToWchar(mapElement->FirstChildElement("top")->GetText()), mapSize,&topMap.texture,&topMap.imgInfo);
		//获取gridMap
		gridMap.CreateGridMap(mapSize);
		for (int i = 0; i < gridMap.gridDataLen; i++)
		{
			gridMap.gridData[i] = 1;
		}
		//加载NPC
		//加载怪物信息
		return S_OK;
	}
	HRESULT Scene::LoadPlayer()
	{
		xmlDoc.LoadFile("./Resources/Data/player.data");
		XMLElement* rootElement = xmlDoc.RootElement();
		if (!rootElement) return E_FAIL;
		if (xmlDoc.FirstChildElement("player"))
		{
			//获取Info
			player->name =ConstCharToChar(xmlDoc.FirstChildElement("player")->Attribute("name"));
			player->SetCenter(38,96);
			//获取Animation
			XMLElement* renderElement = rootElement->FirstChildElement("render");
			XMLElement* firstAnimationElement = renderElement->FirstChildElement("animation");
			//获取animation信息
			XMLElement* firstFrameElement = firstAnimationElement->FirstChildElement("frame");
			if (renderElement && firstAnimationElement && firstFrameElement)
			{
				LPDIRECT3DTEXTURE9 texture;
				Animation* ani1 = new Animation();
				ani1->name = firstAnimationElement->Attribute("name");
				dx9Device->CreateTexture(CharToWchar(firstFrameElement->GetText()), Size(76,96), &texture);
				ani1->AddFrame(texture);
				while (firstFrameElement = firstFrameElement->NextSiblingElement())
				{
					dx9Device->CreateTexture(CharToWchar(firstFrameElement->GetText()), Size(76, 96), &texture);
					ani1->AddFrame(texture);
				}
				ani1->setAnimationFace(4);//检查动画帧是否合法
				player->AddAnimation(ani1);
				while (firstAnimationElement = firstAnimationElement->NextSiblingElement())
				{
					if (firstFrameElement = firstAnimationElement->FirstChildElement("frame"))
					{
						Animation* ani2 = new Animation();
						dx9Device->CreateTexture(CharToWchar(firstFrameElement->GetText()), Size(76, 96), &texture);
						ani2->AddFrame(texture);
						while (firstFrameElement = firstFrameElement->NextSiblingElement())
						{
							dx9Device->CreateTexture(CharToWchar(firstFrameElement->GetText()), Size(76, 96), &texture);
							ani2->AddFrame(texture);
						}
						ani2->setAnimationFace(4);//检查动画帧是否合法
						player->AddAnimation(ani2);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				return E_FAIL;
			}
		}
		else
		{
			return E_FAIL;
		}
		return S_OK;
	}
	int Scene::SetPlayerPosition(Point p)
	{
		//修正坐标
		Point newP = gridMap.PointToGridPoint(p);
		//MessageBox(NULL, ToWchar(IntToChar(newP.X)), ToWchar(IntToChar(newP.Y)), NULL);
		if (gridMap.GetPointValue(newP) == 1)
		{
			player->SetPosition(newP.X*gridMap.unitGrid.width, newP.Y*gridMap.unitGrid.height);
			//MessageBox(NULL, ToWchar(IntToChar(p.X)), ToWchar(IntToChar(p.X)), NULL);
			//MessageBox(NULL, ToWchar(IntToChar(gridMap.gridSize.width)), ToWchar(IntToChar(gridMap.gridSize.height)), NULL);
			//MessageBox(NULL, ToWchar(IntToChar(gridMap.gridDataLen)), ToWchar(IntToChar(gridMap.gridData[7499])), NULL);
		}
		else
		{
			return 1;
		}
		return 0;
	}
	Point Scene::GetPlayerGridPoint()
	{
		return Point(player->pPosition->x,player->pPosition->y);
	}
	int Scene::Render()
	{
	}
}
