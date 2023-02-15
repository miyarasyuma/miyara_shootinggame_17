#include "SceneManager.h"
#include "KeyManager.h"

//�����o�ϐ��̒l��u��������̂��A�b�v�f�[�g�֐�
void SceneManager::Update()
{
	//���݂̃V�[���̃A�b�v�f�[�g�����s
	KeyManager::Update();
	mScene->Update();
}

//�`�揈���݂̂��s���֐�
void SceneManager::Draw() const
{
	//���݂̃V�[���̕`��֐������s
	mScene->Draw();
}

//�V�[���̕ύX����
AbstractScene* SceneManager::ChangeScene()
{
	AbstractScene* nextScene = mScene->ChangeScene();

	if (nextScene != mScene)
	{
		delete mScene;
		mScene = nextScene;
	}

	return nextScene;
}