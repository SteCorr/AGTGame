#pragma once
#include "BaseObject.h"
class Enemy : public BaseObject
{
public:
	Enemy(void);
	Enemy(Ogre::String name, Ogre::String mesh);
	Ogre::String getName();
	Ogre::String getMeshName();
	virtual void Scene();

	~Enemy(void);
};

