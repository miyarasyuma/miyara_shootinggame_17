#pragma once
#include "CharaBase.h"

//�f�[�^�x�[�X����f�[�^�����������Ă���悤�Ȋ���
struct T_MoveInformation
{
	int pattern; //�s���p�^�[��
	T_Location destination;//�ړI�n
	int nextArrayNum; //���̔z��ԍ�
	int waitFrameTime;//�҂�����
	int attackType; //�U���̎��
};

class Enemy : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;

	T_MoveInformation moveInfo[5];


	int current = 0;
	int waittime = 0;

public:
	Enemy(T_Location location);


public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit(int damage) override;

	bool HpCheck();//�q�b�g�|�C���g���`�F�b�N����֐�
	int GetPoint();//�|�C���g�����炤�֐�
	void Move();//�G�̈ړ�����
	void inputCSV();//CSV�t�@�C���̓Ǎ���

};

