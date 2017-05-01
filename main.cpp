#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include "ngraph.hpp"
#include "catch.hpp"
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

typedef boost::adjacency_matrix<boost::undirectedS> Graph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

bool DEBUG = true;

std::vector<int> find_critical_nodes_given_k(Graph graph, int k) {
  std::vector<int> nodes;

  boost::clear_vertex(3, graph);
  boost::clear_vertex(4, graph);

  return nodes;
}

Graph* create_graph_from_input_file(std::string filename) {
  int num_nodes, num_edges, size_of_s, u, v;
	std::ifstream input_file;
	input_file.open(filename);
	input_file >> num_nodes >> num_edges >> size_of_s;
	if(DEBUG) std::cout << "first line: " << num_nodes << " " << num_edges << " " << size_of_s << std::endl;
  Graph* input_graph = new Graph(num_nodes+1);

	while(input_file >> u >> v) {
		if(DEBUG) std::cout << "inserting: " << u << " " << v << std::endl;
    boost::add_edge(u, v, *input_graph);
	}

	input_file.close();
  return input_graph;
}

int main(void) {
	bool DEBUG = true;
  boost::minstd_rand gen;

  //use input file to create graph
	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;
  Graph* input_graph = create_graph_from_input_file("cnp.in");

  //find the critical nodes for the graph
  std::vector<int> junk = find_critical_nodes_given_k(*input_graph, 4);
  if(DEBUG) boost::print_graph(*input_graph);
  delete input_graph;

  //generate random graphs
  Graph random_graph(ERGen(gen, 100, .05), ERGen(), 100);

	return 0;
}
