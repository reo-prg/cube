#include <Scene/GameScene.h>

std::vector<std::shared_ptr<object>> GameScene::_objList;

GameScene::GameScene()
{
	_stageCount = 0;
	_keyOldR = false;
	StageMngIns.UpdateStagecount(_stageCount);
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

	if (CheckHitKey(KEY_INPUT_R) && (!_keyOldR))
	{
		StageMngIns.resetObj();
	}
	_keyOldR = CheckHitKey(KEY_INPUT_R);

	StageMngIns.Update();

	return std::move(scene);
}
