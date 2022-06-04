#include "Weapon.h"
#include "../../Engine/Video/ResourceManager.h"

Weapon::Weapon(int id)
{
	ID = id;
	
	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/bala1.png"), Transform.w, Transform.h);

	switch (id)
	{
	case 0:
		//missil
		Ammo = -1;
		break;
	case 1:
		//rifle
		Ammo = 2;
		break;
	case 2:
		//granada
		Ammo = 2;
		break;
	case 3:
		//atac aeri
		Ammo = 0;
		break;
	default:
		break;
	}
}

Projectile* Weapon::shoot()
{
	pProjectile = new Projectile(ID);
	pProjectile->setTransform(this->Transform.x, this->Transform.y);
	return pProjectile;
}
