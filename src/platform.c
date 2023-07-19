#include "../include/platform.h"


// Fonction pour dessiner une plateforme
void drawPlatform(SDL_Renderer* renderer, Platform platform) {
    SDL_Rect rect = { platform.x, platform.y, platform.width, platform.height };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
