
#include "../Main.h"

Target TargetFactory::all_minions(Game &game, int dmg, int dmgtype) {
	Target t;
	for (int i = 0; i < HERO_NUM; ++i) {
		Hero *curPlayer = game.getPlayer(i);
		int sz = curPlayer->getMinionSize();
		for (int j = 0; j < sz; ++j) {
			Damage d(dmgtype, curPlayer->getMinion(j));
			d.dmg = dmg;
			d.specify = 0;
			t.dmgs.push_back(d);
		}
	}
	return t;
}

Target TargetFactory::fatigue(Hero *Hero, int dmg) {
	Target t;
	t.addOrigin("Fatigue ");
	Damage d(DMG_FATIGUE, Hero);
	d.dmg = dmg;
	t.dmgs.push_back(d);
	return t;
}

void TargetFactory::generateTarget(Character *ch, int dmg, int type,
		Target &t) {
	t.clear();
	Damage d(type, ch);
	d.dmg = dmg;
	t.dmgs.push_back(d);
}

string TargetFactory::getDescribe(int t) {
	switch (t) {
	case TARGET_U_MINION:
		return "a friendly minion";
	case TARGET_O_MINION:
		return "a enemy minion";
	}
	return "";
}

ReturnVal TargetFactory::checkTarget(Game &game, Target &t, int uid,
		int target) {
	if (target == TARGET_NON)
		return ReturnVal();
	Hero *curPlayer = game.getPlayer(uid);
	if (t.noTarget()) {
		switch (target) {
		case TARGET_U_MINION:
			if (curPlayer->getMinionSize() == 0)
				return ReturnVal();
			break;
		case TARGET_O_MINION:
			if (curPlayer->getOpponent()->getMinionSize() == 0)
				return ReturnVal();
			break;
		case TARGET_ANY_MINION:
			if (curPlayer->getMinionSize()
					+ curPlayer->getOpponent()->getMinionSize() == 0) {
				return ReturnVal();
			}
			break;
		}
		return ReturnVal(-1);
	}
	Character *ch = t.dmgs[0].victim;
	if (target & TARGET_U_MINION) {
		if (!ch->isHero() && ch->getHeroUid() == uid) {
			return 0;
		}
	}
	if (target & TARGET_O_MINION) {
		if (!ch->isHero() && ch->getHeroUid() != uid) {
			return 0;
		}
	}
	if (target & TARGET_U) {
		if (ch->getUid() == uid) {
			return 0;
		}
	}
	if (target & TARGET_O) {
		if (ch->isHero() && ch->getUid() != uid) {
			return 0;
		}
	}
	return -1;
}

