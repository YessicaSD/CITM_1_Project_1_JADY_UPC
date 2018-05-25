#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "Particle.h"
#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Mix_Chunk;

enum PARTICLE_TYPE
{
	//- Basic
	PARTICLE_FOLLOW_WORLD,
	PARTICLE_FOLLOW_BACKGROUND,//Follows background, but can have speed (in that case it will follow the background and move at that speed)
	//- More complex
	PARTICLE_LASER,
	PARTICLE_G_MISSILE,
	MAX_PARTICLE,//Always last
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	//Inherited functons
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	//Module functions
	void AddParticle(Particle& particle, fPoint position, fPoint speed, SDL_Texture *tex ,COLLIDER_TYPE collider_type = COLLIDER_IGNORE_HIT, Uint32 delay = 0, PARTICLE_TYPE particle_type = PARTICLE_FOLLOW_WORLD);
	

private:
	void InitParticleValues();

	SDL_Texture* explosionTx = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	//TEXTURES-----------------------------------------
	SDL_Texture * particlesTx;
	SDL_Texture * laserTx;
	
	//SFX----------------------------------------------
	Mix_Chunk* AsteroidDestroySfx;
	//Mix_Chunk* g_explosion02_2sfx = nullptr;
	//Mix_Chunk* g_explosion02_3sfx = nullptr;	
	//Mix_Chunk* g_explosion01_2sfx = nullptr;
	//Mix_Chunk* g_explosion01_3sfx = nullptr;

	//PARTICLES----------------------------------------
	//- Player
	Particle basicShot;
	Particle basic_explosion; //Basic Shot Explosion
	Mix_Chunk* basicShotSfx = nullptr;
	Particle unit_explosion;//Unit shot explosion
	Particle unitShot;
	Particle death_explosion;//Death explosion 
	Mix_Chunk* deathSfx = nullptr;

	Particle basicLaser;
	Particle littleRings;

	//- General
	Particle g_explosion01;
	Particle g_explosion02;
	Mix_Chunk* g_explosion01_1sfx = nullptr;
	Mix_Chunk* g_explosion02_1sfx = nullptr;
	Mix_Chunk* basicLaserFx = nullptr;

	//- Enemies
	Particle MiddleBossShot;
	Particle MiddleBosExplotion;
	Particle orangeBall;
	Particle orangeBallExplosion;
	Particle LaserEnemyShot;
	Particle AsteroidDestroy;
	Particle MiddleAsteroidDestroy;
	Particle fireBall;

	//- OTHER
	iPoint VectorMiddleBossShots;
};

#endif // __MODULEPARTICLES_H__

