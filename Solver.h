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
    // it might be more efficent to handle the weighing here and simply assign a front to start and end to end 
    // as I can utilize the graph.h functions directly 
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
        list<Edge> pathListA = graphObj.edges();
        list<Edge> PathListB;
        list<Edge> PathListC;
        bool done = false;

        while(!done)
        {
            for(auto i = pathListA.begin(); i != pathListA.end(); i++)
            {   
                auto j = graphObj.neighbors(graphObj.endpoints(*i).first);
                double newWeight = graphObj.get_edge(graphObj.endpoints(*i).first, j.front()).weight() + 1.0;
                cout << "TESTER A" << endl;
                /*
                if(graphObj.endpoints(createdPath.front()).first == cellToVertex[rowForStart][colForStart] && 
                graphObj.endpoints(createdPath.back()).second == cellToVertex[rowForEnd][colForEnd])
                {
                    //createdPath = PathListB;
                    done = true;
                    break;
                }
                */
                // This is to initialize the start 
                if(PathListB.empty() && graphObj.endpoints(*i).first == cellToVertex[rowForStart][colForStart].value())
                {
                    cout << "TESTER B" << endl;
                    
                    //if(graphObj.has_edge(graphObj.endpoints(*i).first, j.front()))
                    //{
                        while(!j.empty())
                        {
                            //newWeight = graphObj.get_edge(graphObj.endpoints(*i).first, j.first())->weight + 1.0;
                            PathListB.push_back(graphObj.insert_edge(graphObj.endpoints(*i).first, j.front(), newWeight));
                            j.pop_front();
                            if(j.size() >= 1)
                            {
                                PathListC.push_back(graphObj.insert_edge(graphObj.endpoints(*i).first, j.front(), newWeight));
                                j.pop_front();
                            }
                        }
                    //}
                     
                    //graphObj.erase(graphObj.endpoints(i).first);
                }
                // The seperation becomes more apparent here as I need to check the neighbors of the neighbors 
                // and then compare weights to find the lowest weight path to assign to a list of edges that I can then output at the end
                if(!PathListB.empty())
                {
                    
                    cout << "TESTER C" << endl;
                    
                    //if(graphObj.has_edge(graphObj.endpoints(*i).first, j.front()))
                    //{
                        while(!j.empty())
                        {
                            cout << "TESTER E" << endl;
                            PathListB.push_back(graphObj.insert_edge(graphObj.endpoints(*i).first, j.front(), newWeight));
                            j.pop_front();
                            if(j.size() >= 1)
                            {
                                PathListC.push_back(graphObj.insert_edge(j.front(), graphObj.endpoints(*i).first, newWeight));
                                j.pop_front();
                            }
                        }    
                    //}
                    cout << "PathListB size: " << PathListB.size() << endl;
                    cout << "PathListC size: " << PathListC.size() << endl;
                    auto itrB = PathListB.begin();
                        while(itrB != PathListB.end() && !PathListC.empty())
                        {
                            auto itrC = PathListC.begin();
                            bool erasedB = false;
                            bool erasedC = false;
                            
                            cout << "TESTER F" << endl;
                            
                            while(itrC != PathListC.end() || !PathListC.empty())
                            {
                                cout << "THE WHILE IS WORKING" << endl;

                                if( graphObj.has_edge(graphObj.endpoints(*itrB).first, graphObj.endpoints(*itrB).second) &&
                                    graphObj.has_edge(graphObj.endpoints(*itrC).first, graphObj.endpoints(*itrC).second) &&
                                    graphObj.endpoints(*itrB).second == graphObj.endpoints(*itrC).second)
                                {
                                    cout << "TESTER G" << endl;
                                    
                                    if(graphObj.get_edge(graphObj.endpoints(*itrC).first,graphObj.endpoints(*itrC).second).weight() 
                                    < graphObj.get_edge(graphObj.endpoints(*itrB).first,graphObj.endpoints(*itrB).second).weight())
                                    {
                                        //auto next = itrB;
                                        //++next;
                                        cout << "TESTER H" << endl;                                        
                                        itrB = PathListB.erase(itrB);
                                        erasedB = true;
                                        //itrB = next;
                                        break;
                                        
                                    }
                                    else
                                    {
                                        //auto next = itrC;
                                        //++next;
                                        cout << "TESTER I" << endl;
                                        itrC = PathListC.erase(itrC);
                                        erasedC = true;
                                        //itrC = next;
                                        //found = true;
                                    }
                                }
                                if(!erasedC)
                                {
                                   ++itrC;
                                }
                                    
                            }
                            if(!erasedB)
                            {
                                ++itrB;
                            }
                        }
                   
                }
            }
            if(!PathListB.empty() && graphObj.endpoints(PathListB.front()).first == cellToVertex[rowForStart][colForStart] && 
                graphObj.endpoints(PathListB.back()).second == cellToVertex[rowForEnd][colForEnd])
            {
                createdPath = move(PathListB);
                done = true;
            }
            else if(!PathListC.empty() && graphObj.endpoints(PathListC.front()).first == cellToVertex[rowForStart][colForStart] && 
                graphObj.endpoints(PathListC.back()).second == cellToVertex[rowForEnd][colForEnd])
            {
                createdPath = move(PathListC);
                done = true;
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