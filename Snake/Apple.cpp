#include "Apple.h"


Apple::Apple(vec2 pos)
{
	applePos = vec2(pos.x, pos.y);
	baseModel = translate(baseModel, vec3(pos.x, 0.1, pos.y));
	cout << "\n ============== \nAPPLE POS: " << pos.x << "\t" << pos.y << endl;
}

Apple::~Apple()
{
}

vec2 Apple::getPos(){
	return applePos;
}

bool Apple::setPos(vec2 newPos){
	applePos = newPos;
	return true;

}
