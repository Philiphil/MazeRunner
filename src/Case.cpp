#include <iostream>
#include <Windows.h>
#include "Case.h"

using namespace std;

Case::Case(){
	Type = 0;
}

int Case::GetType(){
	return Type;
}

void Case::SetType(int foo){
	Type = foo;
}
