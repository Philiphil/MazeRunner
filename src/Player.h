#ifndef __PLAYER__
#define __PLAYER__
#include "Maze.h"

class Player{
private:
	int PosX;
	int PosY;
	int* Regard;
public:
	Player();//constructeur basique
	~Player();//destructeur
	void SetDepart(Maze*);//positionne le player au départ
	void SeTourner(int);//tourne
	int* GetView(Maze*);//renvoie ce que le player est censé voir
	void Move(int, Maze*);//gere les mouvements, divisé en 4 partie
	void Up(Maze*);//haut
	void Down(Maze*);//bas
	void Left(Maze*);//gauche
	void Right(Maze*);//droite
	void Turn(int, Maze*);//se tourner
	void DebugConsole(Maze*);//le nom est assez explicite nah ?
	int Win(Maze*);//atteste de la victoire ou non
};








#endif