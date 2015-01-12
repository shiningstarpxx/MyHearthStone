
#ifndef HEADER_FACTORY_VARIETYBUFFTYPE_H_
#define HEADER_FACTORY_VARIETYBUFFTYPE_H_

#include "../Base.h"
#include "../Buff.h"

class BasicBuff: public Buff {
public:
	BasicBuff(Game &g, EntityObject *ch, int du, BuffType tp) :
			Buff(g, ch, du, tp) {
	}

	bool canClone() {
		return 1;
	}
	Buff* clone(EntityObject *p) {
		return new BasicBuff(getGame(), p, duration, type);
	}
};

/*
 * 光环 激怒类buff
 * （生效后会对其他角色产生影响）
 */
class AuraBuff: public Buff {
protected:
	vector<Buff*> buffHolder;
	void disableOldBuff() {
		// ʹԭ����buffʧЧ��ɾ��
		vector<Buff*>::iterator it;
		for (it = buffHolder.begin(); it != buffHolder.end();) {
			(*it)->setDuration(-1);
			it = buffHolder.erase(it);
		}
	}
public:
	AuraBuff(Game &g, EntityObject *ch) :
			Buff(g, ch, PERMANENT, AURA) {
	}
	// 订阅该对象
	void regist(Buff* buff) {
		buffHolder.push_back(buff);
	}
	// 取消订阅
	void notify(Buff* buff) {
		vector<Buff*>::iterator it;
		for (it = buffHolder.begin(); it != buffHolder.end();) {
			if ((*it) == buff) {
				buffHolder.erase(it);
				return;
			} else {
				++it;
			}
		}
		cerr << "error in " << __FUNCTION__ << endl;
	}
	ReturnVal onRemove() override {
		disableOldBuff();
		return ReturnVal();
	}
	// 对其他角色产生影响的buff
	virtual Buff* generateBuff() = 0;

	bool canClone() {
		return 1;
	}
};

// 由激怒，光环产生的子buff
class AuraAffectBuff: public Buff {
protected:
	AuraBuff *buff;
public:
	AuraAffectBuff(Game &g, EntityObject *ch, AuraBuff *b, BuffType type) :
			Buff(g, ch, PERMANENT, type) {
		buff = b;
		b->regist(this);
	}
	ReturnVal onRemove() override {
		buff->notify(this);
		return ReturnVal();
	}
	bool canClone() override {
		return 0;
	}
	Buff* clone(EntityObject *p) {
		return NULL;
	}
};

// 激怒buff
class EnrageBuff: public AuraBuff {
protected:
	bool enrageActived;
	void checkEnrage() {
		Character *p = static_cast<Character*>(parent);
		if (p->isHurted() && !enrageActived) {
			enrageActived = 1;
			activeEnrage();
		}
	}
	virtual void activeEnrage() = 0;
public:
	EnrageBuff(Game &g, EntityObject *ch) :
			AuraBuff(g, ch) {
		type = ENRAGE;
		enrageActived = 0;
	}
	ReturnVal onPositionChange() {
		checkEnrage();
		return ReturnVal();
	}
	ReturnVal onDmg(Target &t, Damage &d) override {
		checkEnrage();
		return ReturnVal();
	}
	ReturnVal onHeal(Target &t, Damage &d) override {
		Character *p = static_cast<Character*>(parent);
		if (!p->isHurted() && enrageActived) {
			disableOldBuff();
			enrageActived = 0;
		}
		return ReturnVal();
	}
};

/**************** 具体的buff定义 *******************/
// 加攻击类buff
class AuraAffectATKUp: public AuraAffectBuff {
	int atkChange;
public:
	AuraAffectATKUp(Game &g, EntityObject *ch, AuraBuff *b, BuffType type,
			int up) :
			AuraAffectBuff(g, ch, b, type) {
		atkChange = up;
		describer = "+" + myitoa(up) + " attack.";
	}

	int atkUp() {
		return atkChange;
	}
};

