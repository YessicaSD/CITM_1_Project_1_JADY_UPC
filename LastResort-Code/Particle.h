#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"



struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Sfx;

class Particle
{
public:
	Particle();
	Particle(Particle& , fPoint, fPoint, Uint32, COLLIDER_TYPE colType, SDL_Texture* tex);
	virtual ~Particle();

	virtual bool CheckParticleDeath();
	virtual void Move();
	virtual void Draw();
	virtual void OnCollision(Collider* c1, Collider* c2);


public:
	fPoint position;
	fPoint fixedPos;
	Collider * collider = nullptr;
	Animation anim;
	SDL_Texture* texture = nullptr;
	Particle* collision_fx = nullptr;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	Sfx *sfx = nullptr;
	int renderLayer = 1;

	bool flipY = false;
	bool flipX = false;
	bool hasCallback = false;
	int distanceToPlayer = 0;//used for the H missiles

protected:
	SDL_Rect currentFrame;
};

#endif // __PARTICLES_H__
