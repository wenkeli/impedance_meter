/*
 * pagetypes.h
 *
 *  Created on: Jun 18, 2014
 *      Author: consciousness
 */

#ifndef PAGETYPES_H_
#define PAGETYPES_H_

#include <UTFT.h>
#include <UTFTGUIIncludes/elements/button.h>
#include <UTFTGUIIncludes/elements/rectangle.h>
#include <UTFTGUIIncludes/elements/textdisplay.h>

#include <UTFTGUIIncludes/actions/baseaction.h>

#include <UTFTGUIIncludes/containers/basepage.h>

#include "hardware.h"
#include "actiontypes.h"

class StartPage : public BasePage
{
public:
	StartPage();
	~StartPage();

	void init(UTFT *screen);

protected:
	Button *buttonList[3];
	TextDisplay *displayList[2];

	Button chkGNDButton;
	Button runCurrentButton;
	Button measureImpButton;

	TextDisplay groundImpValDisp;
	TextDisplay ohmLabel;

	MeasureChannel measureGND;
	SwitchPage toRunCurrent;
	SwitchPage toMeasureImp;
};

class ImpMeasurePage : public BasePage
{
public:
	ImpMeasurePage();
	~ImpMeasurePage();

	void init(UTFT *screen);

protected:
	Button *buttonList[5];
	TextDisplay *displayList[80];

	Button measureButtons[4];
	Button backButton;

	TextDisplay unitLabel;
	TextDisplay tetrodeCHLabel;
	TextDisplay miscCHLabels[3];
	TextDisplay miscCHImps[3];
	TextDisplay tetrodeLabels[8];
	TextDisplay tetrodeCHs[32];
	TextDisplay *tetrodeImpPts[32];
	TextDisplay tetrodeImps[32];

	MeasureTetrodes measureTetrodes;
	MeasureChannel measureMiscCHs[3];
//	DisplayImpTetrodes dispTrodeImps;
//	DisplayImpCH displayMiscCHs[3];

	SwitchPage back;

};


class CurPassPage : public BasePage
{
public:
	CurPassPage();
	~CurPassPage();

	void init(UTFT *screen);

protected:
	Button *buttonList[43];
	TextDisplay *displayList[19];

	Button tetrodeCHs[32];
	Button backButton;
	Button *tetrodeBList[32];

	Button extCHButton;
	Button ref1CHButton;
	Button ref2CHButton;

	Button displayImpsButton;

	Button select5Sec;
	Button select10Sec;

	Button select2uA;
	Button select5uA;

	Button unlockCurrent;
	Button passCurrent;

	TextDisplay tetrodeLabels[8];
	TextDisplay trodeCHLabels[4];
	TextDisplay extCHLabel;
	TextDisplay ref1CHLabel;
	TextDisplay ref2CHLabel;

	TextDisplay uADisp;
	TextDisplay secDisp;
	TextDisplay uALabel;
	TextDisplay secLabel;

	TextDisplay *tetrodeDisps[32];

	DisplayImpTetrodes dispTrodeImps;
	DisplayImpCH extCHImps;
	DisplayImpCH ref1CHImps;
	DisplayImpCH ref2CHImps;
	BaseAction *dispActs[4];
	CompondActions dispImps;

	SwitchPage back;
	ToggleChannel toggleTetrodeChannels[32];
	ToggleChannel toggleExtCH;
	ToggleChannel toggleRef1CH;
	ToggleChannel toggleRef2CH;

	SetVal set5Sec;
	SetVal set10Sec;
	SetVal set2uA;
	SetVal set5uA;

	ToggleBool toggleCurLock;

	PassCurrentTetrodes passCurTrodes;
	PassCurrentCH passCurExtCH;
	PassCurrentCH passCurRef1CH;
	PassCurrentCH passCurRef2CH;
	PressButton clickCurLock;
	BaseAction *passCurActs[5];
	PassCurrent runPassCurrent;

	bool currentLocked;
};

void initPages(UTFT *screen);
extern StartPage startPage;
extern ImpMeasurePage impMeasurePage;
extern CurPassPage curPassPage;

extern BasePage *curPage;


#endif /* PAGETYPES_H_ */
