#pragma once
#include <vector>
#include <chrono>
#include <algorithm>
#include <Scene/BaseScene.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <Objects/object.h>
#include <Objects/player.h>
#include <func/CanGripCube.h>
#include <func/CheckHitObj.h>

using namespace std::chrono;

#define RESULT_MOVE_OFFSET	600

// プレイヤーのアニメーションの種類
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

	Base_unq Update(Base_unq scene);
	void setStage(int count);			// ステージの設定
private:
	friend class StageMng;
	friend struct CanGripCube;
	friend struct CheckHitObj;

	bool clearCheck(void);				// クリアしたのかをチェック

	
	int _count;											// アニメーション,リザルト用フレームカウンタ
	std::vector<std::pair<OBJ_STATS, int>> _LRAnim;		// 回転アニメーション
	int _animCount;										// 現在のアニメーション

	// プレイヤーのアニメーション
	bool moveFall(void);				// 落ちる
	bool moveUp(void);					// 上がる
	bool moveLR(void);					// 回転

	bool (GameScene::*_plMove)(void);	// 上3つのアニメーションの関数ポインタ

	int _keySpaceOld;					// 1フレ前のスペースキーの状態
	int _theta;							// リザルト移動用

	bool moveResult(void);				// リザルト画面の移動
	bool resultScene(void);				// リザルト画面の処理

	bool(GameScene::*_result)(void);	// 上2つの関数ポインタ

	bool objUpdate(void);				// プレイ中の処理	
	bool animUpdate(void);				// アニメーション中の処理
	bool resultUpdate(void);			// リザルトの処理
	
	bool (GameScene::*_update)(void);	// 上3つの関数ポインタ

	void Draw(void);

	unsigned int _stageCount;			// 現在のステージ数
	bool _keyOldR;						// Rキーの1フレ前の状態

	// ゲーム開始時間と終了時間
	steady_clock::time_point _startTime;
	steady_clock::time_point _clearTime;

	static std::vector<std::shared_ptr<object>> _objList;	// オブジェクトのsharedptrを格納
};

