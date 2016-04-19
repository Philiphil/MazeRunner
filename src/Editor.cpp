#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include "Editor.h"
#include "Maze.h"

using namespace std;


Maze Lecteur(string fichier){
	int *x = Compteur(fichier);
	int **y = Analizeur(x, fichier);
	Maze *maze = new Maze(x[0], x[1]);
	maze->SetPlateau(y);
	delete[]x;
	delete[]y;
	return *maze;
}


int* Compteur(string fichier){
	/*
	Le boulot de compteur, �a va etre de stocker les dimentions du .maze
	Donc, j'ouvre le fichier, � chaque ligne du fichier, l'augmente retour[0]
	et je capture apres la longueur de chaque ligne, bon je pourrais le faire qu'une fois
	mais bon, quite � avoir une boucle, autant s'en servir, c'est pas une op�ration tres violente
	*/
	ifstream file(fichier);
	string foo;



	int *retour = new int[2];
	retour[0] = 0;
	while (getline(file, foo))
	{
		retour[0]++;
		retour[1] = foo.length();
	}
	return retour;
}

int** Analizeur(int *foo, string fichier){

	int** plateau = new int*[foo[0]];
	for (int i = 0; i < foo[0]; i++){
		plateau[i] = new int[foo[1]];
	}
	//Je vais analyser le contenu du fichier pour en faire un tableau
	//je viens de le faire � la bonne taille.

	string* lignesdufichier = new string[foo[0]];
	//je vais stocker les lignes du fichier dans un tableau du m�me nombre de ligne que le plateau.
	//Car justement, les lignes du fichier sont celles du tableau.
	int x = 0;//J'ai besoin d'une variable pour naviguer dans lignesdufichier
	ifstream file(fichier);
	string fnord;//je nomme toujours tres mal mes variables tempo
	while (getline(file, fnord)){
		//Fnord va juste servir � contenir les lignes durant le getline
		lignesdufichier[x] = fnord;//je transfere dans le tableau
		x++;
	}
	//Bon, j'ai d�coup� le fichier en ligne, il faut que je le d�coupe en colone.

	for (int i = 0; i < foo[0]; i++)//Bon, maintenant �a va devenir serieux
	{
		for (int j = 0; j < foo[1]; j++){
			plateau[i][j] = stoi(lignesdufichier[i].substr(0, 1));
			lignesdufichier[i].erase(0, 1);
		}
	}
	//Ah bah non, c'�tait simple.
	//Bon, plateau contient ce qu'il doit contenir, c'est cool.
	//On peut le renvoyer mais d'abbord
	delete[] lignesdufichier;//je clean;
	return plateau;
}

void Sauvegardeur(Maze* maze, string file){
	//Bon, il est 3 heures du mat, et ces histoirs de pointeurs comencent � me fatiguer, mais je dois lui balancer une reference pour qu'il marche
	ofstream fichier(file);
	int *x = maze->GetDim();
	for (int i = 0; i < x[0]; i++)
	{
		for (int j = 0; j < x[1]; j++)
		{
			Case& foo = maze->GetCase(i, j);
			fichier << foo.GetType();
		}
		fichier << endl;
	}
	fichier.close();
	delete[] x;
}

bool DoesFileExist(const string &file)
{
	ifstream infile(file);
	return infile.good();
}