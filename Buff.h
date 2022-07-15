#pragma once
#include"Bot.h"
struct Stun :public Buff {
	Stun(Bot* obj) {
		obj->setStun(true);
		lifeTime = 2000;
		timerlife = 0;
		object = obj;
	}
	void UpdateBuf(list<Bot>& E, list<Bot>& H, float time) override{
		timerlife += time;
	}
	void DethRattle() {
		object->setStun(false);
	}
	~Stun() {
		DethRattle();
	}
};
struct Fire :public Buff {
	float damage;
	float timer;
	float Cooldown;
	Fire(Bot* obj) {
		object = obj;
		Cooldown = 200;
		damage = 20;
		timer = 0;
		timerlife = 0;
		lifeTime = 1500;
		object->getdam(damage);
	}
	void UpdateBuf(list<Bot>& E, list<Bot>& H, float time) override{
		timerlife += time;
		timer += time;
		if (timer >= Cooldown) {
			object->getdam(damage);
			timer = 0;
		}
	}
	~Fire() {}
};