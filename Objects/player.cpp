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

	if (_jumpDeley > 0)
	{
		_jumpDeley--;
	}
}

void player::control(void)
{
	_padInput = GetJoypadInputState(DX_INPUT_PAD1);
	GetJoypadAnalogInput(&_stickInput.x, &_stickInput.y, DX_INPUT_PAD1);
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


	if (StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x) / BlockSize, static_cast<int>(_pos.y) / BlockSize }) ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x) / BlockSize, static_cast<int>(_pos.y + _size.y - 1) / BlockSize }))
	{
		_pos.x = (static_cast<double>(static_cast<int>(_pos.x + _size.x) / BlockSize - 1) * BlockSize);
	}
	if (StageMngIns.getStageData({ static_cast<int>(_pos.x - 1) / BlockSize, static_cast<int>(_pos.y) / BlockSize }) ||
		StageMngIns.getStageData({ static_cast<int>(_pos.x - 1) / BlockSize, static_cast<int>(_pos.y + _size.y - 1) / BlockSize }))
	{
		_pos.x = static_cast<double>((static_cast<int>(_pos.x - 1) / BlockSize + 1) * BlockSize);
	}

	if (((_padInput & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_SPACE))&&
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
		StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1) / BlockSize, static_cast<int>(_pos.y + _initVel) / BlockSize }))
	{
		_pos.y = (static_cast<int>(_pos.y) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}

	// 自分の下にブロックが無いなら加速度を変える 無いならば加速度を0にする
	if ((StageMngIns.getStageData({ static_cast<int>(_pos.x) / BlockSize, static_cast<int>(_pos.y + _size.y + _initVel) / BlockSize }) == 0) &&
		(StageMngIns.getStageData({ static_cast<int>(_pos.x + _size.x - 1) / BlockSize, static_cast<int>(_pos.y + _size.y + _initVel) / BlockSize }) == 0))
	{
		_initVel += PL_G_ACC;
		_jumpDeley = JUMP_DELEY;
	}
	else
	{
		_pos.y = (static_cast<int>(_pos.y + _initVel) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}

	
	_pos.y += _initVel;
}
