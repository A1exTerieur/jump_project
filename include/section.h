#include "../include/struct.h"
#include "../include/const.h"
#include "../include/platform.h"
#include "../include/light.h"

Section *init_section(int id);
void draw_section(SDL_Renderer *renderer, Section *section, Texture **textures);
