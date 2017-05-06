#include <iostream>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <vector>
#include "graph.hpp"

bool DEBUG = false;

void random_graphs_fixed_k(int graph_size) {
  boost::minstd_rand gen;
  int k = 5;

  BoostGraph random_graph(ERGen(gen, graph_size, .05), ERGen(), graph_size);
  Graph ran_graph(&random_graph);
  std::cout << "with k fixed to 5. generating graph of size: " << graph_size << " with " << boost::num_edges(*ran_graph.graph) << " edges." << std::endl;
  if(DEBUG)std::cout << "original graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
  ran_graph.find_and_sort_adjacent_vertices();
  ran_graph.reduce_by_n_critical_nodes(k);

  std::cout << "removed these nodes:" << std::endl;
  for(auto const& node : ran_graph.removed_nodes)
    std::cout << node << std::endl;
  std::cout << "removed 5 nodes and the graph now has a pairwise connectivity of:  " << boost::num_edges(*ran_graph.graph) << std::endl;
  if(DEBUG)std::cout << "reduced graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
}

void random_graphs_fixed_size(int k) {
  boost::minstd_rand gen;
  int size = 100;

  BoostGraph random_graph(ERGen(gen, size, .05), ERGen(), size);
  Graph ran_graph(&random_graph);

  std::cout << "with size fixed to 100. generating graph with size of " << boost::num_edges(*ran_graph.graph) << " and removing " << k << " nodes." << std::endl;
  if(DEBUG)std::cout << "original graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
  ran_graph.find_and_sort_adjacent_vertices();
  ran_graph.reduce_by_n_critical_nodes(k);

  std::cout << "removed these nodes:" << std::endl;
  for(auto const& node : ran_graph.removed_nodes)
    std::cout << node << std::endl;
  std::cout << "the graph now has a pairwise connectivity of:  " << boost::num_edges(*ran_graph.graph) << std::endl;

  if(DEBUG)std::cout << "reduced graph" << std::endl;
  if(DEBUG)boost::print_graph(*ran_graph.graph);
}

int main(void) {
  int num_nodes, num_edges, size_of_s, u, v;
	std::ifstream input_file;

	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;
	input_file.open("cnp.in");
	input_file >> num_nodes >> num_edges >> size_of_s;
  BoostGraph* input_graph = new BoostGraph(num_nodes+1);
	while(input_file >> u >> v)
    boost::add_edge(u, v, *input_graph);
  input_file.close();

  //use input file to create graph
  Graph graph(input_graph);
  if(DEBUG)std::cout << "original graph" << std::endl;
  if(DEBUG)boost::print_graph(*graph.graph);
  graph.find_and_sort_adjacent_vertices();
  graph.reduce_by_n_critical_nodes(size_of_s);
  if(DEBUG)std::cout << "reduced graph" << std::endl;
  if(DEBUG)boost::print_graph(*graph.graph);

  std::ofstream output_file("cnp.out");
  output_file << boost::num_edges(*graph.graph) << std::endl;
  for(auto const& node : graph.removed_nodes)
    output_file << "removed node: " << node << std::endl;
  output_file.close();


  //generate random graphs of fixed k in seperate scopes so graphs are garbaged after use
  for(int i = 50; i <= 500; i+=50) {
    std::cout << std::endl;
    random_graphs_fixed_k(i);
  }

  for(int i = 5; i <= 50; i+=5) {
    std::cout << std::endl;
    random_graphs_fixed_size(i);
  }
  //for(auto const& node : ran_graph.removed_nodes)
  //  std::cout << "removed node: " << node << std::endl;

	return 0;
}

