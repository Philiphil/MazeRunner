#ifndef __RUNNER__
#define __RUNNER__
#include <SDL2/SDL.h>
#include "Maze.h"
#include <string>
#include "Player.h"

void RunnerMainMenu(SDL_Window*, SDL_Renderer*);
void RunnerSee(SDL_Window*, SDL_Renderer*, int*);
void RunnerGUI(SDL_Window*, SDL_Renderer*);
void RunnerFullMode(SDL_Window*, SDL_Renderer*, Maze*);
void RunnerInputDetector(SDL_Event, Maze*, Player*);
void FinishMenu(SDL_Window*, SDL_Renderer*);




#endif