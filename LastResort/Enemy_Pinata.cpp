#include "Application.h"
#include "Enemy_Pinata.h"
#include "ModuleCollision.h"
#include "Player1.h"
#include "Player2.h"
#include "MovPath.h"


Enemy_Pinata::Enemy_Pinata(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	pinataMov.originPoint = { 0,0 };
	pinataMov.PushBack({ 0,90 }, 150);
	//Animations-----------------------------
	moveAnim.PushBack({ 263, 63,40,38 });   //1
	moveAnim.PushBack({ 223, 101,40,38 });  //2
	moveAnim.PushBack({ 263, 101,40,38 });  //3

	rotateAnim.PushBack({ 223, 139,40,38 }); //1
	rotateAnim.PushBack({ 263, 139,40,38 }); //2
	rotateAnim.PushBack({ 223, 139,40,38 }); //3

	initAnim.PushBack({ 223, 63,40,38 });   //1
	initAnim.PushBack({ 263, 139,40,38 });  //2
	initAnim.PushBack({ 223, 139,40,38 });  //3
	//Add collider--------------------------
	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Pinata::Move()
{
	//Search tarjet player---------------------------------------------
	if (searchPlayers == true) {

		if (App->player2->position.DistanceTo(position) > App->player1->position.DistanceTo(position)) {
			targetPlayer = App->player1;
		}
		else {
			targetPlayer = App->player2;
		}




	}

	//Move-------------------------------------------------------------

	switch (currentState)
	{
	case Enemy_Pinata::INIT:
		if (pinataMov.movFinished) {
			searchPlayers = true;
			currentState = FOLLOW;
			break;
		}
		pinataMov.GetCurrentPosition();
		position.x = pinataMov.GetPosition().x;
		position.y = pinataMov.GetPosition().y;
		break;
	case Enemy_Pinata::FOLLOW:


		break;
	case Enemy_Pinata::ROTATE:
		break;
	default:
		break;
	}

}