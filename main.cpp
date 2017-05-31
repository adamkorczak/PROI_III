#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <unistd.h>
#include "btf.hpp"
#include "chars.hpp"



#define N 450

class Player
{

	int numTurn;
	int numChars;
	Character **playerChars;
	
public:

	Player(int _side, sf::RenderWindow &D, Battlefield &BF);
	void move(sf::RenderWindow &D, Player &P,Battlefield &BF);
	void init();
	void drawAll(sf::RenderWindow &D);
	void animateWalking(sf::RenderWindow &D,int dx, int dy ,int, Player &P,Battlefield &BF);



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
	{
		playerChars[i]->drawOjb(D);
		playerChars[i]->drawHP(D);
	}
	return;
	
}


void Player::move(sf::RenderWindow &D, Player &P,Battlefield &BF)
{

	bool run = true;
	int val;
	sf::Event action;
	int xx;
	int yy;
	int dx,dy;
	double buffX;
	double buffY;

	while(run)
	{	
			playerChars[numTurn]->drawSelected(D);
			D.display();

			while(D.pollEvent(action))
			if(action.type == sf::Event::MouseButtonPressed &&
	 			action.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i positionMouse = sf::Mouse::getPosition(D);

				buffX = ((double)positionMouse.x/N)*10;
				buffY = ((double)positionMouse.y/N)*10;
				xx = floor(buffX)*N/10;
				yy = floor(buffY)*N/10;
				val = BF.returnValue(squarConverterX(xx), squarConverterY(yy));
				

				if(val == 0)
				{
					dx = xx - playerChars[numTurn]->getX();
					dy = yy - playerChars[numTurn]->getY();
					playerChars[numTurn]->checkNeighborhood(BF);
					animateWalking(D,dx,dy,numTurn,P,BF);
					playerChars[numTurn]->showMask();
				}
				else if((val > 0 && playerChars[numTurn]->getID() > 0) || (val < 0 && playerChars[numTurn]->getID() < 0))
				continue;
				else if((val > 0 && playerChars[numTurn]->getID() < 0) || (val < 0 && playerChars[numTurn]->getID() > 0))
				{
					dx = xx - playerChars[numTurn]->getX();
					dy = yy - playerChars[numTurn]->getY();
					playerChars[numTurn]->attack(*P.playerChars[abs(val)-1],dx,dy);	
					drawAll(D);
					P.drawAll(D);
					playerChars[numTurn]->showHP();
					P.playerChars[abs(val)- 1]->showHP();
				}	
			
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
		playerChars[i]->drawHP(D);
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
		//bField.showBattleField(N/45);
		p2.move(RW, p1,bField);
		RW.display();
		//bField.showBattleField(N/45);

	}
	
	return 0;
}
