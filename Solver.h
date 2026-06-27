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
        //reassign edges 
        double newWeight;

        //control operation tokens
        bool done = false;
        bool firstPass = false;
        list<Edge> edges;
        
        typename list<Edge>::const_iterator EdgePtrItr;
        const Edge* ptrEdges = nullptr;

        typename list<Edge>::const_iterator createdPathPtrItr;
        const Edge* createdPathPtr = nullptr;

        list<Vertex> neighbors; 
        list<Vertex> neighbors2; // neighbor of a neighbor 
        

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
                        EdgePtrItr = edges.begin();
                        ptrEdges = &(*EdgePtrItr); // can change to just direct object reference instead of edges
                        neighbors = graphObj.neighbors(graphObj.endpoints(*ptrEdges).first);
                        
                        createdPathPtrItr = createdPath.begin();
                        createdPathPtr = &(*createdPathPtrItr);
                        neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second);
                        //neighbors2.pop_front(); // should remove the origin copy over
                        neighbors2.remove(graphObj.endpoints(*ptrEdges).first);
                    } 
                    
                }
                
                if(firstPass)
                {                    
                    
                    //auto neighbors = graphObj.neighbors(graphObj.endpoints(*ptrEdges).first);
                    
                    int localRow = r;
                    int localCol = c;
                    
                    // Soon I'll have to start removing unnecassary weight 
                    // changed to neighbors2 to check this logic out same thing with every if statement !neighbors.empty 
                    while(!neighbors2.empty())
                    {       
                        // for now the issue is the neighbors are random so this pass can work to find a actual edge                 
                        // using incident edges function can be more optimal than using neighbors2 as it's the same thing except using the custom map already designed for storing data
                        for(auto i : neighbors2)
                        {
                            if(graphObj.has_edge(graphObj.endpoints(createdPath.back()).second, i))
                            {
                                newWeight = graphObj.get_edge(graphObj.endpoints(createdPath.back()).second, i).weight() + 1.0;
                                break;
                            }
                        }
                        // add the logic not to duplicate in the if enclosing the assignment operation 
                        // it's possible to check for duplicates in createdPath
                        // another possible idea is remove them from edges map entirely 
                        if(mazeObj.getMaze().at(localRow).at(localCol) == ' ' || mazeObj.getMaze().at(localRow).at(localCol) == 'H' || mazeObj.getMaze().at(localRow).at(localCol) == 'O')
                        {
                            
                            if(CheckCellFromVectorListofVertices(localRow - 1, localCol))
                            {
                                if(!neighbors2.empty() && cellToVertex[localRow][localCol] == neighbors.front() )
                                {
                                    for(auto chk : createdPath)
                                    {
                                        if(chk == graphObj.get_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow - 1][localCol]))
                                        break;
                                        else if(chk == createdPath.end())
                                        createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow - 1][localCol].value(), newWeight));
                                    }

                                    for(auto itr = neighbors2.begin(); itr != neighbors2.end();)
                                    {   
                                        if(*itr == cellToVertex[localRow-1][localCol])
                                        {
                                            itr = neighbors2.erase(itr); 
                                        } 
                                        else ++itr;
                                    }
                                }
                            }
                        if(CheckCellFromVectorListofVertices(localRow + 1, localCol))
                        {
                            if(!neighbors2.empty() && cellToVertex[localRow][localCol] == neighbors.front() )
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow + 1][localCol].value(), newWeight));
                                    
                                    for(auto chk : createdPath)
                                    {
                                        if(chk == graphObj.get_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow + 1][localCol]))
                                        break;
                                        else if(chk == createdPath.end())
                                        createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow + 1][localCol].value(), newWeight));
                                    }
                                    for(auto itr = neighbors2.begin(); itr != neighbors2.end();)
                                    {
                                        if(*itr == cellToVertex[localRow+1][localCol]) 
                                        {
                                            itr = neighbors2.erase(itr);
                                            break;
                                        }
                                        else ++itr;
                                    }
                            }
                        }
                        if(CheckCellFromVectorListofVertices(localRow, localCol - 1))
                        {
                            if(!neighbors2.empty() && cellToVertex[localRow][localCol] == neighbors.front() )
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow][localCol - 1].value(), newWeight));

                                    for(auto chk : createdPath)
                                    {
                                        if(chk == graphObj.get_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow][localCol - 1]))
                                        break;
                                        else if(chk == createdPath.end())
                                        createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow ][localCol- 1].value(), newWeight));
                                    }
                                    for(auto itr = neighbors2.begin(); itr != neighbors2.end();)
                                    {
                                        if(*itr == cellToVertex[localRow][localCol-1])
                                        {
                                            itr = neighbors2.erase(itr);
                                            break;
                                        }
                                        else ++itr;
                                    }
                            }
                        }
                        if(CheckCellFromVectorListofVertices(localRow, localCol + 1))
                        {
                            if(!neighbors2.empty() && cellToVertex[localRow][localCol] == neighbors.front() )
                            {
                                createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow][localCol + 1].value(), newWeight));

                                    for(auto chk : createdPath)
                                    {
                                        if(chk == graphObj.get_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow ][localCol+ 1]))
                                        break;
                                        else if(chk == createdPath.end())
                                        createdPath.push_back(graphObj.insert_edge(cellToVertex[localRow][localCol].value(), cellToVertex[localRow ][localCol+ 1].value(), newWeight));
                                    }
                                    for(auto itr = neighbors2.begin(); itr != neighbors2.end();)
                                    {
                                        if(*itr == cellToVertex[localRow][localCol+1]) 
                                        {
                                            itr = neighbors2.erase(itr);
                                            break;
                                        }
                                        else ++itr;
                                    }
                            }
                        }
                        
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
                    
                }
                if(!createdPath.empty() && (graphObj.endpoints(createdPath.front()).first == cellToVertex[rowForStart][colForStart].value()) 
                && (graphObj.endpoints(createdPath.back()).second == cellToVertex[rowForEnd][colForEnd].value()))
                {
                    done = true;
                    break;
                }
                
                if(neighbors2.empty())
                {
                    if(createdPathPtrItr != createdPath.end())
                    {
                        ++createdPathPtrItr; // one pass  
                        createdPathPtr = &(*createdPathPtrItr);  
                        neighbors2 = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).second); // get a new reference list of vertex
                    } 
                    else done = true; 
                    // try another idea with adjacent function same thing just uses the maps 
                }

                if(EdgePtrItr != edges.end())
                {    
                    ++EdgePtrItr;
                    ptrEdges = &(*EdgePtrItr);
                } 
                else
                {
                    EdgePtrItr = edges.begin(); // recheck if this is needed
                    ptrEdges = &(*EdgePtrItr);
                } 
                    while(!graphObj.has_edge(graphObj.endpoints(*ptrEdges).second, neighbors2.front()))
                    {
                        ptrEdges = &(*EdgePtrItr);
                        if(EdgePtrItr == edges.end())
                        {
                            EdgePtrItr = edges.begin(); // circle back around 
                            ptrEdges = &(*EdgePtrItr);
                            if(graphObj.has_edge(graphObj.endpoints(*ptrEdges).second, neighbors2.front()))
                            {
                                // finds the neighbor should I also remove any index in here that are already listed a edges 
                                // it possible that it can populate looping through as the logic ask for a edge 
                                neighbors = graphObj.neighbors(graphObj.endpoints(*ptrEdges).first);
                                //neighbors2.pop_front();
                                break;
                            }
                        }

                        if(graphObj.has_edge(graphObj.endpoints(*ptrEdges).second, neighbors2.front()))
                        {
                            //neighbors2.pop_front();
                            neighbors = graphObj.neighbors(graphObj.endpoints(*ptrEdges).first);
                            break;
                        }
                        ++EdgePtrItr;                       
                    }
                
                      
                }      
            }
             
            }
            // really no better way to exit quicker that I know of for now 
            if(!createdPath.empty() && (graphObj.endpoints(createdPath.front()).first == cellToVertex[rowForStart][colForStart].value()) 
                && (graphObj.endpoints(createdPath.back()).second == cellToVertex[rowForEnd][colForEnd].value()))
                {
                    done = true;
                    break;
                }
        }       
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