
#ifndef RETURNVAL_H_
#define RETURNVAL_H_

#include "Base.h"

class ReturnVal {
public:
	int val;
	string reason;

public:
	ReturnVal(int v) {
		val = v;
		reason = "";
	}
	ReturnVal() {
		val = 0;
		reason = "";
	}

	void show() {
		cout << reason << endl;
	}

	bool isFail() {
		return val < 0;
	}
};

#endif /* RETURNVAL_H_ */
