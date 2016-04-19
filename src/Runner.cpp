#include "Runner.h"
#include "Player.h"
#include "Maze.h"
#include "Editor.h"
#include <string>
#include <iostream>
#include "Affichage.h"

using namespace std;

void RunnerMainMenu(SDL_Window* fen , SDL_Renderer* ren){
	SDL_RenderClear(ren);//déjà je nettoie;
	string foo;
	do{
		foo = InputDetector(fen, ren);
		foo = foo + ".maze";
	} while (!DoesFileExist(foo));
	Maze &maze = Lecteur(foo);
	if (maze.IsRunnable() == 0){
		RunnerMainMenu(fen, ren);//ça c'est de la boucle violente
	}
	RunnerFullMode(fen, ren, &maze);
}

void RunnerFullMode(SDL_Window* fen, SDL_Renderer* ren, Maze* maze){
	SDL_RenderClear(ren);
	Player MazeRunner = Player();
	maze->Playable();
	MazeRunner.SetDepart(*&maze);
	maze->Afficher();
	bool running = true;
	bool win = false;
	SDL_Event e;
	int* vue = MazeRunner.GetView(maze);
	RunnerSee(fen, ren, MazeRunner.GetView(maze));
	RunnerGUI(fen, ren);

	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				RunnerInputDetector(e, maze, &MazeRunner);
				RunnerSee(fen, ren, MazeRunner.GetView(maze));
				RunnerGUI(fen, ren);
				if (MazeRunner.Win(maze) == 1){
					running = false;
					win = true;
				}
			}//fin du  if
		}//fin de l'attente d'event
	}//fin de la boucle
	if (win == true){
		delete[] vue;
		FinishMenu(fen,ren);
	}
}

void FinishMenu(SDL_Window* fen, SDL_Renderer* ren){
	SDL_RenderClear(ren);
	SDL_Texture *wall = Load("wall.bmp", ren);
	SDL_Texture *titre = Write("You win", ren);
	Draw(wall, ren, NULL, NULL);//mainteant, j'affiche le tout à sa place.
	Draw(titre, ren, 240, 100);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(titre);
	int clique = 0;
	bool running = true;
	SDL_Event e;
	while (running){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_MOUSEBUTTONDOWN){
				clique++;
			}//fin du  if
			if (e.type == SDL_MOUSEBUTTONDOWN && clique > 3){
				running = false;
				MainAffichage(fen, ren);
			}//fin du  if
		}//fin de l'attente d'event
	}//fin de la boucle
}

void RunnerInputDetector(SDL_Event e, Maze* maze, Player* MazeRunner){
	if (e.motion.y >= 575){//bon je check les boutons maintenant
		if (e.motion.x < 30){
			MazeRunner->Move(0, maze);
		}
		if (e.motion.x > 60 && e.motion.x < 116){
			MazeRunner->Move(1, maze);
		}

		if (e.motion.x > 136 && e.motion.x < 183){
			MazeRunner->Move(2, maze);
		}
		if (e.motion.x > 219 && e.motion.x < 275){
			MazeRunner->Move(3, maze);
		}
		if (e.motion.x > 585 && e.motion.x < 630){
			MazeRunner->Turn(0, maze);
		}
		if (e.motion.x > 665 && e.motion.x < 722){
			MazeRunner->Turn(1, maze);
		}

	}

}

void RunnerSee(SDL_Window* fen, SDL_Renderer* ren, int* vue){
	SDL_RenderClear(ren);//déjà je nettoie;
	SDL_Texture *back = Load("000.png", ren);
	cout << vue[0] << " " << vue[1] << " " << vue[2]<<endl;
	if (vue[0] != 1 && vue[1] != 1 && vue[2] != 1){
		back = Load("000.png", ren);
	}
	if (vue[0] == 1 && vue[1] != 1 && vue[2] != 1){
		back = Load("100.png", ren);
	}
	if (vue[0] == 1 && vue[1] == 1 && vue[2] != 1){
		back = Load("110.png", ren);
	}
	if (vue[0] != 1 && vue[1] == 1 && vue[2] != 1){
		back = Load("010.png", ren);
	}
	if (vue[0] != 1 && vue[1] == 1 && vue[2] == 1){
		back = Load("011.png", ren);
	}
	if (vue[0] != 1 && vue[1] != 1 && vue[2] == 1){
		back = Load("001.png", ren);
	}
	if (vue[0] == 1 && vue[1] != 1 && vue[2] == 1){
		back = Load("101.png", ren);
	}
	if (vue[0] == 1 && vue[1] == 1 && vue[2] == 1){
		back = Load("111.png", ren);
	}
	Draw(back, ren, 0, 0);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(back);
}


void RunnerGUI(SDL_Window* fen, SDL_Renderer* ren){
	SDL_Texture *gui= Load("gui.png ",ren);
	Draw(gui, ren, 0, 520);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(gui);
}