/*
 * Graph.cpp
 *
 *  Created on: 1 Mar 2017
 *      Author: Vivian Rajkumar
 */

#include "Graph.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct priorityQueue {
	list<int> path;
	int cost;
	bool operator>(const priorityQueue& rhs) const { return cost > rhs.cost; }
};

class comparison {
public:
	bool operator() (priorityQueue p1, priorityQueue p2) const {
		return (p1 > p2);
	}
};

Graph::Graph(int size) {
	this->size = size;
	adjacent = new vector<int>[size];
	weight = new vector<int>[size];
}

Graph::~Graph() {

}

void Graph::addEdge(int node1, int node2) {
	adjacent[node1].push_back(node2);
	weight[node1].push_back(0);
}

void Graph::addEdge(int node1, int node2, int w) {
	adjacent[node1].push_back(node2);
	weight[node1].push_back(w);
}

void Graph::DFSHelper(int start, int goal, bool visited[]) {
	// Mark the current node as visited and print
	visited[start] = true;
	cout << start;

	// Recur for all adjacent nodes, as long as goal has not yet been visited
	vector<int>::iterator i;
	for(i = adjacent[start].begin(); i != adjacent[start].end(), visited[goal] != true; i++) {
		if(!visited[*i]) {
			cout << "->";
			DFSHelper(*i, goal, visited);
		}
	}
}

void Graph::DFS(int start, int goal) {
	if (start == goal) {
		cout << start;
		return;
	}
	else {
		// Mark all nodes as not visited
		bool *visited = new bool[size];
		for(int i = 0; i < size; i++) {
			visited[i] = false;
		}

		// Call recursive helper function to print explored vertices
		DFSHelper(start, goal, visited);
	}

	cout << endl;
}

void Graph::BFS(int start, int goal) {
	// Mark all nodes as not visited
	bool *visited = new bool[size];
	for(int i = 0; i < size; i++) {
		visited[i] = false;
	}

	// Create queue
	list<int> queue;

	// Mark current node as visited, and enqueue
	visited[start] = true;
	queue.push_back(start);

	// Iterator i used to get all adjacent nodes
	vector<int>::iterator i;

	while(!queue.empty()) {
		// Dequeue a node and print it
		start = queue.front();
		cout << start << " ";
		queue.pop_front();

		// Check if goal has been visited
		if (goal == start) {
			cout << endl;
			return;
		}

		// Get all adjacent vertices of dequeued node
		// If adjacent has not been visited, mark visited
		// and enqueue it
		for(i = adjacent[start].begin(); i != adjacent[start].end(); ++i) {
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

void Graph::UCS(int start, int goal) {
	int cur = 0;
	int pos = 0;
	priority_queue<priorityQueue,vector<priorityQueue>,comparison> pq;
	priorityQueue s;

	// Insert root into queue
	s.path.push_back(start);
	s.cost = 0;

	vector<int>::iterator i;
	pq.push(s);

	// While queue is not empty
	while (!pq.empty()) {
		priorityQueue cPQ, tPQ;

		// Dequeue max priority element from queue
		cur = pq.top().path.back();
		cPQ = pq.top();
		pq.pop();

		// If priorities are the same, choose alphabetically smaller path

		// If path is ending in the goal state, print path and exit
		if (cur == goal) {
			displayPath(cPQ);
			exit(0);
		}
		else {
			// Insert all children of the dequeued element, with cumulative costs as priority
			for(i = adjacent[cur].begin(); i != adjacent[cur].end(); ++i) {
				tPQ = cPQ;
				tPQ.path.push_back(*i);
				pos = find(adjacent[cur].begin(), adjacent[cur].end(), *i) - adjacent[cur].begin();
				tPQ.cost += weight[cur].at(pos);
				pq.push(tPQ);
			}
		}
	}
}

void Graph::displayPath(struct priorityQueue p)
{
  list<int>::iterator i;
//  cout << "Path: ";

  i = p.path.begin();
  cout << *i;
  p.path.pop_front();

  for (i = p.path.begin(); i != p.path.end(); ++i)
  {
    cout << "->" << *i;
  }
	cout << endl;
//  cout << "Path length: " << p.cost;
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

	int startDFS = 2, goalDFS = 1, startBFS = 2, goalBFS = 1;

	cout << "Depth-First Search (start node: " << startDFS << ", goal node: " << goalDFS << ")" << endl;
	g.DFS(startDFS,goalDFS);
	cout << endl;
	cout << "Breadth-First Search (start node: " << startBFS << ", goal node: " << goalBFS << ")" << endl;
	g.BFS(startBFS,goalBFS);
	cout << endl;

	// Create a graph with weights
	Graph s(7);
	s.addEdge(0, 1, 5);
	s.addEdge(0, 3, 3);
	s.addEdge(1, 2, 1);
	s.addEdge(2, 4, 6);
	s.addEdge(2, 6, 8);
	s.addEdge(3, 4, 2);
	s.addEdge(3, 5, 2);
	s.addEdge(4, 1, 1);
	s.addEdge(5, 6, 3);
	s.addEdge(6, 4, 4);

	int startUCS = 0, goalUCS = 6;

	cout << "Uniform-Cost-Search (start node: " << startUCS << ", goal node: " << goalUCS << ")" << endl;
	s.UCS(startUCS, goalUCS);


	return 0;
}
