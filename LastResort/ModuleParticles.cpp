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
#include "ModuleStage05.h"
#include "SDL/include/SDL_timer.h"
#include "Particle_OrangeBall.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
	//PLAYER-----------------------------------------------------------------//
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
	basicShot.speed.x = 12;
	basicShot.speed.y = 0;
	basicShot.anim.loop = false;
	basicShot.collision_fx = &basic_explosion;

	//Basic shot particle---------------------------------------
	unitShot.anim.PushBack({ 155, 288, 13, 13});
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

	//LaserShot particle 
	Basic_Laser.anim.PushBack({ 43,257,16,3 });
	Basic_Laser.anim.PushBack({ 17,257,24,3 });
	Basic_Laser.anim.PushBack({ 61,257,32,3 });
	Basic_Laser.anim.PushBack({ 83,252,40,3 });
	Basic_Laser.anim.PushBack({ 17,252,64,3 });
	Basic_Laser.anim.PushBack({ 75,247,48,3 });
	Basic_Laser.anim.PushBack({ 17,247,56,3 });
	Basic_Laser.anim.speed = 2.0f;
	Basic_Laser.life = 2000;
	Basic_Laser.speed.x = 10;

	//Middle Boss shot particle------------------------------------
	MiddleBossShot.anim.PushBack({232,248,18,17});
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
	MiddleBossShot.speed.x = 1*VectorMiddleBossShots.x;
	MiddleBossShot.speed.y = 1*VectorMiddleBossShots.y;

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

	//Basic shot explosion--------------------------------------
	unit_explosion.anim.PushBack({ 244, 263, 16, 16});
	unit_explosion.anim.PushBack({ 226, 263, 16, 16});
	unit_explosion.anim.PushBack({ 224, 247, 14, 14});
	unit_explosion.anim.PushBack({ 210, 263, 14, 14});
	unit_explosion.anim.PushBack({ 239, 247, 14, 14});
	unit_explosion.anim.PushBack({ 255, 247, 14, 14});
	unit_explosion.anim.PushBack({ 208, 247, 14, 14});
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
	LaserEnemyShot.anim.PushBack({ 42,27,10,29 });
	LaserEnemyShot.anim.PushBack({ 30,27,10,29 });
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
	LaserEnemyShot.speed.y = 3;
	LaserEnemyShot.speed.x = 3;

	AsteroidDestroy.anim.PushBack({191,142,61,60});
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

	MiddleAsteroidDestroy.anim.PushBack({0,206,24,40});
	MiddleAsteroidDestroy.anim.PushBack({ 24,206,32,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 56,206,39,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 95,206,39,40 });
	MiddleAsteroidDestroy.anim.PushBack({133,206,39,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 172,206,39,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 211,206,40,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 0,246,40,40 });
	MiddleAsteroidDestroy.anim.PushBack({ 80,246,39,39 });
	MiddleAsteroidDestroy.anim.PushBack({ 119,246,38,38 });
	MiddleAsteroidDestroy.anim.speed = 0.2f;
	
	orangeBall.anim.PushBack({  1, 0, 5, 5 });
	orangeBall.anim.PushBack({ 13, 0, 5, 5 });
	orangeBall.anim.PushBack({ 25, 0, 5, 5 });
	orangeBall.anim.PushBack({ 36, 0, 5, 5 });
	orangeBall.anim.speed = 0.2;
	orangeBall.anim.loop = true;
	unitShot.collision_fx = &orangeBallExplosion;
	orangeBall.life = 2000;
	//Declare the speed to be what you want just before AddParticle

	orangeBallExplosion.anim.PushBack({  1, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 10, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 19, 6,  8,  8 });
	orangeBallExplosion.anim.PushBack({ 25, 5,  9,  9 });
	orangeBallExplosion.anim.PushBack({ 42, 2, 11, 11 });
	orangeBallExplosion.anim.PushBack({ 54, 1, 13, 13 });
	orangeBallExplosion.anim.PushBack({ 68, 0, 15, 15 });
	orangeBallExplosion.anim.speed = 0.2;
	orangeBallExplosion.anim.loop = false;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading ModuleParticles assets ");
	//Load textures
	ParticleTexture= App->textures->Load("Assets/particles.png");
	graphics = App->textures->Load("Assets/General/Fx/Explosion_2.png");
	LaserTex = App->textures->Load("Assets/General/Enemies/Laser_Niv5.png");
	//particles-----------------------------------------------
	g_explosion02.texture = graphics;
	//Powerups ---------------------------------------------------------------------
	Basic_LaserFx = App->audio->LoadSFX("Assets/014. Lasser_2-Center.WAV");
	Basic_Laser.sfx = Basic_LaserFx;
	//audios--------------------------------------------------
	basic_shot_sfx = App->audio->LoadSFX("Assets/004. Shot - center.wav");
	basicShot.sfx = basic_shot_sfx;
	death_sfx = App->audio->LoadSFX("Assets/005. Death.wav");
	death_explosion.sfx = death_sfx;
	g_explosion01_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_1.wav");
	g_explosion02_1sfx = App->audio->LoadSFX("Assets/General/Fx/Explosion_2.wav");
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	
	//textures--------------------------------------------------
	App->textures->Unload(graphics);
	App->textures->Unload(LaserTex);
	App->textures->Unload(ParticleTexture);
	//audios---------------------------------------------------
	App->audio->UnloadSFX(basic_shot_sfx);
	App->audio->UnloadSFX(death_sfx);
	App->audio->UnloadSFX(Basic_LaserFx);
	App->audio->UnloadSFX(g_explosion01_1sfx);
	App->audio->UnloadSFX(g_explosion02_1sfx);
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
		Particle* p = active[i];

		if (p == nullptr)
		{
			continue;
		}	

		if (p->UpdateParticle() == false)
		{
			delete p;
			active[i] = nullptr;
		}

		else if (SDL_GetTicks() >= p->born)
		{
			p->Draw();
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle( Particle& sentParticle, int x, int y, SDL_Texture *tex,  COLLIDER_TYPE collider_type, Uint32 delay, PARTICLE_TYPE particle_type)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle * p;
			switch(particle_type)
			{
			case PARTICLE_REGULAR:
				p = new Particle(sentParticle);
				AssociateParticleValues(p, sentParticle, x, y, tex, collider_type, delay, particle_type);
				active[i] = p;
				break;
			case PARTICLE_LASER:
				p = new Particle_Laser(sentParticle);
				AssociateParticleValues(p, sentParticle, x, y, tex, collider_type, delay, particle_type);
				active[i] = p;
				break;
			case PARTICLE_ORANGE_BALL:
				p = new Particle_OrangeBall(sentParticle);
				AssociateParticleValues(p, sentParticle, x, y, tex, collider_type, delay, particle_type);
				active[i] = p;
			}			
		}
	}
}

void ModuleParticles::AssociateParticleValues(Particle* newParticle, Particle& sentParticle, int x, int y, SDL_Texture *tex, COLLIDER_TYPE collider_type, Uint32 delay, PARTICLE_TYPE particle_type)
{
	SDL_Rect currentFrame = newParticle->anim.GetCurrentFrame();
	newParticle->born = SDL_GetTicks() + delay;
	newParticle->position.x = x;
	newParticle->position.y = y;
	newParticle->fixedPos.x = x - App->stage05->spawnPos.x;
	newParticle->fixedPos.y = y - App->stage05->spawnPos.y;
	newParticle->texture = tex;
	if (sentParticle.collision_fx != nullptr) { newParticle->collision_fx = sentParticle.collision_fx; }
	if (sentParticle.sfx != nullptr) { App->audio->ControlSFX(sentParticle.sfx, PLAY_AUDIO); }
	if (collider_type != COLLIDER_NONE) { newParticle->collider = App->collision->AddCollider({ newParticle->position.x, newParticle->position.y ,currentFrame.w, currentFrame.h }, collider_type, this); }
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (active[i]->collision_fx != nullptr)
				AddParticle(*active[i]->collision_fx, active[i]->position.x, active[i]->position.y, active[i]->texture);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
