#pragma once
#include <Scene/BaseScene.h>

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();

	Base_unq Update(Base_unq scene);
};

