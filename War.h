#pragma once
#include "EnAndHero.h"

class War :public Child, public Hero {
private:

public:
	War(String F = "War.png", String nam = "War", float W = 40, float H = 24) : Hero(F, nam, W, H) {
		durability = 100;
		speed = 1.2;
		range = 30;
		health = 200;
		max = health;
		attackSp = 50;
		abilSp = 500;
		timeabil = 300;
		damage = 150;
		agro = 0.2;
		numberSkill = 1;
		skills = new Skill * [numberSkill];
		skills[0] = new StuN(this);
	}
	~War() {
		DethRattle();
		if (otec != 0) {
			otec->setnullChild();
		}
		if (parent != 0) {
			(dynamic_cast<Parent*>(parent))->setnullChild(this);
		}
	}

	float useabilities(list<Bot>& E, list<Bot>& H) override{
		skills[0]->request->StartRequest();
		return 0;
	}
};

class AddChild :public Skill {
protected:
	list<Bot>* objects;
	Bot* child;
public:
	AddChild(Bot* Bot) {
		object = Bot;
		Cooldown = 100;
		timer = 500;
		request = new WithoutObjRequest(this);
	}
	~AddChild() {
		if (child != 0) {
			(dynamic_cast<Child*>(child))->setSkill(0);
		}
		delete request;
	}
	void setnullChild() {
		child = 0;
	}
	void updateSk(list<Bot>& E, list<Bot>& H, float time) override {
		objects = &H;
	}
	void cast() {
		if (child == 0) {
			Parent* temp = dynamic_cast<Parent*>(object);
			War* acolyte = new War;
			child = acolyte;
			acolyte->setParent(object);
			acolyte->setSkill(this);
			temp->child->addWD(acolyte);
			objects->add(acolyte);
		}
		else {
			float heal = 50;
			child->gethelp(heal);
		}
		timer = 0;
		object->addotcat(this);
	}
};