/*
 * actiontypes.h
 *
 *  Created on: Jun 18, 2014
 *      Author: consciousness
 */

#ifndef ACTIONTYPES_H_
#define ACTIONTYPES_H_

#include <UTFTGUIIncludes/actions/baseaction.h>
#include <UTFTGUIIncludes/elements/textdisplay.h>
#include <UTFTGUIIncludes/elements/button.h>
#include <UTFTGUIIncludes/elements/rectangle.h>
#include <UTFTGUIIncludes/containers/basepage.h>

#include <wirish/HardwareSerial.h>

#include "hardware.h"

class MeasureTetrodes : public BaseAction
{
public:
	MeasureTetrodes();
	MeasureTetrodes(TextDisplay **disp);
	~MeasureTetrodes();

	void init(TextDisplay **disp);
	void run();

private:
	TextDisplay **displays;
};

class DisplayImpTetrodes: public BaseAction
{
public:
	DisplayImpTetrodes();
	DisplayImpTetrodes(TextDisplay **disp);
	~DisplayImpTetrodes();

	void init(TextDisplay **disp);
	void run();

private:
	TextDisplay **displays;
};

class MeasureChannel : public BaseAction
{
public:
	MeasureChannel();
	MeasureChannel(Channel *channel, TextDisplay *disp, double *impVal);
	~MeasureChannel();
	void init(Channel *channel, TextDisplay *disp, double *impVal);
	void run();
private:
	Channel *channel;
	TextDisplay *display;
	double *impedanceVal;
};

class DisplayImpCH : public BaseAction
{
public:
	DisplayImpCH();
	DisplayImpCH(Channel *channel, TextDisplay *disp);
	~DisplayImpCH();
	void init(Channel *channel, TextDisplay *disp);
	void run();
private:
	Channel *channel;
	TextDisplay *display;
};

class ToggleChannel : public BaseAction
{
public:
	ToggleChannel();
	ToggleChannel(Channel *channel);
	~ToggleChannel();
	void init(Channel *channel);
	void run();
private:
	Channel *channel;
};

class PassCurrentTetrodes : public BaseAction
{
public:
	PassCurrentTetrodes();
	PassCurrentTetrodes(Button **buttons, bool *lock);
	~PassCurrentTetrodes();

	void init(Button **buttons, bool *lock);
	void run();

private:
	Button **buttons;
	bool *lock;
};

class PassCurrentCH : public BaseAction
{
public:
	PassCurrentCH();
	PassCurrentCH(Button *button, Channel *channel, bool *lock);

	~PassCurrentCH();

	void init(Button *button, Channel *channel, bool *lock);
	void run();

private:
	Button *button;
	Channel *channel;
	bool *lock;
};

class PassCurrent : public BaseAction
{
public:
	PassCurrent();
	PassCurrent(BaseAction **actionList, int numActs, bool *lock);

	~PassCurrent();

	void init(BaseAction **actionList, int numActs, bool *lock);
	void run();

private:
	BaseAction **actionList;
	int numActions;
	bool *lock;
};

class SetVal : public BaseAction
{
public:
	SetVal();
	SetVal(TextDisplay *disp, uint32 *val, uint32 setVal);

	~SetVal();

	void init(TextDisplay *disp, uint32 *val, uint32 setVal);
	void run();

private:
	TextDisplay *display;
	uint32 *val;
	uint32 setVal;
};

class ToggleBool : public BaseAction
{
public:
	ToggleBool();
	ToggleBool(bool *boolSwitch);

	~ToggleBool();

	void init(bool *boolSwitch);
	void run();

private:
	bool *boolSwitch;
};

class PressButton : public BaseAction
{
public:
	PressButton();
	PressButton(Button *button);

	~PressButton();

	void init(Button *button);
	void run();

private:
	Button *button;
};

class SwitchPage : public BaseAction
{
public:
	SwitchPage();
	SwitchPage(BasePage *thisPage, BasePage *nextPage, BasePage **curPage);

	~SwitchPage();

	void init(BasePage *thisPage, BasePage *nextPage, BasePage **curPage);
	void run();

private:
	BasePage *thisPage;
	BasePage *nextPage;
	BasePage **currentPage;
};

class ClearAllChannels : public BaseAction
{
public:
	ClearAllChannels();
	~ClearAllChannels();

	void run();
};

class CompondActions : public BaseAction
{
public:
	CompondActions();
	CompondActions(BaseAction **actions, uint32 numActions);

	~CompondActions();

	void init(BaseAction **actions, uint32 numActions);
	void run();

private:
	BaseAction **actions;
	uint32 numActions;
};

#endif /* ACTIONTYPES_H_ */
