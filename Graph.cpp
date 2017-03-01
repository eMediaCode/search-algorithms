/*
 * Graph.cpp
 *
 *  Created on: 1 Mar 2017
 *      Author: Vivian Rajkumar
 */

#include "Graph.h"
#include<iostream>
#include<list>

using namespace std;

Graph::Graph(int size) {
	this->size = size;
	adjacent = new list<int>[size];
}

Graph::~Graph() {

}

void Graph::addEdge(int node1, int node2) {
	adjacent[node1].push_back(node2);
}

void Graph::DFSHelper(int node, bool visited[]) {
	// Mark the current node as visited and print
	visited[node] = true;
	cout << node << " ";

	// Recur for all adjacent nodes
	list<int>::iterator i;
	for(i = adjacent[node].begin(); i != adjacent[node].end(); i++) {
		if(!visited[*i]) {
			DFSHelper(*i, visited);
		}
	}
}

void Graph::DFS(int node) {
	// Mark all nodes as not visited
	bool *visited = new bool[size];
	for(int i = 0; i < size; i++) {
		visited[i] = false;
	}

	// Call recursive helper function to print explored vertices
	DFSHelper(node, visited);
}

void Graph::BFS(int node) {
	// Mark all nodes as not visited
	bool *visited = new bool[size];
	for(int i = 0; i < size; i++) {
		visited[i] = false;
	}

	// Create queue
	list<int> queue;

	// Mark current node as visited, and enqueue
	visited[node] = true;
	queue.push_back(node);

	// Iterator i used to get all adjacent nodes
	list<int>::iterator i;

	while(!queue.empty()) {
		// Dequeue a node and print it
		node = queue.front();
		cout << node << " ";
		queue.pop_front();

		// Get all adjacent vertices of dequeued node
		// If adjacent has not been visited, mark visited
		// and enqueue it
		for(i = adjacent[node].begin(); i != adjacent[node].end(); i++) {
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

int main() {

	// Create a graph
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Depth-First Traversal" << endl;
	g.DFS(2);
	cout << endl;
	cout << "Breadth-First Traversal" << endl;
	g.BFS(3);
	cout << endl;

	return 0;
}
