#include "Grid.h"
#include "Common.h"
#define INF INFINITY
#define NIL -1
#define PERM 1
#define TEMP 0

// using namespace std;
Grid::Grid()
{
    // edge_enabled = false;
    // boundary_node_enabled = false;
    // boundary_edge_enabled = false;
}
Grid::Grid(vector<pair<double, double>> v, int k)
{
    gridMinX = v[0].first;
    gridMaxX = v[1].first;
    gridMinY = v[0].second;
    gridMaxY = v[1].second;
    gridWidth = gridMaxX - gridMinX;
    gridHeight = gridMaxY - gridMinY;
    gridCol = (gridWidth + k - 1) / k;
    gridRow = (gridHeight + k - 1) / k;
    cell_size = k;
    // edge_enabled = false;
    // boundary_node_enabled = false;
    // boundary_edge_enabled = false;
}

void Grid::update_overflow_count(pair<int, int> cellId)
{
    grid[cellId.first][cellId.second].update_overflow_count();
}

int Grid::get_cell_overflow_count(pair<int, int> cellId)
{

    return grid[cellId.first][cellId.second].get_cell_overflow_count();
}

bool Grid::is_edge_enabled(pair<int, int> cellId)
{

    return grid[cellId.first][cellId.second].is_edge_enabled();
}

void Grid::update_edge_enabled(pair<int, int> cellId)
{

    grid[cellId.first][cellId.second].update_edge_enabled();
}

bool Grid::is_boundary_edge_enabled(pair<int, int> cellId)
{

    return grid[cellId.first][cellId.second].is_boundary_edge_enabled();
}

void Grid::update_boundary_edge_enabled(pair<int, int> cellId)
{

    grid[cellId.first][cellId.second].update_boundary_edge_enabled();
}

bool Grid::is_boundary_node_enabled(pair<int, int> cellId)
{

    return grid[cellId.first][cellId.second].is_boundary_node_enabled();
}

void Grid::update_boundary_node_enabled(pair<int, int> cellId)
{

    grid[cellId.first][cellId.second].update_boundary_node_enabled();
}
void Grid::print_grid_size()
{
    cout << "Total Cells = " << gridRow * gridCol << endl;
    // cout << "gridRow = " << gridRow << endl;
    // cout << "gridCol = " << gridCol << endl;
}
void Grid::print_grid()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            // if( grid[i][j] != NULL )
            grid[i][j].print_cell();
        }
        cout << endl;
    }
}

void Grid::initialize_grid(vector<pair<double, double>> v, int k, vector<tuple<int, double, double>> node_tuple)
{

    int V = node_tuple.size();
    this->V = V + 1;
    adj = new list<pair<int, double>>[V + 1];
    // vector<int> temp(V + 1, NIL);
    // predecessor = temp;
    // vector<double> pathTemp(V + 1, INF);
    // pathLength = pathTemp;
    // vector<bool> status_temp(V + 1, false);
    // status = status_temp;
    gridMinX = v[0].first;
    gridMaxX = v[1].first;
    gridMinY = v[0].second;
    gridMaxY = v[1].second;
    gridWidth = gridMaxX - gridMinX;
    gridHeight = gridMaxY - gridMinY;
    gridCol = (gridWidth + k - 1) / k;
    gridRow = (gridHeight + k - 1) / k;
    cell_size = k;
    double x = gridMinX;
    double y = gridMinY;
    int i = 0;
    int j = 0;

    for (int i = 0; i < node_tuple.size(); i++)
    {

        node_map.insert({get<0>(node_tuple[i]), make_pair(get<1>(node_tuple[i]), get<2>(node_tuple[i]))});
    }

    while (x <= gridMaxX)
    {
        y = gridMinY;
        vector<Cell> v;
        j = 0;
        while (y <= gridMaxY)
        {
            Cell cell(make_pair(i, j), make_pair(x, y), make_pair(x + cell_size, y + cell_size));
            v.push_back(cell);
            y += cell_size;
            j++;
        }
        if (v.size() > 0)
        {
            grid.push_back(v);
        }
        x += cell_size;
        i++;
    }
}

pair<int, int> Grid::get_cell_id(double x, double y)
{
    int i, j;
    i = (int)((x - gridMinX) / cell_size);
    j = (int)((y - gridMinY) / cell_size);
    // if( i <= gridRow && j <= gridCol )
    return make_pair(i, j);
}

