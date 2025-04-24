#include<vector>
#include<iostream>
#include<ctime>
#include<random>
#include<map>

#include "Graph.h"

template<typename V,typename E>
class maze : public Graph<V, E> // char = character/ board & int is edge weight
{
    public:
    maze() : Graph<V, E>(false) {} // Explicitly call the base class constructor

    private:

    typedef Graph<V,E> g;

    typedef std::map<typename Graph<V,E>::Vertex, typename Graph<V,E>::Edge> trial;


    const static int size = 4;
    const static int big_size = size * 4;
    std::vector<std::vector<char>> big_maze;
    
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
        
        typename Graph<V, E>::Vertex* pos{nullptr};
        Position(const typename Graph<V, E>::Vertex* v) : pos{const_cast<typename Graph<V, E>::Vertex*>(v)} {}
    
    };
    
    class Path : public Graph<V,E>::Edge
    {
        private:
        typename Graph<V,E>::Edge* edge{nullptr};
        Path(const typename Graph<V,E>::Edge* e) : edge{const_cast<typename Graph<V,E>::Edge*>(e)} {}
    
    };

        void createMaze()
        {
            //std::vector<int> Grid_choices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // can be inlined for dynamics
            //std::vector<int> wall_choices = {0, 1, 2, 3, 4, 7, 8, 11, 12, 13, 14, 15}; // utilized in switch
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
                            big_maze[block_row * size + i][block_col * size + j] = grid[i][j];
                            if(grid[i][j] == ' ')
                            {
                               this->insert_vertex(big_maze[block_row * size + i][block_col * size + j] = grid[i][j]);// here
                            }
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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
                    big_maze.at(random_choice).at(random_choice2) = 'A';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                }
                break;
                case 15 :
                {
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, big_size - 1);
                    int random_choice2 = distrib(engine);
                    big_maze.at(random_choice).at(random_choice2) = 'A';
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

        }
    

};


using namespace std;

int main()
{
    maze<char, int> game;

    game.createMaze();

    game.output();
}