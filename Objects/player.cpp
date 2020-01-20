#include <Objects/player.h>



player::player()
{
}

player::player(Vector2Template<double> pos, double rad, Vector2Template<int> size, int color)
{
	_pos = pos;
	_rad = rad;
	_size = size;
	_initVel = 0.0;
	_jumpDeley = 0;
	_stats = OBJ_STATS::RIGHT;
	_type = OBJ_TYPE::PLAYER;
	_grip = false;
	_gripCube = nullptr;

	setImage(OBJ_STATS::RIGHT, ImageMngIns.getImage("player")[color * 2 + 0]);
	setImage(OBJ_STATS::LEFT , ImageMngIns.getImage("player")[color * 2 + 1]);
}


player::~player()
{
}

void player::Update(void)
{
	control();
	velUpdate();

	if (_grip)
	{
		_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });
	}
	
	if (_jumpDeley > 0)
	{
		_jumpDeley--;
	}
}

void player::control(void)
{
	_padInput = GetJoypadInputState(DX_INPUT_PAD1);
	GetJoypadAnalogInput(&_stickInput.x, &_stickInput.y, DX_INPUT_PAD1);
	if (CheckHitKey(KEY_INPUT_SPACE) && !_grip)
	{
		_gripCube = CanGripCube()(*this);
	}
	if (!CheckHitKey(KEY_INPUT_SPACE) && _grip)
	{
		_grip = false;
		_gripCube->setGrip(false);
		_gripCube = false;
	}

	Vector2Template<double> tmpPos;

	// 左右移動
	if (_stickInput.x > 300 || CheckHitKey(KEY_INPUT_RIGHT))
	{
		_stats = OBJ_STATS::RIGHT;
		if (StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED), static_cast<int>(_pos.y + _size.y - 1) }) >= 24)
		{
			if (CheckHitCube(CHECK_DIR::RIGHT))
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x) / BlockSize - 1) * BlockSize);
			}
			else
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x + PL_SPEED) / BlockSize) * BlockSize);
			}
		}
		else if (CheckHitCube(CHECK_DIR::RIGHT))
		{
			_pos.x = _gripCube->getPos().x - _gripCube->getSize().x;
			if (StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED - 1), static_cast<int>(_pos.y) }) >= 24 ||
				StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED - 1), static_cast<int>(_pos.y + _size.y - 1) }) >= 24)
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x + PL_SPEED) / BlockSize - 1) * BlockSize);
			}
			else
			{
				tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::RIGHT);
				if (tmpPos.x != -100 && tmpPos.y != -100)
				{
					_pos.x = tmpPos.x - _size.x;
				}
			}
		}
		else
		{
			tmpPos = CheckHitObj()({ _pos.x + PL_SPEED, _pos.y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::RIGHT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_pos.x = tmpPos.x - _size.x;
			}
			else
			{
				_pos.x += PL_SPEED;
			}
		}
	}
	else if (_stickInput.x < -300 || CheckHitKey(KEY_INPUT_LEFT))
	{
		_stats = OBJ_STATS::LEFT;
		if (StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y + _size.y - 1) }) >= 24)
		{
			if (CheckHitCube(CHECK_DIR::LEFT))
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x - PL_SPEED - 1) / BlockSize + 1) * BlockSize);
			}
			else
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x - PL_SPEED - 1) / BlockSize) * BlockSize);
			}
		}
		else if (CheckHitCube(CHECK_DIR::LEFT))
		{
			_pos.x = _gripCube->getPos().x + _gripCube->getSize().x;
			if (StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y) }) >= 24 ||
				StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y + _size.y - 1) }) >= 24)
			{
				_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x - PL_SPEED - 1) / BlockSize + 1) * BlockSize);
			}
			else
			{
				tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::LEFT);
				if (tmpPos.x != -100 && tmpPos.y != -100)
				{
					_pos.x = tmpPos.x + _size.x;
				}
			}
		}
		else
		{
			tmpPos = CheckHitObj()({ _pos.x - PL_SPEED, _pos.y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::LEFT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_pos.x = tmpPos.x + _size.x;
			}
			else
			{
				_pos.x -= PL_SPEED;
			}
		}
	}
	else
	{
		// なにもしない
	}
	if (_grip)
	{
		_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });
	}

	// 特殊な場合の左右の衝突チェック(データが23以下は貫通可能　24以上は貫通不可)
	// 右
	if (_stats == OBJ_STATS::RIGHT)
	{
		if ((StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y - 1) }) >= 24) &&
			CheckHitCube(CHECK_DIR::RIGHT))
		{
			_pos.x = (static_cast<double>(static_cast<int>(_pos.x) / BlockSize - 1) * BlockSize);
			_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });
		}

		if (_grip)
		{
			if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
				StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
			{
				_pos.x = static_cast<double>((static_cast<int>(_pos.x) / BlockSize - 1) * BlockSize);
			}

			tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::LEFT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_pos.x = tmpPos.x - _size.x * 2;
			}
		}
	}

	// 左
	if (_stats == OBJ_STATS::LEFT)
	{
		if ((StageMngIns.getStageData({ static_cast<int>(_pos.x - 1), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x - 1), static_cast<int>(_pos.y + _size.y - 1) }) >= 24) &&
			CheckHitCube(CHECK_DIR::LEFT))
		{
			_pos.x = static_cast<double>((static_cast<int>(_pos.x + _size.x - 1) / BlockSize + 1) * BlockSize);
			_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });
		}

		if (_grip)
		{
			if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
				StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
			{
				_pos.x = static_cast<double>((static_cast<int>(_pos.x + _size.x - 1) / BlockSize + 1) * BlockSize);
			}

			tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::RIGHT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_pos.x = tmpPos.x + _size.x * 2;
			}
		}
	}
	

	// ジャンプ
	if (((_padInput & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_UP)) && _jumpDeley <= 0)
	{
		if(StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _size.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _size.y) }) >= 24)
		{
			_initVel = -10.0;
		}
		else
		{
			tmpPos = CheckHitObj()({ _pos.x, _pos.y }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::DOWN);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_initVel = -10.0;
			}
		}
	}
}

