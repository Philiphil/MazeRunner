#include "Player.h"
#include "Maze.h"
#include "Case.h"
#include <iostream>

using namespace std;
Player::Player(){
	Regard = new int[2];
}

Player::~Player(){
	delete[] Regard;
}

void Player::SetDepart(Maze* maze){
	// Parmis les case du tableau, le 2 est le point de depart
	// du coup je le cherche et tout.
	Case** x = maze->GetPlateau();
	int* y = maze->GetDim();
	for (int i = 0; i < y[0]; i++)
	{
		for (int j = 0; j < y[1]; j++)
		{
			int z = x[i][j].GetType();// knock knock 
			if (z == 2){//sarah connor ?
				PosX = i;
				PosY = j;
			}//finduif
		}//findupremierfor
	}//findelagrosseboucle
	//Maintenant c'est la partie rigolote experimentale que je vais tester pendant des heures à la console
	//gerer la vue
	Regard[0] = PosX-1;
	Regard[1] = PosY;
}


int* Player::GetView(Maze* maze){
	int* retour = new int[3];
	
	if (Regard[0] == PosX){
		if (Regard[1] < PosY){
			Case& fnord = maze->GetCase(PosX + 1, PosY);
			retour[0] = fnord.GetType();
			Case& foobar = maze->GetCase(Regard[0], Regard[1]);
			retour[1] = foobar.GetType();
			Case& foo = maze->GetCase(PosX - 1, PosY);
			retour[2] = foo.GetType();
		}
		else if (Regard[1] > PosY){
			Case& fnord = maze->GetCase(PosX - 1, PosY);
			retour[0] = fnord.GetType();
			Case& foobar = maze->GetCase(Regard[0], Regard[1]);
			retour[1] = foobar.GetType();
			Case& foo = maze->GetCase(PosX + 1, PosY);
			retour[2] = foo.GetType();
		}
	}
	else if (Regard[1] == PosY){
		if (Regard[0] < PosX){
			Case& fnord = maze->GetCase(PosX, PosY - 1);
			retour[0] = fnord.GetType();
			Case& foobar = maze->GetCase(Regard[0], Regard[1]);
			retour[1] = foobar.GetType();
			Case& foo = maze->GetCase(PosX, PosY + 1);
			retour[2] = foo.GetType();
		}
		else if (Regard[0]> PosX){
			Case& fnord = maze->GetCase(PosX, PosY + 1);
			retour[0] = fnord.GetType();
			Case& foobar = maze->GetCase(Regard[0], Regard[1]);
			retour[1] = foobar.GetType();
			Case& foo = maze->GetCase(PosX, PosY - 1);
			retour[2] = foo.GetType();
		}
	}
	return retour;
}

void Player::Move(int x, Maze* maze){
	if (x == 0){
		Up(maze);
	}
	if (x == 1){
		Down(maze);
	}
	if (x == 2){
		Left(maze);
	}
	if (x == 3){
		Right(maze);
	}
}

void Player::Up(Maze* maze){
	int px=PosX;
	int py=PosY;
	Case& fnord = maze->GetCase(Regard[0], Regard[1]);
	if (fnord.GetType() != 1){
		PosX = Regard[0];
		PosY = Regard[1];
	}
	/**/
	if (px == Regard[0]){
		if (py < Regard[1]){

			Regard[0] = Regard[0];
			Regard[1] = PosY+1;
		}
		if (py > Regard[1]){
			Regard[0] = Regard[0];
			Regard[1] = PosY-1;
		}
	}
	else if (py == Regard[1]){
		if (px < Regard[0]){
			Regard[0] = PosX +1;
			Regard[1] = Regard[1];
		}
		if (px > Regard[0]){
			Regard[0] = PosX-1;
			Regard[1] = Regard[1];
		}
	}
}

