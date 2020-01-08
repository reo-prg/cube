#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <tuple>
#include <Graphic/LAYER.h>

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

	std::vector<int> getImage(const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key);
	std::vector<int> getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y);

	void Draw(void);				// �`��

	void AddDraw(DrawData data);	// �`����̒ǉ�

private:
	static ImageMng* sInstance;								// �C���X�^���X

	std::map<std::string, std::vector<int>> _imageMap;		// �摜ID�ۑ��p

	std::vector<DrawData> _drawList;						// �`����ۑ��p

	ImageMng();
	~ImageMng();
};

