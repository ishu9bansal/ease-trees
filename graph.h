#ifndef graph_h
#define graph_h

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template <class T>
class graph {
protected:
	unordered_map<T, int> dataMap;
	T findByValue(int i) {
		for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it)
			if (it->second == i)
				return it->first;
	}
public:
	graph() {
	}
	~graph() {
		dataMap.clear();
	}
	virtual bool checkVertex(const T& node) {
		return dataMap.find(node) != dataMap.end();
	}
	virtual bool addVertex(const T& node) = 0;	// pure virtual function
	virtual void removeVertex(int nodeIndex) = 0;	// pure virtual function
	virtual bool checkEdge(int, int, bool) = 0;	// pure virtual function
	virtual bool checkEdge(int a, int b) {
		return checkEdge(a, b, true) || checkEdge(a, b, false);
	}
	virtual void addEdge(int, int, bool) = 0;		// pure virtual function
	virtual void addEdge(int a, int b) {
		addEdge(a, b, true);
		addEdge(a, b, false);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		addEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB) {
		addEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, vector<bool> newToOld) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		for (int i = 0; i<nodeList.size(); i++)
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld[i]);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, bool newToOld) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		for (int i = 0; i<nodeList.size(); i++)
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		int s = nodeList.size();
		for (int i = 0; i<s; i++)
			addEdge(nodeIndex, dataMap[nodeList[i]]);
		return;
	}
	virtual void removeEdge(int, int, bool) = 0;		// pure virtual function
	virtual void removeEdge(int a, int b) {
		removeEdge(a, b, true);
		removeEdge(a, b, false);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual vector<int> getChildren(int) = 0;		// pure virtual function
	virtual vector<int> getParents(int) = 0;		// pure virtual function
	virtual vector<int> getAdjacent(int x) {
		vector<int> children = getChildren(x);
		vector<int> result = getParents(x);
		result.insert(result.end(), children.begin(), children.end());
		return result;
	}
	virtual vector<int> getChildren(const T& node) {
		return getChildren(dataMap[node]);
	}
	virtual vector<int> getParents(const T& node) {
		return getParents(dataMap[node]);
	}
	virtual vector<int> getAdjacent(const T& node) {
		return getAdjacent(dataMap[node]);
	}
	virtual void removeEdgesFrom(int nodeIndex) {
		vector<int> adjacent = getChildren(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], true);
	}
	virtual void removeEdgesFrom(const T& node) {
		removeEdgesFrom(dataMap[node]);
	}
	virtual void removeEdgesTo(int nodeIndex) {
		vector<int> adjacent = getParents(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], false);
	}
	virtual void removeEdgesTo(const T& node) {
		removeEdgesTo(dataMap[node]);
	}
	virtual void removeEdgesOf(int nodeIndex) {
		removeEdgesFrom(nodeIndex);
		removeEdgesTo(nodeIndex);
	}
	virtual void removeEdgesOf(const T& node) {
		return removeEdgesOf(dataMap[node]);
	}
	virtual void removeVertex(const T& node) {
		removeVertex(dataMap[node]);
	}
	virtual void change(const T& nodeA, const T& nodeB) {
		int temp = dataMap[nodeA];
		dataMap[nodeA] = dataMap[nodeB];
		dataMap[nodeB] = temp;
	}
	virtual void print() {

		cout << "Vetex Mapping:" << endl;
		for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it) {
			cout << it->second << "\t" << it->first << endl;
		}
	}

};

#endif // !graph_h
