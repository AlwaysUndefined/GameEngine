#include <Game.h>
#include <EventManager.h>
namespace GameEngine
{
	Game::Game(DX9Device* dx9Device, EventManager* eventManager)
	{
		Game::eventManager = eventManager;
		Game::dx9Device = dx9Device;
	}
	//�������ǰ���ó�ʼ��������������Դ
	int Game::Init(Game* me)
	{
		Game::me = me;
		//GUI����
		Gui = new GUI(dx9Device);
		//����
		scene = new Scene(dx9Device);
		return 0;
	}
	//���������ɺ��һ�����õĺ�������ʼ���߼�
	int Game::Start()
	{
		if (FAILED(scene->SceneInit("scene_jnyw.data", 400, 100)))
		{
			return 1;
		}
		status = Game_Normal;
		scene->player->ChangeAnimation(1);
		//ShowCursor(false);
		//GUIInit();
		return 0;
	}
	int Game::InitGUI()
	{
		Texture2D* main = new Texture2D();
		dx9Device->CreateTexture(L"./Resources/UI/main.png", Size(800, 600), &main->texture);
		return 1;
	}
	//�߼�ѭ��
	int Game::Update(EventArgs e)
	{
	}
	int Game::AnimationFrameUpdate(EventArgs e)
	{
		//������Ϸ���嶯��
		int len = scene->gameObject.size();
		for (int i = 0;i < len;i++)
		{
			scene->gameObject[i]->Update();
		}
		return 0;
	}
	int Game::Render(EventArgs e)
	{
		dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
		dxDevice->BeginScene();
		dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
		switch (status)
		{
		case GameEngine::Game_Begin:
		{
			dxSprite->SetTransform(&scene->foreGound.matx2D);
			dxSprite->Draw(scene->foreGound.texture, scene->foreGound.pRect, scene->foreGound.pCenter, scene->foreGound.pPosition, scene->foreGound.color);
			//dx9Device->dxSprite->Draw(Input->mouse->mouseIcon, NULL, NULL, Input->getMousePosition(), 0xffffffff);
		}
		break;
		case GameEngine::Game_Load:
			break;
		case GameEngine::Game_Pause:
			break;
		case GameEngine::Game_Normal:
		{
			//�ײ�
			dxSprite->SetTransform(&scene->bottomMap.matx2D);
			dxSprite->Draw(scene->bottomMap.texture, scene->bottomMap.pRect, scene->bottomMap.pCenter, scene->bottomMap.pPosition, scene->bottomMap.color);
			//GameObject
			int len = scene->gameObject.size();
			for (int i = 0;i < len;i++)
			{
				dxSprite->Draw(scene->gameObject[i]->Render(),
					scene->gameObject[i]->GetpRect(),
					scene->gameObject[i]->GetpCenter(),
					scene->gameObject[i]->GetpPosition(),
					scene->gameObject[i]->GetColor());
			}
			//�ڵ���
			dxSprite->SetTransform(&scene->topMap.matx2D);
			dxSprite->Draw(scene->topMap.texture, scene->topMap.pRect, scene->topMap.pCenter, scene->topMap.pPosition, scene->topMap.color);
			//GUI��
			len = Gui->labelGroup.size();
			for (int i = 0; i < len; i++)
			{
				dxFont->DrawTextW(dxSprite, Gui->labelGroup[i]->str, -1, &Gui->labelGroup[i]->rect, DT_CENTER, Gui->labelGroup[i]->color);
			}
			//dxFont->DrawTextW(dxSprite,CharToWchar(ByteToChar(dxInput->mouseState.rgbButtons)), -1, &Gui->labelGroup[0]->rect, DT_CENTER, Gui->labelGroup[0]->color);
			len = Gui->texture2DGroup.size();
			for (int i = 0; i < len; i++)
			{
				dxSprite->Draw(Gui->texture2DGroup[i]->texture,
					Gui->texture2DGroup[i]->pRect,
					Gui->texture2DGroup[i]->pCenter,
					Gui->texture2DGroup[i]->pPosition,
					Gui->texture2DGroup[i]->color
					);
			}
			len = Gui->buttonGroup.size();
			for (int i = 0; i < len; i++)
			{
				dxSprite->Draw(Gui->buttonGroup[i]->buttonTexture2D->texture,
					Gui->buttonGroup[i]->buttonTexture2D->pRect,
					Gui->buttonGroup[i]->buttonTexture2D->pCenter,
					Gui->buttonGroup[i]->buttonTexture2D->pPosition,
					Gui->buttonGroup[i]->buttonTexture2D->color);
			}
		}
		break;
		case GameEngine::Game_Lock:
			break;
		case GameEngine::Game_Fight:
			break;
		case GameEngine::Game_Over:
			break;
		default:
			break;
		}
		dx9Device->dxSprite->End();
		dx9Device->dxDevice->EndScene();
		dx9Device->dxDevice->Present(NULL, NULL, NULL, NULL);
		return 0;
	}
	void Game::CleanUp()
	{
		dx9Device->CleanUp();
	}
	Game::~Game()
	{

	}
	//�ص�����
	int Game::PlayerMove(EventArgs e)
	{
		Point target = Point(e.X, e.Y);
		scene->player->MoveInit();
		int a = FindBestPath(scene->gridMap.PointToGridPoint(scene->GetPlayerGridPoint()), scene->gridMap.PointToGridPoint(target), &scene->gridMap, &scene->player->path);
		scene->player->Move(&scene->gridMap.unitGrid, GetPointsDirection(scene->gridMap.PointToGridPoint(scene->GetPlayerGridPoint()), scene->gridMap.PointToGridPoint(target)));
		return 0;
	}
	int Game::GoodsButtonEventHandler(EventArgs e)
	{

	}
}