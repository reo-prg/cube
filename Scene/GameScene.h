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

	bool clearCheck(void);				// �N���A�����̂����`�F�b�N

	bool moveFall(void);
	bool moveUp(void);
	bool moveLR(void);
	
	int _count;											// �A�j���[�V�����p�t���[���J�E���^
	std::vector<std::pair<OBJ_STATS, int>> _LRAnim;		// ��]�A�j���[�V����
	int _animCount;										// ���݂̃A�j���[�V����

	bool (GameScene::*_plMove)(void);

	bool objUpdate(void);
	bool animUpdate(void);

	bool (GameScene::*_update)(void);

	void Draw(void);

	unsigned int _stageCount;		// ���݂̃X�e�[�W��
	bool _keyOldR;					// R�L�[��1�t���O�̏��

	static std::vector<std::shared_ptr<object>> _objList;	// �I�u�W�F�N�g��sharedptr���i�[
};

