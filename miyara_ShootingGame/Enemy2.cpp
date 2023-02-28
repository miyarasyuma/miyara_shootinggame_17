#include "Enemy2.h"
#include"DxLib.h"
#include"BulletsBase.h"
#include"StraightBullets.h"
#include "SpiralBullet.h"
#include"Diffusion.h"

void Enemy2::inputCSV()
{
	FILE* fp;//FILE�^�\����
	errno_t error;// fopen_s�̃G���[�m�F

	error = fopen_s(&fp, "EnemyDate/EnemyMove2.csv", "r");//�f�[�^��u�����ꏊ����������Ǝw�肷��
		//CSV�t�@�C�������B�W���A���X�^�W�I�ɓǂݍ��܂���Ƃ��̓X�y�[�X�Ȃǂ͎g��Ȃ��悤�ɂ���

	if (error != 0)
	{
		//�G���[����
		return;
	}
	else
	{
		//�t�@�C�����J����
		char line[100];//��s
		//while (fgets(line, 100, fp) != NULL)
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)//100�̏��͈�s��100������������Ƃ����Ӗ�
		{
			sscanf_s(line, "%d, %f, %f, %d, %d, %d",//line����s������ : %�̏��͐������������Ƃ��Ă������ : �Ō�͍\���̂ɓ��Ă͂߂�
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

	fclose(fp); //�t�@�C�������
}

Enemy2::Enemy2(T_Location location) :CharaBase(location, 20.f, T_Location{ 1.4,1 })
, hp(10), point(100), shotNum(0)
{
	bullets = new BulletsBase * [30];//�����ɂR�O���o����悤�ɂ���
	for (int i = 0; i < 30; i++)//���g��nullptr�����Ă���
	{
		bullets[i] = nullptr;
	}


	inputCSV();//CSV�t�@�C���̏�����


}

void Enemy2::Update()
{
	switch (moveInfo[current].pattern)
	{
	case 0://�ړ�����
		Move();
		break;

	case 1://�����Ȃ�
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

		//��ʊO�ɍs������e������
		if (bullets[bulletCount]->isScreenOut())//��ʊO�ŏ��������m���߂�
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
				//enemy�̒e���𐶐�
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
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));//�G�̖{��

	//�G�l�~�[�̒e�̕`��

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

bool Enemy2::HpCheck()//Enemy�̗̑�	
{
	//�O�ɂȂ�����true,0�ȊOfalse
	bool ret = (hp <= 0);
	return ret;
}

int Enemy2::GetPoint()//
{
	return point;
}

void Enemy2::Move()
{
	T_Location nextLocation = GetLocation();//��������W�������Ă���

	if ((nextLocation.y == moveInfo[current].destination.y) &&  //�������W�ɂ����玟�̍��W�Ɉړ�����
		(nextLocation.x == moveInfo[current].destination.x))
	{
		current = moveInfo[current].nextArrayNum;
		return;
	}
	else
	{//�ړI�n�ɂ��Ȃ�������
		if (nextLocation.y != moveInfo[current].destination.y)
		{
			if (nextLocation.y < moveInfo[current].destination.y)//��������W���傫����������Z���čs��
			{
				nextLocation.y += speed.y;
				if ((GetLocation().y <= moveInfo[current].destination.y) && (moveInfo[current].destination.y <= nextLocation.y))//���̍��W���ړI�n���ł����Ƃ�
				{
					nextLocation.y = moveInfo[current].destination.y;//�ړI�n���щz�����Ƃ��ɑ�����ē������W�ɂ���
				}
			}
			else
			{
				nextLocation.y -= speed.y;
				if ((nextLocation.y <= moveInfo[current].destination.y) && (moveInfo[current].destination.y <= GetLocation().y))//���̍��W���ړI�n���ł����Ƃ�
				{
					nextLocation.y = moveInfo[current].destination.y;//�ړI�n���щz�����Ƃ��ɑ�����ē������W�ɂ���
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