
#include "Application.h"
 
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include "BaseObject.h"
#include "Player.h"
 
//-------------------------------------------------------------------------------------
Application::Application(void)
    : mRoot(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mWindow(0),
    mSceneMgr(0),
    mCamera(0)
{
	pFrameListener = NULL;
}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;

	if(pFrameListener)
	{
		delete pFrameListener;
	}
}

bool Application::worldConfig()
{
	 // construct Ogre::Root
    mRoot = new Ogre::Root(mPluginsCfg);
 
    // setup resources
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);
 
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

	//mRoot->showConfigDialog();
    // configure
    // Show the configuration dialog and initialise the system
    if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
        return false;
    }
 
    mWindow = mRoot->initialise(true, "Application Render Window");
 
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    // initialise all resource groups
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
    // Create the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	// Create the OcTree for the collisions.
	tree = new OcTree();
	tree->BuildFullTree(NBR_LEVELS, 0, 0, 0, MAP_X*MAP_SCALE, MAP_Y, MAP_Z*MAP_SCALE);
}

void Application::createScene()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//create plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");

	// create player mesh.
	p = new Player("player", "Sinbad.mesh", 1);
	p->setPos(0,0,0);
	// Create an Entity
	p->entity = mSceneMgr->createEntity(p->getName(), p->getMeshName());
	p->pNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", Ogre::Vector3(p->getXpos(), p->getYpos(), p->getZpos()));
	p->pNode->attachObject(p->entity);
	p->pNode->showBoundingBox(p->entity);
	tree->addObject(p);
	//creat enemy mesh
	e = new Enemy("Enemy", "ninja.mesh", 2);
	e->entity = mSceneMgr->createEntity(e->getName(), e->getMeshName());
	e->pNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyNode", Ogre::Vector3(0, 0, 0));
	e->pNode->attachObject(e->entity);
	e->pNode->setScale(0.05f,0.05f,0.05f);
	e->pNode->setPosition(0,-5,0);
	e->pNode->showBoundingBox(e->entity);
	tree->addObject(e);
}

void Application::createCamera()
{
	 // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
	UpdateCamera();
    mCamera->setNearClipDistance(5);
}

void Application::UpdateCamera()
{
	  // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(mSceneMgr->getSceneNode("PlayerNode")->getPosition().x,0,mSceneMgr->getSceneNode("PlayerNode")->getPosition().z + 50));
    // Look back along -Z
	mCamera->lookAt(Ogre::Vector3(mSceneMgr->getSceneNode("PlayerNode")->getPosition().x, mSceneMgr->getSceneNode("PlayerNode")->getPosition().y, mSceneMgr->getSceneNode("PlayerNode")->getPosition().z));
}

void Application::createViewpoint()
{
 // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
 
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void Application::createLight()
{
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);
}
 
bool Application::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
	// World Configaration
	worldConfig();
	// Create a scene 
	createScene();
	// Create a camera
	createCamera();
	// Create a view point
    createViewpoint();
	
    // Create a light
	createLight();
    
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    mInputManager = OIS::InputManager::createInputSystem( pl );
 
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
 
    //Set initial mouse clipping size
    windowResized(mWindow);
 
    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
 
    mRoot->addFrameListener(this);
 
    mRoot->startRendering();
 
    return true;
}
 
//Adjust mouse clipping area
void Application::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
 
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
 
//Unattach OIS before window shutdown (very important under Linux)
void Application::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );
 
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
 
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 translate(0,0,0);

    if(mWindow->isClosed())
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

	// keyboard presses for player movement
	// key press for moving forward
	if(mKeyboard->isKeyDown(OIS::KC_W))
	{
		translate += p->moveForward();
		p->animate(evt);	
		p->pNode->setOrientation(0,0,1,0);
		UpdateCamera();
	}

	// key press for moving backwards
	if(mKeyboard->isKeyDown(OIS::KC_S))
	{
		translate += p->moveBack();
		p->animate(evt);
		p->pNode->resetOrientation();
		UpdateCamera();

	}
	// key press for moving to the left
	if(mKeyboard->isKeyDown(OIS::KC_A))
	{
		translate += p->moveLeft();
		p->animate(evt);
		p->pNode->setOrientation(-1,0,1,0);
		UpdateCamera();
	}
	// key press for moving to the right
	if(mKeyboard->isKeyDown(OIS::KC_D))
	{
		translate += p->moveRight();
		p->animate(evt);
		p->pNode->setOrientation(1,0,1,0);
		UpdateCamera();
	}
	if(mKeyboard->isKeyDown(OIS::KC_W) && mKeyboard->isKeyDown(OIS::KC_D))
	{
		p->animate(evt);
		p->pNode->setOrientation(1,0,2,0);
		UpdateCamera();
	}
	if(mKeyboard->isKeyDown(OIS::KC_W) && mKeyboard->isKeyDown(OIS::KC_A))
	{
		p->animate(evt);
		p->pNode->setOrientation(1,0,-2,0);
		UpdateCamera();
	}
	if(mKeyboard->isKeyDown(OIS::KC_S) && mKeyboard->isKeyDown(OIS::KC_D))
	{
		p->animate(evt);
		p->pNode->setOrientation(2,0,1,0);
		UpdateCamera();
	}
	if(mKeyboard->isKeyDown(OIS::KC_S) && mKeyboard->isKeyDown(OIS::KC_A))
	{
		p->animate(evt);
		p->pNode->setOrientation(-2,0,1,0);
		UpdateCamera();
	}
	if(mKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		p->attackAnimation(evt);
	}
	if(mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		p->jumpAnimation(evt);
	}
	p->pNode->translate(translate*evt.timeSinceLastFrame);

    return true;
}
 
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Application app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif