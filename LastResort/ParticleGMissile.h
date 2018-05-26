#ifndef __PARTICLE_G_MISSILE_H__
#define __PARTICLE_G_MISSILE_H__

#include "Particle.h"
#include "ModuleUnit.h"

enum moveStates {
	air_State,
	ft_State
};

class Particle_G_Missile : public Particle
{
public:
	moveStates moveState = air_State;
	fPoint aceleration;
	SDL_Rect*  currentAnim = nullptr;

	int followTerrainSpeed = 4;
	int centerOffset = 8;

	Collider* wallDetectorUp = nullptr;
	Collider* wallDetectorDown = nullptr;
	Collider* wallDetectorLeft = nullptr;
	Collider* wallDetectorRight = nullptr;

	Collider* colliderToFollow = nullptr;

public:

	Particle_G_Missile(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);
	void Move();
	void Draw();
	void OnCollision(Collider* c1, Collider* c2);

	void AirOnCollision(Collider* c1, Collider* c2);
	void FtOnCollision(Collider* c1, Collider* c2);

	void UpdateColliders();
	~Particle_G_Missile();

	void AirMovement();
	void FtMovement();

	//Following terrain
	FollowingTerrainDirection followTerrainDir ;
	bool ColliderIsOnLeft();//Returns true if collider to follow is on the left of the unit
	bool ColliderIsOnRight();//Returns true if collider to follow is on the right of the unit
	bool ColliderIsAbove();//Returns true if collider to follow is above of the unit
	bool ColliderIsBellow();//Returns true if collider to follow is bellow of the unit
};

#endif // __PARTICLE_G_MISSILE_H__