pair<double, double> Grid::get_node_cordinates(int nodeId)
{
    if (node_map.find(nodeId) == node_map.end())
    {
        return make_pair(-1, -1);
    }
    else
        return node_map[nodeId];
}

bool Grid::invalid_pair(pair<double, double> cord)
{
    return cord.first < 0 || cord.second < 0;
}

bool Grid::invalid_cell_id(pair<int, int> cellId)
{
    return cellId.first < 0 || cellId.second < 0;
}

bool Grid::compare_pair(pair<int, int> p1, pair<int, int> p2)
{
    return (p1.first == p2.first && p1.second == p2.second);
}

vector<string> Grid::tokenize(string s, char del)
{
    vector<string> tokens;
    // stringstream class check1
    stringstream check1(s);
    string intermediate;
    // Tokenizing w.r.t. space ','
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

void Grid::insert_nodes(string filename, int blockSize)
{
    string line;
    ifstream datasetfile(filename);
    if (datasetfile.is_open())
    {
        vector<double> x_cordinate;
        vector<double> y_cordinate;
        while (getline(datasetfile, line))
        {
            vector<string> v = tokenize(line, ' ');
            int nodeId = stoi(v[0]);
            double x = stod(v[1]);
            double y = stod(v[2]);
            pair<int, int> cell_id = get_cell_id(x, y);
            // cout << "printing cell id" << endl;
            // print_pair(cell_id);
            Node node(nodeId, x, y);
            grid[cell_id.first][cell_id.second].insert_node_to_cell(node, cell_id, blockSize);
        }
        datasetfile.close();
    }
    else
        cout << "Unable to open file";
}
void Grid::insert_edges(map<pair<int, int>, string> e_map, int blockSize)
{
    map<pair<int, int>, string>::iterator itr;
    for (itr = e_map.begin(); itr != e_map.end(); itr++)
    {
        int n1 = itr->first.first;
        int n2 = itr->first.second;
        string e_w = itr->second;
        pair<double, double> node1_cordinate = get_node_cordinates(n1);
        pair<double, double> node2_cordinate = get_node_cordinates(n2);

        pair<int, int> node1_cellId = get_cell_id(node1_cordinate.first, node1_cordinate.second);
        pair<int, int> node2_cellId = get_cell_id(node2_cordinate.first, node2_cordinate.second);

        if (compare_pair(node1_cellId, node2_cellId))
        {

            // both node is in same cell
            // need to add those edges in txt
            Edge e(n1, n2, e_w);
            grid[node1_cellId.first][node1_cellId.second].insert_edge_to_cell(e, node1_cellId, blockSize);
        }
        else
        {
            // Node node1(n1, node1_cordinate.first, node1_cordinate.second);
            // Node node2(n2, node1_cordinate.first, node1_cordinate.second);
            Edge edge(n1, n2, e_w);

            if (boundary_nodes.find(node1_cellId) != boundary_nodes.end())
            {
                boundary_nodes[node1_cellId].insert(n2);
            }
            else
            {
                set<int> s;
                s.insert(n2);
                boundary_nodes.insert(make_pair(node1_cellId, s));
            }

            if (boundary_nodes.find(node2_cellId) != boundary_nodes.end())
            {
                boundary_nodes[node2_cellId].insert(n1);
            }
            else
            {
                set<int> s;
                s.insert(n1);
                boundary_nodes.insert(make_pair(node2_cellId, s));
            }

            // boundary_edges.insert(make_tuple(edge, node1_cellId, node2_cellId));
            boundary_edges.push_back(make_tuple(edge, node1_cellId, node2_cellId));
            // grid[node2_cellId.first][node2_cellId.second].insert_boundary_node_to_cell(node1,node2_cellId,blockSize);
            // grid[node1_cellId.first][node1_cellId.second].insert_boundary_node_to_cell(node2,node1_cellId,blockSize);
            // Edge e(n1,n2,v[2]);
            // grid[node1_cellId.first].insert_boundary_edge_to_cell(e,node1_cellId,blockSize);
            // grid[node2_cellId.second].insert_boundary_edge_to_cell(e,node2_cellId,blockSize);
            // insert_node_to_cell()
            // boundary nodes
            // boundary edges
        }
    }
}

void Grid::insert_boundary_nodes(int blockSize)
{
    map<pair<int, int>, set<int>>::iterator itr;
    // set<pair<Node,pair<int,int>>>::iterator itr;
    for (itr = boundary_nodes.begin(); itr != boundary_nodes.end(); itr++)
    {
        set<int>::iterator set_itr;
        for (set_itr = itr->second.begin(); set_itr != itr->second.end(); set_itr++)
        {
            pair<double, double> node_cordinate = get_node_cordinates(*set_itr);
            Node node(*set_itr, node_cordinate.first, node_cordinate.second);
            grid[itr->first.first][itr->first.second].insert_boundary_node_to_cell(node, itr->first, blockSize);
        }
    }
}
void Grid::insert_boundary_edges(int blockSize)
{
    // set<tuple<Edge,pair<int,int>, pair<int,int>>>::iterator itr;
    // for ( itr = boundary_edges.begin(); itr != boundary_edges.end(); itr++)
    // {
    //     Edge e = get<0>(*itr);
    //     pair<int, int> cellId1 = get<1>(*itr);
    //     pair<int, int> cellId2 = get<2>(*itr);
    //     grid[cellId1.first][cellId1.second].insert_boundary_edge_to_cell(get<0>(*itr), get<1>(*itr), blockSize);
    //     grid[cellId2.first][cellId2.second].insert_boundary_edge_to_cell(get<0>(*itr), get<2>(*itr), blockSize);
    // }

    for (int i = 0; i < boundary_edges.size(); i++)
    {
        Edge e = get<0>(boundary_edges[i]);
        pair<int, int> cellId1 = get<1>(boundary_edges[i]);
        pair<int, int> cellId2 = get<2>(boundary_edges[i]);
        grid[cellId1.first][cellId1.second].insert_boundary_edge_to_cell(get<0>(boundary_edges[i]), get<1>(boundary_edges[i]), blockSize);
        grid[cellId2.first][cellId2.second].insert_boundary_edge_to_cell(get<0>(boundary_edges[i]), get<2>(boundary_edges[i]), blockSize);
    }
}

void Grid::visualize_grid()
{

    cout << "Visulaizing Grid" << endl;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {

            // if( grid[i][j] !=  )
            grid[i][j].print_cell_files();
        }
    }
    cout << "visiualized" << endl;
}

