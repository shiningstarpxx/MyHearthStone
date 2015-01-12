/*
 * VarietyHeroSpell.h
 *
 *  Created on: 2015年1月11日
 *      Author: Joshua
 */

#ifndef HEADER_FACTORY_VARIETYHEROSPELL_H_
#define HEADER_FACTORY_VARIETYHEROSPELL_H_

#include "../HeroSpell.h"

class Hero;

// 防战
class ArmorWarriorSpell: public HeroSpell {
public:
	ArmorWarriorSpell(Game &g, EntityObject *p) :
			HeroSpell(g, p, 2, 1) {
		describe = "+2 armor.";
	}

	ReturnVal check(Target &t) {
		return ReturnVal();
	}

	ReturnVal cast(Target &t) {
		getHero()->armorUp(2);
		return ReturnVal(0);
	}
};

#endif /* HEADER_FACTORY_VARIETYHEROSPELL_H_ */
