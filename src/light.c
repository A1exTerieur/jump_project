#include "../include/light.h"

// Ajouter cette constante pour contrôler la durée de chaque étape de l'animation

void fillLight(SDL_Renderer *renderer, int x, int y, int intensity, int size, int animationState)
{

    // Transformation de l'animationState en une valeur entre 0 et 1 pour l'interpolation
    float t = (float)animationState / ANIMATION_DURATION;

    // Appliquer une fonction sinus à t pour obtenir une interpolation en douceur pour la moitié extérieure du cercle
    float alphaFactor = 0.5f + 0.5f * sin(t * M_PI);

    // Remplir les carrés voisins en fonction de la distance du centre de la lumière
    for (int distance = 0; distance <= intensity; distance++)
    {
        // Calculer la taille actuelle de la lumière en fonction de la distance du centre
        int currentSize = size + (int)((float)distance * LIGHT_SQUARE_SIZE);

        for (int dx = -distance; dx <= distance; dx++)
        {
            for (int dy = -distance; dy <= distance; dy++)
            {
                int distSquared = dx * dx + dy * dy;
                if (distSquared <= distance * distance)
                {
                    // Calculer l'intensité de l'alpha en fonction de la distance par rapport au centre du cercle
                    float distanceToCenter = sqrt(dx * dx + dy * dy);
                    float alpha;

                    // Appliquer une interpolation exponentielle plus douce pour ajuster le dégradé du centre
                    alpha = 1.0f - pow(distanceToCenter / intensity, 2); // Fonction d'interpolation exponentielle plus douce

                    // Appliquer l'effet de clignotement en fonction de l'animationState
                    alpha *= alphaFactor;

                    // Réglage de la couleur avec un alpha transparent
                    // Vous pouvez ajuster les valeurs des canaux RGB pour augmenter le contraste
                    int r = 255;
                    int g = 255;
                    int b = 0;
                    int alphaValue = (int)(16 * alpha); // Ajuster la valeur de l'alpha pour augmenter l'opacité

                    SDL_SetRenderDrawColor(renderer, r, g, b, alphaValue);

                    // Dessiner le carré de lumière avec la taille actuelle
                    SDL_Rect rect = {x + dx * LIGHT_SQUARE_SIZE - currentSize / 2, y + dy * LIGHT_SQUARE_SIZE - currentSize / 2, currentSize, currentSize};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
}

void draw_light(SDL_Renderer *renderer, Light *lights, int numLights, int currentSection)
{
    for (int i = 0; i < numLights; i++)
    {
        Light *light = &lights[i]; // Utiliser un pointeur pour accéder à la lumière
        if (light->section == currentSection)
        {
            // Mettre à jour l'état d'animation de la lumière
            light->animationState++;
            if (light->animationState >= ANIMATION_DURATION)
            {
                light->animationState = 0;
            }

            int x = light->x * SQUARE_SIZE + LIGHT_SQUARE_SIZE;
            int y = light->y * SQUARE_SIZE + LIGHT_SQUARE_SIZE;
            int intensity = light->intensity;
            int size = LIGHT_SQUARE_SIZE; // Taille de la lumière initiale
            fillLight(renderer, x, y, intensity, size, light->animationState);
        }
    }
}
