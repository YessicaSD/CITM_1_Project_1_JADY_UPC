#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "Particle.h"

#define MAX_ACTIVE_PARTICLES 200

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;
struct Sfx;

enum PARTICLE_TYPE
{
	//- Basic
	PARTICLE_FOLLOW_WORLD,
	PARTICLE_FOLLOW_BACKGROUND,//Follows background, but can have speed (in that case it will follow the background and move at that speed)
	//- More complex
	PARTICLE_LASER,
	PARTICLE_G_MISSILE,
	PARTICLE_H_MISSILE,
	PARTICLE_MISSILE,
	PARTICLE_FIREBALL,
	PARTICLE_INDOOR_LASER,
	PARTICLE_BOSS,
	PARTICLE_ASSIS_TURRET,
	MAX_PARTICLE,//Always last
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	//Inherited functons
	bool Start();
	update_status LogicUpdate();
	update_status RenderUpdate0();
	update_status RenderUpdate1();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	//Module functions
	Particle* AddParticle(Particle& particle, fPoint position, fPoint speed, SDL_Texture *tex ,COLLIDER_TYPE collider_type = COLLIDER_IGNORE_HIT, Uint32 delay = 0, PARTICLE_TYPE particle_type = PARTICLE_FOLLOW_WORLD);
	

private:
	void InitParticleValues();

	
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	//TEXTURES-----------------------------------------
	SDL_Texture* explosionTx = nullptr;
	SDL_Texture * particlesTx = nullptr;
	SDL_Texture * laserTx = nullptr;
	
	//SFX----------------------------------------------
	//Mix_Chunk* g_explosion02_2sfx = nullptr;
	//Mix_Chunk* g_explosion02_3sfx = nullptr;	
	//Mix_Chunk* g_explosion01_2sfx = nullptr;
	//Mix_Chunk* g_explosion01_3sfx = nullptr;

	//PARTICLES----------------------------------------
	//- Player
	Particle basicShot;
	Particle basic_explosion; //Basic Shot Explosion
	Sfx* basicShotSfx = nullptr;

	Particle unit_explosion;//Unit shot explosion
	Particle unitShot;

	Particle death_explosion;//Death explosion 
	Sfx* deathSfx = nullptr;

	//- PoweUps 
	Particle basicLaser; //Basic laser Shot
	Particle littleRings;
	Particle littleRingsExplosion;
	Particle bigRings;
	Particle bigRingsExplotion;
	Particle hMissile;
	Sfx* basicLaserFx = nullptr;

	Particle groundMissile;
	Particle gM_explosion;

	//- General
	Particle g_explosion01;
	Particle g_explosion02;
	Sfx* g_explosion01_1sfx = nullptr;
	Sfx* g_explosion02_1sfx = nullptr;
	Sfx* laserEnemyShot_sfx = nullptr;
	Sfx* laserTravelling = nullptr;
	Sfx* rocketExplosion = nullptr;
	Sfx* rocket = nullptr;

	//- Enemies
	Particle i_f_Shot;
	Particle middleBossShot;
	Particle middleBosExplosion;
	Particle orangeBall;
	Particle orangeBallExplosion;
	Particle laserEnemyShot;
	Particle asteroidDestroy;
	Particle littleAsteroidDestroy;
	Particle MiddleAsteroidDestroy;
	Sfx* asteroisExplotionSfx=nullptr;

	Particle fireBall;
	Particle fireBar;
	Particle missile;
	Particle missile_2;
	Particle missileExplosion;
	Particle indoorLaser;
	Particle barGuardShot;
	Particle bossShot;
	Sfx* bossShot_sfx = nullptr;

	//- OTHER
	iPoint VectorMiddleBossShots;
};

#endif // __MODULEPARTICLES_H__

