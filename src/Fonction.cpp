#include <iostream>
#include "Fonction.h"
#include <string>
#include "Editor.h"
#include "Affichage.h"
#include "Maze.h"
#include <SDL2/SDL.h>


void Launcher(){
	Initializeur();
	startmenu();

}

void Initializeur(){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
	{
		std::cout << "Impossible de lancer SDL";
		std::cin.get();
		exit(0);
	}
}