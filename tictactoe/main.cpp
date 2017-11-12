//
//  main.cpp
//  tictactoe
//
//  Created by Fernando Gomez on 11/11/17.
//  Copyright © 2017 Nando Gomez. All rights reserved.
//

/***********************************************************************
 * Program:
 *    Lesson 08, Tic-Tac-Toe
 * Summary:
 *    This program reads, displays, and writes a Tic-Tac-Toe board
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define SIZE 3
#define B '.'
#define X 'X'
#define O 'O'

bool read(         char board[][SIZE][SIZE], const char* fileName);
bool write(  const char board[][SIZE][SIZE], const char* fileName);
void display(const char board[][SIZE][SIZE]);
bool didWin( const char board[][SIZE][SIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
    char board[SIZE][SIZE][SIZE];
    
    // read the board
    char fileName[256];
    cout << "Enter source filename: ";
    cin  >> fileName;
    if (!read(board, fileName))
    {
        cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
        return 1;
    }
    
    // display the board
    display(board);
    
    // write the board to a file
    cout << "Enter destination filename: ";
    cin  >> fileName;
    if (!write(board, fileName))
    {
        cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
        return 1;
    }
    return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][SIZE][SIZE], const char* fileName)
{
    assert(*fileName);
    
    // open the file
    ifstream fin(fileName);
    if (fin.fail())
        return false;
    
    // read 9 symbols, hopefully they are . X O
    for (int d = 0; d < SIZE; d++)
        for (int r = 0; r < SIZE; r++)
        {
            for (int c = 0; c < SIZE; c++)
            {
                fin >> board[d][r][c];
                assert(!fin.fail());
                assert(board[d][r][c] == X ||
                       board[d][r][c] == O ||
                       board[d][r][c] == B);
            }
        }
    
    
    // close the file
    fin.close();
    return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][SIZE][SIZE], const char* fileName)
{
    assert(fileName[0] != '\0');
    
    // open the file
    ofstream fout(fileName);
    if (fout.fail())
        return false;
    
    // write my 9 symbols
    for (int d = 0; d < SIZE; d++)
    {
        if (d != 0)
            fout << '\n';
        for (int r = 0; r < SIZE; r++)
        {
            for (int c = 0; c < SIZE; c++)
                fout << board[d][r][c] << (c == SIZE - 1 ? '\n' : ' ');
        }
    }
    
    // close it!
    fout.close();
    cout << "File written\n";
    return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][SIZE][SIZE])
{
    
    
    for (int d = 0; d < SIZE; d++)
    {
        if (d)
            cout << endl;
        cout << "Level " << d + 1 << endl;
        // loop through each row
        for (int r = 0; r < SIZE; r++)
        {
            // only the first row is not preceeded with the --+-- magic
            if (r != 0)
                cout << "---+---+---\n";
            
            // now, on each row, do the column stuff
            for (int c = 0; c < SIZE; c++)
            {
                // display a space for the dot
                if (board[d][r][c] == B)
                    cout << "   ";
                else
                    cout << " " << board[d][r][c] << " ";
                
                // end with a | or a newline
                cout << (c == SIZE - 1 ? '\n' : '|');
                
                if (d == SIZE - 1 && c == SIZE - 1 && r == SIZE - 1)
                    cout << endl;
                
            }
        }
    }
    
    // display who won
    if (didWin(board, X))
        cout << "X won!\n";
    if (didWin(board, O))
        cout << "O won!\n";
    
    return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][SIZE][SIZE], char turn)
{
    int d, i, j, row;
    
    // Dimensional check
    for(d = 0; d < SIZE; d++)
    {
        
        // horizontal check
        for(i = 0; i < SIZE; i++)
        {
            for(j = 1; j < SIZE; j++)
            {
                if(board[d][i][0] == turn && board[d][i][0] == board[d][i][j])
                {
                    if(j == SIZE - 1)
                    {
                        return true;
                    }
                }
                else
                    break;
            }
        }
        // vertical check
        for(i = 0; i < SIZE; i++)
        {
            for(j = 1; j < SIZE; j++)
            {
                if(board[d][0][i] == turn && board[d][0][i] == board[d][j][i])
                {
                    if(j == SIZE - 1)
                        return true;
                }
                else
                    break;
            }
        }
        // Diagonal check 1
        for(i = 1; i < SIZE; i++)
        {
            if(board[d][0][0] == turn && board[d][0][0] == board[d][i][i])
            {
                if (i == SIZE - 1)
                    return true;
            }
            else
                break;
        }
        
        // Diagonal check 2
        for(i = SIZE - 1, row = 0; i > -1; i--, row++)
        {
            
            if(board[d][0][SIZE - 1] == turn && board[d][0][SIZE - 1] == board[d][row][i])
            {
                if (i == 0)
                    return true;
            }
            else
                break;
        }
    }
    return false;
}