// 增加随从费用buff
class AuraAffectMinionCostUp: public AuraAffectBuff {
	int costChange;
public:
	AuraAffectMinionCostUp(Game &g, EntityObject *ch, AuraBuff *b,
			BuffType type, int up) :
			AuraAffectBuff(g, ch, b, type) {
		costChange = up;
		describer = "Minions cost (" + myitoa(up) + ") more.";
	}
	int costUp(Card &card) {
		return card.isMinion() ? costChange : 0;
	}
};

// 激怒后自身加攻buff
class EnrageSelfATK: public EnrageBuff {
	int atkUp;
public:
	EnrageSelfATK(Game &g, EntityObject *ch, int up) :
			EnrageBuff(g, ch) {
		atkUp = up;
		describer = BuffFactory::getBuffTypeDesc(type);
		describer += ": +" + myitoa(up) + " attack.";
	}

	Buff* generateBuff() {
		return new AuraAffectATKUp(getGame(), parent, this, ENRAGE_AFFECT,
				atkUp);
	}

	void activeEnrage() {
		parent->addBuff(generateBuff());
	}

	Buff* clone(EntityObject *p) {
		return new EnrageSelfATK(getGame(), p, atkUp);
	}
};

// 己方随从费用增加
class AuraSelfMinionCost: public AuraBuff {
	int costUp;
public:
	AuraSelfMinionCost(Game &g, EntityObject *ch, int up) :
			AuraBuff(g, ch) {
		costUp = up;
		describer += "Your Minions cost (" + myitoa(up) + ") more.";
	}

	Buff* generateBuff() {
		return new AuraAffectMinionCostUp(getGame(), parent, this, AURA_AFFECT,
				costUp);
	}

	ReturnVal onPositionChange() {
		disableOldBuff();
		Character *p = static_cast<Character*>(parent);
		p->getHero()->addBuff(generateBuff());
		return ReturnVal();
	}

	Buff* clone(EntityObject *p) {
		return new AuraSelfMinionCost(getGame(), p, costUp);
	}
};

// 指定随从返回手牌buff
class MinionReturnBuff: public Buff {
	int target;
public:
	MinionReturnBuff(Game &g, EntityObject* ch, int t) :
			Buff(g, ch, PERMANENT, BATTLECRY) {
		target = t;
		describer += ": Return " + TargetFactory::getDescribe(t)
				+ " from the battlefield to your hand.";
	}
	ReturnVal check(Target &t) override {
		Character *p = static_cast<Character*>(parent);
		int uid = p->getUid();
		return TargetFactory::checkTarget(getGame(), t, uid, target);
	}
	ReturnVal onSummon(Target &t) override {
		if (t.noTarget()) {
			return ReturnVal();
		}
		Minion *m = static_cast<Minion*>(t.dmgs[0].victim);
		m->returnHand(0);
		return ReturnVal();
	}
	bool canClone() {
		return 1;
	}
	Buff* clone(EntityObject *p) override {
		return new MinionReturnBuff(getGame(), p, target);
	}
};

// 亡语 全部随从受伤害
class DRAllMinionsDMGBuff: public Buff {
	int dmg;
public:
	DRAllMinionsDMGBuff(Game &g, EntityObject *ch, int d) :
			Buff(g, ch, PERMANENT, DEATH_RATTLE) {
		describer += ": Deal " + myitoa(d) + " damage to all minions.";
		dmg = d;
	}
	virtual ReturnVal onLeave() override {
		Target t = TargetFactory::all_minions(getGame(), dmg, DMG_MINION);
		t.addOrigin(getDesc(1));
		getGame().damage(t);
		return ReturnVal();
	}
	bool canClone() {
		return 1;
	}
	Buff* clone(EntityObject *p) override {
		return new DRAllMinionsDMGBuff(getGame(), p, dmg);
	}
};
/**************** buff定义 结束 *******************/

#endif /* HEADER_FACTORY_VARIETYBUFFTYPE_H_ */
