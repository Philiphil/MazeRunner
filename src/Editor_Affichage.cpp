#include <string>
#include <SDL2/SDL.h>
#include "Editor_Affichage.h"
#include "Editor.h"
#include "Affichage.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Maze.h"
#include "EditorFull.h"

using namespace std;

void EditorMainMenu(SDL_Window* fen, SDL_Renderer* ren){
	SDL_RenderClear(ren);//déjà je nettoie;
	SDL_Texture *wall = Load("wall.bmp", ren);
	SDL_Texture *edit = Load("edit.png", ren);
	SDL_Texture *newx = Load("new.png", ren);
	SDL_Texture *back = Load("back.png", ren);
	Draw(wall, ren, NULL, NULL);
	Draw(newx, ren, 345, 248);
	Draw(edit, ren, 345, 325);
	Draw(back, ren, 345, 410);
	SDL_RenderPresent(ren);
	bool running = true;
	SDL_Event e;
	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				int x = MainMenuInputDetector(e.motion.x, e.motion.y);
				if (x != 0){
					running = false;
					SDL_DestroyTexture(wall);
					SDL_DestroyTexture(newx);
					SDL_DestroyTexture(edit);
					SDL_DestroyTexture(back);
					switch (x)
					{
					case 1:
						EditorNewAffichage(fen, ren);
						break;
					case 2:
						EditorEditAffichage(fen, ren);
						break;
					case 3:
						MainAffichage(fen, ren);
						break;
					}//fin du switch
				}//fin du if
			}//fin du second if
		}//fin de l'attente d'event
	}//fin de la boucle
}

void EditorNewAffichage(SDL_Window* fen, SDL_Renderer* ren){
	string foo;
	do{
		foo = InputDetector(fen, ren);
		foo = foo + ".maze";
	} while (DoesFileExist(foo));//tant que le fichier existe, donc run qu'une fois à moins que
	int x = EditorXY(fen, ren, "x");
	int y = EditorXY(fen, ren, "y");
	Maze *maze = new Maze(y, x);//creation du labyrinthe
	Sauvegardeur(maze, foo);
	EditFullMode(fen, ren, maze, foo);
}

void EditorEditAffichage(SDL_Window* fen, SDL_Renderer* ren){
	string foo;
	do{
		foo = InputDetector(fen, ren);
		foo = foo + ".maze";
	} while (!DoesFileExist(foo));
	Maze &maze = Lecteur(foo);
	EditFullMode(fen, ren, &maze, foo);
}

int EditorXY(SDL_Window* fen, SDL_Renderer* ren, string foo){
	//comme Input validator en gros
	SDL_RenderClear(ren);
	SDL_Texture *wall = Load("wall.bmp", ren);
	SDL_Texture *width;
	if (foo == "x"){
		width = Write("Width (best : 100)", ren);//maintenant que je sais faire ça, je suis deg d'avoir perdu  beaucoup de temps à les faire en image
	}
	else{
		width = Write("Height (best : 65)", ren);

	}
	Draw(wall, ren, NULL, NULL);
	Draw(width, ren, 200, 100);
	SDL_RenderPresent(ren);
	bool running = true;
	SDL_Event e;
	string ligne = "";
	SDL_Texture *texte;
	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_KEYDOWN){
				if (IntValidator(e) == 1){//intvalidator est plutot clair à comprendre je dirais
					ligne = ligne + InputAlgo(e);//pas besoin de redefinir ça.
					texte = Write(ligne, ren);
					SDL_RenderClear(ren);
					Draw(wall, ren, NULL, NULL);
					Draw(texte, ren, (300 - (20 * ligne.length() / 2)), 250);//ce calcul savant permet de centrer le texte
					Draw(width, ren, 200, 100);
					SDL_RenderPresent(ren);
				}
				else if (InputValidator(e) == 3){// si l'user appuie sur retour
					ligne = ligne.substr(0, ligne.length() - 2);//Cette fonction savante permet de supprimer la derniere lettre tapée
					texte = Write(ligne, ren);
					SDL_RenderClear(ren);
					Draw(wall, ren, NULL, NULL);
					Draw(texte, ren, (300 - (20 * ligne.length() / 2)), 250);
					Draw(width, ren, 200, 100);
					SDL_RenderPresent(ren);
				}
				else if (InputValidator(e) == 2){
					running = false;
				}
			}
		}//event
	}//running
	//Bon maintenant je vais m'eclater à delete chaque pointeur
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(texte);
	SDL_DestroyTexture(width);
	return stoi(ligne);
}

int IntValidator(SDL_Event e){
	//Bon, comme on peut pas mettre n'importe quoi en nom de fichier, je vais definir de maniere un poil stricte ce qui peut entrer
	int x;
	switch (e.key.keysym.scancode)
	{
	case SDL_SCANCODE_1:
	case SDL_SCANCODE_KP_1:
	case SDL_SCANCODE_2:
	case SDL_SCANCODE_KP_2:
	case SDL_SCANCODE_3:
	case SDL_SCANCODE_KP_3:
	case SDL_SCANCODE_4:
	case SDL_SCANCODE_KP_4:
	case SDL_SCANCODE_5:
	case SDL_SCANCODE_KP_5:
	case SDL_SCANCODE_6:
	case SDL_SCANCODE_KP_6:
	case SDL_SCANCODE_7:
	case SDL_SCANCODE_KP_7:
	case SDL_SCANCODE_8:
	case SDL_SCANCODE_KP_8:
	case SDL_SCANCODE_9:
	case SDL_SCANCODE_KP_9:
	case SDL_SCANCODE_0:
	case SDL_SCANCODE_KP_0:
		x = 1;
		break;
	case SDL_SCANCODE_KP_ENTER:
	case SDL_SCANCODE_RETURN:
		x = 2;
	case SDL_SCANCODE_DELETE:
		x = 3;
	default:
		x = 0;
		break;
	}
	return x;
}