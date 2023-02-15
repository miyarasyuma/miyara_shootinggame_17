#include "Player.h"
#include"StraightBullets.h"
#include"KeyManager.h"
#include"Recovery.h"
#include "DxLib.h"


Player::Player(T_Location location) :CharaBase(location, 10.f, T_Location{2,2}),score(0),life(10)
{

	//BulletsBase** bullets
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

void Player::Update()
{
	T_Location newLocation = GetLocation();
	//プレイヤー操作キー
	if (KeyManager::OnKeyPressed(KEY_INPUT_W))//上
	{
		newLocation.y -= speed.y;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_A))//左
	{
		newLocation.x -= speed.x;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_S))//下
	{
		newLocation.y += speed.y;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_D))//右
	{
		newLocation.x += speed.x;
	}
	

	SetLocation(newLocation);

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//画面外に行ったら弾を消す
		if (bullets[bulletCount]->isScreenOut())//画面外で消えたか確かめる
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}

	if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT))
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,1 });

		}
	}
}

void Player::Draw()
{
    #define _DEBUG_MODE_

	#ifdef _DEBUG_MODE_
	DrawFormatString(10, 10, GetColor(255, 255, 255), "life=%d", life);
	DrawFormatString(10, 30, GetColor(255, 255, 255), "score=%d", score);

	#endif

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));

	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Player::Hit(int damage)
{
	if (0 < damage)
	{
		life -= damage;
		if (life < 0)
		{
			life = 0;
		}
	}
}

void Player::Hit(class ItemBase* item)
{
	switch (item->GetType())
	{
	 case E_ITEM_TYPE::Heal:
	 {
		 Recovery* recovery = dynamic_cast<Recovery*>(item);
		 life += recovery->GetVolume();
		 break;
	 }
	   default:
		  break;
	}
}

bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

int  Player::GetScore()
{
	return score;
}

void Player::AddScore(int score)
{
	if (0 <= score) 
	{
		this->score += score;
	}
}