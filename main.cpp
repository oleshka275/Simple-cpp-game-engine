#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

using namespace sf;
using namespace std;

class Player
{
public:
	float x,y=0;
	float dx,dy,speed=0;
	int health;
	bool life;
	int dir;
	string file;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(string F, float X,float Y)
	{
		dx=0;dy=0;speed=0;health=100;life=true;dir=0;
		file=F;
		x=X;y=Y;

		image.loadFromFile("images/"+file);
	    texture.loadFromImage(image);
	    sprite.setTexture(texture);
	
	}

	void control()
	{
		if (life)
		{
	        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) && x > 0){dir = 1; speed = 0.5;}
	        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) && x < 448){dir = 0; speed = 0.5;}
		}
	}

	void update(float time)
	{
		control();
		switch (dir)
		{
			case 0: dx=speed;dy=0;break;
			case 1: dx=-speed;dy=0;break;
		}
		x += dx*time;
		y += dy*time;
 
		speed = 0;
		sprite.setPosition(x,y);

		if (health <=0){life = false;}
	}

};

class Enemy
{
public:
	float x,y;
	float dx,dy,speed=0;
	bool existence;
	string file;
	Image image;
	Texture texture;
	Sprite sprite;

	Enemy(string F, float X, float Y)
	{
		dx=0;dy=0;speed=0.6;existence=true;
		file=F;
		x=X;y=Y;

		image.loadFromFile("images/"+file);
	    texture.loadFromImage(image);
	    sprite.setTexture(texture);
	}

	void update(float time)
	{
		speed = 0.6;

		dy = speed;

		y += dy*time;

		if (y <= 648)
		{
			sprite.setPosition(x,y);
		}else
		{
			y = rand() % 150 - 200;
			x = rand() % 450;
			sprite.setPosition(x,y);
		}
	}
};

int main()
{
    RenderWindow window(VideoMode(480, 648), "SFML works!");

    srand(time(NULL));

    Player p("ship.png", 218, 556);
    Enemy e("meteor.png", rand() % 648,rand() % 30);
    Enemy e2("meteor.png", rand() % 648,rand() % 30);
    Enemy e3("meteor.png", rand() % 648,rand() % 30);

    Clock clock;
	Clock gameTimeClock;

	int gameTime = 0;

	Font font;
	font.loadFromFile("fonts/Samson.ttf");
	Text text(" ", font, 20);
	text.setStyle(Text::Underlined);

    while (window.isOpen())
    {

    	float time = clock.getElapsedTime().asMicroseconds();
    	if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
    	clock.restart();
    	time = time/800;

    	ostringstream playerHealthString;
    	ostringstream gameTimeString;
    	gameTimeString << gameTime;
    	playerHealthString << p.health;
        text.setString("Health: "+ playerHealthString.str() + "\nTime: "+gameTimeString.str());
        text.setPosition(10,10);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
	
        p.update(time);
        e.update(time);
        e2.update(time);
        e3.update(time);

        int realPosX = p.sprite.getPosition().x;
        int realPosY = p.sprite.getPosition().y;

        int realPosXE = e.sprite.getPosition().x;
        int realPosYE = e.sprite.getPosition().y;

        int realPosXE2 = e2.sprite.getPosition().x;
        int realPosYE2 = e2.sprite.getPosition().y;

        int realPosXE3 = e3.sprite.getPosition().x;
        int realPosYE3 = e3.sprite.getPosition().y;

        

        window.clear();

        window.draw(text);

		if (p.sprite.getGlobalBounds().contains(realPosXE,realPosYE))
		{
			if (p.health > 0)
			{
			p.health -=100;
			cout<<p.health<<endl;
			}
		}

		if (p.sprite.getGlobalBounds().contains(realPosXE2,realPosYE2))
		{
			if (p.health > 0)
			{
			p.health -=100;
			cout<<p.health<<endl;
			}
		}
		if (p.sprite.getGlobalBounds().contains(realPosXE3,realPosYE3))
		{
			if (p.health > 0)
			{
			p.health -=100;
			cout<<p.health<<endl;
			}
		}

        window.draw(p.sprite);
        window.draw(e.sprite);
        window.draw(e2.sprite);
        window.draw(e3.sprite);
        window.draw(text);

        window.display();
    }

    return 0;
}		
