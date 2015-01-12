
#ifndef GAME_H_
#define GAME_H_

#include "Base.h"
#include "ReturnVal.h"
#include "Timing.h"
#include "Const.h"
#include "Buff.h"
#include "Target.h"
#include "Hero.h"
#include "Minion.h"
#include "Card.h"
#include "Game.h"
#include "HeroSpell.h"
#include "gameObject/TargetCheck.h"
#include "gameObject/BaseGameObject.h"
#include "gameObject/EntityObject.h"
#include "gameObject/Character.h"
#include "factory/TargetFactory.h"
#include "factory/BuffFactory.h"
#include "factory/CardFactory.h"
#include "factory/VarietyBuffType.h"
#include "factory/HeroSpellFactory.h"
#include "factory/VarietyHeroSpell.h"

// battle information output
void battleInfo(Target &t, Character &victim, Damage &d);
void winInfo(Hero &player);
void loseInfo(Hero &player);

#define _MY_DEBUG_

#ifdef _MY_DEBUG_
void g_init(Game &game, Hero &one, Hero &two);
#endif

#endif /* GAME_H_ */
