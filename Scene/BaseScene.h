#pragma once
#include <memory>

class BaseScene;

using Base_unq = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual Base_unq Update(Base_unq scene) = 0;

};

