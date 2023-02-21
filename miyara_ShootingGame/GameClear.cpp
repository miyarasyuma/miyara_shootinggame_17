#include "GameClearScene.h"
#include"DxLib.h"
#include"TitleScene.h"
#include"KeyManager.h"

GameClearScene::GameClearScene()
{

}

void GameClearScene::Update()
{

}

void GameClearScene::Draw()const
{

}

AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_X))
	{
		return new TitleScene();
	}

	return this;
}