#include <func/CanGripCube.h>

std::shared_ptr<object> CanGripCube::operator()(player& pl_obj)
{
	Vector2Template<double> plArmPos = { pl_obj.getPos().x + static_cast<double>(pl_obj.getStats()) * 56 - 12, pl_obj.getPos().y + pl_obj.getSize().x / 2 };

	

	for (auto data : GameScene::_objList)
	{
		if (data->getType() != OBJ_TYPE::PLAYER)
		{
			if (plArmPos.x >= data->getPos().x && plArmPos.x < data->getPos().x + data->getSize().x &&
				plArmPos.y >= data->getPos().y + 12 && plArmPos.y < data->getPos().y + 20)
			{
				data->setGrip(true);
				pl_obj.setGrip(true);
				pl_obj.setPos({data->getPos().x + pl_obj.getSize().x - (static_cast<int>(pl_obj.getStats()) * (pl_obj.getSize().x + data->getSize().x)),data->getPos().y});
				return data;
			}
		}
	}
	return nullptr;
}
