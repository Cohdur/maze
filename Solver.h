#include<iostream>

#include "maze.h"
#include "Graph.h"

template<typename V,typename E>
class Solver //: public Graph<V, E> // char = character/ board & int is edge weight
{
    public:
    Solver() //: Graph<V, E>(false) {} // Explicitly call the base class constructor || There may be circles so not acycle
    
    maze mazeObj;
    Graph<V,E> graphObj{false}; 

    using ActualVertex = typename Graph<V,E>::ActualVertex;
    using ActualEdge   = typename Graph<V,E>::ActualEdge;
    using Vertex       = typename Graph<V,E>::Vertex;
    using Edge         = typename Graph<V,E>::Edge;
    using Graph<V,E> graph;


    ActualVertex startOrigin = ActualVertex(mazeObj::big_maze.at(mazeObj.getStartIndexRow()).at(mazeObj.getStartIndexCol()));
    ActualVertex endOrigin = ActualVertex(mazeObj::big_maze.at(mazeObj.getEndIndexRow()).at(mazeObj.getEndIndexCol()));

    protected :
    std::list<ActualVertex> vertices;
    std::list<ActualEdge> edges;
     
    private:



    // this would need a container plus a way to compare weight per trial then assign lowest to map 
    // redirect a . that is placed along path for visual representation of path taken
    // SO NOT SURE IF I WANT TO KEEP THIS TRIAL MAP
    typedef std::map<typename Graph<V,E>::Vertex, typename Graph<V,E>::Edge> trial;

    //Change of plans this will be BFS and Dijkstra's algorithm 
    pathFinder()
    {
        for(const auto& i : mazeObj.big_maze)
        {
            for(const auto& j : i)
            {
                if(j == ' ')
                {
                    graphObj.insert_vertex(j);
                }
            }
        }
    }

    int outputVertices()
    {
        return vertices.size();
    }

};

//reference table for graph 

/*
ACCESSING H IN THIS EXAMPLE 

This is the big maze index for the grid on that index
blockRow = 0 / 4 = 0
blockCol = 8 / 4 = 2

This is the narrowed index
localRow = 0 % 4 = 0
localCol = 8 % 4 = 0

      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
r0    + + + + + + + + H +  +  +  +  +  +  +
r1    +     + +     +       +  +     +
r2    +     + +     + +     +  +     +
r3    + + + + + + + + + +  +  +  +  +  +  +
r4    + + + + + + + + + +  +  +  +  +  +  +
r5    +     + +     + +     +  +     +
r6    +     + +     + +     +  +     +
r7    + + + + + + + + + +  +  +  +  +  +  +
r8    O   + + + + + + + +  +  +  +  +  +  +
r9    +     + +     + +     +  +     +
r10   +     + +     + +     +  +     +
r11   + + + + + + + + + +  +  +  +  +  +  +
r12   + + + + + + + + + +  +  +  +  +  +  +
r13   +     + +     + +     +  +     +
r14   +     + +     + +     +  +     +
r15   + + + + + + + + + +  +  +  +  +  +  +
*/