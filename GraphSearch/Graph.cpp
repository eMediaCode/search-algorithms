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
			cout << " ";
			DFSHelper(*i, goal, visited);
		}
	}
}

void Graph::DFSHelper(int start, int goal1, int goal2, bool visited[]) {
	// Mark the current node as visited and print
	visited[start] = true;
	cout << start;

	// Recur for all adjacent nodes, as long as goal has not yet been visited
	vector<int>::iterator i;
	for(i = adjacent[start].begin(); i != adjacent[start].end(), visited[goal1] != true, visited[goal2] != true; i++) {
		if(!visited[*i]) {
			cout << " ";
			DFSHelper(*i, goal1, goal2, visited);
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

void Graph::DFS(int start, int goal1, int goal2) {
	if (start == goal1 || start == goal2) {
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
		DFSHelper(start, goal1, goal2, visited);
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

void Graph::BFS(int start, int goal1, int goal2) {
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
		if (start == goal1 || start == goal2) {
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

void Graph::UCS(int start, int goal1, int goal2) {
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
		if (cur == goal1 || cur == goal2) {
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

void Graph::AStarTS(int start, int goal) {

}

void Graph::AStarGS(int start, int goal) {

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
    cout << " " << *i;
  }
	cout << endl;
//  cout << "Path length: " << p.cost;
}

int main() {

	// Graph 1
	Graph g1(5);
	g1.addEdge(0, 1); // 0 is S, 1 is A
	g1.addEdge(0, 2); // 2 is B
	g1.addEdge(1, 2);
	g1.addEdge(1, 4); // 4 is G
	g1.addEdge(2, 3); // 3 is C
	g1.addEdge(3, 4);

	g1.DFS(0, 4);
	g1.BFS(0, 4);
	cout << endl;

	// Graph 2
	Graph g2(5);
	g2.addEdge(0, 2); // 0 is S, 3 is C
	g2.addEdge(0, 3); // 2 is B
	g2.addEdge(1, 4); // 4 is G
	g2.addEdge(2, 1); // 1 is A
	g2.addEdge(3, 2);

	g2.DFS(0, 4);
	g2.BFS(0, 4);
	cout << endl;

	// Graph 3
	Graph g3(5);
	g3.addEdge(0, 1); // 0 is S, 1 is B
	g3.addEdge(0, 2); // 2 is C
	g3.addEdge(1, 3); // 3 is A
	g3.addEdge(1, 4); // 4 is G
	g3.addEdge(2, 3);
	g3.addEdge(3, 4);

	g3.DFS(0, 4);
	g3.BFS(0, 4);
	cout << endl;

	// Graph 4
	Graph g4(9);
	g4.addEdge(0, 1, 1);
	g4.addEdge(0, 2, 3);
	g4.addEdge(1, 4, 2);
	g4.addEdge(2, 4, 8);
	g4.addEdge(2, 5, 5);
	g4.addEdge(3, 1, 1);
	g4.addEdge(3, 7, 4);
	g4.addEdge(4, 3, 5);
	g4.addEdge(4, 7, 14);
	g4.addEdge(4, 8, 6);
	g4.addEdge(5, 6, 1);
	g4.addEdge(5, 8, 4);
	g4.addEdge(6, 8, 2);
	g4.addEdge(7, 8, 0);

	g4.DFS(0, 7, 8);
	g4.BFS(0, 7, 8);
	g4.UCS(0, 7, 8);
	cout << endl;

	// Graph 5
	Graph g5(6);
	g5.addEdge(0, 1, 2);
	g5.addEdge(0, 2, 1);
	g5.addEdge(1, 2, 1);
	g5.addEdge(1, 3, 3);
	g5.addEdge(1, 4, 1);
	g5.addEdge(2, 4, 5);
	g5.addEdge(2, 5, 10);
	g5.addEdge(3, 5, 7);
	g5.addEdge(4, 5, 4);

//	g5.DFS(0, 5);
//	g5.BFS(0, 5);
//	g5.UCS(0, 5);
	cout << endl;

	return 0;
}
