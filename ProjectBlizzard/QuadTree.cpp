#include "QuadTree.h"

QuadTree::QuadTree(void){
	root = NULL;
}

QuadTree::~QuadTree(void){
	delete root;
}

void QuadTree::buildFullTree(int nbrLevels, float cX, float cY, float cZ,
		float sizeX, float sizeY, float sizeZ){
	root = new QuadPart(NULL, 0, cX, cY, cZ, sizeX, sizeY, sizeZ);
	root->makeSubPartitions(nbrLevels);
}

Collider* QuadTree::processCollisions(Model* obj){
	return root->processCollisions(obj);
}

Collider* QuadTree::processCollisions(Model* obj, Vector pos){
	return root->processCollisions(obj, pos);
}

void QuadTree::addObject(Collider *obj){
	root->addObject(obj);
}

void QuadTree::removeObject(Vector pos){
	root->removeObject(pos);
}

void QuadTree::printTree(int type){
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

void QuadTree::render(){
	root->render();
}