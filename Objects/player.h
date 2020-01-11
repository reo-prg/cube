#pragma once
#include <Objects/object.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <func/CanGripCube.h>

#define PL_G_ACC 0.4		// �v���C���[�̏d�͉����x
#define JUMP_DELEY 5		// �W�����v�̊Ԋu(����)

enum class CHECK_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class player :
	public object
{
public:
	player();
	player(Vector2Template<double> pos, double rad, Vector2Template<int> size);
	~player();

	void Update(void)override;
private:
	Vector2Template<int> _stickInput;
	int _padInput;

	double _initVel;					// ����
	int _jumpDeley;						// ���W�����v�ł���悤�ɂȂ邽�߂̊Ԋu
	std::shared_ptr<object> _gripCube;	// �͂�ł���L���[�u

	void control(void);
	void velUpdate(void);
	bool CheckHitCube(CHECK_DIR);
};

