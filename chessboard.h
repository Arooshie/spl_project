#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include "chesspiece.h"

struct Square
{
    int file;             // alphabet (Column)
    int rank;             // number (Row)
    bool occupied;        // check if a piece is on it
    Chesspiece *occupant; // check which chesspiece is here
};

class Chessboard
{
private:
    Square chessboard[8][8];

public:
    void setup(); // initialize squares
    bool hasOccupant(int file, int rank);
    Chesspiece *getOccupantInfo(int file, int rank);
    Square &getSquare(int file, int rank);
    void fillBoard(); // fill board with chesspieces
};

#endif