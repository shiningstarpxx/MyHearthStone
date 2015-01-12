/*
 * TargetCheck.h
 *
 *  Created on: 2015年1月11日
 *      Author: Joshua
 */

#ifndef HEADER_GAMEOBJECT_TARGETCHECK_H_
#define HEADER_GAMEOBJECT_TARGETCHECK_H_

class ReturnVal;

class TargetCheck {
public:
	virtual ReturnVal check(Target &t) = 0;
};

#endif /* HEADER_GAMEOBJECT_TARGETCHECK_H_ */
