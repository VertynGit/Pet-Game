#include "War.h"


class Magician : public Hero, public Parent {
private:
	float intel;
public:
	Magician(String F = "Mag.png", String nam = "Magician", float W = 40, float H = 37) : Hero(F, nam, W, H) {
		speed = 0.1;
		durability = 30;
		health = 100;
		max = health;
		range = 100;
		damage = 100;
		abilSp = 200;
		attackSp = 300;
		intel = 50;
		numberSkill = 3;
		child = new list<Bot>;
	}
	~Magician() {
		node<Bot>* temp = child->head;
		for (int i = child->count; i > 0; i--) {
			(dynamic_cast<Child*>(temp->val))->setParent(0);
			node<Bot>* DEL = temp;
			temp = temp->next;
			child->del(DEL);
		}
		delete child;
		DethRattle();
	}
	void Birth(list <Bot>& H) {
		skills = new Skill * [numberSkill];
		skills[0] = new Break(this);
		skills[1] = new StuN(this);
		skills[2] = new AddChild(this);
		skills[2]->updateSk(H, H, time);
		skills[2]->request->StartRequest();
	};

	float useabilities(list<Bot>& E, list<Bot>& H) {
		nodeV<Event>* temp = Ev.head;
		for (int i = 0; i < Ev.count; i++) {
			if (temp->val.type == sf::Event::KeyPressed)
				switch (temp->val.key.code) {
				case (sf::Keyboard::Q):
					skills[0]->request->StartRequest();
					break;
				case (sf::Keyboard::W):
					skills[1]->request->StartRequest();
					break;
				case (sf::Keyboard::E):
					skills[2]->request->StartRequest();
					break;
				default:
					break;
				}
			if (temp->val.type == Event::MouseButtonPressed) {
				Vector2i pixelPos;
				Vector2f pos;
				pixelPos = Mouse::getPosition(*myWindow);//забираем коорд курсора
				pos = myWindow->mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
				if (temp->val.key.code == Mouse::Left) {
					Bot* tempObj = 0;
					node<Bot>* tempB = E.head;
					for (int i = E.count; i > 0; i--) {
						if (tempB->val->sprite.getGlobalBounds().contains(pos.x, pos.y))
						{
							tempObj = tempB->val;
						}
						else tempB = tempB->next;
					}
					if (Keyboard::isKeyPressed(Keyboard::LShift)) {
						if (tempObj == 0) { //Установка цели и состояния боя, если выбран противник, иначе перемещение в точку
							node<Bot>* temp = child->head;
							for (int i = 0; i < child->count; i++) {
								Bot* Child = temp->val;
								Child->setFight(false);
								Child->setMove(true);
								Child->setTempXY(pos.x, pos.y);
								temp = temp->next;
							}
						}
						else {
							node<Bot>* temp = child->head;
							for (int i = 0; i < child->count; i++) {
								Bot* Child = temp->val;
								Child->setobj(tempObj);
								Child->setFight(true);
								temp = temp->next;
							}
						}
					}
					else {
						if (tempObj == 0) {
							isFight = false;
							setMove(true);
							setTempXY(pos.x, pos.y);
						}
						else {
							object = tempObj;
							isFight = true;
						}
					}
				}
			}
			temp = temp->next;
		}
		return 0;
	}
};