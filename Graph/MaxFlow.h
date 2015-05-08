#pragma once
#include "Graph.h"

template <class T>
class MaxFlow : public Graph <T>
{
	bool Connected(int distance);
	int CustomFunctionBFS(int src, int dst, vector <int> path);
public:
	int FindMaxFlow(int src, int dst);
	void PrintMatrix(void);

	MaxFlow(void);
	MaxFlow(int size);
};

template <class T>
bool MaxFlow <T>::Connected(int distance)
{
	return (distance > 0);
}

template <class T>
void MaxFlow <T>::PrintMatrix(void)
{
	for (int i=0; i<Graph<T>::size; i++)
	{
		for (int j=0; j<Graph<T>::size; j++)
		{
			cout << Graph<T>::adjMatrix[Graph<T>::mapNameToIdx[i]][Graph<T>::mapNameToIdx[j]] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
int MaxFlow<T>::CustomFunctionBFS(int src, int dst, vector <int> path)
{
	unsigned minflow;

	minflow = -1;

	if (path.size() == 0)
		return -1;

	for (int i=0; i<path.size()-1; i++)
	{
		int cur;
		int next;
		int flow;

		cur = path[i];
		next = path[i+1];

		flow = Graph<T>::adjMatrix[cur][next];

		if (flow < minflow)
			minflow = flow;
	}

	for (int i=0; i<path.size()-1; i++)
	{
		int cur;
		int next;

		cur = path[i];
		next = path[i+1];

		Graph<T>::adjMatrix[cur][next] -= minflow;
		Graph<T>::adjMatrix[next][cur] += minflow;
	}

	Graph<T>::updated = true;

	return minflow;
}

template <class T>
int MaxFlow<T>::FindMaxFlow(int src, int dst)
{
	int sum;
	int flow;

	sum = 0;
	while ((flow = Graph<T>::BFS(src, dst, true)) >= 0)
	{
		sum += flow;
	}
	return sum;
}

template <class T>
MaxFlow <T>::MaxFlow(void)
{
	MaxFlow(0);
}

template <class T>
MaxFlow<T>::MaxFlow(int size)
{
	Graph<T>::Resize(size);
	Graph<T>::maxIdx = 0;
	Graph<T>::init = 0;
}
