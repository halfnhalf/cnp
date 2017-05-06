#include "graph.hpp"

Graph::Graph(BoostGraph* a_graph) {
  graph = a_graph;
}

Graph::Graph(std::string input_file_name) {
  graph = this->create_graph_from_input_file(input_file_name);
}

void Graph::reduce_by_n_critical_nodes(int num) {
  for(int i = 0; i < num; i++) {
    removed_nodes.push_back(sorted_nodes.at(i));
    boost::clear_vertex(sorted_nodes.at(i), *graph);
  }
}

std::vector<Vertex> Graph::find_and_sort_adjacent_vertices() {
  std::vector<Vertex> nodes;
  BoostGraph::vertex_iterator vertexIt, vertexEnd;
  boost::tie(vertexIt, vertexEnd) = boost::vertices(*graph);
  nodes.push_back(*vertexIt);
  ++vertexIt;

  for(; vertexIt != vertexEnd; ++vertexIt) {
    int num_adjacent_edges_i;
    BoostGraph::adjacency_iterator adjBegin, adjEnd;

    boost::tie(adjBegin, adjEnd) = boost::adjacent_vertices(*vertexIt, *this->graph);
    num_adjacent_edges_i = std::distance(adjBegin, adjEnd);
    //std::cout << num_adjacent_edges_i << std::endl;
    
    bool did_insert = false;

    for(auto vertexIt2 = nodes.begin(); vertexIt2 != nodes.end(); ++vertexIt2) {
      int num_adjacent_edges_j;
      BoostGraph::adjacency_iterator adjBegin2, adjEnd2;

      boost::tie(adjBegin2, adjEnd2) = boost::adjacent_vertices(*vertexIt2, *this->graph);
      num_adjacent_edges_j = std::distance(adjBegin2, adjEnd2);
      //std::cout << "nodes: " << num_adjacent_edges_j << " " << num_adjacent_edges_i << std::endl;

      if(num_adjacent_edges_i > num_adjacent_edges_j) {
        nodes.insert(vertexIt2, *vertexIt);
        did_insert = true;
        break;
      }
    }

    if(!did_insert)
      nodes.push_back(*vertexIt);
  }

  this->sorted_nodes = nodes;
  return nodes;
}

BoostGraph* Graph::create_graph_from_input_file(std::string filename) {
  int num_nodes, num_edges, size_of_s, u, v;
	std::ifstream input_file;
	input_file.open(filename);
	input_file >> num_nodes >> num_edges >> size_of_s;
  BoostGraph* input_graph = new BoostGraph(num_nodes+1);

	while(input_file >> u >> v) {
    boost::add_edge(u, v, *input_graph);
	}

	input_file.close();
  return input_graph;
}
