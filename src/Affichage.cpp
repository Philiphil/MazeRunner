#include <SDL2/SDL.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Affichage.h"
#include "Editor_Affichage.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Runner.h"

/*
SDL_DestroyTexture(tex);
SDL_DestroyRenderer(ren);
SDL_DestroyWindow(win);
IMG_Quit();
SDL_Quit();
*/

using namespace std;

void startmenu()
{
	//Donc, je commence par intialiser une fenetre 
	SDL_Window* fen = NULL;
	fen = SDL_CreateWindow("Maze Runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	//Un render pour afficher
	SDL_Renderer *ren = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	MainAffichage(fen, ren);
}

void MainAffichage(SDL_Window* fen, SDL_Renderer* ren){
	//j'initialise toutes les textures
	SDL_Texture *wall = Load("wall.bmp", ren);
	SDL_Texture *titre = Load("titre.png", ren);
	SDL_Texture *credit = Load("credit.png", ren);
	SDL_Texture *run = Load("run.png", ren);
	SDL_Texture *edit = Load("edit.png", ren);
	SDL_Texture *quit = Load("quit.png", ren);
	//au passage, c'est moi où le menu est assez stylé ?
	SDL_RenderClear(ren);
	Draw(wall, ren, NULL, NULL);//mainteant, j'affiche le tout à sa place.
	Draw(titre, ren, 160, 15);
	Draw(credit, ren, 200, 570);
	Draw(run, ren, 345, 248);
	Draw(edit, ren, 345, 325);
	Draw(quit, ren, 345, 410);
	SDL_RenderPresent(ren);
	bool running = true;
	SDL_Event e;
	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){//puis j'attends que l'user clique
				int x = MainMenuInputDetector(e.motion.x, e.motion.y);//je detecte sur quoi
				if (x != 0){//si l'user a pas cliqué dans le vide
					running = false; //(bon bah je quitte la boucle déjà)
					//bon, bah ces textures que je me suis cassé le cul à creer et à placer proprement je peux les enlever
					SDL_DestroyTexture(wall);
					SDL_DestroyTexture(titre);
					SDL_DestroyTexture(credit);
					SDL_DestroyTexture(run);
					SDL_DestroyTexture(edit);
					SDL_DestroyTexture(quit);
					switch (x)
					{
					case 1:
						RunnerMainMenu(fen, ren);
						break;
					case 2:
						EditorMainMenu(fen, ren);
						break;
					case 3:
						Fermeture(fen, ren);
						break;
					}
				}
			}
		}
	}
}

SDL_Texture* Load(string fichier, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, fichier.c_str());
	return texture;
}

