#include "../include/light.h"


void fillLight(SDL_Renderer *renderer, int x, int y, int intensity, int size, int frame)
{
    int maxFrame = ANIMATION_FRAMES / 2; // La moitié du nombre total de frames pour la transition en taille

    // Remplir les carrés voisins en fonction de la distance du centre de la lumière
    for (int distance = 0; distance <= intensity; distance++)
    {
        // Calculer l'intensité de l'alpha en fonction de la distance
        float alpha = (float)(intensity - distance) / (float)intensity;

        // Rendre l'alpha plus doux pour créer un effet de transparence
    

        // Calculer la taille actuelle de la lumière en fonction de la distance du centre
        int currentSize;
        if (frame <= maxFrame)
        {
            // Expansion initiale
            float scale = (float)frame / (float)maxFrame;
            currentSize = size + (int)((float)distance * LIGHT_SQUARE_SIZE * scale);
        }
        else
        {
            // Rétrécissement progressif après l'expansion
            int reversedFrame = ANIMATION_FRAMES - frame;
            float scale = (float)reversedFrame / (float)maxFrame;
            currentSize = size + (int)((float)distance * LIGHT_SQUARE_SIZE * scale);
        }

        for (int dx = -distance; dx <= distance; dx++)
        {
            for (int dy = -distance; dy <= distance; dy++)
            {
                int distSquared = dx * dx + dy * dy;
                if (distSquared <= distance * distance)
                {
                    // Réglage de la couleur avec un alpha transparent
                    // Vous pouvez ajuster les valeurs des canaux RGB pour augmenter le contraste
                    int r = 255;
                    int g = 255;
                    int b = 0;
                    int alphaValue = (int)(128 *alpha); // Ajuster la valeur de l'alpha pour augmenter l'opacité

                    SDL_SetRenderDrawColor(renderer, r, g, b, alphaValue);

                    // Dessiner le carré de lumière avec la taille actuelle
                    SDL_Rect rect = {x + dx * LIGHT_SQUARE_SIZE - currentSize / 2, y + dy * LIGHT_SQUARE_SIZE - currentSize / 2, currentSize, currentSize};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
}







void draw_light(SDL_Renderer *renderer, Light *lights, int numLights, int currentSection, int frame)
{
    for (int i = 0; i < numLights; i++)
    {
        Light light = lights[i];
        if (light.section == currentSection)
        {
            int x = light.x * SQUARE_SIZE + LIGHT_SQUARE_SIZE;
            int y = light.y * SQUARE_SIZE + LIGHT_SQUARE_SIZE;
            int intensity = light.intensity;
            int size = LIGHT_SQUARE_SIZE; // Taille de la lumière initiale

            fillLight(renderer, x, y, intensity, size, frame);

            // Mettre à jour le frame pour l'animation de la lumière
            light.frame = (light.frame + 1) % ANIMATION_FRAMES;
            lights[i] = light;
        }
    }
}
