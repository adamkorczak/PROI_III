#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <unistd.h>


#define N 450
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

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


class Battlefield
{
	int **field;
	int **idBot;	
	
public:
	Battlefield(){}
	Battlefield(int size);
	
	void showBattleField(int size);
	void addID(int xx, int yy, int id);
	void clearID(int xx, int yy, int id);
};

void Battlefield::clearID(int xx, int yy, int id)
{
	field[yy][xx] = 0;
	
	return;
}

void Battlefield::addID(int xx, int yy, int id)
{
	field[yy][xx] = id;

	return;
}

Battlefield::Battlefield(int size)
{

	field = new int*[size];
	for(int i = 0; i < size; ++i)
	{
		field[i] = new int[size];
		for(int j = 0; j < size; ++j)
		field[i][j] = 0;		
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


class Character
{
	int id;
	int hpUnit;
	int hp;
	int quantity;
	int x;
	int y;
	
public:	

	Character();
	Character(int _id, int _hpUnit, int _quantity, int _x, int _y)
	:	id(_id),
		hpUnit(_hpUnit),
		quantity(_quantity),
		x(_x),
		y(_y)
	{hp = hpUnit*quantity;}
		
	virtual ~Character(){}
	//virtual attack(int &param);
	//virtual deffend(int &param);
	int getX();
	int getY();
	int getID();
	void set(int, int, Battlefield &BF);
	void move(int, int, Battlefield &BF);
	void locateInBTF(Battlefield &BF);
	void changeLocateInBTF(Battlefield &BF);
	void checkNeighborhood(Battlefield &BF);
	
	virtual void drawOjb(sf::RenderWindow &D) = 0;	
	virtual void move(sf::RenderWindow &D, int xx, int yy) = 0;


};

int Character::getID()
{
	return id;
}



void Character::locateInBTF(Battlefield &BF)
{	
	BF.addID(squarConverterX(getX()), squarConverterY(getY()), getID());
	return;
}


void Character::move(int xx, int yy, Battlefield &BF)
{
	BF.clearID(squarConverterX(x),squarConverterY(y),id);
	x = x + xx;
	y = y + yy;
	locateInBTF(BF);
	
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
	{	dmg = 100; def = 25;
		if(_x == 0)
		paladinTexture.loadFromFile( "Paladin.png" );
		else
		paladinTexture.loadFromFile( "Paladin_right.png" );
	}
	void drawOjb(sf::RenderWindow &D);
	void move(sf::RenderWindow &D, int xx, int yy);

};

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
	{	dmg = 100; def = 25;
		if(_x == 0)
		knightTexture.loadFromFile( "knight.png" );
		else
		knightTexture.loadFromFile( "knight_right.png" );
	}
	void drawOjb(sf::RenderWindow &D);
	void move(sf::RenderWindow &D, int xx, int yy);

};


void Warrior::move(sf::RenderWindow &D, int xx, int yy)
{
	tempTexture.move(xx,yy);
	D.draw( tempTexture );	
}


void Paladin::move(sf::RenderWindow &D, int xx, int yy)
{
	tempTexture.move(xx,yy);
	D.draw( tempTexture );	
}

void Warrior::drawOjb(sf::RenderWindow &D)
{
	
	tempTexture.setTexture(knightTexture);
	tempTexture.setPosition(getX(),getY());
	D.draw( tempTexture );			
}


void Paladin::drawOjb(sf::RenderWindow &D)
{

	tempTexture.setTexture(paladinTexture);
	tempTexture.setPosition(getX(),getY());
	D.draw( tempTexture );		
}




class Player
{
	
public:

	int numTurn;
	int numChars;
	Character **playerChars;

	Player(int _side, sf::RenderWindow &D, Battlefield &BF);
	void move(sf::RenderWindow &D, Player &P,Battlefield &BF);
	void init();
	void drawAll(sf::RenderWindow &D);
	void animateWalking(sf::RenderWindow &D,int dx, int dy ,int, Player &P,Battlefield &BF);
	//void drawObjects(sf::RenderWindow &D);


};

void Player::animateWalking(sf::RenderWindow &D,int dx, int dy, int numTurn, Player &P, Battlefield &BF)
{
	for(int i = 0; i <abs(dx); ++i)
	{
		playerChars[numTurn]->move(abs(dx)/dx,0,BF);
		D.clear();
		drawAll(D);
		P.drawAll(D);
		D.display();
		usleep(2000);
		}

		for(int j = 0; j < abs(dy); ++j)
		{
		playerChars[numTurn]->move(0,abs(dy)/dy,BF);
		D.clear();
		drawAll(D);
		P.drawAll(D);
		D.display();
		usleep(2000);
		}
}


void Player::drawAll(sf::RenderWindow &D)
{
	
	for(int i = 0; i <numChars; ++i)
	playerChars[i]->drawOjb(D);
	return;
	
}


void Player::move(sf::RenderWindow &D, Player &P,Battlefield &BF)
{

	bool run = true;
	sf::Event action;
	int xx;
	int yy;
	int dx,dy;
	double buffX;
	double buffY;
	while(run)
	{	
		
			while(D.pollEvent(action))
			if(action.type == sf::Event::MouseButtonPressed &&
	 			action.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i positionMouse = sf::Mouse::getPosition(D);
				std::cout <<positionMouse.x << "\t" << positionMouse.y <<std::endl;

				buffX = ((double)positionMouse.x/N)*10;
				buffY = ((double)positionMouse.y/N)*10;
				xx = floor(buffX)*N/10;
				yy = floor(buffY)*N/10;
				std::cout << buffX << "\t" << buffY <<std::endl;
				std::cout << xx << "\t" << yy <<std::endl;
				dx = xx - playerChars[numTurn]->getX();
				dy = yy - playerChars[numTurn]->getY();
				animateWalking(D,dx,dy,numTurn,P,BF);
				
				
				
				
				
			
				run = false;
				if(numTurn < numChars - 1)
				numTurn++;
				else
				numTurn = 0;
				break;
			}
			else if(action.type	== sf::Event::Closed)
			{
				D.close();
				break;
			}
		
	}

	
}


Player::Player(int _side, sf::RenderWindow &D, Battlefield &BF)
{
	numTurn = 0;
	numChars = 3;
	playerChars = new Character *[3];
	if(_side == 0)
	{
		playerChars[0] = new Warrior(1, 10, _side, 45);
		playerChars[1] = new Warrior(2, 10, _side, 135);
		playerChars[2] = new Paladin(3, 10, _side, 225);
	}
	else
	{
		playerChars[0] = new Warrior(-1, 10, _side, 45);
		playerChars[1] = new Warrior(-2, 10, _side, 135);
		playerChars[2] = new Paladin(-3, 10, _side, 225);
	}
	for(int i = 0; i <numChars; ++i)
	{
		playerChars[i]->drawOjb(D);
		playerChars[i]->locateInBTF(BF);
	}

};





int main() {
	
	
	std::string c;
	bool gameOver = false;	
	sf::RenderWindow RW(sf::VideoMode(N, N, 32), "GamePlay");
	Battlefield bField(N/45);

	Player p1(0,RW,bField);
	Player p2(405,RW,bField);
	bField.showBattleField(N/45);

	
	RW.display();

	while(!gameOver)
	{	
		
		p1.move(RW, p2,bField);
		RW.display();

		p2.move(RW, p1,bField);
		RW.display();
		bField.showBattleField(N/45);

	}
	
	return 0;
}
