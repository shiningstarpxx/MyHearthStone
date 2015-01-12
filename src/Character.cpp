#include "../header/Main.h"

Hero* Character::getHero() {
	return getGame().getPlayer(getHeroUid());
}

ReturnVal Character::isValidAttack(Hero &hero, Character &ch) {
	// 己方攻击敌方
	int uid = hero.getUid();
	if (!(getHeroUid() == uid && ch.getHeroUid() != hero.getUid())) {
		return ReturnVal(-1);
	}

	// 刚刚被召唤
	if (hasBuff(0, SUMMON_SICKNESS) > 0) {
		return ReturnVal(-1);
	}

	// 是否已经攻击过（有风怒攻击次数加一）
	int windfury = hasBuff(0, WIND_FURY) > 0 ? 1 : 0;
	if (atkCnt - windfury >= 1) {
		return ReturnVal(-1);
	}

	// 无攻击力不能攻击
	if (getAtk() <= 0)
		return ReturnVal(-1);

	// 带有不能攻击buff
	if (hasBuff(0, CANT_ATK) > 0)
		return ReturnVal(-1);

	// 目标有潜行buff
	if (ch.hasBuff(0, STEALTH))
		return ReturnVal(-1);

	// 目标没有被嘲讽怪保护
	Hero *op = hero.getOpponent();
	if (ch.hasBuff(0, TAUNT) || op->hasBuff(1, TAUNT) == 0) {
		return ReturnVal(0);
	}
	return ReturnVal(-1);
}

ReturnVal Character::onTurnStart() {
	EntityObject::onTurnStart();
	atkCnt = 0;
	return ReturnVal();
}

ReturnVal Character::onDmg(Target &t, Damage &d) {
	hp -= d.dmg;
	EntityObject::onDmg(t, d);
	battleInfo(t, *this, d);
	return ReturnVal();
}

ReturnVal Character::onHeal(Target &t, Damage &d) {
	int hpChange = hp;
	hp += d.dmg;
	if (hp > maxHp)
		hp = maxHp;
	hpChange -= hp;
	d.dmg = abs(hpChange);
	if (d.dmg) {
		EntityObject::onHeal(t, d);
		battleInfo(t, *this, d);
	}
	return ReturnVal();
}

ReturnVal Character::onAttack(Character &ch) {
	// 从潜行现身
	removeBuff(STEALTH);
	EntityObject::onAttack(ch);

	++atkCnt;

	Target t, v;
	TargetFactory::generateTarget(this, getAtk(), DMG_PHYSIC, t);
	TargetFactory::generateTarget(&ch, ch.getAtk(), DMG_PHYSIC, v);

	t.addOrigin(getDesc(1));
	ch.onHit(t, t.dmgs[0]);

	v.addOrigin(ch.getDesc(1));
	onHit(v, v.dmgs[0]);

	getGame().judge();
	return ReturnVal(0);
}

