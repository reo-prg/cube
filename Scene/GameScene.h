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

	bool clearCheck(void);				// �N���A�����̂����`�F�b�N

	unsigned int _stageCount;		// ���݂̃X�e�[�W��
	bool _keyOldR;					// R�L�[��1�t���O�̏��

	static std::vector<std::shared_ptr<object>> _objList;	// �I�u�W�F�N�g��sharedptr���i�[
};

