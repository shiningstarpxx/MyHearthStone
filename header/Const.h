/*
 * const.h
 *
 *  Created on: 2015��1��10��
 *      Author: Administrator
 */

#ifndef HEADER_CONST_H_
#define HEADER_CONST_H_

enum BuffType {
	NON,
	SUMMON_SICKNESS,
	BATTLECRY,
	BLOCK,
	IMUNE_SPELL,
	CHARGE,
	WIND_FURY,
	CANT_ATK,
	TAUNT,
	STEALTH,
	DEATH_RATTLE,
	AURA,           // 光环
	AURA_AFFECT,    // 光环影响
	ENRAGE,         // 激怒
	ENRAGE_AFFECT,  // 激怒影响
	LAST            // 用于计数， 保证放在最后
};

// 职业
enum ClassType {
	NEUTRAL, WARRIOR,
};

const int HERO_NUM = 2;
const int MINION_LIMIT = 7;
const int HAND_CARD_LIMIT = 10;
const int CRYSTAL_LIMIT = 10;

// 分类
const int MINION = 1 << 0;
const int SPELL = 1 << 1;

// 种族
const int TYPE_NON = 0;
const int TYPE_BEAST = 1;
const int TYPE_MURLOC = 2;

// 伤害类型
const int DMG_NON = 0;
const int DMG_FATIGUE = 1;
const int DMG_PHYSIC = 2;
const int DMG_SPELL = 3;       // 法术
const int DMG_MINION = 4;      // 随从技能

// 无目标
const int TARGET_NON = 0;
// 己方随从
const int TARGET_U_MINION = 1 << 0;
// 敌方随从
const int TARGET_O_MINION = 1 << 1;
const int TARGET_U = 1 << 2;
const int TARGET_O = 1 << 3;
const int TARGET_ANY_MINION = TARGET_U_MINION | TARGET_O_MINION;
const int TARGET_ANY_PLAYER = TARGET_U | TARGET_O;
const int TARGET_ANY = TARGET_ANY_MINION | TARGET_ANY_PLAYER;

/****************BUFF DURATION******************/
const int PERMANENT = 1 << 30;
const int EXPIRED = 0;

#endif /* HEADER_CONST_H_ */
