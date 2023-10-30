#include <bits/stdc++.h>
#include "Cell.h"
#include "Block.h"
#include "Common.h"
using namespace std;

Cell::Cell()
{

    overflow_count = 0;
    edge_enabled = false;
    boundary_edge_enabled = false;
    boundary_node_enabled = false;
    cellProcessed = false;
}
Cell::Cell(pair<int, int> cellId, pair<double, double> cellMin, pair<double, double> cellMax)
{
    cell_id.first = cellId.first;
    cell_id.second = cellId.second;
    cell_max.first = cellMax.first;
    cell_max.second = cellMax.second;
    cell_min.first = cellMin.first;
    cell_min.second = cellMin.second;
    block = new Block();
    overflow_count = 0;
    edge_enabled = false;
    boundary_node_enabled = false;
    boundary_edge_enabled = false;
    cellProcessed = false;
}
int Cell::get_cell_overflow_count()
{
    return this->overflow_count;
}
void Cell::update_overflow_count()
{
    this->overflow_count = this->overflow_count + 1;
}
void Cell::print_cell()
{
    if (this)
    {
        cout << "Cell Id =>";
        print_pair(this->cell_id);
        cout << "Cell Min Cordinates =>";
        print_pair(this->cell_min);
        cout << "Cell Max Cordinates =>";
        print_pair(this->cell_max);
        cout << "Print blocks => " << endl;

        if (this->block)
        {
            this->block->print_block(this->cell_id);
            cout << endl;
        }
    }
}

void Cell::print_cell_files()
{
    cout << "Cell Id =>";
    print_pair(this->cell_id);
    cout << "Cell Min Cordinates =>";
    print_pair(this->cell_min);
    cout << "Cell Max Cordinates =>";
    print_pair(this->cell_max);
    cout << "Print blocks => " << endl;
    pair<int, int> cellId = this->cell_id;
    int overflow_count = this->overflow_count;
    string filename = "(" + to_string(cellId.first) + "," + to_string(cellId.second) + ").txt";
    ifstream infile(filename);
    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            cout << line << endl;
        }
    }
    infile.close();
    if (overflow_count > 0)
    {
        int i = 0;
        while (i <= overflow_count)
        {
            filename = "(" + to_string(cellId.first) + "," + to_string(cellId.second) + ")_" + to_string(i) + ".txt";
            ifstream infile(filename);
            if (infile.is_open())
            {
                string line;
                while (getline(infile, line))
                {
                    cout << line << endl;
                }
            }
            i++;
            infile.close();
        }
    }
}
void Cell::print_pair(const pair<int, int> p)
{
    cout << "<" << p.first << "," << p.second << ">" << endl;
}

bool Cell::is_edge_enabled()
{
    return this->edge_enabled;
}

void Cell::update_edge_enabled()
{
    this->edge_enabled = true;
}

bool Cell::is_boundary_node_enabled()
{
    return this->boundary_node_enabled;
}

void Cell::update_boundary_node_enabled()
{
    this->boundary_node_enabled = true;
}

bool Cell::is_boundary_edge_enabled()
{
    return this->boundary_edge_enabled;
}

void Cell::update_boundary_edge_enabled()
{
    this->boundary_edge_enabled = true;
}

void Cell::insert_node_to_cell(Node node, pair<int, int> cellId, int blockSize)
{
    // cout << "cellId" << endl;
    // print_pair(cellId);
    block->insert_node_to_block(node, cellId, blockSize);
}

void Cell::insert_boundary_node_to_cell(Node node, pair<int, int> cellId, int blockSize)
{
    block->insert_boundary_node_to_block(node, cellId, blockSize);
}
void Cell::insert_boundary_edge_to_cell(Edge e, pair<int, int> cellId, int blockSize)
{
    block->insert_boundary_edge_to_block(e, cellId, blockSize);
}

void Cell::insert_edge_to_cell(Edge e, pair<int, int> cellId, int blockSize)
{

    block->insert_edge_to_block(e, cellId, blockSize);
}
vector<Edge> Cell::get_edges_with_in_cell()
{
    vector<Edge> edge;
    if (this)
    {
        edge = this->block->get_edges_with_in_block();
    }
    return edge;
}
int Cell::digits_only(string s) // "123" "-3"
{
    int i =0;
    while (i < s.length())
    {

        if (isdigit(s[i++]) == 0)
            return 0;
    }

    return 1;
}


vector<Edge> Cell::get_boundary_edges_with_in_cell()
{
    vector<Edge> boundaryEdge;
    if (this)
    {
        boundaryEdge = this->block->get_boundary_edges_with_in_block();
    }
    return boundaryEdge;
}

vector<Node> Cell::get_nodes_with_in_cell()
{
    vector<Node> node;
    if (this)
    {
        node = this->block->get_nodes_with_in_block();
    }
    return node;
}

vector<Node> Cell::get_boundary_nodes_with_in_cell()
{
    vector<Node> boundaryNode;
    if (this)
    {
        boundaryNode = this->block->get_boundary_nodes_with_in_block();
    }
    return boundaryNode;
}

bool Cell::is_cell_processed()
{
    // if(this){
    return this->cellProcessed;
    // }
}

void Cell::update_cell_processed()
{
    this->cellProcessed = true;
}