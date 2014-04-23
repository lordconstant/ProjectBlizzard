#include "QuadPart.h"


QuadPart::QuadPart(QuadPart *parent, int level, float cX, float cY, float cZ,
	float sizeX, float sizeY, float sizeZ){
	this->parent = parent;
	this->level = level;
	this->cX = cX;
	this->cY = cY;
	this->cZ = cZ;

	lowX = cX - sizeX/2;
	highX = cX + sizeX/2;
	lowY = cY - sizeY/2;
	highY = cY + sizeY/2;
	lowZ = cZ - sizeZ/2;
	highZ = cZ + sizeZ/2;

	child[0] = NULL;
	child[1] = NULL;
	child[2] = NULL;
	child[3] = NULL;

	area = new BoxCollider();
	area->setDimension(sizeX, sizeY, sizeZ);
	area->setPos(cX, cY, cZ);
}

QuadPart::~QuadPart(void){
	if(hasChildren()){
		delete child[0];
		delete child[1];
		delete child[2];
		delete child[3];
	}

	objects.clear();
}

QuadPart* QuadPart::getRoot(){
	if(parent == NULL)
		return this;
	else
		return parent->getRoot();
}

bool QuadPart::contains(Collider* obj){
	return area->checkCollision(obj);
}

bool QuadPart::contains(Vector pos){
	return area->checkCollision(pos);
}

void QuadPart::addObject(Collider *obj){
	if(!hasChildren()){
		objects.push_back(obj);
		return;
	}
	int x = 0;
	int y = 0;
	int xy = 0;

	x += (obj->getPos().x < cX) ? 0 : 1;

	y += (obj->getPos().y < cY) ? 0 : 1;

	if (x == 0 && y == 0){
		xy = 0;
	}
	else if(x == 1 && y == 0){
		xy = 1;
	}
	else if (x == 0 && y == 1){
		xy = 2;
	}
	else if (x == 1 && y == 1){
		xy = 3;
	}

	if(child[xy]->contains(obj)){
		child[xy]->addObject(obj);
	}
	else {
		objects.push_back(obj);
	}
}

void QuadPart::removeObject(int id){
	vector<Collider*>::iterator it;
	for(it = objects.begin(); it != objects.end(); ++it){
		if((*it)->getID() == id){
			objects.erase(it);
			break;
		}
	}
}

bool QuadPart::removeObject(Vector pos){
	if (hasChildren()){
		if (child[0]->removeObject(pos)){
			return true;
		}

		if (child[1]->removeObject(pos)){
			return true;
		}

		if (child[2]->removeObject(pos)){
			return true;
		}

		if (child[3]->removeObject(pos)){
			return true;
		}
	}

	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->getPos() == pos){
			delete objects[i];
			objects.erase(objects.begin() + i);

			return true;
		}
	}

	return false;
}

Collider* QuadPart::processCollisions(Model* obj){
	// Start with leaf partitions
	Collider* tempCol;
	tempCol = NULL;

	if (contains(obj->getCollider())){
		if (hasChildren()){
			tempCol = child[0]->processCollisions(obj);
			if (tempCol){
				return tempCol;
			}

			tempCol = child[1]->processCollisions(obj);
			if (tempCol){
				return tempCol;
			}

			tempCol = child[2]->processCollisions(obj);
			if (tempCol){
				return tempCol;
			}

			tempCol = child[3]->processCollisions(obj);
			if (tempCol){
				return tempCol;
			}
		}
	}

	int n = objects.size();

	if (n >= 1 && parent != NULL){
		tempCol = parent->processBorderCollisions(this, obj);
		if (tempCol){
			return tempCol;
		}
	}

	return tempCol;
}

Collider* QuadPart::processCollisions(Model* obj, Vector pos){
	Vector point, stepInc;
	int steps, curStep;

	curStep = 0;
	steps = (obj->getPos().Dist(pos) / obj->getScale());

	stepInc = obj->getPos() - pos;

	if (obj->getPos().x < pos.x){
		point = obj->getPos();
	}
	else{
		point = pos;
	}

	if (steps <= 0){
		steps = obj->getScale();
	}

	stepInc /= steps;

	while (curStep < steps){
		point += stepInc;
		
		Model* tempMod = new Model();
		*tempMod = *obj;
		tempMod->setPos(point);

		Collider* tempCol = processCollisions(tempMod);

		delete tempMod;

		if (tempCol){
			return tempCol;
		}

		curStep++;
	}

	return processCollisions(obj);
}

Collider* QuadPart::processBorderCollisions(QuadPart* part, Model* obj){
	int nPart = part->objects.size();
	int n = objects.size();

	for (int i = 0; i < n; i++){
		if (objects[i]->checkCollision(obj->getCollider())){
			return objects[i];
		}
	}

	for (int i = 0; i < nPart; i++){
		if (part->objects[i]->checkCollision(obj->getCollider())){
			return part->objects[i];
		}
	}

	if(parent != NULL)
		return parent->processBorderCollisions(part, obj);

	return NULL;
}


void QuadPart::makeSubPartitions(int nbrLevels){
	if(level < nbrLevels - 1){
		float newSizeX = (highX - lowX)/2;
		float newSizeY = (highY - lowY)/2;
		float newSizeZ = (highZ - lowZ);

		child[0] = new QuadPart(this, level + 1, cX - newSizeX / 2, cY - newSizeY / 2, cZ, newSizeX, newSizeY, newSizeZ);
		child[1] = new QuadPart(this, level + 1, cX + newSizeX / 2, cY - newSizeY / 2, cZ, newSizeX, newSizeY, newSizeZ);
		child[2] = new QuadPart(this, level + 1, cX - newSizeX / 2, cY + newSizeY / 2, cZ, newSizeX, newSizeY, newSizeZ);
		child[3] = new QuadPart(this, level + 1, cX + newSizeX / 2, cY + newSizeY / 2, cZ, newSizeX, newSizeY, newSizeZ);

		child[0]->makeSubPartitions(nbrLevels);
		child[1]->makeSubPartitions(nbrLevels);
		child[2]->makeSubPartitions(nbrLevels);
		child[3]->makeSubPartitions(nbrLevels);
	}
}

void QuadPart::printDetails(){
	char text[256];
	sprintf_s(text, "Level %d  at %5.1f %5.1f, %5.1f   X[%5.1f to %5.1f]  y[%5.1f to %5.1f]  z[%5.2f to %5.2f] %d",
		level, cX, cY, cZ, lowX, highX, lowY, highY, lowZ, highZ, objects.size());
	DebugOut(text);
	if(child[0] != NULL){
		child[0]->printDetails();
		child[1]->printDetails();
		child[2]->printDetails();
		child[3]->printDetails();
	}
}

void QuadPart::printShortDetails(){
	char text[256];
	sprintf_s(text, "Level %d  at %5.1f %5.1f, %5.1f No of objects %d", level, cX, cY, cZ, objects.size());
	DebugOut(text);
	if(child[0] != NULL){
		child[0]->printShortDetails();
		child[1]->printShortDetails();
		child[2]->printShortDetails();
		child[3]->printShortDetails();
	}
}

void QuadPart::render(){
	if (hasChildren()){
		child[0]->render();
		child[1]->render();
		child[2]->render();
		child[3]->render();
	}

	for (int i = 0; i < objects.size(); i++){
		BoxCollider* temp = (BoxCollider*)objects[i];
		temp->render();
	}
}