#pragma once
#include"AbstractScene.h"
class TitleScene :  public  AbstractScene
{
private:
	int Cr;

public:
	TitleScene();

	virtual ~TitleScene() {};//�f�X�g���N�^

	virtual void Update()override;//�`��ȊO�̍X�V���������� 
	virtual void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
	virtual AbstractScene* ChangeScene() override;//�V�[���̕ύX����
};

