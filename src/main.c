#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/player.h"
#include "../include/platform.h"
#include "../include/light.h"
#include "../include/texture.h"
#include "../include/section.h"


// Fonction pour initialiser la SDL
int initializeSDL(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Jeu de plateforme", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL)
    {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void runGame(SDL_Renderer *renderer)
{

    int quit = 0;

    Texture *textures = init_textures(renderer);
    SDL_Event event;

    Section sections[] = {
        *init_section(0),
        *init_section(1),
        *init_section(2),
    };

  

    // Exemple de joueur
    Player player = {200, 20, 25, 25, 0, 0, 0, 0, 0, 0};

    int currentSection = 0;

    Uint32 lastUpdate = SDL_GetTicks(); // Temps écoulé depuis le démarrage de l'application
                                        // Définir la taille de chaque carré vide

    // Calculer le nombre de carrés horizontaux et verticaux sur l'écran
    // int num_horizontal_squares = SCREEN_WIDTH / SQUARE_SIZE;
    // int num_vertical_squares = SCREEN_HEIGHT / SQUARE_SIZE;

    // int num_horizontal_squares_light = SCREEN_WIDTH / LIGHT_SQUARE_SIZE;
    // int num_vertical_squares_light = SCREEN_HEIGHT / LIGHT_SQUARE_SIZE;
    // Boucle principale du jeu

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        // Obtenir le temps actuel
        Uint32 currentTicks = SDL_GetTicks();

        // Calculer le temps écoulé depuis la dernière mise à jour
        Uint32 deltaTime = currentTicks - lastUpdate;

        // Mettre à jour la position du joueur si suffisamment de temps s'est écoulé
        if (deltaTime >= UPDATE_RATE)
        {
            updatePlayer(&player, keystate, sections[currentSection].platforms, sections[currentSection].numPlatforms);
            // Mettre à jour l'état d'animation des lumières
            /*for (int i = 0; i < numLights; i++)
            {
                Light *light = &lights[i];
                light->animationState += 1;
                if (light->animationState >= ANIMATION_DURATION)
                {
                    light->animationState = 0;
                }
            }*/
            // Mettre à jour le temps de la dernière mise à jour
            lastUpdate = currentTicks;
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderClear(renderer);

        draw_section(renderer, &sections[currentSection], &textures);
        
        // Dessiner les carrés vides
        /*for (int i = 0; i < num_horizontal_squares_light; i++)
        {
            for (int j = 0; j < num_vertical_squares_light; j++)
            {
                // Calculer les coordonnées du carré
                int x = i * LIGHT_SQUARE_SIZE;
                int y = j * LIGHT_SQUARE_SIZE;

                // Dessiner le carré vide
                SDL_Rect rect = {x, y, LIGHT_SQUARE_SIZE, LIGHT_SQUARE_SIZE};

                // Dessiner les bordures autour du carré
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }*/
        // Dessiner les carrés vides
        /*for (int i = 0; i < num_horizontal_squares; i++)
        {
            for (int j = 0; j < num_vertical_squares; j++)
            {
                // Calculer les coordonnées du carré
                int x = i * SQUARE_SIZE;
                int y = j * SQUARE_SIZE;

                // Dessiner le carré vide
                SDL_Rect rect = {x, y, SQUARE_SIZE, SQUARE_SIZE};

                // Dessiner les bordures autour du carré
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }*/
        // Dessiner le joueur
        drawPlayer(renderer, player);
        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
        // Vérifier si le joueur dépasse la bordure supérieure
        if (player.y < 0 - player.height)
        {
            currentSection++;

            // Réinitialiser la position du joueur dans la nouvelle section
            player.y = SCREEN_HEIGHT - player.height;
        }
        // Vérifier si le joueur dépasse la bordure inférieure
        else if (player.y + player.height > SCREEN_HEIGHT)
        {
            currentSection--;

            // Réinitialiser la position du joueur dans la nouvelle section
            player.y = 0;
        }
    }
    free_textures();

}

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!initializeSDL(&window, &renderer))
    {
        return 1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    runGame(renderer);

    // Libérer les ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