void player::velUpdate(void)
{
	Vector2Template<double> tmpPos;

	// 自分の上のブロックにぶつかったら加速度を0にする
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _initVel) }) >= 24 ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _initVel) }) >= 24)
	{
		_pos.y = (static_cast<int>(_pos.y) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}
	else if (CheckHitCube(CHECK_DIR::UP))
	{
		_pos.y = _gripCube->getPos().y;
		_initVel = 0.0;
	}
	else
	{
		tmpPos = CheckHitObj()({ _pos.x, _pos.y + _initVel }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::UP);
		if (tmpPos.x != -100 && tmpPos.y != -100)
		{
			_pos.y = tmpPos.y + _size.y;
			_initVel = 0.0;
		}
	}

	// 自分の下にブロックが無いなら加速度を変える　あるならば加速度を0にする
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _size.y + _initVel) }) >= 24 ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _size.y + _initVel) }) >= 24)
	{
		_pos.y = (static_cast<int>(_pos.y + _initVel) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}
	else if (CheckHitCube(CHECK_DIR::DOWN))
	{
		_pos.y = _gripCube->getPos().y;
		_initVel = 0.0;
	}
	else
	{
		tmpPos = CheckHitObj()({ _pos.x, _pos.y + _initVel }, _size, OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::DOWN);
		if (tmpPos.x == -100 && tmpPos.y == -100)
		{
			_jumpDeley = JUMP_DELEY;
			_pos.y += _initVel;
			_initVel += PL_G_ACC;
		}
		else
		{
			_pos.y = tmpPos.y - _size.y;
			_initVel = 0.0;
		}
	}
}

bool player::CheckHitCube(CHECK_DIR dir)
{
	if (_gripCube == nullptr)
	{

		return false;
	}
	Vector2Template<double> tmpPos;
	_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });

	switch (dir)
	{
	case CHECK_DIR::RIGHT:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x + PL_SPEED - 1), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x + PL_SPEED - 1), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
		{
			_gripCube->setPos({ static_cast<double>(static_cast<int>(_gripCube->getPos().x + PL_SPEED) / BlockSize) * BlockSize, _gripCube->getPos().y });
			return true;
		}
		else
		{
			tmpPos = CheckHitObj()({ _gripCube->getPos().x + PL_SPEED, _gripCube->getPos().y }, _gripCube->getSize(), OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::RIGHT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_gripCube->setPos({ tmpPos.x - _gripCube->getSize().x, _gripCube->getPos().y });
				return true;
			}
		}
		break;
	case CHECK_DIR::LEFT:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - PL_SPEED), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - PL_SPEED), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
		{
			_gripCube->setPos({ static_cast<double>(static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - PL_SPEED - 1) / BlockSize) * BlockSize, _gripCube->getPos().y });
			return true;
		}
		else
		{
			tmpPos = CheckHitObj()({ _gripCube->getPos().x - PL_SPEED, _gripCube->getPos().y }, _gripCube->getSize(), OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::LEFT);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_gripCube->setPos({ tmpPos.x + _gripCube->getSize().x, _gripCube->getPos().y });
				return true;
			}
		}
		break;
	case CHECK_DIR::UP:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y + _initVel) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y + _initVel) }) >= 24)
		{
			_gripCube->setPos({ _gripCube->getPos().x, static_cast<double>(static_cast<int>(_gripCube->getPos().y) / BlockSize) * BlockSize });
			return true;
		}
		else
		{
			tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y + _initVel }, _gripCube->getSize(), OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::UP);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_gripCube->setPos({ _gripCube->getPos().x, tmpPos.y + _gripCube->getSize().y });
				return true;
			}
		}
		break;
	case CHECK_DIR::DOWN:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) }) >= 24)
		{
			_gripCube->setPos({ _gripCube->getPos().x, static_cast<double>(static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) / BlockSize) * BlockSize });
			return true;
		}
		else
		{
			tmpPos = CheckHitObj()({ _gripCube->getPos().x, _gripCube->getPos().y + _initVel }, _gripCube->getSize(), OBJ_TYPE::PLAYER, _gripCube, CHECK_DIR::DOWN);
			if (tmpPos.x != -100 && tmpPos.y != -100)
			{
				_gripCube->setPos({ _gripCube->getPos().x, tmpPos.y - _gripCube->getSize().y });
				return true;
			}
		}
		break;
	default:
		AST();
		break;
	}

	return false;
}
