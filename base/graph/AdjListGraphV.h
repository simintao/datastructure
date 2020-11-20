#include <iostream>
#include <queue>

#include "Vector.h"
namespace pcl {

struct Edge {
  int adjvex;
  int weight;
  Edge *next;
};

struct Vertex {
  int vertex;
  int indegree;
  int outdegree;
  Edge *next;
};

class Graph {
 private:
  int numVer;
  int numEdge;
  // Vertex *adjVector;
  pcl::Vector<Vertex> *adjVector;
  // pcl::List<int> *list;
  bool *visited;
  std::queue<int> que;

 public:
  explicit Graph(int numVer);
  void createGraph(int tail, int head, int weight);
  ~Graph();
  int getNumVer() { return numVer; }
  int getNumEdge() { return numEdge; }
  void insertEdge(int vertex, int adjvex, int weight);
  void deleteEdge(int tail, int head);
  void setWeight(int tail, int head, int weight);
  bool checkVer(int tail, int head);
  void printAdjVector();
  void BFS(int vertex);
  void DFS(int vertex);
  bool topological_sort();
};
}  // namespace pcl