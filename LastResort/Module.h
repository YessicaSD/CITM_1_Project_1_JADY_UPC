#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
public:
	bool enabled = true;
public:
	virtual ~Module() {}

	// Game execution phases ---
	virtual bool Init()						{ return true; }
	virtual bool Start()					{ return true; }
	virtual update_status InputUpdate()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status LogicUpdate()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status RenderUpdate0()	{ return update_status::UPDATE_CONTINUE; }
	virtual update_status RenderUpdate1()	{ return update_status::UPDATE_CONTINUE; }
	virtual update_status RenderUpdate2() 	{ return update_status::UPDATE_CONTINUE; }
	virtual bool CleanUp()				{ return true; }

	// Module activation ---
	bool IsEnabled() const { return enabled; }

	 void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	// Callbacks ---
	virtual void OnCollision(Collider*, Collider*) {}
};

#endif // __MODULE_H__