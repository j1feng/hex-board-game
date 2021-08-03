/*
Coursera C and C++: Programming Assignment Week 4;
Create a graph as an ADT (Abstract Data Type) using C++ classes;
Using ths ADT to implement Dijkstra’s algorithm for the shortest path problem; 
and the implementation of a minimum spanning tree (MST) algorithm.
*/

#include <iostream>
#include <bits/stdc++.h> 
#include <typeinfo>
#include <string.h>
using namespace std;
const int INF = 99999;
const int NINF = -99999;

//create integer pair data type
typedef pair <int, int> iPair;

//using edge pair list to implement a graph class
class Graph{
    int numV;
    int numE;
    list<iPair> *adj;

    public:
        //constructor
        Graph(int numV){
            this->numV = numV; //avoid confusion
            this->numE = 0;
            adj = new list<iPair>[numV];
        };

        //if number of vertices not specified
        Graph() {
            this->numV = numV; //avoid confusion
            this->numE = 0;
            adj = NULL;
        }

        //change number of vertices
        void setNumV(int numV){
            adj = new list<iPair>[numV];
        }

        //returns the number of vertices in the graph
        int V(){
            return numV;
        }

        //returns the number of edges in the graph
        int E(){
            return numE;
        }
        
        //tests whether there is an edge from node x to node y.
        void adjacent(int x, int y){
            bool result = false;

            //using iterators
            list<pair<int, int>>::iterator i;
            for (i = adj[x].begin(); i != adj[x].end(); i ++){
                if (y == (*i).first){
                    result = true;
                }
            }
            if (result) {
                printf("Vertex %d and %d are adjacent.\n", x, y);
            } else {
                printf("Vertex %d and %d are NOT adjacent.\n", x, y); 
            }
        }

        //lists all nodes y such that there is an edge from x to y.
        void neighbors(int x){
            printf("The neighbors for node %d are: ", x);
            bool result = false;
            set<int> neighborSet;
            list<pair<int, int>>::iterator i;
            for (i = adj[x].begin(); i != adj[x].end(); i ++){
                neighborSet.insert((*i).first);
            }
            for (auto i: neighborSet){
                printf("%d ", i);
            }
            printf("\n");
        }

        //adds to G the edge from x to y, if it is not there.
        void add(int x, int y, int weight){
            adj[x].push_back(make_pair(y, weight));
            adj[y].push_back(make_pair(x, weight));
            numE += 1;
        };

        //find the shortest path from the start node
        void findShortestPath(int start){

            //initialize the distances to positive infinites
            vector<int> dist(numV, INF);
            //initialize self as 0 distance
            dist[start] = 0;
            
            //The value of the PriorityQueue is to always have access to the vertex 
            //with the next shortest link in the shortest path calculation at the top of the queue. 
            priority_queue<iPair> pq;
            pq.push(make_pair(0, start));

            //keep iterating untill all nodes are done
            while (pq.empty() == false){
                int x = pq.top().second;
                pq.pop();

                list<pair<int, int>>::iterator i;
                for (i = adj[x].begin(); i != adj[x].end(); i ++){
                    int y = (*i).first;
                    int weight = (*i).second;
                    int curDist = dist[x] + weight;
                    if (curDist < dist[y]){
                        dist[y] = curDist;
                        pq.push(make_pair(dist[y], y));
                    }
                }
                
            }
            for (int i = 0; i < numV; i ++){
                printf("Shortest distance from %d to %d: %d\n", start, i, dist[i]);
            }
        };

        //Implementation of prim's algorithm to find the short spanning tree starting
        //from note 'start'
        void mst(int start = 0){

            //initialize the distances to positive infinites
            vector<int> dist(numV, INF);
            //initialize self as 0 distance
            dist[start] = 0;

            //visited nodes
            vector<int> visited(numV, 0);

            //MST path
            vector<int> mst(numV, NINF);

            //similar above, create priority queue 
            priority_queue<iPair> pq;
            pq.push(make_pair(0, start));

            //keep iterating untill all nodes are done
            while (pq.empty() == false){
                int x = pq.top().second;
                pq.pop();
                
                //we only care about unvisited node
                if (visited[x] == 0){
                    
                    visited[x] = 1;

                    //iterator, similarly to the previous implementation
                    list<pair<int, int>>::iterator i;
                    for (i = adj[x].begin(); i != adj[x].end(); i ++){

                        int y = (*i).first; //its connected node
                        int weight = (*i).second;
    
                        //if the current weight is smaller, update the dist
                        if (weight < dist[y] && visited[y] == 0 ){
                            dist[y] = weight;
                            pq.push(make_pair(weight, y));
                            mst[y] = x;
                        }

                    }
                    //mark x as visited
                    visited[x] = 1;
                }
            }
            cout << "Edges for the minimum spanninng tree: " << endl;
            for (int i = start; i < numV; i ++){
                if (mst[i] != NINF){
                    cout << mst[i] << " -> " << i << endl;
                }
            }
        }
};

//Main method where we test the graph structure and algorithm
// int main() {

//     ifstream file("data.txt");
//     string str;
//     int start, numNode;
//     int x, y, weight;
//     vector<vector<int>> vec;

//     while (getline(file, str)){
//         if (start == 0){
//             numNode = stoi(str);
//             start = 1;
//         } else{
//             int strLoc = str.find(" ");
//             x = stoi(str.substr(0, strLoc));
//             string rest = str.substr(strLoc + 1, str.length());
//             strLoc = rest.find(" ");
//             y = stoi(rest.substr(0, strLoc));
//             rest = rest.substr(strLoc + 1, rest.length());
//             weight = stoi(rest);
//             //cout << x << ":" <<y << ":" << weight << endl;
//             vec.push_back({x, y, weight});
//         }
//     }
//     Graph g(numNode);
//     for (auto v: vec){
//         g.add(v[0], v[1], v[2]);
//     }
//     g.adjacent(1, 2);
//     g.neighbors(1);
//     //g.findShortestPath(0);
//     g.mst();
//     return 0;
// }
