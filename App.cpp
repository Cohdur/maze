#include<iostream>
#include "maze.h"
#include "Solver.h" // It would have to be just this class 


using namespace std;

int main()
{
    //maze<char, int> game;
    Solver<char,int> game;
    
    game.createMaze();

    // for sake this is just a test on algorithm I'll refine the maze with multiple calls 
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
 

    game.output();

}

// reference table for 