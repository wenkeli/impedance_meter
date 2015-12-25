/*
 * pagetypes.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: consciousness
 */

#include "../include/pagetypes.h"

BasePage *curPage;

StartPage startPage;
ImpMeasurePage impMeasurePage;
CurPassPage curPassPage;
void initPages(UTFT *screen)
{
	startPage.init(screen);
	impMeasurePage.init(screen);
	curPassPage.init(screen);
	curPage=&startPage;
	curPage->drawPage();
}

StartPage::StartPage()
	:BasePage(buttonList, 3, displayList, 2, 0, 0, VGA_BLACK)
{
	buttonList[0]=&chkGNDButton;
	buttonList[1]=&runCurrentButton;
	buttonList[2]=&measureImpButton;

	displayList[0]=&groundImpValDisp;
	displayList[1]=&ohmLabel;

	bgColor=VGA_BLACK;//UTFT::rgbTo16Bit(0x55, 0x6B, 0x2F);

	groundImpValDisp.setParams(160-(16*2.5), 30, VGA_GRAY, bgColor, BigFont,
			INTLABEL, 5, "", 0, 1000);
	ohmLabel.setParams(205, 30, VGA_GRAY, bgColor, BigFont,
			STRLABEL, 4, "KOhm", 0, 1);

	chkGNDButton.setParams(&measureGND, 160-30, 60, 60, 40,
			UTFT::rgbTo16Bit(0x00, 0x4C, 0x99), UTFT::rgbTo16Bit(0x00, 0x80, 0xFF),
			VGA_WHITE, 7, SmallFont, STRLABEL,
			"CHK GND", 0, 1, false);
	runCurrentButton.setParams(&toRunCurrent, 80-45, 160, 90, 40,
			UTFT::rgbTo16Bit(0xCC, 0x00, 0x00), UTFT::rgbTo16Bit(0xFF, 0x33, 0x33),
			VGA_WHITE, 7, SmallFont, STRLABEL, "CURRENT",
			0, 1, false);

	measureImpButton.setParams(&toMeasureImp, 240-45, 160, 90, 40,
			UTFT::rgbTo16Bit(0x66, 0x00, 0xCC), UTFT::rgbTo16Bit(0x99, 0x33, 0xFF),
			VGA_WHITE, 10, SmallFont, STRLABEL, "IMPEADANCE",
			0, 1, false);

	measureGND.init(extCH, &groundImpValDisp, &extCH->impedance);

	toRunCurrent.init(this, &curPassPage, &curPage);
	toMeasureImp.init(this, &impMeasurePage, &curPage);
}
StartPage::~StartPage()
{

}
void StartPage::init(UTFT *screen)
{
	BasePage::init(screen);
}

