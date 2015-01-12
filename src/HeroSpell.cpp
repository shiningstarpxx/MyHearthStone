#include "../header/Main.h"

HeroSpell::HeroSpell(Game &g, EntityObject *p, int c, int limit) :
		BaseGameObject(g, p) {
	cost = c;
	useTime = 0;
	useTimeLimit = limit;
}

void HeroSpell::setSpellId(int id) {
	spellId = id;
}

void HeroSpell::resetUseTime(int t) {
	useTime = t;
}

Hero* HeroSpell::getHero() {
	return static_cast<Hero*>(parent);
}

ReturnVal HeroSpell::castCommand(Target &t) {
	Hero *hero = getHero();
	// 费用不足
	if (hero->getCrystal() < cost) {
		return ReturnVal(-1);
	}

	// 目标不合法
	ReturnVal r = check(t);
	if (r.val < 0)
		return r;

	// 已使用过
	if (useTime >= useTimeLimit) {
		return ReturnVal(-1);
	}

	// 合法
	++useTime;
	hero->crystalChange(-cost);
	return cast(t);
}

bool HeroSpell::canRead() {
	return 1;
}

void HeroSpell::show(bool detail) {
	cout << getDesc(detail) << endl;
}

string HeroSpell::getDesc(bool detail) {
	string s;
	if (detail && parent != NULL) {
		s = parent->getDesc(detail);
	}
	return s + " " + describe;
}
