#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h" 
#include "p2Point.h"
#include "ModulePowerups.h"

#define HORIZONTAL_MARGIN 16
#define VERTICAL_MARGIN 2


struct SDL_Texture;
struct Collider; //SHOT
class Particle;
struct Sfx;

enum ShipFrames
{
	MaxUp,
	TransitionUp,
	Idle,
	TransitionDown,
	MaxDown
};

enum PlayerAnimationState
{
	Initial,
	Movement,
	Death,
	None
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status InputUpdate();
	update_status LogicUpdate();
	update_status RenderUpdate2();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	//Added-----------------------------
	void Reappear();
	void MovementLogic(); 
	void ShootingLogic();  
	void ShipAnimation();

	//Functions that will be rewritten in each player
	virtual bool MoveUp() = 0;
	virtual bool MoveDown() = 0;
	virtual bool MoveLeft() = 0;
	virtual bool MoveRight() = 0;
	virtual bool Shoot() = 0;
	virtual bool Charge() = 0;
	virtual bool ReleaseCharge() = 0;
	virtual bool Lock() = 0;
	virtual void PlayerDies() = 0;
	virtual void KillUnit() = 0;

public:
	//Player Data------------------------------------------------------------//
	//--------Gameplay------------------------------
	int lives = 2;
	int score = 0;
	//--------Movment-------------------------------
	iPoint position;
	iPoint initPosition;
	float movementSpeed = 2;
	//--------States--------------------------------
	bool isActive = false; //If you can play with this ship
	bool isAppearing;
	bool isInvincible = false;
	bool isDying;
	bool canMove;
	bool shoot = false;
	bool shootLaser = false;
	int LaserCount = 0;
	
	//--------PowerUps-----------------------------
	POWERUP_TYPE currentPowerUp = POWERUP_TYPE::NOPOWERUP;
	int powerupUpgrades = 0;
	bool unitPowerUp = false;
	bool speedPowerup = false;
	bool despeed_Powerup = false;
	int gCounter = 0;
	int hCounter = 0;
	//------------States----------------------------
	PlayerAnimationState playerAnimState;
	Animation initAnim;
	Animation shipAnim;
	Animation shipAnimBlack;
	Animation deathAnim;
	//------------PowerUps--------------------------
	Animation ShotLaserBasic;
	Animation SpeedAnimation;
	Animation Despeed_Animation;
	iPoint ShotPosition;
	//------------Basic----------------------------
	SDL_Rect *current_animation = nullptr; //pointer to the only one animation 
	Animation shotFire;                    //Animation infront of ship when we are shooting basic shots
	//------------Variables-------------------------
	int const playerwidth = 32;
	int const playerheight = 12;
	int invincibilityFrames;
	float yAxis = 0;//This value will control the animation of the ship. It will increase up to 1 when S is pressed and it will decrease up to -1 when W is pressed. When none of those keys are pressed, it will progressively go back to 0.
	const float keyPressSpeed = 0.05f;//The speed at which the ship will change its frame when the key is pressed
	const float keyReleaseSpeed = 0.05f;//The speed at which the ship goes basck to the idle frame when the key is release
	int currentFrame;//The frame we'll render. It will take a value from the ShipFrames enumerator
	float const transitionLimit = 0.5f;//This indicates when the ship will transition from its idle animation to its transition animation
	float const MaxLimit = 0.90f;//This indicates when the ship will transition from its transition animation to its max animation
	iPoint playerCenter = { 16, 6 };//Useful to make the unit rotate around the center of the player

	//Colliders---------------------------------------------------------------//
	Collider* playerCol = nullptr;
	COLLIDER_TYPE shot_colType;

	//Win variables
	bool winlvl=false;
	bool winlvlsingle=false;
	int numLvlwin;
	void Winlvl();
	void WinlvlSingle();
	virtual void Winposition()=0; 
	bool start_timer;

	int FadeToBlackAlfa;
	SDL_Rect backgroundBlack;
};

#endif