/*
 * =====================================================================================
 *
 *       Filename:  display.cpp
 *
 *    Description:  class implementation file for Display (Game of Life)
 *
 *        Version:  1.0
 *        Created:  04/03/15 19:13:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Display.hpp"
#include "Gol.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showDisplay
 *  Description:  prints grid display with menu
 *   Parameters:  grid array 
 * =====================================================================================
 */

void Display::showDisplay(cell **grid)
{
    system("clear");
    cout << endl;
    for (int y=YMARGIN; y<20+YMARGIN; y++){
        for (int x=XMARGIN; x<40+XMARGIN; x++){
            if (grid[x][y] == empty){
                cout << "| ";
            }
            else if (grid[x][y] == full){
                cout << "|O";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
    showMenuBar();
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  moveDisplay
 *  Description:  moves display using character control; prevents display movement at
 *                cell boundaries
 *   Parameters:  display grid, movement
 * =====================================================================================
 */

cell **Display::moveDisplay(cell **grid, char direction)
{

    //temporary grid   
    int xWidth = 40 + 2*XMARGIN;
    int yWidth = 20 + 2*YMARGIN;

    cell **tmpGrid = new cell*[xWidth];
    for (int i=0; i<xWidth; i++){
        tmpGrid[i] = new cell[yWidth];
    }
    for (int y=0; y<yWidth; y++){
        for (int x=0; x<xWidth; x++){
            tmpGrid[x][y] = empty;
        }
    }

    //check for valid display movement when full cell is not compromised
    bool canMove = true; 
    for (int y=0; y<20; y++){
        if (direction == 'h' && grid[XMARGIN][YMARGIN+y]==full){
            canMove = false;
        }
        else if (direction == 'l' && grid[XMARGIN+40-1][YMARGIN+y]==full){
            canMove = false;
        }
    }
    for (int x=0; x<40; x++){
        if (direction == 'k' && grid[XMARGIN+x][YMARGIN]==full){
            canMove = false;
        }
        else if (direction == 'j' && grid[XMARGIN+x][YMARGIN+20-1]==full){
            canMove = false;
        }
    }
    
    //shift temporary grid axis one away from original grid by direction 
    if (canMove){
        for (int x=XMARGIN; x<XMARGIN+40; x++){
            for (int y=YMARGIN; y<YMARGIN+20; y++){
                if (direction == 'h' && x > XMARGIN){
                    tmpGrid[x-1][y] = grid[x][y]; 
                }
                else if (direction == 'l' && x < XMARGIN+39){
                    tmpGrid[x+1][y] = grid[x][y];
                }
                else if (direction == 'k' && y > YMARGIN){
                    tmpGrid[x][y-1] = grid[x][y];
                }
                else if (direction == 'j' && y < YMARGIN+19){
                    tmpGrid[x][y+1] = grid[x][y];
                }
            }
        }
        return tmpGrid;
    }
    return grid; 
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  buildGrid
 *  Description:  builds grid for program start and new patterns
 *   Parameters:  uses pre-built pattern with size to build grid
 * =====================================================================================
 */

cell **Display::buildGrid(int **pattern, int size){
    int xWidth = 40 + 2*XMARGIN;
    int yWidth = 20 + 2*YMARGIN;

    cell **grid = new cell*[xWidth];
    for (int i=0; i<xWidth; i++){
        grid[i] = new cell[yWidth];
    }

    for (int y=0; y<yWidth; y++){
        for (int x=0; x<xWidth; x++){
            grid[x][y] = empty;
        }
    }

    if (pattern != NULL){
        for (int i=0; i<size; i++){
            grid[pattern[i][0]+XMARGIN][pattern[i][1]+YMARGIN] = full;
        }
    }

    return grid;
}

void Display::showMenuBar()
{
    cout << "[P]attern | [M]ove | [I]ncrement | [H]elp | [Q]uit " << endl;
}

void Display::showPatternOptions()
{
    cout << "----------" << endl;
    cout << "[O]scillator" << endl;
    cout << "[G]lider" << endl;
    cout << "[C]annon" << endl;
    cout << "[E]xit" << endl;
}

void Display::showMoveOptions()
{
    cout << "            ------" << endl;
    cout << "            [H] LEFT" << endl;
    cout << "            [J] DOWN" << endl;
    cout << "            [K] UP" << endl;
    cout << "            [L] RIGHT" << endl;
    cout << "            [E] EXIT" << endl;
}

void Display::showIncrementOptions()
{
    cout << "                     -----------" << endl;
    cout << "                     [F]orward" << endl;
    cout << "                     [P]lay" << endl;
    cout << "                     [S]top" << endl;
    cout << "                     [E]xit"<< endl;
}

void Display::showHelp()
{
    cout << "                                   ------" << endl;
    cout << "                                   =)" << endl;
}


//collect user option without line buffering
char Display::getOption()
{
    char option;
    system("stty raw");
    cin >> option;
    system("clear");
    system("stty cooked");
    return option;
}
