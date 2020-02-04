#pragma once
#include <DxLib.h>
#include <vector>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Graphic/ImageMng.h>

#define CHAR_SIZE		32
#define CHAR_DUR_X		30
#define CHAR_DUR_Y		10
#define CHAR_OFFSET_X	(SceneMngIns.ScreenCenter.x - CHAR_SIZE * 5 -  CHAR_DUR_X * 4.5)
#define CHAR_OFFSET_Y	230
#define CHAR_COUNT_X	10
#define CHAR_COUNT_Y	10

#define NAME_OFFSET_X	(SceneMngIns.ScreenCenter.x - CHAR_SIZE * 3)
#define NAME_OFFSET_Y	150
#define NAME_COUNT_MAX	6


class NameSelectScene :
	public BaseScene
{
public:
	NameSelectScene();
	~NameSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _nameScreen;
	Vector2Template<int> _cursor;
	int _charCount;
	static std::vector<int> _name;					// 名前の格納

	bool _sceneMoveFlag;					// 次のシーンに移行するか
	int _scenePos_x;						// このシーンの座標

	std::map<int, int> _keyOld;				// 1フレ前のキー状態

	bool NameSceneMove(void);				// このシーンを動かす関数
	bool NameSceneUpdate(void);				// このシーンの処理

	bool (NameSelectScene::*_update)(void);	// 上２つの関数の関数ポインタ

	int keyUpdate(int key);					// キー状態の管理
	void Draw(void);						// 描画
};

