#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>



class Battlefield
{
	int **field;
	int **idBot;
	int **mask;
	int size;
	
public:
	Battlefield(){}
	Battlefield(int size);
	
	void showBattleField(int size);
	void addID(int xx, int yy, int id);
	void clearID(int xx, int yy, int id);
	void moveID(int xx, int yy, int xxN, int yyN, int id);
	void checkNeighborhood(int xx, int yy);
	int** returnMask(int xx, int yy);
	void clearMask();
	int returnValue(int xx, int yy);

friend class Character;
};


int Battlefield::returnValue(int xx, int yy)
{
	return field[yy][xx];
}


int **Battlefield::returnMask(int xx, int yy)
{
	checkNeighborhood(xx, yy);
	return mask;
}


void Battlefield::clearMask()
{
	for(int k = 0; k < 3; ++k)
	for(int j = 0; j < 3; ++j)
	field[k][j] = 0;

	return;
}


void Battlefield::checkNeighborhood(int xx, int yy)
{
	clearMask();

	if( xx == 0 && yy == 0)
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if( i == 0 || j == 0)
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];

	return;		
	}
	else if(xx == 0 && yy == (size-1))
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if( i == 0 || j == 2)
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];
	
	return;
	}
	else if(xx == (size-1) && yy == (size-1))
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if( i == 2 || j == 2)
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];
	
	return;
	}
	else if(xx == (size-1) && yy == 0)
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if( i == 2 || j == 0)
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];
	
	return;
	}
	else if(yy == 0)
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if(j == 0 )
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];

	return;
	}
	else if(xx == 0)
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if(i == 0 )
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];

	return;
	}
	else if(yy == (size-1))
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if(j == 2 )
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];

	return;
	}
	else if(xx == (size-1))
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		if(i == 2 )
		mask[j][i] = -9;
		else
		mask[j][i] = field[yy+j-1][xx+i-1];

	return;
	}
	else
	{
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		mask[j][i] = field[yy+j-1][xx+i-1];
	
	return;
	}
	
	
}


void Battlefield::moveID(int xx, int yy, int xxN, int yyN, int id)
{	
	int val;

	if(field[yyN][xxN] == 0 && returnValue(xx,yy) == id )
	{
		field[yyN][xxN] = id;
		field[yy][xx] = 0;
	}
	else if(field[yyN][xxN] == 0 && returnValue(xx,yy) != id)
	{
		field[yyN][xxN] = id;
	}
	else if(field[yyN][xxN] != 0 && returnValue(xx,yy) == id)
	{
		field[yy][xx] = 0;
	}
	return;
}


void Battlefield::clearID(int xx, int yy, int id)
{
	field[yy][xx] = 0;
	
	return;
}

void Battlefield::addID(int xx, int yy, int id)
{
	if(field[yy][xx] != 0)
	return;
	else
	field[yy][xx] = id;

	return;
}

Battlefield::Battlefield(int _size)
{
	size = _size;
	field = new int*[size];
	for(int i = 0; i < size; ++i)
	{
		field[i] = new int[size];
		for(int j = 0; j < size; ++j)
		field[i][j] = 0;		
	}
	mask = new int*[3];
	for(int k = 0; k < 3; ++k)
	{
		mask[k] = new int[3];
		for(int j = 0; j < 3; ++j)
		mask[k][j] = 0;
	}
}


void Battlefield::showBattleField(int size)
{	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			std::cout << field[i][j];
		}
		std::cout <<std::endl;
	}
}
