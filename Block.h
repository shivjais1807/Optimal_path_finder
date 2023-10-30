
#ifndef BLOCK_H__
#define BLOCK_H__
#include "Node.h"
#include "Edge.h"
using namespace std;
class Block
{
    vector<Node> nodes;
    vector<Edge> edges;
    vector<Node> boundary_nodes;
    vector<Edge> boundary_edges;
    Block *overflow;
public:
    Block()
    {
        overflow = NULL;
    }
    void append_overflow_marker_to_file(pair<int, int> cellId);
    void append_node_to_file(Node node, pair<int, int> cellId);
    void append_edge_to_file(Edge edge, pair<int, int> cellId);
    void append_boundary_node_to_file(Node node, pair<int, int> cellId);
    void append_boundary_edge_to_file(Edge edge, pair<int, int> cellId);
    void insert_node_to_block(Node node, pair<int, int> cellId, int blockSize);
    void insert_boundary_node_to_block(Node node, pair<int, int> cellId, int blockSize);
    void insert_boundary_edge_to_block(Edge edge, pair<int, int> cellId, int blockSize);
    void insert_edge_to_block(Edge e, pair<int, int> cellId, int blockSize);
    bool file_exist(string &filename);
    void print_block(pair<int, int> cellId);
    vector<Edge> get_edges_with_in_block();
    vector<Edge> get_boundary_edges_with_in_block();
    vector<Node> get_nodes_with_in_block();
    vector<Node> get_boundary_nodes_with_in_block();
};
#endif