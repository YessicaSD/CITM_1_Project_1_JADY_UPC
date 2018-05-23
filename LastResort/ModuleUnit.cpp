#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "Player1.h"
#include "Player2.h"
#include <stdio.h>
#include <math.h>
#include "SDL\include\SDL.h"
#include "Rotation.h"

ModuleUnit::ModuleUnit() //Constructor 
{

	//Push backs
	//- North
	spinAnimation[N].frame[0]   = {  48,  61, 16, 22 };
	spinAnimation[N].frame[1]   = {  32,  61, 16, 22 };
	spinAnimation[N].frame[2]   = {  16,  61, 16, 22 };
	spinAnimation[N].frame[3]   = {   0,  61, 16, 22 };
	spinAnimation[N].frame[4]   = { 226,  38, 16, 22 };
	spinAnimation[N].frame[5]   = { 210,  38, 16, 22 };
	spinAnimation[N].frame[6]   = { 194,  38, 16, 22 };
	spinAnimation[N].frame[7]   = { 178,  38, 16, 22 };
	//- West
	spinAnimation[W].frame[0]   = { 220, 105, 22, 16 };
	spinAnimation[W].frame[1]   = { 198, 105, 22, 16 };
	spinAnimation[W].frame[2]   = { 176, 105, 22, 16 };
	spinAnimation[W].frame[3]   = { 154, 105, 22, 16 };
	spinAnimation[W].frame[4]   = { 132, 105, 22, 16 };
	spinAnimation[W].frame[5]   = { 110, 105, 22, 16 };
	spinAnimation[W].frame[6]   = {  88, 105, 22, 16 };
	spinAnimation[W].frame[7]   = {  66, 105 ,22, 16 };
	//- Eastw
	spinAnimation[E].frame[0]   = { 154,   0, 22, 16 };
	spinAnimation[E].frame[1]   = { 132,   0, 22, 16 };
	spinAnimation[E].frame[2]   = { 110,   0, 22, 16 };
	spinAnimation[E].frame[3]   = {  88,   0, 22, 16 };
	spinAnimation[E].frame[4]   = {  66,   0, 22, 16 };
	spinAnimation[E].frame[5]   = {  44,   0, 22, 16 };
	spinAnimation[E].frame[6]   = {  22,   0, 22, 16 };
	spinAnimation[E].frame[7]   = {   0,   0, 22, 16 };
	//- South
	spinAnimation[S].frame[0]   = { 112, 166, 16, 22 };
	spinAnimation[S].frame[1]   = {  96, 166, 16, 22 };
	spinAnimation[S].frame[2]   = {  80, 166, 16, 22 };
	spinAnimation[S].frame[3]   = {  64, 166, 16, 22 };
	spinAnimation[S].frame[4]   = {  48, 166, 16, 22 };
	spinAnimation[S].frame[5]   = {  32, 166, 16, 22 };
	spinAnimation[S].frame[6]   = {  16, 166, 16, 22 };
	spinAnimation[S].frame[7]   = {   0, 166, 16, 22 };
	//- North east
	spinAnimation[NE].frame[0]  = {  21,  38, 21, 21 };
	spinAnimation[NE].frame[1]  = {   0,  38, 21, 21 };
	spinAnimation[NE].frame[2]  = { 215,  17, 21, 21 };
	spinAnimation[NE].frame[3]  = { 194,  17, 21, 21 };
	spinAnimation[NE].frame[4]  = { 173,  17, 21, 21 };
	spinAnimation[NE].frame[5]  = { 152,  17, 21, 21 };
	spinAnimation[NE].frame[6]  = { 131,  17, 21, 21 };
	spinAnimation[NE].frame[7]  = { 110,  17, 21, 21 };
	//- North west
	spinAnimation[NW].frame[0]  = { 105,  84, 21, 21 };
	spinAnimation[NW].frame[1]  = {  84,  84, 21, 21 };
	spinAnimation[NW].frame[2]  = {  63,  84, 21, 21 };
	spinAnimation[NW].frame[3]  = {  42,  84, 21, 21 };
	spinAnimation[NW].frame[4]  = {  21,  84, 21, 21 };
	spinAnimation[NW].frame[5]  = {   0,  84, 21, 21 };
	spinAnimation[NW].frame[6]  = { 221,  61, 21, 21 };
	spinAnimation[NW].frame[7]  = { 200,  61, 21, 21 };
	//- South east
	spinAnimation[SE].frame[0]  = { 164, 189, 21, 21 };
	spinAnimation[SE].frame[1]  = { 143, 189, 21, 21 };
	spinAnimation[SE].frame[2]  = { 122, 189, 21, 21 };
	spinAnimation[SE].frame[3]  = { 101, 189, 21, 21 };
	spinAnimation[SE].frame[4]  = {  80, 189, 21, 21 };
	spinAnimation[SE].frame[5]  = {  59, 189, 21, 21 };
	spinAnimation[SE].frame[6]  = {  38, 189, 21, 21 };
	spinAnimation[SE].frame[7]  = {  17, 189, 21, 21 };
	//- South west
	spinAnimation[SW].frame[0]  = {  84, 143, 21, 21 };
	spinAnimation[SW].frame[1]  = {  63, 143, 21, 21 };
	spinAnimation[SW].frame[2]  = {  42, 143, 21, 21 };
	spinAnimation[SW].frame[3]  = {  21, 143, 21, 21 };
	spinAnimation[SW].frame[4]  = {   0, 143, 21, 21 };
	spinAnimation[SW].frame[5]  = { 218, 122, 21, 21 };
	spinAnimation[SW].frame[6]  = { 197, 122, 21, 21 };
	spinAnimation[SW].frame[7]  = { 176, 122, 21, 21 };
	//- North north east
	spinAnimation[NNE].frame[0] = { 161,  38, 17, 23 };
	spinAnimation[NNE].frame[1] = { 144,  38, 17, 23 };
	spinAnimation[NNE].frame[2] = { 127,  38, 17, 23 };
	spinAnimation[NNE].frame[3] = { 110,  38, 17, 23 };
	spinAnimation[NNE].frame[4] = {  93,  38, 17, 23 };
	spinAnimation[NNE].frame[5] = {  76,  38, 17, 23 };
	spinAnimation[NNE].frame[6] = {  59,  38, 17, 23 };
	spinAnimation[NNE].frame[7] = {  42,  38, 17, 23 };
	//- North east east
	spinAnimation[ENE].frame[0] = {  88,  17, 22, 17 };
	spinAnimation[ENE].frame[1] = {  66,  17, 22, 17 };
	spinAnimation[ENE].frame[2] = {  44,  17, 22, 17 };
	spinAnimation[ENE].frame[3] = {  22,  17, 22, 17 };
	spinAnimation[ENE].frame[4] = {   0,  17, 22, 17 };
	spinAnimation[ENE].frame[5] = { 220,   0, 22, 17 };
	spinAnimation[ENE].frame[6] = { 198,   0, 22, 17 };
	spinAnimation[ENE].frame[7] = { 176,   0, 22, 17 };
	//- South east east
	spinAnimation[ESE].frame[0] = {  88, 212, 22, 17 };
	spinAnimation[ESE].frame[1] = {  66, 212, 22, 17 };
	spinAnimation[ESE].frame[2] = {  44, 212, 22, 17 };
	spinAnimation[ESE].frame[3] = {  22, 212, 22, 17 };
	spinAnimation[ESE].frame[4] = {   0, 212, 22, 17 };
	spinAnimation[ESE].frame[5] = { 229, 189, 22, 17 };
	spinAnimation[ESE].frame[6] = { 207, 189, 22, 17 };
	spinAnimation[ESE].frame[7] = { 185, 189, 22, 17 };
	//- South south east
	spinAnimation[SSE].frame[0] = {   0, 189, 17, 23 };
	spinAnimation[SSE].frame[1] = { 230, 166, 17, 23 };
	spinAnimation[SSE].frame[2] = { 213, 166, 17, 23 };
	spinAnimation[SSE].frame[3] = { 196, 166, 17, 23 };
	spinAnimation[SSE].frame[4] = { 179, 166, 17, 23 };
	spinAnimation[SSE].frame[5] = { 162, 166, 17, 23 };
	spinAnimation[SSE].frame[6] = { 145, 166, 17, 23 };
	spinAnimation[SSE].frame[7] = { 128, 166, 17, 23 };
	//- South south west
	spinAnimation[SSW].frame[0] = { 224, 143, 17, 23 };
	spinAnimation[SSW].frame[1] = { 207, 143, 17, 23 };
	spinAnimation[SSW].frame[2] = { 190, 143, 17, 23 };
	spinAnimation[SSW].frame[3] = { 173, 143, 17, 23 };
	spinAnimation[SSW].frame[4] = { 156, 143, 17, 23 };
	spinAnimation[SSW].frame[5] = { 139, 143, 17, 23 };
	spinAnimation[SSW].frame[6] = { 122, 143, 17, 23 };
	spinAnimation[SSW].frame[7] = { 105, 143, 17, 23 };
	//- Shouth west west
	spinAnimation[WSW].frame[0] = { 154, 122, 22, 17 };
	spinAnimation[WSW].frame[1] = { 132, 122, 22, 17 };
	spinAnimation[WSW].frame[2] = { 110, 122, 22, 17 };
	spinAnimation[WSW].frame[3] = {  88, 122, 22, 17 };
	spinAnimation[WSW].frame[4] = {  66, 122, 22, 17 };
	spinAnimation[WSW].frame[5] = {  44, 122, 22, 17 };
	spinAnimation[WSW].frame[6] = {  22, 122, 22, 17 };
	spinAnimation[WSW].frame[7] = {   0, 122, 22, 17 };
	//- North west west
	spinAnimation[WNW].frame[0] = {  44, 105, 22, 17 };
	spinAnimation[WNW].frame[1] = {  22, 105, 22, 17 };
	spinAnimation[WNW].frame[2] = {   0, 105, 22, 17 };
	spinAnimation[WNW].frame[3] = { 214,  84, 22, 17 };
	spinAnimation[WNW].frame[4] = { 192,  84, 22, 17 };
	spinAnimation[WNW].frame[5] = { 170,  84, 22, 17 };
	spinAnimation[WNW].frame[6] = { 148,  84, 22, 17 };
	spinAnimation[WNW].frame[7] = { 126,  84, 22, 17 };
	//- North north west
	spinAnimation[NNW].frame[0] = { 183,  61, 17, 23 };
	spinAnimation[NNW].frame[1] = { 166,  61, 17, 23 };
	spinAnimation[NNW].frame[2] = { 149,  61, 17, 23 };
	spinAnimation[NNW].frame[3] = { 132,  61, 17, 23 };
	spinAnimation[NNW].frame[4] = { 115,  61, 17, 23 };
	spinAnimation[NNW].frame[5] = {  98,  61, 17, 23 };
	spinAnimation[NNW].frame[6] = {  81,  61, 17, 23 };
	spinAnimation[NNW].frame[7] = {  64,  61, 17, 23 };
	//- Charge animation
	chargeAnim.PushBack({ 184, 86, 36, 36 });
	chargeAnim.PushBack({ 152, 86, 32, 32 });
	chargeAnim.PushBack({ 120, 86, 32, 32 });
	chargeAnim.PushBack({  92, 86, 28, 28 });
	chargeAnim.PushBack({  64, 86, 28, 28 });
	chargeAnim.PushBack({  32, 86, 32, 32 });
	chargeAnim.PushBack({   0, 86, 32, 32 });
	chargeAnim.PushBack({ 220, 41, 30, 30 });
	chargeAnim.PushBack({ 190, 41, 30, 30 });
	chargeAnim.PushBack({ 162, 41, 28, 27 });
	chargeAnim.PushBack({ 134, 41, 28, 27 });
	chargeAnim.PushBack({  88, 41, 46, 45 });
	chargeAnim.PushBack({  42, 41, 46, 45 });
	chargeAnim.PushBack({   0, 41, 42, 41 });
	chargeAnim.PushBack({ 176,  0, 42, 41 });
	chargeAnim.speed = 0.5f;
	chargeAnim.loop = true;
	//-Throw animation
	throwAnim.PushBack({   0, 0, 22, 22 });
	throwAnim.PushBack({  22, 0, 24, 24 });
	throwAnim.PushBack({  46, 0, 26, 26 });
	throwAnim.PushBack({  72, 0, 24, 24 });
	throwAnim.PushBack({  96, 0, 22, 22 });
	throwAnim.PushBack({ 118, 0, 20, 20 });
	throwAnim.PushBack({ 138, 0, 18, 18 });
	throwAnim.PushBack({ 156, 0, 20, 20 });
	throwAnim.speed = 0.1f;
	throwAnim.loop = true;
}

