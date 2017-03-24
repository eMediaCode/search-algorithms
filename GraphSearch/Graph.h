/*
 * Graph.h
 *
 *  Created on: 1 Mar 2017
 *      Author: Vivian Rajkumar
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <list>
#include <vector>

using namespace std;

class Graph {
	int size;
	vector<int> *adjacent;
	vector<int> *weight;
	void DFSHelper(int node, int goal, bool visited[]);
public:
	Graph(int size);
	virtual ~Graph();
	void addEdge(int node1, int node2);
	void addEdge(int node1, int node2, int weight);
	void DFS(int start, int goal);
	void BFS(int start, int goal);
	void UCS(int start, int goal);
	void displayPath(struct priorityQueue p);
};

#endif /* GRAPH_H_ */