void Grid::visualize_cell_by_nodeId(int nodeId)
{
    pair<double, double> node_cords = get_node_cordinates(nodeId);

    if (invalid_pair(node_cords))
    {
        cout << "invalid node" << endl;
    }
    else
    {
        pair<int, int> cellId = get_cell_id(node_cords.first, node_cords.second);
        grid[cellId.first][cellId.second].print_cell_files();
    }
}

bool Grid::is_edge_present(Edge e)
{
    for (auto child : adj[e.nodeId1])
    {
        if (child.first == e.nodeId2)
            return true;
    }
    return false;
}
void Grid::add_edge(Edge e)
{
    if (!is_edge_present(e))
    {
        // cout << "edge not present" << endl;
        adj[e.nodeId1].push_back(make_pair(e.nodeId2, stod(e.weight)));
    }
}
void Grid::reset_adjancey_list()
{

    for (int i = 0; i < V; i++)
    {
        cout << i << "-->";

        for (auto x : adj[i])
        {
            cout << x.first << " ";
        }
        cout << endl;
    }
}
void Grid::print_adjancey_list()
{
    ofstream logfile;
    logfile.open("logs.txt", ios_base::app);

    for (int i = 0; i < V; i++)
    {
        cout << i << "-->";
        logfile << i << "-->";
        for (auto x : adj[i])
        {
            cout << x.first << " ";
            logfile << x.first << " ";
        }
        cout << endl;
        logfile << endl;
    }
}
bool Grid::is_cell_processed(pair<int, int> cellId)
{

    return grid[cellId.first][cellId.second].is_cell_processed();
}

