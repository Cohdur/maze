#include<iostream>
#include<sstream>
#include<thread>
#include<chrono>
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
    // Maybe delete in final form 
    list<Edge> createdPath;
    vector<int> AllIndexes;
    public:
    
    Solver() {};
    // key index for path finder
    int rowForStart;
    int colForStart;
    int IndexKeyForStart;

    int rowForEnd;
    int colForEnd;
    int IndexKeyForEnd;
    double weight = 1;
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
        
        for(auto x = 0; x < 15; x++)
        {
            mazeObj.create_openeings();
        }

        mazeObj.output();
    }
    void outputmaze()
    {
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
                    AllIndexes.push_back(index);
                    if(mazeObj.getMaze().at(r).at(c) == 'H')
                    {
                        rowForEnd = r;
                        colForEnd = c;
                        IndexKeyForEnd = index;
                    }
                    if(mazeObj.getMaze().at(r).at(c) == 'O')
                    {
                        rowForStart = r;
                        colForStart = c;
                        IndexKeyForStart = index;
                    }
                        // this is for the open spaces that are not start or end 
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
    void FindPath()
    {
        const list<Edge>& pathListA = graphObj.edges();
        list<Edge> PathListB;
        bool done = false;

        while(!done)
        {

            for(auto i : pathListA)
            {   
                if(PathListB.empty() && graphObj.endpoints(i).first == cellToVertex[rowForStart][colForStart].value())
                {
                    cout << "TESTER A" << endl;
                    PathListB.push_back(i);
                    //graphObj.erase(graphObj.endpoints(i).first);
                }if(!PathListB.empty())
                {
                    
                    cout << "TESTER B" << endl;
                    for(auto j : graphObj.neighbors(graphObj.endpoints(i).first))
                    {
                        cout << "TESTER C" << endl;
                        // in connecting these edges I must also pass through the seperate cells 
                        if(graphObj.endpoints(i).second == j)
                        {
                            cout << "TESTER D" << endl;
                                for(auto k : graphObj.neighbors(j))
                                {
                                    cout << "TESTER E" << endl;
                                //for(int itr = 0; itr < graphObj.degree(graphObj.endpoints(i).first); itr++)
                                //{
                                    if(graphObj.has_edge(graphObj.endpoints(i).first, k))
                                    {
                                        for(auto e : PathListB)
                                        {
                                            cout << "TESTER F" << endl;
                                        }
                                        //if(PathListB.back().weight() + graphObj.degree(j) + 1 < PathListB.back().weight()) 
                                        //{
                                            PathListB.push_back(graphObj.insert_edge(graphObj.endpoints(i).first, k, PathListB.back().weight() + graphObj.degree(j) + 1));
                                        //}
                                        /*
                                        else 
                                        {
                                            PathListB.push_back() 
                                        }
                                        */
                                    }
                                    else
                                    {
                                        cout << "TESTER G" << endl;
                                        PathListB.push_back(graphObj.insert_edge(graphObj.endpoints(i).first, j, PathListB.back().weight() + graphObj.degree(j) + 1));  
                                        PathListB.push_back(graphObj.insert_edge(j, k, PathListB.back().weight() + graphObj.degree(graphObj.endpoints(i).first) + 1));
                                        break;
                                        //graphObj.erase(i);  
                                    }
                                //}
                                }
                        }
                if(/*graphObj.endpoints(PathListB.front()).first == cellToVertex[rowForStart][colForStart].value() &&*/ graphObj.endpoints(PathListB.back()).first == cellToVertex[rowForEnd][colForEnd].value()|| graphObj.endpoints(PathListB.back()).second == cellToVertex[rowForEnd][colForEnd].value())
                {
                    createdPath = PathListB;
                    done = true;
                    //break;
                }
                }
                }
            }
        }
        
        // this is where I would implement Dijkstra's to find the lowest weight path from start to end and then assign that path to a list of edges that I can then output at the end 
        // this is also where I would update the maze with the . for visual representation of the path taken
        /*
        for(auto i : pathListA)
        {
            cout << "Edge from " << *graphObj.endpoints(i).first << " to " << *graphObj.endpoints(i).second << " with weight " << i.weight() << endl;
        }
        */
        //createdPath = PathListB;
    }
        
    void usePath()
    {
        
        for(auto i : createdPath)
        {
            //cout << "Edge from " << *graphObj.endpoints(i).first << " to " << *graphObj.endpoints(i).second << " with weight " << i.weight() << endl;
            int row = *graphObj.endpoints(i).first / 16;
            int col = *graphObj.endpoints(i).first % 16;
            mazeObj.changeMaze(row, col, '.');
            mazeObj.output();
            cout << flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mazeObj.changeMaze(row, col, ' ');
            row = *graphObj.endpoints(i).second / 16;
            col = *graphObj.endpoints(i).second % 16;
            mazeObj.changeMaze(row, col, '.');
            mazeObj.output();
            cout << flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            mazeObj.changeMaze(row, col, ' ');
            
        }
        
    }
    
    // TESTER FOR FUNCTION TO BE WORKING PROPERLY 
    int outputVertices()
    {
        return graphObj.num_vertices();
    }
    void outputEdgeCheck()
    { 
        cout << graphObj.num_edges() << endl;
    }
    
    int degreeOfVertex()
    { int n = 0;
        for(auto i : cellToVertex)
        {
            for(auto j : i)
            {
                if(j.has_value())
                {
                    if(n == cellToVertex.size() - 10)
                    {
                        cout << "Index " << *j.value() << endl;
                        return graphObj.degree(j.value());
                    }
                    n++;
                }
            }
        }
        return 0;
    }
    void outputCells()
    {
        for(auto r = 0; r < cellToVertex.size(); r++)
        {
            for(auto c = 0; c < cellToVertex.at(0).size(); c++)
            {
                if(cellToVertex.at(r).at(c).has_value())
                {
                    cout << "Row: " << r << " Col: " << c << " Vertex Index: " << *cellToVertex.at(r).at(c).value() << endl;
                }
            }
        }
    }
    //////////////////////////////////////////
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