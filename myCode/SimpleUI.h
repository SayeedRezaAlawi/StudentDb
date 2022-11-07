/*
 * SimpleUI.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_
#include "StudentDb.h"

class SimpleUI
{
private:
	StudentDb * db;
public:
	SimpleUI(StudentDb& db);
	void run();
	virtual ~SimpleUI();
};

#endif /* SIMPLEUI_H_ */
