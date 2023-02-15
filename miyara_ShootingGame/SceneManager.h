#pragma once
#include "AbstractScene.h"
class SceneManager :public AbstractScene
{
private:
	AbstractScene* mScene; //現在のシーン

public:
	//コンストラクタ
	SceneManager(AbstractScene* scene) 
		:mScene(scene) 
	{}

	//デストラクタ
	~SceneManager() 
	{
		delete mScene;
	}

	//描画以外の更新を実装する
	void Update() override;

	//描画に関することを実装する
	void Draw() const override;

	//シーンの変更処理
	virtual AbstractScene* ChangeScene() override;
};
