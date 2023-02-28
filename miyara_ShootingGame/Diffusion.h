#pragma once
#include "BulletsBase.h"
class Diffusion : public BulletsBase
{
public:
	Diffusion(T_Location location, float speed, int dgAngle);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};

