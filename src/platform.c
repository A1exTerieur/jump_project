#include "../include/platform.h"

// Fonction pour dessiner une plateforme
void draw_platform(SDL_Renderer *renderer, Platform *platforms, int numPlatforms, int currentSection)
{
    for (int i = 0; i < numPlatforms; i++)
    {
        Platform platform = platforms[i];
        if (platform.section == currentSection)
        {
            // Calculer les coordonnées et la taille de la plateforme en pixels
            int x = platform.x * SQUARE_SIZE;
            int y = platform.y * SQUARE_SIZE;
            int width = platform.width * SQUARE_SIZE;
            int height = platform.height * SQUARE_SIZE; // Vous pouvez ajuster la hauteur de la plateforme selon vos préférences

            SDL_Rect rect = {x, y, width, height};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
