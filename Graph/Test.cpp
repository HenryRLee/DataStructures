#include "Graph.h"

int main(void)
{
	Graph <int> graph(3);

	graph.AddEdgeByName(1, 2);
	graph.AddEdgeByName(2, 3);
	graph.AddEdgeByName(3, 1);

	graph.PrintMatrix();

	return 0;
}
