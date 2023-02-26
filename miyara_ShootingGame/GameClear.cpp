#include "GameClear.h"
#include"DxLib.h"
#include"TitleScene.h"
#include"KeyManager.h"

GameClear::GameClear()
{

}

void GameClear::Update()
{
	KeyManager::Update();
}

void GameClear::Draw()const
{
	DrawFormatString(500, 500, 0xffffff, "GameClear");
	DrawFormatString(500, 700, 0xffffff, "XƒL[‚ğ‰Ÿ‚µ‚Ä‚Ë");
}

AbstractScene* GameClear::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_X))
	{
		return new TitleScene();
	}

	return this;
}