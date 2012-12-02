#include "Player.h"


Player::Player(void)
{
}

Player::Player(Ogre::String name, Ogre::String mesh)
{
	pName = name;
	pMesh = mesh;
}

Ogre::String Player::getName()
{
	return pName;
}

Ogre::String Player::getMeshName()
{
	return pMesh;
}

void Player::setPos(int X, int Y, int Z)
{
	xPos = X;
	yPos = Y;
	zPos = Z;
}

int Player::getXpos()
{
	return xPos;
}

int Player::getYpos()
{
	return yPos;
}

int Player::getZpos()
{
	return zPos;
}

Ogre::Vector3 Player::moveForward()
{
	return Ogre::Vector3(0,0,-10);
}

Ogre::Vector3 Player::moveBack()
{
	return Ogre::Vector3(0,0,10);
}

Ogre::Vector3 Player::moveRight()
{
	return Ogre::Vector3(10,0,0);
}

Ogre::Vector3 Player::moveLeft()
{
	return Ogre::Vector3(-10,0,0);
}

void Player::Scene()
{
	
}

Player::~Player()
{
}
