#include "Graph.h"

int main(void)
{
	Graph <int> graph(5);

	graph.AddEdgeByName(1, 2);
	graph.AddEdgeByName(2, 3);
	graph.AddEdgeByName(3, 1);
	graph.AddEdgeByName(3, 4);
	graph.AddEdgeByName(3, 5);

	cout << graph.BFS(1, 5, true) << endl;

	return 0;
}