ImpMeasurePage::ImpMeasurePage()
	:BasePage(buttonList, 5, displayList, 80, 0, 0, VGA_BLACK)
{
	int counter;

	bgColor=UTFT::rgbTo16Bit(0x38, 0x1E, 0x52);

	counter=0;
	for(int i=0; i<4; i++)
	{
		buttonList[counter]=&measureButtons[i];
		counter++;
	}
	buttonList[4]=&backButton;

	counter=0;
	for(int i=0; i<3; i++)
	{
		displayList[counter]=&miscCHImps[i];
		counter++;
	}
	for(int i=0; i<3; i++)
	{
		displayList[counter]=&miscCHLabels[i];
		counter++;
	}
	for(int i=0; i<8; i++)
	{
		displayList[counter]=&tetrodeLabels[i];
		counter++;
	}
	for(int i=0; i<32; i++)
	{
		displayList[counter]=&tetrodeCHs[i];
		counter++;
	}
	for(int i=0; i<32; i++)
	{
		displayList[counter]=&tetrodeImps[i];
		tetrodeImpPts[i]=&tetrodeImps[i];
		counter++;
	}
	displayList[78]=&unitLabel;
	displayList[79]=&tetrodeCHLabel;

	measureTetrodes.init(tetrodeImpPts);
//	dispTrodeImps.init(tetrodeCHPts);

	measureMiscCHs[0].init(extCH, &miscCHImps[0], &(extCH->impedance));
	measureMiscCHs[1].init(ref1CH, &miscCHImps[1], &(ref1CH->impedance));
	measureMiscCHs[2].init(ref2CH, &miscCHImps[2], &(ref2CH->impedance));

//	displayMiscCHs[0].init(extCH, &miscCHImps[0]);
//	displayMiscCHs[1].init(ref1CH, &miscCHImps[1]);
//	displayMiscCHs[2].init(ref2CH, &miscCHImps[2]);

	back.init(this, &startPage, &curPage);
}
ImpMeasurePage::~ImpMeasurePage()
{

}
void ImpMeasurePage::init(UTFT *screen)
{
	int fontX;
	int fontY;
	int curX;
	int curY;
	int buttonSY;
	int buttonSX;
	uint16 buttonColor;
	uint16 buttonTColor;
	buttonColor=UTFT::rgbTo16Bit(0x33, 0x66, 0x00);
	buttonTColor=UTFT::rgbTo16Bit(0x00, 0x99, 0x00);

	screen->setFont(SmallFont);
	fontX=screen->getFontXsize();
	fontY=screen->getFontYsize();

	for(int i=0; i<2; i++)
	{
		curX=fontX*10*i;
		for(int j=0; j<4; j++)
		{
			tetrodeLabels[i*4+j].setParams(curX, j*5*fontY,
					VGA_WHITE, bgColor, SmallFont, STRLABEL, 8, "", 0, 1);
			for(int k=0; k<4; k++)
			{
				tetrodeImps[(i*4+j)*4+k].setParams(curX+fontX*4, (j*5+k+1)*fontY,
						VGA_WHITE, bgColor, SmallFont, INTLABEL, 5, "", 0, 1000);
			}
			tetrodeCHs[(i*4+j)*4+0].setParams(curX, (j*5+0+1)*fontY,
					VGA_WHITE, bgColor, SmallFont, STRLABEL, 3, "CH1", 0, 1);
			tetrodeCHs[(i*4+j)*4+1].setParams(curX, (j*5+1+1)*fontY,
					VGA_WHITE, bgColor, SmallFont, STRLABEL, 3, "CH2", 0, 1);
			tetrodeCHs[(i*4+j)*4+2].setParams(curX, (j*5+2+1)*fontY,
					VGA_WHITE, bgColor, SmallFont, STRLABEL, 3, "CH3", 0, 1);
			tetrodeCHs[(i*4+j)*4+3].setParams(curX, (j*5+3+1)*fontY,
					VGA_WHITE, bgColor, SmallFont, STRLABEL, 3, "CH4", 0, 1);
		}
	}

	tetrodeLabels[0].setStr("Tetrode1");
	tetrodeLabels[1].setStr("Tetrode2");
	tetrodeLabels[2].setStr("Tetrode3");
	tetrodeLabels[3].setStr("Tetrode4");
	tetrodeLabels[4].setStr("Tetrode5");
	tetrodeLabels[5].setStr("Tetrode6");
	tetrodeLabels[6].setStr("Tetrode7");
	tetrodeLabels[7].setStr("Tetrode8");

	curX=fontX*21;
	curY=5;
	unitLabel.setParams(curX, curY, VGA_WHITE, bgColor, BigFont,
			STRLABEL, 9, "Unit:KOhm", 0, 1);
	curY=curY+25;

	tetrodeCHLabel.setParams(curX, curY, VGA_WHITE, bgColor, SmallFont,
			STRLABEL, 8, "Tetrodes", 0, 1);
	curY=curY+40;

	for(int i=0; i<3; i++)
	{
		miscCHLabels[i].setParams(curX, curY, VGA_WHITE, bgColor, SmallFont,
				STRLABEL, 7, "", 0, 1);
		miscCHImps[i].setParams(curX, curY+15, VGA_WHITE, bgColor, SmallFont,
				INTLABEL, 5, "", 0, 1000);
		curY=curY+40;
	}
	miscCHLabels[0].setStr("EXT CH");
	miscCHLabels[1].setStr("REF1 CH");
	miscCHLabels[2].setStr("REF2 CH");

	curY=25;
	buttonSY=30;
	buttonSX=8*fontX;
	measureButtons[0].setParams(&measureTetrodes, curX+buttonSX+5, curY,
			buttonSX, buttonSY, buttonColor, buttonTColor, VGA_WHITE, 7, SmallFont,
			STRLABEL, "MEASURE", 0, 1, false);

	curY=curY+40;

	for(int i=1; i<4; i++)
	{
		measureButtons[i].setParams(&measureMiscCHs[i-1], curX+buttonSX+5, curY,
				buttonSX, buttonSY, buttonColor, buttonTColor, VGA_WHITE, 7, SmallFont,
				STRLABEL, "MEASURE", 0, 1, false);
		curY=curY+40;
	}

	backButton.setParams(&back, curX, curY, buttonSX*2, buttonSY, buttonColor, buttonTColor,
			VGA_WHITE, 4, SmallFont, STRLABEL, "BACK", 0, 1, false);

	BasePage::init(screen);
}

