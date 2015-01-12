
#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

#include "Base.h"

class Game {
	Hero *player[HERO_NUM];
	bool gameover;
	int turn;
	int dfsLevel;
	set<Minion*> deadMinion;
private:
	int init();
	int readCommand();
	void show();
	void show(Character &ch);
public:
	Game();
	~Game();
	void updateUid();
	int getTurn();
	int getCurplayer();
	int damage(Target &t);
	int run();
	// 死亡结算
	int judge();
	Character* parseUid(int uid);
	Hero* getPlayer(int uid);
};

#endif /* HEADER_GAME_H_ */
