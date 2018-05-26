#include <math.h>

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "Player1.h"
#include "Player2.h"
#include "ParticleLaser.h"
#include "ParticleGMissile.h"
#include "Particle_Follow_background.h"
#include "Particle_HMissile.h"
#include "Particle_Missile.h"
#include "ModuleStage05.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	//Clear the array
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		active[i] = nullptr;
	}
	
	InitParticleValues();
}

ModuleParticles::~ModuleParticles()
{

}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading ModuleParticles assets ");
	//- Load textures
	particlesTx = App->textures->Load("Assets/particles.png");
	explosionTx = App->textures->Load("Assets/General/Fx/Explosion_2.png");
	laserTx     = App->textures->Load("Assets/General/Enemies/Laser_Niv5.png");
	//- Load audios
	basicLaserFx       = App->audio->LoadSFX("Assets/014. Lasser_2-Center.WAV");
	basicShotSfx       = App->audio->LoadSFX("Assets/004. Shot - center.wav");
	deathSfx           = App->audio->LoadSFX("Assets/005. Death.wav");
	g_explosion01_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_1.wav");
	g_explosion02_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_2.wav");
	laserEnemyShot_sfx = App->audio->LoadSFX("Assets/General/Fx/lasers spawning.wav");
	laserTravelling    = App->audio->LoadSFX("Assets/General/Fx/lasers traveling.wav");
	rocketExplosion    = App->audio->LoadSFX("Assets/General/Fx/rocket explosion.wav");
	rocket             = App->audio->LoadSFX("Assets/General/Fx/rocket.wav");
	//- Initializate textures
	g_explosion02.texture = explosionTx;
	//- Initializate audios
	basicLaser.sfx = basicLaserFx;
	basicShot.sfx = basicShotSfx;
	death_explosion.sfx = deathSfx;
	LaserEnemyShot.sfx = laserEnemyShot_sfx;
	Missile.sfx = rocket;
	MissileExplosion.sfx = rocketExplosion;
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	
	//textures--------------------------------------------------
	App->textures->Unload(explosionTx);
	App->textures->Unload(laserTx);
	App->textures->Unload(particlesTx);
	//audios---------------------------------------------------
	App->audio->UnloadSFX(basicShotSfx);
	App->audio->UnloadSFX(deathSfx);
	App->audio->UnloadSFX(basicLaserFx);
	App->audio->UnloadSFX(g_explosion01_1sfx);
	App->audio->UnloadSFX(g_explosion02_1sfx);
	App->audio->UnloadSFX(laserEnemyShot_sfx);

	//----------------------------------------------------------
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//If there isn't a particle in that position of the array, go to the next particle in the array
		if (active[i] == nullptr)
		{
			continue;
		}	

		//Check if it needs to be deleted
		if (active[i]->CheckParticleDeath() == true)
		{
			//Delete the particle
			delete active[i];
			active[i] = nullptr;
		}

		else if (SDL_GetTicks() >= active[i]->born)
		{
			//Update the particle
			active[i]->Move();
			active[i]->Draw();
		}
	}
	return UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(Particle& particle, fPoint position, fPoint speed, SDL_Texture *tex, COLLIDER_TYPE colType, Uint32 delay, PARTICLE_TYPE particle_type)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = nullptr;

			switch (particle_type)
			{
			case PARTICLE_FOLLOW_WORLD:
				p = new Particle(particle, position, speed, delay, colType, tex);
				break;
			case PARTICLE_FOLLOW_BACKGROUND:
				p = new Particle_Follow_background(particle, position, speed, delay, colType, tex);
				break;
			case PARTICLE_LASER:
				p = new Particle_Laser(particle, position, speed, delay, colType, tex);
				break;
			case PARTICLE_G_MISSILE:
				p = new Particle_G_Missile(particle, position, speed, delay, colType, tex);
				p->hasCallback = true;
				break;
			case PARTICLE_H_MISSILE:
				p = new Particle_HMissile(particle, position, speed, delay, colType, tex);
				p->hasCallback = true;
				break;
			case PARTICLE_MISSILE:
				p = new Particle_Missile(particle, position, speed, delay, colType, tex);
				break;
			}

			//Check if the particle is still nullptr (that would mean it hasn't been created)
			if (p == nullptr)
			{
				LOG("Particle could not be created.")
				return nullptr;
			}

			//Associate new particle with a position in the array
			active[i] = p;
			return  active[i];
		}
	}
	return nullptr;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Special particles that needs OnCollision checks (for example, H and G missiles)
		if (active[i] != nullptr && active[i]->hasCallback == true)
		{
			active[i]->OnCollision(c1, c2);
			//Destroy if it's the particle collider what collided
			if(active[i]->collider == c1)
			{
				delete active[i];
				active[i] = nullptr;
				break;
			}
			continue;
		}

		// Destroy if it's the particle's collider what collided
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			active[i]->OnCollision(c1, c2);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

