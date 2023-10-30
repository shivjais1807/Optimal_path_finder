#include "Common.h"

bool file_exist(string &name)
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

vector<string> tokenize(string s, char del)
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

map<pair<int, int>, string> read_edge_file(string filename)
{
    string line;
    ifstream datasetfile(filename);

    map<pair<int, int>, string> m;
    vector<pair<set<int, int>, string>> vs;
    if (datasetfile.is_open())
    {
        while (getline(datasetfile, line))
        {
            vector<string> v = tokenize(line, ' ');
            int n1 = stoi(v[0]);
            int n2 = stoi(v[1]);
            double edge = stod(v[2]);


            if (m.find(make_pair(n1, n2)) != m.end())
            {
                // map::iterator itr;
                map<pair<int,int>,string>::iterator itr = m.find(make_pair(n1,n2));
                if( stod(v[2]) < stod(itr->second) ){
                    // m.insert({make_pair(n1, n2), v[2]});
                    itr->second = v[2];
                }
            }
            else{
                m.insert({make_pair(n1, n2), v[2]});
            }

            // if (m.find(make_pair(n1, n2)) == m.end())
            // {
            //         m.insert({make_pair(n1, n2), v[2]});
            // }
            // else{

            // }
        }
        datasetfile.close();
    }
    // else
    //     cout << "Unable to open file";
    return m;
}
vector<tuple<int, double, double>> read_node_file(string filename)
{

    string line;
    ifstream datasetfile(filename);
    int xCells = 0;
    int yCells = 0;
    vector<tuple<int, double, double>> node_tuple;
    map<int, pair<double, double>> node_map;
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
            node_tuple.emplace_back(make_tuple(nodeId, x, y));
            node_map.insert({nodeId, make_pair(x, y)});
        }
    }
    return node_tuple;
}

void read_block_file(string filename){
    string line;
    ifstream blockfile(filename);

    if(blockfile.is_open()){

        while(getline(blockfile,line)){

            vector<string> v = tokenize(line,' ');


        }
    }
}