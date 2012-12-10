#include "OcTree.h"

OcTree::OcTree(void){
	root = NULL;
}

OcTree::~OcTree(void){
	delete root;
}

void OcTree::BuildFullTree(int nbrLevels, float cX, float cY, float cZ, float sizeX, float sizeY, float sizeZ){
	root = new OcPart(NULL, 0, cX, cY, cZ, sizeX, sizeY, sizeZ);
	root->makeSubPartitions(nbrLevels);
}

void OcTree::ProcessCollisions(int &nbrTests, int &nbrCollisions){
	nbrTests = nbrCollisions = 0;  //reset EACH frame???
	root->ProcessCollisions(nbrTests, nbrCollisions);
}

void OcTree::addObject(BaseObject *obj){
	root->addObject(obj);
}

void OcTree::printTree(int type){
	DebugOut("==================== TREE ====================");
	if(root != NULL){
		switch(type) {
			case 0:
				root->printDetails();
				break;
			case 1:
				root->printShortDetails();
				break;
		}
	}
	DebugOut("==============================================");
}
