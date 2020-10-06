//---------------------------include------------------------------------
#include "Bullet.h"
//------------------------Bullet----------------------------------------
//Ctor of Bullet that get radius and update data members
Bullet::Bullet(float radius)
	: m_currVelocity(0.f, 0.f), m_maxSpeed(15.f)
{
		m_shape.setRadius(radius);
		m_shape.setFillColor({ 255,99,71 });
		
}

