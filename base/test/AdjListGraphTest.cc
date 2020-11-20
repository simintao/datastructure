
#include <iostream>

#include "AdjListGraphV.h"
#include "gtest/gtest.h"

using pcl::Graph;

TEST(AdjGraphTest, test) {
  Graph graph(7);
  graph.createGraph(0, 1, 3);
  graph.createGraph(0, 2, 5);
  graph.createGraph(2, 3, 4);
  graph.createGraph(2, 4, 2);
  graph.createGraph(4, 5, 3);
  graph.createGraph(5, 6, 3);
  graph.printAdjVector();
  graph.insertEdge(2, 5, 5);
  graph.printAdjVector();
  graph.deleteEdge(2, 5);
}