void Player::Down(Maze* maze){
	int px;
	int py;
	if (PosY == Regard[1]){//ici c'est comme partout je dois tout calculer
		if (PosX > Regard[0])
		{//j'ai globalement tout tester jusqu'à ce que ça marche alors bon
			px = PosX + 1;//mais ça marche
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				PosX++;
				Regard[0]++;
			}
		}
		if (PosX < Regard[0])
		{
			px = PosX - 1;
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				PosX--;
				Regard[0]--;
			}
		}
	}
	if (PosX == Regard[0]){
		if (PosY > Regard[1])
		{
			py = PosY + 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
			{
				Regard[1]++;
				PosY++;
			}
		}
		if (PosY < Regard[1])
		{
			py = PosY - 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
				{
					Regard[1]--;
					PosY--;
				}
		}
	}
}

void Player::Left(Maze* maze){
	int px;
	int py;
	if (PosY == Regard[1]){
		if (PosX > Regard[0])
		{
			py = Regard[1] - 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
			{
				Regard[1]--;
				PosY--;
			}

		}
		if (PosX < Regard[0])
		{
			py = Regard[1] + 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
			{
				Regard[1]++;
				PosY++;
			}

		}
	}
	if (PosX == Regard[0]){
		if (PosY > Regard[1])
		{
			px = Regard[0] + 1;
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				Regard[0]++;
				PosX++;
			}
		}
		if (PosY < Regard[1])
		{
			px = Regard[0] - 1;
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				Regard[0]--;
				PosX--;
			}
		}
	}
}

void Player::Right(Maze* maze){
	int px;
	int py;
	if (PosY == Regard[1]){
		if (PosX > Regard[0])
		{
			py = Regard[1] + 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
			{
				Regard[1]++;
				PosY++;
				Case& fnord = maze->GetCase(Regard[0], Regard[1]);
			}

		}
		if (PosX < Regard[0])
		{
			py = Regard[1] - 1;
			Case& fnord = maze->GetCase(PosX, py);
			if (fnord.GetType() != 1)
			{
				Regard[1]--;
				PosY--;
			}

		}
	}
	if (PosX == Regard[0]){
		if (PosY > Regard[1])
		{
			px = Regard[0] - 1;
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				Regard[0]--;
				PosX--;
			}
		}
		if (PosY < Regard[1])
		{
			px = Regard[0] + 1;
			Case& fnord = maze->GetCase(px, PosY);
			if (fnord.GetType() != 1)
			{
				Regard[0]++;
				PosX++;
			}
		}
	}
}



void Player::Turn(int x, Maze* maze){
	if (x == 0){
		if (PosX == Regard[0])
		{
			if (PosY < Regard[1]){
				Regard[0] = PosX - 1;
				Regard[1] = PosY;
			}
			if (PosY > Regard[1]){
				Regard[0] = PosX+1;
				Regard[1] = PosY;
			}
		}else
		{
			if (PosX < Regard[0]){
				Regard[0] = PosX;
				Regard[1] = PosY + 1;
			}
			if (PosX > Regard[0]){
				Regard[0] = PosX;
				Regard[1] = PosY - 1;
			}
		}
	}
	if (x == 1){
		if (PosX == Regard[0])
		{
			if (PosY < Regard[1]){
				Regard[0] = PosX + 1;
				Regard[1] = PosY;
			}
			if (PosY > Regard[1]){
				Regard[0] = PosX - 1;
				Regard[1] = PosY;
			}
		}
		else
		{
			if (PosX < Regard[0]){
				Regard[0] = PosX;
				Regard[1] = PosY - 1;
			}
			if (PosX > Regard[0]){
				Regard[0] = PosX;
				Regard[1] = PosY + 1;
			}
		}
	}
}

void Player::DebugConsole(Maze* maze){

	Case& fnord = maze->GetCase(PosX, PosY);
	fnord.SetType(7);
	Case& foo = maze->GetCase(Regard[0], Regard[1]);
	foo.SetType(8);
}

int Player::Win(Maze* maze){
	Case& fnord = maze->GetCase(PosX, PosY);
	if (fnord.GetType() == 3){
		return 1;
	}
	else{
		return 0;
	}
}