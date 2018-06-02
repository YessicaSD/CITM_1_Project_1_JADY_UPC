#ifndef __PARTICLE_H_MISSILE_H__
#define __PARTICLE_H_MISSILE_H__

#include "Particle.h"

//CONSIDERATIONS
//- Pivot point
//x = at the front of the missile
//y = at the center of the missile
//Explanatory drawing:
//----------
//---------+
//----------

enum HMissilePhase
{
	steppingOut,
	movingForward
};

class Particle_HMissile : public Particle
{
public:
	Particle_HMissile();
	Particle_HMissile(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);
	~Particle_HMissile();

	void Move();
	void Draw();
	void OnCollision(Collider*, Collider*);
	bool CheckParticleDeath();

private:
	void OnCollisionHitDetection(Collider*, Collider*);
	void OnCollisionParticle(Collider*, Collider*);

	int frameCounter;
	HMissilePhase hmissilePhase;

	float distanceToTarget;
	float largestPossibleDistance;
	iPoint targetPos;
	Collider* enemyDetectionCol = nullptr;

	//Animation
	Animation steppingOutAnim;
	Animation movingAnim;
	SDL_Rect currentFrame;
	SDL_Rect missilePartRect;
	SDL_Rect hitDetectionRect;

	int steppingOutSpeed;
	bool firstFrame = true;
	bool destroyMissile = false;
};

#endif // __PARTICLE_ORANGE_BALL_H__
