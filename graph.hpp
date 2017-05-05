#ifndef graph_h_included
#define graph_h_included
#include <vector>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

/**
 *  Author: Zachary Clute
 *
 *  Acts as a wrapper around your boost graph so we can make comparisions within
 *  the graph and run algorithms cleanly
 */

typedef boost::adjacency_matrix<boost::undirectedS> BoostGraph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, BoostGraph> ERGen;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;

class Graph {

  public:
    BoostGraph* graph;

    Graph(BoostGraph*);
	  Graph(std::string);
    std::vector<Vertex> find_critical_nodes(int);
    BoostGraph* create_graph_from_input_file(std::string);
    bool adjacent_vertices_compare(const Vertex, const Vertex);
};

#endif
