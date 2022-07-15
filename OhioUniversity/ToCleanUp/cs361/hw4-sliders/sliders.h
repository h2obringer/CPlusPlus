#ifndef SLIDERS_H
#define SLIDERS_H

#include <queue>
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class sliders{
  public:
    void BFS(string &v);
  private:
    string build_sequence(string const &start,string const &next,string &answer);
    void build_adjacent_vertex_list(pair<string,string> &p,vector <pair <string,string> > &avl);
};

#endif
