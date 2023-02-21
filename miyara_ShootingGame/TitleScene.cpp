#include "TitleScene.h"
#include"KeyManager.h"
#include"GameMainScene.h"
#include"DxLib.h"

TitleScene::TitleScene()
{
	Cr = GetColor(255, 255, 255);
}

void TitleScene::Update()
{
	KeyManager::Update();
}

void TitleScene::Draw()const
{
	DrawString(500, 200,"GameStart", Cr);
	DrawString(500, 300, "Prease Z", Cr);
}


AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_Z))
	{
		return new GameMainScene();
	}

	return this;
}