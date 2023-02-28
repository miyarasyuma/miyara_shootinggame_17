#pragma once
#include "AbstractScene.h"
#include"Player.h"
#include"Enemy.h"
#include"ItemBase.h"
class GameMainScene :  public AbstractScene
{
private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;

protected:
	//������̂̃G�l�~�[��������瓯�������ɂ��Ăǂ���Ƃ�TURE��������݂����Ȕ�������
	int enemyDown = 0;//�G�l�~�[���|���ꂽ��|���ꂽ�����J�E���g����
	int enemyVolume = 1;//�X�e�[�W�ɏo�����̃G�l�~�[���̐���ݒ肵�Ă���

public:
	GameMainScene();
	virtual ~GameMainScene()	//�f�X�g���N�^
	{}


public:
	virtual void Update() override;  //�`��ȊO�̍X�V����������
	virtual void Draw() const override;	//�`��Ɋւ��邱�Ƃ���������
	virtual AbstractScene* ChangeScene() override;	//�V�[���̕ύX����
	int EnemyDown();//�J�E���g���ꂽ������Ⴄ
};

