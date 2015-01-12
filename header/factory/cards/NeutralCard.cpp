
#include "../../Main.h"

// 荆棘谷猛虎
Minion* CardFactory::gStranglethornTiger(Game &game, EntityObject *p) {
	string name = "Stranglethorn Tiger";
	int cost = 5;
	int atk = 5;
	int hp = 5;
	int claxx = NEUTRAL;
	int type = TYPE_BEAST;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, STEALTH));
	return m;
}

// 牛头人战士
Minion* CardFactory::gTaurenWarrior(Game &game, EntityObject *p) {
	string name = "Tauren Warrior";
	int cost = 3;
	int atk = 2;
	int hp = 3;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(new EnrageSelfATK(game, m, 3));
	m->addBuff(BuffFactory::generateBasicBuff(game, m, TAUNT));
	return m;
}

// 萨尔玛先知
Minion* CardFactory::gThrallmarFarseer(Game &game, EntityObject *p) {
	string name = "Thrallmar Farseer";
	int cost = 3;
	int atk = 2;
	int hp = 3;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, WIND_FURY));
	return m;
}

// 风险投资公司雇佣兵
Minion* CardFactory::gVentureCoMercenary(Game &game, EntityObject *p) {
	string name = "Venture Co. Mercenary";
	int cost = 5;
	int atk = 7;
	int hp = 6;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(new AuraSelfMinionCost(game, m, 3));
	return m;
}

// 作战傀儡
Minion* CardFactory::gWarGolem(Game &game, EntityObject *p) {
	string name = "War Golem";
	int cost = 7;
	int atk = 7;
	int hp = 7;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	return m;
}

// 风怒鹰身人
Minion* CardFactory::gWindfuryHarpy(Game &game, EntityObject *p) {
	string name = "Windfury Harpy";
	int cost = 6;
	int atk = 4;
	int hp = 5;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, WIND_FURY));
	return m;
}

// 小精灵
Minion* CardFactory::gWisp(Game &game, EntityObject *p) {
	string name = "Wisp";
	int cost = 0;
	int atk = 1;
	int hp = 1;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	return m;
}

// 狼人渗透者
Minion* CardFactory::gWorgenInfiltrator(Game &game, EntityObject *p) {
	string name = "Worgen Infiltrator";
	int cost = 1;
	int atk = 2;
	int hp = 1;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, STEALTH));
	return m;
}

// 幼龙鹰
Minion* CardFactory::gYoungDragonhawk(Game &game, EntityObject *p) {
	string name = "Young Dragonhawk";
	int cost = 1;
	int atk = 1;
	int hp = 1;
	int claxx = NEUTRAL;
	int type = TYPE_BEAST;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, WIND_FURY));
	return m;
}

// 年轻的酒仙
Minion* CardFactory::gYouthfulBrewmaster(Game &game, EntityObject *p) {
	string name = "Youthful Brewmaster";
	int cost = 2;
	int atk = 3;
	int hp = 2;
	int claxx = NEUTRAL;
	int type = TYPE_BEAST;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(new MinionReturnBuff(game, m, TARGET_U_MINION));
	return m;
}

