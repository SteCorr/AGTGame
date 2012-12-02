#ifndef _BaseObject_h_
#define _BaseObject_h_

#include <iostream>

#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <OgreEntity.h>

using namespace std;

class BaseObject : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	Ogre::String pName;
	Ogre::String pMesh;
	Ogre::Entity* entity;
	Ogre::AnimationState* mAnimationState;
	Ogre::SceneNode* pNode;
	BaseObject(){};
	virtual void Scene()=0;
	BaseObject(Ogre::String name,Ogre::String mesh){};
};

#endif //ifndef _BaseObject_h_