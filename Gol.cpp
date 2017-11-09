/*
 * =====================================================================================
 *
 *       Filename:  gol.cpp
 *
 *    Description:  class implementation file for Gol (Game of Life) containing game
 *                  logic for cells on an "infinite" cell plate (grid)
 *
 *        Version:  1.0
 *        Created:  04/04/15 01:49:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include "Gol.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  nextGeneration
 *  Description:  increments cell cycle generation using game of life rules
 *   Parameters:  grid of cells
 * =====================================================================================
 */

cell **Gol::nextGeneration(cell **grid)
{
    //temporary grid
    cell **temp = new cell*[40+2*XMARGIN];
    for (int i=0; i<40+2*XMARGIN; i++){
        temp[i] = new cell[20+2*YMARGIN];
    }

    //collect cell neighbors and determine fate of empty or full cells
    for (int i=1; i<40+2*XMARGIN-1; i++){
        for (int j=1; j<20+2*YMARGIN-1; j++){
            int neighbors = countNeighbors(grid, i, j); 
            if (grid[i][j] == empty && neighbors == 3){
                temp[i][j] = full;
            }
            else if (grid[i][j] == full && 
                    (neighbors == 2 || neighbors == 3)){
                temp[i][j] = full;
            }
        }
    }
    
    //clear grid margin not affecting pattern movement on borders
    if (!isBorderCell(temp)){
        clearBorder(temp); 
    }

    return temp;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  countNeighbors
 *  Description:  counts neighboring cells 
 *   Parameters:  cell grid and center cell's position
 * =====================================================================================
 */

int Gol::countNeighbors(cell **grid, int xPos, int yPos)
{
    int neighbors = 0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if (i == 1 && j == 1){
                continue;
            }
            else if (grid[xPos+i-1][yPos+j-1] == full){
                neighbors += 1;
            }
        }
    }
    return neighbors;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isBorderCell
 *  Description:  returns true when a full cell bordering the visible display is found 
 *   Parameters:  cell grid
 * =====================================================================================
 */

bool Gol::isBorderCell(cell **grid)
{
    bool borderCell = false;
    for (int y=YMARGIN; y<20+YMARGIN; y++){
        if (grid[XMARGIN-1][y] == full){
            borderCell = true;
        }
        else if (grid[XMARGIN+40][y] == full){
            borderCell = true;
        }
    }
    for (int x=XMARGIN; x<40+XMARGIN; x++){
        if (grid[x][YMARGIN-1] == full){
            borderCell = true;
        }
        else if (grid[x][YMARGIN+20] == full){
            borderCell = true;
        }
    }
    return borderCell; 
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  clearBorder
 *  Description:  clears the border/margin of the grid surrounding visible display
 *   Parameters:  cell grid
 * =====================================================================================
 */

void Gol::clearBorder(cell **grid)
{
    for (int x=0; x<XMARGIN; x++){
        for (int y=0; y<20+2*YMARGIN; y++){
            grid[x][y] = empty;
        }
    }
    for (int x=40+XMARGIN; x<40+2*XMARGIN-1; x++){
        for (int y=0; y<20+2*YMARGIN; y++){
            grid[x][y] = empty;
        }
    }
    for (int y=0; y<YMARGIN; y++){
        for (int x=0; x<40+2*XMARGIN; x++){
            grid[x][y] = empty;
        }
    }
    for (int y=20+YMARGIN; y<20+2*YMARGIN-1; y++){
        for (int x=0; x<40+2*XMARGIN; x++){
            grid[x][y] = empty;
        }
    }
    
}




