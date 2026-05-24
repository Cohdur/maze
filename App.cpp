#include<iostream>
#include "Solver.h" // It would have to be just this class 


using namespace std;

int main()
{
    Solver<int,int> game;

    game.Maze();
    game.pathFinder();
    //cout << game.outputVertices() << endl;
    //game.createEdges();
    //game.outputEdgeCheck();
    //game.outputTheWrappedList();

}
