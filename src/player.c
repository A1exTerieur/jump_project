#include "../include/player.h"
#include <stdio.h>

// Fonction pour dessiner le joueur
void drawPlayer(SDL_Renderer *renderer, Player player)
{
    SDL_Rect rect = {player.x, player.y, player.width, player.height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void movePlayer(Player *player, const Uint8 *keystate)
{
    if (keystate[SDL_SCANCODE_LEFT] && player->isJumping == 0)
    {

        if (player->isInAir == 1)
        {
            player->dx += -PLAYER_JUMP_SPEED;
        }
        else
        {
            player->dx = -PLAYER_SPEED;
        }
    }
    else if (keystate[SDL_SCANCODE_RIGHT] && player->isJumping == 0)
    {

        if (player->isInAir == 1)
        {
            player->dx += PLAYER_JUMP_SPEED;
        }
        else
        {
            player->dx = PLAYER_SPEED;
        }
    }
    else
    {
        if (player->dy == 0)
        {
            if (player->dx > 0)
            {
                player->dx -= PLAYER_INERTIA;
                if (player->dx < 0)
                {
                    player->dx = 0;
                }
            }
            else if (player->dx < 0)
            {
                player->dx += PLAYER_INERTIA;
                if (player->dx > 0)
                {
                    player->dx = 0;
                }
            }
        }
    }
}

void jumpPlayer(Player *player, const Uint8 *keystate)
{
    if (keystate[SDL_SCANCODE_SPACE] && player->isJumping == 0 && player->dy == 0)
    {
        player->isJumping = 1;
    }
    if (keystate[SDL_SCANCODE_SPACE] && player->isJumping == 1)
    {
        player->jumpForce += 1;
        if (player->jumpForce > PLAYER_MAX_JUMP_FORCE)
        {
            player->jumpForce = PLAYER_MAX_JUMP_FORCE;
        }
    }
    if (!keystate[SDL_SCANCODE_SPACE] && player->isJumping == 1)
    {
        if (keystate[SDL_SCANCODE_LEFT])
        {
            player->dx = -PLAYER_SPEED;
        }
        else if (keystate[SDL_SCANCODE_RIGHT])
        {
            player->dx = PLAYER_SPEED;
        }

        player->isJumping = 0;
        player->dy = -player->jumpForce;
        player->jumpForce = 0;
    }
}

void limitPlayer(Player *player)
{
    if (player->x < 0)
    {
        player->x = 0;
    }

    // Limiter le joueur à l'écran droit
    if (player->x + player->width > SCREEN_WIDTH)
    {
        player->x = SCREEN_WIDTH - player->width;
    }
}

void platformCollisionPlayer(Player *player, Platform *platforms, int numPlatforms, int currentSection)
{
    // Variable pour suivre si le joueur se trouve sur une plateforme
    int onPlatform = 0;

    // Gérer les collisions avec les plateformes de la section courante
    for (int i = 0; i < numPlatforms; i++)
    {
        Platform platform = platforms[i];

        // Vérifier si le joueur se chevauche avec la plateforme de la section courante
        if (platform.section == currentSection &&
            player->x < platform.x + platform.width &&
            player->x + player->width > platform.x &&
            player->y + player->height > platform.y &&
            player->y < platform.y + platform.height)
        {
            onPlatform = 1; // Le joueur est sur une plateforme

            if (player->dy > 0 && player->y + player->height - player->dy <= platform.y)
            {
                // Atterrissage sur la plateforme depuis le haut
                player->y = platform.y - player->height;
                player->dy = 0;
                player->isInAir = 0;
            }
            else if (player->dy < 0 && player->y - player->dy >= platform.y + platform.height)
            {
                // Collision avec la plateforme depuis le bas
                player->y = platform.y + platform.height;
                player->dy = 0;
            }
            else if (player->dx > 0 && player->x + player->width > platform.x && player->x + player->width <= platform.x + platform.width)
            {
                // Collision avec la gauche de la plateforme
                if (player->y + player->height > platform.y && player->y < platform.y + platform.height)
                {
                    // Ajuster la position du joueur à droite de la plateforme
                    player->x = platform.x - player->width;
                    player->dx = 0;
                }
            }
            else if (player->dx < 0 && player->x < platform.x + platform.width && player->x >= platform.x)
            {
                // Collision avec la droite de la plateforme
                if (player->y + player->height > platform.y && player->y < platform.y + platform.height)
                {
                    // Ajuster la position du joueur à gauche de la plateforme
                    player->x = platform.x + platform.width;
                    player->dx = 0;
                }
            }
            else if (player->dy > 0 && player->y + player->height <= platform.y)
            {
                // Collision avec le dessous de la plateforme lors du saut
                player->y = platform.y - player->height;
                player->dy = 0;
            }
        }
    }

    // Vérifier si le joueur est en l'air après la boucle de collision
    if (!onPlatform)
    {
        player->isInAir = 1;
    }
}

void updatePlayer(Player *player, const Uint8 *keystate, Platform *platforms, int numPlatforms, int currentSection)
{
    //  Gérer les touches de déplacement du joueur
    movePlayer(player, keystate);
    //  Gérer le saut du joueur
    jumpPlayer(player, keystate);
    // Limiter le joueur à l'écran
    limitPlayer(player);
    // Appliquer la gravité
    player->dy += GRAVITY;
    // Mettre à jour les coordonnées du joueur
    player->x += player->dx;
    player->y += player->dy;
    // Gérer les collisions avec les plateformes de la section courante
    platformCollisionPlayer(player, platforms, numPlatforms, currentSection);
}
