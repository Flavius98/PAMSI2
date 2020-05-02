#include <iostream>

#include "Graph.h"
#include"BellmanAlg.h"

template<typename T>
std::string Driver(int(&vertStorage)[5], double(&denStorage)[4], int loops)
{
	std::string result;

	for (auto density : denStorage)
	{
		for (auto verticles : vertStorage)
		{
			double accumulatedTime = 0;

			for (int iterLoops = 0; iterLoops < loops; iterLoops++)
			{
				std::shared_ptr<T> graph = std::make_shared<T>(verticles, density);

				int startingNode = rand() % verticles;

				graph->FillGraph(false);
				accumulatedTime += BellmanAlg(std::move(graph), startingNode);
			}

			result += std::to_string((accumulatedTime * 100 / loops) + 1);
			result += ",";

			std::cout << verticles << " verticles done " << std::endl;
		}
		std::cout << density << " density done " << std::endl;
	}
	return result;
}

int main()
{
	int vertStorage[5] = { 5,10,30,50,100 };
	double denStorage[4] = { 0.25,0.5,0.75,1.00 };
	int loop = 100;

	std::ofstream file("Times.txt");

	file << Driver<List>(vertStorage, denStorage, loop);
	std::cout << "LIST DONE\n" << std::endl;
	std::cout << " ";
	file << Driver<Matrix>(vertStorage, denStorage, loop);	
	std::cout << "MATRIX DONE" << std::endl;
	file.close();

	return 0;
}