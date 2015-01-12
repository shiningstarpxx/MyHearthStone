
#ifndef HEADER_GAMEOBJECT_ENTITYOBJECT_H_
#define HEADER_GAMEOBJECT_ENTITYOBJECT_H_

#include "../Base.h"
#include "../Const.h"

class Timing;
class BaseGameObject;
class Buff;

class EntityObject: public Timing, public BaseGameObject {
protected:
	vector<Buff*> buffs;
public:
	EntityObject(Game &game, EntityObject *p) :
			BaseGameObject(game, p) {
	}
	virtual ~EntityObject() {
		vector<Buff*>::iterator it;
		for (it = buffs.begin(); it != buffs.end(); it = buffs.erase(it)) {
			delete *it;
		}
	}
	void addBuff(Buff* b) {
		buffs.push_back(b);
	}

	/*
	 * 返回值
	 * 拥有该类型buff的数量
	 * （不一定是实际数量）
	 */
	int hasBuff(bool sub, BuffType buff) {
		int sz = buffs.size();
		int buffCnt[LAST] = { 0 };
		for (int i = 0; i < sz; ++i) {
			if (!buffs[i]->expired()) {
				++buffCnt[buffs[i]->getType()];
			}
		}
		// 特殊判定
		switch (buff) {
		// 嘲讽会被潜行屏蔽
		case TAUNT:
			return buffCnt[STEALTH] ? 0 : buffCnt[buff];
		// 召唤虚弱会被冲锋屏蔽
		case SUMMON_SICKNESS:
			return buffCnt[CHARGE] ? 0 : buffCnt[buff];
		}
		return buffCnt[buff];
	}

	int removeBuff(BuffType buff) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			if (buffs[i]->getType() == buff) {
				buffs[i]->onRemove();
				buffs[i]->setDuration(-1);
			}
		}
		return 0;
	}

	void cleanBuff() {
		vector<Buff*>::iterator it;
		for (it = buffs.begin(); it != buffs.end();) {
			if ((*it)->expired()) {
				delete *it;
				it = buffs.erase(it);
			} else {
				++it;
			}
		}
	}

	/********** implement start *************/
	virtual int atkUp() {
		int sz = buffs.size();
		int atk = 0;
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			atk += buffs[i]->atkUp();
		}
		return atk;
	}

	virtual int costUp(Card &card) {
		int sz = buffs.size();
		int cost = 0;
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			cost += buffs[i]->costUp(card);
		}
		return cost;
	}
	/********** implement end ***************/

	/********** implement start *************/
	virtual ReturnVal onTurnStart() {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			buffs[i]->timePass();
			if (buffs[i]->expired())
				continue;
			buffs[i]->onTurnStart();
		}
		ReturnVal r;
		return r;
	}

	virtual ReturnVal onTurnEnd() {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			buffs[i]->timePass();
			if (buffs[i]->expired())
				continue;
			buffs[i]->onTurnEnd();
		}
		ReturnVal r;
		return r;
	}

	// 受到伤害前的判定，1被格挡 0 没被格挡
	virtual ReturnVal preDmg(Target &t) {
		int sz = buffs.size();
		ReturnVal r;
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			int ret = buffs[i]->preDmg(t).val;
			if (ret == 1) {
				r.val = 1;
				break;
			}
		}
		return r;
	}

	virtual ReturnVal onHit(Target &t, Damage &d) {
		ReturnVal r = preDmg(t).val;
		if (r.val == 1)
			return r;
		return onDmg(t, d);
	}

	virtual ReturnVal onDmg(Target &t, Damage &d) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			buffs[i]->timePass();
			if (buffs[i]->expired())
				continue;
			buffs[i]->onDmg(t, d);
		}
		ReturnVal r;
		return r;
	}

	virtual ReturnVal onHeal(Target &t, Damage &d) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			buffs[i]->timePass();
			if (buffs[i]->expired())
				continue;
			buffs[i]->onHeal(t, d);
		}
		ReturnVal r;
		return r;
	}

	virtual ReturnVal onLeave() {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			buffs[i]->onRemove();
			buffs[i]->onLeave();
		}
		ReturnVal r;
		return r;
	}
	virtual ReturnVal onSummon(Target &t) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			buffs[i]->onSummon(t);
		}
		return ReturnVal();
	}
	// 被施放
	virtual ReturnVal onCast(Target &t) {
		return ReturnVal();
	}
	// 被装备
	virtual ReturnVal onEquip(Target &t) {
		return ReturnVal();
	}
	virtual ReturnVal onPositionChange() {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			buffs[i]->onPositionChange();
		}
		ReturnVal r;
		return r;
	}
	// 被沉默或死亡后buff移除
	virtual ReturnVal onRemove() {
		return ReturnVal();
	}
	// 进行攻击
	virtual ReturnVal onAttack(Character &ch) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (buffs[i]->expired())
				continue;
			buffs[i]->onAttack(ch);
		}
		return ReturnVal();
	}
	// 被沉默
	virtual ReturnVal onSilent() {
		return ReturnVal();
	}
	/********** implement end ***************/
};

#endif /* HEADER_GAMEOBJECT_ENTITYOBJECT_H_ */