ModuleUnit::~ModuleUnit()
{

}

bool ModuleUnit::Start()
{
	bool ret = true;
	LOG("Loading unit assets");
	//Load assets
	orangeUnitTx = App->textures->Load("Assets/Unit/OrangeUnitSpritesheet.png");
	blueUnitTx = App->textures->Load("Assets/Unit/BlueUnitSpritesheet.png");
	throwUnitOrangeTx = App->textures->Load("Assets/Unit/OrangeUnitThrow.png");
	throwUnitBlueTx = App->textures->Load("Assets/Unit/BlueUnitThrow.png");
	currentOrbit = currentTurnAround = angleValue[E];
	unitCol = App->collision->AddCollider({ (int)position.x - sphereDiameter/2, (int)position.y - sphereDiameter / 2, sphereDiameter, sphereDiameter}, COLLIDER_UNIT , this);
	hitDetectionUp    = App->collision->AddCollider({ (int)position.x - sphereDiameter / 2, (int)position.y - sphereDiameter / 2 - (int)throwingSpeed, sphereDiameter,    (int)throwingSpeed }, COLLIDER_HIT_DETECTION_WALL, this);
	hitDetectionDown  = App->collision->AddCollider({ (int)position.x - sphereDiameter / 2, (int)position.y + sphereDiameter / 2,                      sphereDiameter,    (int)throwingSpeed }, COLLIDER_HIT_DETECTION_WALL, this);
	hitDetectionLeft  = App->collision->AddCollider({ (int)position.x - sphereDiameter / 2 - (int)throwingSpeed, (int)position.y - sphereDiameter / 2, (int)throwingSpeed, sphereDiameter    }, COLLIDER_HIT_DETECTION_WALL, this);
	hitDetectionRight = App->collision->AddCollider({ (int)position.x + sphereDiameter / 2, (int)position.y - sphereDiameter / 2,                      (int)throwingSpeed, sphereDiameter    }, COLLIDER_HIT_DETECTION_WALL, this);
	//INFO: throwing speed is the width / heigth because we want to snap it if the distance to it is less than what it travels
	return ret;
}

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");
	unitTx = nullptr;
	App->textures->Unload(orangeUnitTx);
	App->textures->Unload(blueUnitTx);
	throwUnitTx = nullptr;
	App->textures->Unload(throwUnitOrangeTx);
	App->textures->Unload(throwUnitBlueTx);
	//If we have created a unit collider, we destroy it
	if (unitCol != nullptr)           { unitCol->type = COLLIDER_TYPE::COLLIDER_NONE; }
	if (hitDetectionUp != nullptr)    { hitDetectionUp->type = COLLIDER_TYPE::COLLIDER_NONE; }
	if (hitDetectionDown != nullptr)  { hitDetectionDown->type = COLLIDER_TYPE::COLLIDER_NONE; }
	if (hitDetectionLeft != nullptr)  { hitDetectionLeft->type = COLLIDER_TYPE::COLLIDER_NONE; }
	if (hitDetectionRight != nullptr) { hitDetectionRight->type = COLLIDER_TYPE::COLLIDER_NONE; }
	//if (unitCol != nullptr)           { unitCol->to_delete = true; }
	//if (hitDetectionUp != nullptr)    { hitDetectionUp->to_delete = true; }
	//if (hitDetectionDown != nullptr)  { hitDetectionDown->to_delete = true; }
	//if (hitDetectionLeft != nullptr)  { hitDetectionLeft->to_delete = true; }
	//if (hitDetectionRight != nullptr) { hitDetectionRight->to_delete = true; }
	return true;
}

