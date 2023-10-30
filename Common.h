#ifndef COMMON_H_
#define COMMON_H_
#include<bits/stdc++.h>
#include "Grid.h"
extern Grid g;
vector<string> tokenize(string s, char del);
map<pair<int, int>, string> read_edge_file(string filename);
vector<tuple<int, double, double>> read_node_file(string filename);
bool file_exist(string &name);
#endif

