#pragma once
#include <Scene/BaseScene.h>


class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	Base_unq Update(Base_unq scene);
private:


	void Draw();
};

