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

std::vector<int> find_critical_nodes_given_k(Graph graph, int k) {
  std::vector<int> nodes;

  boost::clear_vertex(3, graph);
  boost::clear_vertex(4, graph);


  return nodes;
}

int main(void) {
	int num_nodes, num_edges, size_of_s, u, v; 
	std::ifstream input_file;
	bool debug = true;
  boost::minstd_rand gen;

  //use input file to create graph
	input_file.open("cnp.in");
	std::cout << "CMSC 401 project by Zachary Clute" << std::endl;
	input_file >> num_nodes >> num_edges >> size_of_s;
	if(debug) std::cout << "first line: " << num_nodes << " " << num_edges << " " << size_of_s << std::endl;
  Graph* input_graph = new Graph(num_nodes+1);
	while(input_file >> u >> v) {
		if(debug) std::cout << "inserting: " << u << " " << v << std::endl;
    boost::add_edge(u, v, *input_graph);
	}
	input_file.close();
  assert(boost::num_edges(*input_graph) == num_edges);

  //find the critical nodes for the graph
  std::vector<int> junk = find_critical_nodes_given_k(*input_graph, 4);
  if(debug) boost::print_graph(*input_graph);
  delete input_graph;

  //generate random graphs
  Graph random_graph(ERGen(gen, 100, .05), ERGen(), 100);

	return 0;
}
