#include "../include/section.h"

// Modifier la fonction init_section_0 pour avoir un type de retour void
void fill_section(Section *section)
{
    

       char sectionFileName[256]; // Assurez-vous que la taille est suffisamment grande
    snprintf(sectionFileName, sizeof(sectionFileName), "./assets/section/section_%d.txt", section->id);

    // Ouvrir le fichier en lecture
    FILE *file = fopen(sectionFileName, "r");
    if (!file)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    // Compter le nombre de lignes dans le fichier
    int count_line = 0; // Initialisez le compteur à zéro

    char line[256]; // Assurez-vous que la taille est suffisamment grande pour contenir une ligne du fichier
    while (fgets(line, sizeof(line), file))
    {
        count_line++; // Incrémentez le compteur à chaque ligne lue
    }

    fseek(file, 0, SEEK_SET);

    // Allouer de la mémoire pour les plateformes en fonction du nombre de lignes
    section->platforms = (Platform *)malloc(sizeof(Platform) * count_line);
    if (!section->platforms)
    {
        printf("Erreur lors de l'allocation de mémoire pour les plateformes\n");
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    int i = 0;
    // Initialiser les plateformes
    while (fgets(line, sizeof(line), file))
    {
        int value1, value2, value3, value4;
        char value5[256]; // Supposons que la chaîne peut avoir jusqu'à 255 caractères

        if (sscanf(line, "{%d, %d, %d, %d, %255[^}]}", &value1, &value2, &value3, &value4, value5) == 5)
        {

           

            char *tmp = (char *)malloc(sizeof(char) * strlen(value5));
            strcpy(tmp, value5);
          
            section->platforms[i] = (Platform){value1, value2, value3, value4, tmp};
            i++;
        }
    }

    section->numPlatforms = count_line;
    /*
         // Allouer de la mémoire pour les lumières
    section->lights = (Light *)malloc(sizeof(Light) * 1);
    if (!section->lights)
    {
        printf("Erreur lors de l'allocation de mémoire pour les lumières\n");
        free(section->platforms); // Libérer la mémoire allouée pour les plateformes
        exit(1);                  // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    // Initialiser les lumières
    section->lights[0] = (Light){15, 8, 4, 0, 0};

    section->numLights = 1;
    
    */
   
}


// Modifier la fonction draw_section pour appeler les fonctions correctes
void draw_section(SDL_Renderer *renderer, Section *section, Texture **textures)
{

    draw_platforms(renderer, section->platforms, section->numPlatforms);
    //draw_lights(renderer, section->lights, section->numLights);
}

// Modifier la fonction init_section pour allouer de la mémoire pour la structure Section
Section *init_section(int id)
{

    Section *section = (Section *)malloc(sizeof(Section));
    if (!section)
    {
        printf("Erreur lors de l'allocation de mémoire pour la section\n");
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    section->id = id;
    section->numPlatforms = 0;
    printf("init section %d ...\n", id);
    fill_section(section);

    return section;
}