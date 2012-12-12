#include "BaseObject.h"

BaseObject::BaseObject(int ID)
{
	id = ID;
}

BaseObject::BaseObject(Ogre::String name, Ogre::String mesh, int ID)
{
	pName = name;
	pMesh = mesh;
	id = ID;
}

bool BaseObject::collidesWith(BaseObject* obj)
{
	if(pNode->getPosition().x + entity->getBoundingBox().getMaximum().x < obj->pNode->getPosition().x + obj->entity->getBoundingBox().getMaximum().x)
	{
		//if is player, flag cube
		if (type == TYPE_PLAYER)
		{
			obj->collided();
			return true;
		}
		//if cube is player, flag this
		if (obj->getType() == TYPE_PLAYER)
		{
			colPlayer = true;
			return true;
		}

		// Swap velocities
		Vector v = vel;
		vel = obj->vel;
		obj->vel = v;
		return true;
	}

	if(pNode->getPosition().z + entity->getBoundingBox().getMaximum().z < obj->pNode->getPosition().z + obj->entity->getBoundingBox().getMaximum().z)
	{
		//if is player, flag cube
		if (type == TYPE_PLAYER)
		{
			obj->collided();
			return true;
		}
		//if cube is player, flag this
		if (obj->getType() == TYPE_PLAYER)
		{
			colPlayer = true;
			return true;
		}
		// Swap velocities
		Vector v = vel;
		vel = obj->vel;
		obj->vel = v;
		return true;
	}

	if(obj->pNode->getPosition().x + obj->entity->getBoundingBox().getMaximum().x < pNode->getPosition().x + entity->getBoundingBox().getMaximum().x)
	{
		//if is player, flag cube
		if (type == TYPE_PLAYER)
		{
			obj->collided();
			return true;
		}
		//if cube is player, flag this
		if (obj->getType() == TYPE_PLAYER){
			colPlayer = true;
			return true;
		}
		// Swap velocities
		Vector v = vel;
		vel = obj->vel;
		obj->vel = v;
		return true;
	}

	if(obj->pNode->getPosition().z + obj->entity->getBoundingBox().getMaximum().z < pNode->getPosition().z + entity->getBoundingBox().getMaximum().z)
	{
		//if is player, flag cube
		if (type == TYPE_PLAYER)
		{
			obj->collided();
			return true;
		}
		//if cube is player, flag this
		if (obj->getType() == TYPE_PLAYER)
		{
			colPlayer = true;
			return true;
		}
		// Swap velocities
		Vector v = vel;
		vel = obj->vel;
		obj->vel = v;
		return true;
	}
	return false;
}

int BaseObject::getType()
{
	return type;
}

void BaseObject::collided()
{
	colPlayer = true;
}

int BaseObject::getID()
{
	return id;
}