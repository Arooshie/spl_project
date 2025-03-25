#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "chessboard.h"
#include "chesspiece.h"

const int board_size = 8;
const int square_size = 80;
const int board_pixel_size = board_size * square_size;
const int hud_width = 200;
const int window_width = board_pixel_size + hud_width;
const int window_height = board_pixel_size;

const SDL_Color LIGHT_SQUARE = {235, 235, 208, 255};
const SDL_Color DARK_SQUARE = {119, 148, 85, 255};

// Translate coordinates board to screen
SDL_Point translateCoordinates(int file, int rank)
{
    return {file * square_size, (7 - rank) * square_size};
}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (!texture)
        std::cerr << "Failed to load image: " << filename << " SDL_Error: " << SDL_GetError() << std::endl;
    return texture;
}

void drawSquare(SDL_Renderer *renderer, int x, int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, square_size, square_size};
    SDL_RenderFillRect(renderer, &rect);
}

void drawChessPiece(SDL_Renderer *renderer, SDL_Texture *texture, int file, int rank)
{
    SDL_Point pos = translateCoordinates(file, rank);
    SDL_Rect dst_rect = {pos.x, pos.y, square_size, square_size};
    SDL_RenderCopy(renderer, texture, nullptr, &dst_rect);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG || TTF_Init() == -1)
    {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          window_width, window_height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("Arial.ttf", 36);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *white_pawn_texture = loadTexture("images/white_pawn.png", renderer);
    SDL_Texture *black_pawn_texture = loadTexture("images/black_pawn.png", renderer);
    SDL_Texture *white_rook_texture = loadTexture("images/white_rook.png", renderer);
    SDL_Texture *black_rook_texture = loadTexture("images/black_rook.png", renderer);
    SDL_Texture *white_knight_texture = loadTexture("images/white_knight.png", renderer);
    SDL_Texture *black_knight_texture = loadTexture("images/black_knight.png", renderer);
    SDL_Texture *white_bishop_texture = loadTexture("images/white_bishop.png", renderer);
    SDL_Texture *black_bishop_texture = loadTexture("images/black_bishop.png", renderer);
    SDL_Texture *white_queen_texture = loadTexture("images/white_queen.png", renderer);
    SDL_Texture *black_queen_texture = loadTexture("images/black_queen.png", renderer);
    SDL_Texture *white_king_texture = loadTexture("images/white_king.png", renderer);
    SDL_Texture *black_king_texture = loadTexture("images/black_king.png", renderer);

    if (!white_pawn_texture || !black_pawn_texture || !white_rook_texture || !black_rook_texture ||
        !white_knight_texture || !black_knight_texture || !white_bishop_texture || !black_bishop_texture ||
        !white_queen_texture || !black_queen_texture || !white_king_texture || !black_king_texture)
    {
        std::cerr << "Failed to load one or more textures. Exiting." << std::endl;
        return 1;
    }

    Chessboard board;
    board.setup();
    board.fillBoard();

    bool running = true;
    SDL_Event event;
    Chesspiece *selected_piece = nullptr;
    std::string winner_message = "";
    std::string current_turn = "white";

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && winner_message.empty())
            {
                int mx = event.button.x;
                int my = event.button.y;
                SDL_Point boardPos = {mx / square_size, 7 - (my / square_size)};

                try
                {
                    Square &target_square = board.getSquare(boardPos.x, boardPos.y);

                    if (!selected_piece)
                    {
                        if (target_square.occupied && target_square.occupant->getTeam() == current_turn)
                            selected_piece = target_square.occupant;
                    }

                    else
                    {
                        Chesspiece *target_occupant = target_square.occupant;

                        if (selected_piece->validMove(target_square, board))
                        {
                            if (target_occupant && target_occupant->getName() == "king")
                            {
                                winner_message = selected_piece->getTeam() + " wins!";
                            }
                        }

                        if (winner_message.empty())
                        {
                            current_turn = (current_turn == "white") ? "black" : "white";
                        }

                        else
                        {
                            std::cout << "Illegal move!" << std::endl;
                        }

                        selected_piece = nullptr;
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw board
        for (int file = 0; file < board_size; file++)
        {
            for (int rank = 0; rank < board_size; rank++)
            {
                SDL_Color color = ((file + rank) % 2 == 0) ? DARK_SQUARE : LIGHT_SQUARE;
                drawSquare(renderer, file * square_size, (7 - rank) * square_size, color);
            }
        }

        // Draw pieces
        for (int file = 0; file < board_size; file++)
        {
            for (int rank = 0; rank < board_size; rank++)
            {
                Square &square = board.getSquare(file, rank);
                if (square.occupied && square.occupant)
                {
                    SDL_Texture *texture = nullptr;
                    std::string name = square.occupant->getName();
                    std::string team = square.occupant->getTeam();

                    if (name == "pawn")
                        texture = (team == "white") ? white_pawn_texture : black_pawn_texture;
                    else if (name == "rook")
                        texture = (team == "white") ? white_rook_texture : black_rook_texture;
                    else if (name == "knight")
                        texture = (team == "white") ? white_knight_texture : black_knight_texture;
                    else if (name == "bishop")
                        texture = (team == "white") ? white_bishop_texture : black_bishop_texture;
                    else if (name == "queen")
                        texture = (team == "white") ? white_queen_texture : black_queen_texture;
                    else if (name == "king")
                        texture = (team == "white") ? white_king_texture : black_king_texture;

                    if (texture)
                        drawChessPiece(renderer, texture, file, rank);
                }
            }
        }

        if (!winner_message.empty())
        {
            SDL_Color text_color = {255, 255, 255, 255};
            SDL_Surface *text_surface = TTF_RenderText_Solid(font, winner_message.c_str(), text_color);
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            int texW = 0, texH = 0;
            SDL_QueryTexture(text_texture, NULL, NULL, &texW, &texH);
            SDL_Rect dst_rect = {(window_width - texW) / 2, (window_height - texH) / 2, texW, texH};
            SDL_RenderCopy(renderer, text_texture, NULL, &dst_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }

        SDL_Color hud_color = {255, 255, 255, 255};
        std::string hud_text = "Turn: " + current_turn;

        SDL_Surface *hud_surface = TTF_RenderText_Solid(font, hud_text.c_str(), hud_color);
        SDL_Texture *hud_texture = SDL_CreateTextureFromSurface(renderer, hud_surface);

        int hud_text_w, hud_text_h;
        SDL_QueryTexture(hud_texture, NULL, NULL, &hud_text_w, &hud_text_h);

        SDL_Rect hud_rect = {board_pixel_size + (hud_width - hud_text_w) / 2, 50, hud_text_w, hud_text_h};
        SDL_RenderCopy(renderer, hud_texture, NULL, &hud_rect);

        SDL_FreeSurface(hud_surface);
        SDL_DestroyTexture(hud_texture);

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // grey
        SDL_RenderDrawLine(renderer, board_pixel_size, 0, board_pixel_size, window_height);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(white_pawn_texture);
    SDL_DestroyTexture(black_pawn_texture);
    SDL_DestroyTexture(white_rook_texture);
    SDL_DestroyTexture(black_rook_texture);
    SDL_DestroyTexture(white_knight_texture);
    SDL_DestroyTexture(black_knight_texture);
    SDL_DestroyTexture(white_bishop_texture);
    SDL_DestroyTexture(black_bishop_texture);
    SDL_DestroyTexture(white_queen_texture);
    SDL_DestroyTexture(black_queen_texture);
    SDL_DestroyTexture(white_king_texture);
    SDL_DestroyTexture(black_king_texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
