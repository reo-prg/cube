#include <Objects/FallCube.h>



FallCube::FallCube()
{
}

FallCube::FallCube(Vector2Template<int> pos, Vector2Template<int> size)
{
	_pos.x = static_cast<double>(pos.x);
	_pos.y = static_cast<double>(pos.y);
	_size = size;
	_rad = 0.0;
	_stats = OBJ_STATS::NORMAL;
	_type = OBJ_TYPE::CUBE_FALL;

	setImage(OBJ_STATS::NORMAL, ImageMngIns.getImage("cube")[0]);
}


FallCube::~FallCube()
{
}

void FallCube::Update(void)
{

}

void FallCube::velUpdate(void)
{
}
