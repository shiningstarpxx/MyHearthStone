
#include "../header/Main.h"

void battleInfo(Target &t, Character &victim, Damage &d) {
	if (!d.dmg)
		return;
	cout << t.getOrigin();
	cout << (d.heal ? "restore " : "deal ") << d.dmg;
	cout << " " << (d.heal ? "health" : "damage");
	cout << " to " << victim.getDesc(1) << endl;
}

void winInfo(Hero &player) {
	cout << player.getDesc(0) << " win!!!!!!!!!!!!!!" << endl;
}

void loseInfo(Hero &player) {
	cout << player.getDesc(0) << " lose!!!!!!!!!!!!!!" << endl;
}

void split(const string& src, const string& separator, vector<string>& dest) {
	string str = src;
	string substring;
	string::size_type start = 0, index;

	do {
		index = str.find_first_of(separator, start);
		if (index != string::npos) {
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator, index);
			if (start == string::npos)
				return;
		}
	} while (index != string::npos);

	// the last token
	substring = str.substr(start);
	dest.push_back(substring);
}

int myatoi(const string& src) {
	const char *fp = src.c_str();
	for (int i = 0; fp[i]; ++i) {
		if (!isdigit(fp[i])) {
			return -1;
		}
	}
	return atoi(fp);
}

string myitoa(int i) {
	char buff[50];
	sprintf(buff, "%d", i);
	return string(buff);
}

Game::Game() {
	player[0] = new Hero(*this, NULL, 0);
	player[1] = new Hero(*this, NULL, 1);
	dfsLevel = 0;
	gameover = 0;
	turn = 0;
}

Game::~Game() {
	delete player[0];
	delete player[1];
}

int Game::damage(Target &t) {
	int sz = t.dmgs.size();
	for (int i = 0; i < sz; ++i) {
		Damage &d = t.dmgs[i];
		if (d.heal)
			d.victim->onHeal(t, d);
		else
			d.victim->onHit(t, d);
	}
	judge();
	return 0;
}

int Game::judge() {
	++dfsLevel;
	for (int i = 0; i < HERO_NUM; ++i) {
		if (player[i]->isDead()) {
			gameover = 1;
		}
	}
	if (gameover) {
		goto _OUT;
	}
	int pler[HERO_NUM];
	pler[0] = (turn % 2) ^ 1;
	pler[1] = pler[0] ^ 1;
	for (int i = 0; i < HERO_NUM; ++i) {
		player[i]->findAllDeadMinion(deadMinion);
	}
	if (dfsLevel == 1) {
		set<Minion*>::iterator it;
		while (!deadMinion.empty()) {
			it = deadMinion.begin();
			deadMinion.erase(it);
			getPlayer((*it)->getUid())->clear(*it);
		}
	}
	_OUT: --dfsLevel;
	return gameover ? 1 : 0;
}

void Game::updateUid() {
	for (int i = 0; i < HERO_NUM; ++i)
		player[i]->updateUid();
}

int Game::getCurplayer() {
	return getTurn() % HERO_NUM;
}

int Game::getTurn() {
	return turn;
}

int Game::init() {
	dfsLevel = 0;
	turn = 0;
	gameover = 0;
#ifdef _MY_DEBUG_
	g_init(*this, *player[0], *player[1]);
#else
	cout << "xxxxxxxxxxxxxxxxxxxxxxxx" << endl;
#endif
	return 0;
}

int Game::run() {
	init();
	cout << "game start!" << endl;
	while (!gameover) {
		int cur = turn % 2;
		cout << player[cur]->getDesc(0) << " 's turn" << endl;
		player[cur]->onTurnStart();
		if (gameover)
			break;
		while (1) {
			int ret = readCommand();
			if (ret == 1)
				break;
			else if (ret == -1)
				cout << "invalid command" << endl;
			if (gameover)
				break;
		}
		if (gameover)
			break;
		player[cur]->onTurnEnd();
		if (gameover)
			break;
		++turn;
	}
	for (int i = 0; i < HERO_NUM; ++i) {
		if (player[i]->isDead()) {
			winInfo(*player[i]);
		} else {
			loseInfo(*player[i]);
		}
	}
	cout << "game end!" << endl;
	return 0;
}

int Game::readCommand() {
	string comm;
	vector<string> v;
	getline(cin, comm);
	split(comm, " ", v);
	int sz = v.size();
	Character *ch = NULL;
	if (!sz)
		return 0;

	ReturnVal r;
	int curPlayer = getCurplayer();
	if (v[0] == "end") {
		return 1;
	} else if (v[0] == "show") {
		if (sz == 1) {
			show();
			return 0;
		} else if (v[1] == "hand") {
			player[curPlayer]->showHand();
			return 0;
		} else {
			int uId = myatoi(v[1]);
			if (uId < 0 || (ch = parseUid(uId)) == NULL) {
				return -1;
			}
			show(*ch);
			return 0;
		}
	} else if (v[0] == "summon") {
		if (sz >= 3) {
			// 选择的手牌
			int which = myatoi(v[1]);

			// 放置的位置
			// 从左到右 <=0, 1, 2, 3, 4, 5, >=6
			int pos = myatoi(v[2]);

			// 战吼，连击。。 的目标
			int uid = -1;
			if (sz >= 4) {
				uid = myatoi(v[3]);
			}
			 r = player[curPlayer]->summonCommand(which, pos, uid);
			 return r.val;
		}
	} else if (v[0] == "atk") {
		if (sz >= 3) {
			int atkuid = myatoi(v[1]);
			int defuid = myatoi(v[2]);
			r = player[curPlayer]->attackCommand(atkuid, defuid);
			return r.val;
		}
	} else if (v[0] == "hero") {
		int uid = -1;
		if (sz >= 2) {
			uid = myatoi(v[1]);
		}
		r = player[curPlayer]->heroSpellCommand(uid);
		return r.val;
	} else if (v[0] == "test") {
		return 0;
	}
	return -1;
}

void Game::show() {
	int cur = getCurplayer();
	player[cur ^ 1]->show(0);
	player[cur]->show(0);
}

void Game::show(Character &ch) {
	ch.show(1);
}

Character* Game::parseUid(int uid) {
	Character *ch = NULL;
	for (int i = 0; i < HERO_NUM; ++i) {
		ch = player[i]->parseUid(uid);
		if (ch != NULL)
			return ch;
	}
	return NULL;
}

Hero* Game::getPlayer(int uid) {
	return player[uid % HERO_NUM];
}

