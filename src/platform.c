#include "../include/platform.h"
#include "../include/texture.h"

// Fonction pour dessiner une plateforme
void draw_platform(SDL_Renderer *renderer, Platform *platforms, int numPlatforms, int currentSection, Texture *noTexture)
{
    for (int i = 0; i < numPlatforms; i++)
    {
        Platform platform = platforms[i];
        if (platform.section == currentSection)
        {
            for (int x = platform.x; x < platform.x + platform.width; x++)
            {
                for (int y = platform.y; y < platform.y + platform.height; y++)
                {
                    draw_texture(x, y, noTexture, renderer, platform.section);
                }
            }
        }
    }
}