update_status ModuleUnit::Update()
{
	switch (unitPhase)
	{
	case UnitPhase::rotating:
		Rotating();
		break;
	case UnitPhase::throwing:
		Throwing();
		break;
	case UnitPhase::followingTerrain:
		FollowingTerrain();
		break;
	case UnitPhase::bouncingOnTerrain:
		BouncingOnTerrain();
		break;
	case UnitPhase::returning:
		Returning();
		break;
	case UnitPhase::positioning:
		Positioning();
		break;
	}

	return UPDATE_CONTINUE;
}

void ModuleUnit::Rotating()
{
	//Initial set up--------------------------------------------------------------------------------------
	//- We update our orbiting bool to false, if any key is pressed and the unit is not locked it will go to true
	//- We update our turningAround bool to false, if the player is moving, if any key is pressed it will go to ture
	orbiting = false;
	turningAround = false;

	//Conditions for movement-----------------------------------------------------------------------------
	if (playerToFollow->MoveLeft() == true)
	{
		orbiting = true;
		turningAround = true;
		//- The unit goes to the right (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[E];
	}
	if (playerToFollow->MoveRight() == true)
	{
		orbiting = true;
		turningAround = true;
		//- The unit goes to the left (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[W];
	}
	if (playerToFollow->MoveUp() == true)
	{
		orbiting = true;
		turningAround = true;
		//- The unit moves down (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[S];
		//- We check if a part from going down, it's also going to one of the sides (for the diagonals)
		if (playerToFollow->MoveLeft() == true) { targetOrbit -= PI / 4; }
		if (playerToFollow->MoveRight() == true) { targetOrbit += PI / 4; }
	}
	if (playerToFollow->MoveDown() == true)
	{
		orbiting = true;
		turningAround = true;
		//- The unit goes up (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[N];
		//- We check if a part from going up, it's also going to one of the sides (for the diagonals)
		if (playerToFollow->MoveLeft() == true) { targetOrbit += PI / 4; }
		if (playerToFollow->MoveRight() == true) { targetOrbit -= PI / 4; }
	}

	//If the ball is locked it won't rotate around the player ship
	if (playerToFollow->unitLocked == true) { orbiting = false; }

	//Move the orbit to the target rotation---------------------------------------------------------------
	//- Orbit around the player
	if (orbiting == true) { RotateTo(targetOrbit, currentOrbit, orbitSpeed); }
	//- Rotation of the unit itself
	if (turningAround == true) { RotateTo(targetOrbit, currentTurnAround, turnAroundSpeed); }

	//Limit the rotation----------------------------------------------------------------------------------
	//- On the orbit
	if (orbiting == true) { LimitRotation(currentOrbit); }
	//- On the spin
	if (turningAround == true) { LimitRotation(currentTurnAround); }

	//- We grab the spin we need to render--------------------------------------------------------------------
	turnAroundToRender = GetNearestAngle(currentTurnAround);

	//Set the position----------------------------------------------------------------------------------------
	position.x = radius * cosf(currentOrbit) + playerToFollow->position.x + playerToFollow->playerCenter.x;
	position.y = radius * sinf(currentOrbit) + playerToFollow->position.y + playerToFollow->playerCenter.y;

	//Update the collider position (after having set its position)--------------------------------------------
	UpdateUnitColliders();

	//Increase the animation current frame--------------------------------------------------------------------
	currentSpinFrame += spinSpeed;

	//- Limit the animation frames
	if (currentSpinFrame >= SPIN_FRAMES) { currentSpinFrame = 0; }

	//Set the rotation and render (all in the same place)-----------------------------------------------------
	App->render->Blit(
		unitTx,
		(int)position.x - spriteXDifferences[turnAroundToRender],
		(int)position.y - spriteYDifferences[turnAroundToRender],
		&spinAnimation[turnAroundToRender].frame[(int)currentSpinFrame]);

	//Shoot---------------------------------------------------------------------------------------------------
	if (playerToFollow->Shoot() == true)
	{
		App->particles->AddParticle(
			App->particles->unitShot,
			{ (int)position.x + shotPosXDifferences[turnAroundToRender], (int)position.y + shotPosYDifferences[turnAroundToRender]},
			{ (int)(unitProjectileSpeed * cosf(angleValue[turnAroundToRender])) , (int)(unitProjectileSpeed * sinf(angleValue[turnAroundToRender]))},
			playerToFollow->PlayerTexture,
			playerToFollow->shot_colType,
			0);
	}

	//Check if the player is charging---------------------------------------------------------------------
	if (playerToFollow->Charge())
	{
		//We increase the power if the player is mantaining the button pressed
		power += powerSpeed;
		//We make sure the power doesn't get above 1
		if (power > 1) { power = 1; }
	}

	if(power > 0.1)
	{
		//Play the charging animation
		chargeFrame = chargeAnim.GetCurrentFrame();
		App->render->Blit(
			throwUnitTx,
			(int)position.x - chargeXOffset[(int)chargeAnim.current_frame],
			(int)position.y - chargeYOffset[(int)chargeAnim.current_frame],
			&chargeFrame);
	}

	if (playerToFollow->ReleaseCharge())
	{
		if (power > 0.3f)//0.3 minimum limit at which the game considers the unit to be charged
		{
			//Throw
			unitPhase = UnitPhase::throwing;
			throwSpeed.x = cosf(currentOrbit) * throwingSpeed;
			throwSpeed.y = sinf(currentOrbit) * throwingSpeed;
			unitCol->SetDamage(12);
			shootTime = SDL_GetTicks();
		}
		//If the player releases the button, we set the power to 0
		power = 0;
	}
}

