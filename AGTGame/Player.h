#pragma once

#include "BaseObject.h"


class Player : BaseObject
{
	int xPos;
	int yPos; 
	int zPos;

public:
	Player(int ID);
	Player(Ogre::String name, Ogre::String mesh, int ID);
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
	void animate(const Ogre::FrameEvent& evt);
	void attackAnimation(const Ogre::FrameEvent& evt);
	void jumpAnimation(const Ogre::FrameEvent& evt);
	~Player();
};


