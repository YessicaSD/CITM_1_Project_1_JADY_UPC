#include "Application.h"
#include "Enemy_Missile.h"
#include "ModuleStage05.h"
Enemy_Missile::Enemy_Missile(int x, int y, float hp, int scoreValue, POWERUP_TYPE powerupDrop):Enemy(x,y,hp,scoreValue,powerupDrop) {
	Missile.PushBack({ 152,458,77,32 });
	Missile.PushBack({ 142,490,60,16 });
	Missile.PushBack({ 142,506,48,12 });
	Missile.speed = 0.2f;
	animation = &Missile;
	speed.x = 0.0f;
	
}
void Enemy_Missile::Move() 
{

	speed.x += 0.1f;
	fixedPos.x += speed.x;
	position = fixedPos + App->stage05->spawnPos;

	if (collider != nullptr)
		collider->SetPos(position.x - animation->GetFrame().w, position.y - animation->GetFrame().h / 2);
}

void Enemy_Missile::Draw(SDL_Texture* sprites)
{
	if (animation != nullptr)
		App->render->Blit(sprites, position.x-animation->GetFrame().w, position.y - animation->GetFrame().h/2, &(animation->GetCurrentFrame()));
}