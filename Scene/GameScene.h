#pragma once
#include <vector>
#include <algorithm>
#include <Scene/BaseScene.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <Objects/object.h>
#include <Objects/player.h>
#include <func/CanGripCube.h>
#include <func/CheckHitObj.h>

class GameScene :
	public BaseScene
{
public:
	GameScene();
	GameScene(int stage);
	~GameScene();

	Base_unq Update(Base_unq);
	void setStage(int);
private:
	friend class StageMng;
	friend struct CanGripCube;
	friend struct CheckHitObj;

	bool clearCheck(void);				// クリアしたのかをチェック

	unsigned int _stageCount;		// 現在のステージ数
	bool _keyOldR;					// Rキーの1フレ前の状態

	static std::vector<std::shared_ptr<object>> _objList;	// オブジェクトのsharedptrを格納
};

