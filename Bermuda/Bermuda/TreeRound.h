#pragma once
#include "header_loader.h"
#include "Tree.h"

class TreeRound :
	public Tree
{
public:
	TreeRound(int id, double x, double y, Image* treeImage, Image* stumpImage); 
	virtual ~TreeRound();
};

