#include "chesspiece.h"
#include "chessboard.h"
#include <cmath>

bool Pawn::validMove(Square &space, Chessboard &board)
{
    int direction = (this->getTeam() == "white") ? 1 : -1;
    int start_rank = (this->getTeam() == "white") ? 1 : 6;

    int file_diff = space.file - this->getFile();
    int rank_diff = space.rank - this->getRank();
    Square *current = this->getSpace();

    // Forward one
    if (file_diff == 0 && rank_diff == direction && !space.occupied)
    {
        current->occupant = nullptr;
        current->occupied = false;
        setFile(space.file);
        setRank(space.rank);
        setSpace(space);
        space.occupant = this;
        space.occupied = true;
        return true;
    }

    // Forward two from start
    if (file_diff == 0 && rank_diff == 2 * direction && this->getRank() == start_rank)
    {
        int middle_rank = this->getRank() + direction;
        Square &middle = board.getSquare(this->getFile(), middle_rank);

        if (!space.occupied && !middle.occupied)
        {
            current->occupant = nullptr;
            current->occupied = false;
            setFile(space.file);
            setRank(space.rank);
            setSpace(space);
            space.occupant = this;
            space.occupied = true;
            return true;
        }
    }

    // Diagonal capture
    if (std::abs(file_diff) == 1 && rank_diff == direction && space.occupied &&
        space.occupant->getTeam() != this->getTeam())
    {
        delete space.occupant;
        current->occupant = nullptr;
        current->occupied = false;
        setFile(space.file);
        setRank(space.rank);
        setSpace(space);
        space.occupant = this;
        space.occupied = true;
        return true;
    }

    return false;
}

bool King::validMove(Square &space, Chessboard &board)
{
    int file_diff = abs(space.file - this->getFile());
    int rank_diff = abs(space.rank - this->getRank());

    if ((file_diff <= 1 && rank_diff <= 1) && !(file_diff == 0 && rank_diff == 0))
    {
        if (space.occupied && space.occupant->getTeam() == this->getTeam())
            return false;

        if (space.occupied)
            delete space.occupant;

        Square *current = this->getSpace();
        current->occupant = nullptr;
        current->occupied = false;
        setFile(space.file);
        setRank(space.rank);
        setSpace(space);
        space.occupant = this;
        space.occupied = true;
        return true;
    }

    return false;
}

bool Queen::validMove(Square &space, Chessboard &board)
{
    int file_diff = space.file - this->getFile();
    int rank_diff = space.rank - this->getRank();

    bool is_diagonal = std::abs(file_diff) == std::abs(rank_diff);
    bool is_straight = (file_diff == 0 || rank_diff == 0);

    if (!is_diagonal && !is_straight)
        return false;

    int file_step = (file_diff == 0) ? 0 : (file_diff > 0 ? 1 : -1);
    int rank_step = (rank_diff == 0) ? 0 : (rank_diff > 0 ? 1 : -1);

    int steps = std::max(std::abs(file_diff), std::abs(rank_diff));
    
    for (int i = 1; i < steps; ++i)
    {
        int f = this->getFile() + i * file_step;
        int r = this->getRank() + i * rank_step;
        
        if (board.getSquare(f, r).occupied)
            return false;
    }

    if (space.occupied && space.occupant->getTeam() == this->getTeam())
        return false;

    if (space.occupied)
        delete space.occupant;

    Square *current = this->getSpace();
    current->occupant = nullptr;
    current->occupied = false;
    setFile(space.file);
    setRank(space.rank);
    setSpace(space);
    space.occupant = this;
    space.occupied = true;
    return true;
}

bool Bishop::validMove(Square &space, Chessboard &board)
{
    int file_diff = space.file - this->getFile();
    int rank_diff = space.rank - this->getRank();

    if (std::abs(file_diff) != std::abs(rank_diff))
        return false;

    int file_step = (file_diff > 0) ? 1 : -1;
    int rank_step = (rank_diff > 0) ? 1 : -1;

    for (int i = 1; i < std::abs(file_diff); ++i)
    {
        int f = this->getFile() + i * file_step;
        int r = this->getRank() + i * rank_step;
        if (board.getSquare(f, r).occupied)
            return false;
    }

    if (space.occupied && space.occupant->getTeam() == this->getTeam())
        return false;

    if (space.occupied)
        delete space.occupant;

    Square *current = this->getSpace();
    current->occupant = nullptr;
    current->occupied = false;
    setFile(space.file);
    setRank(space.rank);
    setSpace(space);
    space.occupant = this;
    space.occupied = true;
    return true;
}

bool Knight::validMove(Square &space, Chessboard &board)
{
    int file_diff = abs(space.file - this->getFile());
    int rank_diff = abs(space.rank - this->getRank());

    if (!((file_diff == 2 && rank_diff == 1) || (file_diff == 1 && rank_diff == 2)))
        return false;

    if (space.occupied && space.occupant->getTeam() == this->getTeam())
        return false;

    if (space.occupied)
        delete space.occupant;

    Square *current = this->getSpace();
    current->occupant = nullptr;
    current->occupied = false;
    setFile(space.file);
    setRank(space.rank);
    setSpace(space);
    space.occupant = this;
    space.occupied = true;
    return true;
}

bool Rook::validMove(Square &space, Chessboard &board)
{
    int file_diff = space.file - this->getFile();
    int rank_diff = space.rank - this->getRank();

    if (file_diff != 0 && rank_diff != 0)
        return false;

    int file_step = (file_diff == 0) ? 0 : (file_diff > 0 ? 1 : -1);
    int rank_step = (rank_diff == 0) ? 0 : (rank_diff > 0 ? 1 : -1);

    int steps = std::max(std::abs(file_diff), std::abs(rank_diff));
    for (int i = 1; i < steps; ++i)
    {
        int f = this->getFile() + i * file_step;
        int r = this->getRank() + i * rank_step;
        if (board.getSquare(f, r).occupied)
            return false;
    }

    if (space.occupied && space.occupant->getTeam() == this->getTeam())
        return false;

    if (space.occupied)
        delete space.occupant;

    Square *current = this->getSpace();
    current->occupant = nullptr;
    current->occupied = false;
    setFile(space.file);
    setRank(space.rank);
    setSpace(space);
    space.occupant = this;
    space.occupied = true;
    return true;
}
