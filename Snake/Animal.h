#pragma once
#include "Model.h"
class Animal :
	public Model
{
public:
	Animal(char*, vec3);
	Animal(char*, vec3, GLfloat);
	~Animal();
	void draw(mat4* view, mat4* projection);
};

