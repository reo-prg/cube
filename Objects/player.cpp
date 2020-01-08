#include "player.h"



player::player()
{
}

player::player(Vector2Template<double> pos, double rad)
{
	_pos = pos;
	_rad = rad;
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
	if (_stickInput.x > 300)
	{
		_pos.x += _stickInput.x / 100;
	}
	if (_stickInput.x < -300)
	{
		_pos.x += _stickInput.x / 100;
	}

	if (StageMngIns.getStageData((static_cast<int>(_pos.y) / BlockSize) * StageWidth + (static_cast<int>(_pos.x + 32) / BlockSize)) ||
		StageMngIns.getStageData((static_cast<int>(_pos.y + 31) / BlockSize) * StageWidth + (static_cast<int>(_pos.x + 32) / BlockSize)))
	{
		_pos.x = (static_cast<double>(static_cast<int>(_pos.x + 32) / BlockSize - 1) * BlockSize);
	}
	if (StageMngIns.getStageData((static_cast<int>(_pos.y) / BlockSize) * StageWidth + (static_cast<int>(_pos.x - 1) / BlockSize)) ||
		StageMngIns.getStageData((static_cast<int>(_pos.y + 31) / BlockSize) * StageWidth + (static_cast<int>(_pos.x - 1) / BlockSize)))
	{
		_pos.x = static_cast<double>((static_cast<int>(_pos.x - 1) / BlockSize + 1) * BlockSize);
	}

	if ((_padInput & PAD_INPUT_2) != 0 &&
		_jumpDeley <= 0 &&
		(StageMngIns.getStageData((static_cast<int>(_pos.y + 32) / BlockSize) * StageWidth + (static_cast<int>(_pos.x) / BlockSize)) ||
		StageMngIns.getStageData((static_cast<int>(_pos.y + 32) / BlockSize) * StageWidth + (static_cast<int>(_pos.x + 31) / BlockSize))))
	{
		_initVel = -10.0;
	}
}

void player::velUpdate(void)
{
	// 自分の上のブロックにぶつかったら加速度を0にする
	if ((StageMngIns.getStageData(static_cast<int>(_pos.y + _initVel) / BlockSize * StageWidth + (static_cast<int>(_pos.x) / BlockSize)) == 1) ||
		(StageMngIns.getStageData(static_cast<int>(_pos.y + _initVel) / BlockSize * StageWidth + (static_cast<int>(_pos.x + 31) / BlockSize)) == 1))
	{
		_pos.y = (static_cast<int>(_pos.y) / BlockSize) * BlockSize;
		_initVel = 0.0;
	}

	// 自分の下にブロックが無いなら加速度を変える 無いならば加速度を0にする
	if ((StageMngIns.getStageData(static_cast<int>(_pos.y + 32 + _initVel) / BlockSize * StageWidth + (static_cast<int>(_pos.x) / BlockSize))== 0) &&
		(StageMngIns.getStageData(static_cast<int>(_pos.y + 32 + _initVel) / BlockSize * StageWidth + (static_cast<int>(_pos.x + 31) / BlockSize)) == 0))
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
