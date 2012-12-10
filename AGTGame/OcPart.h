#pragma once

#include <vector>
#include "BaseObject.h"
using namespace std;

// Only needed for printing details of the partition method and any 
// other temporary debugging code
extern void DebugOut(const char *);

// forward declaration
class BaseObject;

/**
This class represents a octree partition along the x, y and z axis. This class has an 
accompanying class called OcTree which utilises this class to provide a 
binary tree implementation that can be used to increase efficiency of 
collision detection where there are a large number of objects. <br>

It should be simple enough to create a BinPartition or OcPartition
(for use in quadtrees or octrees) based on the code/algorithms in this class. <br>

Do not use 'delete' to release the dynamic memory used for the
partitions rather as they will be deleted when the parent BinTree is deleted. <br>

This class does not release the dynamic memory used for the objects in the tree. <br>

@author Peter Lager (2011)
@version 1.0
*/
class OcPart{
private:
	OcPart* parent;  /// pointer to parent partition - will be NULL for root partition
	OcPart* child[8];  /// Only 2 sub-partitions since its a  Octree

	vector<BaseObject*> objects;  /// A collection of game objects (cubes for this prog)
		float cX, cY, cZ;  /// XYZ coordinates of the partition's centre

	/// Record the borders of the partition since these are used a lot
	float lowX, highX;
	float lowY, highY;
	float lowZ, highZ;

	int level;  /// The partition level. root is level 0 next level is 1 and so on...

private:
	OcPart(void){}  /// Make the default constructor private so it can't be used.

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
	OcPart(OcPart* parent, int level, float cX, float cY, float cZ, float sizeX, float sizeY, float sizeZ);

	~OcPart(void);  /// clears the collection (objects) of object pointers

	/**
	Will create a binary partition tree from the current partition (normally the root).
	@param nbrLevels the number of levels for this binary tree
	*/
	void makeSubPartitions(int nbrLevels);

	/**
	Adds a cube to the partition tree
	@param obj the cube to add.
	*/
	void addObject(BaseObject* obj);

	/**
	Determines whether the object can be totally contained by the partition. 
	It makes use of the collision sphere radius for	the object.
	@param obj: the cube to test
	@returns true if it fits inside the partition else false
	*/
	bool contains(BaseObject* obj);

	/**
	Remove an object from this partition based on its unique id number.
	@param id the unique id number of the object to remove.
	*/
	void removeObject(int id);

	/**
	Recursive function (starting with the leaf nodes) to process all the objects 
	in the partition and then test them against the	nodes in the parent partitions. <br>
	@param nbrTests count of the number of tests performed
	@param nbrCollisions count of the number of collisions detected
	*/
	void ProcessCollisions(int &nbrTests, int &nbrCollisions);

	/**
	Recursive function to process all the objects in the partition with each parent partition in turn. 
	This method is only called from the ProcessCollisions method.
	@param nbrTests count of the number of tests performed
	@param nbrCollisions count of the number of collisions detected
	*/
	void ProcessBorderCollisions(OcPart* part, int &nbrTests, int &nbrCollisions);

	/**
	Recursive function to get the root partition from any other	partition.
	@return pointer to the root node
	*/
	OcPart* getRoot();

	/**
	In-line method to see if this partition has children i.e. not a leaf node.
	@return true if this partition has children else false
	*/
	bool hasChildren(){ return child[0] != NULL; }

	/// Print various partition details (see implementation) 
	void printDetails();

	/// Print various partition details (see implementation) 
	void printShortDetails();
};
