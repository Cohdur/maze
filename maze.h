#include<vector>
#include<iostream>
#include<ctime>
#include<random>
#include<map> //no longer involved in this file DELETE IN FINAL VERSION
#include<list>
#include<memory>


using namespace std; // delete after testing 

//template<typename V,typename E>
class maze //: public Graph<V, E> // char = character/ board & int is edge weight
{
    const static int size = 4;
    const static int big_size = size * 4;

    int StartIndexRow = -1;
    int StartIndexCol =  -1;

    int EndIndexRow = -1;
    int endIndexCol =  -1;
    std::vector<std::vector<char>> big_maze; 
    
    public : 
    // changes these to hold vertex or utilize to add value to vertex for edge weight
    // simply assign a pointer to each one per vertex as created in class then assign the open and close as start end
    // each weight is 1 that way from start to end each possible edge is tested with arthimetic math +1 per vertex
    // output the path at the end if found per move update
    // DIRECTED 
    maze() {};
    std::vector<std::vector<char>> grid
    {
        {'+', '+', '+', '+'},
        {'+', ' ', ' ', '+'},
        {'+', ' ', ' ', '+'},
        {'+', '+', '+', '+'}
    };


    bool condition = false;
        // Unless there is a cleaner way simple accessor functions for now to be used in solver class
        int getStartIndexRow()
        {
            return StartIndexRow;
        }
        int getStartIndexCol()
        {
            return StartIndexCol;
        }
        int getEndIndexRow()
        {
            return EndIndexRow;
        }
        int getEndIndexCol()
        {
            return endIndexCol;
        }
        const std::vector<std::vector<char>>& getMaze() const
        {
            return big_maze;
        }
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
            // most likely delete in the end not being used. 
             StartIndexRow = random_choice;
             endIndexCol = random_choice;

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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                    
                }
                break;
                case 1 :
                {

                    std::vector<int> wall_choices{0, big_size - 1}; // can create one local variable up top for more professional look 
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                    
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                 
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                 
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                 
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                 
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                 
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
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
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
                }
                break;
                case 15 :
                {
                
                     std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, 1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice).at(random_choice2 + 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 + 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'H') break;
                        else 
                        big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice).at(random_choice2 - 1) != 'H' 
                    && big_maze.at(random_choice).at(random_choice2 - 1) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 - 1) == 'H') break;
                        else 
                       big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                        
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while(big_maze.at(random_choice2 + 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 + 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while(big_maze.at(random_choice2 - 1).at(random_choice) != 'O' 
                    && big_maze.at(random_choice2 - 1).at(random_choice) != ' ')
                    {
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == ' ' 
                        || big_maze.at(random_choice).at(random_choice2 + 1) == 'O') break;
                        else 
                       big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                                                
                }
                break;
                default :
                std::cout << "Maze generator operation didn't work " << std::endl;
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

        }
    

};

