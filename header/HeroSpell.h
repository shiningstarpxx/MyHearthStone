#ifndef HEADER_HEROSPELL_H_
#define HEADER_HEROSPELL_H_

#include "Base.h"
#include "gameObject/TargetCheck.h"
#include "gameObject/BaseGameObject.h"

class ReturnVal;
class EntityObject;
class Target;

class HeroSpell: public BaseGameObject, public TargetCheck {
protected:
	int spellId;
	int cost;
	int useTime;
	int useTimeLimit;
	string describe;
public:
	HeroSpell(Game &g, EntityObject *p, int c, int limit);

	void setSpellId(int id);

	void resetUseTime(int t);

	virtual ReturnVal cast(Target &t) = 0;

	ReturnVal castCommand(Target &t);

	Hero* getHero();

	/********** implement start *************/
	bool canRead();

	void show(bool detail);

	virtual string getDesc(bool detail);
	/********** implement end ***************/

};

#endif /* HEADER_HEROSPELL_H_ */
