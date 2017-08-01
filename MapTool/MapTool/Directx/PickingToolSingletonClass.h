#pragma once	

#include "PickingToolClass.h"

class PickingToolSingletonClass
{
private:
	PickingToolSingletonClass();
	PickingToolSingletonClass(const PickingToolSingletonClass &);
	~PickingToolSingletonClass();

private:
	static PickingToolClass *inst;

public:
	static PickingToolClass *GetInstance()
	{
		if (inst == nullptr)
			inst = new PickingToolClass();
		
		return inst;
	}
};