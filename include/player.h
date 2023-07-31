#include <SDL2/SDL.h>
#include "../include/struct.h"
#include "../include/const.h"



void drawPlayer(SDL_Renderer* renderer, Player player);
void updatePlayer(Player* player, const Uint8* keystate, Platform* platforms, int numPlatforms);