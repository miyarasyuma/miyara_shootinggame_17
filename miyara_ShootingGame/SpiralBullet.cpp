#include "SpiralBullet.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES
#include<math.h>


SpiralBullet::SpiralBullet(T_Location location, float speed, int dgAngle) :BulletsBase(location, 5.f, 1, T_Location{ 0.0 })
{
	//degAngleで角度を取って玉を出す
	int deg = dgAngle % 360;
	double rad = (M_PI / 180) * deg;
	float x = (abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad); //(条件式)？TRUE:FALSE
	float y = sin(rad);

	this->speed = T_Location{ (speed * x),(speed * y) };
}

void SpiralBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void SpiralBullet::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));
}

bool SpiralBullet::isScreenOut()
{
	//弾が完全に画面外に行くと消える
	bool ret = (GetLocation().y + GetRadius() <= 0 || GetLocation().y + GetRadius() >= 720);
	     ret= (GetLocation().x + GetRadius() <= 0 || GetLocation().x + GetRadius() >= 1280);

	return ret;
}