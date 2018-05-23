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


enum PARTICLE_TYPE
{
	PARTICLE_REGULAR,
	PARTICLE_LASER,
	PARTICLE_G_MISSILE,
	MAX_PARTICLE,

};
class Particle
{
public:
	Collider * collider = nullptr;
	Animation anim;
	SDL_Texture* texture = nullptr;
	Particle* collision_fx = nullptr;
	iPoint position;
	iPoint initialPosition;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	Mix_Chunk *sfx = nullptr;
	virtual void Move();
	virtual void Draw();
	Particle();
	Particle( Particle& p);
	~Particle();
	bool Update();
	/*virtual void Move();*/
};

#endif // __PARTICLES_H__
