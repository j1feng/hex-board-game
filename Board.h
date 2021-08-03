#ifndef BOARD
#define BOARD

#include <iostream>
#include "Graph.h"
using namespace std;

typedef pair <int, int> pos;
const int SIZE = 11;

/*
Create the board class for the game;
*/
class Board {

    int numPos = SIZE * SIZE;
    //array to save and update the board information
    int arr[SIZE][SIZE] = {0};
    int numStep;

    //two unweighted undirected graph represented the 
    //connectivities of the locations on the board for two players
    Graph p1Graph;
    Graph p2Graph;

    public:

        Board(){};

        /* Show the gameboard at the moment */
        void show();

        /* Check if stone can be placed as the (x, y) location */
        bool stepValidCheck(int x, int y);

        /* calculate the one-D position index for the given position */
        int to_graph_idx(int x, int y){
            return x * SIZE + y;
        }

        /* one step into the game */
        string step(int p, int x, int y);
        
        /* helper function to determine if player p has won */
        bool hasWin(int p);

        /*start the game */
        void play();

};

bool Board::stepValidCheck(int x, int y){
    //if location outside of the board
    if ((x < 0) || (x >= SIZE) || (y < 0) || (y >= SIZE)){
        cout << "Invalid input index! Please enter number before 0 to " << SIZE << endl;
        return false;
    }
    //if stone has already been place on this position
    if (arr[x][y] != 0){
        cout << "Stone has already been place on this position!" << endl;
        return false;
    }
    return true;
}

string Board::step(int p, int x, int y){
    //step check
    if (stepValidCheck(x, y) == false){
        return "invalid step";
    }
    int gPos = to_graph_idx(x, y); //cur position in graph
    arr[x][y] = p;
    //determine which player's graph to use
    Graph* g;
    if (p == 1){
        g = &p1Graph;
    } else if (p == 2){
        g = &p2Graph;
    }
    //add the connectivity relationship to the graph
    try{
        if (arr[x - 1][y] == p){
            //case 1: find edge to top left
            g->addEdge(gPos, to_graph_idx(x - 1, y));
            //cout << "case1 " << endl;
        }
        if (arr[x - 1][y + 1] == p){
            //case 2: find edge to top right
            g->addEdge(gPos, to_graph_idx(x - 1, y + 1));
            //cout << "case2 " << endl;
        }
        if (arr[x][y - 1] == p){
            //case 3: find edge to the left
            g->addEdge(gPos, to_graph_idx(x, y - 1));
            //cout << "case3 " << endl;
        }
        if (arr[x][y + 1] == p){
            //case 4: find edge to the right
            g->addEdge(gPos, to_graph_idx(x, y + 1));
            //cout << "case4 " << endl;
        } 
        if (arr[x + 1][y - 1] == p){
            //case 5: find edge to the right
            g->addEdge(gPos, to_graph_idx(x + 1, y - 1));
            //cout << "case5 " << endl;
        }
        if (arr[x + 1][y] == p){
            //case 6: find edge to the right
            g->addEdge(gPos, to_graph_idx(x + 1, y));
            //cout << "case6 " << endl;
        }
    } catch (int e){};

    //check for winner, note that winner cannot be decided 
    //in the first few rounds
    if (numStep >= (SIZE - 1) * 2 && hasWin(p)){
        return "Game Over!";
    }
    return "Continue...";
}

//determine if player p won
bool Board::hasWin(int p){
    //determine which graph to use
    Graph* g;
    if (p == 1){
        g = &p1Graph;
    } else if (p == 2){
        g = &p2Graph;
    }

    //determine if player 1 wins 
    if (p == 1){
        for (int left = 0; left < SIZE; left ++){
            for (int right = 0; right < SIZE; right ++){
                //cout << "k: ";
                //find all the connected nodes for the border nodes
                vector<int> connection = (*g).findConnection(
                    to_graph_idx(left, 0));
                for (auto k = connection.begin(); 
                        k != connection.end(); k++){
                    //cout << (*k) << "-";
                    //if a node on the border is connected to the other
                    //border, return true
                    if ((*k) == to_graph_idx(right, SIZE - 1)){
                        return true;
                    }
                }
                //cout << " " << endl;
            }
        }
    }
    //determine if player 2 wins 
    if (p == 2){
        for (int top = 0; top < SIZE; top ++){
            for (int bottom = 0; bottom < SIZE; bottom ++){
                //find all the connected nodes for the border nodes
                vector<int> connection = (*g).findConnection(
                    to_graph_idx(0, top));
                for (auto k = connection.begin(); 
                        k != connection.end(); k++){
                        //if a node on the border is connected to the other
                        //border, return true
                    if ((*k) == to_graph_idx(SIZE - 1, bottom)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Board::play(){
    //play the game
    numStep = 0;
    cout << "==================================================" << endl;
    cout << "Game Started. Generating game board... " << endl;
    cout << "Player 1 win by connecting the left to the right." << endl;
    cout << "Player 2 win by connecting the top to the bottom." << endl;

    show();

    while (true) {
        cout << "Player 1 - left/right to win; Player 2 - Top/bottom to win." << endl;
        cout << "Steps: " << numStep << endl;
        if (numStep % 2 == 0){
            string i, j;
            cout << "Player 1 turn: please input the vertical(row) position:" << endl;
            cin >> i;
            cout << "Player 1 turn: please input the horizontal(col) position:" << endl;
            cin >> j;
            string result = step(1, stoi(i), stoi(j));
            cout << result << endl;
            if (result == "invalid step"){
                numStep -= 1;
            } else if (result == "Game Over!"){
                cout << "Player 1 won." << endl;
                break;
            }
            numStep += 1;
            show();
        } else {
            //player 2's turn
            string i, j;
            cout << "Player 2 turn: please input the vertical(row) position:" << endl;
            cin >> i;
            cout << "Player 2 turn: please input the horizontal(col) position:" << endl;
            cin >> j;
            string result = step(2, stoi(i), stoi(j));
            if (result == "invalid step"){
                numStep -= 1;
            } else if (result == "Game Over!"){
                cout << "Player 2 won." << endl;
                break;
            }
            numStep += 1;
            show();
        }
    }
}

void Board::show() {
    cout << "==================================================" << endl;
    cout << "Current Gameboard: (X -> Player 1; O -> Player 2;)" << endl;
    string firLine = "  ";
    string betweenLine = " ";
    for (int i = 0; i < SIZE; i++){
        firLine += (to_string(i) + "   ");
        betweenLine += "\\ / ";
    }
    betweenLine = betweenLine.substr(0, betweenLine.size() - 2);
    cout << firLine << endl;;
    string indent = " ";
    for (int i = 0; i < SIZE; i ++) {
        cout << i << indent;
        for (int j = 0; j < SIZE; j ++){
            if (j != SIZE - 1){
                switch (arr[i][j]) {
                    case (0): cout << ". - "; break;
                    case (1): cout << "X - "; break;
                    case (2): cout << "O - "; break;
                    }
            } else {
                switch (arr[i][j]) {
                    case (0): cout << ". "; break;
                    case (1): cout << "X "; break;
                    case (2): cout << "O "; break;
                }
            }
        }
        indent += " ";
        cout << endl;
        if (i == SIZE - 1) break;
        cout << indent << betweenLine << endl;
        indent += " ";
    }
}

#endif
