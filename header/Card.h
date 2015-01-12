
#ifndef HEADER_CARD_H_
#define HEADER_CARD_H_

#include "Base.h"
#include "gameObject/TargetCheck.h"
#include "gameObject/BaseGameObject.h"

class Hero;
class Game;
class Target;
class EntityObject;

class Card : public BaseGameObject , public TargetCheck {
public:
	int cardId;	    // 卡的id，唯一
	int cost;	    // 费用
	int claxx;	    // 职业
	int category;	// 随从还是法术
	string name;
public:
	Card(Game &g, EntityObject *p);

	void setCardId(int id);
	void setPlayer(Hero *player);
	void changeCost(int change);
	bool isMinion();
	int getCost();
	int getCardId() {
		return cardId;
	}
	virtual ReturnVal check(Target &t) {
		return ReturnVal();
	}
};


#endif /* HEADER_CARD_H_ */
