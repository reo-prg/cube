#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <tuple>
#include <Graphic/LAYER.h>
#include <common/Vector2.h>

// �`��f�[�^�̗v�f
enum class DrawElm
{
	ID,
	X,
	Y,
	RAD,
	LAYER,
	ZORDER
};

// �G�t�F�N�g�̎��
enum class EFFECT
{
	SMOKE,
	GRIP
};

#define ImageMngIns ImageMng::getInstance()

using DrawData = std::tuple<int, int, int, double, LAYER, int>;	// �`��p�f�[�^�@�摜ID, ���Wx, y, �p�x, ���C���[, z�I�[�_�[

class ImageMng
{
public:
	static ImageMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ImageMng();
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

	void setEffect(EFFECT effect, Vector2Template<int> pos);

	std::vector<int> getImage(const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y);

	void Draw(void);				// �`��
	void UpdateEffect(void);		// �G�t�F�N�g�̕`��ƍX�V

	void AddDraw(DrawData data);	// �`����̒ǉ�

private:
	static ImageMng* sInstance;								// �C���X�^���X

	std::map<std::string, std::vector<int>> _imageMap;					// �摜ID�ۑ��p
	std::map<EFFECT, std::vector<std::pair<int, int>>>	_effectMap;		// �G�t�F�N�g�ۑ��p

	std::vector<DrawData> _drawList;						// �`����ۑ��p
	std::vector<std::tuple<EFFECT, Vector2Template<int>, int, int>> _effectList;		// �i�s���̃G�t�F�N�g

	ImageMng();
	~ImageMng();
};

