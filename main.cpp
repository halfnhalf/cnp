#include <iostream>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <vector>
#include "graph.hpp"

bool DEBUG = true;

//bool compare_num_adjacent_edges(Vertex i, Vertex j) {
//  int num_adjacent_edges_i, num_adjacent_edges_j;
//  BoostGraph::vertex_iterator vertexIt, vertexEnd;
//
//  boost::tie(vertexIt, vertexEnd) = boost::adjacent_vertices(i, );
//}
//

int main(void) {
	bool DEBUG = true;
  boost::minstd_rand gen;

  //use input file to create graph
	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;
  Graph graph("cnp.in");
  boost::print_graph(*graph.graph);

  //find the critical nodes for the graph
  std::vector<Vertex> junk = graph.find_critical_nodes(4);

  //generate random graphs
  BoostGraph random_graph(ERGen(gen, 100, .05), ERGen(), 100);

	return 0;
}
