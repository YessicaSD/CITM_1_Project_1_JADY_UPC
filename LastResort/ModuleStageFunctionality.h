#ifndef __ModuleStageFunctionality_H__
#define __ModuleStageFunctionality_H__

#include "Module.h"
#include "Globals.h"

enum DebugElement
{
	none = -1,
	scene,
	checkpoint,
	enemy,
	powerup
};

class ModuleStageFunctionality : public Module
{
public:

	ModuleStageFunctionality();
	~ModuleStageFunctionality();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	void Debugging();
	void ChooseDebugElem(int);
	void GoToScene();

public:
	int selectedElemNum = -1;//Selected element number
	DebugElement debugElem = DebugElement::none;//Debug element = the type of element we're debugging. It can be any type from the enum "DebugElement"
	Module * currentStage = nullptr;
};

#endif // __ModuleStageFunctionality_H_H__
