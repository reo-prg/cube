#pragma once
#include <DxLib.h>
#include <vector>
#include <Graphic/ImageMng.h>
#include <Scene/SceneMng.h>
#include <_debug/_DebugConOut.h>
#include <Objects/LockCube.h>
#include <Objects/FallCube.h>

#define StageMngIns StageMng::getInstance()

#define StageHeight	24		// �X�e�[�W�̏c�}�X��
#define StageWidth	32		// �X�e�[�W�̉��}�X��
#define CubeSize	32		// �L���[�u�̑傫��

#define PLAYER_OFFSET	-800	// �v���C���[�̏o���ʒu�̃I�t�Z�b�g

class StageMng
{
public:

	static StageMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new StageMng();
		}
		return *sInstance;
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	void Update(void);
	void UpdateStagecount(int count);			// �ʂ̃X�e�[�W�ɍX�V
	
	int getStageData(Vector2Template<int> val);	// ����̃}�X�ɔ��肪���邩
	int getPlayerColor(void);					// �v���C���[�̐F��n��

	void setPlayerColor(int);					// �v���C���[�̐F���󂯎��
	void resetObj(void);						// �X�e�[�W��������Ԃɖ߂�
private:
	static StageMng* sInstance;

	int _stageData[StageHeight][StageWidth];						// �X�e�[�W�̏���ۑ�
	int _stageScreen;												// �X�e�[�W�p�̃X�N���[��
	std::vector<std::pair<Vector2Template<int>, int>> _objInitPos;	// �I�u�W�F�N�g�̏����ʒu��ۑ�
	
	int _playerColor;												// �v���C���[�̐F

	// �X�e�[�W�f�[�^�̃p�X
	const std::vector<std::string> fileName = { "data/stage_0.csv", "data/stage_1.csv", "data/stage_2.csv","data/stage_3.csv", 
												"data/stage_4.csv", "data/stage_5.csv", "data/stage_6.csv", "data/stage_7.csv", };

	StageMng();
	~StageMng();
};

