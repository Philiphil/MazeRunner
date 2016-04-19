#ifndef __EDITOR__
#define __EDITOR__
#include <string>
#include "Maze.h"

Maze Lecteur(std::string);
int* Compteur(std::string);
int** Analizeur(int*, std::string);
void Sauvegardeur(Maze*, std::string);
bool DoesFileExist(const std::string&);
#endif