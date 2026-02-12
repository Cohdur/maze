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
    // DIRECTED OR NOT DIRECTED??
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
                    cout << 'a' << endl;

                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, big_size - 1);
                    int random_choice2 = distrib(engine);
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice + 1).at(random_choice2) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice2).at(random_choice + 1) = ' ';
                }
                break;
                case 1 :
                {
                    cout << '1' << endl;
                    std::vector<int> wall_choices{0, big_size - 1}; // can create one local variable up top for more professional look 
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                        
                        big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                }
                break;
                case 2 :
                {
                    cout << '2' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';

                }
                break;
                case 3 :
                {
                    cout << '3' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 4 :
                {
                    cout << '4' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' '; 
                }
                break;
                case 5 :
                {
                    cout << '5' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' '; 

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                     
                }
                break;
                case 6 :
                {
                    cout << '6' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' '; 

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                     
                }
                break;
                case 7 :
                {
                    cout << '7' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                     
                }
                break;
                case 8 :
                {
                    cout << '8' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 9 :
                {
                    cout << '9' << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 10 :
                {
                    cout << "10" << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 11 :
                {
                    cout << "11" << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' '; 

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                     
                }
                break;
                case 12 :
                {
                    cout << "12" << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 13 :
                {
                    cout << "13" << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 14 :
                {
                    cout << "14" << endl;
                    std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' '; 

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
                }
                break;
                case 15 :
                {
                    cout << "15" << endl;
                     std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, 1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0) 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    else if(random_choice2 == (big_size - 1))
                        big_maze.at(random_choice).at(random_choice2 - 1) = ' ';

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0) 
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    else if(random_choice2 == (big_size - 1))
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';                    
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

/*
using namespace std;

int main()
{
    maze<char, int> game;
    
    game.createMaze();
    
    // for sake this is just a test on algorithm I'll refine the maze with multiple calls 
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    game.create_openeings();
    
    
    game.output();
}
*/