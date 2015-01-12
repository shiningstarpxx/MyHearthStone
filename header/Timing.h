
#ifndef TIMING_H_
#define TIMING_H_

class Target;
class Damage;
class Character;
class ReturnVal;

class Timing {
public:
	virtual ReturnVal onTurnStart() = 0;
	virtual ReturnVal onTurnEnd() = 0;
	virtual ReturnVal preDmg(Target &t) = 0;
	virtual ReturnVal onHit(Target &t, Damage &d) = 0;
	virtual ReturnVal onDmg(Target &t, Damage &d) = 0;
	virtual ReturnVal onHeal(Target &t, Damage &d) = 0;
	virtual ReturnVal onLeave() = 0;
	virtual ReturnVal onSummon(Target &t) = 0;
	virtual ReturnVal onCast(Target &t) = 0;
	virtual ReturnVal onEquip(Target &t) = 0;
	virtual ReturnVal onPositionChange() = 0;
	virtual ReturnVal onRemove() = 0;
	virtual ReturnVal onAttack(Character &ch) = 0;
	virtual ReturnVal onSilent() = 0;
};

#endif /* TIMING_H_ */
