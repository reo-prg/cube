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

// �v���C���[�̃A�j���[�V�����̎��
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
	void setStage(int count);			// �X�e�[�W�̐ݒ�
private:
	friend class StageMng;
	friend struct CanGripCube;
	friend struct CheckHitObj;

	bool clearCheck(void);				// �N���A�����̂����`�F�b�N

	// �v���C���[�̃A�j���[�V����
	bool moveFall(void);				// ������
	bool moveUp(void);					// �オ��
	bool moveLR(void);					// ��]
	
	int _count;											// �A�j���[�V�����p�t���[���J�E���^
	std::vector<std::pair<OBJ_STATS, int>> _LRAnim;		// ��]�A�j���[�V����
	int _animCount;										// ���݂̃A�j���[�V����

	bool (GameScene::*_plMove)(void);					// �A�j���[�V�����̊֐��|�C���^

	bool objUpdate(void);				// �v���C���̏���	
	bool animUpdate(void);				// �A�j���[�V�������̏���
	
	bool (GameScene::*_update)(void);	// ��2�̊֐��|�C���^

	void Draw(void);

	unsigned int _stageCount;			// ���݂̃X�e�[�W��
	bool _keyOldR;						// R�L�[��1�t���O�̏��

	// �Q�[���J�n���ԂƏI������
	steady_clock::time_point _startTime;
	steady_clock::time_point _clearTime;

	static std::vector<std::shared_ptr<object>> _objList;	// �I�u�W�F�N�g��sharedptr���i�[
};