//// 血沼迅猛龙
//// Bloodfen Raptor
//Minion* CardFactory::gBloodfenRaptor(Game &game, EntityObject *p) {
//	string name = "Bloodfen Raptor";
//	int cost = 2;
//	int atk = 3;
//	int hp = 2;
//	int claxx = NEUTRAL;
//	int type = TYPE_BEAST;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 石拳食人魔
//// Boulderfist Ogre
//Minion* CardFactory::gBoulderfistOgre(Game &game, EntityObject *p) {
//	string name = "Boulderfist Ogre";
//	int cost = 6;
//	int atk = 6;
//	int hp = 7;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 岩浆暴怒者
//// Magma Rager
//Minion* CardFactory::gMagmaRager(Game &game, EntityObject *p) {
//	string name = "Magma Rager";
//	int cost = 3;
//	int atk = 5;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 鱼人袭击者
//Minion* CardFactory::gMurlocRaider(Game &game, EntityObject *p) {
//	string name = "Murloc Raider";
//	int cost = 1;
//	int atk = 2;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_MURLOC;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 夜刃刺客
//Minion* CardFactory::gNightblade(Game &game, EntityObject *p) {
//	class NightbladeBuff: public Buff {
//	public:
//		NightbladeBuff(Character* ch) :
//				Buff(ch, PERMANENT, BATTLECRY) {
//			describer += ": Deal 3 damage to the enemy hero.";
//		}
//		int onSummon(Game &game, Target &t) override {
//			Hero *op = getCharacter()->getPlayer()->getOpponent();
//			TargetFactory::generateTarget(op, 3, DMG_MINION, t);
//			t.addOrigin(getFullDesc());
//			return game.damage(t);
//		}
//		Buff* clone() override {
//			return new NightbladeBuff(character);
//		}
//	};
//
//	string name = "Nightblade";
//	int cost = 5;
//	int atk = 4;
//	int hp = 4;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(new NightbladeBuff(m));
//	return m;
//}
//
//// 工程师学徒
//Minion* CardFactory::gNoviceEngineer(Game &game, EntityObject *p) {
//	class NoviceEngineerBuff: public Buff {
//	public:
//		NoviceEngineerBuff(Character* ch) :
//				Buff(ch, PERMANENT, BATTLECRY) {
//			describer += ": Draw a card.";
//		}
//		int onSummon(Game &game, Target &t) override {
//			getCharacter()->getPlayer()->drag(1);
//			return 0;
//		}
//		Buff* clone() override {
//			return new NoviceEngineerBuff(character);
//		}
//	};
//
//	string name = "Novice Engineer";
//	int cost = 2;
//	int atk = 1;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(new NoviceEngineerBuff(m));
//	return m;
//}
//
//// 绿洲钳嘴龟
//Minion* CardFactory::gOasisSnapjaw(Game &game, EntityObject *p) {
//	string name = "Oasis Snapjaw";
//	int cost = 4;
//	int atk = 2;
//	int hp = 7;
//	int claxx = NEUTRAL;
//	int type = TYPE_BEAST;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 团队领袖
//Minion* CardFactory::gRaidLeader(Game &game, EntityObject *p) {
//	class RaidLeaderBuff: public AuraBuff {
//	public:
//		RaidLeaderBuff(Character* ch) :
//				AuraBuff(ch) {
//			describer = "Your other minions have +1 Attack.";
//		}
//		Buff* generateBuff() {
//			// ������ӻ�õļӹ�buff
//			class RaidLeaderChildBuff: public AuraAffectBuff {
//			public:
//				RaidLeaderChildBuff(AuraBuff *buff, Character* ch) :
//						AuraAffectBuff(ch, buff, AURA_AFFECT) {
//					describer = "+1 Attack.";
//				}
//				int atkUp() override {
//					return 1;
//				}
//				Buff* clone() {
//					return new RaidLeaderChildBuff(buff, getCharacter());
//				}
//			};
//			return new RaidLeaderChildBuff(this, getCharacter());
//		}
//		int onPositionChange(Game &game) override {
//			disableOldBuff();
//			int uid = getCharacter()->getUID();
//			Hero *player = getCharacter()->getPlayer();
//			vector<Minion*> holder;
//			player->getAllMinion(holder);
//			int sz = holder.size();
//			for (int i = 0; i < sz; ++i) {
//				if (holder[i]->getUID() != uid) {
//					holder[i]->addBuff(generateBuff());
//				}
//			}
//			return 0;
//		}
//		Buff* clone() {
//			return new RaidLeaderBuff(character);
//		}
//	};
//
//	string name = "Raid Leader";
//	int cost = 3;
//	int atk = 2;
//	int hp = 2;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(new RaidLeaderBuff(m));
//	return m;
//}
//
//// 鲁莽火箭兵
//Minion* CardFactory::gRecklessRocketeer(Game &game, EntityObject *p) {
//	string name = "Reckless Rocketeer";
//	int cost = 6;
//	int atk = 5;
//	int hp = 2;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(BuffFactory::generateBasicBuff(m, CHARGE));
//	return m;
//}
//
//// 淡水鳄
//Minion* CardFactory::gRiverCrocolisk(Game &game, EntityObject *p) {
//	string name = "River Crocolisk";
//	int cost = 2;
//	int atk = 2;
//	int hp = 3;
//	int claxx = NEUTRAL;
//	int type = TYPE_BEAST;
//	return new Minion(name, cost, atk, hp, claxx, type);
//}
//
//// 森金持盾卫士
//Minion* CardFactory::gSenjinShieldmasta(Game &game, EntityObject *p) {
//	string name = "Sen'jin Shieldmasta";
//	int cost = 4;
//	int atk = 3;
//	int hp = 5;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(BuffFactory::generateBasicBuff(m, TAUNT));
//	return m;
//}
//
//// 石牙野猪
//Minion* CardFactory::gStonetuskBoar(Game &game, EntityObject *p) {
//	string name = "Stonetusk Boar";
//	int cost = 1;
//	int atk = 1;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_BEAST;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(BuffFactory::generateBasicBuff(m, CHARGE));
//	return m;
//}
//
//// 狼骑兵
//Minion* CardFactory::gWolfrider(Game &game, EntityObject *p) {
//	string name = "Wolfrider";
//	int cost = 3;
//	int atk = 3;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(BuffFactory::generateBasicBuff(m, CHARGE));
//	return m;
//}
//
//// 巫医
//Minion* CardFactory::gVoodooDoctor(Game &game, EntityObject *p) {
//	class VoodooDoctorBuff: public Buff {
//	public:
//		VoodooDoctorBuff(Character *ch) :
//				Buff(ch, PERMANENT, BATTLECRY) {
//			describer += ": Restore 2 Health.";
//		}
//		int check(Game &game, Target &t) override {
//			int uid = getCharacter()->getPlayerUID();
//			return TargetFactory::checkTarget(game, t, uid, TARGET_ANY);
//		}
//		int onSummon(Game &game, Target &t) override {
//			Damage &d = t.dmgs[0];
//			t.addOrigin(getFullDesc());
//			d.heal = 1;
//			d.dmg = 2;
//			return game.damage(t);
//		}
//		Buff* clone() override {
//			return new VoodooDoctorBuff(character);
//		}
//	};
//
//	string name = "Voodoo Doctor";
//	int cost = 1;
//	int atk = 2;
//	int hp = 1;
//	int claxx = NEUTRAL;
//	int type = TYPE_NON;
//	Minion *m = new Minion(name, cost, atk, hp, claxx, type);
//	m->addBuff(new VoodooDoctorBuff(m));
//	return m;
//}

// 蹒跚的食尸鬼
Minion* CardFactory::gUnstableGhoul(Game &game, EntityObject *p) {
	string name = "Unstable Ghoul";
	int cost = 2;
	int atk = 1;
	int hp = 3;
	int claxx = NEUTRAL;
	int type = TYPE_NON;
	Minion *m = new Minion(game, p);
	m->init(name, cost, atk, hp, claxx, type);
	m->addBuff(BuffFactory::generateBasicBuff(game, m, TAUNT));
	m->addBuff(new DRAllMinionsDMGBuff(game, m, 1));
	return m;
}

