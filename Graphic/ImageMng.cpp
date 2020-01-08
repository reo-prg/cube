#include <algorithm>
#include <Graphic/ImageMng.h>

ImageMng* ImageMng::sInstance = nullptr;

std::vector<int> ImageMng::getImage(const std::string& key)
{
	return getImage(key,key);
}

std::vector<int> ImageMng::getImage(const std::string& filename, const std::string& key)
{
	if (_imageMap.find(key) == _imageMap.end())
	{
		_imageMap[key].resize(1);
		_imageMap[key][0] = (key, LoadGraph(filename.c_str(), true));
	}

	return _imageMap[key];
}

std::vector<int> ImageMng::getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y)
{
	if (_imageMap.find(key) == _imageMap.end())
	{
		_imageMap[key].resize(cnt_x * cnt_y);
		LoadDivGraph(filename.c_str(), cnt_x * cnt_y, cnt_x, cnt_y, size_x, size_y, &_imageMap[key][0], true);
	}
	return _imageMap[key];
}

void ImageMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// レイヤーとzオーダーでソート
	std::sort(_drawList.begin(), _drawList.end(), [](DrawData i,DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});


	for (auto data : _drawList)
	{
		int id, x, y;
		double rad;
		LAYER layer;

		std::tie(id, x, y, rad, layer, std::ignore) = data;

		DrawRotaGraph(x, y, 1.0, rad, id, true);
	}

	ScreenFlip();

	_drawList.clear();
}

void ImageMng::AddDraw(DrawData data)
{
	_drawList.emplace_back(data);
}

ImageMng::ImageMng()
{
	
}


ImageMng::~ImageMng()
{
}