//Each new particle has to initializate:
//- Push backs for its animation
void ModuleParticles::InitParticleValues()
{
	//Player----------------------------------------------------------------------------//

	//Basic Shot Explosion Particle-----------------------------
	basic_explosion.anim.PushBack({ 305,263, 16,16 }); //1
	basic_explosion.anim.PushBack({ 287,263, 16,16 }); //2
	basic_explosion.anim.PushBack({ 285,247, 13,13 }); //3
	basic_explosion.anim.PushBack({ 271,263, 14,14 }); //4
	basic_explosion.anim.PushBack({ 300,247, 14,14 }); //5
	basic_explosion.anim.PushBack({ 316,247, 14,14 }); //6
	basic_explosion.anim.PushBack({ 217,247, 12,12 }); //7
	basic_explosion.anim.loop = false;
	basic_explosion.anim.speed = 0.3f;

	//Basic Shot Particle---------------------------------------
	basicShot.anim.PushBack({ 0,247, 15,7 });
	basicShot.anim.speed = 0.0f;
	basicShot.anim.loop = false;
	basicShot.collision_fx = &basic_explosion;

	//Basic shot particle---------------------------------------
	unitShot.anim.PushBack({ 155, 288, 13, 13 });
	unitShot.anim.PushBack({ 170, 288, 13, 13 });
	unitShot.anim.PushBack({ 155, 303, 13, 13 });
	unitShot.anim.PushBack({ 170, 303, 13, 13 });
	unitShot.anim.PushBack({ 155, 318, 13, 13 });
	unitShot.anim.PushBack({ 170, 318, 13, 13 });
	unitShot.anim.PushBack({ 155, 333, 13, 13 });
	unitShot.anim.PushBack({ 170, 333, 13, 13 });
	unitShot.anim.loop = true;
	unitShot.anim.speed = 0.3f;
	unitShot.life = 2000;
	unitShot.collision_fx = &unit_explosion;

	//-----------------------------------------------------------------------------------PowerUps-------------------------------------------------------------------------------------//

	//LaserShot particle -------------------------------------------
	basicLaser.anim.PushBack({ 43,257,16,3 });
	basicLaser.anim.PushBack({ 17,257,24,3 });
	basicLaser.anim.PushBack({ 61,257,32,3 });
	basicLaser.anim.PushBack({ 83,252,40,3 });
	basicLaser.anim.PushBack({ 17,252,64,3 });
	basicLaser.anim.PushBack({ 75,247,48,3 });
	basicLaser.anim.PushBack({ 17,247,56,3 });
	basicLaser.anim.speed = 2.0f;
	basicLaser.life = 2000;

	//LittleRings -------------------------------------------------
	littleRings.anim.PushBack({96,288,4,7});
	littleRings.anim.PushBack({ 102,288,6,15 });
	littleRings.anim.PushBack({ 110,288,11,31 });
	littleRings.anim.speed = 0.5f;
	littleRings.life = 2000;
	littleRings.anim.loop = false;
	littleRings.collision_fx = &littleRingsExplotion;

	littleRingsExplotion.anim.PushBack({149,247,11,31});
	littleRingsExplotion.anim.PushBack({ 162,247,11,31 });
	littleRingsExplotion.anim.PushBack({ 175,247,11,31 });
	littleRingsExplotion.anim.PushBack({ 186,247,11,31 });
	littleRingsExplotion.anim.PushBack({ 197,247,11,31 });
	littleRingsExplotion.anim.speed = 0.2f;

	//BigRings ---------------------------------------------------
	bigRings.anim.PushBack({ 96,288,4,7 });
	bigRings.anim.PushBack({ 102,288,6,15 });
	bigRings.anim.PushBack({ 110,288,11,31 });
	bigRings.anim.PushBack({ 123,288,16,47 });
	bigRings.anim.speed = 0.5f;
	bigRings.life = 2000;
	bigRings.anim.loop = false;
	bigRings.collision_fx = &bigRingsExplotion;

	bigRingsExplotion.anim.PushBack({185,288,16,47});
	bigRingsExplotion.anim.PushBack({ 203,288,17,47 });
	bigRingsExplotion.anim.PushBack({ 222,288,17,47 });
	bigRingsExplotion.anim.PushBack({ 185,337,18,47 });
	bigRingsExplotion.anim.PushBack({ 205,337,18,47 });
	bigRingsExplotion.anim.speed = 0.2f;

	//G Missile particle----------------------------------------

	for (int i = 0; i < 5; ++i) {
		groundMissile.anim.PushBack({ 0,283 + i * 16 ,16,16 });
	}
	groundMissile.anim.speed = 0.2f;

	//H Missle particles----------------------------------------
	hMissile.life = 2000;

	//Basic shot explosion--------------------------------------
	unit_explosion.anim.PushBack({ 244, 263, 16, 16 });
	unit_explosion.anim.PushBack({ 226, 263, 16, 16 });
	unit_explosion.anim.PushBack({ 224, 247, 14, 14 });
	unit_explosion.anim.PushBack({ 210, 263, 14, 14 });
	unit_explosion.anim.PushBack({ 239, 247, 14, 14 });
	unit_explosion.anim.PushBack({ 255, 247, 14, 14 });
	unit_explosion.anim.PushBack({ 208, 247, 14, 14 });
	unit_explosion.anim.loop = false;
	unit_explosion.anim.speed = 0.3f;

	//Death Explosion Particle----------------------------------
	for (int i = 0; i < 5; ++i) {
		death_explosion.anim.PushBack({ 244 + 32 * i ,288, 32,32 });
	}

	death_explosion.anim.speed = 0.2f;
	death_explosion.anim.loop = false;

	//----------------------------------------------------------------------------------GENERAL---------------------------------------------------------------//
	//General explosion 02 particle-----------------------------
	g_explosion02.anim.PushBack({ 0,0,32,32 });
	g_explosion02.anim.PushBack({ 32,0,32,32 });
	g_explosion02.anim.PushBack({ 64,0,16,16 });
	g_explosion02.anim.PushBack({ 80,0,20,20 });
	g_explosion02.anim.PushBack({ 100,0,25,25 });
	g_explosion02.anim.PushBack({ 0,32,26,26 });
	g_explosion02.anim.PushBack({ 26,32,32,32 });
	g_explosion02.anim.PushBack({ 58,32,32,32 });
	g_explosion02.anim.PushBack({ 90,32,32,32 });
	g_explosion02.anim.PushBack({ 0,64,32,32 });
	g_explosion02.anim.PushBack({ 32,64,32,32 });
	g_explosion02.anim.PushBack({ 64,64,32,32 });
	g_explosion02.anim.PushBack({ 96,64,32,32 });
	g_explosion02.anim.PushBack({ 0,96,31,32 });
	g_explosion02.anim.PushBack({ 31,96,30,32 });
	g_explosion02.anim.PushBack({ 61,96,30,32 });
	g_explosion02.anim.loop = false;
	g_explosion02.anim.speed = 0.3f;

	//--------------------------------------------------------------------------------ENEMIES----------------------------------------------------------------------//
	LaserEnemyShot.anim.PushBack({ 52,27,6,32 });
	LaserEnemyShot.anim.PushBack({ 42,27,10,32 });
	LaserEnemyShot.anim.PushBack({ 30,27,12,29 });
	LaserEnemyShot.anim.PushBack({ 22,9,15,16 });
	LaserEnemyShot.anim.PushBack({ 14,43,16,16 });
	LaserEnemyShot.anim.PushBack({ 22,9,15,16 });
	LaserEnemyShot.anim.PushBack({ 14,43,16,16 });
	LaserEnemyShot.anim.PushBack({ 22,9,15,16 });
	LaserEnemyShot.anim.PushBack({ 14,43,16,16 });
	LaserEnemyShot.anim.PushBack({ 22,9,15,16 });
	LaserEnemyShot.anim.PushBack({ 14,43,16,16 });
	LaserEnemyShot.anim.PushBack({ 36,9,16,16 });
	LaserEnemyShot.anim.PushBack({ 0,8,22,16 });
	LaserEnemyShot.anim.PushBack({ 32,0,29,10 });
	LaserEnemyShot.anim.PushBack({ 0,0,32,6 });
	LaserEnemyShot.anim.loop = false;
	LaserEnemyShot.life = 5000;
	LaserEnemyShot.anim.speed = 0.0f;
	

	AsteroidDestroy.anim.PushBack({ 191,142,61,60 });
	AsteroidDestroy.anim.PushBack({ 128,142,63,62 });
	AsteroidDestroy.anim.PushBack({ 64,142,64,64 });
	AsteroidDestroy.anim.PushBack({ 0,142,64,64 });
	AsteroidDestroy.anim.PushBack({ 185,78,64,64 });
	AsteroidDestroy.anim.PushBack({ 123,78,62,64 });
	AsteroidDestroy.anim.PushBack({ 62,78,61,59 });
	AsteroidDestroy.anim.PushBack({ 0,78,62,62 });
	AsteroidDestroy.anim.PushBack({ 178,15,62,63 });
	AsteroidDestroy.anim.PushBack({ 116,15,62,63 });
	AsteroidDestroy.anim.PushBack({ 55,15,61,63 });
	AsteroidDestroy.anim.PushBack({ 0,15,55,63 });
	AsteroidDestroy.anim.speed = 0.2f;

	//Middle Boss shot particle------------------------------------
	MiddleBossShot.anim.PushBack({ 232,248,18,17 });
	MiddleBossShot.anim.PushBack({ 232,267,17,17 });
	MiddleBossShot.anim.PushBack({ 233,285,17,17 });
	MiddleBossShot.anim.PushBack({ 232,303,18,17 });
	MiddleBossShot.anim.PushBack({ 233,320,17,18 });
	MiddleBossShot.anim.PushBack({ 233,320,17,18 });
	MiddleBossShot.anim.PushBack({ 233,339,17,18 });
	MiddleBossShot.anim.PushBack({ 232,358,18,17 });
	MiddleBossShot.anim.PushBack({ 232,377,18,16 });
	MiddleBossShot.anim.speed = 0.2f;
	MiddleBossShot.life = 5000;
	MiddleBossShot.speed.x = 1 * VectorMiddleBossShots.x;
	MiddleBossShot.speed.y = 1 * VectorMiddleBossShots.y;

	//Middle Boss Explosition shot----------------------------------
	MiddleBosExplotion.anim.PushBack({ 0,434,23,24 });
	MiddleBosExplotion.anim.PushBack({ 24,434,23,24 });
	MiddleBosExplotion.anim.PushBack({ 48,434,23,24 });
	MiddleBosExplotion.anim.PushBack({ 72,434,23,24 });
	MiddleBosExplotion.anim.PushBack({ 96,435,24,23 });
	MiddleBosExplotion.anim.PushBack({ 121,434,24,24 });
	MiddleBosExplotion.anim.PushBack({ 145,434,22,25 });
	MiddleBosExplotion.anim.PushBack({ 168,434,22,25 });
	MiddleBosExplotion.anim.PushBack({ 192,434,22,25 });
	MiddleBosExplotion.anim.PushBack({ 214,434,22,25 });
	MiddleBosExplotion.anim.PushBack({ 237,434,22,25 });
	MiddleBosExplotion.anim.speed = 0.2;
	MiddleBossShot.collision_fx = &MiddleBosExplotion;

	//Orange ball
	orangeBallExplosion.anim.PushBack({ 1, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 10, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 19, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 25, 5,  9,  9 });
	orangeBallExplosion.anim.PushBack({ 42, 2, 11, 11 });
	orangeBallExplosion.anim.PushBack({ 54, 1, 13, 13 });
	orangeBallExplosion.anim.PushBack({ 68, 0, 15, 15 });
	orangeBallExplosion.anim.speed = 0.2;
	orangeBallExplosion.anim.loop = false;
	orangeBall.life = 10000;

	orangeBall.anim.PushBack({ 1, 0, 5, 5 });
	orangeBall.anim.PushBack({ 13, 0, 5, 5 });
	orangeBall.anim.PushBack({ 25, 0, 5, 5 });
	orangeBall.anim.PushBack({ 36, 0, 5, 5 });
	orangeBall.anim.speed = 0.2;
	orangeBall.anim.loop = true;
	orangeBall.collision_fx = &orangeBallExplosion;
	orangeBall.life = 10000;

	//Fireball
	fireBall.anim.PushBack({ 1, 287, 64, 32 });
	fireBall.anim.PushBack({ 1, 321, 59, 32 });
	fireBall.anim.PushBack({ 1, 355, 53, 32 });
	fireBall.anim.pingpong = true;
	fireBall.anim.speed = 0.5f;
	fireBall.life = 10000;

	//Missile 
	Missile.anim.PushBack({157,246,15,8});
	Missile.anim.PushBack({ 172,246,13,8 });
	Missile.anim.speed = 0.5f;
	Missile.life = 5000;
	Missile.collision_fx = &MissileExplosion;
	
	MissileExplosion.anim.PushBack({ 157,254,21,19 });
	MissileExplosion.anim.PushBack({ 178,254,27,27 });
	MissileExplosion.anim.PushBack({ 205,254,30,30 });
	MissileExplosion.anim.PushBack({ 235,254,31,32 });
	MissileExplosion.anim.PushBack({ 267,254,28,31 });
	MissileExplosion.anim.PushBack({ 295,254,31,31 });
	MissileExplosion.anim.PushBack({ 326,254,30,31 });
	MissileExplosion.anim.PushBack({ 179,280,31,29 });
	MissileExplosion.anim.PushBack({ 210,281,29,27 });
	MissileExplosion.anim.speed = 0.2f;
}
