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
  boost::minstd_rand gen;

	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;

  //use input file to create graph
  Graph graph("cnp.in");
  std::cout << "original graph" << std::endl;
  boost::print_graph(*graph.graph);
  graph.find_and_sort_adjacent_vertices();
  graph.reduce_to_n_pairwise(4);
  std::cout << "reduced graph" << std::endl;
  boost::print_graph(*graph.graph);
  for(auto const& node : graph.removed_nodes)
    std::cout << "removed node: " << node << std::endl;

  //generate random graphs
  BoostGraph random_graph(ERGen(gen, 50, .05), ERGen(), 50);
  Graph ran_graph(&random_graph);
  std::cout << "original graph" << std::endl;
  boost::print_graph(*ran_graph.graph);
  ran_graph.find_and_sort_adjacent_vertices();
  ran_graph.reduce_to_n_pairwise(5);
  std::cout << "reduced graph" << std::endl;
  boost::print_graph(*ran_graph.graph);
  for(auto const& node : ran_graph.removed_nodes)
    std::cout << "removed node: " << node << std::endl;

	return 0;
}
