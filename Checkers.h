#include "Bot.h"

class CooldownChecker :public CastChecker {
public:
	CooldownChecker(Skill* Iskill) {
		skill = Iskill;
	}
	bool check() {
		if (skill->timer >= skill->Cooldown)
			return true;
		else
			return false;
	}
};
class ObjChecker :public CastChecker {
public:
	ObjChecker(Skill* Iskill) {
		skill = Iskill;
	}
	bool check() {
		if (skill->object->GetObj() != 0) {
			return true;
		}
		else {
			return false;
		}
	}
};
class TerminalChecker :public CastChecker {
public:
	TerminalChecker(Skill* Iskill) {
		skill = Iskill;
	}
	bool check() {
		skill->object->SetMove(false);
		skill->Cast();
		return true;
	}
};
