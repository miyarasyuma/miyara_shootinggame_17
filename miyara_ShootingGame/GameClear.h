#pragma once
#include "AbstractScene.h"
class GameClear :  public AbstractScene
{
public:
	GameClear();//�R���X�g���N�^
	virtual ~GameClear() {};//�f�X�g���N�^

	virtual void Update()override;//�`��ȊO�̍X�V���������� 
	virtual void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
	virtual AbstractScene* ChangeScene() override;//�V�[���̕ύX����
};

