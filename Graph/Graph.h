#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

template <class T> class Node;
template <class T> class Graph;


template <class T>
class Graph
{
protected:
	enum color
	{
		WHITE,
		GRAY,
		BLACK
	};

	class Node
	{
	protected:
		unsigned int distance;
		int parent;
		int color;

	public:
		int GetDistance(void);

		Node(void);

		friend class Graph <T>;
	};

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

	virtual bool Connected(int distance);

	virtual int CustomFunctionBFS(int src, int dst, vector <int> path,
			vector <Node> &vertex);
	vector<int> BFSbyList(int source, int destination, vector <Node> &vertex);
	vector<int> BFSbyMatrix(int source, int destination, vector <Node> &vertex);

public:
	void AddEdgeByName(T a, T b, int distance = 1);

	void PrintMatrix(void);

	int BFS(T source, T destination, bool byMatrix = false);

	void Resize(int size);
	void SetInitValue(int val);

	Graph(void);
	Graph(int size);
};

template <class T>
int Graph<T>::Node::GetDistance(void)
{
	return distance;
}

template <class T>
Graph<T>::Node::Node(void)
{
	parent = -1;
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
vector <int> Graph<T>::BFSbyList(int source, int destination,
		vector <Node> &vertex)
{
	vector <int> path;
	queue <int> q;

	vertex.resize(size);

	vertex[source].color = GRAY;
	vertex[source].distance = 0;
	vertex[source].parent = -1;

	q.push(source);

	while (!q.empty())
	{
		int u;
		u = q.front();
		q.pop();

		for (int i=0; i<adjList[u].size(); i++)
		{
			pair <int, int> data;
			int v;
			int distance;

			data = adjList[u][i];
			v = data.first;
			distance = data.second;

			if (v >= vertex.size())
			{
				cout << "Error: index out of range" << endl;
				return path;
			}

			if (vertex[v].color == WHITE)
			{
				vertex[v].color = GRAY;
				vertex[v].distance = vertex[u].distance + distance;
				vertex[v].parent = u;

				if (v == destination)
				{
					int cur;
					int parent;

					cur = v;
					while ((parent = vertex[cur].parent) != source)
					{
						path.push_back(cur);
						cur = parent;
					}
					path.push_back(source);

					reverse(path.begin(), path.end());

					return path;
				}

				q.push(v);
			}
		}
		vertex[u].color = BLACK;
	}

	return path;
}

template <class T>
vector <int> Graph<T>::BFSbyMatrix(int source, int destination,
		vector <Node> &vertex)
{
	vector <int> path;
	queue <int> q;

	UpdateMatrix();

	vertex.resize(size);

	vertex[source].color = GRAY;
	vertex[source].distance = 0;
	vertex[source].parent = -1;

	q.push(source);

	while (!q.empty())
	{
		int u;
		u = q.front();
		q.pop();

		for (int v=0; v<adjMatrix[u].size(); v++)
		{
			int distance;

			distance = adjMatrix[u][v];

			if (!Connected(distance))
				continue;

			if (v >= vertex.size())
			{
				cout << "Error: index out of range" << endl;
				return path;
			}

			if (vertex[v].color == WHITE)
			{
				vertex[v].color = GRAY;
				vertex[v].distance = vertex[u].distance + distance;
				vertex[v].parent = u;

				if (v == destination)
				{
					int cur;
					int parent;

					cur = v;
					while ((parent = vertex[cur].parent) != source)
					{
						path.push_back(cur);
						cur = parent;
					}
					path.push_back(source);

					reverse(path.begin(), path.end());

					return path;
				}

				q.push(v);
			}
		}
		vertex[u].color = BLACK;
	}

	return path;
}

template <class T>
bool Graph<T>::Connected(int distance)
{
	if (distance == -1)
		return false;
	else
		return true;
}
		
template <class T>
int Graph<T>::CustomFunctionBFS(int src, int dst, vector <int> path,
		vector <Node> &vertex)
{
	/*
	 * This one simply returns the distance
	 */
	if (path.size() > 0)
	{
		return vertex[dst].distance;
	}
	else
	{
		return 0;
	}
}

template <class T>
int Graph<T>::BFS(T source, T destination, bool byMatrix)
{
	int src;
	int dst;
	vector <Node> vertex;
	vector <int> path;

	src = mapNameToIdx[source];
	dst = mapNameToIdx[destination];

	if (byMatrix)
		path = BFSbyMatrix(src, dst, vertex);
	else
		path = BFSbyList(src, dst, vertex);

	return CustomFunctionBFS(src, dst, path, vertex);
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


