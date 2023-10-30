#ifndef GRID_H__
#define GRID_H__
#include <bits/stdc++.h>
#include "Cell.h"
#include "Edge.h"
using namespace std;
class Grid : public Cell
{
    vector<vector<Cell>> grid;
    map<int, pair<double, double>> node_map;
    double gridMinX, gridMinY, gridMaxX, gridMaxY, gridWidth, gridHeight;
    int cell_size, gridRow, gridCol;
    map<pair<int, int>, set<int>> boundary_nodes;
    vector<tuple<Edge, pair<int, int>, pair<int, int>>> boundary_edges;
    int V;
    list<pair<int, double>> *adj;



public:
    Grid();
    Grid(vector<pair<double, double>> v, int k);
    void update_overflow_count(pair<int, int> cellId);
    int get_cell_overflow_count(pair<int, int> cellId);
    bool is_edge_enabled(pair<int, int> cellId);
    void update_edge_enabled(pair<int, int> cellId);
    bool is_boundary_edge_enabled(pair<int, int> cellId);
    void update_boundary_edge_enabled(pair<int, int> cellId);
    bool is_boundary_node_enabled(pair<int, int> cellId);
    void update_boundary_node_enabled(pair<int, int> cellId);
    void print_grid_size();
    void print_grid();
    void initialize_grid(vector<pair<double, double>> v, int k, vector<tuple<int, double, double>> node_tuple);
    pair<int, int> get_cell_id(double x, double y);
    pair<double, double> get_node_cordinates(int nodeId);
    bool invalid_pair(pair<double, double> cord);
    bool invalid_cell_id(pair<int, int> cellId);
    bool compare_pair(pair<int, int> p1, pair<int, int> p2);
    void insert_nodes(string filename, int blockSize);
    void insert_edges(map<pair<int, int>, string> e_map, int blockSize);
    void insert_boundary_nodes(int blockSize);
    void insert_boundary_edges(int blockSize);
    void visualize_grid();
    void visualize_cell_by_nodeId(int nodeId);
    vector<string> tokenize(string s, char del);
    void compute_shortest_path_on_grid(int source,int destination);
    void shortest_path(int source,int destination);
    bool is_cell_processed(pair<int,int>cellId);
    void update_cell_processed(pair<int,int> cellId);
    void add_edge(Edge e);
    bool is_edge_present(Edge e);
    void find_path(int source,int destination);
    void print_adjancey_list();
    vector<Edge> read_edges_from_cell_file(pair<int,int>cellId, int overflow_count);
    void reset_adjancey_list();

};
#endif