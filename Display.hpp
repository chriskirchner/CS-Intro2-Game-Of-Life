/*
 * =====================================================================================
 *
 *       Filename:  Display.hpp
 *
 *    Description:  class specification file for Gol
 *
 *        Version:  1.0
 *        Created:  04/04/15 14:31:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Gol.hpp"

class Display
{
    public:
        static const int XMARGIN = 10;
        static const int YMARGIN = 10;
        void showDisplay(cell**);
        cell **buildGrid(int**, int);
        cell **moveDisplay(cell**,char);
        char getOption();
        void showMenuBar();
        void showPatternOptions();
        void showMoveOptions();
        void showIncrementOptions();
        void showHelp();
};

#endif
