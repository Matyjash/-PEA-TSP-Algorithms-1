#pragma once
#include "Graph.h"
#include <iostream>
#include <vector>
class Node
{
public:
	Graph* graph;
	int cost;
	int vertexNumber;
	int level;
	std::vector<int> road;
	
};

