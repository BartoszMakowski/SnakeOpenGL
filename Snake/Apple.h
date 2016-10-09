#pragma once
#include "Model.h"
class Apple :
	public Model
{
public:
	Apple(vec2);
	~Apple();
	vec2 getPos();
	bool setPos(vec2);
private:
	vec2 applePos;
};

