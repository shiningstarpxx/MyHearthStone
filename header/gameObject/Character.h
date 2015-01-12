#ifndef HEADER_GAMEOBJECT_CHARACTER_H_
#define HEADER_GAMEOBJECT_CHARACTER_H_

#include "../Base.h"
#include "EntityObject.h"
#include "../factory/TargetFactory.h"

class ReturnVal;
class Hero;

/*
 * uid 用法
 * 英雄的uid 为 0， 1
 * uid 为 0 的英雄的随从从左到右为 2 4 6 8 10 。。。
 * uid 为 1 的英雄的随从从左到右为 3 5 7 9 11 。。。
 * uid 对于某个角色不是恒定的， 对于位置是恒定的
 */
class Character: public EntityObject {
protected:
	bool dead;
	int Uid;
	int atk;
	int hp;
	int maxHp;
	int atkCnt;
	string name;
public:
	Character(Game &game, EntityObject *p) :
			EntityObject(game, p) {
		dead = 0;
		atkCnt = 0;
	}

	void setUid(int id) {
		Uid = id;
	}

	bool isHurted() {
		return hp != maxHp;
	}

	bool isDead() {
		return hp <= 0 || dead;
	}

	bool isHero() {
		return getUid() < HERO_NUM;
	}

	bool isMinion() {
		int id = getUid();
		return id >= HERO_NUM && id < (1 + MINION_LIMIT) * HERO_NUM;
	}

	int getUid() {
		return Uid;
	}

	int getHeroUid() {
		return getUid() % HERO_NUM;
	}

	int getHp() {
		return hp;
	}

	virtual int getAtk() {
		return atk + atkUp();
	}

	Hero* getHero();

	ReturnVal isValidAttack(Hero &hero, Character &ch);

	/********** implement start *************/
	ReturnVal onDmg(Target &t, Damage &d);

	ReturnVal onAttack(Character &ch);
	ReturnVal onTurnStart();
	ReturnVal onHeal(Target &t, Damage &d);
	/********** implement end ***************/

	/********** implement start *************/
	virtual bool canRead() {
		return 1;
	}
	virtual string getDesc(bool detail) {
		string s;
		if (detail && parent != NULL) {
			s = parent->getDesc(detail);
		}
		return s + "(" + name + ")";
	}
	/********** implement end ***************/
};

#endif /* HEADER_GAMEOBJECT_CHARACTER_H_ */
