#include <SDL2/SDL.h>
#include "Maze.h"
#include "EditorFull.h"
#include <iostream>
#define _TailleBloc 8
#include "Editor_Affichage.h"
#include "Editor.h"
#include "Affichage.h"

using namespace std;


void EditFullMode(SDL_Window* fen, SDL_Renderer* ren, Maze* maze, string foo){
	int select = 1;
	int* index = new int[2];
	index[0] = 0;
	index[1] = 0;
	SDL_RenderClear(ren);
	bool running = true;
	SDL_Event e;

	EditorFullMazeAfficher(fen, ren, maze, index);

	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){
					EditorInputDetector(fen, ren, e, maze, index, &select, foo);
					SDL_RenderClear(ren);
					EditorFullMazeAfficher(fen, ren, maze, index);
			}//fin du  if
		}//fin de l'attente d'event
	}//fin de la boucle
}

void EditorInputDetector(SDL_Window* fen, SDL_Renderer* ren, SDL_Event e, Maze* maze, int* index, int* select, string foo){
	int retour = -1;
	if (e.motion.y >= 520){
		retour = EditorInputGUI(e);
		switch (retour)
		{
		case 1:
			Sauvegardeur(maze, foo);
			break;
		case 2:
			Sauvegardeur(maze, foo);//pas besoin de break pour celle ci
		case 3:
			delete[] index;
			MainAffichage(fen, ren);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			EditorCamera(index, retour, maze);
			break;
		case 8:
			*select = 1;
			break;
		case 9:
			*select = 0;
			break;
		case 10:
			*select =2 ;
			break;
		case 11:
			*select =3 ;
			break;
		case -1:
		default:
			break;
		}
	}
	else{
		EditorInputMaze(e, maze, index, *select);
	}
}

void EditorCamera(int* index, int foo, Maze* maze){
	int* x = maze->GetDim();
	if (foo == 4 && index[0] > 0 ){
		index[0]--;
	}
	if (foo == 5 && index[0]+65 < x[0]){//
		index[0]++;
	}
	if (foo == 6 && index[1] > 0){
		index[1]--;
	}
	if (foo == 7 && index[1]+65 < x[0]){//
		index[1]++;
	}
}


void EditorInputMaze(SDL_Event e, Maze* maze, int* index, int select){
	int x = e.motion.x; //admetons que l'user clique en 80*80
	int y = e.motion.y;// ma taille de bloc est de 8, donc normalement c'est la case 10-10 ou 9-9 selon les points de vue
	x = x / _TailleBloc;// Donc, la case cliquée est probablement case[9][9] nah ?
	y = y / _TailleBloc;//Bah nah, car si l'user depalce la camera, tout change
	x = x + index[1];//du coup je prends ça en compte
	y = y + index[0];//

	int *z = maze->GetDim();//Maintenant, je regarde si la case existe et si l'user a pas clique dans le vide
	if (x < z[1] && y < z[0]){
		Case& fnord = maze->GetCase(y, x);
		fnord.SetType(select);
	}
}

int EditorInputGUI(SDL_Event e){
	if (e.motion.x > 45 && e.motion.x < 89 && e.motion.y > 527 && e.motion.y <544){//save
		return 1;
	}
	if (e.motion.x > 20 && e.motion.x < 125 && e.motion.y > 550 && e.motion.y <570){//save&quit
		return 2;
	}
	if (e.motion.x > 45 && e.motion.x < 86 && e.motion.y > 573){//quit
		return 3;
	}
	if (e.motion.x > 174 && e.motion.x < 196 && e.motion.y > 575){//up
		return 4;
	}
	if (e.motion.x > 232 && e.motion.x < 286 && e.motion.y > 575){//down
		return 5;
	}
	if (e.motion.x > 308 && e.motion.x < 352 && e.motion.y > 575){//left
		return 6;
	}
	if (e.motion.x > 391 && e.motion.x < 447 && e.motion.y > 575){//right
		return 7;
	}

	if (e.motion.x > 519 && e.motion.x < 590 && e.motion.y > 525 && e.motion.y <548){//wall
		return 8;
	}
	if (e.motion.x > 647 && e.motion.x < 715 && e.motion.y > 525 && e.motion.y <548){//free
		return 9;
	}
	if (e.motion.x > 519 && e.motion.x < 590 && e.motion.y > 562 && e.motion.y < 591){//start
		return 10;
	}
	if (e.motion.x > 647 && e.motion.x < 715 && e.motion.y > 562 && e.motion.y < 591){//end
		return 11;
	}

}


void EditorFullMazeAfficher(SDL_Window* fen, SDL_Renderer* ren, Maze* maze, int* index){
	SDL_Texture *background = Load("editor.png", ren);
	SDL_Texture *free = Load("free.png", ren);
	SDL_Texture *wall = Load("brick.png", ren);
	SDL_Texture *start = Load("start.png", ren);
	SDL_Texture *end = Load("arival.png", ren);
	Draw(background, ren, NULL, NULL);

	int *z = maze->GetDim();
	Case** y = maze->GetPlateau();
	int *x = new int[2];
	x[0] = z[0];
	x[1] = z[1];
	if (x[0] - index[0] > 64){
		//Si le plateau est trop grand pour la fenetre
		x[0] = 64;
	}
	if (x[1] - index[1] >99){
		x[1] = 99;
	}
	int k=-1;
	int l=-1;
	for (int i = index[0]; i < x[0]+index[0]; i++){
		l++;
		k=-1;
		for (int j = index[1]; j < x[1] + index[1]; j++){
			k++;
			switch (y[i][j].GetType()){
			case 0:
				Draw(free, ren, 8 * k, 8 * l);//Ce calcul vachement complexe permet de determiner l'emplacement de la case sur la fenetre
				break;
			case 1:
				Draw(wall, ren, 8 * k, 8 * l);//faut que j'arrête de denigrer ce que je fais à coup de sarcasme quand meme
				break;
			case 2:
				Draw(start, ren, 8 * k, 8 * l);//ça marche, et c'est pas trop sale
				break;
			case 3:
				Draw(end, ren, 8 * k, 8 * l);//pas trop
				break;//quand même y'a des fois j'ai abandonné l'idée d'essayer de comprendre et juste bruteforce les solutions eventuelles qui me passaient en tete
			default:
				break;
			}
		}
	}
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(free);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(start);
	SDL_DestroyTexture(end);
	SDL_RenderPresent(ren);
}
