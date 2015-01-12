#include "../header/factory/TargetFactory.h"
#include "../header/Main.h"

Hero::Hero(Game &game, EntityObject *p, int uid) :
		Character(game, p) {
	fatigue = 0;
	dead = 0;
	setUid(uid);
}

Hero::~Hero() {
	for (vector<Card*>::iterator it = handCard.begin(); it != handCard.end();) {
		delete *it;
		it = handCard.erase(it);
	}
	for (vector<Minion*>::iterator it = minions.begin(); it != minions.end();) {
		delete *it;
		it = minions.erase(it);
	}
	while (!deckCard.empty()) {
		Card *card = deckCard.front();
		delete card;
		deckCard.pop();
	}
	cleanUp();
}

ReturnVal Hero::onTurnStart() {
	drag(1);
	Character::onTurnStart();
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		minions[i]->onTurnStart();
	}
	maxCrystalChange(1);
	crystalFill();
	return ReturnVal();
}

ReturnVal Hero::onTurnEnd() {
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		minions[i]->onTurnEnd();
	}
	EntityObject::onTurnEnd();
	cleanUp();
	return ReturnVal();
}

void Hero::addCard(Card *card) {
	if (handCard.size() >= HAND_CARD_LIMIT) {
		cout << "delete card " << card->getDesc(0) << endl;
		delete card;
	} else {
		cout << getDesc(1) << " get card " << card->getDesc(0) << endl;
		handCard.push_back(card);
	}
}

int Hero::drag(int c) {
	for (int i = 0; i < c; ++i) {
		if (deckCard.empty()) {
			++fatigue;
			Target t = TargetFactory::fatigue(this, fatigue);
			getGame().damage(t);
		} else {
			Card *c = deckCard.front();
			deckCard.pop();
			cout << getDesc(0) << " drag a card" << endl;
			addCard(c);
		}
	}
	return 0;
}

void Hero::init(int h, string ming, vector<Card*>& deck, int cl, int xstal,
		HeroSpell *hSpell) {
	name = ming;
	maxHp = hp = h;
	armor = 0;
	fatigue = 0;
	claxx = cl;
	overload = 0;
	crystal = 0;
	maxCrystal = xstal;
	heroSpell = hSpell;
	handCard.clear();
	buffs.clear();
	while (!deckCard.empty()) {
		deckCard.pop();
	}
	for (vector<Card*>::iterator it = deck.begin(); it != deck.end();) {
		(*it)->setPlayer(this);
		deckCard.push(*it);
		it = deck.erase(it);
	}
}

int Hero::getAtk() {
	// TODO
	return 0;
}

int Hero::getArmor() {
	return armor;
}

/*
 * 如果是扣除护甲，注意
 * 护甲扣除量比护甲高的情况
 */
void Hero::armorUp(int change) {
	int ap = max(0, armor + change);
	change = ap - armor;
	armor = ap;
	cout << getDesc(1);
	cout << (change > 0 ? " get " : " remove ");
	cout << abs(change) << " armor." << endl;
}

ReturnVal Hero::onDmg(Target &t, Damage &d) {
	ReturnVal r;
	if (getArmor() > 0) {
		int armorChange = min(getArmor(), d.dmg);
		armorUp(-armorChange);
		d.dmg -= armorChange;
		if (d.dmg <= 0)
			return r;
	}
	return Character::onDmg(t, d);
}

ReturnVal Hero::onPositionChange() {
	int sz = minions.size();
	getGame().updateUid();
	for (int i = 0; i < sz; ++i) {
		minions[i]->onPositionChange();
	}
	return ReturnVal();
}

ReturnVal Hero::summon(Minion *m, bool summon, int pos, Target &t) {
	cout << m->getDesc(1) << " summoned." << endl;
	pos = max(pos, 0);
	pos = min(pos, (int) minions.size());
	minions.insert(minions.begin() + pos, m);
	onPositionChange();
	if (summon)
		m->onSummon(t);
	return m->onDeployed(t);
}

/*
 * 召唤命令
 * 0  成功
 * -1 失败
 */
ReturnVal Hero::summonCommand(int which, int pos, int uid) {
	// 选择手牌是否正确
	if (which < 0 || which >= handCard.size()) {
		return ReturnVal(-1);
	}

	Card *card = handCard[which];
	int cost = card->getCost();
	// 水晶是否足够
	if (getCrystal() < cost) {
		return ReturnVal(-1);
	}
	// 是否是随从
	if (!card->isMinion()) {
		return ReturnVal(-1);
	}

	Minion *m = static_cast<Minion*>(card);
	m->setUid(getUid());
	Character *ch = getGame().parseUid(uid);
	Target t;
	TargetFactory::generateTarget(ch, 0, DMG_NON, t);
	// 是否满足战吼目标要求
	if (m->check(t).val < 0) {
		return ReturnVal(-1);
	}

	//
	crystalChange(-cost);
	handCard.erase(handCard.begin() + which);
	return summon(m, 1, pos, t);
}

/*
 * 攻击命令
 * 0  成功
 * -1 失败
 */
