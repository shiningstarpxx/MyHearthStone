/*
 * BuffFactory.cpp
 *
 *  Created on: 2015��1��11��
 *      Author: Administrator
 */

#include "../../Main.h"

Buff* BuffFactory::generateBasicBuff(Game &g, Character *ch, BuffType buff) {
	Buff *b = new BasicBuff(g, ch, PERMANENT, buff);
	switch (buff) {
	case SUMMON_SICKNESS:
		// 一回合内不能攻击
		b->setDuration(1);
		break;
	}
	return b;
}

string BuffFactory::getBuffTypeDesc(BuffType buff) {
	switch (buff) {
	case NON:
	case AURA_AFFECT:
	case AURA:
		return "";
	case TAUNT:
		return "Taunt";
	case DEATH_RATTLE:
		return "DeathRattle";
	case SUMMON_SICKNESS:
		return "SummonSickness";
	case CHARGE:
		return "Charge";
	case BATTLECRY:
		return "Battlecry";
	case WIND_FURY:
		return "Windfury";
	case STEALTH:
		return "Stealth";
	case ENRAGE:
		return "Enrage";
	}
	return "non-type";
}
