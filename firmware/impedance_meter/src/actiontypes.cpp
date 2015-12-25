/*
 * actiontypes.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: consciousness
 */

#include "../include/actiontypes.h"

MeasureTetrodes::MeasureTetrodes()
{
	init(0);
}

MeasureTetrodes::MeasureTetrodes(TextDisplay **disp)
{
	init(disp);
}
MeasureTetrodes::~MeasureTetrodes()
{

}
void MeasureTetrodes::init(TextDisplay **disp)
{
	displays=disp;
}
void MeasureTetrodes::run()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			tetrodes[i].channels[j]->activateCH();
			tetrodes[i].channels[j]->impedance=impedance.measureImpedance();
			displays[i*4+j]->setNum(tetrodes[i].channels[j]->impedance);
			displays[i*4+j]->draw();
		}
	}
	extCH->activateCH();
}

DisplayImpTetrodes::DisplayImpTetrodes()
{
	init(0);
}
DisplayImpTetrodes::DisplayImpTetrodes(TextDisplay **disp)
{
	init(disp);
}
DisplayImpTetrodes::~DisplayImpTetrodes()
{

}
void DisplayImpTetrodes::init(TextDisplay **disp)
{
	displays=disp;
}
void DisplayImpTetrodes::run()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			displays[i*4+j]->setNum(tetrodes[i].channels[j]->impedance);
			displays[i*4+j]->draw();
		}
	}
}

MeasureChannel::MeasureChannel()
{
	init(0, 0, 0);
}
MeasureChannel::MeasureChannel(Channel *channel, TextDisplay *disp, double *impVal)
{
	init(channel, disp, impVal);
}
MeasureChannel::~MeasureChannel()
{

}
void MeasureChannel::init(Channel *channel, TextDisplay *disp, double *impVal)
{
	this->channel=channel;
	this->display=disp;
	this->impedanceVal=impVal;
}
void MeasureChannel::run()
{
	channel->activateCH();
	*impedanceVal=impedance.measureImpedance();
	channel->impedance=*impedanceVal;
	display->setNum(*impedanceVal);
	display->draw();
	extCH->activateCH();
}

DisplayImpCH::DisplayImpCH()
{
	init(0, 0);
}
DisplayImpCH::DisplayImpCH(Channel *channel, TextDisplay *disp)
{
	init(channel, disp);
}
DisplayImpCH::~DisplayImpCH()
{

}
void DisplayImpCH::init(Channel *channel, TextDisplay *disp)
{
	this->channel=channel;
	this->display=disp;
}
void DisplayImpCH::run()
{
	display->setNum(channel->impedance);
	display->draw();
}

ToggleChannel::ToggleChannel()
{
	init(0);
}
ToggleChannel::ToggleChannel(Channel *channel)
{
	init(channel);
}
ToggleChannel::~ToggleChannel()
{

}
void ToggleChannel::init(Channel *channel)
{
	this->channel=channel;
}
void ToggleChannel::run()
{
	channel->selected=!channel->selected;
}


PassCurrentTetrodes::PassCurrentTetrodes()
{
	init(0, 0);
}
PassCurrentTetrodes::PassCurrentTetrodes(Button **buttons, bool *lock)
{
	init(0, 0);
}
PassCurrentTetrodes::~PassCurrentTetrodes()
{

}
void PassCurrentTetrodes::init(Button **buttons, bool *lock)
{
	this->buttons=buttons;
	this->lock=lock;
}
void PassCurrentTetrodes::run()
{
	if(*lock)
	{
		return;
	}
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(tetrodes[i].channels[j]->selected)
			{
				buttons[i*4+j]->flashOn(VGA_RED);
				tetrodes[i].channels[j]->activateCH();
				curSrc.passCurrent();
				buttons[i*4+j]->flashOff();
			}
		}
	}
	extCH->activateCH();
}

