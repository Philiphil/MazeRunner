#ifndef __CASE__
#define __CASE__

class Case{
	/*
	Maze est un tableau de Case.
	*/
private:
	/*
	0=free
	1=wall
	2=start point
	3 = end point
	*/
	int Type;
public:
	Case();
	int GetType();
	void SetType(int);
};


#endif