/* 
Graph data structure (unweighted)
Find the neighbors of a graph node using DFS algorithm
*/
#ifndef GRAPH
#define GRAPH

#include <bits/stdc++.h>
using namespace std;
 
class Graph {
 
public:
    //visited and neighbor list for DFS
    map<int, bool> visited;
    map<int, list<int>> neighbor;
    vector<int> connected;

    /* add an edge to the graph */
    void addEdge(int x, int y){
        neighbor[x].push_back(y);
        neighbor[y].push_back(x);
    }
 
    /* function to start dfs search with a result list */
    vector<int> findConnection(int start){
        //clear visited and connected list for different result;
        visited.clear();
        connected.clear();
        DFS(start);
        return connected;
    }

    /* recursive DFS algorithm */
    void DFS(int x) {
        connected.push_back(x);
        visited[x] = true;
        for (auto i = neighbor[x].begin(); i != neighbor[x].end(); ++i){
            if (!visited[*i]){
                // Recursively call the DFS algorithm to save nodes visited
                DFS((*i));
            }
        }
    }
};

// int main(){
//     Graph g;
//     g.addEdge(0, 1);
//     vector<int> vec = g.findConnection(0);
//     cout << vec.size();
//     for (auto i = vec.begin(); i!= vec.end(); i ++){
//         cout << *i << " ";
//     }
//     cout << vec.size();
// }

#endif