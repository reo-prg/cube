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

enum class PL_ANIM
{
	FALL,
	UP,
	LR
};

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

	bool moveFall(void);
	bool moveUp(void);
	bool moveLR(void);
	
	int _count;											// アニメーション用フレームカウンタ
	std::vector<std::pair<OBJ_STATS, int>> _LRAnim;		// 回転アニメーション
	int _animCount;										// 現在のアニメーション

	bool (GameScene::*_plMove)(void);

	bool objUpdate(void);
	bool animUpdate(void);

	bool (GameScene::*_update)(void);

	void Draw(void);

	unsigned int _stageCount;		// 現在のステージ数
	bool _keyOldR;					// Rキーの1フレ前の状態

	static std::vector<std::shared_ptr<object>> _objList;	// オブジェクトのsharedptrを格納
};

