#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Player1.h"
#include <stdio.h>
#include <math.h>
#include "SDL\include\SDL.h"

ModuleUnit::ModuleUnit() //Constructor 
{
	//Define the angle values
	angleValue[E] = 2 * PI;
	angleValue[ESE] = PI / 8;
	angleValue[SE] = PI / 4;
	angleValue[SSE] = 3 * PI / 8;
	angleValue[S] = PI / 2;
	angleValue[SSW] = 5 * PI / 8;
	angleValue[SW] = 3 * PI / 4;
	angleValue[WSW] = 7 * PI / 8;
	angleValue[W] = PI;
	angleValue[WNW] = 9 * PI / 8;
	angleValue[NW] = 5 * PI / 4;
	angleValue[NNW] = 11 * PI / 8;
	angleValue[N] = 3 * PI / 2;
	angleValue[NNE] = 13 * PI / 8;
	angleValue[NE] = 7 * PI / 4;
	angleValue[ENE] = 15 * PI / 8;
	//Push backs
	//- North
	spinAnimation[N].frame[0] = {  48, 61, 16, 22 };
	spinAnimation[N].frame[1] = {  32, 61, 16, 22 };
	spinAnimation[N].frame[2] = {  16, 61, 16, 22 };
	spinAnimation[N].frame[3] = {   0, 61, 16, 22 };
	spinAnimation[N].frame[4] = { 226, 38, 16, 22 };
	spinAnimation[N].frame[5] = { 210, 38, 16, 22 };
	spinAnimation[N].frame[6] = { 194, 38, 16, 22 };
	spinAnimation[N].frame[7] = { 178, 38, 16, 22 };
	//- West
	spinAnimation[W].frame[0] = { 220, 105, 22, 16 };
	spinAnimation[W].frame[1] = { 198, 105, 22, 16 };
	spinAnimation[W].frame[2] = { 176, 105, 22, 16 };
	spinAnimation[W].frame[3] = { 154, 105, 22, 16 };
	spinAnimation[W].frame[4] = { 132, 105, 22, 16 };
	spinAnimation[W].frame[5] = { 110, 105, 22, 16 };
	spinAnimation[W].frame[6] = {  88, 105, 22, 16 };
	spinAnimation[W].frame[7] = {  66, 105 ,22, 16 };
	//- East
	spinAnimation[E].frame[0] = { 154, 0, 22, 16 };
	spinAnimation[E].frame[1] = { 132, 0, 22, 16 };
	spinAnimation[E].frame[2] = { 110, 0, 22, 16 };
	spinAnimation[E].frame[3] = {  88, 0, 22, 16 };
	spinAnimation[E].frame[4] = {  66, 0, 22, 16 };
	spinAnimation[E].frame[5] = {  44, 0, 22, 16 };
	spinAnimation[E].frame[6] = {  22, 0, 22, 16 };
	spinAnimation[E].frame[7] = {   0, 0, 22, 16 };
	//- South
	spinAnimation[S].frame[0] = { 112, 166, 16, 22 };
	spinAnimation[S].frame[1] = {  96, 166, 16, 22 };
	spinAnimation[S].frame[2] = {  80, 166, 16, 22 };
	spinAnimation[S].frame[3] = {  64, 166, 16, 22 };
	spinAnimation[S].frame[4] = {  48, 166, 16, 22 };
	spinAnimation[S].frame[5] = {  32, 166, 16, 22 };
	spinAnimation[S].frame[6] = {  16, 166, 16, 22 };
	spinAnimation[S].frame[7] = {   0, 166, 16, 22 };
	//- North east
	spinAnimation[NE].frame[0] = {  21, 38, 21, 21 };
	spinAnimation[NE].frame[1] = {   0, 38, 21, 21 };
	spinAnimation[NE].frame[2] = { 215, 17, 21, 21 };
	spinAnimation[NE].frame[3] = { 194, 17, 21, 21 };
	spinAnimation[NE].frame[4] = { 173, 17, 21, 21 };
	spinAnimation[NE].frame[5] = { 152, 17, 21, 21 };
	spinAnimation[NE].frame[6] = { 131, 17, 21, 21 };
	spinAnimation[NE].frame[7] = { 110, 17, 21, 21 };
	//- North west
	spinAnimation[NW].frame[0] = { 105, 84, 21, 21 };
	spinAnimation[NW].frame[1] = {  84, 84, 21, 21 };
	spinAnimation[NW].frame[2] = {  63, 84, 21, 21 };
	spinAnimation[NW].frame[3] = {  42, 84, 21, 21 };
	spinAnimation[NW].frame[4] = {  21, 84, 21, 21 };
	spinAnimation[NW].frame[5] = {   0, 84, 21, 21 };
	spinAnimation[NW].frame[6] = { 221, 61, 21, 21 };
	spinAnimation[NW].frame[7] = { 200, 61, 21, 21 };
	//- South east
	spinAnimation[SE].frame[0] = { 164, 189, 21, 21 };
	spinAnimation[SE].frame[1] = { 143, 189, 21, 21 };
	spinAnimation[SE].frame[2] = { 122, 189, 21, 21 };
	spinAnimation[SE].frame[3] = { 101, 189, 21, 21 };
	spinAnimation[SE].frame[4] = {  80, 189, 21, 21 };
	spinAnimation[SE].frame[5] = {  59, 189, 21, 21 };
	spinAnimation[SE].frame[6] = {  38, 189, 21, 21 };
	spinAnimation[SE].frame[7] = {  17, 189, 21, 21 };
	//- South west
	spinAnimation[SW].frame[0] = {  84, 143, 21, 21 };
	spinAnimation[SW].frame[1] = {  63, 143, 21, 21 };
	spinAnimation[SW].frame[2] = {  42, 143, 21, 21 };
	spinAnimation[SW].frame[3] = {  21, 143, 21, 21 };
	spinAnimation[SW].frame[4] = {   0, 143, 21, 21 };
	spinAnimation[SW].frame[5] = { 218, 122, 21, 21 };
	spinAnimation[SW].frame[6] = { 197, 122, 21, 21 };
	spinAnimation[SW].frame[7] = { 176, 122, 21, 21 };
	//- North north east
	spinAnimation[NNE].frame[0] = { 161, 38, 17, 23 };
	spinAnimation[NNE].frame[1] = { 144, 38, 17, 23 };
	spinAnimation[NNE].frame[2] = { 127, 38, 17, 23 };
	spinAnimation[NNE].frame[3] = { 110, 38, 17, 23 };
	spinAnimation[NNE].frame[4] = {  93, 38, 17, 23 };
	spinAnimation[NNE].frame[5] = {  76, 38, 17, 23 };
	spinAnimation[NNE].frame[6] = {  59, 38, 17, 23 };
	spinAnimation[NNE].frame[7] = {  42, 38, 17, 23 };
	//- North east east
	spinAnimation[ENE].frame[0] = {  88, 17, 22, 17 };
	spinAnimation[ENE].frame[1] = {  66, 17, 22, 17 };
	spinAnimation[ENE].frame[2] = {  44, 17, 22, 17 };
	spinAnimation[ENE].frame[3] = {  22, 17, 22, 17 };
	spinAnimation[ENE].frame[4] = {   0, 17, 22, 17 };
	spinAnimation[ENE].frame[5] = { 220,  0, 22, 17 };
	spinAnimation[ENE].frame[6] = { 198,  0, 22, 17 };
	spinAnimation[ENE].frame[7] = { 176,  0, 22, 17 };
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
	spinAnimation[NNW].frame[0] = { 183, 61, 17, 23 };
	spinAnimation[NNW].frame[1] = { 166, 61, 17, 23 };
	spinAnimation[NNW].frame[2] = { 149, 61, 17, 23 };
	spinAnimation[NNW].frame[3] = { 132, 61, 17, 23 };
	spinAnimation[NNW].frame[4] = { 115, 61, 17, 23 };
	spinAnimation[NNW].frame[5] = {  98, 61, 17, 23 };
	spinAnimation[NNW].frame[6] = {  81, 61, 17, 23 };
	spinAnimation[NNW].frame[7] = {  64, 61, 17, 23 };
}

