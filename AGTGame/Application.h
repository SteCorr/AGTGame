
#ifndef __Application_h_
#define __Application_h_
 
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include <OgreMeshManager.h>

 
class Application : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
    Application(void);
	bool worldConfig();
	void createScene();
	void createCamera();
	void createViewpoint();
	void createLight();
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