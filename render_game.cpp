#include "render_game.h"

void renderGame(SDL_Renderer* renderer, Ball ball, Hole hole, Obstacle obstacles[], int NUM_OBSTACLES, bool isDragging, bool win, int strokes, int score, bool menuDisplayed, bool blink, int logoWidth, int logoHeight) {
    if (isBallReleased) {
        updateBallMovement(ball, obstacles, NUM_OBSTACLES, hole, collisionSound, holeSound, FRICTION, win);
    }
            
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    for (int i = 0; i < NUM_OBSTACLES; ++i) {
        SDL_Rect obstacleRect = { (int)(obstacles[i].x - obstacles[i].width / 2), (int)(obstacles[i].y - obstacles[i].height / 2), obstacles[i].width, obstacles[i].height };
        SDL_RenderCopy(renderer, obstacles[i].texture, NULL, &obstacleRect);
    }
    SDL_Rect holeRect = { (int)(hole.x - hole.width / 2), (int)(hole.y - hole.height / 2), hole.width, hole.height };
    SDL_RenderCopy(renderer, hole.texture, NULL, &holeRect);
    if (isDragging) {
        drawPowerBar(renderer, ball);
    }
    SDL_Rect dstRect = { (int)(ball.x - ball.width / 2), (int)(ball.y - ball.height / 2), ball.width, ball.height };
    SDL_RenderCopy(renderer, ballTexture, NULL, &dstRect);
    string strokesText = "Strokes: " + to_string(strokes);
    string scoreText = "Score: " + to_string(score);
    renderText(renderer, strokesText.c_str(), textColor, 350, 1);
    renderText(renderer, scoreText.c_str(), textColor, 350, 565);
    if (win) {
        SDL_Rect frameRect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 200);
        SDL_RenderFillRect(renderer, &frameRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &frameRect);
        string restartText = "Press R to restart!";
        string winText = "Congratulations! You Won!";
        string strokesText = "Your strokes: " + to_string(strokes);
        string scoreText = "Your score: " + to_string(score);
        renderText(renderer, winText.c_str(), textColor, WINDOW_WIDTH / 2 - 155, WINDOW_HEIGHT / 2 - 80);
        renderText(renderer, strokesText.c_str(), textColor, WINDOW_WIDTH / 2 - 95, WINDOW_HEIGHT / 2 - 40);
        renderText(renderer, scoreText.c_str(), textColor, WINDOW_WIDTH / 2 - 95, WINDOW_HEIGHT / 2 );
        renderText(renderer, restartText.c_str(), textColor, WINDOW_WIDTH / 2 - 115, WINDOW_HEIGHT / 2 + 40);
    }
}
