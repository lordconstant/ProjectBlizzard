#pragma once

#include <vector>
#include "DebugPrint.h"
#include "Model.h"
#include "BoxCollider.h"

using namespace std;

// forward declaration

/**
This class represents a binary partition along the x axis. This class
has an accompanying class called BinTreeWith which utilises this
class to provide a binary tree implementation that can be used to 
increase efficiency of collision detection where there is a large
number of objects. <br>

It should be simple enough to create a QuadPartition or OcPartition
(for use in quadtrees or octrees) based on the code/algorithms in 
this class. <br>

Do not use 'delete' to release the dynamic memory used for the
partitions rather as they will be deleted when the parent BinTree is 
deleted. <br>

This class does not release the dynamic memory used for the objects
in the tree. <br>

@author Peter Lager (2011)
@version 1.0
*/
class QuadPart{
private:
	/// pointer to parent partition - will be NULL for root partition
	QuadPart* parent;
	/// Only 2 sub-partitions since its a binary tree
	QuadPart* child[4];

	/// A collection of game objects
	vector<BoxCollider*> objects;

	BoxCollider* area;

	/// XYZ coordinates of the partitions centre
	float cX, cY, cZ;

	/// Record the borders of the partition since these are used a lot
	float lowX, highX;
	float lowY, highY;
	float lowZ, highZ;

	/// The partition level. root is level 0 next level is 1 and so on...
	int level;

private:
	/// Make the default constructor private so it can't be used.
	QuadPart(void){}

public:

	/**
	This is the ctor to use when creating a partition
	@param parent a pointer to this partitions parent
	@param level for this partition
	@param cX X coordinate for centre of this partition
	@param cY Y coordinate for centre of this partition
	@param cZ Z coordinate for centre of this partition
	@param sizeX the length of the partition in the X direction
	@param sizeY the length of the partition in the Y direction
	@param sizeZ the length of the partition in the Z direction
	*/
	QuadPart(QuadPart* parent, int level, float cX, float cY, float cZ, float sizeX, float sizeY, float sizeZ);

	/// clears the collection (objects) of object pointers
	~QuadPart(void);

	/**
	Will create a binary partition tree from the current partition 
	(normally the root).
	@param nbrLevels the number of levels for this binary tree
	*/
	void makeSubPartitions(int nbrLevels);

	/**
	Adds a cube to the partition tree
	@param obj the cube to add.
	*/
	void addObject(BoxCollider* obj);

	/**
	Determines whether the object can be totally contained by the
	partition. It makes use of the collision sphere radius for
	the object.
	@param obj the cube to test
	@returns true it fits inside the partition else false
	*/
	bool contains(BoxCollider* obj);
	bool contains(Vector pos);

	/**
	Remove an object from this partition based on its unique id number.
	@param id the unique id number of the object to remove.
	*/
	bool removeObject(Vector pos);
	/**
	Recursive function (starting with the leaf nodes) to process all 
	the objects in the partition and then test them against the 
	nodes in the parent partitions. <br>
	@param nbrTests count of the number of tests performed
	@param nbrCollisions count of the number of collisions detected
	*/

	Collider* processCollisions(Model* obj);
	Collider* processCollisions(Model* obj, Vector pos);

	/**
	Recursive function to process all the objects in the partition 
	with each parent partition in turn. This method is only called
	from the only ProcessCollisions method.
	@param nbrTests count of the number of tests performed
	@param nbrCollisions count of the number of collisions detected
	*/

	Collider* processBorderCollisions(QuadPart* part, Model* obj);

	/**
	Recursive fucntion to get the root partition from any other
	partition.
	@return pointer to the root node
	*/
	QuadPart* getRoot();

	/**
	In-line method to see if this partition has children i.e. not
	a leaf node.
	@return true if this partition has children else false
	*/
	bool hasChildren(){ return child[0] != NULL;}

	/// Print various partition details (see implementation) 
	void printDetails();

	/// Print various partition details (see implementation) 
	void printShortDetails();

	void render();
};
