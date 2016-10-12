#include "Apple.h"


Apple::Apple(vec2 pos) : Model((char*)APPLEOBJPATH)
{
	scaleMultiplier = 2.0;
	applePos = vec2(pos.x, pos.y);
	baseModel = translate(baseModel, vec3(pos.x, 0.0f, pos.y));
	baseModel = scale(baseModel, vec3(1.0, 1.0, 1.0)*scaleMultiplier);
	cout << "\n ============== \nAPPLE POS: " << pos.x << "\t" << pos.y << endl;
}

Apple::~Apple()
{
}

vec2 Apple::getPos(){
	return applePos;
}

void Apple::draw(mat4* view, mat4* projection){
	baseModel = rotate(baseModel, glm::radians(5.0f), vec3(0.0f, 1.0f, 0.0f));
	Model::draw(view, projection);
}

bool Apple::setPos(vec2 newPos){
	applePos = newPos;
	return true;

}
