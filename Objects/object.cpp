#include "object.h"



object::object()
{
	_pos = { 0,0 };
	_rad = 0.0;
	_zOrder = 100;
}


object::~object()
{
}

void object::objDraw(void)
{
	ImageMngIns.AddDraw({ _image[_stats],static_cast<int>(_pos.x) + 16,static_cast<int>(_pos.y) + 16,_rad,LAYER::CHAR,_zOrder });
}

void object::setImage(OBJ_STATS stats, int id)
{
	_image.emplace(stats, id);
}


