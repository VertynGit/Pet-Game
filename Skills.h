#include "Buff.h"
#include"Requests.h"

class StuN :public Skill {
public:
	float damage;
	StuN(Bot* Bot) {
		object = Bot;
		Cooldown = 3000;
		timer = 500;
		damage = 100;
		request = new CooldownRequest(this);
	}
	~StuN() {
		delete request;
	}
	void cast() {
		Stun* temp = new Stun(object->getobj());
		Bot* Goal = object->getobj();
		Goal->createMod(temp);
		Goal->getdam(damage);
		timer = 0;
		object->addotcat(this);
	}

};


class Break :public Skill {
protected:
	list<Bot>* objects;
	float range;
public:
	Break(Bot* Bot) {
		object = Bot;
		Cooldown = 2000;
		timer = 500;
		range = 100;
		request = new WithoutObjRequest(this);
	}
	~Break() {
		delete request;
	}
	void updateSk(list <Bot>& E, list <Bot>& H, float time) {
		objects = &E;
	}
	void cast() {
		if (objects != 0) {
			node<Bot>* HEAD = objects->head;
			node<Bot>* temp = HEAD;
			do {
				Bot* t = temp->val;
				float X = t->getx(), Y = t->gety();
				float d = object->dist(X, Y);
				if (d <= range) {
					Fire* tempfire = new Fire(t);
					t->createMod(tempfire);
				}
				temp = temp->next;
			} while (temp != HEAD);
		}
		timer = 0;
		object->addotcat(this);
	}

};

