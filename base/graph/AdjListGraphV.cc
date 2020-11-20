#include "AdjListGraphV.h"

#include <iostream>
#include <queue>

#include "List.h"
#include "Vector.h"
namespace pcl {

Graph::Graph(int numVer) {
  this->numVer = numVer;
  numEdge = 0;

  adjVector = new Vector<Vertex>(numVer);
  for (int i = 0; i < numVer; i++) {
    Vertex ver = {i, 0, 0, nullptr};
    adjVector->push_back(ver);
  }
}
Graph::~Graph() {
  Edge *p, *q;
  for (int i = 0; i < numVer; i++) {
    if ((*adjVector)[i].next) {
      p = (*adjVector)[i].next;
      while (p) {
        q = p->next;
        delete p;
        p = q;
      }
    }
  }
  delete adjVector;
}
bool Graph::checkVer(int tail, int head) {
  if (tail >= 0 && tail < numVer && head >= 0 && head < numVer)
    return true;
  else
    return false;
}
void Graph::createGraph(int tail, int head, int weight) {
  insertEdge(tail, head, weight);
}
void Graph::insertEdge(int tail, int head, int weight) {
  Edge *p, *q, *r;
  p = q = r = nullptr;
  if ((*adjVector)[tail].next) {
    p = (*adjVector)[tail].next;

    while (p && (p->adjvex < head)) {
      q = p;
      p = p->next;
    }
    if (p && (p->adjvex == head))
      p->weight = weight;
    else {
      r = new Edge;
      r->adjvex = head;
      r->weight = weight;
      r->next = p;

      if ((*adjVector)[tail].next == p)
        (*adjVector)[tail].next = r;
      else
        q->next = r;
      numEdge++;
      (*adjVector)[tail].outdegree++;
      (*adjVector)[head].indegree++;
    }
  } else {
    p = new Edge;
    p->adjvex = head;
    p->weight = weight;
    p->next = nullptr;
    (*adjVector)[tail].next = p;
    numEdge++;
    (*adjVector)[tail].outdegree++;
    (*adjVector)[head].indegree++;
  }
}
void Graph::printAdjVector() {
  Edge *edge = nullptr;
  for (int i = 0; i < this->numVer; i++) {
    edge = (*adjVector)[i].next;
    if (edge) {
      while (edge) {
        std::cout << "w(" << i << "," << edge->adjvex << ")=" << edge->weight
                  << "  ";
        edge = edge->next;
      }
      std::cout << std::endl;
    }
  }
}
void Graph::deleteEdge(int tail, int head) {
  Edge *p = (*adjVector)[tail].next;

  Edge *q = nullptr;

  while (p != nullptr) {
    if (p->adjvex == head) {
      break;
    }

    q = p;
    p = p->next;
  }

  if (p == nullptr) {
    std::cout << "边[" << (*adjVector)[tail].vertex << "->"
              << (*adjVector)[head].vertex << "]不存在。" << std::endl;
    return;
  }

  if (q == nullptr) {
    (*adjVector)[tail].next = p->next;
  }

  else {
    q->next = p->next;
  }

  delete p;
}
void Graph::BFS(int startVertex) {
  visited = new bool[numVer];
  for (int i = 0; i < numVer; i++) visited[i] = false;

  pcl::List<int> queue;

  visited[startVertex] = true;
  queue.push_back(startVertex);

  // pcl::List<int>::iterator it;
  Edge *e = nullptr;
  while (!queue.empty()) {
    int currVertex = queue.front();
    std::cout << "Visited " << currVertex << " ";
    queue.pop_front();
    e = (*adjVector)[currVertex].next;
    for (int i = 0; i < (*adjVector)[currVertex].outdegree; ++i) {
      int adjVertex = e->adjvex;
      if (!visited[adjVertex]) {
        visited[adjVertex] = true;
        queue.push_back(adjVertex);
      }
      e = e->next;
    }
  }
}
void Graph::DFS(int vertex) {
  visited[vertex] = true;
  // pcl::List<int> adjVector = list[vertex];

  std::cout << vertex << " ";

  // pcl::List<int>::iterator i;
  for (int i = 0; i < (*adjVector)[vertex].outdegree; ++i)
    if (!visited[i]) DFS(i);
}
bool Graph::topological_sort() {
  for (int i = 0; i < numVer; ++i)
    if ((*adjVector)[i].indegree == 0) que.push(i);

  int count = 0;
  while (!que.empty()) {
    int ver = que.front();
    que.pop();

    std::cout << ver << " ";
    ++count;

    // pcl::List<int>::iterator beg = adjVector[ver].begin();
    for (int i = 0; i < (*adjVector)[ver].outdegree; ++i)
      if (!(--(*adjVector)[i].indegree)) que.push(i);
  }

  if (count < numVer)
    return false;
  else
    return true;
}
}  // namespace pcl