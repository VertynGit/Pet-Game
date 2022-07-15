#include "Checkers.h"
class CooldownRequest :public SkillCastRequest {
protected:
public:
	CooldownRequest(Skill* Iskill) {
		list = new CooldownChecker(Iskill);
		list->next = new ObjChecker(Iskill);
		list->next->next = new TerminalChecker(Iskill);
	}
};
class WithoutObjRequest :public SkillCastRequest {
public:
	WithoutObjRequest(Skill* Iskill) {
		list = new CooldownChecker(Iskill);
		list->next = new TerminalChecker(Iskill);
	}
};
