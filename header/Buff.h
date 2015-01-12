
#ifndef HEADER_BUFF_H_
#define HEADER_BUFF_H_

#include "Base.h"
#include "gameObject/BaseGameObject.h"
#include "Timing.h"

class Game;
class Card;
class EntityObject;

class Buff: public BaseGameObject, public Timing {
protected:
	int duration;
	BuffType type;
public:
	string describer;
	Buff(Game &g, EntityObject *p, int du, BuffType tp);
	void setDuration(int du) {
		duration = du;
	}
	void timePass() {
		--duration;
	}
	bool expired() {
		return duration <= EXPIRED;
	}
	BuffType getType() {
		return type;
	}

	/********** implement start *************/
	virtual bool isVisible() {
		return 1;
	}
	virtual bool canClone() = 0;
	virtual Buff* clone(EntityObject *p) = 0;
	virtual ReturnVal check(Target &t) {
		return ReturnVal();
	}
	/********** implement end ***************/

	/********** implement start *************/
	virtual int costUp(Card &card) {
		return 0;
	}
	virtual int atkUp() {
		return 0;
	}
	/********** implement end ***************/

	/********** implement start *************/
	bool canRead() {
		return 1;
	}
	void show(bool detail) {
		cout << getDesc(detail) << endl;
	}
	string getDesc(bool detail);
	/********** implement end ***************/

	/********** implement start *************/
	virtual ReturnVal onTurnStart() {
		return 0;
	}
	virtual ReturnVal onTurnEnd() {
		return 0;
	}
	virtual ReturnVal preDmg(Target &t) {
		return 0;
	}
	virtual ReturnVal onHit(Target &t, Damage &d) {
		return 0;
	}
	virtual ReturnVal onDmg(Target &t, Damage &d) {
		return 0;
	}
	virtual ReturnVal onHeal(Target &t, Damage &d) {
		return 0;
	}
	virtual ReturnVal onLeave() {
		return 0;
	}
	virtual ReturnVal onSummon(Target &t) {
		return 0;
	}
	virtual ReturnVal onCast(Target &t) {
		return 0;
	}
	virtual ReturnVal onEquip(Target &t) {
		return 0;
	}
	virtual ReturnVal onPositionChange() {
		return 0;
	}
	virtual ReturnVal onRemove() {
		return 0;
	}
	virtual ReturnVal onAttack(Character &ch) {
		return 0;
	}
	virtual ReturnVal onSilent() {
		return 0;
	}
	/********** implement end ***************/
};

#endif /* HEADER_BUFF_H_ */
