#include "Enemy.h"


Enemy::Enemy(void)
{
}

Enemy::Enemy(Ogre::String name, Ogre::String mesh)
{
	pName = name;
	pMesh = mesh;
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
