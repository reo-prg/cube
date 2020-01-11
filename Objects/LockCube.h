#pragma once
#include <Objects/object.h>
class LockCube :
	public object
{
public:
	LockCube();
	LockCube(Vector2Template<int> pos, Vector2Template<int> size);
	~LockCube();
};

