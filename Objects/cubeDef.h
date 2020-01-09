#pragma once
#include <Objects/object.h>
class cubeDef :
	public object
{
public:
	cubeDef();
	cubeDef(Vector2Template<double> pos, Vector2Template<int> size);
	~cubeDef();
	
};

