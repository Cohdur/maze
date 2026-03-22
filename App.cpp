#include<iostream>
#include "maze.h"




using namespace std;

int main()
{
    //maze<char, int> game;
    maze game;

    game.createMaze();

    // for sake this is just a test on algorithm I'll refine the maze with multiple calls 
    //game.create_openeings();
    //game.create_openeings();
    //game.create_openeings();
    //game.create_openeings();
    //game.create_openeings();
 

    game.output();
}

// reference table for 