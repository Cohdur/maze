#include<iostream>
#include<sstream>
#include<thread>
#include<chrono>
#include<climits>
#include<optional>
#include<unordered_map>
#include<map>
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
    int createdPathSize = 0;

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
        int controlNumber;
        //reassign edges 
        double newWeight = 0; 
        //control operation tokens
        bool done = false;
        bool firstPass = false;
        bool startWalk = false;
        list<Edge> edges; // not being used 
        
        //typename list<Edge>::const_iterator EdgePtrItr;
        //const Edge* ptrEdges = nullptr;
        
        typename list<Edge>::const_iterator createdPathPtrItr;
        const Edge* createdPathPtr = nullptr;
        
        list<Vertex> neighbors; 
        list<Edge> tempRef; // not being used 

        unordered_map<Vertex, list<Edge>, typename Vertex::Hash> pathA; // projecting outward so only use one for all possibilities 
        unordered_map<Vertex, list<Edge>, typename Vertex::Hash> pathB; 
        unordered_map<Vertex, list<Edge>, typename Vertex::Hash> pathC; 
        

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
                        createdPathSize = createdPath.size();
                        createdPathPtrItr = createdPath.begin();
                        createdPathPtr = &(*createdPathPtrItr);
                        pathA.insert({graphObj.endpoints(*createdPathPtr).second, graphObj.incident_edges(graphObj.endpoints(*createdPathPtr).second)});
                        startWalk = true;

                    } 
                    
                }

                }
            }    
            
                // instead maybe use a sentinal value to propigate the logic of weighing into a extended edge to find a common vertex and check the weight amongst them 
                   
                if(!createdPath.empty() && (graphObj.endpoints(createdPath.front()).first == cellToVertex[rowForStart][colForStart].value()) 
                && (graphObj.endpoints(createdPath.back()).second == cellToVertex[rowForEnd][colForEnd].value()))
                {
                    done = true;
                    break;
                }
                // ok the incoming map from incident_edges() can be used to see if the current paths are meeting somewhere.
                while(startWalk)
                {
                    list<Edge> incomingRef;
                    list<Edge> updatedPath;
                    for(auto walk = pathA.begin(); walk != pathA.end(); ++walk)
                    {
                        tempRef = walk->second;
                        incomingRef = graphObj.incident_edges(graphObj.endpoints(tempRef.front()).second); // looking to balance a merge

                        for(auto itr = walk->second.begin(); itr != walk->second.end(); ++itr )
                        {
                            pathA.insert({walk->first, updatedPath.push_back(graphObj.insert_edge(walk->first, graphObj.endpoints(*itr).second, 2.0))}); // slight change to 2.0
                        }
                        

                    }
                }
    
                // end of while(startWalk)      
                    
                    if(createdPathPtrItr != createdPath.end()) 
                    {
                        // 
                        if(createdPathSize != createdPath.size())
                        {                           
                            // not really liking this design 
                            /*
                            
                            neighbors = graphObj.neighbors(graphObj.endpoints(*createdPathPtr).first);
                            if(neighbors.size() == 3)
                            {
                                pathA.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                pathA.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                pathA.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                startWalk = true;
                                
                            }
                            else if(neighbors.size() == 2)
                            {
                                pathA.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                pathB.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                startWalk = true;
                                
                            }
                            else if(neighbors.size() == 1)
                            {
                                pathA.insert({graphObj.endpoints(neighbors.front()).first, graphObj.incident_edges(graphObj.endpoints(neighbors.front()).first)});
                                neighbors.pop_front();
                                startWalk = true;
                                controlNumber = 1;
                            }
                            ++createdPathPtrItr; // one pass  
                            createdPathPtr = &(*createdPathPtrItr); 
                            */                           
                            //newWeight = createdPath.size() - neighbors.size() + 2; // this would need to more dynamic per edge so not here 
                        }                    
                    }else done = true;
                      
             

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