
#include "../header/Main.h"

#ifdef _MY_DEBUG_

void g_init(Game& game, Hero &one, Hero &two) {
	int card1[] = { 15, 2, 2,};
	int card2[] = {19, 21, 23 };
	int spellid1 = 0;
	int spellid2 = 0;
	int crystal1 = 4;
	int crystal2 = 4;

	string name1 = ">.<";
	int hp1 = 30;
	int sz1 = (sizeof card1) / (sizeof card1[0]);
	vector<Card*> deck;
	for (int i = 0; i < sz1; ++i) {
		deck.push_back(CardFactory::createCard(game, &one, card1[i]));
	}
	one.init(hp1, name1, deck, WARRIOR, crystal1, NULL);

	string name2 = "@@@@@@@@@@@";
	int hp2 = 30;
	int sz2 = (sizeof card2) / (sizeof card2[0]);
	for (int i = 0; i < sz2; ++i) {
		deck.push_back(CardFactory::createCard(game, &two, card2[i]));
	}
	HeroSpell * hspell2 = HeroSpellFactory::createHeroSpellById(game, &two, spellid2);
	two.init(hp2, name2, deck, WARRIOR, crystal2, hspell2);
}

#endif



