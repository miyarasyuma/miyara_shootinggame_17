#pragma once
#include "AbstractScene.h"
class GameClear :  public AbstractScene
{
public:
	GameClear();//コンストラクタ
	virtual ~GameClear() {};//デストラクタ

	virtual void Update()override;//描画以外の更新を実装する 
	virtual void Draw() const override;//描画に関することを実装する
	virtual AbstractScene* ChangeScene() override;//シーンの変更処理
};

