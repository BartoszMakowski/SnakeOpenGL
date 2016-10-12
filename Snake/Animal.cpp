#include "Animal.h"


Animal::Animal(char* obj, vec3 pos) : Model(obj)
{
	baseModel = translate(baseModel, vec3(pos.x, pos.y, pos.z));
}

Animal::Animal(char* obj, vec3 pos, GLfloat scaleMul) : Model(obj)
{
	baseModel = translate(baseModel, pos);
	baseModel = scale(baseModel, vec3(1.0, 1.0, 1.0)*scaleMul);
}



Animal::~Animal()
{
}


void Animal::draw(mat4* view, mat4* projection){
	baseModel = rotate(baseModel, glm::radians((0.2f) +(rand()%3 *1.0f) ), vec3(0.0f, 1.0f, 0.0f));
	Model::draw(view, projection);
}