﻿#include "MainLogic.h"
#include "map.h"
#include "view.h"
#include <ctime>
#include<Math.h>
#include <iostream>
//Все временные эффекты должны добавляться в статический список класса общего gameobj, все объекты при рождении(Birth) тоже туда записываются и удаляются при смерти(dethrattle)
//////////////////

listV<Event> Bot::Ev;
RenderWindow* Bot::myWindow = 0;
float Bot::time = 0;


int main()
{
	int n = 1;
	int N = 1;
	srand(time(NULL));
	setlocale(0, "Russian");
	cin >> n;
	cin >> N;
	list<Bot> Enem; list<Bot> Hero;

	for (int i = 0; i < n; i++) {
		Enem.Add(new Enemy);
	}

	for (int i = 0; i < N; i++) {
		Hero.Add(new Magician);
	}

	node<Bot>* tempH = Hero.head;
	for (int i = Hero.count; i > 0; i--) {
		tempH->val->Birth(Hero);
		tempH = tempH->next;
	}

	node<Bot>* tempE = Enem.head;
	for (int i = Enem.count; i > 0; i--) {
		tempE->val->Birth(Enem);
		tempE = tempE->next;
	}
	
///
	/////
	/////
	RenderWindow window(VideoMode(1400, 800), "...");
	Bot::SetWin(window);
	view.reset(FloatRect(0, 0, 640, 480));
	window.setFramerateLimit(40);

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	float currentFrame = 0;
	Clock clock;
	float tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	float tempY = 0;//коорд Y
	float tim = 0.000;
	while (window.isOpen())
	{
	    tim = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		tim = tim/1000;
		Bot::SetTime(tim);
		view.setSize(window.getSize().x, window.getSize().y);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
					SelectedBot(Hero, &window);
			}
			if (event.type == sf::Event::Closed)
				window.close();
			Bot::Add(event);	
		}
		
		Logic(Hero, Enem);

		Bot::ClearEvent();

			if (Hero.count == 0 || Enem.count == 0)
				break;

		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////	
			
			Bot* main = Hero.head->val;
		getplayercoordinateforview(main->getx(), main->GetY());
		window.setView(view);
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));			
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		window.getSystemHandle();

		DrawT(Hero, Enem);
		
		window.display();
		
	}
	return 0;
}























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































