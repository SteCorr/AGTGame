#pragma once
#include "BaseObject.h"

class Terrian: public BaseObject
{
public:
	Terrian();
	Terrian(Ogre::String name, Ogre::String mesh);
	void Scene();
	~Terrian();
};

