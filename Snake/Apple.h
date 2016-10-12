#pragma once
#include "Model.h"
static const char* APPLEOBJPATH = ".\\OBJ\\Rabbit.obj";

class Apple :
	public Model
{
public:
	Apple(vec2);
	~Apple();
	vec2 getPos();
	bool setPos(vec2);
	void draw(mat4* view, mat4* projection);
private:
	vec2 applePos;
};

