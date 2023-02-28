#pragma once
#include "AbstractScene.h"
#include"Player.h"
#include"Enemy2.h"
#include"ItemBase.h"
class GameMainScene2 : public AbstractScene
{
private:
	Player* player;
	Enemy2** enemy2;
	ItemBase** items;

protected:
	//もう一体のエネミーを作ったら同じ感じにしてどちらともTUREだったらみたいな判定を作る
	int enemyDown = 0;//エネミーが倒されたら倒された分をカウントする
	int enemyVolume = 1;//ステージに出す分のエネミー分の数を設定しておく


public:
	GameMainScene2();
	virtual ~GameMainScene2()	//デストラクタ
	{}


public:
	virtual void Update() override;  //描画以外の更新を実装する
	virtual void Draw() const override;	//描画に関することを実装する
	virtual AbstractScene* ChangeScene() override;	//シーンの変更処理
	int EnemyDown();//カウントされた数字を貰う
};