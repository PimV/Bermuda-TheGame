#pragma once
#include "header_loader.h"
#include "Tree.h"

class TreePine :
	public Tree
{
public:
	TreePine(int id, double x, double y, Image* treeImage, Image* stumpImage); 
	virtual ~TreePine();
};

