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
        
        //typename list<Edge>::const_iterator EdgePtrItr;
        //const Edge* ptrEdges = nullptr;
        
        typename list<Edge>::const_iterator createdPathPtrItr;
        const Edge* createdPathPtr = nullptr;
        list<Edge> tempRef;  
        list<Edge> updatedPath;
        
        list<Vertex> VertexOrder; // there is no order insertion this is the key for returning the maps order of walked path
        typename list<Vertex>::const_iterator neighborPtrItr;
        const Vertex* neighborPtr = nullptr;

        

        unordered_map<Vertex, list<Edge>, typename Vertex::Hash> pathA; // projecting outward so only use one for all possibilities
        typename unordered_map<Vertex, list<Edge>, typename Vertex::Hash>::iterator pathAPtrItr; 
        const Vertex* pathAPtr = nullptr;

        

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
                        pathA.insert({graphObj.endpoints(*createdPathPtr).first, graphObj.incident_edges_X(graphObj.endpoints(*createdPathPtr).first, graphObj.endpoints(*createdPathPtr).first)});
                        VertexOrder.push_back(graphObj.endpoints(*createdPathPtr).first);
                        tempRef = graphObj.incident_edges_X(graphObj.endpoints(*createdPathPtr).second, graphObj.endpoints(*createdPathPtr).first);
                        
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
                // if needs to check or not ?? 
                while(startWalk)
                {
                    if(pathA.size() > 1)
                    {
                        cout << "x";
                    }
                    list<Edge> incomingRef;
                    Vertex tempVertex; 
                    pathA.insert({graphObj.endpoints(tempRef.front()).first, tempRef});
                    VertexOrder.push_back(graphObj.endpoints(tempRef.front()).first);
                    //  pathA.insert({graphObj.endpoints(tempRef.front()).first, tempRef})
                    // needs a weight function
                    /*
                    if(!tempRef.empty())
                    {
                       //incomingRef = graphObj.incident_edges_X(graphObj.endpoints(tempRef.front()).second); // looking to balance a merge
                       tempVertex = graphObj.endpoints(tempRef.front()).first; // this should be the same vertex origin for all
                       tempRef.pop_front();
                    }else
                    {
                        pathA.insert({tempVertex, std::move(updatedPath)});
                        tempRef = graphObj.incident_edges_X(tempVertex);
                        incomingRef = graphObj.incident_edges_X(graphObj.endpoints(tempRef.front()).second); // looking to balance a merge
                        tempVertex = graphObj.endpoints(tempRef.front()).first;
                        tempRef.pop_front(); 
                    }

                    for(const Edge& itr : incomingRef)
                    {
                        Edge newEdge = graphObj.insert_edge(tempVertex, graphObj.endpoints(itr).second, 2.0);
                        updatedPath.push_back(newEdge);
                    }                   
                    */
                }// end of while(startWalk)
                      
             
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