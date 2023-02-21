#include "GameMainScene.h"
#include"Recovery.h"
#include"DxLib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

GameMainScene::GameMainScene()
{
	T_Location location = T_Location{100,100};
	player = new Player(location);


	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	//Enemy�����
	//enemy[0] = new Enemy(T_Location{ 200, 0 });
	enemy[0] = new Enemy(T_Location{ 640, -100});

	//�A�C�e���̏�����
	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = nullptr;
	}

}
//�`��ȊO�̍X�V����������
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
	//�G�l�~�[�Ƀ_���[�W��^������
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

				//�G�l�~�[�Ƀ_���[�W��^���܂��B
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());
				
				//�e���폜���܂��B
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G�l�~�[��Hssdaa P���O�ȉ���������A�G�l�~�[���폜���܂��B
				if (enemy[enemyCount]->HpCheck())
				{
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation()); //�G�l�~�[��������Əo�Ă���悤�ɂ���
							break;
						}
					}

					//�X�R�A���Z
					player->AddScore(enemy[enemyCount]->GetPoint());

					//�G�l�~�[�̍폜
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//�z���O�ɋl�߂�
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

	//���܃��[�v�Q��
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
				//�v���C���[�Ƀ_���[�W��^���܂�
				player->Hit(bullet[i]->GetDamage());

				//�e���폜���܂�
				enemy[enemyCount]->DeleteBullet(i);
				i--;

				//�v���C���[��HP��0�ɂȂ�����v���C���[������
				if (player->LifeCheck())
				{

				}
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
//�V�[���̕ύX����
AbstractScene* GameMainScene::ChangeScene()
{
	return this;
}