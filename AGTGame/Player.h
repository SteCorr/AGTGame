#pragma once

#include "BaseObject.h"


class Player:public BaseObject
{
	int xPos;
	int yPos; 
	int zPos;
	Ogre::String pName;
	Ogre::String pMesh;
	OIS::Keyboard* pKeyboard;

public:
	Ogre::Vector3 translate;
	Player(void);
	Player(Ogre::String name, Ogre::String mesh);
	Ogre::String getName();
	Ogre::String getMeshName();
	void setPos(int X, int Y, int Z);
	int getXpos();
	int getYpos();
	int getZpos();
	Ogre::Vector3 moveForward();
	Ogre::Vector3 moveBack();
	Ogre::Vector3 moveLeft();
	Ogre::Vector3 moveRight();
	void Scene();
	~Player(void);
};


