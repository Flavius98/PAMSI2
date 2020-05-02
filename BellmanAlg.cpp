#include "BellmanAlg.h"

double BellmanAlg(std::shared_ptr<Matrix> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->GetNodes()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distStorage = new int[workingGraph->GetNodes()];

	for (int iterNodes = 0; iterNodes < workingGraph->GetNodes(); iterNodes++)
		distStorage[iterNodes] = infinity;

	distStorage[startingNode] = 0;

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->GetNodes(); iterNodeCell++)
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->GetNodes(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
				int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->GetVal(iterNodeCell, iterNodeCollumn);

				if (distStorage[temNodeStart] + temValue < distStorage[temNodeEnd])
				{
					distStorage[temNodeEnd] = distStorage[startingNode] + temValue;
					pathStorage[temNodeEnd].clear();
					pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
				}
			}


	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->GetNodes(); iterNodeCell++)
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->GetNodes(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
				int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->GetVal(iterNodeCell, iterNodeCollumn);

				if (distStorage[temNodeStart] + temValue < distStorage[temNodeEnd])
				{
					if (distStorage[temNodeStart] > infinity / 2)
						distStorage[temNodeStart] = infinity;

					else if (temValue == infinity)
						continue;

					else
						distStorage[temNodeEnd] = negInfinity;

				}

				else if (distStorage[temNodeStart] > infinity / 2)
					distStorage[temNodeStart] = infinity;
			}

	auto endTime = std::chrono::high_resolution_clock::now();

	Results(std::move(pathStorage), std::move(distStorage), workingGraph->GetNodes(), startingNode);

	delete[] pathStorage;
	delete[] distStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

double BellmanAlg(std::shared_ptr<List> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->GetNodes()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distStorage = new int[workingGraph->GetNodes()];

	for (int iterNodes = 0; iterNodes < workingGraph->GetNodes(); iterNodes++)
		distStorage[iterNodes] = infinity;
	
	distStorage[startingNode] = 0;

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterEdges = 0; iterEdges < workingGraph->GetEdges(); iterEdges++)
		{
			int temNodeStart = workingGraph->GetEdge()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->GetEdge()[iterEdges].nodeEnd;
			int temValue = workingGraph->GetEdge()[iterEdges].value;

			if (distStorage[temNodeStart] + temValue < distStorage[temNodeEnd])
				distStorage[temNodeEnd] = distStorage[temNodeStart] + temValue;
			
			pathStorage[temNodeEnd].clear();
			pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
		}
	
	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterEdges = 0; iterEdges < workingGraph->GetEdges(); iterEdges++)
		{
			int temNodeStart = workingGraph->GetEdge()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->GetEdge()[iterEdges].nodeEnd;
			int temValue = workingGraph->GetEdge()[iterEdges].value;

			if (distStorage[temNodeStart] + temValue < distStorage[temNodeEnd])
			{
				if (distStorage[temNodeStart] > infinity / 2)
					distStorage[temNodeStart] = infinity;

				else
					distStorage[temNodeEnd] = negInfinity;
			}

			else if (distStorage[temNodeStart] > infinity / 2)
				distStorage[temNodeStart] = infinity;
		}

	auto endTime = std::chrono::high_resolution_clock::now();

	Results(std::move(pathStorage), std::move(distStorage), workingGraph->GetNodes(), startingNode);

	delete[] pathStorage;
	delete[] distStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

void Results(std::string pathString[], int distStorage[], int nodesAmount, int startingNode)
{
	std::ofstream ResultsFile("Results.txt");
	std::cout << "\n           Results            \n\n";
	std::cout << "Starting node was : " << startingNode << std::endl;
	ResultsFile << "\n           Results            \n\n";
	ResultsFile << "Starting node was : " << startingNode << std::endl;
	for (int itrNodes = 0; itrNodes < nodesAmount; itrNodes++)
	{
		if (distStorage[itrNodes] == infinity)
		{
			std::cout << itrNodes << "-> inf" << std::endl;
			ResultsFile << itrNodes << "-> inf" << std::endl;
			continue;
		}

		else if (distStorage[itrNodes] == negInfinity)
		{
			std::cout << itrNodes << "-> -inf" << std::endl;
			ResultsFile << itrNodes << "-> -inf" << std::endl;
			continue;
		}

		else
		{
			std::cout << itrNodes << "->" << distStorage[itrNodes] << std::endl;
			ResultsFile << itrNodes << "->" << distStorage[itrNodes] << std::endl;
		}

		std::cout << "  ";
		ResultsFile << "  ";

		if ((distStorage[itrNodes] >= 100 && distStorage[itrNodes] < 1000) || (-100 > distStorage[itrNodes] && distStorage[itrNodes] <= -10)) 
		{
			std::cout << " The shortest path: " << pathString[itrNodes] << itrNodes;
			ResultsFile << " The shortest path: " << pathString[itrNodes] << itrNodes;
		}

		else if (0 <= distStorage[itrNodes] && distStorage[itrNodes] < 10) 
		{
			std::cout << "   The shortest path: " << pathString[itrNodes] << itrNodes;
			ResultsFile << "   The shortest path: " << pathString[itrNodes] << itrNodes;
		}

		else if ((distStorage[itrNodes] >= 10 && distStorage[itrNodes] < 100) || (-10 < distStorage[itrNodes] && distStorage[itrNodes] < 0)) 
		{
			std::cout << "  The shortest path: " << pathString[itrNodes] << itrNodes;
			ResultsFile << "  The shortest path: " << pathString[itrNodes] << itrNodes;
		}

		else 
		{
			std::cout << "The shortest path: " << pathString[itrNodes] << itrNodes;
			ResultsFile << "The shortest path: " << pathString[itrNodes] << itrNodes;
		}

		std::cout << std::endl;
	}

	ResultsFile << std::endl;
}