void Draw(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

int MainMenuInputDetector(int x, int y){
	/*
	Ouais, il y a surrement plus optis et propre, et je vais sans doute devoir faire plus optis et propre apres justement
	Mais bon, ici ça passe	
	*/
	if (x < 340 || x > 460){//en gros je regarde la position  de la sourie au moment du clic
		return 0;//ensuite je  compare aux emplacements de bouton
	}
	if (y > 250 && y < 300){
		return 1;
	}
	if (y > 330 && y < 385){
		return 2;
	}
	if (y > 410 && y < 470){
		return 3;
	}
	return 0;
}

void Fermeture(SDL_Window* win, SDL_Renderer* ren){
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	exit(1);
}

string InputDetector(SDL_Window* fen, SDL_Renderer* ren){
	//ici on va gerer l'affichage de chaque menu qui necessite que l'user ecrive
	TTF_Init();
	SDL_RenderClear(ren);//déjà je nettoie;
	SDL_Texture *wall = Load("wall.bmp", ren);
	SDL_Texture *file = Load("file.png", ren);
	SDL_Texture *back = Write("Back", ren);

	Draw(wall, ren, NULL, NULL);
	Draw(file, ren, 210, 100);
	Draw(back, ren, 100, 450);
	SDL_RenderPresent(ren);
	bool running = true;
	SDL_Event e;
	/**/
	string ligne = "";
	SDL_Texture *texte=nullptr;
	/**/
	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				if (e.motion.x > 105 && e.motion.x < 250 && e.motion.y >405 && e.motion.y < 505){
					SDL_DestroyTexture(wall);
					SDL_DestroyTexture(back);
					if (texte != nullptr){
						SDL_DestroyTexture(texte);
					}
					SDL_DestroyTexture(file);
					MainAffichage(fen,ren);
				}
			}
			if (e.type == SDL_KEYDOWN){
				/*si l'utilisateur appuie sur son clavier*/
				if (InputValidator(e) ==1){
					ligne = ligne + InputAlgo(e);;
					texte = Write(ligne, ren);
					SDL_RenderClear(ren);
					Draw(wall, ren, NULL, NULL);
					Draw(texte, ren, (300-(20*ligne.length()/2)), 250);//ce calcul savant permet de centrer le texte
					Draw(file, ren, 210, 100);
					Draw(back, ren, 100, 450);
					SDL_RenderPresent(ren);
				}
				else if (InputValidator(e) == 3){// si l'user appuie sur retour
					ligne = ligne.substr(0, ligne.length() - 1);//Cette fonction savante permet de supprimer la derniere lettre tapée
					texte = Write(ligne, ren);
					SDL_RenderClear(ren);
					Draw(wall, ren, NULL, NULL);
					Draw(texte, ren, (300 - (20 * ligne.length() / 2)), 250);
					Draw(file, ren, 210, 100);
					Draw(back, ren, 100, 450);
					SDL_RenderPresent(ren);
				}
				else if (InputValidator(e) == 2){
					running = false;
					}
			}//typevent
		}//event
	}//running
	//Bon maintenant je vais m'eclater à delete chaque pointeur
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(back);
	SDL_DestroyTexture(texte);
	SDL_DestroyTexture(file);
	return ligne;
}

int InputValidator(SDL_Event e){
	//Bon, comme on peut pas mettre n'importe quoi en nom de fichier, je vais definir de maniere un poil stricte ce qui peut entrer
	int x;
	switch (e.key.keysym.scancode)
	{
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_Z:
		case SDL_SCANCODE_E:
		case SDL_SCANCODE_R:
		case SDL_SCANCODE_T:
		case SDL_SCANCODE_Y:
		case SDL_SCANCODE_U:
		case SDL_SCANCODE_I:
		case SDL_SCANCODE_O:
		case SDL_SCANCODE_P:
		case SDL_SCANCODE_Q:
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_F:
		case SDL_SCANCODE_G:
		case SDL_SCANCODE_H:
		case SDL_SCANCODE_J:
		case SDL_SCANCODE_K:
		case SDL_SCANCODE_L:
		case SDL_SCANCODE_SEMICOLON:
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_X:
		case SDL_SCANCODE_C:
		case SDL_SCANCODE_V:
		case SDL_SCANCODE_B:
		case SDL_SCANCODE_N:
		case SDL_SCANCODE_KP_1:
		case SDL_SCANCODE_KP_2:
		case SDL_SCANCODE_KP_3:
		case SDL_SCANCODE_KP_4:
		case SDL_SCANCODE_KP_5:
		case SDL_SCANCODE_KP_6:
		case SDL_SCANCODE_KP_7:
		case SDL_SCANCODE_KP_8:
		case SDL_SCANCODE_KP_9:
		case SDL_SCANCODE_0:
		case SDL_SCANCODE_KP_0:
		case SDL_SCANCODE_1:
		case SDL_SCANCODE_2:
		case SDL_SCANCODE_3:
		case SDL_SCANCODE_4:
		case SDL_SCANCODE_5:
		case SDL_SCANCODE_6:
		case SDL_SCANCODE_7:
		case SDL_SCANCODE_8:
		case SDL_SCANCODE_9:
			x = 1;
			break;
		case SDL_SCANCODE_KP_ENTER :
		case SDL_SCANCODE_RETURN:
			x = 2;
			break;
		case SDL_SCANCODE_BACKSPACE:
			x = 3;
			break;
		default:
			x = 0;
			break;
	}
	return x;
}

