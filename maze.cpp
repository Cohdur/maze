#include<vector>
#include<iostream>
#include<ctime>
#include<random>
#include<map>
#include<list>
#include<memory>
//#include<queue>


#include "Graph.h"

using namespace std; // delete after testing 

template<typename V,typename E>
class maze : public Graph<V, E> // char = character/ board & int is edge weight
{
    public:
    maze() : Graph<V, E>(false) {} // Explicitly call the base class constructor || There may be circles so not acycle

    private:

    typedef Graph<V,E> g;
    typedef typename g::Vertex Vertex;
    typedef typename g::Edge Edge;

    typedef std::map<typename Graph<V,E>::Vertex, typename Graph<V,E>::Edge> trial;



    const static int size = 4;
    const static int big_size = size * 4;

    int startIndex;
    int endIndex;
    
    std::vector<std::vector<char>> big_maze; 
    // changes these to hold vertex or utilize to add value to vertex for edge weight
    // simply assign a pointer to each one per vertex as created in class then assign the open and close as start end
    // each weight is 1 that way from start to end each possible edge is tested with arthimetic math +1 per vertex
    // output the path at the end if found per move update
    std::vector<std::vector<char>> grid
    {
        {'+', '+', '+', '+'},
        {'+', ' ', ' ', '+'},
        {'+', ' ', ' ', '+'},
        {'+', '+', '+', '+'}
    };

    public :


    class Position : public Graph<V,E>::Vertex
    {
        private:
        
        Vertex* Start{nullptr};
        Vertex* End{nullptr};
        std::shared_ptr<Vertex> pos{nullptr};
        Position(const typename Graph<V, E>::Vertex* v) : pos{const_cast<typename Graph<V, E>::Vertex*>(v)} {}
    
    };
    
    class Path : public Graph<V,E>::Edge
    {
        private:
        typename Graph<V,E>::Edge* edge{nullptr};
        Path(const Edge* e) : edge{const_cast<Edge*>(e)} {}
    
    };

    protected :
    std::list<Vertex> vertices;
    std::list<Edge> edges;

    bool condition = false;
    public : 

