#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/struct.h"
#include "../include/const.h"

Texture *loadTexture(SDL_Renderer *renderer, const char *imagePath, int section);
void draw_texture(int x, int y, Texture *imageTexture, SDL_Renderer *renderer, int currentSection);