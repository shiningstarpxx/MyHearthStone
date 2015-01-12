
#ifndef HEADER_MINION_H_
#define HEADER_MINION_H_

#include "Base.h"
#include "gameObject/Character.h"
#include "Card.h"
#include "../header/factory/BuffFactory.h"

class EntityObject;

class Minion: public Card, public Character {
protected:
	int type;
public:
	Minion(Game &game, EntityObject *p);

	ReturnVal onDeployed(Target &t);
	ReturnVal returnHand(int costChange);

	void init(string name, int c, int a, int h, int cl, int ty);

	/********** implement start *************/
	ReturnVal check(Target &t);
	/********** implement end ***************/

	/********** implement start *************/
	bool canRead() {
		return 1;
	}

	string getDesc(bool detail) {
		return Character::getDesc(detail);
	}

	void show(bool detail) {
		if (detail)
			cout << "uid(" << getUid() << ") ";
		cout << " ~~~~~~~~ " << getDesc(0);
		cout << " " << getCost() << "/" << getAtk();
		cout << "/" << hp << "(" << maxHp << ")";
		cout << endl;
		if (detail) {
			int sz = buffs.size();
			for (int i = 0; i < sz; ++i) {
				if (!buffs[i]->expired())
					buffs[i]->show(0);
			}
		}
	}
	/********** implement end ***************/
};

#endif /* HEADER_MINION_H_ */
