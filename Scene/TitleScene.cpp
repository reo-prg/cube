#include <Scene/TitleScene.h>




TitleScene::TitleScene()
{
	// ������
	_keyAllOld = 1;
	_theta = 0;
	_sceneMoveFlag = false;
	_mesMoveFlag = true;
	_mesPos_x = -MES_SIZE_X;
}


TitleScene::~TitleScene()
{
}

Base_unq TitleScene::Update(Base_unq scene)
{
	// ���������ꂽ��L�����I����
	if (!_mesMoveFlag)
	{
		if ((CheckHitKeyAll() > 0 && _keyAllOld == 0) || (SceneMngIns.GetPad() != 0 && SceneMngIns.GetPadOld() == 0))
		{
			_sceneMoveFlag = true;
			_mesMoveFlag = true;
		}
	}
	else
	{
		scene = mesMove(std::move(scene));
	}
	// ���݂̃L�[��Ԃ̕ۑ�
	_keyAllOld = CheckHitKeyAll();

	Draw();

	// ���b�Z�[�W���㉺�ɓ������p
	_theta = (_theta + 6) % 360;

	return std::move(scene);
}

Base_unq TitleScene::mesMove(Base_unq scene)
{
	_mesPos_x += 10;
	
	// �^�C�g���ɓ��������Ǝ��ɍs���Ƃ��̃A�j���[�V��������
	if (!_sceneMoveFlag)
	{
		if (_mesPos_x >= SceneMngIns.ScreenCenter.x)
		{
			_mesPos_x = SceneMngIns.ScreenCenter.x;
			_mesMoveFlag = false;
		}
	}
	else
	{
		if (_mesPos_x >= SceneMngIns.ScreenSize.x + MES_SIZE_X / 2)
		{
			return std::make_unique<NameSelectScene>();
		}
	}

	return std::move(scene);
}

void TitleScene::Draw(void)
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("logo")[0], _mesPos_x, SceneMngIns.ScreenCenter.y - 70, 0.0, LAYER::UI, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleMes")[0], _mesPos_x, 600 - static_cast<int>(std::sin(RAD(_theta)) * 60), 0.0, LAYER::UI, 10 });
}
