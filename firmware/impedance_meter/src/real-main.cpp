#include <wirish/HardwareSerial.h>
#include <wirish/wirish.h>

#include <UTFT.h>
#include <UTouch.h>

#include "../include/hardware.h"

#include "../include/pagetypes.h"

void setup(void)
{
	delay(3000);
//	Serial1.begin(9600);

	initHardware();

	initPages(&screen);
}

void loop(void)
{

//	x8Map.selectChannel(X8EXTCH);
////	Serial1.println(impedance.measureImpedance());
//
//	led0Pin.togglePin();
//	curSrc.passCurrent(5, 5000);
//	led0Pin.togglePin();
//	delay(1000);

	while(1)
	{
		bool endPress;

		int rejectedN;
		int numPoints;
		int x;
		int y;

		x=0;
		y=0;
		rejectedN=0;
		numPoints=0;

//		if(prevPage!=curPage)
//		{
//			curPage->drawPage();
//			prevPage=curPage;
//		}
		while(1)
		{
			int tempX;
			int tempY;

			endPress=true;
			for(int i=0; i<10; i++)
			{
				delay(5);

				if(tPanel.dataAvailable())
				{
					tPanel.read();
					tempX=320-tPanel.getY();
					tempY=tPanel.getX();
					endPress=false;
					break;
				}
			}
			if(endPress)
			{
				break;
			}

			if(rejectedN<5)
			{
				rejectedN++;
				continue;
			}

			x=x+tempX;
			y=y+tempY;
			numPoints++;
		}
		if(numPoints<=5)
		{
			continue;
		}

		x=x/numPoints;
		y=y/numPoints;

		curPage->checkPageClicked(x, y);
	}
}

// Standard libmaple init() and main.
//
// The init() part makes sure your board gets set up correctly. It's
// best to leave that alone unless you know what you're doing. main()
// is the usual "call setup(), then loop() forever", but of course can
// be whatever you want.

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
