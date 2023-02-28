#include "GameMainScene2.h"
#include "GameClear.h"
#include"GameOver.h"
#include"Recovery.h"
#include"DxLib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

GameMainScene2::GameMainScene2()
{
	T_Location location = T_Location{ 600,500 };
	player = new Player(location);

	enemy2 = new Enemy2 * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy2[i] = nullptr;
	}



	//Enemy�����
	//enemy[0] = new Enemy(T_Location{ 200, 0 });
	enemy2[0] = new Enemy2(T_Location{ 640, -100 });

	//�A�C�e���̏�����
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = nullptr;
	}

}
//�`��ȊO�̍X�V����������
void GameMainScene2::Update()
{
	player->Update();

	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy2[enemyCount] == nullptr)
		{
			break;
		}
		enemy2[enemyCount]->Update();
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
	//�G�l�~�[�Ƀ_���[�W��^������
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy2[enemyCount] == nullptr)
		{
			break;
		}
		for (int bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr)
			{
				break;
			}

			if (enemy2[enemyCount]->HitSphere(bullet[bulletCount]))
			{

				//�G�l�~�[�Ƀ_���[�W��^���܂��B
				enemy2[enemyCount]->Hit(bullet[bulletCount]->GetDamage());

				//�e���폜���܂��B
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G�l�~�[��Hssdaa P���O�ȉ���������A�G�l�~�[���폜���܂��B
				if (enemy2[enemyCount]->HpCheck())
				{

					EnemyDown();//�֐��̌Ăяo��
					
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy2[enemyCount]->GetLocation()); //�G�l�~�[��������Əo�Ă���悤�ɂ���
							break;
						}
					}

					//�X�R�A���Z
					player->AddScore(enemy2[enemyCount]->GetPoint());

					//�G�l�~�[�̍폜
					delete enemy2[enemyCount];
					enemy2[enemyCount] = nullptr;

					//�z���O�ɋl�߂�
					for (int i = enemyCount; i < 10; i++)
					{
						if (enemy2[i] == nullptr)
						{
							break;
						}
						enemy2[i - 1] = enemy2[i];
						enemy2[i] = nullptr;
					}

					enemyCount--;
					break;
				}
			}
		}
	}

	//���܃��[�v�Q��
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy2[enemyCount] == nullptr)
		{
			break;
		}
		bullet = enemy2[enemyCount]->GetBullets();
		for (int i = 0; i < 30; i++)
		{
			if (bullet[i] == nullptr)
			{
				break;
			}

			if (player->HitSphere(bullet[i]))
			{
				//�v���C���[�Ƀ_���[�W��^���܂�
				player->Hit(bullet[i]->GetDamage());

				//�e���폜���܂�
				enemy2[enemyCount]->DeleteBullet(i);
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
			//�񕜏���
			player->Hit(items[itemCount]);

			//�A�C�e���ɐG���Ə�����
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

//�`��Ɋւ��邱�Ƃ���������
void GameMainScene2::Draw() const
{
	player->Draw();
	for (int enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy2[enemyCount] == nullptr)
		{
			break;
		}
		enemy2[enemyCount]->Draw();
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

int GameMainScene2::EnemyDown()//�J�E���g���ꂽ���������炤
{
	enemyDown++;
	return enemyDown;//�v���X1���ꂽ��Ԃ̂͂��c
}


//�V�[���̕ύX����
AbstractScene* GameMainScene2::ChangeScene()
{
	if (enemyDown == enemyVolume) //�G��|���ƃN���A
	{
		return new GameClear();
	}

	if (player->LifeCheck())//�v���C���[��HP���O�ɂȂ�ƃQ�[���I�[�o�[
	{
		return new GameOver();
	}

	return this;
}