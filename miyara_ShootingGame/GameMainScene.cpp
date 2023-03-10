#include "GameMainScene.h"
#include "GameMainScene2.h"
#include "GameClear.h"
#include"GameOver.h"
#include"Recovery.h"
#include"DxLib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

GameMainScene::GameMainScene()
{
	T_Location location = T_Location{600,500};
	player = new Player(location);

	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	

	//Enemyを作る
	//enemy[0] = new Enemy(T_Location{ 200, 0 });
	enemy[0] = new Enemy(T_Location{ 640, -100});

	//アイテムの初期化
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = nullptr;
	}

}
//描画以外の更新を実装する
void GameMainScene::Update()
{
	player->Update();
	
	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Update();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Update();
	}

	BulletsBase** bullet = player->GetBullets();
	//エネミーにダメージを与えられる
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		for (int bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr)
			{
				break;
			}

			if (enemy[enemyCount]->HitSphere(bullet[bulletCount]))
			{

				//エネミーにダメージを与えます。
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());
				
				//弾を削除します。
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//エネミーのHssdaa Pが０以下だったら、エネミーを削除します。
				if (enemy[enemyCount]->HpCheck())
				{

					EnemyDown();//関数の呼び出し

					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation()); //エネミーが消えると出てくるようにする
							break;
						}
					}

					//スコア加算
					player->AddScore(enemy[enemyCount]->GetPoint());

					//エネミーの削除
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//配列を前に詰める
					for (int i = enemyCount; i < 10; i++)
					{
						if (enemy[i] == nullptr)
						{
							break;
						}
						enemy[i - 1] = enemy[i];
						enemy[i] = nullptr;
					}

					enemyCount--;
					break;
				}
			}
		}
	}

	//たまループ参照
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		bullet = enemy[enemyCount]->GetBullets();
		for (int i = 0; i < 30; i++)
		{
			if (bullet[i] == nullptr)
			{
				break;
			}

			if (player->HitSphere(bullet[i]))
			{
				//プレイヤーにダメージを与えます
				player->Hit(bullet[i]->GetDamage());

				//弾を削除します
				enemy[enemyCount]->DeleteBullet(i);
				i--;

			}
		}
	}

	for (int itemCount = 0; itemCount < 10; itemCount++)
	{
		if (items[itemCount] == nullptr)
		{
			break;
		}

		if (items[itemCount]->HitSphere(player) == true)
		{
			//回復処理
			player->Hit(items[itemCount]);

			//アイテムに触れると消える
			delete items[itemCount];
			items[itemCount] = nullptr;

			for (int i = itemCount + 1; i < 10; i++)
			{
				if (items[i] == nullptr)
				{
					break;
				}

				items[i - 1] = items[i];
				items[i] = nullptr;
			}
			itemCount--;
		}
	}
}

//描画に関することを実装する
void GameMainScene::Draw() const
{
	player->Draw();
	for (int enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Draw();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Draw();
	}
}


int GameMainScene::EnemyDown()//カウントされた数字をもらう
{
	enemyDown++;
	return enemyDown;//プラス1された状態のはず…
}


//シーンの変更処理
AbstractScene* GameMainScene::ChangeScene()
{
	if (enemyDown == enemyVolume)//ステージ移行
	{
		return new GameMainScene2();
	}

	return this;
}