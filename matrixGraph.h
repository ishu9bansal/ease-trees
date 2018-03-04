#ifndef matrix_graph_h
#define matrix_graph_h

#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include "SquareVector.h"

template <class T>
class matrixGraph : public graph<T> {
	vectorSquare<int> edgeMap;
public:
	using graph<T>::addVertex;
	using graph<T>::removeVertex;
	bool checkEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		return edgeMap(x, y);
	}
	bool addVertex(const T& node) {
		if (this->checkVertex(node))	return false;
		this->dataMap[node] = edgeMap.size();
		edgeMap.addOne();
		return true;
	}
	void addEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = 1;
		return;
	}
	void removeEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = 0;
		return;
	}
	vector<int> getChildren(int x) {
		vector<int> result;
		for (int i = 0; i<edgeMap.size(); i++) {
			if (edgeMap(x, i))	result.push_back(i);
		}
		return result;
	}
	vector<int> getParents(int x) {
		vector<int> result;
		for (int i = 0; i<edgeMap.size(); i++) {
			if (edgeMap(i, x))	result.push_back(i);
		}
		return result;
	}
	void removeVertex(int nodeIndex) {
		this->removeEdgesOf(nodeIndex);
		this->dataMap.erase(this->findByValue(nodeIndex));
		edgeMap.remove(nodeIndex);
		this->dataMap[this->findByValue(edgeMap.size())] = nodeIndex;
		return;
	}
	void print() {
		cout << "Total vertices in graph: " << edgeMap.size() << endl;
		graph<T>::print();
		cout << "Edge mapping:" << endl;
		cout << edgeMap << endl;
		return;
	}

};

void testMatrixGraph();

#endif // !matrix_graph_h
