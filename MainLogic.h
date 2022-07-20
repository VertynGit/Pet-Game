#include"Magician.h"

Bot* SelectedBot(list<Bot>& T, RenderWindow* window) {
	Vector2i pixelPos;
	Vector2f pos;
	pixelPos = Mouse::getPosition(*window);
	pos = window->mapPixelToCoords(pixelPos);
	node<Bot>* tempB = T.head;
	for (int i = T.count; i > 0; i--) {
		if (tempB->val->sprite.getGlobalBounds().contains(pos.x, pos.y))
		{
			tempB->val->Select(true);
			return tempB->val;
		}
		else tempB = tempB->next;
	}
	return 0;
}

void DethBot(list<Bot>& T, list<Bot>& Enem) {
	node<Bot>* tempH = T.head;
	node<Bot>* tempE = Enem.head;
	for (int i = T.count; i > 0; i--) {
		Bot* del = tempH->val;
		if (del->GetHeal() <= 0) {
			for (int i = Enem.count; i > 0; i--) {
				Bot* enemy = tempE->val;
				if (enemy->GetObj() == del) {
					enemy->SetNullObj();
				}
				tempE = tempE->next;
			}
			node<Bot>* Del = tempH;
			tempH = tempH->next;
			T.Del(Del);
		}
		else tempH = tempH->next;
	}
}

void Logic(list<Bot>& T, list<Bot>& T1) {
	node<Bot>* tempH = T.head;
	node<Bot>* tempE = T1.head;
	for (int i = T1.count; i > 0; i--) {
		tempE->val->Botlogic(T, T1);
		tempE = tempE->next;
	}
	for (int i = T.count; i > 0; i--) {
		tempH->val->Botlogic(T1, T);
		tempH = tempH->next;
	}

	DethBot(T, T1);
	DethBot(T1, T);
}

void DrawT(list<Bot>& T, list<Bot>& T1) {
	node<Bot>* tempH = T.head;
	node<Bot>* tempE = T1.head;
	int n = T.count, n1 = T1.count;

	for (int i = n; i > 0; i--) {
		tempH->val->Draw();
		tempH = tempH->next;
	}
	for (int i = n1; i > 0; i--) {
		tempE->val->Draw();
		tempE = tempE->next;
	}
	for (int i = n; i > 0; i--) {
		tempH->val->DrawLife();
		tempH = tempH->next;
	}
	for (int i = n1; i > 0; i--) {
		tempE->val->DrawLife();
		tempE = tempE->next;
	}
}
