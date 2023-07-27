#ifndef STRUCT_H
#define STRUCT_H

// Définir la structure pour représenter une plateforme
typedef struct
{
    int x, y, width, height, section;
} Platform;

// Définir la structure pour représenter le joueur
typedef struct
{
    int x, y, width, height;
    double dx, dy;
    int isJumping;
    int jumpForce;
    int jumpDirection;
    int isInAir;
} Player;

typedef struct
{
    int x;         // Position x de la lumière sur la grille
    int y;         // Position y de la lumière sur la grille
    int intensity; // Ajout de l'attribut intensity
    int section;
    int animationState; // Ajout de l'état d'animation

} Light;

typedef struct
{
    int x;
    int y;
    int resolution;
    SDL_Texture *texture;
    int section;
} Texture;
#endif // STRUCT_H