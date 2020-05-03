#pragma once

#include "Graph.h"

static int regValue = -1;

class List : public Graph {
	Edge* inEdge;

public:
	const Edge* GetEdge()
	{
		return this->inEdge;
	}

	void FillGraph(const bool allowLoops) const override;
	void PrintGraph() const override;
	const int RFile(const std::string fName) override;
	void CreateInput(const int startNode) const override;

	void AddEdge(int nodeStart, int nodeEnd, int value, int posFlag) const;
	bool IsExisting(int nodeStart, int nodeEnd) const;

	~List() { delete[] inEdge; }
	List() : Graph() {};
	List(int inAmOfNodes, int inDensity) : Graph(inAmOfNodes, inDensity* inAmOfNodes* (inAmOfNodes - 1), inDensity), inEdge(new Edge[inDensity * inAmOfNodes * (inAmOfNodes - 1)]) {}
};

