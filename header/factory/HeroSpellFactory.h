/*
 * HeroSpellFactory.h
 *
 *  Created on: 2015年1月11日
 *      Author: Joshua
 */

#ifndef HEADER_FACTORY_HEROSPELLFACTORY_H_
#define HEADER_FACTORY_HEROSPELLFACTORY_H_

#include "VarietyHeroSpell.h"

class HeroSpell;

class HeroSpellFactory {
	static HeroSpell* gHeroSpellById(Game &g, Hero *h, int id) {
		switch (id) {
		case 0:
			return new ArmorWarriorSpell(g, h);
		}
	}
public:
	static HeroSpell* createHeroSpellById(Game &g, Hero *h, int id) {
		HeroSpell *spell = gHeroSpellById(g, h, id);
		spell->setSpellId(id);
		return spell;
	}
};

#endif /* HEADER_FACTORY_HEROSPELLFACTORY_H_ */
