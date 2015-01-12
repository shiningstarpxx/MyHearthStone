
#include "../header/Main.h"

Buff::Buff(Game &g, EntityObject *p, int du, BuffType tp) :
		BaseGameObject(g, p) {
	duration = du;
	type = tp;
}

string Buff::getDesc(bool detail) {
	if (detail) {
		return parent->getDesc(detail) + " " + BuffFactory::getBuffTypeDesc(type);
	}
	return BuffFactory::getBuffTypeDesc(type) + describer;
}
