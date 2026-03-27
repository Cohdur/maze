#include<iostream>
#include "Solver.h" // It would have to be just this class 


using namespace std;

int main()
{
    Solver<char,int> game;

    game.Maze();
    game.outputVertices();

}

// reference table for 