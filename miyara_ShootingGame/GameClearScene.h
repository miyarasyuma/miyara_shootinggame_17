#pragma once
#include "AbstractScene.h"
class GameClearScene : public AbstractScene
{


public:
	GameClearScene();//�R���X�g���N�^
	virtual ~GameClearScene() {};//�f�X�g���N�^

	virtual void Update()override;//�`��ȊO�̍X�V���������� 
	virtual void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
	virtual AbstractScene* ChangeScene() override;//�V�[���̕ύX����
};

