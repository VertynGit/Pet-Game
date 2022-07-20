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
	virtual void Cast() override{
		Stun* temp = new Stun(object->GetObj());
		Bot* Goal = object->GetObj();
		Goal->CreateMod(temp);
		Goal->GetDam(damage);
		timer = 0;
		object->AddCooldown(this);
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
	virtual void UpdateSk(list <Bot>& E, list <Bot>& H, float time) override {
		objects = &E;
	}
	virtual void Cast() override {
		if (objects != 0) {
			node<Bot>* HEAD = objects->head;
			node<Bot>* temp = HEAD;
			do {
				Bot* t = temp->val;
				float X = t->getx(), Y = t->GetY();
				float d = object->Dist(X, Y);
				if (d <= range) {
					Fire* tempfire = new Fire(t);
					t->CreateMod(tempfire);
				}
				temp = temp->next;
			} while (temp != HEAD);
		}
		timer = 0;
		object->AddCooldown(this);
	}

};

