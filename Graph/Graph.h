#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum color
{
	WHITE,
	GRAY,
	BLACK
};

template <class T> class GraphNode;
template <class T> class Graph;

template <class T>
class GraphNode
{
protected:
	T key;

	int color;
	unsigned int distance;
	int parent;

public:
	void PrintKey(void);
	T ReturnKey(void);

	int GetDistance(void);

	GraphNode(void);

	friend class Graph <T>;
};

template <class T>
class Graph
{
protected:
	unsigned int size;

	unsigned int maxIdx;
	int init;
	bool updated;

	map <T, int> mapNameToIdx;
	vector <T> mapIdxToName;

	vector < vector < pair <int, int> > > adjList;	// pair <idx, distance>
	vector < vector <int> > adjMatrix;

	void CleanMatrix(void);
	void UpdateMatrix(void);

	void InitializeGraph(void);

	bool AddNameToMap(T a);
	void AddEdgeByIdx(int a, int b, int distance = 1);

public:
	void AddEdgeByName(T a, T b, int distance = 1);

	void PrintMatrix(void);

	void Resize(int size);
	void SetInitValue(int val);

	Graph(void);
	Graph(int size);
};

template <class T>
void GraphNode<T>::PrintKey(void)
{
	cout << key << " ";
}

template <class T>
T GraphNode<T>::ReturnKey(void)
{
	return key;
}

template <class T>
int GraphNode<T>::GetDistance(void)
{
	return distance;
}

template <class T>
GraphNode<T>::GraphNode(void)
{
	parent = 0;
	color = WHITE;
	distance = -1;
}

template <class T>
void Graph<T>::AddEdgeByIdx(int a, int b, int distance)
{
	if (adjList.size() <= a)
	{
		cout << "Error: index out of range" << endl;
		return;
	}

	adjList[a].push_back(make_pair(b, distance));

	updated = false;
}

template <class T>
void Graph<T>::InitializeGraph(void)
{
	adjList.resize(size);

	for (int i=0; i<adjList.size(); i++)
	{
	}

	adjMatrix.resize(size);

	for (int i=0; i<adjMatrix.size(); i++)
	{
		adjMatrix[i].resize(size);
	}

	mapIdxToName.resize(size);
}

template <class T>
void Graph<T>::CleanMatrix(void)
{
	for (int i=0; i<adjMatrix.size(); i++)
	{
		for (int j=0; j<adjMatrix[i].size(); j++)
		{
			adjMatrix[i][j] = init;
		}
	}
}

template <class T>
void Graph<T>::UpdateMatrix(void)
{
	if (updated)
		return;

	CleanMatrix();

	if (adjList.size() > adjMatrix.size())
	{
		cout << "Error: index out of range" << endl;
		return;
	}

	for (int i=0; i<adjList.size(); i++)
	{
		for (int j=0; j<adjList[i].size(); j++)
		{
			pair <int, int> data;
			int idx;
			int distance;

			data = adjList[i][j];
			idx = data.first;
			distance = data.second;

			if (idx >= adjMatrix[i].size())
			{
				cout << "Error: index out of range" << endl;
				return;
			}

			adjMatrix[i][idx] = distance;
		}
	}

	updated = true;
}

template <class T>
bool Graph<T>::AddNameToMap(T a)
{
	if (mapIdxToName[mapNameToIdx[a]] == a)
		return true;

	if (maxIdx >= mapIdxToName.size())
	{
		cout << "Error: index out of range" << endl;
		return false;
	}

	mapNameToIdx[a] = maxIdx++;

	mapIdxToName[mapNameToIdx[a]] = a;

	return true;
}

template <class T>
void Graph<T>::AddEdgeByName(T a, T b, int distance)
{
	if (!AddNameToMap(a) || !AddNameToMap(b))
		return;

	AddEdgeByIdx(mapNameToIdx[a], mapNameToIdx[b], distance);
}

template <class T>
void Graph<T>::PrintMatrix(void)
{
	UpdateMatrix();

	for (int i=0; i<adjMatrix.size(); i++)
	{
		for (int j=0; j<adjMatrix[i].size(); j++)
		{
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
void Graph<T>::Resize(int size)
{
	this->size = size;
	InitializeGraph();
}

template <class T>
void Graph<T>::SetInitValue(int val)
{
	init = val;
}

template <class T>
Graph<T>::Graph(void)
{
	Graph(0);
}

template <class T>
Graph<T>::Graph(int size)
{
	Resize(size);
	maxIdx = 0;
	init = -1;
}


