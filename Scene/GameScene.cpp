#include <Scene/GameScene.h>

std::vector<std::shared_ptr<object>> GameScene::_objList;

GameScene::GameScene()
{
}

GameScene::GameScene(int stage)
{
	_keyOldR = false;
	StageMngIns.UpdateStagecount(stage);
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

	if (clearCheck())
	{
		scene = std::make_unique<StageSelectScene>();
		_objList.clear();
	}

	return std::move(scene);
}

void GameScene::setStage(int count)
{
	_stageCount = count;
}

bool GameScene::clearCheck(void)
{
	auto pl_data = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<object> data) { return data->getType() == OBJ_TYPE::PLAYER; });
	if (pl_data == _objList.end())
	{
		AST();
		return false;
	}

	if (StageMngIns.getStageData({ static_cast<int>((*pl_data)->getPos().x + (*pl_data)->getSize().x / 2), static_cast<int>((*pl_data)->getPos().y + (*pl_data)->getSize().y / 2) }) >= 0 &&
		StageMngIns.getStageData({ static_cast<int>((*pl_data)->getPos().x + (*pl_data)->getSize().x / 2), static_cast<int>((*pl_data)->getPos().y + (*pl_data)->getSize().y / 2) }) <= 3)
	{
		return true;
	}
	return false;
}
