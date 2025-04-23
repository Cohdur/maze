#include "graph_class.h"
#include<vector>

class maze : public graph_class<char, int> // char = character/ board & int is edge weight
{

    private:

    const static int size = 4;
    char grid[4][4] =
    {
        {'+', '+', '+', '+'},
        {'|', ' ', ' ', '|'},
        {'|', ' ', ' ', '|'},
        {'+', '+', '+', '+'}
    };

    std::vector<std::vector<char>> big_maze;


    class position : public graph_class::Vertex
    {


    };
    

};