#pragma once
#include <Objects/object.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>

#define PL_G_ACC 0.4		// �d�͉����x
#define JUMP_DELEY	5		// �W�����v�̊Ԋu(����w)

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

	double _initVel;		// ����
	int _jumpDeley;			// ���W�����v�ł���悤�ɂȂ邽�߂̊Ԋu
	void control(void);
	void velUpdate(void);	
};

