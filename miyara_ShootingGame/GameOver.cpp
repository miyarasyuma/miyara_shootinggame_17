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
	if (KeyManager::OnKeyPressed(KEY_INPUT_X))//�L�[�{�[�h�p���}�E�X�p�������ƌ���
	{
		return new TitleScene();//�s�������ꏊ
	}

	return this;//�ǂ̏ꏊ�ɂ��K�v
}