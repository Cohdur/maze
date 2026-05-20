#include<iostream>
#include<optional>
#include "maze.h"
#include "Graph.h"

using namespace std;

template<typename V,typename E>
class Solver //: public Graph<V, E> // char = character/ board & int is edge weight
{
    private:
    
    maze mazeObj;
    Graph<V,E> graphObj{true}; 
    
    using Vertex       = typename Graph<V,E>::Vertex;
    using Edge         = typename Graph<V,E>::Edge;

    protected:
    std::vector<std::vector<std::optional<Vertex>>> cellToVertex{16, std::vector<std::optional<Vertex>>(16)};
    
    public:
    
    Solver() {};

    // this would need a container plus a way to compare weight per trial then assign lowest to map 
    // redirect a . that is placed along path for visual representation of path taken
    // SO NOT SURE IF I WANT TO KEEP THIS TRIAL MAP

    bool CheckCellFromVectorListofVertices(int row, int col)
    {
        if (row < 0 || col < 0 || row >= static_cast<int>(cellToVertex.size())
            || col >= static_cast<int>(cellToVertex[0].size()))
            return false;
        return cellToVertex.at(row).at(col).has_value();
    }

    void Maze()
    {
        mazeObj.createMaze();
        
        //mazeObj.create_openeings();

        mazeObj.output();
    }

    //Working a on the idea of index per vertex given the placement of vertex within the graph 
    // Diagnole moves require this to be Dijkstra's and not BFS as it's weights different 1 or sqrt(2) 
    // this means that the edge should use a double and not an int for the weight 
    void pathFinder()
    {
        // these are based on maze size dimensions 
        int row = 16;
        int col = 16;

        for(auto r = 0; r < row; r++)
        {
            for(auto c = 0; c < col; c++)
            {
                if(mazeObj.getMaze().at(r).at(c) == ' ' || mazeObj.getMaze().at(r).at(c) == 'H' || mazeObj.getMaze().at(r).at(c) == 'O')
                {
                    int index = r * col + c;
                    cellToVertex[r][c] = graphObj.insert_vertex(index);
                }
            }
        }
    }

    void createEdges()
    {
        // this is based on the maze size dimensions 
        int row = mazeObj.getMaze().size();
        int col = mazeObj.getMaze().at(0).size();

        for(auto r = 0; r < row; r++)
        {
            for(auto c = 0; c < col; c++)
            {
                if(mazeObj.getMaze().at(r).at(c) == ' ' || mazeObj.getMaze().at(r).at(c) == 'H' || mazeObj.getMaze().at(r).at(c) == 'O')
                {
                    if(CheckCellFromVectorListofVertices(r - 1, c))
                    {
                        graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r - 1][c].value(), 1.0);
                    }
                    if(CheckCellFromVectorListofVertices(r + 1, c))
                    {
                        graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r + 1][c].value(), 1.0);
                    }
                    if(CheckCellFromVectorListofVertices(r, c - 1))
                    {
                        graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r][c - 1].value(), 1.0);
                    }
                    if(CheckCellFromVectorListofVertices(r, c + 1))
                    {
                        graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r][c + 1].value(), 1.0);
                    }
                }
            }
        }
    }

    int outputVertices()
    {
        return graphObj.num_vertices();
    }

    void outputEdgeCheck()
    { cout << graphObj.num_edges() << endl;
        /*
        for(auto r = 0; r < 16; r++)
        {
            for(auto c = 0; c < 16; c++)
            {
                cout << boolalpha << CheckCellFromVectorListofVertices(r,c) << endl;
                if(CheckCellFromVectorListofVertices(r,c))
                {
                    cout << "origin vertex; " << *cellToVertex.at(r).at(c).value() << endl;
                    if(CheckCellFromVectorListofVertices(r - 1, c))
                    {
                        cout << "edge to vertex above: " << *cellToVertex.at(r - 1).at(c).value() << endl;
                    }
                    if(CheckCellFromVectorListofVertices(r + 1, c))
                    {
                        cout << "edge to vertex below: " << *cellToVertex.at(r + 1).at(c).value() << endl;
                    }
                    if(CheckCellFromVectorListofVertices(r, c - 1))
                    {
                        cout << "edge to vertex left: " << *cellToVertex.at(r).at(c - 1).value() << endl;
                    }
                    if(CheckCellFromVectorListofVertices(r, c + 1))
                    {
                        cout << "edge to vertex right: " << *cellToVertex.at(r).at(c + 1).value() << endl;
                    }
                }
                
            }
        }
        */
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