#include "Enemy.h"


Enemy::Enemy(int ID)
{
	type = TYPE_ENEMY;
	id = ID;
}

Enemy::Enemy(Ogre::String name, Ogre::String mesh, int ID)
{
	type = TYPE_ENEMY;
	pName = name;
	pMesh = mesh;
	id = ID;
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
