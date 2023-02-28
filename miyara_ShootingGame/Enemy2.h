#pragma once
#include "CharaBase.h"

//データベースからデータを引っ張ってくるような感じ
struct T_MoveInformation2
{
	int pattern; //行動パターン
	T_Location destination;//目的地
	int nextArrayNum; //次の配列番号
	int waitFrameTime;//待ち時間
	int attackType; //攻撃の種類
};

class Enemy2 : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;

	T_MoveInformation2 moveInfo[5];


	int current = 0;
	int waittime = 0;

public:
	Enemy2(T_Location location);


public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit(int damage) override;

	bool HpCheck();//ヒットポイントをチェックする関数
	int GetPoint();//ポイントをもらう関数
	void Move();//敵の移動処理
	void inputCSV();//CSVファイルの読込み
};

