#pragma once

#include"QuadPart.h"
#include "Model.h"
#include"DebugPrint.h"

/**
This class is a simple implementation of a binary partition tree 
that can be used to increase efficiency of collision detection 
where there is a large number of objects. <br>

The partitions are implemented in the BinPart class. <br>

It is provided solely to demonstrate the algorithms used in a partition 
tree and is not practical for use in 2D/3D object domains where a 
quadtree or an octree would be a more realistic approach. <br>

That said it should be fairly straight forward to create a quadtree
or an octree based on the code in this class.  <br>

@author Peter Lager (2011)
@version 1.0
*/
class QuadTree{
public:
	/// The root partition
	QuadPart* root;

	/** 
	Create an empty tree
	*/
	QuadTree(void);

	/**
	This will release all the memory reserved for the tree.
	*/
	~QuadTree(void);

	/**
	Builds a full binary tree implementation for a given domain
	location and size.
	@param nbrLevel number of levels for this binary tree
	@param cX X coordinate for centre of this tree domain
	@param cY Y coordinate for centre of this tree domain
	@param cZ Z coordinate for centre of this tree domain
	@param sizeX the length of the domain in the X direction
	@param sizeY the length of the domain in the Y direction
	@param sizeZ the length of the domain in the Z direction
	*/ 
	void buildFullTree(int nbrLevels, float cX, float cY, float cZ, float sizeX, float sizeY, float sizeZ);

	/**
	Call this method to initiate collision detection for the 
	objects in the tree. <br>
	*/
	Collider* processCollisions(Model* obj);
	Collider* processCollisions(Model* obj, Vector pos);

	/**
	Add a cube to the binary tree. <br>
	*/

	void addObject(BoxCollider* obj);
	void removeObject(Vector pos);

	/**
	Call this to print the tree.
	@param type the type of details to be printed.
	*/
	void printTree(int type);

	void render();
};
