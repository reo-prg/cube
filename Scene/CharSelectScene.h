#pragma once
#include <Scene/BaseScene.h>


class CharSelectScene :
	public BaseScene
{
public:
	CharSelectScene();
	~CharSelectScene();

	Base_unq Update(Base_unq scene);
};

