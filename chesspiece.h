#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

struct Square;
class Chessboard;

class Chesspiece
{
protected:
    std::string name;
    std::string team;
    int file_position; // Column
    int rank_position; // Row
    Square *occupied_space;

public:
    Chesspiece(const std::string NAME, std::string TEAM, int FILE, int RANK, Square *SPACE)
        : name(NAME), team(TEAM), file_position(FILE),
          rank_position(static_cast<int>(RANK)), occupied_space(SPACE) {}

    virtual ~Chesspiece() {}
    std::string getName() const { return name; }
    unsigned getFile() { return file_position; }
    unsigned getRank() { return rank_position; }
    Square *getSpace() { return occupied_space; }
    std::string getTeam() { return team; }

    void setFile(unsigned int file) { file_position = file; }
    void setRank(unsigned int rank) { rank_position = rank; }
    void setSpace(Square &space) { occupied_space = &space; }
    
    virtual bool validMove(Square &space, Chessboard &board) = 0;

    std::string status() const
    {
        return "Chesspiece " + name + " is located at " + static_cast<char>(file_position) + std::to_string(rank_position) + "\n";
    }
};

class Pawn : public Chesspiece
{
public:
    Pawn(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

class King : public Chesspiece
{
public:
    King(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

class Queen : public Chesspiece
{
public:
    Queen(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

class Bishop : public Chesspiece
{
public:
    Bishop(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

class Knight : public Chesspiece
{
public:
    Knight(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

class Rook : public Chesspiece
{
public:
    Rook(const std::string NAME, std::string TEAM, unsigned int FILE, int RANK, Square *SPACE) : Chesspiece(NAME, TEAM, FILE, RANK, SPACE) {}
    bool validMove(Square &space, Chessboard &board) override;
};

#endif