#include <Objects/object.h>



object::object()
{
	_pos = { 0,0 };
	_rad = 0.0;
	_zOrder = 0;
}


object::~object()
{
}

void object::Update(void)
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

void object::setGrip(bool grip)
{
	_grip = grip;
}

void object::setPos(Vector2Template<double> pos)
{
	_pos = pos;
}

void object::setState(OBJ_STATS stats)
{
	_stats = stats;
}

void object::setEffect(EFFECT effect, Vector2Template<int> pos)
{

}

OBJ_STATS object::getStats(void)
{
	return _stats;
}

OBJ_TYPE object::getType(void)
{
	return _type;
}

Vector2Template<double> object::getPos(void)
{
	return _pos;
}

Vector2Template<int> object::getSize(void)
{
	return _size;
}



