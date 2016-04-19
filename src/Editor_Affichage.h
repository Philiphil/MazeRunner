#ifndef __E_AFFICHAGE__
#define __E_AFFICHAGE__
#include <string>
#include <SDL2/SDL.h>
#include "Maze.h"
void EditorMainMenu(SDL_Window*, SDL_Renderer*);
void EditorNewAffichage(SDL_Window*, SDL_Renderer*);
void EditorEditAffichage(SDL_Window*, SDL_Renderer*);
int EditorXY(SDL_Window*, SDL_Renderer*, std::string);
int IntValidator(SDL_Event);
#endif