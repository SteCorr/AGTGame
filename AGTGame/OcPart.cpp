#include "OcPart.h"
#include "OcTree.h"
#include "BaseObject.h"


OcPart::OcPart(OcPart *parent, int level, float cX, float cY, float cZ, float sizeX, float sizeY, float sizeZ)
{
	this->parent = parent;
	this->level = level;
	this->cX = cX;
	this->cY = cY;
	this->cZ = cZ;

	lowX = cX - sizeX/2; //calc partition high / low values in x, y & z
	highX = cX + sizeX/2;
	lowY = cY - sizeY/2;
	highY = cY + sizeY/2;
	lowZ = cZ - sizeZ/2;
	highZ = cZ + sizeZ/2;

	for (int i = 0; i < 8; i++){
		child[i] = NULL;//init child pointers, if NULL, they are leaf nodes
	}

}


void OcPart::makeSubPartitions(int nbrLevels)
{
	if(level < nbrLevels - 1)
	{
		float newSizeX = (highX - lowX)/2;
		float newSizeY = (highY - lowY)/2;
		float newSizeZ = (highZ - lowZ)/2;

		child[0] = new OcPart(this, level + 1, cX - newSizeX/2, cY + newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[1] = new OcPart(this, level + 1, cX + newSizeX/2, cY + newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[2] = new OcPart(this, level + 1, cX - newSizeX/2, cY - newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[3] = new OcPart(this, level + 1, cX + newSizeX/2, cY - newSizeY/2, cZ + newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[4] = new OcPart(this, level + 1, cX - newSizeX/2, cY + newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[5] = new OcPart(this, level + 1, cX + newSizeX/2, cY + newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[6] = new OcPart(this, level + 1, cX - newSizeX/2, cY - newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);
		child[7] = new OcPart(this, level + 1, cX + newSizeX/2, cY - newSizeY/2, cZ - newSizeZ/2, newSizeX, newSizeY, newSizeZ);

		for(int i = 0; i < 8; i++){
			child[i]->makeSubPartitions(nbrLevels);
		}
		
	}
}


OcPart::~OcPart(void)
{
	if(hasChildren())
	{
		for(int i = 0; i < 8; i++)
		{
			delete child[i];
		}
	}
	objects.clear();
}

OcPart* OcPart::getRoot()
{
	if(parent == NULL)
		return this;
	else
		return parent->getRoot();
}

bool OcPart::contains(BaseObject* obj)
{  //check if obj is inside partition
	float nLowX = obj->entity->getBoundingBox().getMinimum().x;
	float nHighX = obj->entity->getBoundingBox().getMaximum().x;
	float nLowY = obj->entity->getBoundingBox().getMinimum().y;
	float nHighY = obj->entity->getBoundingBox().getMaximum().y;
	float nLowZ = obj->entity->getBoundingBox().getMinimum().z;
	float nHighZ = obj->entity->getBoundingBox().getMaximum().z;
	
	return (nLowX > lowX && nHighX < highX && nLowY > lowY && nHighY < highY && nLowZ > lowZ && nHighZ < highZ);
}

void OcPart::addObject(BaseObject *obj)
{
	if(!hasChildren()){
		obj->part = this;
		objects.push_back(obj);
		return;
	}
	// puts objects into the correct node of the octree
	int p = 0;
	p += (obj->pNode->getPosition().x < cX) ? 0 : 1;
	p += (obj->pNode->getPosition().y > cY) ? 0 : 2;
	p += (obj->pNode->getPosition().z > cZ)? 0 : 4;
	if(child[p]->contains(obj))
		child[p]->addObject(obj);
	else 
	{
		obj->part = this;
		objects.push_back(obj);
	}
}

void OcPart::removeObject(int id) 
{
	vector<BaseObject*>::iterator it;
	for(it = objects.begin(); it != objects.end(); ++it)
	{
		if((*it)->getID() == id){
			objects.erase(it);
			break;
		}
	}
}

void OcPart::ProcessCollisions(int &nbrTests, int &nbrCollisions)
{
	if(hasChildren())
	{  // Start with leaf partitions	
		for(int m = 0; m < 8; m++)
		{
			child[m]->ProcessCollisions(nbrTests, nbrCollisions);
		}
	}

	int n = objects.size();
	if(n >= 2){
		for(int i = 0; i < n-1; i++){  //check each object against ALL other objs in partition
			for(int j = i+1; j < n; j++){
				nbrTests++;
				if(objects[i]->collidesWith(objects[j]))
					nbrCollisions++;
			}
		}
	}
	if(n >= 1 && parent != NULL)
		parent->ProcessBorderCollisions(this, nbrTests, nbrCollisions);
}

void OcPart::ProcessBorderCollisions(OcPart* part, int &nbrTests, int &nbrCollisions){
	int nPart = part->objects.size();
	int n = objects.size();

	if(n > 0){
		for(int i = 0; i < nPart; i++){
			for(int j = 0; j < n; j++){
				nbrTests++;
				if(part->objects[i]->collidesWith(objects[j]))
					nbrCollisions++;
			}
		}
	}
	if(parent != NULL)
		parent->ProcessBorderCollisions(part, nbrTests, nbrCollisions);
}


void OcPart::printDetails(){  //output details to Debug output window
	char text[256];
	sprintf_s(text, "Level %d  at %5.1f %5.1f, %5.1f   X[%5.1f to %5.1f]  y[%5.1f to %5.1f]  z[%5.2f to %5.2f] %d",
		level, cX, cY, cZ, lowX, highX, lowY, highY, lowZ, highZ, objects.size());
	DebugOut(text);
	for(int i = 0; i < 8; i++){
		if(child[0] != NULL){
			child[i]->printDetails();
		}
	}
}

void OcPart::printShortDetails(){
	char text[256];
	sprintf_s(text, "Level %d  at %5.1f %5.1f, %5.1f No of objects %d",
		level, cX, cY, cZ, objects.size());
	DebugOut(text);
	for(int i = 0; i < 8; i++){
		if(child[0] != NULL){
			child[i]->printShortDetails();
		}
	}
}