#include <bits/stdc++.h>
#include <stdlib.h>
#include "Node.h"
#include "Edge.h"
#include "Grid.h"
#include "Block.h"
#include "Cell.h"
#include "Common.h"
#define INF INFINITY
#define NIL -1
using namespace std;
#define endl '\n'

void shortest_path(int source, int destination,map<pair<int,int>,string> edge_map,int V)
{
    vector<int> predecessor(V+1,NIL);
    vector<bool> status(V+1,false);
    vector<double> pathLength(V+1,INF);
    list<pair<int, double>> *adj;
    adj =  new list<pair<int, double>>[V + 1];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<pair<int,int>,string>::iterator itr;
    for(itr = edge_map.begin(); itr!= edge_map.end(); itr++){
        // add_edge(itr->first.first,itr->first.second,stod(itr->second));
        adj[itr->first.first].push_back(make_pair(itr->first.second,stod(itr->second)));
    }
    pq.push(make_pair(0, source));
    pathLength[source] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        status[u] = true;
        list<pair<int, int>>::iterator it;
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

        if( u == destination ) break;
    }

     int s = source;
    int v = destination;
    bool pathNotFound = false;
    vector<int>path;
    int count = 0;
    while(v != s && count < V){
        path.push_back(v);
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
    cout << "Vertex distance from source : " << source << " to destination " << destination << " : " <<  pathLength[destination] << endl;

    if (pathNotFound)
    {
        cout << "path not exist" << endl;

    }
    else
    {
        cout << "Shortest route path from source to destination is : " << endl;

        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << "-->";

        }
        cout << endl;
        cout << "Number of nodes between source and destination are " << path.size() << endl;

    }
}


/* read record from dataset.txt file */
vector<pair<double, double>> compute_grid_cordinates(int blockSize, string filename)
{
    string line;
    ifstream datasetfile(filename);
    int xCells = 0;
    int yCells = 0;
    vector<pair<double, double>> v;
    if (datasetfile.is_open())
    {
        vector<double> x_cordinate;
        vector<double> y_cordinate;
        while (getline(datasetfile, line))
        {
            vector<string> v = tokenize(line, ' ');
            int nodeId = stoi(v[0]);
            // double x = atof(v[1].c_str());
            // double y = atof(v[2].c_str());
            double x = stod(v[1]);
            double y = stod(v[2]);
            x_cordinate.push_back(x);
            y_cordinate.push_back(y);
        }
        double maxX = *max_element(x_cordinate.begin(), x_cordinate.end());
        double minX = *min_element(x_cordinate.begin(), x_cordinate.end());
        double maxY = *max_element(y_cordinate.begin(), y_cordinate.end());
        double minY = *min_element(y_cordinate.begin(), y_cordinate.end());
        cout << "maxX = " << maxX << endl;
        cout << "maxY = " << maxY << endl;
        cout << "minX = " << minX << endl;
        cout << "minY = " << minY << endl;
        v.push_back(make_pair(minX, minY));
        v.push_back(make_pair(maxX, maxY));
        datasetfile.close();
    }
    return v;
}
Grid g;

int main()
{
    int cellSize, blockSize;
    cout << "Please enter the size of the grid" << endl;
    cin >> cellSize;
    cout << "Please enter the disk block size" << endl;
    cin >> blockSize;
    cout << setprecision(15);
    vector<tuple<int, double, double>> v = read_node_file("nodes1.txt");
    vector<pair<double, double>> gridCord = compute_grid_cordinates(blockSize, "nodes1.txt");
    g.initialize_grid(gridCord, cellSize, v);
    g.print_grid_size();
    g.insert_nodes("nodes1.txt", blockSize);
    map<pair<int, int>, string> edge_map = read_edge_file("edges1.txt");
    cout << "Nodes Inserted" << endl;
    g.insert_edges(edge_map, blockSize);
    cout << "Edges Inserted" << endl;
    g.insert_boundary_nodes(blockSize);
    cout << "Boundary Nodes Inserted" << endl;
    g.insert_boundary_edges(blockSize);
    cout << "Boundary Edge Inserted" << endl;
    int options;
    int nodeId;

    cout << "node tuple size = " << v.size() << endl;
    while (1)
    {
        cout << "##########################################################" << endl;
        cout << "1. Get cellId from nodeId" << endl;
        cout << "2. Visualize the content of disk block and its associated overflow block for a particular Node." << endl;
        cout << "3. Visulaize the whole grid" << endl;
        cout << "4. Apply Dijkastra on Entire Data set." << endl;
        cout << "5. Apply Dijkastra on Grid" << endl;
        cout << "6. Exit from Menu" << endl;
        cout << "##########################################################" << endl;
        cin >> options;
        if (options == 1)
        {
            cout << "Please Enter NodeId" << endl;
            cin >> nodeId;
            pair<double, double> node_cord = g.get_node_cordinates(nodeId);
            if (!g.invalid_pair(node_cord))
            {
                pair<int, int> cellId = g.get_cell_id(node_cord.first, node_cord.second);
                cout << "cellId => "
                     << "<" << cellId.first << "," << cellId.second << ">" << endl;
            }
            else
            {
                cout << "invalid node" << endl;
            }
        }
        else if (options == 2)
        {
            cout << "Please Enter NodeId" << endl;
            cin >> nodeId;
            g.visualize_cell_by_nodeId(nodeId);
        }
        else if (options == 3)
        {
            g.visualize_grid();
        }
        else if (options == 4)
        {
            int srcNodeId,destNodeId;
            cout<<"Please enter source node id" << endl;
            cin >> srcNodeId;
            cout<<"Please enter destyination node id" << endl;
            cin >> destNodeId;
            shortest_path(srcNodeId,destNodeId,edge_map,v.size());

        }
        else if(options == 5){
            int srcNodeId,destNodeId;
            cout<<"Please enter source node id" << endl;
            cin >> srcNodeId;
            cout<<"Please enter destyination node id" << endl;
            cin >> destNodeId;
            g.compute_shortest_path_on_grid(srcNodeId,destNodeId);
        }
        else if( options == 6){
            cout << "Exit" << endl;
            break;
        }
    }
    return 0;
}