#pragma once
#include "AbstractScene.h"
class GameOver :   public AbstractScene
{

public:
	GameOver();//�R���X�g���N�^
	virtual ~GameOver() {};//�f�X�g���N�^

	virtual void Update()override;//�`��ȊO�̍X�V���������� 
	virtual void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
	virtual AbstractScene* ChangeScene() override;//�V�[���̕ύX����
};

