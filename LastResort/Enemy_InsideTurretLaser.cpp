#include "Enemy_InsideTurretLaserh.h"
#include "Application.h"
#include "ModuleStage05.h"
Enemy_Inside_Turret_Laser::Enemy_Inside_Turret_Laser(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop,iPoint speed) : Enemy(x,y,hp,scoreValue,powerupDrop,speed)
{
	renderLayer = 2;
	turret.PushBack({ 250,310,16,24 });
	animation = &turret;
	collider = App->collision->AddCollider({ x, y, 16, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_LIGHT, (Module*)App->enemies);
}
void Enemy_Inside_Turret_Laser::Move() {

	if (framecount > 250)
	{
		framecount = 0;
		if(speed.x>0)
		App->particles->AddParticle(App->particles->indoorLaser, { (float)position.x+animation->GetFrame().w/2,(float)position.y }, { (float)speed.x, (float)speed.y }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_INDOOR_LASER);
		else
			App->particles->AddParticle(App->particles->indoorLaser, { (float)position.x - animation->GetFrame().w / 2,(float)position.y }, { (float)speed.x, (float)speed.y }, App->particles->particlesTx, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, 0, PARTICLE_INDOOR_LASER);
	}
		
	position = fixedPos + App->stage05->spawnPos;

	//------------------------------------------------------
	collider->rect.y = position.y - animation->GetFrame().h/2;
	collider->rect.x = position.x - animation->GetFrame().w/2;
	framecount += 1;
}
void Enemy_Inside_Turret_Laser::Draw(SDL_Texture* sprites)
{
	if (speed.x > 0)
	{
		App->render->Blit(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h/2, &(animation->GetCurrentFrame()));
	}
	else
	{
		App->render->BlitEx(sprites, position.x - animation->GetFrame().w / 2, position.y - animation->GetFrame().h / 2, &(animation->GetCurrentFrame()));
	}
}