void ModuleUnit::Throwing()
{
	//Logic-------------------------------------------------------------------
	position.x += throwSpeed.x;
	position.y += throwSpeed.y;
	UpdateUnitColliders();
	//- Check return conditions-----------------------------------------------
	CheckOutOfScreen();
	CheckReturnTime();

	//Render------------------------------------------------------------------
	throwFrame = throwAnim.GetCurrentFrame();
	App->render->Blit(
		throwUnitTx,
		(int)position.x - throwFrame.w / 2,
		(int)position.y - throwFrame.h / 2,
		&throwFrame);
}

void ModuleUnit::FollowingTerrain()
{
	//Logic-------------------------------------------------------------------
	switch (followTerrainDir)
	{
	case FTD_up:
		//Set the position
		position.y -= followTerrainSpeed;
		if (ColliderIsOnRight()) { position.x = colliderToFollow->rect.x - sphereDiameter / 2; }
		else if (ColliderIsOnLeft()) { position.x = colliderToFollow->rect.x + colliderToFollow->rect.w + sphereDiameter / 2; }
		//Check if it runs out of collider
		if (position.y + sphereDiameter / 2 < colliderToFollow->rect.y)
		{
			if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
		}
		break;
	case FTD_down:
		//Set the position
		position.y += followTerrainSpeed;
		if (ColliderIsOnRight()) { position.x = colliderToFollow->rect.x - sphereDiameter / 2; }
		else if (ColliderIsOnLeft()) { position.x = colliderToFollow->rect.x + colliderToFollow->rect.w + sphereDiameter / 2; }
		//Check if it runs out of collider
		if (position.y - sphereDiameter / 2 > colliderToFollow->rect.y + colliderToFollow->rect.h)
		{
			if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnLeft()) { followTerrainDir = FollowingTerrainDirection::FTD_left; }
		}
		break;
	case FTD_left:
		//Set the position
		position.x -= followTerrainSpeed;
		if (ColliderIsAbove()) { position.y = colliderToFollow->rect.y + colliderToFollow->rect.h + sphereDiameter / 2; }
		else if (ColliderIsBellow()) { position.y = colliderToFollow->rect.y - sphereDiameter / 2; }
		//Check if it runs out of collider
		if (position.x + sphereDiameter / 2 < colliderToFollow->rect.x)
		{
			if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
		}
		break;
	case FTD_right:
		//Set the position
		position.x += followTerrainSpeed;
		if (ColliderIsAbove()) { position.y = colliderToFollow->rect.y + colliderToFollow->rect.h + sphereDiameter / 2; }
		else if (ColliderIsBellow()) { position.y = colliderToFollow->rect.y - sphereDiameter / 2; }
		//Check if it runs out of collider
		if (position.x - sphereDiameter / 2 > colliderToFollow->rect.x + colliderToFollow->rect.w)
		{
			if (ColliderIsAbove()) { followTerrainDir = FollowingTerrainDirection::FTD_up; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_down; }
		}
		break;
	}
	UpdateUnitColliders();

	//- Check return conditions-----------------------------------------------
	CheckPlayerClose();
	CheckOutOfScreen();
	CheckReturnTime();

	//Render------------------------------------------------------------------
	throwFrame = throwAnim.GetCurrentFrame();
	App->render->Blit(
		throwUnitTx,
		(int)position.x - throwFrame.w / 2,
		(int)position.y - throwFrame.h / 2,
		&throwFrame);
}

