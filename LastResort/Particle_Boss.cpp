#include "Application.h"
#include "Particle.h"
#include "Particle_Boss.h"
#include "ModuleStage05.h"

#define LASERS_SPEED 0.2f
#define COLIDER_OFFSET 2.0f
#define LASER_1_SPEED 1.8f
#define LINEAR_OFFSET 18
#define DIAGONAL_OFFSET 24

Particle_Boss::Particle_Boss(fPoint position, SDL_Texture* tex)
{
	this->position = position;
	//this->anim = p.anim;
	this->texture = tex;
	laserPos = position;
	//laserMesures = { 85, 6 };
	
	
	//Animations-----------------------------------------------

	 for (int j = 0; j < 3; ++j) {

		 for (int i = 0; i < 6; ++i) {
			 originAnim.PushBack({ 333 + i*27,6 + j*26 ,27,26 });
		 }

	 }

	 originAnim.speed = 0.3f;

	 for (int j = 0; j < 3; ++j) {

		 for (int i = 0; i < 8; ++i) {
			 finalAnim.PushBack({ 333 + i * 16,84 + j * 16,16,16 });
		 }
		  
	 }
	 for (int j = 2; j >= 0; --j) {

		 for (int i = 7; i >= 0; --i) {
			 finalAnim.PushBack({ 333 + i * 16,84 + j * 16,16,16 });
		 }

	 }
	 finalAnim.speed = 0.3f;
	  


	diagonalLaserRAnim.PushBack({ 495,6,36,36 });
	diagonalLaserRAnim.PushBack({ 531,6,36,36 });

	diagonalLaserRAnim.speed = 0.1f;

	diagonalLaserLAnim.PushBack({ 495,138,36,36 });
	diagonalLaserLAnim.PushBack({ 531,138,36,36 });

	diagonalLaserLAnim.speed = 0.1f; 

	linearLaserXAnim.PushBack({ 495,90,48,48 });
	linearLaserXAnim.PushBack({ 543,90,48,48 });

	linearLaserXAnim.speed = 0.1f;

	linearLaserYAnim.PushBack({ 495,42,48,48 });
	linearLaserYAnim.PushBack({ 543,42,48,48 });

	linearLaserYAnim.speed = 0.1f;

	lasers[N].animation = linearLaserYAnim;
	lasers[NE].animation = diagonalLaserRAnim;
	lasers[E].animation = linearLaserXAnim;
	lasers[SE].animation = diagonalLaserRAnim;
	lasers[S].animation = linearLaserYAnim;
	lasers[SW].animation = diagonalLaserLAnim;
	lasers[W].animation = linearLaserXAnim;
	lasers[NW].animation = diagonalLaserLAnim;


}


Particle_Boss:: ~Particle_Boss() {

	for (int i = 0; i < MAX_DIR ; ++i) {
		if (lasers[i].collider != nullptr) {
			lasers[i].collider->to_delete = true;
			lasers[i].collider = nullptr;
		}
	}

	if (collider != nullptr) {
		collider->to_delete = true;
		collider = nullptr;
	}

}

