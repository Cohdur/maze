#include<vector>
#include<iostream>
#include<ctime>
#include<random>
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
        bool isValid(const std::vector<std::vector<char>>& big_maze, int row, int col) const
        {
            if(row == 1 || row == 15 && col == 1 || col == 15)
            {
               return true;
            }
            // maybe use a throw exception for more detail in the future 
            return false;
                   
        }
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
            
            for(int i = 0; i < big_size; i++)
            {
                for(int j = 0; j < big_size; j++)
                {
                    if(big_maze.at(random_choice).at(random_choice2) == '+')
                    {
                        if(big_maze.at(random_choice - 1).at(random_choice2) == '+')
                        {
                            big_maze.at(random_choice - 1).at(random_choice2) = ' ';
                        }
                        if(big_maze.at(random_choice + 1).at(random_choice2) == '+')
                        {
                            big_maze.at(random_choice + 1).at(random_choice2) = ' ';
                        }
                        if(big_maze.at(random_choice).at(random_choice2 - 1) == '+')
                        {
                            big_maze.at(random_choice).at(random_choice2 - 1) = ' ';
                        }
                        if(big_maze.at(random_choice).at(random_choice2 + 1) == '+')
                        {
                            big_maze.at(random_choice).at(random_choice2 + 1) = ' ';
                        }
                    }
                    else if(big_maze.at(random_choice2).at(random_choice) == '+')
                    {
                        if(big_maze.at(random_choice2 - 1).at(random_choice) == '+')
                        {
                            big_maze.at(random_choice2 - 1).at(random_choice) = ' ';
                        }
                        if(big_maze.at(random_choice2 + 1).at(random_choice) == '+')
                        {
                            big_maze.at(random_choice2 + 1).at(random_choice) = ' ';
                        }
                        if(big_maze.at(random_choice2).at(random_choice - 1) == '+')
                        {
                            big_maze.at(random_choice2).at(random_choice - 1) = ' ';
                        }
                        if(big_maze.at(random_choice2).at(random_choice + 1) == '+')
                        {
                            big_maze.at(random_choice2).at(random_choice + 1) = ' ';
                        }
                    }
                    else if(big_maze.at(random_choice2).at(random_choice) == ' ' 
                    || big_maze.at(random_choice).at(random_choice2) == ' ')
                    {
                        while(big_maze.at(random_choice).at(random_choice2) != '+' 
                        || big_maze.at(random_choice2).at(random_choice) != '+')
                        {
                            random_choice = distrib(engine);
                            random_choice2 = distrib(engine);
                        }
                    }
                }
            }
            
        }
        void changeMaze(int row, int col, char value)
        {
            big_maze.at(row).at(col) = value;
        }
        void createMaze()
        {

            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<> distrib(1, big_size - 1); //changed lower bound to 1 and upper bound to - 2 instead of - 1
            
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
                
                /*
                case 0 : 
                {
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(1, big_size - 1);
                    int random_choice2 = distrib(engine);

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 1)
                big_maze.at(random_choice2).at(random_choice) = 'H';
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice2).at(random_choice) != 'H' )
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        
                        random_choice++;
                        big_maze.at(random_choice).at(random_choice2) = ' '; // adding one to both 
                        
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        
                        random_choice--;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                         
                    if(random_choice2 == 1)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice2).at(random_choice) != 'O' )
                    {
                        if(random_choice + 1 == 16) break;
                     
                        random_choice++;
                        //random_choice2++;
                        big_maze.at(random_choice2).at(random_choice) = ' ';

                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice2).at(random_choice) != 'O' )
                    {
                        if(random_choice - 1 == 0) break;
                        else
                        
                        random_choice--;
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }

                    EndIndexRow = random_choice2;
                    
                }
                break;
                */
                case 1 :
                {

                    std::vector<int> wall_choices{0, big_size - 1}; // can create one local variable up top for optimization
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0,1);
                    int random_choice2 = wall_choices[distrib(engine)];

                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break; // this might work out as they move at the same rate
                        else 
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                        //random_choice++; 
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H'
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else 
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                   
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
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        cout << isValid(big_maze, random_choice, random_choice2) << endl;
                        if(random_choice2 + 1 == 15) break;
                        else 
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else 
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else 
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else 
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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
                    
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        
                        if(random_choice2 + 1 == 15) break;
                        else 
                            random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    
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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else 
                            random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                       
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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--;
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    
                
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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    
                
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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    

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

                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else
                        random_choice2++; 
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else
                        random_choice2--; 
                       big_maze.at(random_choice).at(random_choice2) = ' ';
                       big_maze.at(random_choice2).at(random_choice) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                     
                
                    EndIndexRow = random_choice2;
                                                
                }
                break;
                /* possibly try test running this 
                case 15 :
                {
                
                std::vector<int> wall_choices{0, big_size - 1};
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<> distrib(0, 1);
                    int random_choice2 = wall_choices[distrib(engine)];
                    
                    big_maze.at(random_choice2).at(random_choice) = 'H';
                    big_maze.at(random_choice).at(random_choice2) = 'O';
                    
                    if(random_choice2 == 0)
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 + 1 == 15) break;
                        else 
                        random_choice2++;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                    }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                    while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice).at(random_choice2) != 'H' 
                    || big_maze.at(random_choice2).at(random_choice) != 'O')
                    {
                        if(random_choice2 - 1 == 0) break;
                        else 
                        random_choice2--;
                        big_maze.at(random_choice).at(random_choice2) = ' ';
                    }
                    }
                    
                    StartIndexCol = random_choice2;
                    
                    if(random_choice2 == 0)
                    {
                        while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice2).at(random_choice) != 'O' 
                        && big_maze.at(random_choice2 ).at(random_choice) != ' ')
                        {
                            if(random_choice2 + 1 == 15) break;
                            else
                            random_choice2++; 
                            big_maze.at(random_choice2).at(random_choice) = ' ';
                        }
                    } 
                    else if(random_choice2 == (big_size - 1))
                    {
                        while((isValid(big_maze, random_choice, random_choice2)) && big_maze.at(random_choice2).at(random_choice) != 'O' 
                        && big_maze.at(random_choice2).at(random_choice) != ' ')
                        {
                            if(random_choice2 - 1 == 0) break;
                            else
                        random_choice2--; 
                        big_maze.at(random_choice2).at(random_choice) = ' ';
                        
                    }
                }
                
                EndIndexRow = random_choice2;
                
            }
            break;
                */
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

