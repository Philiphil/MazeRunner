#include <string>
#include <iostream>
#include "Maze.h"
#include "Case.h"

using namespace std;



Maze::Maze(){
	//Constructeur par défaut
	DimX = 10;
	DimY = 10;
	Plateau = new Case*[DimX];
	for (int i = 0; i < DimX; i++){
		Plateau[i] = new Case[DimY];
	}
}

Maze::Maze(int x, int y){
	DimX = x;
	DimY = y;
	Plateau = new Case*[DimX];
	for (int i = 0; i < DimX; i++){
		Plateau[i] = new Case[DimY];
	}
}

Case& Maze::GetCase(int x, int y){
	return Plateau[x][y];
}

int* Maze::GetDim(){
	int *foo = new int[2];
	foo[0] = DimX;
	foo[1] = DimY;
	return foo;
}

void Maze::Afficher(){
	for (int i = 0; i < DimX; i++)
	{
		for (int j = 0; j < DimY; j++)
		{
			cout << Plateau[i][j].GetType();
		}
		cout << endl;
	}
}


void Maze::SetPlateau(int** foo){
	for (int i = 0; i < DimX; i++)
	{
		for (int j = 0; j < DimY; j++)
		{
			Plateau[i][j].SetType(foo[i][j]);
		}
	}
}

Case** Maze::GetPlateau(){
	return Plateau;
}

Maze::~Maze(){
	//destructeur propre
	delete[] Plateau;
}

void Maze::Playable(){//Entour le labyrinthe de mur pour le mode run
	Case** Old = new Case*[DimX];
	for (int i = 0; i < DimX; i++){
		Old[i] = new Case[DimY];
	}
	for (int i = 0; i < DimX; i++)
	{
		for (int j = 0; j < DimY; j++)
		{
			Old[i][j].SetType(Plateau[i][j].GetType());
		}
	}
	DimX = DimX + 2;
	DimY = DimY + 2;
	Plateau = new Case*[DimX];
	for (int i = 0; i < DimX; i++){
		Plateau[i] = new Case[DimY];
	}
	for (int i = 0; i < DimX; i++)
	{
		for (int j = 0; j < DimY; j++)
		{
			Plateau[i][j].SetType(1);
		}
	}
	for (int i = 1; i < DimX-1; i++)
	{
		for (int j = 1; j < DimY-1; j++)
		{
			Plateau[i][j].SetType(Old[i-1][j-1].GetType());
		}
	}
	delete[] Old;
}

int Maze::IsRunnable(){
	int x=0;//ici je verifie que le plateau contient un début et une fin
	int y=0;//et un seul de chaque
	for (int i = 0; i < DimX; i++)
	{
		for (int j = 0; j < DimY; j++)
		{
			if (Plateau[i][j].GetType() == 2){// 2 = début
				cout << "kanmem" << endl;
				x++;
			}
			else if (Plateau[i][j].GetType() == 3){// 3 = fin
				y++;
			}
		}
	}
	cout << x << " " << y << endl;
	if (x != 1 || y != 1){
		return 0;
	}
	else{
		return 1;
	}

}

