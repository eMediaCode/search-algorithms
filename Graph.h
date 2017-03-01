/*
 * Graph.h
 *
 *  Created on: 1 Mar 2017
 *      Author: Vivian Rajkumar
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include<list>

using namespace std;

class Graph {
	int size;
	list<int> *adjacent;
	void DFSHelper(int node, bool visited[]);
public:
	Graph(int size);
	virtual ~Graph();
	void addEdge(int node1, int node2);
	void DFS(int node);
	void BFS(int node);
};

#endif /* GRAPH_H_ */
