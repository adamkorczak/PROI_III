#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <unistd.h>
#include "function.cpp"



class Character
{

protected:

	int id;
	int hpUnit;
	int hp;
	int quantity;
	int x;
	int y;
	int **neighborhood;
	
public:	
	sf::Font font;
	sf::Text atext;
	sf::Text sigh;
	std::ostringstream ss;

	Character();
	Character(int _id, int _hpUnit, int _quantity, int _x, int _y);
	
		
	virtual ~Character(){}

	int getX();
	int getY();
	int getID();
	void set(int, int, Battlefield &BF);
	void move(int, int, Battlefield &BF);
	void locateInBTF(Battlefield &BF);
	void changeLocateInBTF(Battlefield &BF);
	void checkNeighborhood(Battlefield &BF);
	void showMask();
	void showHP();
	void drawHP(sf::RenderWindow &D);
	void drawSelected(sf::RenderWindow &D);
	
	virtual void drawOjb(sf::RenderWindow &D) = 0;	
	virtual void attack(Character &D, int dx, int dy) = 0;
	virtual	void defend(int dmg) = 0;

};


Character::Character(int _id, int _hpUnit, int _quantity, int _x, int _y)
:	id(_id), hpUnit(_hpUnit), quantity(_quantity), x(_x), y(_y)
{
	hp = hpUnit*quantity;
	neighborhood = new int*[3];
	for(int k = 0; k < 3; ++k)
	{
		neighborhood[k] = new int[3];
		for(int j = 0; j < 3; ++j)
		neighborhood[k][j] = 0;
	}
	font.loadFromFile("Kingthings Petrock light.ttf");
	atext.setFont(font);
	atext.setCharacterSize(16);
	atext.setColor(sf::Color::Green);
	sigh.setFont(font);
	sigh.setCharacterSize(16);
	sigh.setColor(sf::Color::Red);
}


void Character::drawSelected(sf::RenderWindow &D)
{
	ss << "!";
	sigh.setString(ss.str());
	sigh.setPosition(x,y-2);
	D.draw(sigh);
	ss.str("");

}


void Character::drawHP(sf::RenderWindow &D)
{
	ss << quantity;
	atext.setString(ss.str());
	atext.setPosition(x+25,y+2);
	D.draw(atext);
	ss.str("");

}

void Character::showHP()
{
	std::cout << hp <<"\t"<< quantity << std::endl;
}


void Character::showMask()
{

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			std::cout << neighborhood[i][j];
		}
		std::cout <<std::endl;
	}
}


int Character::getID()
{
	return id;
}


void Character::checkNeighborhood(Battlefield &BF)
{
	neighborhood = BF.returnMask(squarConverterX(getX()), squarConverterY(getY()));

	return;

}


void Character::locateInBTF(Battlefield &BF)
{	
	BF.addID(squarConverterX(getX()), squarConverterY(getY()), getID());
	return;
}


void Character::move(int xx, int yy, Battlefield &BF)
{
	BF.moveID(squarConverterX(x),squarConverterY(y),squarConverterX(x+xx),squarConverterY(y+yy),id);
	x = x + xx;
	y = y + yy;
	locateInBTF(BF);
	checkNeighborhood(BF);

	return;
}


void Character::set(int xx, int yy, Battlefield &BF)
{
	BF.clearID(squarConverterX(x),squarConverterY(y),id);
	x =  xx;
	y =  yy;
	locateInBTF(BF);

	return;
}

int Character::getX()
{
	return x;
}


int Character::getY()
{
	return y;
}


class Warrior
	: public Character
{
	int dmg;
	int def;


public:

	sf::Texture knightTexture;
	sf::Sprite tempTexture;

	Warrior(int _id, int _quantity, int _x, int _y)
	:	Character(_id, 1200, _quantity, _x, _y)
	{	dmg = 1000; def = 250;
		if(_x == 0)
		knightTexture.loadFromFile( "knight.png" );
		else
		knightTexture.loadFromFile( "knight_right.png" );
	}

	void drawOjb(sf::RenderWindow &D);
	void attack(Character &D, int dx, int dy);
	void defend(int dmg);

};


void Warrior::attack(Character &D, int dx, int dy)
{
	//std::cout << squarConverterX(dx) <<"\t"<<squarConverterY(dy)<<std::endl;
	if((squarConverterX(dx) == 1) || (squarConverterY(dy) == 1))
	{
		D.defend(dmg);	
	}
	

}

void Warrior::defend(int dmg)
{
	hp = hp - (dmg -def);
	quantity = ceil(hp/hpUnit);
}

void Warrior::drawOjb(sf::RenderWindow &D)
{
	
	tempTexture.setTexture(knightTexture);
	tempTexture.setPosition(getX(),getY());
	D.draw( tempTexture );			
}



class Paladin
	: public Character
{
	int dmg;
	int def;


public:

	sf::Texture paladinTexture;
	sf::Sprite tempTexture;

	Paladin(int _id, int _quantity, int _x, int _y)
	:	Character(_id, 1200, _quantity, _x, _y)
	{	dmg = 1000; def = 100;
		if(_x == 0)
		paladinTexture.loadFromFile( "Paladin.png" );
		else
		paladinTexture.loadFromFile( "Paladin_right.png" );
	}
	void drawOjb(sf::RenderWindow &D);
	void attack(Character &D, int dx, int dy);
	void defend(int dmg);
};


void Paladin::attack(Character &D, int dx, int dy)
{
		D.defend(5*dmg/(abs(squarConverterX(dx)) + abs(squarConverterY(dy))));	
}


void Paladin::defend(int dmg)
{
	hp = hp - (dmg -def);
	quantity = ceil(hp/hpUnit);

}
void Paladin::drawOjb(sf::RenderWindow &D)
{

	tempTexture.setTexture(paladinTexture);
	tempTexture.setPosition(getX(),getY());
	D.draw( tempTexture );		
}


