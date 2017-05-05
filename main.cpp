#include <iostream>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <vector>
#include "graph.hpp"

bool DEBUG = true;

int main(void) {
  int num_nodes, num_edges, size_of_s, u, v;
	std::ifstream input_file;
  boost::minstd_rand gen;

	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;
	input_file.open("cnp.in");
	input_file >> num_nodes >> num_edges >> size_of_s;
  BoostGraph* input_graph = new BoostGraph(num_nodes+1);
	while(input_file >> u >> v)
    boost::add_edge(u, v, *input_graph);
  input_file.close();

  //use input file to create graph
  Graph graph(input_graph);
  std::cout << "original graph" << std::endl;
  if(DEBUG)boost::print_graph(*graph.graph);
  graph.find_and_sort_adjacent_vertices();
  graph.reduce_by_n_critical_nodes(size_of_s);
  if(DEBUG)std::cout << "reduced graph" << std::endl;
  if(DEBUG)boost::print_graph(*graph.graph);

  std::ofstream output_file("cnp.out");
  output_file << boost::num_edges(*graph.graph) << std::endl;
  for(auto const& node : graph.removed_nodes)
    output_file << "removed node: " << node << std::endl;


  //generate random graphs
  BoostGraph random_graph(ERGen(gen, 50, .05), ERGen(), 50);
  Graph ran_graph(&random_graph);
  if(DEBUG)std::cout << "original graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
  ran_graph.find_and_sort_adjacent_vertices();
  ran_graph.reduce_by_n_critical_nodes(5);
  std::cout << "reduced graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
  //for(auto const& node : ran_graph.removed_nodes)
  //  std::cout << "removed node: " << node << std::endl;

	return 0;
}
