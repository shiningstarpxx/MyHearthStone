
#ifndef HEADER_HERO_H_
#define HEADER_HERO_H_

#include "Base.h"
#include "gameObject/Character.h"

class Game;
class BaseGameObject;
class Minion;
class Card;
class ReturnVal;
class HeroSpell;

class Hero: public Character {
protected:
	int overload;           // 本回合使用的过载数
	int crystal;            // 可用水晶数
	int maxCrystal;         // 总水晶数
	int fatigue;            // 疲劳
	int armor;              // 护甲
	int claxx;              // 职业
	vector<Minion*> minions;
	vector<Card*> handCard;
	queue<Card*> deckCard;
	vector<Minion*> minionsGrave;
	HeroSpell *heroSpell;
public:
	Hero(Game &game, EntityObject *p, int id);
	~Hero();

	void init(int h, string ming, vector<Card*>& deck, int cl, int xstal, HeroSpell *hSpell);
	void addCard(Card *card);
	void cleanUp();
	void armorUp(int change);
	void updateUid();
	void showHand();
	void getAllMinion(vector<Minion*> &holder);
	void findAllDeadMinion(set<Minion*> &holder);
	int clear(Minion *m);
	int drag(int c);
	int getArmor();
	int getMinionSize();
	int getHandCnt();
	int getDeckCnt();
	int hasBuff(bool sub, BuffType buff);
	Character* parseUid(int uid);
	Minion* getMinion(int pos);
	Hero* getOpponent();
	ReturnVal summon(Minion *m, bool summon, int pos, Target &t);

	/*********** 控制台命令相关 开始 ************/
	ReturnVal summonCommand(int which, int pos, int uid);
	ReturnVal attackCommand(int atkuid, int defuid);
	ReturnVal heroSpellCommand(int uid);
	/*********** 控制台命令相关 结束 ************/

	/*********** 英雄技能相关 开始 ************/
	void resetHeroSpell();
	void showHeroSpell();
	ReturnVal castHeroSpell(Target &t);
	/*********** 英雄技能相关 结束 ************/

	/*********** 水晶相关 开始 ************/
	void maxCrystalChange(int v);
	void crystalChange(int v);
	void crystalOverload(int v);
	void crystalFill();
	int getCrystal();
	/*********** 水晶相关 结束 ************/

	/********** implement start *************/
	int getAtk();
	/********** implement end ***************/

	/********** implement start *************/
	void show(bool detail);
	/********** implement end ***************/

	/********** implement start *************/
	ReturnVal onTurnStart();
	ReturnVal onTurnEnd();
	ReturnVal onDmg(Target &t, Damage &d);
	ReturnVal onPositionChange();
	/********** implement end ***************/
};

#endif /* HEADER_HERO_H_ */