        void create_openeings()
        {
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<> distrib(2, big_size - 3);

            int random_choice = distrib(engine);
            int random_choice2 = distrib(engine);
            for(auto i : big_maze)
            {
                

            if(big_maze.at(random_choice).at(random_choice2) == '+')
            {
                int n = 1;
                if(big_maze.at(random_choice + n).at(random_choice2) == '+')
                {
                    big_maze.at(random_choice + n).at(random_choice2) = ' ';

                    // not pushing to git so this is last prior to edit: while(big_maze.at(random_choice + n)
                    while(big_maze.at(random_choice).at(random_choice2) != ' ' /*&& 
                    random_choice != 2 && random_choice != big_size - 3 || 
                    random_choice2 != 2 && random_choice2 != big_size - 3*/)
                    {
                        if( big_maze.at(random_choice + n).at(random_choice2) == ' ')
                        {
                            if(big_maze.at(random_choice).at(random_choice2) == '+')
                            big_maze.at(random_choice).at(random_choice2) = ' ';
                            
                            break;
                        }else
                        big_maze.at(random_choice + n).at(random_choice2) = ' ';
                        n++;
                        //break;
                    }
                }
                else if(big_maze.at(random_choice - n).at(random_choice2) == '+')
                {
                    big_maze.at(random_choice - n).at(random_choice2) = ' ';
    
                    //same
                    while(big_maze.at(random_choice).at(random_choice2) != ' ' /*&& 
                    random_choice != 2 && random_choice != big_size - 3 ||
                    random_choice2 != 2 && random_choice2 != big_size - 3*/)
                    {
                        if( big_maze.at(random_choice + n ).at(random_choice2) == ' ')
                        {
                            if(big_maze.at(random_choice).at(random_choice2) == '+')
                            big_maze.at(random_choice).at(random_choice2) = ' ';
                            
                            break;
                        }else
                        big_maze.at(random_choice + n).at(random_choice2) = ' ';
                        n++;
                        //break;
                    }
                }
                else if(big_maze.at(random_choice).at(random_choice2 + 1) == '+')
                {
                    big_maze.at(random_choice).at(random_choice2 + n) = ' ';

                    //same
                    while(big_maze.at(random_choice).at(random_choice2 ) != ' ' /*&& 
                    random_choice != 2 && random_choice != big_size - 3 ||
                    random_choice2 != 2 && random_choice2 != big_size - 3*/)
                    {
                        if( big_maze.at(random_choice).at(random_choice2 + n) == ' ')
                        {
                            if(big_maze.at(random_choice).at(random_choice2) == '+')
                            big_maze.at(random_choice).at(random_choice2) = ' ';
                            
                            break;
                        }else
                        big_maze.at(random_choice).at(random_choice2 + n) = ' ';
                        n++;
                        //break;
                    }
                }
                else if(big_maze.at(random_choice).at(random_choice2 - n) == '+')
                {
                    big_maze.at(random_choice).at(random_choice2 - n) = ' ';

                    while(big_maze.at(random_choice).at(random_choice2 ) != ' ' /*&& 
                    random_choice != 2 && random_choice != big_size - 3 ||
                    random_choice2 != 2 && random_choice2 != big_size - 3*/)
                    {
                        if( big_maze.at(random_choice).at(random_choice2 - n) == ' ')
                        {
                            if(big_maze.at(random_choice).at(random_choice2) == '+')
                            big_maze.at(random_choice).at(random_choice2) = ' ';
                            
                            break;
                        }else
                        big_maze.at(random_choice).at(random_choice2 - n) = ' ';
                        n++;
                        //break;
                    }
                }
                big_maze.at(random_choice).at(random_choice2) = ' ';

                //std::cout << n << std::endl; // erase + delete breaks 
            }

            else 
            {
                while(big_maze.at(random_choice).at(random_choice2) != '+')
                {
                    random_choice = distrib(engine);
                    random_choice2 = distrib(engine);
                   // cout << "CHECK THIS BODY " << endl;
                    // redundant maybe delete for optimization 2/2/2026
                    /*
                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                    {
                        break;
                    }
                    */
                    
                    
                    
                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                    {
                        int n = 1;
                        if(big_maze.at(random_choice + n).at(random_choice2) == '+')
                        {
                            big_maze.at(random_choice + n).at(random_choice2) = ' ';
        
                            while(big_maze.at(random_choice).at(random_choice2) != ' ' /*&& 
                            random_choice != 2 && random_choice != big_size - 3 || 
                            random_choice2 != 2 && random_choice2 != big_size - 3*/)
                            {
                                if( big_maze.at(random_choice + n).at(random_choice2) == ' ')
                                {
                                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                                    big_maze.at(random_choice).at(random_choice2) = ' ';
                                    
                                    break;
                                }else
                                big_maze.at(random_choice + n).at(random_choice2) = ' ';
                                n++;
                                //break;
                            }
                        }
                        else if(big_maze.at(random_choice - n).at(random_choice2) == '+')
                        {
                            big_maze.at(random_choice - n).at(random_choice2) = ' ';
            
                            while(big_maze.at(random_choice ).at(random_choice2) != ' ' /*&& 
                            random_choice != 2 && random_choice != big_size - 3 ||
                            random_choice2 != 2 && random_choice2 != big_size - 3*/)
                            {
                                if( big_maze.at(random_choice + n ).at(random_choice2) == ' ')
                                {
                                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                                    big_maze.at(random_choice).at(random_choice2) = ' ';
                                    break;
                                }else
                                big_maze.at(random_choice + n).at(random_choice2) = ' ';
                                n++;
                                //break;
                            }
                        }
                        else if(big_maze.at(random_choice).at(random_choice2 + 1) == '+')
                        {
                            big_maze.at(random_choice).at(random_choice2 + n) = ' ';
        
                            while(big_maze.at(random_choice).at(random_choice2 ) != ' ' /*&& 
                            random_choice != 2 && random_choice != big_size - 3 ||
                            random_choice2 != 2 && random_choice2 != big_size - 3*/)
                            {
                                if( big_maze.at(random_choice).at(random_choice2 + n) == ' ')
                                {
                                    if(big_maze.at(random_choice).at(random_choice2) == '+');
                                    big_maze.at(random_choice).at(random_choice2) = ' ';
                                    break;
                                }else
                                big_maze.at(random_choice).at(random_choice2 + n) = ' ';
                                n++;
                                //break;
                            }
                        }
                        else if(big_maze.at(random_choice).at(random_choice2 - n) == '+')
                        {
                            big_maze.at(random_choice).at(random_choice2 - n) = ' ';
        
                            while(big_maze.at(random_choice).at(random_choice2 ) != ' ' /*&& 
                            random_choice != 2 && random_choice != big_size - 3 ||
                            random_choice2 != 2 && random_choice2 != big_size - 3*/)
                            {
                                if( big_maze.at(random_choice).at(random_choice2 - n) == ' ')
                                {
                                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                                    big_maze.at(random_choice).at(random_choice2) = ' ';
                                    break;
                                }else
                                big_maze.at(random_choice).at(random_choice2 - n) = ' ';
                                n++;
                                //break;
                            }
                        }
                        // commented out 2/2/2026 seemed to be illogical 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                }
                //break; // erase here ?
            }   
            }
        
    }
            
        }
        
        void createMaze()
        {
            
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<> distrib(0, big_size - 1); //Grid_choices.size() - 1); 
            
            int random_choice = distrib(engine);
            //int random_choice = Grid_choices[distrib(engine)];

            // Initialize big_maze with the correct size
            big_maze.resize(big_size, std::vector<char>(big_size, ' '));
            
            // Fill big_maze with repeated copies of grid
            for(int block_row = 0; block_row < 4; ++block_row)
            {
                for (int block_col = 0; block_col < 4; ++block_col)
                {
                    for (int i = 0; i < size; ++i)
                    {
                        for (int j = 0; j < size; ++j)
                        {
                            big_maze[block_row * size + i][block_col * size + j] = grid[i][j]; // maybe use pointer arthmetic instead

                        }
                    }
                }
            }
            

            //Just assigning a start which needs to be root/first vertex assigned for algorithm -> exit 'H'
            switch(random_choice)
            {
                case 0 : 
                {
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, big_size - 1);
                    int random_choice2 = distrib(engine);
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 1 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 2 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 3 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 4 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 5 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 6 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 7 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 8 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 9 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 10 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 11 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 12 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 13 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 14 :
                {
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 15 :
                {
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, big_size - 1);
                    int random_choice2 = distrib(engine);
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                default :
                std::cout << "it didn't work " << std::endl;
                break;
            }

        }

        void output()
        {
            for(auto i : big_maze)
            {
                for(auto x : i)
                {
                    std::cout << x << ' ';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::cout << condition << std::endl;

        }
    

};


using namespace std;

int main()
{
    maze<char, int> game;

    game.createMaze();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
 

    game.output();
}