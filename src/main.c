#include <SDL2/SDL.h>
#include "../include/struct.h"
#include "../include/const.h"
#include "../include/player.h"
#include "../include/platform.h"


// Fonction pour initialiser la SDL
int initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Jeu de plateforme", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}




void runGame(SDL_Renderer* renderer) {
    int quit = 0;

    SDL_Event event;

    // Exemple de plateformes avec les sections correspondantes
    Platform platforms[] = {
        { 300, 400, 200, 20, 0 },  // Plateforme de la section 0
        { 200, 300, 150, 20, 0 },  // Plateforme de la section 1
        { 250, 200, 150, 20, 0 },  // Plateforme de la section 0
        { 300, 100, 150, 20, 0 },  // Plateforme de la section 2
        { 300, 100, 150, 20, 1 },  // Plateforme de la section 2
        { 0, SCREEN_HEIGHT - 10, SCREEN_WIDTH, 10, 0 },  // Plateforme de la section 0
        { 200, SCREEN_HEIGHT - 100, 50, 100, 0 }  // Plateforme de la section 1
    };
    int numPlatforms = sizeof(platforms) / sizeof(Platform);

    // Exemple de joueur
    Player player = { 100, 300, 20, 20, 0, 0, 0, 0 };

    int currentSection = 0;

    Uint32 lastUpdate = SDL_GetTicks();  // Temps écoulé depuis le démarrage de l'application

    // Boucle principale du jeu
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Obtenir le temps actuel
        Uint32 currentTicks = SDL_GetTicks();

        // Calculer le temps écoulé depuis la dernière mise à jour
        Uint32 deltaTime = currentTicks - lastUpdate;

        // Mettre à jour la position du joueur si suffisamment de temps s'est écoulé
        if (deltaTime >= UPDATE_RATE) {
            updatePlayer(&player, keystate, platforms, numPlatforms, currentSection);

            // Mettre à jour le temps de la dernière mise à jour
            lastUpdate = currentTicks;
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner les plateformes de la section courante uniquement
        for (int i = 0; i < numPlatforms; i++) {
            Platform platform = platforms[i];
            if (platform.section == currentSection) {
                SDL_Rect rect = { platform.x, platform.y, platform.width, platform.height };
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        // Dessiner le joueur
        drawPlayer(renderer, player);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Vérifier si le joueur dépasse la bordure supérieure
        if (player.y < 0) {
            currentSection++;
            if (currentSection >= numPlatforms) {
                currentSection = 0;
            }
            // Réinitialiser la position du joueur dans la nouvelle section
            player.y = SCREEN_HEIGHT - player.height;
        }
        // Vérifier si le joueur dépasse la bordure inférieure
        else if (player.y + player.height > SCREEN_HEIGHT) {
            currentSection--;
            if (currentSection < 0) {
                currentSection = numPlatforms - 1;
            }
            // Réinitialiser la position du joueur dans la nouvelle section
            player.y = 0;
        }
    }
}




int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    runGame(renderer);

    // Libérer les ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
