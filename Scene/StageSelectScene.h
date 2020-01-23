#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>

#define STAGE_SPACE		60
#define STAGE_SIZE_X	128
#define STAGE_SIZE_Y	96
#define STAGE_OFFSET	(SceneMngIns.ScreenCenter.x - (STAGE_SIZE_X + STAGE_SPACE) * 3 / 2)


class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _stagePos_x;					// ステージの座標
	int _cursor;						// カーソル
	bool _sceneMoveFlag;				// 場面を変えるかどうか
	Base_unq _tmpScene;					// 一時的に次のシーンを保持
	int _stageViewScreen;					// スクリーン

	std::map<int, int> _keyOld;			// 1フレ前のキー状態

	Base_unq stageMove(Base_unq);
	Base_unq stageSelect(Base_unq);

	Base_unq (StageSelectScene::*_stageSel)(Base_unq);

	int keyUpdate(int);
	void Draw();
};

