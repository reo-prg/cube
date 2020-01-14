#include <Scene/GameScene.h>

std::vector<std::shared_ptr<object>> GameScene::_objList;

GameScene::GameScene()
{
	StageMngIns.UpdateStagecount(0);
}


GameScene::~GameScene()
{
}

Base_unq GameScene::Update(Base_unq scene)
{
	for (auto data : _objList)
	{
		data->Update();
	}
	
	for (auto data : _objList)
	{
		data->objDraw();
	}

	StageMngIns.Update();

	return std::move(scene);
}
