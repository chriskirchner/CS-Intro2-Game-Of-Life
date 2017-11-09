/*
 * =====================================================================================
 *
 *       Filename:  gol.hpp
 *
 *    Description:  class specification file for Gol (Game of Life)
 *
 *        Version:  1.0
 *        Created:  04/04/15 02:38:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Kirchner (CK), kirchnch@onid.oregonstate.edu
 *   Organization:  OSU
 *
 * =====================================================================================
 */

#ifndef GOL_HPP
#define GOL_HPP

enum cell {empty, full};

class Gol
{
    public:
        static const int XMARGIN = 10;
        static const int YMARGIN = 10;
        cell **nextGeneration(cell**);
        int countNeighbors(cell**,int,int);
        bool isBorderCell(cell**);
        void clearBorder(cell**);
};

#endif
