#include <Objects/LockCube.h>



LockCube::LockCube()
{
}

LockCube::LockCube(Vector2Template<int> pos, Vector2Template<int> size)
{
	_pos.x = static_cast<double>(pos.x);
	_pos.y = static_cast<double>(pos.y);
	_rad = 0.0;
	_size = size;
	_stats = OBJ_STATS::NORMAL;
	_type = OBJ_TYPE::CUBE_LOCK;
	_grip = false;

	setImage(OBJ_STATS::NORMAL, ImageMngIns.getImage("cube")[1]);
}


LockCube::~LockCube()
{
	
}

