#pragma once
#include <Objects/object.h>

#define CB_G_ACC 0.2 // �L���[�u�̏d�͉����x

class FallCube :
	public object
{
public:
	FallCube();
	FallCube(Vector2Template<int> pos, Vector2Template<int> size);
	~FallCube();

	void Update(void)override;
	void velUpdate(void);
};

