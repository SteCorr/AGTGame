#pragma once
#include "BaseObject.h"

class Terrian: public BaseObject
{
public:
	Terrian(int id);
	Terrian(Ogre::String name, Ogre::String mesh, int id);
	void Scene();
	~Terrian();
};

