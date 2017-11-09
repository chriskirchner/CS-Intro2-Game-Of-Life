/*
 * =====================================================================================
 *
 *       Filename:  Menu.cpp
 *
 *    Description:  main program file for Game of Life interfacing Display and Gol 
 *                  classes to user control
 *
 *        Version:  1.0
 *        Created:  04/05/15 02:42:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#include    "Display.hpp"
#include    "Gol.hpp"
#include    <iostream>
#include    <cstdlib>
#include    <ncurses.h>
using namespace std;

const int XMARGIN = 10;
const int YMARGIN = 10;

int **getOscillator();
int **getGlider();
int **buildArray(int,int);

//provides hard-coded array for oscillator pattern
int **getOscillator(){
    int **oscillator = buildArray(3,2);
    int pattern[3][2] = {{0,0},{1,0},{2,0}};
    for (int i=0; i<3; i++){
        for (int j=0; j<2; j++){
            oscillator[i][j] = pattern[i][j];
        }
    }
    return oscillator;
}

//provides hard-coded array for glider pattern
int **getGlider(){
    int **glider = buildArray(5,2);
    int pattern[5][2] = {{1,0},{2,1},{0,2},{1,2},{2,2}};
    for (int i=0; i<5; i++){
        for (int j=0; j<2; j++){
            glider[i][j] = pattern[i][j];
        }
    }
    return glider;
}

//provides hard-coded array for glider gun pattern
int **getCannon(){
    int **cannon = buildArray(36,2);
    int pattern[36][2] = {{24,0},{22,1},{24,1},{12,2},{13,2},{20,2},{21,2},{34,2},
                          {35,2},{11,3},{15,3},{20,3},{21,3},{34,3},{35,3},{0,4},
                          {1,4},{10,4},{16,4},{20,4},{21,4},{0,5},{1,5},{10,5},{14,5},
                          {16,5},{17,5},{22,5},{24,5},{10,6},{16,6},{24,6},{11,7},
                          {15,7},{12,8},{13,8}};
    for (int i=0; i<36; i++){
        for (int j=0; j<2; j++){
            cannon[i][j] = pattern[i][j];
        }
    }
    return cannon;
}

//builds array
int **buildArray(int rows, int columns){
    int **array = new int*[rows];
    for (int i=0; i<rows; i++){
        array[i] = new int[columns];
    }
    return array;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  main function for game of life
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    Display display;
    Gol gol;
    char userOption;

    int **pattern = NULL;
    int patternSize = 0;
    cell **grid = display.buildGrid(pattern, patternSize);

    do {
        display.showDisplay(grid);
        userOption = display.getOption();

        //provides pattern option and pattern
        if (userOption == 'p' || userOption == 'P'){
            bool gotOption = false;
            do {
                display.showDisplay(grid);
                display.showPatternOptions();
                userOption = display.getOption();
                if (userOption == 'o' || userOption == 'O'){
                    pattern = getOscillator();
                    patternSize = 3;
                    gotOption = true;
                } 
                else if (userOption == 'g' || userOption == 'G'){
                    pattern = getGlider();
                    patternSize = 5;
                    gotOption = true;
                }
                else if (userOption == 'c' || userOption == 'C'){
                    pattern = getCannon();
                    patternSize = 36;
                    gotOption = true;
                }
                grid = display.buildGrid(pattern,patternSize);
            }while(gotOption != true && userOption != 'e' && userOption != 'E');
        }

        //allows user movement of internal grid
        else if (userOption == 'm' || userOption == 'M'){
            do {
                display.showDisplay(grid); 
                display.showMoveOptions();
                userOption = display.getOption();
                if (userOption == 'j' || userOption == 'k' ||
                    userOption == 'h' || userOption == 'l'){
                    grid = display.moveDisplay(grid, userOption);
                }
            }while(userOption != 'e' && userOption != 'E');
        }

        //allows user to increment game of life generations
        else if (userOption == 'i' || userOption == 'I'){
            do {
                display.showDisplay(grid);
                display.showIncrementOptions();
                userOption = display.getOption();
                //forwards to next generation
                if (userOption == 'f' || userOption == 'F'){
                    grid = gol.nextGeneration(grid);
                    display.showDisplay(grid);
                    display.showIncrementOptions();
                }
                else if (userOption == 'p' || userOption == 'P'){
                    //allows user continuous play and stop controls
                   do{ 
                        grid = gol.nextGeneration(grid);
                        display.showDisplay(grid);
                        display.showIncrementOptions();
                        initscr();
                        cbreak();
                        timeout(100);     // wait 500ms for key press
                        userOption = getch();
                        nocbreak();
                        endwin();
                    }while(userOption != 's' && userOption != 'S' &&
                            userOption != 'e' && userOption != 'E');
                }
            }while (userOption != 'e' && userOption != 'E');
        }

        //shows help 
        else if (userOption == 'h' || userOption == 'H'){
            display.showDisplay(grid);
            display.showHelp();
            display.getOption();
        }

    }while(userOption != 'q');

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

