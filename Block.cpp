#include <bits/stdc++.h>
#include "Block.h"
#include "Common.h"
using namespace std;

bool Block::file_exist(string &name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
void Block::append_boundary_node_to_file(Node node, const pair<int, int> cell_id)
{

    int overflow_count = g.get_cell_overflow_count(cell_id);
    bool edge_enabled = g.is_edge_enabled(cell_id);
    bool boundary_node_enabled = g.is_boundary_node_enabled(cell_id);
    ifstream infile;
    ofstream outfile;
    string filename;
    if (overflow_count > 0)
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "Contents of Overflow Disk block File. => (" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt" << endl;
            outfile << "?? Main Disk Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;

            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
        }
        outfile << to_string(node.id) << " " << to_string(node.x) << " " << to_string(node.y) << endl;
        outfile.close();
    }
    else
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ").txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "--Primary Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
        }
        outfile << to_string(node.id) << " " << fixed << setprecision(8) << node.x << " " << fixed << setprecision(8) << node.y << endl;
        outfile.close();
    }
}
void Block::append_node_to_file(Node node, const pair<int, int> cell_id)
{
    int overflow_count = g.get_cell_overflow_count(cell_id);
    ifstream infile;
    ofstream outfile;
    string filename;
    if (overflow_count > 0)
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "Content of Overflow Disk block File. => (" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt" << endl;
            outfile << "?? Main Disk Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
        }
        else
        {
            outfile.open(filename, ios_base::app);
        }
        outfile << to_string(node.id) << " " << fixed << setprecision(8) << node.x << " " << fixed << setprecision(8) << node.y << endl;
        outfile.close();
    }
    else
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ").txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "--Primary Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
        }
        else
        {
            outfile.open(filename, ios_base::app);
        }
        outfile << to_string(node.id) << " " << fixed << setprecision(8) << node.x << " " << fixed << setprecision(8) << node.y << endl;
        outfile.close();
    }
}

void Block::append_boundary_edge_to_file(Edge e, const pair<int, int> cell_id)
{
    int overflow_count = g.get_cell_overflow_count(cell_id);
    bool boundary_edge_enabled = g.is_boundary_edge_enabled(cell_id);
    bool edge_enabled = g.is_edge_enabled(cell_id);
    bool boundary_node_enabled = g.is_edge_enabled(cell_id);
    ifstream infile;
    ofstream outfile;
    string filename;
    if (overflow_count > 0)
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "Contents of Overflow Disk block File. => (" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt" << endl;
            outfile << "?? Main Disk Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
            // outfile << "Overflow Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ")_" << overflow_count << ".txt" << endl;

            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }

            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
            if (!boundary_edge_enabled)
            {
                outfile << "%%" << endl;
                g.update_boundary_edge_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
            if (!boundary_node_enabled)
            {
                outfile << "**" << endl;
                g.update_boundary_node_enabled(cell_id);
            }
            if (!boundary_edge_enabled)
            {
                outfile << "%%" << endl;
                g.update_boundary_edge_enabled(cell_id);
            }
        }
        outfile << to_string(e.nodeId1) << " " << to_string(e.nodeId2) << " " << e.weight << endl;
        outfile.close();
    }
    else
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ").txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "--Primary Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
            if (!boundary_edge_enabled)
            {
                outfile << "%%" << endl;
                g.update_boundary_edge_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!boundary_edge_enabled)
            {
                outfile << "%%" << endl;
                g.update_boundary_edge_enabled(cell_id);
            }
        }
        //outfile.open(filename, ios_base::app);
        // outfile << std::setprecision(18);
        outfile << to_string(e.nodeId1) << " " << to_string(e.nodeId2) << " " << e.weight << endl;
        outfile.close();
    }
}

void Block::append_edge_to_file(Edge e, const pair<int, int> cell_id)
{
    int overflow_count = g.get_cell_overflow_count(cell_id);
    bool edge_enabled = g.is_edge_enabled(cell_id);
    ifstream infile;
    ofstream outfile;
    string filename;
    if (overflow_count > 0)
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "Contents of Overflow Disk block File. => (" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt" << endl;
            outfile << "?? Main Disk Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
            // outfile << " ?? Overflow Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ")_" << overflow_count << ".txt" << endl;

            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
        }
        outfile << to_string(e.nodeId1) << " " << to_string(e.nodeId2) << " " << e.weight << endl;
        outfile.close();
    }
    else
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ").txt";
        if (!file_exist(filename))
        {
            outfile.open(filename, ios_base::app);
            outfile << "--Primary Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ").txt" << endl;
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
        }
        else
        {
            outfile.open(filename, ios_base::app);
            if (!edge_enabled)
            {
                outfile << "##" << endl;
                g.update_edge_enabled(cell_id);
            }
        }
        //outfile.open(filename, ios_base::app);
        // outfile << std::setprecision(18);
        outfile << to_string(e.nodeId1) << " " << to_string(e.nodeId2) << " " << e.weight << endl;
        outfile.close();
    }
}

