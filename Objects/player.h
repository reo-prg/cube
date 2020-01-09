#pragma once
#include <Objects/object.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>

#define PL_G_ACC 0.4		// 重力加速度
#define JUMP_DELEY	5		// ジャンプの間隔(時間w)

class player :
	public object
{
public:
	player();
	player(Vector2Template<double> pos, double rad, Vector2Template<int> size);
	~player();

	void Update(void);
private:
	Vector2Template<int> _stickInput;
	int _padInput;

	double _initVel;		// 初速
	int _jumpDeley;			// 次ジャンプできるようになるための間隔
	void control(void);
	void velUpdate(void);	
};

