
#ifndef __Application_h_
#define __Application_h_
 
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreBitwise.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "OcTree.h" 

#include <OgreMeshManager.h>

const int MAP_X = 32;
const int MAP_Z = 32;
const float MAP_Y = 255.0f;  //max y hgt
const float MAP_SCALE = 32.0f;  //scale
const int NBR_LEVELS = 1;

 
class Application : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	OcTree* tree;
    Application(void);
	bool worldConfig();
	void createScene();
	void createCamera();
	void createViewpoint();
	void createLight();
	void UpdateCamera();

    virtual ~Application(void);
    bool go(void);
 
protected:
    // Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
 
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
 
private:
    Ogre::Root* mRoot;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;
	Ogre::SceneNode* pNode;
	Ogre::FrameListener* pFrameListener;
	
 
    // OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

	Player* p;
	Enemy* e;
	
};
 
#endif // 