vector<Edge> Grid::read_edges_from_cell_file(pair<int, int> cellId, int overflow_count)
{

    vector<Edge> cellEdges;
    // cout << "reading edge from file overflow_count = " << overflow_count << endl;
    string line;
    string filename;

    string edge_marker = "##";
    string boundary_edge_marker = "%%";
    string boundary_node_marker = "**";
    string overflow_marker = "??";

    bool edge_seperator = false;
    bool boundary_edge_seperator = false;
    bool node_seperator = false;
    bool boundary_node_seperator = false;
    bool overflow_seperator = false;
    bool loading = false;
    int cnt = 1;

    for (int i = 0; i < overflow_count + 1; i++)
    {

        if (i == 0)
        {
            filename = "(" + to_string(cellId.first) + "," + to_string(cellId.second) + ").txt";
        }
        else
        {
            filename = "(" + to_string(cellId.first) + "," + to_string(cellId.second) + ")_" + to_string(cnt) + ".txt";
            cnt++;
        }
        ifstream infile(filename);
        string line;
        while (getline(infile, line))
        {
            // cout << line;
            vector<string> v = tokenize(line, ' ');
            if (v[0].compare(edge_marker) == 0)
            {
                loading = true;
                edge_seperator = true;
                boundary_edge_seperator = false;
                continue;
            }
            else if (v[0].compare(boundary_node_marker) == 0)
            {
                loading = false;
                edge_seperator = false;
                boundary_edge_seperator = false;
                continue;
            }
            else if (v[0].compare(boundary_edge_marker) == 0)
            {
                loading = true;
                boundary_edge_seperator = true;
                edge_seperator = false;

                continue;
            }
            // else if (v[0].compare(overflow_marker) == 0)
            // {
            //     loading = false;
            //     edge_seperator = false;
            //     boundary_node_seperator = false;
            //     overflow_seperator = true;
            //     continue;
            // }

            if (edge_seperator || boundary_edge_seperator)
            {
                if (digits_only(v[0]) && v[0] != overflow_marker && v[0] != edge_marker && v[0] != boundary_node_marker && v[0] != boundary_edge_marker)
                {
                    int nodeId1 = stoi(v[0]);
                    int nodeId2 = stoi(v[1]);
                    string weight = v[2];
                    Edge e(nodeId1, nodeId2, weight);
                    cellEdges.push_back(e);
                }
            }
        }
        infile.close();
    }

    return cellEdges;
}
void Grid::compute_shortest_path_on_grid(int source, int destination)
{
    vector<int> predecessor(V + 1, NIL);
    vector<bool> status(V + 1, false);
    vector<double> pathLength(V + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<pair<int, int>, int> processedCell;
    // list<pair<int, double>> *adj;
    pair<double, double> src_node_cords = get_node_cordinates(source);
    pair<double, double> dest_node_cords = get_node_cordinates(destination);
    ofstream logfile;
    logfile.open("logs.txt", ios_base::app);
    if (invalid_pair(src_node_cords))
    {
        cout << "invalid source node" << endl;
        return;
    }

    if (invalid_pair(dest_node_cords))
    {
        cout << "invalid destination node id" << endl;
        return;
    }
    pq.push(make_pair(0, source));
    pathLength[source] = 0;

    while (!pq.empty())
    {

        int u = pq.top().second;
        // cout << " u = " << u << " ";
        // pathLength[u] =
        // cout << "pathLength[u]" =
        pq.pop();

        pair<double, double> node_cords = get_node_cordinates(u);
        if (invalid_pair(node_cords))
        {
            cout << "invalid node" << endl;
            return;
        }
        pair<int, int> nodeCellId = get_cell_id(node_cords.first, node_cords.second);
        status[u] = true;
        // print_pair(nodeCellId);
        logfile << "u = " << u << " "
                << "<" << nodeCellId.first << "," << nodeCellId.second << ">" << endl;
        // if( is_cell_processed(nodeCellId) )
        if (processedCell.find(nodeCellId) != processedCell.end())
        {
            // cell already processed
            for (auto x : adj[u])
            {
                int v = x.first;
                double weight = x.second;
                if (status[v] == false && pathLength[v] > pathLength[u] + weight)
                {
                    pathLength[v] = pathLength[u] + weight;
                    predecessor[v] = u;
                    pq.push(make_pair(pathLength[v], v));
                }
            }
        }
        else
        {
            // cout << "cell not processed" << endl;
            // cell not processed
            // logfile << "cell not processed" << endl;
            int overflow_count = grid[nodeCellId.first][nodeCellId.second].get_cell_overflow_count();
            processedCell.insert(make_pair(nodeCellId, overflow_count));
            // vector<Node> nodes = grid[nodeCellId.first][nodeCellId.second].get_nodes_with_in_cell();
            // vector<Edge> edges = grid[nodeCellId.first][nodeCellId.second].get_edges_with_in_cell();
            // vector<Node> boundaryNodes = grid[nodeCellId.first][nodeCellId.second].get_boundary_nodes_with_in_cell();
            // vector<Edge> boundaryEdges = grid[nodeCellId.first][nodeCellId.second].get_boundary_edges_with_in_cell();
            // cout << "edges" << endl;
            // logfile << "edges" << endl;
            // for (int i = 0; i < edges.size(); i++)
            // {
            //     logfile << edges[i].nodeId1 << " " << edges[i].nodeId2 << " " << edges[i].weight << endl;
            //     // add_edge(edges[i]);
            // }
            // cout << "boundary edges" << endl;
            // for (int i = 0; i < boundaryEdges.size(); i++)
            // {
            //     logfile << boundaryEdges[i].nodeId1 << " " << boundaryEdges[i].nodeId2 << " " << boundaryEdges[i].weight << endl;
            //     // add_edge(boundaryEdges[i]);
            // }
            vector<Edge> cellEdges = read_edges_from_cell_file(nodeCellId, overflow_count);
            // cout << "cellEdges from file" << endl;
            for (int i = 0; i < cellEdges.size(); i++)
            {
                // cout << cellEdges[i].nodeId1 << " " << cellEdges[i].nodeId2 << " " << cellEdges[i].weight << endl;
                logfile << cellEdges[i].nodeId1 << " " << cellEdges[i].nodeId2 << " " << cellEdges[i].weight << endl;
                add_edge(cellEdges[i]);
            }
            // print_adjancey_list();
            for (auto x : adj[u])
            {
                int v = x.first;
                // cout << "v = " << v << endl;
                double weight = x.second;
                // cout << "weight = " << weight << endl;
                // cout << "pathLength[v] = " << pathLength[v] << endl;
                if (status[v] == false && pathLength[v] > pathLength[u] + weight)
                {
                    pathLength[v] = pathLength[u] + weight;
                    predecessor[v] = u;
                    pq.push(make_pair(pathLength[v], v));
                }
            }
        }
        if (u == destination)
            break;
    }

    int s = source;
    int v = destination;
    bool pathNotFound = false;
    vector<int> path;
    int count = 0;
    while (v != s && count < V)
    {
        path.push_back(v);
        // cout << "v = " << v << endl;
        v = predecessor[v];

        if (v == -1)
        {
            pathNotFound = true;
            break;
        }
        count++;
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    cout << "Vertex distance from source : " << source << " to destination " << destination << " : " << pathLength[destination] << endl;
    logfile << "Vertex distance from source : " << source << " to destination " << destination << " : " << pathLength[destination] << endl;
    if (pathNotFound)
    {
        cout << "path not exist" << endl;
        logfile << "path not exist" << endl;
    }
    else
    {
        cout << "Shortest route path from source to destination is : " << endl;
        logfile << "Shortest route path from source to destination is : " << endl;
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << "-->";
            logfile << path[i] << "-->";
        }
        cout << endl;
        cout << "Number of nodes between source and destination are " << path.size() << endl;
        logfile << "Number of nodes between source and destination are " << path.size() << endl;
    }
    int overflow_blocks = 0;
    map<pair<int, int>, int>::iterator itr;
    for (itr = processedCell.begin(); itr != processedCell.end(); itr++)
    {
        overflow_blocks += itr->second;
    }
    cout << "Total Disk blocks brought to main memory = " << processedCell.size() + overflow_blocks << endl;
    cout << "Total main disk blocks brought to main memory = " << processedCell.size() << endl;
    cout << "Total overflow disk blocks brought to main memory =  " << overflow_blocks << endl;
    logfile << "Total Disk blocks brought to main memory = " << processedCell.size() + overflow_blocks << endl;
    logfile << "Total main disk blocks brought to main memory = " << processedCell.size() << endl;
    logfile << "Total overflow disk blocks brought to main memory =  " << overflow_blocks << endl;
    logfile.close();
    // reset_adjancey_list();

}