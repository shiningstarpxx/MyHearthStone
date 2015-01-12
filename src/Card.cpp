
#include "../header/Main.h"

Card::Card(Game &g, EntityObject *p) :
		BaseGameObject(g, p) {
}

void Card::setCardId(int id) {
	cardId = id;
}

void Card::setPlayer(Hero *player) {
	parent = player;
}

void Card::changeCost(int change) {
	cost += change;
	cost = max(cost, 0);
}

bool Card::isMinion() {
	return category == MINION;
}

int Card::getCost() {
	int co = cost + parent->costUp(*this);
	return max(co, 0);
}
