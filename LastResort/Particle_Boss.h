#ifndef __PARTICLE_BOSS_H__
#define __PARTICLE_BOSS_H__

#include "Particle.h"
#include "MovPath.h"



struct Laser {
	fPoint position = {0.0f, 0.0f};
	Collider *collider = nullptr;
	Animation animation;

};

class ModulePlayer;

class Particle_Boss : public Particle
{
public:
	enum ParticleDirection {
		N = 0,
		NE = 1,
		E = 2,
		SE = 3,
		S = 4,
		SW = 5,
		W = 6,
		NW = 7,
		MAX_DIR = 8
	};

	int frames = 0;
	bool addedColliders = false;
	bool addedLaserCol= false;
	bool deletedLaserCol = false;
	Laser lasers[MAX_DIR - 1];
	fPoint linearOffset = { 18.0f,18.0f };
	fPoint diagonalOffset = { 12.0f,12.0f };
	fPoint laserPos;
	float laserWeight = 0;
	fPoint laserPosTex1 = { 333,0,};
	fPoint laserPosTex2 = { 418,0 };
	Animation originAnim;
	Animation finalAnim;

	Animation diagonalLaserRAnim;
	Animation diagonalLaserLAnim;
	Animation linearLaserXAnim;
	Animation linearLaserYAnim;

public:

	Particle_Boss(fPoint position, SDL_Texture* tex);
	~Particle_Boss();

	void Move();
	void Draw();

	void AddColliders();

};

#endif // __PARTICLE_BOSS_H__


