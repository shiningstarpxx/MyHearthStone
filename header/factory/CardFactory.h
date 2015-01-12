
#ifndef HEADER_FACTORY_CARDFACTORY_H_
#define HEADER_FACTORY_CARDFACTORY_H_

class CardFactory {

	static Minion* gStranglethornTiger(Game &game, EntityObject *p);
	static Minion* gTaurenWarrior(Game &game, EntityObject *p);
	static Minion* gThrallmarFarseer(Game &game, EntityObject *p);
	static Minion* gVentureCoMercenary(Game &game, EntityObject *p);
	static Minion* gWarGolem(Game &game, EntityObject *p);
	static Minion* gWindfuryHarpy(Game &game, EntityObject *p);
	static Minion* gWisp(Game &game, EntityObject *p);
	static Minion* gWorgenInfiltrator(Game &game, EntityObject *p);
	static Minion* gYoungDragonhawk(Game &game, EntityObject *p);
	static Minion* gYouthfulBrewmaster(Game &game, EntityObject *p);
	static Minion* gRecklessRocketeer(Game &game, EntityObject *p);
	static Minion* gWolfrider(Game &game, EntityObject *p);
	static Minion* gUnstableGhoul(Game &game, EntityObject *p);
	static Minion* gVoodooDoctor(Game &game, EntityObject *p);
	static Minion* gStonetuskBoar(Game &game, EntityObject *p);
	static Minion* gRiverCrocolisk(Game &game, EntityObject *p);
	static Minion* gRaidLeader(Game &game, EntityObject *p);
	static Minion* gSenjinShieldmasta(Game &game, EntityObject *p);
	static Minion* gNoviceEngineer(Game &game, EntityObject *p);
	static Minion* gNightblade(Game &game, EntityObject *p);
	static Minion* gMurlocRaider(Game &game, EntityObject *p);
	static Minion* gMagmaRager(Game &game, EntityObject *p);
	static Minion* gBoulderfistOgre(Game &game, EntityObject *p);
	static Minion* gBloodfenRaptor(Game &game, EntityObject *p);
	static Minion* gOasisSnapjaw(Game &game, EntityObject *p);

	static Card* gCardById(Game &game, EntityObject *p, int cardId) {
		switch (cardId) {
//		case 0:
//			return gRecklessRocketeer(game, p);
//		case 1:
//			return gWolfrider(game, p);
		case 2:
			return gUnstableGhoul(game, p);
//		case 3:
//			return gVoodooDoctor(game, p);
//		case 4:
//			return gStonetuskBoar(game, p);
//		case 5:
//			return gRiverCrocolisk(game, p);
//		case 6:
//			return gRaidLeader(game, p);
//		case 7:
//			return gSenjinShieldmasta(game, p);
//		case 8:
//			return gNoviceEngineer(game, p);
//		case 9:
//			return gNightblade(game, p);
//		case 10:
//			return gMurlocRaider(game, p);
//		case 11:
//			return gMagmaRager(game, p);
//		case 12:
//			return gBoulderfistOgre(game, p);
//		case 13:
//			return gBloodfenRaptor(game, p);
//		case 14:
//			return gOasisSnapjaw(game, p);
		case 15:
			return gYouthfulBrewmaster(game, p);
		case 16:
			return gYoungDragonhawk(game, p);
		case 17:
			return gWorgenInfiltrator(game, p);
		case 18:
			return gWisp(game, p);
		case 19:
			return gWindfuryHarpy(game, p);
		case 20:
			return gWarGolem(game, p);
		case 21:
			return gVentureCoMercenary(game, p);
		case 22:
			return gThrallmarFarseer(game, p);
		case 23:
			return gTaurenWarrior(game, p);
		case 24:
			return gStranglethornTiger(game, p);
		}
	}
public:
	static Card* createCard(Game &game, EntityObject *p, int cardId) {
		Card *card = gCardById(game, p, cardId);
		card->setCardId(cardId);
		return card;
	}
};

#endif /* HEADER_FACTORY_CARDFACTORY_H_ */
