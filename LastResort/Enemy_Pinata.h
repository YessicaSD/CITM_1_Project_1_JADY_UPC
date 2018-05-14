#ifndef __ENEMY_PINATA_H__
#define __ENEMY_PINATA_H__

#include "Enemy.h"
#include "MovPath.h"


class Enemy_Pinata : public Enemy
{
public:
	Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t);
	void Move();

private:
	Animation moveAnim;
	Animation rotateAnim;
	Animation initAnim;
	
	enum {
		MOVE_RIGHT = 0,
		MOVE_LEFT = 1
	};

	enum Move_States {
		INIT,
		FOLLOW,
		ROTATE
	};

	bool direction;
	Move_States currentState = INIT;
	Move_States lastState = INIT;
	int moveSpeed;
	MovePath pinataMov;
	bool searchPlayers = false;
	Module* targetPlayer = nullptr;
};

#endif // __ENEMY_PINATA_H__
