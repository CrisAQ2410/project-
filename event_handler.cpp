#include "event_handler.h"
#include "mouse_handler.h"
#include "restart.h"

void handleEvents(SDL_Event &e, bool &quit, bool &menuDisplayed, bool &isBallReleased, Ball &ball, Obstacle obstacles[], Hole &hole, int &strokes, int &highestScore, int &score, bool &win, SDL_Renderer* renderer) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (menuDisplayed && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            menuDisplayed = false;
            isBallReleased = true;
            startTime = high_resolution_clock::now();
        } 
        handleMouseEvents(e);
        if (!menuDisplayed && !win && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if (mouseX >= WINDOW_WIDTH - 100 && mouseX <= WINDOW_WIDTH - 20 && mouseY >= 10 && mouseY <= 50) {
                resetGame(ball, obstacles, hole, score, strokes, highestScore, win, renderer);
                strokes --;
                if (highestScore > 0) highestScore -= 100;
            }
        }
        if (!menuDisplayed && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if (mouseX >= WINDOW_WIDTH - 50 && mouseX <= WINDOW_WIDTH - 10 && mouseY >= 10 && mouseY <= 50) {
                quit = true;
            }
            if (mouseX >= WINDOW_WIDTH - 160 && mouseX <= WINDOW_WIDTH - 100 && mouseY >= 10 && mouseY <= 50) {
                menuDisplayed = true;
                resetGame(ball, obstacles, hole, score, strokes, highestScore, win, renderer);
                startTime = high_resolution_clock::now();
                highestScore = 0;
                extraTimeToAdd = duration<double>(0);
                extraTimeAdded = false;
            }
        }
    }
}