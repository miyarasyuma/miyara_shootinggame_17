#include "GameOver.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"TitleScene.h"

GameOver::GameOver()
{

}

void GameOver::Update()
{
	KeyManager::Update();
}

void GameOver::Draw() const
{
	DrawFormatString(500, 200, 0xffffff, "GameOver");
	DrawFormatString(500, 300, 0xffffff, "Prease X");
}

AbstractScene* GameOver::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_X))//キーボード用かマウス用かちゃんと見る
	{
		return new TitleScene();//行きたい場所
	}

	return this;//どの場所にも必要
}