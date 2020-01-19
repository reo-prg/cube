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
	_grip = false;

	setImage(OBJ_STATS::NORMAL, ImageMngIns.getImage("cube")[0]);
}


FallCube::~FallCube()
{
}

void FallCube::Update(void)
{
	velUpdate();
}

void FallCube::velUpdate(void)
{
	if (!_grip)
	{
		Vector2Template<double> tmpPos;

		if (StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _size.y + _initVel) }) <= 23 &&
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _size.y + _initVel) }) <= 23)
		{
			tmpPos = CheckHitObj()({ _pos.x, _pos.y + _initVel }, _size, OBJ_TYPE::MAX, std::make_shared<object>(*this), CHECK_DIR::DOWN);
			if (tmpPos.x == -100 && tmpPos.y == -100)
			{
				_initVel += CB_G_ACC;
				_pos.y += _initVel;
			}
			else
			{
				_pos.y = tmpPos.y - _size.y;
				_initVel = 0.0;
			}
		}
		else
		{
			_pos.y = (static_cast<int>(_pos.y + _initVel) / BlockSize) * BlockSize;

			_initVel = 0.0;
		}
	}
	else
	{
		_initVel = 0.0;
	}
}