void ModuleUnit::BouncingOnTerrain()
{
	//Logic-------------------------------------------------------------------
	position.x += throwSpeed.x;
	position.y += throwSpeed.y;
	UpdateUnitColliders();
	//- Check return conditions-----------------------------------------------
	CheckPlayerClose();
	CheckOutOfScreen();
	CheckReturnTime();

	//Render------------------------------------------------------------------
	throwFrame = throwAnim.GetCurrentFrame();
	App->render->Blit(
		throwUnitTx,
		(int)position.x - throwFrame.w / 2,
		(int)position.y - throwFrame.h / 2,
		&throwFrame);
}


void ModuleUnit::Returning()
{
	//MOVEMENT----------------------------------------------------------------
	//- We calculate the unit vector from the position to the target
	fPoint vectorIncrease;
	fPoint floatPlayerPos;
	floatPlayerPos.x = (float)playerToFollow->position.x + playerToFollow->playerCenter.x;
	floatPlayerPos.y = (float)playerToFollow->position.y + playerToFollow->playerCenter.y;
	vectorIncrease.UnitVector(floatPlayerPos, position);
	
	//- If the unit has reached the center of the player, we slowly position it on the position it was when we shot it
	if (sqrt(pow(position.x - floatPlayerPos.x, 2) + pow(position.y - floatPlayerPos.y, 2)) >= returningSpeed)
	{
		//- We add that vector to the position of the orbit
		//position.x = playerToFollow->position.x + vectorIncrease * positioningStep;
		position.x += vectorIncrease.x * returningSpeed;
		position.y += vectorIncrease.y * returningSpeed;
		UpdateUnitColliders();
	}
	else
	{
		//- We go to position the unit around the player ship again
		position.x = floatPlayerPos.x;
		position.y = floatPlayerPos.y;
		radius = 0;
		unitPhase = UnitPhase::positioning;
	}

	//RENDER------------------------------------------------------------------
	throwFrame = throwAnim.GetCurrentFrame();
	App->render->Blit(
		throwUnitTx,
		(int)position.x - throwFrame.w / 2,
		(int)position.y - throwFrame.h / 2,
		&throwFrame);
}

