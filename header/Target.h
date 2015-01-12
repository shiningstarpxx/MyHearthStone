
#ifndef HEADER_TARGET_H_
#define HEADER_TARGET_H_

#include "Base.h"

class BaseGameObject;
class EntityObject;

class Damage {
public:
	bool specify; 	  			    // 是否指定目标
	bool kill;		                // 是否秒杀效果
	bool heal;						// 是否治疗
	int type;					    // 伤害类型
	int dmg;						// 伤害量
	Character *victim;
	Damage(int t, Character *en) {
		dmg = 0;
		specify = 1;
		kill = 0;
		type = t;
		victim = en;
		heal = 0;
	}
	bool noDmg() {
		return dmg == 0 && !kill;
	}
};

class Target {
	BaseGameObject *dmgOrigin;
	string dmgDesc;
public:
	vector<Damage> dmgs;
	void setDmgOrigin(BaseGameObject* ob) {
		dmgOrigin = ob;
	}
	void addOrigin(string s) {
		dmgDesc += s;
	}
	void clear() {
		dmgOrigin = NULL;
		dmgs.clear();
	}
	bool isAoe() {
		return dmgs.size() > 1;
	}
	bool noTarget() {
		return dmgs.size() == 0 || dmgs[0].victim == NULL;
	}
	string getOrigin() {
		return dmgDesc;
	}
};

#endif /* HEADER_TARGET_H_ */
