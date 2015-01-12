
#ifndef HEADER_FACTORY_BUFFFACTORY_H_
#define HEADER_FACTORY_BUFFFACTORY_H_

#include "../Base.h"

class BuffFactory {
public:
	static string getBuffTypeDesc(BuffType buff);

	static Buff* generateBasicBuff(Game &g, Character *ch, BuffType buff);

};


#endif /* HEADER_FACTORY_BUFFFACTORY_H_ */
