#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Mix_Chunk;

class Particle
{
public:
	Particle();
	Particle(Particle& , iPoint, Uint32, COLLIDER_TYPE colType);
	~Particle();

	bool CheckParticleDeath();
	virtual void Move();
	virtual void Draw();

public:
	iPoint position;
	iPoint fixedPos;
	Collider * collider = nullptr;
	Animation anim;
	SDL_Texture* texture = nullptr;
	Particle* collision_fx = nullptr;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	Mix_Chunk *sfx = nullptr;

};

#endif // __PARTICLES_H__
