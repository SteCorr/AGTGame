#pragma once

#include <iostream>
#include "vector.h"
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <OgreEntity.h>
#include "OcPart.h"

using namespace std;

const int TYPE_PLAYER = 0;
const int TYPE_ENEMY = 1;
const int TYPE_PICKUP =2;

class BaseObject : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	int id;
	bool colPlayer;
	int type;
	Vector vel;
	Ogre::String pName;
	Ogre::String pMesh;
	Ogre::Entity* entity;
	OcPart *part; 
	Ogre::SceneNode* pNode;
	BaseObject(int ID);
	virtual void Scene()=0;
	int getID();
	bool collidesWith(BaseObject* obj);
	int getType();
	void collided();
	BaseObject(Ogre::String name, Ogre::String mesh, int ID);
};
