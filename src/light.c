#include "../include/light.h"



void fillLight(SDL_Renderer *renderer, int x, int y, int intensity)
{
    // Remplir les carrés voisins en fonction de l'intensité de la lumière
    for (int dx = -intensity; dx <= intensity; dx++)
    {
        for (int dy = -intensity; dy <= intensity; dy++)
        {
            int distSquared = dx * dx + dy * dy;
            if (distSquared <= intensity * intensity)
            {
                // Calculer l'intensité de l'alpha en fonction de la distance
                float alpha = (float)(intensity * intensity - distSquared) / (float)(intensity * intensity);

                // Rendre l'alpha plus doux pour créer un effet de transparence
                alpha = alpha * alpha;

                // Réglage de la couleur avec un alpha transparent
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, (int)(255 * alpha));
               
                SDL_Rect rect = {x + dx * LIGHT_SQUARE_SIZE, y + dy * LIGHT_SQUARE_SIZE, LIGHT_SQUARE_SIZE, LIGHT_SQUARE_SIZE};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void draw_light(SDL_Renderer *renderer, Light *lights, int numLights, int currentSection)
{
    for (int i = 0; i < numLights; i++)
    {
        Light light = lights[i];
        if (light.section == currentSection)
        {
            int x = light.x * SQUARE_SIZE + LIGHT_SQUARE_SIZE / 2;
            int y = light.y * SQUARE_SIZE + LIGHT_SQUARE_SIZE / 2;
            int intensity = light.intensity;

            fillLight(renderer, x, y, intensity);
        }
    }
}