#ifndef __ENEMY_LAMELLA_H__
#define __ENEMY_LAMELLA_H__

#include "Enemy.h"

class ModulePlayer;

class Enemy_Lamella : public Enemy
{
public:
	Enemy_Lamella(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop);
	void Move();
	void Draw(SDL_Texture* sprites);

private:
	enum phases
	{
		appearing,
		moving,
		disappearing,
	};
	phases lamellaPhase = appearing;

	fPoint auxPos;//A float position that will help us keep the decimals on the position

	Animation appearingAnim;
	Animation disappearingAnim;
	Animation movingAnim;

	iPoint targetPos;
	const float moveSpeed = 2;

	SDL_Rect currentFrame;
	bool flip = false;
};

#endif // __ENEMY_RED_LAMELLA_H__