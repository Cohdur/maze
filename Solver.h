#include<iostream>
#include<sstream>
#include<thread>
#include<chrono>
#include<climits>
#include<optional>
#include<list>
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
    list<Edge> createdPath;
    // Use the cellToVertex in more optimal option 
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
        
        for(auto x = 0; x < 5; x++)
        {
            mazeObj.create_openeings();
        }

        mazeObj.output();
    }
    void outputmaze()
    {
        mazeObj.output();
    }
 
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

        //list<Edge> edges = graphObj.edges();
        list<Edge> edges;

        Edge* ptrEdges = nullptr;
        Edge* createdPathPtr = nullptr;
        list<Vertex> neighbors2; // neighbor of a neighbor 
        bool done = false;
        bool firstPass = false;

        while(!done)
        {
            for(auto r = 0; r < row; r++)
            {

                for(auto c = 0; c < col; c++)
                {
                    if(!firstPass && graphObj.edges().size() == 0 && r == rowForStart && c == colForStart)
                    {
                        if(mazeObj.getMaze().at(r).at(c) == ' ' || mazeObj.getMaze().at(r).at(c) == 'H' || mazeObj.getMaze().at(r).at(c) == 'O')
                        {
                            if(CheckCellFromVectorListofVertices(r - 1, c))
                        {
                            createdPath.push_back(graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r - 1][c].value(), 1.0));
                        }
                        if(CheckCellFromVectorListofVertices(r + 1, c))
                        {
                            createdPath.push_back(graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r + 1][c].value(), 1.0));
                        }
                        if(CheckCellFromVectorListofVertices(r, c - 1))
                        {
                            createdPath.push_back(graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r][c - 1].value(), 1.0));
                        }
                        if(CheckCellFromVectorListofVertices(r, c + 1))
                        {
                            createdPath.push_back(graphObj.insert_edge(cellToVertex[r][c].value(), cellToVertex[r][c + 1].value(), 1.0));
                        }
                        //reset the count 
                        r = 0;
                        c = 0;
                    }
                }
                    else if(!firstPass && graphObj.edges().size() != 0)
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
                    if(r == 15 && c == 15)
                    {
                        firstPass = true;
                        
                        // itital assignment 
                        edges = graphObj.edges();
                        ptrEdges = &edges.front();
                        createdPathPtr = &createdPath.front();
                        neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second);
                        neighbors2.pop_front(); // should remove the origin copy over
                    } 
                    
                }
                
                if(/*graphObj.edges().size() != 0 &&*/ firstPass)
                {                    
                    //auto ptrEdges = edges.begin();
                    
                    auto neighbors = graphObj.neighbors(graphObj.endpoints(*ptrEdges).first);
                    //auto neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second);
                    
                    int localRow = r;
                    int localCol = c;
                    
                    while(!neighbors.empty())
                    {
                        double newWeight = graphObj.get_edge(graphObj.endpoints(createdPath.back()).second, neighbors.front()).weight() + 1.0;
                        
                        if(mazeObj.getMaze().at(localRow).at(localCol) == ' ' || mazeObj.getMaze().at(localRow).at(localCol) == 'H' || mazeObj.getMaze().at(localRow).at(localCol) == 'O')
                        {
                            
                            if(CheckCellFromVectorListofVertices(localRow - 1, localCol))
                            {
                                if(!neighbors.empty() && cellToVertex[localRow][localCol] == neighbors.front() && graphObj.has_edge(cellToVertex[localRow-1][localCol].value(), neighbors.front()))
                                {
                                    createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow - 1][localCol].value(), newWeight));
                                    neighbors.pop_front();
                                }
                            }
                        if(CheckCellFromVectorListofVertices(localRow + 1, localCol))
                        {
                            if(!neighbors.empty() && cellToVertex[localRow][localCol] == neighbors.front() && graphObj.has_edge(cellToVertex[localRow+1][localCol].value(), neighbors.front()))
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow + 1][localCol].value(), newWeight));
                               neighbors.pop_front();
                            }
                        }
                        if(CheckCellFromVectorListofVertices(localRow, localCol - 1))
                        {
                            if(!neighbors.empty() && cellToVertex[localRow][localCol] == neighbors.front() && graphObj.has_edge(cellToVertex[localRow][localCol-1].value(), neighbors.front()))
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow][localCol - 1].value(), newWeight));
                                neighbors.pop_front();
                            }
                        }
                        if(CheckCellFromVectorListofVertices(localRow, localCol + 1))
                        {
                            if(!neighbors.empty() && cellToVertex[localRow][localCol] == neighbors.front() && graphObj.has_edge(cellToVertex[localRow][localCol+1].value(), neighbors.front()))
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow][localCol + 1].value(), newWeight));
                                neighbors.pop_front();
                            }
                        }
                        //cout << "neighbors size after: " << neighbors.size() << endl;
                    }
                    if(localCol < 15)
                    localCol++;
                    
                    else if(localCol == 15)
                    {
                        if(localRow < 15)
                        {
                            localCol = 0;
                            localRow++;
                        }
                        else
                        {
                            localCol = 0;
                            localRow = 0;
                        } 
                    }
                    if(createdPath.size() > 15) done = true; // delete after few runs 
                }
                if(!createdPath.empty() && graphObj.endpoints(createdPath.front()).first == cellToVertex[rowForStart][colForStart].value() 
                && graphObj.endpoints(createdPath.back()).second == cellToVertex[rowForEnd][colForEnd].value())
                {
                    done = true;
                }
                
                //auto neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second); // more than 1?
                if(neighbors2.empty())
                {
                    neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second);
                    neighbors2.pop_front(); // should remove the origin copy 
                    if(createdPathPtr != &createdPath.back()) createdPathPtr++;
                    else createdPathPtr = &createdPath.front();
                }
                if(ptrEdges != &edges.back())
                {
                    cout << "WTF edge from " << *graphObj.endpoints(*ptrEdges).first
                         << " to " << *graphObj.endpoints(*ptrEdges).second << endl;
                    cout << "neightbors 2 " << *neighbors2.front(); 
                    // it's looking for a edge that doesn't exists but the logic is moving it correctly
                    // this will cause a error each time as the argument requires a edge already intialized 
                    while(!graphObj.has_edge(graphObj.endpoints(*ptrEdges).second, neighbors2.front()))
                    {
                        if(neighbors2.empty()) break;

                        if(ptrEdges == &edges.back())
                        {
                            ptrEdges = &edges.front();
                        }
                        else if(graphObj.has_edge(graphObj.endpoints(*ptrEdges).second, neighbors2.front()))
                        {
                            neighbors2.pop_front(); // it's assigning the previous vertex from the original so it might back track due to this
                            break;
                        }
                            
                        ptrEdges++;
                    }
                } 
                else ptrEdges = &edges.front(); // recheck if this is needed 
                      
                }      
            }
             
            }
            
        }       
    }
    
    void usePath()
    {
        
        for(auto i : graphObj.edges())
        {
            //cout << "Edge from " << *graphObj.endpoints(i).first << " to " << *graphObj.endpoints(i).second << " with weight " << i.weight() << endl;
            int row = *graphObj.endpoints(i).first / 16;
            int col = *graphObj.endpoints(i).first % 16;
            mazeObj.changeMaze(row, col, '.');
            mazeObj.output();
            cout << flush;
            mazeObj.changeMaze(row, col, ' ');
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            
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