#ifndef __Player2_H__
#define __Player2_H__

#include "ModulePlayer.h"

class Player2 : public ModulePlayer
{
public:
	Player2();
	//void LoadSprites() override;
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
	bool Shoot();
	bool Charge();
	bool ReleaseCharge();
	bool Lock();
	void Winposition() override;
	void PlayerDies();
	void KillUnit();
};
#endif