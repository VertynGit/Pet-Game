
#include"Listnoder.h"

class Bot;

class SkillCastRequest;
class Skill {//Скилл должен хранить и код клавиши и расположение и анимацию 
public:
	void update(double time) { timer += time; }
	virtual void updateSk(list<Bot>& E, list<Bot>& H, float time) {};
	virtual void setnullChild() {};
	float Cooldown;
	float timer;
	Bot* object;
	virtual void DethRattle() {};
	virtual void cast() {};
	SkillCastRequest* request;
	virtual ~Skill() {}
};

class CastChecker {
public:
	Skill* skill;
	CastChecker* next;
	virtual bool check() = 0;

};

class SkillCastRequest {
protected:
	CastChecker* list;
public:
	virtual void StartRequest() {
		CastChecker* temp = list;
		while (temp != 0) {
			if (temp->check() == false)
				break;
			else {
				temp = temp->next;
			}
		}
	}
	virtual void CancelRequest() {};
	virtual ~SkillCastRequest() {
		while (list != 0) {
			CastChecker* delCheck = list;
			list = list->next;
			delete delCheck;
		}
	}
};

struct Buff {
	Bot* object;
	float timerlife;
	float lifeTime;
	virtual void UpdateBuf(list<Bot>& E, list<Bot>& H, float time) {
		timerlife += time;
	}
	virtual void update(float time) { timerlife += time; }
	virtual ~Buff() {
	}
};