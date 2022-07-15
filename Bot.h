#pragma once
#include"Baza.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


//////////////////////////
class Bot {
protected:
	static RenderWindow* myWindow; 
	static float time;
	Skill** skills;
	int numberSkill;
	list<Skill>* Otcat;
	list<Buff>* Mods;
	static listV<Event> Ev;
	Bot* object;
	float x, y, tempX, tempY;
	float health; 
	float durability;//Стойкость 
	float damage;
	float speed;
	float attackSp, abilSp;//Скорость атаки и скорость применения способностей
	float range;
	float timeAttack, timeabil;
	float max;
	bool isStun, islife, isMove, isSelect, isFight;
	string name;Image image;Texture texture;Image im; Texture t; Sprite s; RectangleShape bar;
	float w, h;
public:
	Sprite sprite;
	Bot(String F, String nam, float W, float H) {
		isStun = false;
		name = nam;
		numberSkill = 0;
		islife = true;
		timeAttack = 0.000;
		timeabil = 0.000;
		isMove = false; isSelect = false;
		image.loadFromFile("images/" + F);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		w = W, h = H;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);
		im.loadFromFile("images/life.png");
		t.loadFromImage(im);
		s.setTexture(t);
		bar.setFillColor(Color(0, 0, 0));
		Mods = new list<Buff>;
		Otcat = new list<Skill>;
		x = rand() % 600 + 320;
		y = rand() % 314 + 240;
		sprite.setPosition(x, y);

	}
	virtual ~Bot() { };
	static void setwin(RenderWindow & temp) {
		myWindow = &temp;
	}
	static void setTime(float temp) {
		time = temp;
	}
	void addotcat(Skill * temp) {
		Otcat->addWD(temp);
	}
	void updateotcat() { 
		node<Skill>* temp = Otcat->head;
		for (int i = Otcat->count; i > 0; i--) {
			Skill* SkillUp = temp->val;
			SkillUp->update(time);
			if (SkillUp->timer >= SkillUp->Cooldown) {
				node<Skill>* DEL = temp;
				temp = temp->next;
				Otcat->del(DEL);
			}
			else temp = temp->next;
		}

	}
	static void add(Event event) {
		Ev.add(event);
	}
	static void clearevent() {
		Ev.clear();
	}
	void createMod(Buff * M) {
		Mods->add(M);
	}
	void updateMod(list <Bot> & E, list <Bot> & H) {
		node<Buff>* temp = Mods->head;
		for (int i = Mods->count; i > 0; i--) {
			Buff* BuffUp = temp->val;
			BuffUp->UpdateBuf(E, H, time);
			if (BuffUp->timerlife >= BuffUp->lifeTime) {
				node<Buff>* DEL = temp;
				temp = temp->next;
				Mods->del(DEL);
			}
			temp = temp->next;
		}
	}
	void setTempXY(float& X, float& Y) {
		tempX = X;
		tempY = Y;
	}
	void setStun(bool st) {
		isStun = st;
	}
	void Draw() {
		myWindow->draw(sprite);
	}
	void drawlife() {
		bar.setSize(Vector2f((max - health) * 50 / max, 6));
		s.setPosition(x - w / 2, y - h / 2 - 10);
		bar.setPosition(x - w / 2, y - h / 2 - 10);
		myWindow->draw(s);
		myWindow->draw(bar);
	}
	float getrange() {
		return range;
	}
	bool getlife() {
		return islife;
	}
	virtual void gethelp(float& H) {
		float d = health + H;
		if (d >= max)
			health = max;
		else health = d;
	}
	float getheal() {
		return health;
	}
	bool getMove() {
		return isMove;
	}
	void setMove(bool b) { isMove = b; }
	float getx() {
		return x;
	}
	float gety() {
		return y;
	}
	float dist(float X, float Y) {
		return sqrt((X - x) * (X - x) + (Y - y) * (Y - y));
	}
	void Moving(float X, float Y) {
		float distance = dist(X, Y);
		x += speed * time * (X - x) / distance;
		y += speed * time * (Y - y) / distance;
	}
	virtual void getdam(float dg) {
		health = health - dg;
		if (health <= 0)
			islife = false;
	}
	void nultime() {
		timeAttack = 0.000000;
	}
	virtual float useabilities(list<Bot>& E, list<Bot>& H) { return 0; };

	void setobj(Bot* obj) {
		object = obj;
	}
	void setFight(bool b) {
		isFight = b;
	}
	void setnulobj() {
		object = 0;
	}
	Bot* getobj() {
		return object;
	}
	virtual void attack() {
		timeAttack += time;
		if (timeAttack > attackSp) {
			timeAttack = 0;
			object->getdam(damage);
		}
	}
	void DethRattle() {
		delete Otcat;
		delete Mods;
		for (int i = 0; i < numberSkill; i++) {
			delete skills[i];
		}
		delete[] skills;
	}
	virtual void selection(list<Bot>& E, list<Bot>& H);
	virtual void Attack(list<Bot>& E, list<Bot>& H);
	virtual void Birth(list<Bot> & H) {};
	void updateSk(list<Bot> & E, list<Bot> & H) {
		if (skills != 0)
			for (int i = 0; i < numberSkill; i++) {
				skills[i]->updateSk(E, H, time);
			}
	}
	virtual void Botlogic(list<Bot>& E, list<Bot>& H) {
		updateMod(E, H);
		updateotcat();
		updateSk(E, H);
		if (!isStun) {
			if (isFight) {
				if (isSelect) useabilities(E, H);
				if (!object) selection(E, H);
				if (isMove) {
					if (dist(tempX, tempY) > 1) {
						Moving(tempX, tempY);
					}
					else { isMove = false; }
				}
				else Attack(E, H);
			}
			else {
				if (isSelect) useabilities(E, H);
				if (isMove) {
					if (dist(tempX, tempY) > 2) {
						Moving(tempX, tempY);
					}
					else { isMove = false; }
				}
			}

		}


		sprite.setPosition(x, y);
	}
	void Select(bool b) {
		isSelect = b;
	}
};
void Bot::Attack(list<Bot>& E, list<Bot>& H) {
	if (object != 0) {
		float distance = 0, X = 0, Y = 0;
		X = object->getx(), Y = object->gety();
		distance = dist(X, Y);
		if (distance > range) {
			Moving(X, Y);
		}
		else {
			attack();
		}
	}
}
void Bot::selection(list<Bot>& E, list<Bot>& H) {
	float distance = 0, X = 0, Y = 0;
	nultime();
	node<Bot>* HEAD = E.head;
	node<Bot>* temp = HEAD;
	do {
		if (temp->val->getlife() == true) {
			object = temp->val;
			X = object->getx(), Y = object->gety();
			distance = dist(X, Y);
			if (temp->next != HEAD) {
				do {
					temp = temp->next;
					if (temp->val->getlife() == true) {
						Bot* i = temp->val;
						X = i->getx(), Y = i->gety();
						float d = dist(X, Y);
						if (d < distance) {
							distance = d; object = i;
						}
					}
				} while (temp->next != HEAD);
			}
			break;
		}
		temp = temp->next;
	} while (temp != HEAD);
}
