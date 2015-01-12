
#include "../header/Main.h"

Minion::Minion(Game &game, EntityObject *p) :
		Card(game, p), Character(game, p) {
	category = MINION;
	dead = 0;
}

ReturnVal Minion::returnHand(int costChange) {
	Hero *hero = getHero();
	hero->clear(this);
	Card *c = CardFactory::createCard(Card::getGame(), hero, getCardId());
	hero->addCard(c);
	return ReturnVal();
}

ReturnVal Minion::onDeployed(Target &t) {
	if (hasBuff(0, CHARGE))
		return ReturnVal();
	addBuff(
			BuffFactory::generateBasicBuff(Character::getGame(), this,
					SUMMON_SICKNESS));
	return ReturnVal();
}

void Minion::init(string n, int c, int a, int h, int cl, int ty) {
	Character::name = n;
	cost = c;
	atk = a;
	hp = maxHp = h;
	claxx = cl;
	type = ty;
}

ReturnVal Minion::check(Target &t) {
	ReturnVal r;
	int sz = buffs.size();
	for (int i = 0; i < sz; ++i) {
		if (buffs[i]->expired())
			continue;
		r = buffs[i]->check(t);
		if (r.val < 0)
			return r;
	}
	return r;
}
