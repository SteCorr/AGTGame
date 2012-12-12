#include "Player.h"


Player::Player(int ID):BaseObject(ID)
{
	type = TYPE_PLAYER;
}

Player::Player(Ogre::String name, Ogre::String mesh, int ID):BaseObject( name, mesh, ID)
{
	type = TYPE_PLAYER;
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

void Player::animate(const Ogre::FrameEvent& evt)
{
	mAnimationState = entity->getAnimationState("RunBase");
	mAnimationState2 = entity->getAnimationState("RunTop");
	mAnimationState->setLoop(true);
	mAnimationState2->setLoop(true);
	mAnimationState->setEnabled(true);
	mAnimationState2->setEnabled(true);
	mAnimationState->addTime(evt.timeSinceLastFrame);
	mAnimationState2->addTime(evt.timeSinceLastFrame);
}

void Player::attackAnimation(const Ogre::FrameEvent& evt)
{
	mAttack = entity->getAnimationState("SliceVertical");
	mAttack->setLoop(true);
	mAttack->setEnabled(true);
	mAttack->addTime(evt.timeSinceLastFrame);
}

void Player::jumpAnimation(const Ogre::FrameEvent& evt)
{
	mJump = entity->getAnimationState("JumpStart");
	mJump->setLoop(true);
	mJump->setEnabled(true);
	mJump->addTime(evt.timeSinceLastFrame);
}

Player::~Player()
{
}
