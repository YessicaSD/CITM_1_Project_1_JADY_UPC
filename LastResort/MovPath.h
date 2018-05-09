#ifndef __MOVPAT_H__
#define __MOVPAT_H__

#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include <math.h>

#define MAX_MOVEMENTS 25


struct Movements
{
	fPoint speed;
	fPoint finalPoint;
	int frames;
	
};

class MovePath
{
public:
	Movements movements[MAX_MOVEMENTS];
	fPoint originPoint;
private:
	
	fPoint position;
	uint last_mov = 0;
	int currentFrame = 0;
	int currentMov = 0;

public:
	MovePath() {}
	~MovePath() {};

	void PushBack(fPoint finalPoint , int frames)
	{
		movements[last_mov].finalPoint = finalPoint;

		if (last_mov == 0) {
			movements[last_mov].speed.x = (finalPoint.x - originPoint.x) / (float)frames;
			movements[last_mov].speed.y = (finalPoint.y - originPoint.y) / (float)frames;
			movements[last_mov].frames = frames;
			++last_mov;
		}
		else {
			movements[last_mov].speed.x = (finalPoint.x - movements[last_mov - 1].finalPoint.x ) / (float)frames;
			movements[last_mov].speed.y = (finalPoint.y-  movements[last_mov - 1].finalPoint.y)/ (float)frames; 
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

	fPoint GetCurrentPosition()
	{
		LOG("current frame :  %i", currentFrame);
		LOG("position : (%i,%i)", position.x, position.y);

		if (currentFrame > movements[currentMov].frames)
		{
			currentFrame = 0;
			++currentMov;
		}
		else if (currentMov > last_mov) {
			return position;
		}
		else {
			position.x += movements[currentMov].speed.x;
			position.y += movements[currentMov].speed.y;
			++currentFrame;
		}
		return position;
	}


};

#endif // __MOVPAT_H__

