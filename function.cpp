#include <iostream>

#define N 450

int squarConverterX(double xx)
{
	xx = (xx/N)*10;
	int xi = floor(xx);

	return xi;
}


int squarConverterY(double yy)
{
	yy = (yy/N)*10;
	int yi = floor(yy);

	return yi;
}
