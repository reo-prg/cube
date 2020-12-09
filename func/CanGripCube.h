#pragma once
#include <Objects/player.h>
#include <Scene/GameScene.h>


struct CanGripCube
{
public:
	std::shared_ptr<object> operator()(class player&);
};

