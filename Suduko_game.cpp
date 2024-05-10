#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>

using namespace std;

bool is_safe_to_put_value(vector<vector<int> >& grid, int row, int col, int val) 
{
    for (int i = 0; i < 9; i++) 
    {
        // checking row and column to see if it is safe to put the value
        if (grid[row][i] == val || grid[i][col] == val ) 
        {
            return false;
        }
        // checking small 3*3 grid if it is safe to put the value
        if( grid[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val)
        {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<int> >& grid) //Used call by reference to get grid by reference instead of getting a copy
{
    for (int row = 0; row < 9; row++) 
    {
        for (int col = 0; col < 9; col++) 
        {
            if (grid[row][col] == 0) 
            {
                for (int value = 1; value <= 9; value++) 
                {
                    if (is_safe_to_put_value(grid, row, col, value)) 
                    {
                        grid[row][col] = value;
                        if (solve(grid)) 
                        {
                            return true;
                        } 
                        else 
                        {
                            // Backtracking
                            grid[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void need_hint(vector<vector<int> >& grid, vector<vector<int> >& board) 
{
    int r, c;
    cout << "Enter the row you want to see hint(0 to 8)" << endl;
    cin >> r;
    cout << "Enter the column you want to see hint(0 to 8)" << endl;
    cin >> c;
    for (int i = 1; i < 9; i++) 
    {
        for (int j = 1; j < 9; j++) 
        {
            if (i == r && j == c) 
            {
                // the position which needs help is given the values from correct grid
                board[i][j]=grid[i][j];
                cout << board[i][j] << " ";
            } else 
            {
                // in rest cases all other values are printed as it is 
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout<<"******************"<<endl;
}

int main() 
{
    int life_line = 3;
    int hint = 3;
    vector<vector<int> > board(9, vector<int>(9, 0));
    vector<vector<int> > grid(9, vector<int>(9, 0));
    cout << "First You need to make the Sudoku Board" << endl;
    sleep(2);
    cout << "Enter the numbers as in the board and 0 for blank spaces" << endl;
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            cout << "Enter the number for row " << i + 1 << " and column " << j + 1 << endl;
            cin >> board[i][j];
            grid[i][j] = board[i][j];
        }
    }

    cout << "Game starts in 3" << endl;
    sleep(2);
    cout << "2" << endl;
    sleep(1);
    cout << "1" << endl;
    sleep(1);
    cout << "GO!!" << endl;
    
    if(solve(grid))
    {
    char Exit = '0';
    int t1 = time(NULL);                // we start the time for the game 
    while (Exit != 'X' && life_line > 0) 
    {
        int no_of_zeroes = 0;         // this will help us to check the end of game if no_of_zeroes=0 -> game ends
        for (int row = 0; row < 9; row++) 
        {
            for (int col = 0; col < 9; col++) 
            {
                if (board[row][col] == 0) 
                {
                    no_of_zeroes++;
                }
            }
        }
        if (no_of_zeroes == 0) 
        {
            cout << "Congratulations! You have solved the Sudoku!" << endl;
            break;
        }
        for (int row = 0; row < 9; row++) 
        {
            for (int col = 0; col < 9; col++) 
            {
                cout << board[row][col] << " ";
            }
            cout << endl;
        }
        int x, y, number;
        cout << "Enter the row you want to add number" << endl;
        cin >> x;
        cout << "Enter the column you want to add number" << endl;
        cin >> y;
        cout << "Enter the number you want to add" << endl;
        cin >> number;
        if (board[x][y] == 0) 
        {
            if (number == grid[x][y])
            {
                board[x][y] = number;
                cout << "Correct number added!" << endl;
                
            } 
            else 
            {
                cout << "Sorry! Incorrect number" << endl;
                cout << "Lifeline left: " << life_line-- << endl;
                cout << "Hint Left: " << hint << endl;
                char p;
                cout << "Want to use hint? Enter 1. Enter X to Exit or 0 to continue" << endl;
                cin >> p;
                if (p == '1') 
                {
                    need_hint(grid, board);
                    hint--;
                } else if (p == 'X') 
                {
                    Exit = 'X';
                }
                else if(p=='0')
                {
                    continue;
                }
            }
        } 
        else 
        {
            cout << "Cell already filled!" << endl;
        }
    }
    
    
    int t2 = time(NULL);         //end time is noted 
    int time = t2 - t1;          //Net time needed is difference of start and end time
    int sec = time % 60;          
    int min = time / 60;         //the time which we monitered is in second so convert it to min
    cout << "Time taken to solve: " << min << " min " << sec << " sec" << endl;
    }
    else
    {
        cout<<"The Suduku Question entered cant be solved";
    }
    return 0;
}