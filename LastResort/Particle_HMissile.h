#ifndef __PARTICLE_H_MISSILE_H__
#define __PARTICLE_H_MISSILE_H__

#include "Particle.h"

class Particle_HMissile : public Particle
{
public:
	Particle_HMissile();
	Particle_HMissile(Particle&, fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);

	void Move();
	void Draw();
	void OnCollision(Collider*, Collider*);

private:
	void OnCollisionHitDetection(Collider*, Collider*);
	void OnCollisionParticle(Collider*, Collider*);

	float distanceToTarget;
	float largestPossibleDistance;
	iPoint targetPos;
	Collider* enemyDetectionCol;

	//Animation
	Animation steppingOutAnim;
	Animation movingAnim;
	SDL_Rect currentFrame;
	SDL_Rect missilePartRect;
	SDL_Rect hitDetectionRect;
};

#endif // __PARTICLE_ORANGE_BALL_H__
