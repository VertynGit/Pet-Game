#pragma once
#include"Skills.h"

class Child {
protected:
	Bot* parent;
	Skill* otec;
public:
	void setSkill(Skill* temp = 0) {
		otec = temp;
	}
	void setParent(Bot* t) {
		parent = t;
	}
};

class Parent {
public:
	list<Bot>* child;
	virtual void setnullChild(Bot* t) {
		node<Bot>* temp = child->head;
		for (int i = child->count; i > 0; i--) {
			if (temp->val == t) {
				child->del(temp);
				break;
			}
			temp = temp->next;
		}
	}
};

class Enemy : public Bot {
private:
public:
	Enemy(String F = "Enem.png", String nam = "Enemy", float W = 40, float H = 40) :Bot(F, nam, W, H) {
		health = 300;
		max = health;
		damage = 40;
		range = 30;
		speed = 0.5;
		attackSp = 50;
		sprite.setColor(Color::Red);
		numberSkill = 0;
	}
	~Enemy() {
		DethRattle();
	}
};

class Hero : public Bot {
protected:
	float agro;
public:
	Hero(String F = "War.png", String nam = "Hero", float W = 40, float H = 24) : Bot(F, nam, W, H) {

	}
};
