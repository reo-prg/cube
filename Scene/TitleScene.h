#pragma once
#include <Scene/BaseScene.h>

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	Base_unq Update(Base_unq scene);
};

