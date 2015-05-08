#include "MaxFlow.h"

int main(void)
{
	MaxFlow <int> graph(10);

	graph.AddEdgeByName(0, 2, 1);
	graph.AddEdgeByName(0, 3, 1);
	graph.AddEdgeByName(0, 4, 10);
	graph.AddEdgeByName(0, 5, 1);

	graph.AddEdgeByName(2, 6, 1);
	graph.AddEdgeByName(2, 8, 1);
	graph.AddEdgeByName(3, 6, 1);
	graph.AddEdgeByName(3, 9, 1);
	graph.AddEdgeByName(4, 8, 10);

	graph.AddEdgeByName(6, 1, 1);
	graph.AddEdgeByName(7, 1, 1);
	graph.AddEdgeByName(8, 1, 10);
	graph.AddEdgeByName(9, 1, 1);

	cout << graph.FindMaxFlow(0, 1) << endl;

	return 0;
}
