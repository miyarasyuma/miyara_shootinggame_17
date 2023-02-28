#include "Diffusion.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES
#include<math.h>


Diffusion::Diffusion(T_Location location, float speed, int dgAngle) :BulletsBase(location, 5.f, 1, T_Location{ 0.0 })
{
	//degAngle�Ŋp�x������ċʂ��o��
	int deg = dgAngle % 90;
	double rad = (M_PI / 90) * deg;
	float x = (abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad); //(������)�HTRUE:FALSE
	float y = sin(rad);

	this->speed = T_Location{ (speed * x),(speed * y) };
}

void Diffusion::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.x += speed.x;
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void Diffusion::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));
}

bool Diffusion::isScreenOut()
{
	//�e�����S�ɉ�ʊO�ɍs���Ə�����
	bool ret = (GetLocation().y + GetRadius() <= 0 || GetLocation().y + GetRadius() >= 720);
	ret = (GetLocation().x + GetRadius() <= 0 || GetLocation().x + GetRadius() >= 1280);

	return ret;
}