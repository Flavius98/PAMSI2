#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Vertex.h"

class Graph {
protected:
	double mDensity = 0;
	int mAmOfNodes = 0;
	int mAmOfEdges = 0;

public:
	const int GetNodes()
	{
		return this->mAmOfNodes;
	}

	const int GetEdges()
	{
		return this->mAmOfEdges;
	}

	virtual void FillGraph(const bool allowLoops) const = 0;
	virtual void PrintGraph() const = 0;
	virtual const int RFile(const std::string fName) = 0;
	virtual void CreateInput(const int startNode) const = 0;

	virtual ~Graph() {};
	Graph(int inAmOfNodes, int inAmOfEdges, double inDensity) : mAmOfNodes(inAmOfNodes), mAmOfEdges(inAmOfEdges), mDensity(inDensity) {};
};