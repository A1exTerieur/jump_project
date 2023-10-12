#include "../include/texture.h"
Texture *loadedTextures = NULL;
int numLoadedTextures = 0;



Texture *loadTexture(SDL_Renderer *renderer, char *imagePath)
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
        SDL_FreeSurface(surface);
        return NULL;
    }

    // Libérer la surface, car nous n'en avons plus besoin
    SDL_FreeSurface(surface);

    // Allouer de la mémoire pour la structure Texture
    Texture *imageTexture = (Texture *)malloc(sizeof(Texture));
    if (!imageTexture)
    {
        printf("Erreur lors de l'allocation de mémoire pour Texture\n");
        SDL_DestroyTexture(texture);
        return NULL;
    }

    // Remplir les champs de la structure Texture
    imageTexture->x = 0;
    imageTexture->y = 0;
    imageTexture->resolution = 1;
    imageTexture->texture = texture;

    // Allouer de la mémoire pour le nom de l'image et le copier dans la structure Texture
    imageTexture->name = (char *)malloc(strlen(imagePath) + 1);
    if (!imageTexture->name)
    {
        printf("Erreur lors de l'allocation de mémoire pour le nom de l'image\n");
        free(imageTexture);
        SDL_DestroyTexture(texture);
        return NULL;
    }
    strcpy(imageTexture->name, basename(imagePath));

    return imageTexture;
}



void draw_texture(int x, int y, SDL_Renderer *renderer, char *name)
{
   
    // Chercher la texture avec le nom spécifié dans la variable globale des textures chargées
    for (int i = 0; i < numLoadedTextures; i++)
    {
        Texture *imageTexture = &loadedTextures[i];
        if (strcmp(imageTexture->name, name) == 0)
        {
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

            // Sortir de la boucle une fois que la texture a été trouvée et dessinée
            return;
        }
    }
    draw_texture(x, y, renderer, "no_texture.png");

}


// Fonction pour charger toutes les textures du dossier /assets/texture
Texture *init_textures(SDL_Renderer *renderer)
{
    // Ouvrir le dossier /assets/texture
    DIR *dir = opendir(TEXTURE_FOLDER_PATH);
    if (!dir)
    {
        printf("Erreur lors de l'ouverture du dossier %s\n", TEXTURE_FOLDER_PATH);
        return NULL;
    }

    // Compter le nombre de fichiers (textures) dans le dossier
    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG) // DT_REG indique un fichier régulier (non un répertoire)
        {
            count++;
        }
    }
    closedir(dir);

    // Allouer de la mémoire pour le tableau de textures
    Texture *textures = (Texture *)malloc(count * sizeof(Texture));
    if (!textures)
    {
        printf("Erreur lors de l'allocation de mémoire pour les textures\n");
        return NULL;
    }

    // Ouvrir à nouveau le dossier pour charger les textures
    dir = opendir(TEXTURE_FOLDER_PATH);
    if (!dir)
    {
        printf("Erreur lors de l'ouverture du dossier %s\n", TEXTURE_FOLDER_PATH);
        free(textures); // Libérer la mémoire allouée pour le tableau de textures
        return NULL;
    }

    int index = 0;
    // Lire les fichiers du dossier et charger les textures
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG) // DT_REG indique un fichier régulier (non un répertoire)
        {
            // Construire le chemin complet de l'image
            char imagePath[273];
            snprintf(imagePath, sizeof(imagePath), "%s/%s", TEXTURE_FOLDER_PATH, entry->d_name);

            // Charger la texture et l'ajouter au tableau de textures
            Texture *imageTexture = loadTexture(renderer, imagePath);
            if (imageTexture)
            {
                textures[index] = *imageTexture;
                free(imageTexture); // Nous n'avons plus besoin de la structure Texture allouée dans loadTexture
                index++;
            }
        }
    }
    closedir(dir);

    // Mettre à jour le nombre total de textures chargées
    loadedTextures = textures;
    numLoadedTextures = count;
    return textures;
}

void free_textures()
{
    for (int i = 0; i < numLoadedTextures; i++)
    {
        SDL_DestroyTexture(loadedTextures[i].texture);
    }

    free(loadedTextures);
}
