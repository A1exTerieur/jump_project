#ifndef STRUCT_H
#define STRUCT_H


// Définir la structure pour représenter une plateforme
typedef struct {
    int x, y, width, height, section;
} Platform;

// Définir la structure pour représenter le joueur
typedef struct {
    int x, y, width, height;
    double dx, dy;
    int isJumping;
    int jumpForce;
} Player;



#endif  // STRUCT_H