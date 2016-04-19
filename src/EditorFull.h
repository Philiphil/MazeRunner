#ifndef __EDITOR_F__
#define __EDITOR_F__
#include <SDL2/SDL.h>
#include "Maze.h"
#include <string>


void EditFullMode(SDL_Window*, SDL_Renderer*, Maze*, std::string);
void EditorFullMazeAfficher(SDL_Window*, SDL_Renderer*, Maze*, int*);
void EditorInputDetector(SDL_Window*, SDL_Renderer*, SDL_Event, Maze*, int*, int*, std::string);
int EditorInputGUI(SDL_Event);
void EditorInputMaze(SDL_Event, Maze*, int*,int);
void EditorCamera(int*, int, Maze*);
#endif