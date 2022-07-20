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
	list<Skill>* cooldown;
	list<Buff>* mods;
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
		mods = new list<Buff>;
		cooldown = new list<Skill>;
		x = rand() % 600 + 320;
		y = rand() % 314 + 240;
		sprite.setPosition(x, y);

	}
	virtual ~Bot() { };
	static void SetWin(RenderWindow & temp) {
		myWindow = &temp;
	}
	static void SetTime(float temp) {
		time = temp;
	}
	void AddCooldown(Skill * temp) {
		cooldown->AddWD(temp);
	}
	void UpdateCooldown() { 
		node<Skill>* temp = cooldown->head;
		for (int i = cooldown->count; i > 0; i--) {
			Skill* SkillUp = temp->val;
			SkillUp->Update(time);
			if (SkillUp->timer >= SkillUp->Cooldown) {
				node<Skill>* DEL = temp;
				temp = temp->next;
				cooldown->Del(DEL);
			}
			else temp = temp->next;
		}

	}
	static void Add(Event event) {
		Ev.Add(event);
	}
	static void ClearEvent() {
		Ev.Clear();
	}
	void CreateMod(Buff * M) {
		mods->Add(M);
	}
	void UpdateMod(list <Bot> & E, list <Bot> & H) {
		node<Buff>* temp = mods->head;
		for (int i = mods->count; i > 0; i--) {
			Buff* BuffUp = temp->val;
			BuffUp->UpdateBuf(E, H, time);
			if (BuffUp->timerlife >= BuffUp->lifeTime) {
				node<Buff>* DEL = temp;
				temp = temp->next;
				mods->Del(DEL);
			}
			temp = temp->next;
		}
	}
	void SetTempXY(float& X, float& Y) {
		tempX = X;
		tempY = Y;
	}
	void SetStun(bool st) {
		isStun = st;
	}
	void Draw() {
		myWindow->draw(sprite);
	}
	void DrawLife() {
		bar.setSize(Vector2f((max - health) * 50 / max, 6));
		s.setPosition(x - w / 2, y - h / 2 - 10);
		bar.setPosition(x - w / 2, y - h / 2 - 10);
		myWindow->draw(s);
		myWindow->draw(bar);
	}
	float GetRange() {
		return range;
	}
	bool GetLife() {
		return islife;
	}
	virtual void GetHelp(float& H) {
		float d = health + H;
		if (d >= max)
			health = max;
		else health = d;
	}
	float GetHeal() {
		return health;
	}
	bool GetMove() {
		return isMove;
	}
	void SetMove(bool b) { isMove = b; }
	float getx() {
		return x;
	}
	float GetY() {
		return y;
	}
	float Dist(float X, float Y) {
		return sqrt((X - x) * (X - x) + (Y - y) * (Y - y));
	}
	void Moving(float X, float Y) {
		float distance = Dist(X, Y);
		x += speed * time * (X - x) / distance;
		y += speed * time * (Y - y) / distance;
	}
	virtual void GetDam(float dg) {
		health = health - dg;
		if (health <= 0)
			islife = false;
	}
	void NullTime() {
		timeAttack = 0.000000;
	}
	virtual float UseAbilities(list<Bot>& E, list<Bot>& H) { return 0; };

	void SetObj(Bot* obj) {
		object = obj;
	}
	void SetFight(bool b) {
		isFight = b;
	}
	void SetNullObj() {
		object = 0;
	}
	Bot* GetObj() {
		return object;
	}
	virtual void Attack() {
		timeAttack += time;
		if (timeAttack > attackSp) {
			timeAttack = 0;
			object->GetDam(damage);
		}
	}
	void DethRattle() {
		delete cooldown;
		delete mods;
		for (int i = 0; i < numberSkill; i++) {
			delete skills[i];
		}
		delete[] skills;
	}
	virtual void Selection(list<Bot>& E, list<Bot>& H);
	virtual void Attack(list<Bot>& E, list<Bot>& H);
	virtual void Birth(list<Bot> & H) {};
	void UpdateSk(list<Bot> & E, list<Bot> & H) {
		if (skills != 0)
			for (int i = 0; i < numberSkill; i++) {
				skills[i]->UpdateSk(E, H, time);
			}
	}
	virtual void Botlogic(list<Bot>& E, list<Bot>& H) {
		UpdateMod(E, H);
		UpdateCooldown();
		UpdateSk(E, H);
		if (!isStun) {
			if (isFight) {
				if (isSelect) UseAbilities(E, H);
				if (!object) Selection(E, H);
				if (isMove) {
					if (Dist(tempX, tempY) > 1) {
						Moving(tempX, tempY);
					}
					else { isMove = false; }
				}
				else Attack(E, H);
			}
			else {
				if (isSelect) UseAbilities(E, H);
				if (isMove) {
					if (Dist(tempX, tempY) > 2) {
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
		X = object->getx(), Y = object->GetY();
		distance = Dist(X, Y);
		if (distance > range) {
			Moving(X, Y);
		}
		else {
			Attack();
		}
	}
}
void Bot::Selection(list<Bot>& E, list<Bot>& H) {
	float distance = 0, X = 0, Y = 0;
	NullTime();
	node<Bot>* HEAD = E.head;
	node<Bot>* temp = HEAD;
	do {
		if (temp->val->GetLife() == true) {
			object = temp->val;
			X = object->getx(), Y = object->GetY();
			distance = Dist(X, Y);
			if (temp->next != HEAD) {
				do {
					temp = temp->next;
					if (temp->val->GetLife() == true) {
						Bot* i = temp->val;
						X = i->getx(), Y = i->GetY();
						float d = Dist(X, Y);
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
