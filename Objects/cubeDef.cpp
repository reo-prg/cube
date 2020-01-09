#include <Objects/cubeDef.h>



cubeDef::cubeDef()
{
}

cubeDef::cubeDef(Vector2Template<double> pos, Vector2Template<int> size)
{
	_pos = pos;
	_rad = 0.0;
	_size = size;
	_stats = OBJ_STATS::NORMAL;

	setImage(OBJ_STATS::NORMAL, ImageMngIns.getImage("s_cube")[0]);
}


cubeDef::~cubeDef()
{
	
}

