/*
 * baseaction.h
 *
 *  Created on: Jun 7, 2014
 *      Author: consciousness
 */

#ifndef BASEACTION_H_
#define BASEACTION_H_

class BaseAction
{
public:
	virtual ~BaseAction();
	virtual void run()=0;
};



#endif /* BASEACTION_H_ */
