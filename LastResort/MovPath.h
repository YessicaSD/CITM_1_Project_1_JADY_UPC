#ifndef __MOVPATH_H__
#define __MOVPATH_H__

#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include <math.h>

#define MAX_MOVEMENTS 25

struct Movements
{
	dPoint speed;
	dPoint finalPoint;
	double frames;
};

class MovePath
{
public:
	dPoint originPoint;
	int currentMov = 0;
	bool movFinished = false;
	bool loop = false;

private:
	Movements movements[MAX_MOVEMENTS];
	int currentFrame = 0;
	dPoint position;
	uint last_mov = 0;
	enum LoopState {
		HEAD, 
		RETURN
	} state = HEAD;

public:
	MovePath() {}
	~MovePath() {};

	void PushBack(dPoint finalPoint, double frames)
	{
		movements[last_mov].finalPoint = finalPoint;

		if (last_mov == 0) {
			movements[last_mov].speed.x = (finalPoint.x - originPoint.x) / frames;
			movements[last_mov].speed.y = (finalPoint.y - originPoint.y) / frames;
			movements[last_mov].frames = frames;
			++last_mov;
		}
		else {
			movements[last_mov].speed.x = (finalPoint.x - movements[last_mov - 1].finalPoint.x) / frames;
			movements[last_mov].speed.y = (finalPoint.y - movements[last_mov - 1].finalPoint.y) / frames;
			movements[last_mov].frames = frames;
			++last_mov;
		}
	}

	void PushBack(int frames)
	{

		if (last_mov == 0) {
			movements[last_mov].finalPoint = originPoint;
			movements[last_mov].speed.x = 0;
			movements[last_mov].speed.y = 0;
			movements[last_mov].frames = frames;
			++last_mov;
		}
		else {
			movements[last_mov].finalPoint = movements[last_mov - 1].finalPoint;
			movements[last_mov].speed.x = 0;
			movements[last_mov].speed.y = 0;
			movements[last_mov].frames = frames;
			++last_mov;
		}
	}

	dPoint GetCurrentPosition()
	{
		movFinished = false;

		switch (state)
		{
		case MovePath::HEAD:

			if (currentFrame < movements[currentMov].frames)
			{
				position.x += movements[currentMov].speed.x;
				position.y += movements[currentMov].speed.y;
				++currentFrame;
			}
			else if (currentMov >= (int)last_mov) {
				movFinished = true;

				if (loop == true) {
					movFinished = false;
					state = RETURN;
					currentFrame = 0;
					currentMov = last_mov - 1;
				}

				return position;
			}
			else {
				currentFrame = 0;
				++currentMov;
			}

			break;
		case MovePath::RETURN:

			if (currentFrame < movements[currentMov].frames)
			{
				position.x -= movements[currentMov].speed.x;
				position.y -= movements[currentMov].speed.y;
				++currentFrame;
			}
			else if (currentMov > 0) {

					state = HEAD;
					currentFrame = 0;
					currentMov =  0;
			
				return position;
			}

			else {
				currentFrame = 0;
				--currentMov;
			}


			break;
		}

		return position;
	}

	dPoint GetPosition()
	{
		return position;
	}

	dPoint SetMovement(int checkpoint)
	{
		position = { 0,0 };
		currentFrame = 0;
		currentMov = checkpoint;
		movFinished = false;

		for (int i = 0; i < checkpoint; ++i) {

			if (i == 0) {
				position.x += (movements[i].finalPoint.x - originPoint.x);
				position.y += (movements[i].finalPoint.y - originPoint.y);
				
			}
			else {
				position.x += (movements[i].finalPoint.x - movements[i - 1].finalPoint.x) ;
				position.y += (movements[i].finalPoint.y - movements[i - 1].finalPoint.y) ;
			}
		}
		return position;
	}
};

#endif // __MOVPATH_H__

