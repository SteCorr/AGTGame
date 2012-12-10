#include "Terrian.h"


Terrian::Terrian(int id)
{
	id = id;
}

Terrian::Terrian(Ogre::String name, Ogre::String mesh, int id)
{
	pName = name;
	pMesh = mesh;
	id = id;
}

void Terrian::Scene()
{

}

Terrian::~Terrian()
{
}