ModuleUnit::~ModuleUnit()
{

}

bool ModuleUnit::Start()
{
	bool ret = true;
	LOG("Loading unit assets");
	//Load assets
	unitTx = App->textures->Load("Assets/OrangeUnitSpritesheet.png");
	throwUnitTx = App->textures->Load("Assets/OrangeUnitThrow.png");
	currentOrbit = currentTurnAround = angleValue[E];
	unitCol = App->collision->AddCollider({ (int)position.x, (int)position.y, 16, 16 }, COLLIDER_INDESTRUCTIBLE, this);
	return ret;
}

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");
	App->textures->Unload(unitTx);
	App->textures->Unload(throwUnitTx);
	return true;
}

update_status ModuleUnit::Update()
{
	switch (unitPhase)
	{
	case UnitPhase::rotating:
		Rotating();
		break;
	case UnitPhase::trowing:
		Throwing();
		break;
	case UnitPhase::returning:
		Returning();
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
	if (playerToFollow->unit_locked == true) { orbiting = false; }

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
	turnAroundToRender = TurnAroundToRender();

	//Set the position----------------------------------------------------------------------------------------
	position.x = radius * cosf(currentOrbit) + playerToFollow->position.x + 16;//+ 16 and + 6 are to make the unit orbit around the center of the player's ship
	position.y = radius * sinf(currentOrbit) + playerToFollow->position.y + 6;

	//Update the collider position (after having set its position)--------------------------------------------
	unitCol->SetPos((int)position.x - 8, (int)position.y - 8);//- 8 is because the sphere part of the unit has 8 witdh and 8 height, so since the position.x and position.y are in the center in the trajectory, we just need to substract them from that to get the position of the collider

													//Increase the animation current frame--------------------------------------------------------------------
	currentSpinFrame += spinSpeed;

	//- Limit the animation frames
	if (currentSpinFrame >= SPIN_FRAMES) { currentSpinFrame = 0; }

	//Set the rotation and render (all in the same place)-----------------------------------------------------
	App->render->Blit(
		unitTx,
		(int)position.x - spriteXDifferences[turnAroundToRender],
		(int)position.y - spriteYDifferences[turnAroundToRender],
		&spinAnimation[turnAroundToRender].frame[(int)currentSpinFrame]
		);

	//Shoot---------------------------------------------------------------------------------------------------
	App->particles->unitShot.speed.x = unitProjectileSpeed * cosf(angleValue[turnAroundToRender]);
	App->particles->unitShot.speed.y = unitProjectileSpeed * sinf(angleValue[turnAroundToRender]);
	if (playerToFollow->Shoot() == true)
	{
		App->particles->AddParticle(
			App->particles->unitShot,
			(int)position.x + shotPosXDifferences[turnAroundToRender],
			(int)position.y + shotPosYDifferences[turnAroundToRender],
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

	if (playerToFollow->ReleaseCharge())
	{
		if (power > 0.3f)//0.3 minimum limit at which the game considers the ball to be charged
		{
			//Throw
			unitPhase = UnitPhase::trowing;
			shootTime = SDL_GetTicks();
		}
		//If the player releases the button, we set the power to 0
		power = 0;
	}
}

void ModuleUnit::Throwing()
{
	//MOVEMENT----------------------------------------------------------------
	//- If 2 s have passed since the unit was thrown, we return it to the player
	if (SDL_GetTicks() > shootTime + 500)//2000 miliseconds
	{
		unitPhase = UnitPhase::returning;
	}
	position.x += cosf(angleValue[turnAroundToRender]) * throwSpeed;
	position.y += sinf(angleValue[turnAroundToRender]) * throwSpeed;

	//RENDER------------------------------------------------------------------
	App->render->Blit(
		unitTx,
		position.x - spriteXDifferences[turnAroundToRender],
		position.y - spriteYDifferences[turnAroundToRender],
		&spinAnimation[turnAroundToRender].frame[(int)currentSpinFrame]),
		0.0f,
		false;
}

void ModuleUnit::Returning()
{
	//MOVEMENT----------------------------------------------------------------

	//- Move
	fPoint vectorIncrease;
	float vectorModule;
	//-- We calculate the vector from the unit position to the player it needs to return to
	vectorIncrease.x = position.x - playerToFollow->position.x;
	vectorIncrease.y = position.y - playerToFollow->position.y;
	//-- We calculate the unit vector
	vectorModule = sqrt(pow(vectorIncrease.x, 2) * pow(vectorIncrease.y, 2));
	vectorIncrease.x = vectorIncrease.x / vectorModule;
	vectorIncrease.y = vectorIncrease.y / vectorModule;
	//-- We add that vector to the position of the orbit
	position.x -= vectorIncrease.x * throwSpeed;
	position.y -= vectorIncrease.y * throwSpeed;

	//- If the unit has reached its position again, we continue orbiting
	if (sqrt(pow(position.x-playerToFollow->position.x,2) + pow(position.y - playerToFollow->position.y, 2)) < throwSpeed)
	{
		//IMPLEMENT: Make a nice transition for some seconds

		position.x = radius + playerToFollow->position.x + 16;//+ 16 and + 6 are to make the unit orbit around the center of the player's ship
		position.y = playerToFollow->position.y + 6;
		unitPhase = UnitPhase::rotating;
	}

	//RENDER------------------------------------------------------------------
	App->render->Blit(
		unitTx,
		position.x - spriteXDifferences[turnAroundToRender],
		position.y - spriteYDifferences[turnAroundToRender],
		&spinAnimation[turnAroundToRender].frame[(int)currentSpinFrame]),
		0.0f,
		false;
}

//This function has a series of if statatements that do the following
//First if  --> Finds the rotation we want to go to
//Second if --> Determines which distance from the currentRotation to the targetRotation is shorter
//Third if  --> Go to that direction, until we get at it
void ModuleUnit::RotateTo(float targetRotation, float &currentRotation, float speed)
{
	//We create a variable that's going to store the opposite rotation from the targetRotation
	float oppositeRotation;

	//Check if the target rotation is down or one of the lower diagonals
	if (targetRotation == angleValue[S] || targetRotation == angleValue[SE] || targetRotation == angleValue[SW])
	{
		oppositeRotation = targetRotation + PI;
		//Check which way is shorter
		if (currentRotation <= oppositeRotation && currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			currentRotation += speed;
		}
	}

	//Check if the target rotation is up or one of the upper diagonals
	else if (targetRotation == angleValue[N] || targetRotation == angleValue[NE] || targetRotation == angleValue[NW])
	{
		oppositeRotation = targetRotation - PI;
		//Check which way is shorter
		if (currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			currentRotation -= speed;
		}
		else if (currentRotation < targetRotation && currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is left
	else if (targetRotation == angleValue[W])
	{
		//Check which way is shorter
		if (currentRotation == 0 || currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is right
	else if (targetRotation == angleValue[E])
	{
		oppositeRotation = angleValue[W];
		//Check which way is shorter
		if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}
}

void ModuleUnit::LimitRotation(float &rotation)
{
	//- Limit the rotation to positive numbers (after modifing it)
	if (rotation < 0)
	{
		rotation = 2 * PI + rotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//- Limit the rotation to one circle
	while (rotation > 2 * PI)
	{
		rotation -= 2 * PI;
	}
}

int ModuleUnit::TurnAroundToRender()
{
	//Start with the exception (E). We need an or because you can end up in this case if you increase the currentTurnAround to 2PI or we decrease it to 0
	if(currentTurnAround >= angleValue[E] - angleSeparation || currentTurnAround < 0 + angleSeparation)
	{
		return E;
	}
	//Then go through all the other cases
	for(int i = E + 1; i < UNIT_AXIS; ++i)
	{
		if(currentTurnAround >= angleValue[i] - angleSeparation && currentTurnAround < angleValue[i] + angleSeparation)
		{
			return i;
		}
	}
	//In case that it didn't return anything before, we'll return the E position, just so that we don't get an error (this should never execute)
	LOG("Unit spin not found, returning east direction");
	return E;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}