void Block::append_overflow_marker_to_file(pair<int, int> cell_id)
{
    int overflow_count = g.get_cell_overflow_count(cell_id);
    ifstream infile;
    ofstream outfile;
    string filename;
    if (overflow_count > 0)
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ")_" + to_string(overflow_count) + ".txt";
        outfile.open(filename, ios_base::app);
        outfile << "?? Overflow Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ")_" + to_string(overflow_count + 1) + ".txt" << endl;
        outfile.close();
    }
    else
    {
        filename = "(" + to_string(cell_id.first) + "," + to_string(cell_id.second) + ").txt";
        outfile.open(filename, ios_base::app);
        outfile << "?? Overflow Block => CellId = (" << to_string(cell_id.first) << "," << to_string(cell_id.second) << ")_1.txt" << endl;
        outfile.close();
    }
}
void Block::insert_node_to_block(Node node, pair<int, int> cellId, int blockSize)
{
    if (nodes.size() < blockSize)
    {
        nodes.push_back(node);
        append_node_to_file(node, cellId);
    }
    else
    {
        // cout << "overflow" << endl;
        if (overflow == NULL)
        {
            overflow = new Block();
            append_overflow_marker_to_file(cellId);
            // grid_tracking[cellId.first][cellId.second]++;
            g.update_overflow_count(cellId);
        }
        overflow->insert_node_to_block(node, cellId, blockSize);
    }
}
void Block::insert_boundary_node_to_block(Node node, pair<int, int> cellId, int blockSize)
{
    if (nodes.size() + edges.size() + boundary_nodes.size() < blockSize)
    {
        boundary_nodes.push_back(node);
        append_boundary_node_to_file(node, cellId);
    }
    else
    {
        if (overflow == NULL)
        {
            overflow = new Block();
            append_overflow_marker_to_file(cellId);
            // grid_tracking[cellId.first][cellId.second]++;
            g.update_overflow_count(cellId);
            // append_overflow_marker_to_file(cellId);
            // cell->update_overflow_count();
            // grid[cellId.first][cellId.second].
        }
        overflow->insert_boundary_node_to_block(node, cellId, blockSize);
    }
}

void Block::insert_edge_to_block(Edge e, pair<int, int> cellId, int blockSize)
{
    if (nodes.size() + edges.size() < blockSize)
    {
        edges.push_back(e);
        append_edge_to_file(e, cellId);
    }
    else
    {
        if (overflow == NULL)
        {
            overflow = new Block();
            append_overflow_marker_to_file(cellId);
            g.update_overflow_count(cellId);
            // grid_tracking[cellId.first][cellId.second]++;
            // append_overflow_marker_to_file(cellId);
        }
        overflow->insert_edge_to_block(e, cellId, blockSize);
    }
}

void Block::insert_boundary_edge_to_block(Edge e, pair<int, int> cellId, int blockSize)
{
    if (nodes.size() + edges.size() + boundary_nodes.size() + boundary_edges.size() < blockSize)
    {
        boundary_edges.push_back(e);
        append_boundary_edge_to_file(e, cellId);
    }
    else
    {
        if (overflow == NULL)
        {
            overflow = new Block();
            append_overflow_marker_to_file(cellId);

            g.update_overflow_count(cellId);
            // grid_tracking[cellId.first][cellId.second]++;
            // append_overflow_marker_to_file(cellId);
        }
        overflow->insert_boundary_edge_to_block(e, cellId, blockSize);
    }
}

void Block::print_block(pair<int, int> cellId)
{
    cout << "cellId" << cellId.first << cellId.second << endl;
    Block *node = this;
    int overflow_count = 0;
    while (node)
    {

        if (overflow_count == 0)
            cout << "--Primary Block => CellId = (" << cellId.first << "," << cellId.second << ").txt" << endl;
        else if (overflow_count > 0)
            cout << "?? Overflow block => CellId = (" << cellId.first << "," << cellId.second << ")_" << overflow_count << ".txt" << endl;
        for (int i = 0; i < node->nodes.size(); i++)
        {
            cout << node->nodes[i].id << " " << node->nodes[i].x << " " << node->nodes[i].y << endl;
        }
        cout << "##" << endl;
        for (int i = 0; i < node->edges.size(); i++)
        {
            cout << node->edges[i].nodeId1 << " " << node->edges[i].nodeId2 << " " << node->edges[i].weight << endl;
        }
        cout << "**" << endl;
        for (int i = 0; i < node->boundary_nodes.size(); i++)
        {
            cout << node->boundary_nodes[i].id << " " << node->boundary_nodes[i].x << " " << node->boundary_nodes[i].y << endl;
        }
        cout << "%%" << endl;
        for (int i = 0; i < node->boundary_edges.size(); i++)
        {
            cout << node->boundary_edges[i].nodeId1 << " " << node->boundary_edges[i].nodeId2 << " " << node->boundary_edges[i].weight << endl;
        }
        node = node->overflow;
        overflow_count++;
    }
}

vector<Edge> Block::get_edges_with_in_block(){

    Block *node = this;
    vector<Edge> edge;
    while(node){
        for(int i = 0; i < node->edges.size();i++){
            edge.push_back(node->edges[i]);
        }
        node = node->overflow;
    }
    return edge;
}

vector<Edge> Block::get_boundary_edges_with_in_block(){

    Block *node = this;
    vector<Edge> boundaryEdge;
    while(node){
        for(int i = 0; i < node->boundary_edges.size();i++){
            boundaryEdge.push_back(node->boundary_edges[i]);
        }
        node = node->overflow;
    }
    return boundaryEdge;
}

vector<Node> Block::get_nodes_with_in_block(){
    Block *node = this;
    vector<Node> nodes;
    while(node){
        for(int i = 0; i < node->nodes.size();i++){
            nodes.push_back(node->nodes[i]);
        }
        node = node->overflow;
    }
    return nodes;
}

vector<Node> Block::get_boundary_nodes_with_in_block(){
    Block *node = this;
    vector<Node> boundaryNodes;
    while(node){
        for(int i = 0; i < node->boundary_nodes.size();i++){
            boundaryNodes.push_back(node->boundary_nodes[i]);
        }
        node = node->overflow;
    }
    return boundaryNodes;
}