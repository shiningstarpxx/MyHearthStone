
#ifndef HEADER_FACTORY_TARGETFACTORY_H_
#define HEADER_FACTORY_TARGETFACTORY_H_

#include "../Base.h"

class Game;
class Target;
class Hero;
class Character;
class ReturnVal;

class TargetFactory {
public:
	static string getDescribe(int t);

	static Target all_minions(Game &game, int dmg, int dmgtype);

	static Target fatigue(Hero *Hero, int dmg);

	static void generateTarget(Character *ch, int dmg, int type, Target &t);

	static ReturnVal checkTarget(Game &game, Target &t, int uid, int target);
};

#endif /* HEADER_FACTORY_TARGETFACTORY_H_ */
