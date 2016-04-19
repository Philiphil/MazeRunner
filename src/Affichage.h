#ifndef __AFFICHAGE__
#define __AFFICHAGE__
#include <string>
#include <SDL2/SDL.h>

void startmenu();
void MainAffichage(SDL_Window*, SDL_Renderer*);
SDL_Texture* Load(std::string, SDL_Renderer*);
void Draw(SDL_Texture *, SDL_Renderer*, int, int);
int MainMenuInputDetector(int,int);
void Fermeture(SDL_Window*, SDL_Renderer*);
std::string InputDetector(SDL_Window*, SDL_Renderer*);
std::string InputAlgo(SDL_Event);
int InputValidator(SDL_Event);
SDL_Texture* Write(const std::string &, SDL_Renderer*);
#endif