ReturnVal Hero::attackCommand(int atkuid, int defuid) {
	int id = getUid();
	if (atkuid % HERO_NUM == id && defuid % HERO_NUM != id) {
		Character *atker = parseUid(atkuid);
		Character *defer = getGame().parseUid(defuid);
		if (atker == NULL || defer == NULL)
			return ReturnVal(-1);
		if (atker->isValidAttack(*this, *defer).val < 0) {
			return ReturnVal(-1);
		}
		return atker->onAttack(*defer);
	}
	return ReturnVal(-1);
}

ReturnVal Hero::heroSpellCommand(int uid) {
	Character *ch = getGame().parseUid(uid);
	Target t;
	TargetFactory::generateTarget(ch, 0, DMG_NON, t);
	return castHeroSpell(t);
}

Hero* Hero::getOpponent() {
	return getGame().getPlayer(getUid() ^ 1);
}

void Hero::show(bool detail) {
	cout << "(" << getUid() << ")";
	cout << " ************ " << getDesc(0);
	cout << " <" << crystal << "(" << maxCrystal << ")>";
	cout << " <" << getArmor();
	cout << "/" << hp << "(" << maxHp << ")>";
	cout << " " << getAtk();
	cout << " H:" << getHandCnt();
	cout << " D:" << getDeckCnt();
	cout << endl;
	showHeroSpell();
	if (detail) {
		int sz = buffs.size();
		for (int i = 0; i < sz; ++i) {
			if (!buffs[i]->expired())
				cout << buffs[i]->getDesc(1) << endl;
		}
	} else {
		cout << "------------------------------------------" << endl;
		int sz = minions.size();
		for (int i = 0; i < sz; ++i) {
			cout << "(" << minions[i]->getUid() << ") ";
			minions[i]->show(detail);
		}
		cout << endl;
	}
}

void Hero::showHand() {
	int sz = handCard.size();
	cout << sz << " hand card(s)" << endl;
	for (int i = 0; i < sz; ++i) {
		cout << "(" << i << ") ";
		handCard[i]->show(0);
	}
}

Minion* Hero::getMinion(int pos) {
	return minions[pos];
}

Character* Hero::parseUid(int uid) {
	if (getUid() == uid) {
		return this;
	}
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		if (minions[i]->getUid() == uid) {
			return minions[i];
		}
	}
	return NULL;
}

int Hero::clear(Minion *m) {
	int sz = minions.size(), i;
	for (i = 0; i < sz; ++i) {
		if (minions[i] == m)
			break;
	}
	if (i >= sz) {
		cerr << "error in " << __FUNCTION__ << " " << __LINE__ << endl;
		return -1;
	}
	minions.erase(minions.begin() + i);
	onPositionChange();
	if (m->isDead()) {
		m->onLeave();
		cout << m->getDesc(1) << " sent into grave!!! " << endl;
	}

	minionsGrave.push_back(m);
	return 0;
}

int Hero::hasBuff(bool sub, BuffType buff) {
	if (sub) {
		int sz = minions.size();
		int cnt = 0;
		for (int i = 0; i < sz; ++i) {
			cnt += minions[i]->hasBuff(0, buff);
		}
		return cnt;
	} else {
		return Character::hasBuff(sub, buff);
	}
}

void Hero::findAllDeadMinion(set<Minion*> &holder) {
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		if (minions[i]->isDead())
			holder.insert(minions[i]);
	}
}

void Hero::getAllMinion(vector<Minion*> &holder) {
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		holder.push_back(minions[i]);
	}
}

void Hero::cleanUp() {
	cleanBuff();
	for (vector<Minion*>::iterator it = minions.begin(); it != minions.end();
			++it) {
		(*it)->cleanBuff();
	}
	for (vector<Minion*>::iterator it = minionsGrave.begin();
			it != minionsGrave.end(); it = minionsGrave.erase(it)) {
		delete *it;
	}
}

int Hero::getMinionSize() {
	return minions.size();
}

int Hero::getHandCnt() {
	return handCard.size();
}

int Hero::getDeckCnt() {
	return deckCard.size();
}

void Hero::updateUid() {
	int uid = getUid();
	int sz = minions.size();
	for (int i = 0; i < sz; ++i) {
		minions[i]->setUid(uid + HERO_NUM * (i + 1));
	}
}

void Hero::maxCrystalChange(int v) {
	maxCrystal += v;
	maxCrystal = min(maxCrystal, CRYSTAL_LIMIT);
	maxCrystal = max(maxCrystal, 0);
}

void Hero::crystalChange(int v) {
	crystal += v;
}

void Hero::crystalOverload(int v) {
	overload += v;
}

void Hero::crystalFill() {
	crystal = max(maxCrystal - overload, 0);
	overload = 0;
}

int Hero::getCrystal() {
	return crystal;
}

void Hero::showHeroSpell() {
	if (heroSpell != NULL) {
		cout << "hero spell: " << heroSpell->getDesc(0) << endl;
	}
}

void Hero::resetHeroSpell() {
	if (heroSpell != NULL) {
		heroSpell->resetUseTime(0);
	}
}

ReturnVal Hero::castHeroSpell(Target &t) {
	if (heroSpell != NULL) {
		return heroSpell->cast(t);
	}
	return ReturnVal(-1);
}