PassCurrentCH::PassCurrentCH()
{
	init(0, 0, 0);
}
PassCurrentCH::PassCurrentCH(Button *button, Channel *channel, bool *lock)
{
	init(button, channel, lock);
}
PassCurrentCH::~PassCurrentCH()
{

}
void PassCurrentCH::init(Button *button, Channel *channel, bool *lock)
{
	this->button=button;
	this->channel=channel;
	this->lock=lock;
}
void PassCurrentCH::run()
{
	if(!channel->selected || !lock)
	{
		return;
	}
	button->flashOn(VGA_RED);
	channel->activateCH();
	curSrc.passCurrent();
	button->flashOff();
	extCH->activateCH();
}

PassCurrent::PassCurrent()
{
	init(0, 0, 0);
}
PassCurrent::PassCurrent(BaseAction **actionList, int numActs, bool *lock)
{
	init(actionList, numActs, lock);
}
PassCurrent::~PassCurrent()
{

}
void PassCurrent::init(BaseAction **actionList, int numActs, bool *lock)
{
	this->actionList=actionList;
	this->numActions=numActs;
	this->lock=lock;
}
void PassCurrent::run()
{
	if(*lock)
	{
		return;
	}

	for(int i=0; i<numActions; i++)
	{
		actionList[i]->run();
	}
}

SetVal::SetVal()
{
	init(0, 0, 0);
}
SetVal::SetVal(TextDisplay *disp, uint32 *val, uint32 setVal)
{
	init(disp, val, setVal);
}
SetVal::~SetVal()
{

}
void SetVal::init(TextDisplay *disp, uint32 *val, uint32 setVal)
{
	this->display=disp;
	this->val=val;
	this->setVal=setVal;
}
void SetVal::run()
{
	*val=setVal;
	display->setNum(*val);
	display->draw();
}


ToggleBool::ToggleBool()
{
	init(0);
}
ToggleBool::ToggleBool(bool *boolSwitch)
{
	init(boolSwitch);
}
ToggleBool::~ToggleBool()
{

}
void ToggleBool::init(bool *boolSwitch)
{
	this->boolSwitch=boolSwitch;
}
void ToggleBool::run()
{
	*boolSwitch=!(*boolSwitch);
}

PressButton::PressButton()
{
	init(0);
}
PressButton::PressButton(Button *button)
{
	init(button);
}
PressButton::~PressButton()
{

}
void PressButton::init(Button *button)
{
	this->button=button;
}
void PressButton::run()
{
	button->click();
}

SwitchPage::SwitchPage()
{
	init(0, 0, 0);
}
SwitchPage::SwitchPage(BasePage *thisPage, BasePage *nextPage, BasePage **curPage)
{
	init(thisPage, nextPage, curPage);
}
SwitchPage::~SwitchPage()
{

}
void SwitchPage::init(BasePage *thisPage, BasePage *nextPage, BasePage **curPage)
{
	this->thisPage=thisPage;
	this->nextPage=nextPage;
	this->currentPage=curPage;
}
void SwitchPage::run()
{
	thisPage->disable();
	nextPage->drawPage();
	*currentPage=nextPage;
}

ClearAllChannels::ClearAllChannels()
{

}
ClearAllChannels::~ClearAllChannels()
{

}
void ClearAllChannels::run()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			tetrodes[i].channels[j]->selected=false;
		}
	}

	extCH->selected=false;
	calCH->selected=false;
	ref1CH->selected=false;
	ref2CH->selected=false;

	extCH->activateCH();
}

CompondActions::CompondActions()
{
	init(0, 0);
}
CompondActions::CompondActions(BaseAction **actions, uint32 numActions)
{
	init(actions, numActions);
}
CompondActions::~CompondActions()
{

}
void CompondActions::init(BaseAction **actions, uint32 numActions)
{
	this->actions=actions;
	this->numActions=numActions;
}
void CompondActions::run()
{
	for(int i=0; i<numActions; i++)
	{
		actions[i]->run();
	}
}
