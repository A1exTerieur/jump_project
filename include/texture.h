#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>
#include "../include/struct.h"
#include "../include/const.h"

void draw_texture(int x, int y, SDL_Renderer *renderer, char *name);

Texture *init_textures(SDL_Renderer *renderer);

void free_textures();
