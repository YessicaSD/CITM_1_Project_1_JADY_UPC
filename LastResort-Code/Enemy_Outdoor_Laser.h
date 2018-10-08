#ifndef __ENEMY_OUTDOOR_LACER_H__
#define __ENEMY_OUTDOOR_LASER_H__

#include "Enemy.h"

class Enemy_Outdoor_Laser : public Enemy
{
private:
	Animation OutdoorLacerAnim;
	int initialY;
	int position_y;
	int position_x;
public:
	Enemy_Outdoor_Laser(int x, int y, POWERUP_TYPE pu_t);
	void Move();
};

#endif // __ENEMY_OUTDOOR_LASER_H__

