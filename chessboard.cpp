#include "chessboard.h"

void Chessboard::setup()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chessboard[i][j] = {i, j, false, nullptr};
        }
    }
}

bool Chessboard::hasOccupant(int file, int rank)
{
    if (file < 0 || file > 8 || rank < 0 || rank > 8)
    {
        throw std::out_of_range("Invalid board position");
    }

    return chessboard[file][rank].occupied;
}

Chesspiece *Chessboard::getOccupantInfo(int file, int rank)
{
    if (file < 0 || file > 8 || rank < 0 || rank > 8)
    {
        throw std::out_of_range("Invalid board position");
    }

    else if (chessboard[file][rank].occupant == nullptr)
    {
        throw std::invalid_argument("Square is empty");
    }

    return chessboard[file][rank].occupant;
}

Square &Chessboard::getSquare(int file, int rank)
{
    if (file >= 0 && file < 8 && rank >= 0 && rank < 8)
    {
        return chessboard[file][rank];
    }
    else
    {
        throw std::out_of_range("Invalid board position");
    }
}

void Chessboard::fillBoard()
{
    // Fill pawns
    for (int i = 0; i < 8; i++)
    {
        chessboard[i][1].occupant = new Pawn("pawn", "white", i, 1, &chessboard[i][1]); // rank 2
        chessboard[i][1].occupied = true;

        chessboard[i][6].occupant = new Pawn("pawn", "black", i, 6, &chessboard[i][6]); // rank 7
        chessboard[i][6].occupied = true;
    }

    // Fill kings
    chessboard[4][0].occupant = new King("king", "white", 4, 0, &chessboard[4][0]); // e1
    chessboard[4][0].occupied = true;

    chessboard[4][7].occupant = new King("king", "black", 4, 7, &chessboard[4][7]); // e8
    chessboard[4][7].occupied = true;

    // Fill queens
    chessboard[3][0].occupant = new Queen("queen", "white", 3, 0, &chessboard[3][0]); // d1
    chessboard[3][0].occupied = true;

    chessboard[3][7].occupant = new Queen("queen", "black", 3, 7, &chessboard[3][7]); // d8
    chessboard[3][7].occupied = true;

    // Fill bishops
    chessboard[2][0].occupant = new Bishop("bishop", "white", 2, 0, &chessboard[2][0]); // c1
    chessboard[2][0].occupied = true;

    chessboard[5][0].occupant = new Bishop("bishop", "white", 5, 0, &chessboard[5][0]); // f1
    chessboard[5][0].occupied = true;

    chessboard[2][7].occupant = new Bishop("bishop", "black", 2, 7, &chessboard[2][7]); // c8
    chessboard[2][7].occupied = true;

    chessboard[5][7].occupant = new Bishop("bishop", "black", 5, 7, &chessboard[5][7]); // f8
    chessboard[5][7].occupied = true;

    // Fill knights
    chessboard[1][0].occupant = new Knight("knight", "white", 1, 0, &chessboard[1][0]); // b1
    chessboard[1][0].occupied = true;

    chessboard[6][0].occupant = new Knight("knight", "white", 6, 0, &chessboard[6][0]); // g1
    chessboard[6][0].occupied = true;

    chessboard[1][7].occupant = new Knight("knight", "black", 1, 7, &chessboard[1][7]); // b8
    chessboard[1][7].occupied = true;

    chessboard[6][7].occupant = new Knight("knight", "black", 6, 7, &chessboard[6][7]); // g8
    chessboard[6][7].occupied = true;

    // Fill rooks
    chessboard[0][0].occupant = new Rook("rook", "white", 0, 0, &chessboard[0][0]); // a1
    chessboard[0][0].occupied = true;

    chessboard[7][0].occupant = new Rook("rook", "white", 7, 0, &chessboard[7][0]); // h1
    chessboard[7][0].occupied = true;

    chessboard[0][7].occupant = new Rook("rook", "black", 0, 7, &chessboard[0][7]); // a8
    chessboard[0][7].occupied = true;

    chessboard[7][7].occupant = new Rook("rook", "black", 7, 7, &chessboard[7][7]); // h8
    chessboard[7][7].occupied = true;
}