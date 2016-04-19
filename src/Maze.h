#ifndef __MAZE__
#define __MAZE__
#include "Case.h"

class Maze{
private:
	int DimX;
	int DimY;
	Case** Plateau;
public:
	Maze();//constructeur basique
	Maze(int, int);//Ca c'est le super constructeur pour le mode personnalisable
	void Afficher();//affichage pour demo console
	~Maze();//destructeur
	Case& GetCase(int, int);// renvoie une reference vers ladite case
	void SetPlateau(int**);//setter
	Case** GetPlateau();//getter
	int* GetDim();//retourne les dimentions du plateau
	void Playable();//rends le labyrinthe jouable
	int IsRunnable();//Verifie que le labyrinthe est au valide
};








#endif