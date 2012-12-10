#pragma once
#include "BaseObject.h"
class Enemy : public BaseObject
{
public:
	Enemy(int ID);
	Enemy(Ogre::String name, Ogre::String mesh, int ID);
	Ogre::String getName();
	Ogre::String getMeshName();
	virtual void Scene();

	~Enemy(void);
};