void Particle_Boss::Move() {
	

	if (frames < 100 && frames >= 40) {
		if (addedLaserCol == false) {
			collider = App->collision->AddCollider({ (int)laserPos.x , (int)laserPos.y  , 0, 0 }, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, (Module*)App->particles);
			addedLaserCol = true;
		}
		laserPos.x -= LASER_1_SPEED;
		laserWeight += LASER_1_SPEED;
		collider->SetPos((int)laserPos.x, (int)laserPos.y -3);
		collider->SetMeasurements((int)laserWeight, 6);
	}

	else if (frames < 160 && frames >= 100) {
		laserWeight -= LASER_1_SPEED;
		collider->SetMeasurements((int)laserWeight, 6);
	}

	if (frames > 160) {

		if (deletedLaserCol== false) {
			collider->to_delete = true;
			collider = nullptr;
			deletedLaserCol = true;
		}

		if (addedColliders == false) {
			AddColliders();
			addedColliders = true;
		}

		for (int i = 0; i < MAX_DIR; ++i) {

			switch (i)
			{
			case N:
				lasers[i].position += {0.0f, -LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x - COLIDER_OFFSET, lasers[i].position.y - linearOffset.y - COLIDER_OFFSET);
				break;
			case NE:
				lasers[i].position += {LASERS_SPEED, -LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x + diagonalOffset.x - COLIDER_OFFSET, lasers[i].position.y - diagonalOffset.y - COLIDER_OFFSET);
				break;
			case E:
				lasers[i].position += {LASERS_SPEED, 0.0f};
				lasers[i].collider->SetPos(lasers[i].position.x + linearOffset.x - COLIDER_OFFSET, lasers[i].position.y - COLIDER_OFFSET);
				break;
			case SE:
				lasers[i].position += {LASERS_SPEED, LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x + diagonalOffset.x - COLIDER_OFFSET, lasers[i].position.y + diagonalOffset.y - COLIDER_OFFSET);
				break;
			case S:
				lasers[i].position += {0.0f, LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x - COLIDER_OFFSET, lasers[i].position.y + linearOffset.y - COLIDER_OFFSET);

				break;
			case SW:
				lasers[i].position += {-LASERS_SPEED, LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x - diagonalOffset.x - COLIDER_OFFSET, lasers[i].position.y + diagonalOffset.y - COLIDER_OFFSET);
				break;
			case W:
				lasers[i].position += {-LASERS_SPEED, 0.0f};
				lasers[i].collider->SetPos(lasers[i].position.x - linearOffset.x - COLIDER_OFFSET, lasers[i].position.y - COLIDER_OFFSET);
				break;
			case NW:
				lasers[i].position += {-LASERS_SPEED, -LASERS_SPEED};
				lasers[i].collider->SetPos(lasers[i].position.x - diagonalOffset.x - COLIDER_OFFSET, lasers[i].position.y - diagonalOffset.y - COLIDER_OFFSET);
				break;
			}
		}
	}
	++frames;

}
void Particle_Boss::Draw() {

	SDL_Rect laser_rect;
	
	if ((frames / 30) % 2 == true) {
		laser_rect = { (int)laserPosTex1.x,(int)laserPosTex1.y , (int)laserWeight, 6 };
	}
	else {
		laser_rect = { (int)laserPosTex2.x, (int)laserPosTex2.y , (int)laserWeight, 6 };
	}
	


	//Laser animation-----------------------------------------------

	if (frames < 160 && frames >= 40) {

		App->render->Blit(texture, (int)laserPos.x, (int)laserPos.y - 3, &laser_rect);
	}

	//Lasers animation-----------------------------------------------
	

	if (frames > 160) {

		for (int i = 0; i < MAX_DIR ; ++i) {

			switch (i)
			{
			case N:
				App->render->BlitEx(texture, (int)lasers[i].position.x - LINEAR_OFFSET, (int)lasers[i].position.y - LINEAR_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_VERTICAL );
				break;
			case NE:
				App->render->BlitEx(texture, (int)lasers[i].position.x - DIAGONAL_OFFSET, (int)lasers[i].position.y - DIAGONAL_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_VERTICAL);
				break;
			case E:
				App->render->BlitEx(texture, (int)lasers[i].position.x - LINEAR_OFFSET, (int)lasers[i].position.y - LINEAR_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_NONE);
				break;
			case SE:
				App->render->BlitEx(texture, (int)lasers[i].position.x - DIAGONAL_OFFSET, (int)lasers[i].position.y - DIAGONAL_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_NONE);
				break;
			case S:
				App->render->BlitEx(texture, (int)lasers[i].position.x - LINEAR_OFFSET, (int)lasers[i].position.y - LINEAR_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_NONE);
				break;
			case SW:
				App->render->BlitEx(texture, (int)lasers[i].position.x - DIAGONAL_OFFSET, (int)lasers[i].position.y - DIAGONAL_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_NONE);
				break;
			case W:
				App->render->BlitEx(texture, (int)lasers[i].position.x - LINEAR_OFFSET, (int)lasers[i].position.y - LINEAR_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_HORIZONTAL);
				break;
			case NW:
				App->render->BlitEx(texture, (int)lasers[i].position.x - DIAGONAL_OFFSET, (int)lasers[i].position.y - DIAGONAL_OFFSET, &lasers[i].animation.LoopAnimation(), SDL_FLIP_VERTICAL);
				break;
			}
		}
	}

	//Origin animation-----------------------------------------------

	if (originAnim.finished != true) {
		App->render->Blit(texture, (int)position.x - 16, (int)position.y - 16, &originAnim.GetFrameEx());
	}

	//Final animation-----------------------------------------------

	if (frames >= 150 && finalAnim.finished != true) {

		App->render->Blit(texture, (int)laserPos.x, (int)laserPos.y , &finalAnim.GetFrameEx());
	}

	

}

void Particle_Boss::AddColliders() {

	for (int i = 0; i < MAX_DIR; ++i) {
		if (lasers[i].collider == nullptr) {
			lasers[i].collider = App->collision->AddCollider({ (int)lasers[i].position.x - 2, (int)lasers[i].position.y - 2 , 4, 4 }, COLLIDER_ENEMY_SHOT_INDESTRUCTIBLE, (Module*)App->particles);
		}
	}


}