string InputAlgo(SDL_Event e){
	string foo;
	switch (e.key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		foo = "q";
		break;
	case SDL_SCANCODE_Z:
		foo = "w";
		break;
	case SDL_SCANCODE_E:
		foo = "e";
		break;
	case SDL_SCANCODE_R:
		foo = "r";
		break;
	case SDL_SCANCODE_T:
		foo = "t";
		break;
	case SDL_SCANCODE_Y:
		foo = "y";
		break;
	case SDL_SCANCODE_U:
		foo = "u";
		break;
	case SDL_SCANCODE_I:
		foo = "i";
		break;
	case SDL_SCANCODE_O:
		foo = "o";
		break;
	case SDL_SCANCODE_P:
		foo = "p";
		break;
	case SDL_SCANCODE_Q:
		foo = "a";
		break;
	case SDL_SCANCODE_S:
		foo = "s";
		break;
	case SDL_SCANCODE_D:
		foo = "d";
		break;
	case SDL_SCANCODE_F:
		foo = "f";
		break;
	case SDL_SCANCODE_G:
		foo = "g";
		break;
	case SDL_SCANCODE_H:
		foo = "h";
		break;
	case SDL_SCANCODE_J:
		foo = "j";
		break;
	case SDL_SCANCODE_K:
		foo = "k";
		break;
	case SDL_SCANCODE_L:
		foo = "l";
		break;
	case SDL_SCANCODE_SEMICOLON:
		foo = "m";
		break;
	case SDL_SCANCODE_W:
		foo = "z";
		break;
	case SDL_SCANCODE_X:
		foo = "x";
		break;
	case SDL_SCANCODE_C:
		foo = "c";
		break;
	case SDL_SCANCODE_V:
		foo = "v";
		break;
	case SDL_SCANCODE_B:
		foo = "b";
		break;
	case SDL_SCANCODE_N:
		foo = "n";
		break;
	case SDL_SCANCODE_1:
	case SDL_SCANCODE_KP_1:
		foo = "1";
		break;
	case SDL_SCANCODE_2:
	case SDL_SCANCODE_KP_2:
		foo = "2";
		break;
	case SDL_SCANCODE_3:
	case SDL_SCANCODE_KP_3:
		foo = "3";
		break;
	case SDL_SCANCODE_4:
	case SDL_SCANCODE_KP_4:
		foo = "4";
		break;
	case SDL_SCANCODE_5:
	case SDL_SCANCODE_KP_5:
		foo = "5";
		break;
	case SDL_SCANCODE_6:
	case SDL_SCANCODE_KP_6:
		foo = "6";
		break;
	case SDL_SCANCODE_7:
	case SDL_SCANCODE_KP_7:
		foo = "7";
		break;
	case SDL_SCANCODE_8:
	case SDL_SCANCODE_KP_8:
		foo = "8";
		break;
	case SDL_SCANCODE_9:
	case SDL_SCANCODE_KP_9:
		foo = "9";
		break;
	case SDL_SCANCODE_0:
	case SDL_SCANCODE_KP_0:
		foo = "0";
		break;
	}
	return foo;
}

SDL_Texture* Write(const string &input, SDL_Renderer *ren){
	TTF_Font *font = TTF_OpenFont("font.ttf", 70);//je fais pop une font;
	SDL_Color noir = { 0, 0, 0 };//je la met en noir
	//je commence à aimer vachement la sdl/
	SDL_Surface *surface = TTF_RenderText_Blended(font, input.c_str(), noir);//Boom, je fais pop une surface.
	SDL_Texture *texte = SDL_CreateTextureFromSurface(ren, surface);//puis la texture
	SDL_FreeSurface(surface);//pointeur nettoyé
	TTF_CloseFont(font);//font nettoyé
	return texte;
}