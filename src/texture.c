#include "../include/texture.h"

Texture *loadTexture(SDL_Renderer *renderer, const char *imagePath, int section)
{
    // Charger l'image depuis le chemin spécifié
    SDL_Surface *surface = IMG_Load(imagePath);
    if (!surface)
    {
        printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return NULL;
    }

    // Créer une texture à partir de la surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
    }

    // Libérer la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);

    // Allouer de la mémoire pour la structure Texture
    Texture *imageTexture = (Texture *)malloc(sizeof(Texture));

    // Remplir les champs de la structure Texture
    imageTexture->x = 0;
    imageTexture->y = 0;
    imageTexture->resolution = 1;
    imageTexture->section = section;
    imageTexture->texture = texture;

    return imageTexture;
}

void draw_texture(int x, int y, Texture *imageTexture, SDL_Renderer *renderer, int currentSection)
{
    // Vérifier si la texture appartient à la section courante

    // Obtenir les dimensions de la texture
    int width, height;
    SDL_QueryTexture(imageTexture->texture, NULL, NULL, &width, &height);

    // Convertir les coordonnées de base en coordonnées de case
    int squareX = x * SQUARE_SIZE;
    int squareY = y * SQUARE_SIZE;

    // Convertir les dimensions de base en dimensions de case
    int squareWidth = imageTexture->resolution * width * 2;
    int squareHeight = imageTexture->resolution * height * 2;

    // Créer un rectangle pour définir la position et la taille du rendu de la texture
    SDL_Rect destRect = {squareX, squareY, squareWidth, squareHeight};

    // Copier la texture sur le renderer
    SDL_RenderCopy(renderer, imageTexture->texture, NULL, &destRect);
}
