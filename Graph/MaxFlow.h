#pragma once
#include "Graph.h"

template <class T>
class MaxFlow : public Graph <T>
{
	bool Connected(long long distance);
	long long CustomFunctionBFS(int src, int dst, vector <int> path);
public:
	long long FindMaxFlow(int src, int dst);

	MaxFlow(void);
	MaxFlow(int size);
};

template <class T>
bool MaxFlow <T>::Connected(long long distance)
{
	return (distance > 0);
}

template <class T>
long long MaxFlow<T>::CustomFunctionBFS(int src, int dst, vector <int> path)
{
	unsigned long long minflow;

	minflow = -1;

	if (path.size() == 0)
		return -1;

	for (int i=0; i<path.size()-1; i++)
	{
		int cur;
		int next;
		long long flow;

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
long long MaxFlow<T>::FindMaxFlow(int src, int dst)
{
	long long sum;
	long long flow;

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
	Graph<T>::Resize(0);
	Graph<T>::maxIdx = 0;
	Graph<T>::init = 0;
}

template <class T>
MaxFlow<T>::MaxFlow(int size)
{
	Graph<T>::Resize(size);
	Graph<T>::maxIdx = 0;
	Graph<T>::init = 0;
}
