#include "BulletsBase.h"
BulletsBase::BulletsBase(T_Location location, float radius, int 
	, T_Location speed):SphereCollider(location, radius),damage(damage),speed(speed)
{

}

int BulletsBase::GetDamage()
{
	return damage;
}