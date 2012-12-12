#include "Enemy.h"


Enemy::Enemy(int ID):BaseObject(ID)
{
	type = TYPE_ENEMY;
}

Enemy::Enemy(Ogre::String name, Ogre::String mesh, int ID):BaseObject(name, mesh, ID)
{
	type = TYPE_ENEMY;
}

Ogre::String Enemy::getName()
{
	return pName;
}

Ogre::String Enemy::getMeshName()
{
	return pMesh;
}

void Enemy::Scene()
{

}

Enemy::~Enemy(void)
{
}
