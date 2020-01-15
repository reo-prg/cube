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

	// ���E�ړ�
	if (_stickInput.x > 300 || CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x + PL_SPEED), static_cast<int>(_pos.y + _size.y - 1) }) >= 24 ||
			CheckHitCube(CHECK_DIR::RIGHT))
		{
			_pos.x = (static_cast<double>(static_cast<int>(_pos.x + PL_SPEED) / BlockSize) * BlockSize);
		}
		else
		{
			_pos.x += PL_SPEED;
		}
		_stats = OBJ_STATS::RIGHT;
	}
	if (_stickInput.x < -300 || CheckHitKey(KEY_INPUT_LEFT))
	{
		if (StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x - PL_SPEED), static_cast<int>(_pos.y + _size.y - 1) }) >= 24 ||
			CheckHitCube(CHECK_DIR::LEFT))
		{
			_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x - PL_SPEED) / BlockSize) * BlockSize);
		}
		else
		{
			_pos.x -= PL_SPEED;
		}
		_stats = OBJ_STATS::LEFT;

	}

	//// ���E�̏Փ˃`�F�b�N(�f�[�^��23�ȉ��͊ђʉ\�@24�ȏ�͊ђʕs��)
	// �E

	if ((StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y) }) >= 24 ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x), static_cast<int>(_pos.y + _size.y - 1) }) >= 24) &&
		CheckHitCube(CHECK_DIR::RIGHT))
	{
		_pos.x = (static_cast<double>(static_cast<int>(_pos.x) / BlockSize - 1) * BlockSize);
	}

	// ��
	if ((StageMngIns.getStageData({ static_cast<int>(_pos.x - 1), static_cast<int>(_pos.y) }) >= 24 ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x - 1), static_cast<int>(_pos.y + _size.y - 1) }) >= 24) &&
		CheckHitCube(CHECK_DIR::LEFT))
	{
		_pos.x = static_cast<double>((static_cast<int>(_pos.x + _size.x - 1) / BlockSize + 1) * BlockSize);
	}

	// �W�����v
	if (((_padInput & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_X))&&
		_jumpDeley <= 0 &&
		(StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _size.y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _size.y) }) >= 24))
	{
		_initVel = -10.0;
	}
}

void player::velUpdate(void)
{
	// �����̏�̃u���b�N�ɂԂ�����������x��0�ɂ���
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _initVel) }) >= 24 ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _initVel) }) >= 24 ||
		CheckHitCube(CHECK_DIR::UP))
	{
		_pos.y = (static_cast<int>(_pos.y) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}

	// �����̉��Ƀu���b�N�������Ȃ�����x��ς���@����Ȃ�Ή����x��0�ɂ���
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x), static_cast<int>(_pos.y + _size.y + _initVel) }) <= 23 &&
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1), static_cast<int>(_pos.y + _size.y + _initVel) }) <= 23)
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
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
		{
			return true;
		}
		break;
	case CHECK_DIR::LEFT:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - 1), static_cast<int>(_gripCube->getPos().y) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x - 1), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y - 1) }) >= 24)
		{
			return true;
		}
		break;
	case CHECK_DIR::UP:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y + _initVel) }) >= 24 ||
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y + _initVel) }) >= 24)
		{
			return true;
		}
		break;
	case CHECK_DIR::DOWN:
		if (StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) }) <= 23 &&
			StageMngIns.getStageData({ static_cast<int>(_gripCube->getPos().x + _gripCube->getSize().x - 1), static_cast<int>(_gripCube->getPos().y + _gripCube->getSize().y + _initVel) }) <= 23)
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
