#include<sstream>
#include<thread>
#include<chrono>
#include<climits>
#include<functional>
#include<queue>
#include<optional>
#include<map>
#include<utility> 
#include<ranges>

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
        
        
        typename list<Edge>::const_iterator createdPathPtrItr;
        const Edge* createdPathPtr = nullptr;
        list<Edge> createdPath;

        list<Edge> tempRef;
        list<Edge> stemmedTree;
        vector<Vertex> stemmedTreeKeys;

        list<pair<Vertex, double>> lightestEdge;
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

                        pathA.insert({graphObj.endpoints(*createdPathPtr).first, graphObj.incident_edges(graphObj.endpoints(*createdPathPtr).first)});
                        newWeight = pathA.begin()->second.front().weight() + pathA.begin()->second.size();
                        graphObj.insert_edge(pathA.begin()->first, graphObj.endpoints(pathA.begin()->second.front()).second, newWeight);
                        VertexOrder.push_back(graphObj.endpoints(*createdPathPtr).first);

                        tempRef = graphObj.incident_edges_X(graphObj.endpoints(*createdPathPtr).second, graphObj.endpoints(*createdPathPtr).first);
                        pathA.insert({graphObj.endpoints(tempRef.front()).first, tempRef});

                        for(auto i : tempRef)
                        {
                            // one origin two or more vertex need to be weighed based on distance from start 
                            newWeight = i.weight() + graphObj.get_edge(graphObj.endpoints(i).first, graphObj.endpoints(i).second).weight();
                            graphObj.insert_edge(graphObj.endpoints(i).first, graphObj.endpoints(i).second, newWeight);
                        }

                        VertexOrder.push_back(graphObj.endpoints(tempRef.front()).first); // these are all the same origin vertex
                        startWalk = true;
                    } // pathA is pushing back a extra vertex with a empty list?? ////////////
                    
                }

                }
            }    
                    
                        if(!pathA.empty() && (VertexOrder.front() == cellToVertex[rowForStart][colForStart].value()) 
                        && (VertexOrder.back() == cellToVertex[rowForEnd][colForEnd].value()))
                        {
                            done = true;
                            break;
                        }

                        if(!tempRef.empty())
                        {                           
                            stemmedTree = graphObj.incident_edges_X(graphObj.endpoints(tempRef.front()).second, graphObj.endpoints(tempRef.front()).first); // quickly check for matches
                            if(stemmedTree.empty())
                            {
                                stemmedTree = graphObj.incident_edges(graphObj.endpoints(tempRef.front()).second);
                                if(graphObj.endpoints(stemmedTree.front()).first == cellToVertex[rowForEnd][colForEnd].value())
                                {
                                    done = true;
                                    break;
                                }else stemmedTree.clear(); // removing the situation that uses this at dead ends suspected bug for loops
                            }

                            if(stemmedTreeKeys.empty())
                            {
                               stemmedTreeKeys.push_back(graphObj.endpoints(stemmedTree.front()).first);  
                            }
                            else
                            {   
                                for(const auto& i : views::reverse(stemmedTreeKeys))
                                {
                                    if(i == stemmedTreeKeys.front() && i != graphObj.endpoints(stemmedTree.front()).first)
                                    {
                                        stemmedTreeKeys.push_back(graphObj.endpoints(stemmedTree.front()).first); 
                                    }else if(i == graphObj.endpoints(stemmedTree.front()).first) break; // no duplicates for keys 
                                }                               
                            }                            
                            
                            for(const auto& i : stemmedTree)
                            {    // this has to be where the loop is happening                             
                                newWeight = tempRef.front().weight() + i.weight(); 
                                //graphObj.insert_edge(graphObj.endpoints(i).first, graphObj.endpoints(i).second, newWeight);                               

                                for(const auto& j : views::reverse(VertexOrder))
                                {
                                    for(const auto& k : pathA[j])
                                    {
                                        if(graphObj.endpoints(k).first == graphObj.endpoints(i).second) break;
                                        else if(j == VertexOrder.front() && (graphObj.endpoints(k).first != graphObj.endpoints(i).second))
                                        {
                                            graphObj.insert_edge(graphObj.endpoints(i).first, graphObj.endpoints(i).second, newWeight); 
                                            pathA.insert({graphObj.endpoints(i).first, stemmedTree});
                                            if(VertexOrder.back() != graphObj.endpoints(i).first) // this is based on pattern it can be faulty 
                                            VertexOrder.push_back(graphObj.endpoints(i).first); 
                                            //break;
                                        }
                                    } 
                                }                                                          
                            }
                            tempRef.pop_front(); 
                        } // so look for matches the assignment is already started for tempRef use tempRef.move(stemmedTree) for the next wave 
                        else
                        {                       
                            if(stemmedTreeKeys.size() > 1)
                            {
                                for(auto key : stemmedTreeKeys)
                                {
                                    if(!pathA[key].empty())
                                    {
                                        for(auto i : pathA[key])
                                        {
                                            tempRef.push_back(i);
                                        }
                                    }
                                }
                                stemmedTreeKeys.clear(); // clear for a new set of keys 
                            }else if(stemmedTreeKeys.size() == 1)
                            {
                               tempRef = move(stemmedTree); // this is the next wave of edges to check for matches
                               stemmedTreeKeys.clear();
                            }else{done == true;}
                            
                        } // else close                          
    } // end of while(done)

    while(!done)
    {
        for(const auto& itr : views::reverse(VertexOrder))
        {
            list<Edge> edgeRef = pathA[itr];
            for(const auto& itr2 : edgeRef)
            {
                if(createdPath.size() == 1 && graphObj.endpoints(itr2).first == cellToVertex[rowForEnd][colForEnd].value()) // right now its itr2.first due to using incoming map should be .second
            {
                list<Edge> EndCase = graphObj.incident_edges_X(graphObj.endpoints(itr2).second, graphObj.endpoints(itr2).first, false); // these two arguments should be flipped if above is false
                for(const auto& itr3 : EndCase)
                {
                    if(lightestEdge.empty())
                    lightestEdge.emplace_back(graphObj.endpoints(itr3).second, itr3.weight());               
                    else if(!lightestEdge.empty() && itr3.weight() < lightestEdge.front().second)
                    {
                        lightestEdge.pop_front();
                        lightestEdge.emplace_back(graphObj.endpoints(itr3).second, itr3.weight());
                    }
                }
                createdPath.push_front(pathA[lightestEdge.front().first].front());
                lightestEdge.clear();
            }

            else if(createdPath.size() > 1 && graphObj.endpoints(itr2).second == graphObj.endpoints(createdPath.front()).first)
            {
                list<Edge> EndCase = graphObj.incident_edges_X(graphObj.endpoints(itr2).first, graphObj.endpoints(itr2).second, false);
                for(const auto& itr3 : EndCase)
                {
                    if(lightestEdge.empty())
                    lightestEdge.emplace_back(graphObj.endpoints(itr3).second, itr3.weight());               
                    else if(!lightestEdge.empty() && itr3.weight() < lightestEdge.front().second)
                    {
                        lightestEdge.pop_front();
                        lightestEdge.emplace_back(graphObj.endpoints(itr3).second, itr3.weight());
                    }
                }
                createdPath.push_front(pathA[lightestEdge.front().first].front());
                lightestEdge.clear();
            }
            
            }
        } // close a for loop 
        if(graphObj.endpoints(createdPath.back()).first == cellToVertex[rowForStart][colForStart].value() && graphObj.endpoints(createdPath.front()).second == cellToVertex[rowForEnd][colForEnd].value()) done = true;
    }

} // end of createEdges()
    
    void usePath()
    {
        
        for(auto i : views::reverse(createdPath))
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