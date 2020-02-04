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
	static std::vector<int> _name;					// ���O�̊i�[

	bool _sceneMoveFlag;					// ���̃V�[���Ɉڍs���邩
	int _scenePos_x;						// ���̃V�[���̍��W

	std::map<int, int> _keyOld;				// 1�t���O�̃L�[���

	bool NameSceneMove(void);				// ���̃V�[���𓮂����֐�
	bool NameSceneUpdate(void);				// ���̃V�[���̏���

	bool (NameSelectScene::*_update)(void);	// ��Q�̊֐��̊֐��|�C���^

	int keyUpdate(int key);					// �L�[��Ԃ̊Ǘ�
	void Draw(void);						// �`��
};

