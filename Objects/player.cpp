#include <Objects/player.h>



player::player()
{
}

player::player(Vector2Template<double> pos, double rad, Vector2Template<int> size)
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

	setImage(OBJ_STATS::RIGHT, ImageMngIns.getImage("player")[0]);
	setImage(OBJ_STATS::LEFT , ImageMngIns.getImage("player")[1]);
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

	if (CheckHitKey(KEY_INPUT_Z) && !_grip)
	{
		_gripCube = CanGripCube()(*this);
	}
	if (!CheckHitKey(KEY_INPUT_Z) && _grip)
	{
		_grip = false;
		_gripCube->setGrip(false);
		_gripCube = false;
	}

	// 左右移動
	if (_stickInput.x > 300 || CheckHitKey(KEY_INPUT_RIGHT))
	{
		_pos.x += 5;
		_stats = OBJ_STATS::RIGHT;
	}
	if (_stickInput.x < -300 || CheckHitKey(KEY_INPUT_LEFT))
	{
		_pos.x -= 5;
		_stats = OBJ_STATS::LEFT;
	}

	// 左右の衝突チェック
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x) / BlockSize, static_cast<int>(_pos.y) / BlockSize }) ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x) / BlockSize, static_cast<int>(_pos.y + _size.y - 1) / BlockSize }) ||
		CheckHitCube(CHECK_DIR::RIGHT))
	{
		_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x) / BlockSize - 1) * BlockSize);
	}
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x - 1) / BlockSize, static_cast<int>(_pos.y) / BlockSize }) ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x - 1) / BlockSize, static_cast<int>(_pos.y + _size.y - 1) / BlockSize }) ||
		CheckHitCube(CHECK_DIR::LEFT))
	{
		_pos.x = static_cast<double>((static_cast<int>(_pos.x - 1) / BlockSize + 1) * BlockSize);
	}

	// ジャンプ
	if (((_padInput & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_X))&&
		_jumpDeley <= 0 &&
		(StageMngIns.getStageData({ static_cast<int>(_pos.x) / BlockSize, static_cast<int>(_pos.y + _size.y) / BlockSize }) ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1) / BlockSize, static_cast<int>(_pos.y + _size.y) / BlockSize })))
	{
		_initVel = -10.0;
	}
}

void player::velUpdate(void)
{
	// 自分の上のブロックにぶつかったら加速度を0にする
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x) / BlockSize, static_cast<int>(_pos.y + _initVel) / BlockSize }) ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1) / BlockSize, static_cast<int>(_pos.y + _initVel) / BlockSize }) ||
		CheckHitCube(CHECK_DIR::UP))
	{
		_pos.y = (static_cast<int>(_pos.y) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}

	// 自分の下にブロックが無いなら加速度を変える　あるならば加速度を0にする
	if ((StageMngIns.getStageData({ static_cast<int>(_pos.x) / BlockSize, static_cast<int>(_pos.y + _size.y + _initVel) / BlockSize }) == 0) &&
		(StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1) / BlockSize, static_cast<int>(_pos.y + _size.y + _initVel) / BlockSize }) == 0))
	{
		if (CheckHitCube(CHECK_DIR::DOWN))
		{
			_initVel += PL_G_ACC;
			_jumpDeley = JUMP_DELEY;
			_pos.y += _initVel;
		}
		else
		{
			_pos.y = (static_cast<int>(_pos.y + _initVel) / BlockSize) * BlockSize;
		}
	}
	else
	{
		_pos.y = (static_cast<int>(_pos.y + _initVel) / BlockSize) * BlockSize;

		_initVel = 0.0;
	}
}

bool player::CheckHitCube(CHECK_DIR dir)
{
	if (_gripCube == nullptr)
	{
		if (dir == CHECK_DIR::DOWN)
		{
			return true;
		}
		return false;
	}

	_gripCube->setPos({ this->_pos.x + (static_cast<int>(this->_stats) * 2 - 1) * _gripCube->getSize().x, this->_pos.y });

	switch (dir)
	{
	case CHECK_DIR::RIGHT:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x) / BlockSize, static_cast<int>(_gripCube->getPos().y) / BlockSize }) ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x) / BlockSize, static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) / BlockSize }))
		{
			return true;
		}
		break;
	case CHECK_DIR::LEFT:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - 1) / BlockSize, static_cast<int>(_gripCube->getPos().y) / BlockSize }) ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - 1) / BlockSize, static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) / BlockSize }))
		{
			return true;
		}
		break;
	case CHECK_DIR::UP:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x) / BlockSize, static_cast<int>(_gripCube->getPos().y + _initVel) / BlockSize }) ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1) / BlockSize, static_cast<int>(_gripCube->getPos().y + _initVel) / BlockSize }))
		{
			return true;
		}
		break;
	case CHECK_DIR::DOWN:
		if ((StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x) / BlockSize, static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) / BlockSize }) == 0) &&
			(StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1) / BlockSize, static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) / BlockSize }) == 0))
		{
			return true;
		}
		break;
	default:
		AST();
		break;
	}

	return false;
}
