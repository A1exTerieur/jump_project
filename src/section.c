#include "../include/section.h"



// Modifier la fonction init_section_0 pour avoir un type de retour void
void init_section_0(Section *section) {
    section->id = 0;
   
    // Allouer de la mémoire pour les plateformes
    section->platforms = (Platform *)malloc(sizeof(Platform) * 7);
    if (!section->platforms) {
        printf("Erreur lors de l'allocation de mémoire pour les plateformes\n");
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    // Initialiser les plateformes
    
    section->platforms[0] = (Platform){20, 10, 5, 14, "test.png"};
    section->platforms[1] = (Platform){10, 10, 5, 1, ""};
    section->platforms[2] = (Platform){10, 11, 5, 1, ""};
    section->platforms[3] = (Platform){0, 18, 5, 1, ""};
    section->platforms[4] = (Platform){0, 19, 2, 5, ""};
    section->platforms[5] = (Platform){0, 24, 25, 1, ""};

    section->numPlatforms = 7;

    // Allouer de la mémoire pour les lumières
    section->lights = (Light *)malloc(sizeof(Light) * 1);
    if (!section->lights) {
        printf("Erreur lors de l'allocation de mémoire pour les lumières\n");
        free(section->platforms); // Libérer la mémoire allouée pour les plateformes
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    // Initialiser les lumières
    section->lights[0] = (Light){15, 8, 4, 0, 0};

    section->numLights = 1;
}

void init_section_1(Section *section) {
    section->id = 1;
   
    // Allouer de la mémoire pour les plateformes
    section->platforms = (Platform *)malloc(sizeof(Platform) * 1);
    if (!section->platforms) {
        printf("Erreur lors de l'allocation de mémoire pour les plateformes\n");
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    // Initialiser les plateformes
    
    section->platforms[0] = (Platform){0, 23, 15, 1, ""};
   

    section->numPlatforms = 1;

    // Allouer de la mémoire pour les lumières
    section->lights = (Light *)malloc(sizeof(Light) * 1);
    if (!section->lights) {
        printf("Erreur lors de l'allocation de mémoire pour les lumières\n");
        free(section->platforms); // Libérer la mémoire allouée pour les plateformes
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    section->numLights = 0;
}
// Modifier la fonction draw_section pour appeler les fonctions correctes
void draw_section(SDL_Renderer *renderer, Section *section, Texture **textures) {
   
    
   
    
    draw_platforms(renderer, section->platforms, section->numPlatforms);
    draw_lights(renderer, section->lights, section->numLights);
    

  
}

// Modifier la fonction init_section pour allouer de la mémoire pour la structure Section
Section *init_section(int id) {
   
    Section *section = (Section *)malloc(sizeof(Section));
    if (!section) {
        printf("Erreur lors de l'allocation de mémoire pour la section\n");
        exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }

    section->id = id;
        
    switch (id) {
        case 0:
            init_section_0(section);
            break;
        case 1:
            init_section_1(section);
            break;
        // Ajouter d'autres cas pour d'autres sections si nécessaire
        default:
            printf("ID de section inconnu : %d\n", id);
            free(section); // Libérer la mémoire allouée pour la section
            exit(1); // ou retourner une erreur appropriée selon votre gestion d'erreurs
    }
   
    return section;
}