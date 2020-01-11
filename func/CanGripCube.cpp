#include <func/CanGripCube.h>

std::shared_ptr<object> CanGripCube::operator()(player& pl_obj)
{
	Vector2Template<double> plArmPos = { pl_obj.getPos().x + static_cast<double>(pl_obj.getStats()) * 56 - 12, pl_obj.getPos().y + pl_obj.getSize().x / 2 };

	

	for (auto data : GameScene::_objList)
	{
		if (data->getType() != OBJ_TYPE::PLAYER)
		{
			int cubeSizeY = data->getSize().y;
			if ((StageMngIns.getStageData({ static_cast<int>(data->getPos().x) / BlockSize, static_cast<int>(data->getPos().y + data->getSize().y) / BlockSize })== 1) ||
				(StageMngIns.getStageData({ static_cast<int>(data->getPos().x + data->getSize().x - 1) / BlockSize, static_cast<int>(data->getPos().y + data->getSize().y) / BlockSize })== 1))
			{
				cubeSizeY = cubeSizeY / 2 + 1;
			}
			if (plArmPos.x >= data->getPos().x && plArmPos.x < data->getPos().x + data->getSize().x &&
				plArmPos.y >= data->getPos().y && plArmPos.y < data->getPos().y + cubeSizeY)
			{
				data->setGrip(true);
				pl_obj.setGrip(true);
				return data;
			}
		}
	}
	return nullptr;
}