void ModuleUnit::Positioning()
{
	//When it's positioning, it is already rotating, but at the same time it travels to the correct distance from the center of the player
	radius += 2;
	if(radius >= 31)
	{
		radius = 31;
		unitCol->SetDamage(1);
		unitPhase = UnitPhase::rotating;
	}
	Rotating();
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{
	switch(unitPhase)
	{
	//case UnitPhase::rotating:
	//	Simply does damage, no need to write anything
	//	break;
	case UnitPhase::throwing:
		OnCollisionThrowing(collider1, collider2);
		break;
	case UnitPhase::followingTerrain:
		OnCollisionFollowingTerrain(collider1, collider2);
		break;
	case UnitPhase::bouncingOnTerrain:
		OnCollisionBouncingOnTerrain(collider1, collider2);
		break;
	//case UnitPhase::returning:
	//	Simply does damage, no need to write anything
	//	break;
	//case UnitPhase::positioning:
	//	Simply does damage, no need to write anything
	//	break;
	}
}

void ModuleUnit::OnCollisionThrowing(Collider* collider1, Collider* collider2)
{
	if(unitTx == orangeUnitTx)
	{
		if (collider1 == hitDetectionUp)
		{
			unitPhase = UnitPhase::followingTerrain;
			followTerrainDir = FollowingTerrainDirection::FTD_right;
			colliderToFollow = collider2;
		}
		if (collider1 == hitDetectionLeft)
		{
			unitPhase = UnitPhase::followingTerrain;
			followTerrainDir = FollowingTerrainDirection::FTD_down;
			colliderToFollow = collider2;
		}
		if (collider1 == hitDetectionDown)
		{
			unitPhase = UnitPhase::followingTerrain;
			followTerrainDir = FollowingTerrainDirection::FTD_right;
			colliderToFollow = collider2;
		}
		if (collider1 == hitDetectionRight)
		{
			unitPhase = UnitPhase::followingTerrain;
			followTerrainDir = FollowingTerrainDirection::FTD_down;
			colliderToFollow = collider2;
		}
	}
	else if (unitTx == blueUnitTx)
	{
		if (collider1 == hitDetectionUp)
		{
			unitPhase = UnitPhase::bouncingOnTerrain;
			throwSpeed.y = -throwSpeed.y;
		}
		if (collider1 == hitDetectionLeft)
		{
			unitPhase = UnitPhase::bouncingOnTerrain;
			throwSpeed.x = -throwSpeed.x;
		}
		if (collider1 == hitDetectionDown)
		{
			unitPhase = UnitPhase::bouncingOnTerrain;
			throwSpeed.y = -throwSpeed.y;
		}
		if (collider1 == hitDetectionRight)
		{
			unitPhase = UnitPhase::bouncingOnTerrain;
			throwSpeed.x = -throwSpeed.x;
		}
	}

	CheckHitHeavyEnemy(collider1, collider2);
}

void ModuleUnit::OnCollisionFollowingTerrain(Collider* collider1, Collider* collider2)
{
	if (collider1 == hitDetectionUp)
	{
		//If it was moving up
		if (followTerrainDir == FollowingTerrainDirection::FTD_up && collider2 != colliderToFollow)
		{
			if      (ColliderIsOnLeft())  { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_left;  }
			colliderToFollow = collider2;
		}
	}
	if (collider1 == hitDetectionLeft)
	{
		//If it was moving left
		if (followTerrainDir == FollowingTerrainDirection::FTD_left && collider2 != colliderToFollow)
		{
			if      (ColliderIsAbove())  { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_up;   }
			colliderToFollow = collider2;
		}
	}
	if (collider1 == hitDetectionDown)
	{
		//If it was moving down
		if (followTerrainDir == FollowingTerrainDirection::FTD_down && collider2 != colliderToFollow)
		{
			if      (ColliderIsOnLeft())  { followTerrainDir = FollowingTerrainDirection::FTD_right; }
			else if (ColliderIsOnRight()) { followTerrainDir = FollowingTerrainDirection::FTD_left;  }
			colliderToFollow = collider2;
		}
	}
	if (collider1 == hitDetectionRight)
	{
		//If it was moving right
		if (followTerrainDir == FollowingTerrainDirection::FTD_right && collider2 != colliderToFollow)
		{
			if      (ColliderIsAbove())  { followTerrainDir = FollowingTerrainDirection::FTD_down; }
			else if (ColliderIsBellow()) { followTerrainDir = FollowingTerrainDirection::FTD_up;   }
			colliderToFollow = collider2;
		}
	}

	CheckHitHeavyEnemy(collider1, collider2);
}

void ModuleUnit::OnCollisionBouncingOnTerrain(Collider* collider1, Collider* collider2)
{
	if (collider1 == hitDetectionUp)
	{
		//If it was moving up
		if(throwSpeed.y < 0)
		{
			throwSpeed.y = -throwSpeed.y;
		}
	}
	else if (collider1 == hitDetectionLeft)
	{
		//If it was moving left
		if (throwSpeed.x < 0)
		{
			throwSpeed.x = -throwSpeed.x;
		}
	}
	else if (collider1 == hitDetectionDown)
	{
		//If it was moving down
		if (throwSpeed.y > 0)
		{
			throwSpeed.y = -throwSpeed.y;
		}
	}
	else if (collider1 == hitDetectionRight)
	{
		//If it was moving right
		if (throwSpeed.x > 0)
		{
			throwSpeed.x = -throwSpeed.x;
		}
	}

	CheckHitHeavyEnemy(collider1, collider2);
}

void ModuleUnit::MakeUnitBlue()
{
	unitTx = blueUnitTx;
	throwUnitTx = throwUnitBlueTx;
}

void ModuleUnit::MakeUnitOrange()
{
	unitTx = orangeUnitTx;
	throwUnitTx = throwUnitOrangeTx;
}

void ModuleUnit::UpdateUnitColliders()
{
	unitCol->SetPos((int)position.x - 8, (int)position.y - 8);
	hitDetectionUp   ->SetPos((int)position.x - sphereDiameter / 2, (int)position.y - sphereDiameter / 2 - (int)throwingSpeed);
	hitDetectionDown ->SetPos((int)position.x - sphereDiameter / 2, (int)position.y + sphereDiameter / 2);
	hitDetectionLeft ->SetPos((int)position.x - sphereDiameter / 2 - (int)throwingSpeed, (int)position.y - sphereDiameter / 2);
	hitDetectionRight->SetPos((int)position.x + sphereDiameter / 2, (int)position.y - sphereDiameter / 2);
}

bool ModuleUnit::ColliderIsOnLeft()
{
	return (colliderToFollow->rect.x + colliderToFollow->rect.w < position.x);
}

bool ModuleUnit::ColliderIsOnRight()
{
	return (colliderToFollow->rect.x > position.x);
}

bool ModuleUnit::ColliderIsAbove()
{
	return (colliderToFollow->rect.y + colliderToFollow->rect.h < position.y);
}

bool ModuleUnit::ColliderIsBellow()
{
	return (colliderToFollow->rect.y > position.y);
}

void ModuleUnit::CheckOutOfScreen()
{
	if(position.x < 0 - returnMargin ||
		position.x > 0 + SCREEN_WIDTH + returnMargin ||
		position.y < 0 - returnMargin ||
		position.y > 0 + SCREEN_HEIGHT + returnMargin
		)
	{
		unitPhase = UnitPhase::returning;
	}
}

void ModuleUnit::CheckReturnTime()
{
	//If it remains on the screen for more than 10 seconds it's problably bugged in a collider and it should return to the player
	if (SDL_GetTicks() > shootTime + 10000)
	{
		LOG("The unit has been on the screen for too much time and it's probably bugged, returning it to the player.")
		unitPhase = UnitPhase::returning;
	}
}

void ModuleUnit::CheckPlayerClose()
{
	if(sqrt(pow(position.x - playerToFollow->position.x + playerToFollow->playerCenter.x, 2) + pow(position.y - playerToFollow->position.y + playerToFollow->playerCenter.y, 2)) < 20)//20 = distance to return
	{
		unitPhase = UnitPhase::returning;
	}
}

void ModuleUnit::CheckHitHeavyEnemy(Collider* collider1, Collider* collider2)
{
	if (collider1->type == COLLIDER_TYPE::COLLIDER_UNIT && collider2->type == COLLIDER_ENEMY_HEAVY)
	{
		unitPhase = UnitPhase::returning;
	}
}
