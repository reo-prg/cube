#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>
#include <Scene/BaseScene.h>
#include <Scene/TitleScene.h>
#include <Scene/CharSelectScene.h>
#include <Scene/GameScene.h>
#include <Scene/NameSelectScene.h>

#define SceneMngIns SceneMng::getInstance()

class SceneMng
{
public:
	// Singleton
	static SceneMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);				// �Q�[�����[�v

	int GetPad(void)const;							// ���݂̃Q�[���p�b�h�̏�Ԃ�n��
	int GetPadOld(void)const;						// 1�t���O�̃Q�[���p�b�h�̏�Ԃ�n��
	Vector2Template<int> GetStick(void)const;		// ���݂̃A�i���O�X�e�B�b�N�̏�Ԃ�n��
	Vector2Template<int> GetStickOld(void)const;	// 1�t���O�̃A�i���O�X�e�B�b�N�̏�Ԃ�n��

	void StartVib(int pad, int power, int time)const;	// �Q�[���p�b�h��U��������

	const Vector2Template<int> ScreenSize;			// ��ʂ̑傫��
	const Vector2Template<int> ScreenCenter;		// ��ʂ̒���
private:
	static SceneMng* sInstance;
	int _padInput;					// ���݂̃Q�[���p�b�h�̏��
	int _padInputOld;				// 1�t���O�̃Q�[���p�b�h�̏��
	Vector2Template<int> _stick;	// ���݂̃A�i���O�X�e�B�b�N�̏��
	Vector2Template<int> _stickOld;	// 1�t���O�̃A�i���O�X�e�B�b�N�̏��

	Base_unq _runScene;				// ���݂̃V�[��

	bool SystemInit(void);			// ������
	void UpdatePad(void);			// �Q�[���p�b�h�̏�Ԃ̍X�V

	SceneMng();
	~SceneMng();
};