CurPassPage::CurPassPage()
	:BasePage(buttonList, 43, displayList, 19, 0, 0, VGA_BLACK)
{
	int counter;

	uint32 startX;
	uint32 startY;

	uint16 buttonC;
	uint16 buttonTC;

	bgColor=UTFT::rgbTo16Bit(0x99, 0x00, 0x00);
	buttonC=UTFT::rgbTo16Bit(0xCC, 0x66, 0x00);
	buttonTC=UTFT::rgbTo16Bit(0xFF, 0x99, 0x33);

	currentLocked=true;

	startX=8;
	startY=15;
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			tetrodeCHs[i*4+j].setParams(&toggleTetrodeChannels[i*4+j],
					startX+i*32, startY+j*30, 30, 27, buttonC, buttonTC, VGA_WHITE, 3,
					SmallFont, FLOATLABEL, "", 0, 1000000, true);
			toggleTetrodeChannels[i*4+j].init(tetrodes[i].channels[j]);

			buttonList[i*4+j]=&tetrodeCHs[i*4+j];
			tetrodeBList[i*4+j]=&tetrodeCHs[i*4+j];
		}
	}

	startX=startX+15-8;
	counter=0;
	for(int i=0; i<8; i++)
	{
		tetrodeLabels[i].setParams(startX+32*i, 0, VGA_WHITE, bgColor,
				SmallFont, STRLABEL, 2, "", 0, 1);
		displayList[counter]=&tetrodeLabels[i];
		counter++;
	}
	tetrodeLabels[0].setStr("T1");
	tetrodeLabels[1].setStr("T2");
	tetrodeLabels[2].setStr("T3");
	tetrodeLabels[3].setStr("T4");
	tetrodeLabels[4].setStr("T5");
	tetrodeLabels[5].setStr("T6");
	tetrodeLabels[6].setStr("T7");
	tetrodeLabels[7].setStr("T8");

	startY=startY+15-6;
	for(int i=0; i<4; i++)
	{
		trodeCHLabels[i].setParams(0, startY+30*i, VGA_WHITE, bgColor,
				SmallFont, STRLABEL, 1, "", 0, 1);
		displayList[counter]=&trodeCHLabels[i];
		counter++;
	}
	trodeCHLabels[0].setStr("1");
	trodeCHLabels[1].setStr("2");
	trodeCHLabels[2].setStr("3");
	trodeCHLabels[3].setStr("4");

	startY=15;
	startX=320-50;
	back.init(this, &startPage, &curPage);
	backButton.setParams(&back, startX+5, startY, 40, 35, buttonC, buttonTC,
			VGA_WHITE, 4, SmallFont, STRLABEL, "BACK", 0, 1, false);
	buttonList[32]=&backButton;

	startY=startY+45;

	extCHLabel.setParams(startX, startY, VGA_WHITE, bgColor,
			SmallFont, STRLABEL, 3, "EXT", 0, 1000);
	displayList[counter]=&extCHLabel;
	counter++;
	toggleExtCH.init(extCH);
	startY=startY+15;
	extCHButton.setParams(&toggleExtCH, startX, startY, 45, 25, buttonC, buttonTC,
			VGA_WHITE, 5, SmallFont, INTLABEL, "", 0, 1000, true);
	buttonList[33]=&extCHButton;
	startY=startY+30;

	ref1CHLabel.setParams(startX, startY, VGA_WHITE, bgColor,
				SmallFont, STRLABEL, 4, "REF1", 0, 1000);
	displayList[counter]=&ref1CHLabel;
	counter++;
	toggleRef1CH.init(ref1CH);
	startY=startY+15;
	ref1CHButton.setParams(&toggleRef1CH, startX, startY, 45, 25, buttonC, buttonTC,
			VGA_WHITE, 5, SmallFont, INTLABEL, "", 0, 1000, true);
	buttonList[34]=&ref1CHButton;
	startY=startY+30;

	ref2CHLabel.setParams(startX, startY, VGA_WHITE, bgColor,
				SmallFont, STRLABEL, 4, "REF2", 0, 1000);
	displayList[counter]=&ref2CHLabel;
	counter++;
	toggleRef2CH.init(ref2CH);
	startY=startY+15;
	ref2CHButton.setParams(&toggleRef2CH, startX, startY, 45, 25, buttonC, buttonTC,
			VGA_WHITE, 5, SmallFont, INTLABEL, "", 0, 1000, true);
	buttonList[35]=&ref2CHButton;
	startY=startY+35;

	dispTrodeImps.init(tetrodeDisps);
	dispActs[0]=&dispTrodeImps;
	dispActs[1]=&extCHImps;
	dispActs[2]=&ref1CHImps;
	dispActs[3]=&ref2CHImps;
	dispImps.init(dispActs, 4);
	displayImpsButton.setParams(&dispImps, startX, startY, 45, 25, buttonC, buttonTC,
			VGA_WHITE, 4, SmallFont, STRLABEL, "DISP", 0, 1, false);
	buttonList[36]=&displayImpsButton;

	startY=30*4+15+5;
	startX=8+32*4;
	secLabel.setParams(startX+15, startY, VGA_WHITE, bgColor, SmallFont,
			STRLABEL, 4, "TIME", 0, 1);
	displayList[counter]=&secLabel;
	counter++;
	startY=startY+13;
	secDisp.setParams(startX+15, startY, VGA_WHITE, bgColor, SmallFont,
			INTLABEL, 4, "", 0, 1000);
	displayList[counter]=&secDisp;
	counter++;
	startY=startY+13;
	set5Sec.init(&secDisp, curSrc.getTimePt(), 5000);
	select5Sec.setParams(&set5Sec, startX, startY, 50, 27, buttonC, buttonTC,
			VGA_WHITE, 4, SmallFont, STRLABEL, "5sec", 0, 1, false);
	buttonList[37]=&select5Sec;

	startY=startY+33;
	set10Sec.init(&secDisp, curSrc.getTimePt(), 10000);
	select10Sec.setParams(&set10Sec, startX, startY, 50, 27, buttonC, buttonTC,
			VGA_WHITE, 5, SmallFont, STRLABEL, "10sec", 0, 1, false);
	buttonList[38]=&select10Sec;

	startX=startX-60;
	startY=30*4+15+5;
	uALabel.setParams(startX+15, startY, VGA_WHITE, bgColor, SmallFont,
			STRLABEL, 4, "uA", 0, 1);
	displayList[counter]=&uALabel;
	counter++;
	startY=startY+13;
	uADisp.setParams(startX+15, startY, VGA_WHITE, bgColor, SmallFont,
			INTLABEL, 2, "", 0, 1);
	displayList[counter]=&uADisp;
	counter++;

	startY=startY+13;
	set2uA.init(&uADisp, curSrc.getCurrentPt(), 2);
	select2uA.setParams(&set2uA, startX, startY, 50, 27, buttonC, buttonTC,
			VGA_WHITE, 3, SmallFont, STRLABEL, "2uA", 0, 1, false);
	buttonList[39]=&select2uA;

	startY=startY+33;
	set5uA.init(&uADisp, curSrc.getCurrentPt(), 5);
	select5uA.setParams(&set5uA, startX, startY, 50, 27, buttonC, buttonTC,
			VGA_WHITE, 3, SmallFont, STRLABEL, "5uA", 0, 1, false);
	buttonList[40]=&select5uA;

	startY=30*4+15+5+8;
	startX=5;
	toggleCurLock.init(&currentLocked);
	unlockCurrent.setParams(&toggleCurLock, startX, startY, 65, 80, buttonC, buttonTC,
			VGA_WHITE, 6, SmallFont, STRLABEL, "UNLOCK", 0, 1, true);
	buttonList[41]=&unlockCurrent;

	startX=8+32*4+55;
	passCurTrodes.init(tetrodeBList, &currentLocked);
	passCurActs[0]=&passCurTrodes;
	passCurExtCH.init(&extCHButton, extCH, &currentLocked);
	passCurActs[1]=&passCurExtCH;
	passCurRef1CH.init(&ref1CHButton, ref1CH, &currentLocked);
	passCurActs[2]=&passCurRef1CH;
	passCurRef2CH.init(&ref2CHButton, ref2CH, &currentLocked);
	passCurActs[3]=&passCurRef2CH;
	clickCurLock.init(&unlockCurrent);
	passCurActs[4]=&clickCurLock;
	runPassCurrent.init(passCurActs, 5, &currentLocked);
	passCurrent.setParams(&runPassCurrent, startX, startY, 65, 80, buttonC, buttonTC,
			VGA_WHITE, 7, SmallFont, STRLABEL, "RUN CUR", 0, 1, false);
	buttonList[42]=&passCurrent;
}
CurPassPage::~CurPassPage()
{

}
void CurPassPage::init(UTFT *screen)
{
	BasePage::init(screen);
	for(int i=0; i<32; i++)
	{
		tetrodeDisps[i]=tetrodeCHs[i].getLabelDisp();
	}
	extCHImps.init(extCH, extCHButton.getLabelDisp());
	ref1CHImps.init(ref1CH, ref1CHButton.getLabelDisp());
	ref2CHImps.init(ref2CH, ref2CHButton.getLabelDisp());
}
