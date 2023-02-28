#include "Enemy2.h"
#include"DxLib.h"
#include"BulletsBase.h"
#include"StraightBullets.h"
#include "SpiralBullet.h"
#include"Diffusion.h"

void Enemy2::inputCSV()
{
	FILE* fp;//FILE型構造体
	errno_t error;// fopen_sのエラー確認

	error = fopen_s(&fp, "EnemyDate/EnemyMove2.csv", "r");//データを置いた場所をしっかりと指定する
		//CSVファイルをヴィジュアルスタジオに読み込ませるときはスペースなどは使わないようにする

	if (error != 0)
	{
		//エラー発生
		return;
	}
	else
	{
		//ファイルを開いた
		char line[100];//一行
		//while (fgets(line, 100, fp) != NULL)
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)//100の所は一行に100文字分を見るという意味
		{
			sscanf_s(line, "%d, %f, %f, %d, %d, %d",//lineが一行を見る : %の所は整数か少数をとってくるもの : 最後は構造体に当てはめる
				&moveInfo[i].pattern,
				&moveInfo[i].destination.x,
				&moveInfo[i].destination.y,
				&moveInfo[i].nextArrayNum,
				&moveInfo[i].waitFrameTime,
				&moveInfo[i].attackType
			);
		}

		return;
	}

	fclose(fp); //ファイルを閉じる
}

Enemy2::Enemy2(T_Location location) :CharaBase(location, 20.f, T_Location{ 1.4,1 })
, hp(10), point(100), shotNum(0)
{
	bullets = new BulletsBase * [30];//同時に３０発出せるようにする
	for (int i = 0; i < 30; i++)//中身にnullptrを入れている
	{
		bullets[i] = nullptr;
	}


	inputCSV();//CSVファイルの初期化


}

void Enemy2::Update()
{
	switch (moveInfo[current].pattern)
	{
	case 0://移動処理
		Move();
		break;

	case 1://動かない
		waittime++;
		if (moveInfo[current].waitFrameTime <= waittime)
		{
			waittime = 0;
			current = moveInfo[current].nextArrayNum;
		}
		break;

	default:
		break;
	}

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bulletCount == 30)
		{
			break;
		}
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

	if (moveInfo[current].attackType != 0)
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			if (moveInfo[current].attackType == 1)
			{
				//enemyの弾幕を生成
				bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,-2 });
				//bullets[bulletCount]=new StraightBullets(GetLocation(),T_Location)
			}
			else if (moveInfo[current].attackType == 2)
			{
				shotNum++;
				bullets[bulletCount] = new Diffusion(GetLocation(), 2.f, (20 * shotNum));

			}
		}
	}
}


void Enemy2::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));//敵の本体

	//エネミーの弾の描画

	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Enemy2::Hit(int damage)//Enemy
{
	if (0 < damage)
	{
		hp -= damage;
		if (hp < 0)
		{
			hp = 0;
		}
	}
}

bool Enemy2::HpCheck()//Enemyの体力	
{
	//０になったらtrue,0以外false
	bool ret = (hp <= 0);
	return ret;
}

int Enemy2::GetPoint()//
{
	return point;
}

void Enemy2::Move()
{
	T_Location nextLocation = GetLocation();//今いる座標から取ってくる

	if ((nextLocation.y == moveInfo[current].destination.y) &&  //同じ座標にいたら次の座標に移動する
		(nextLocation.x == moveInfo[current].destination.x))
	{
		current = moveInfo[current].nextArrayNum;
		return;
	}
	else
	{//目的地にいなかったら
		if (nextLocation.y != moveInfo[current].destination.y)
		{
			if (nextLocation.y < moveInfo[current].destination.y)//今いる座標より大きかったら加算して行く
			{
				nextLocation.y += speed.y;
				if ((GetLocation().y <= moveInfo[current].destination.y) && (moveInfo[current].destination.y <= nextLocation.y))//今の座標より目的地がでかいとき
				{
					nextLocation.y = moveInfo[current].destination.y;//目的地を飛び越えたときに代入して同じ座標にする
				}
			}
			else
			{
				nextLocation.y -= speed.y;
				if ((nextLocation.y <= moveInfo[current].destination.y) && (moveInfo[current].destination.y <= GetLocation().y))//今の座標より目的地がでかいとき
				{
					nextLocation.y = moveInfo[current].destination.y;//目的地を飛び越えたときに代入して同じ座標にする
				}
			}
		}

		if (nextLocation.x != moveInfo[current].destination.x)
		{
			if (nextLocation.x < moveInfo[current].destination.x)
			{
				nextLocation.x += speed.x;
				if ((GetLocation().x <= moveInfo[current].destination.x) && (moveInfo[current].destination.x <= nextLocation.x))
				{
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
			else
			{
				nextLocation.x -= speed.x;
				if ((nextLocation.x <= moveInfo[current].destination.x) && (moveInfo[current].destination.x <= GetLocation().x))
				{
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}