// Do not remove the include below
#include "PlutoPilot.h"
#include "Motor.h"
#include "Utils.h"

//The setup function is called once at PlutoX's hardware startup
void plutoInit()
{
//Add your hardware initialization code here
    Motor.init(M2);
    Motor.init(M1);
    Motor.init(M3);
    Motor.init(M4);
    Motor.initReversibleMotors();
    Motor.setDirection(M1, CLOCK_WISE);
    Motor.setDirection(M2, CLOCK_WISE);
    Motor.setDirection(M3, CLOCK_WISE);
    Motor.setDirection(M4, CLOCK_WISE);
}

uint32_t starttime;


//The function is called once before plutoLoop() when you activate developer mode
void onLoopStart()
{
//Do your one time stuff here

}



//The loop function is called in an endless loop
void plutoLoop()
{
//Add your repeated code here
	starttime = millis();
	while(true)
	{
		while(millis() - starttime < 3000)
		{
			Motor.set(M1, 2000);
			Motor.set(M2, 2000);
		}
		starttime = millis();
		while(millis() - starttime < 3000)
		{
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 2000);
			Motor.set(M4, 2000);
		}
		break;
	}
}



//The function is called once after plutoLoop() when you deactivate developer mode
void onLoopFinish()
{
//Do your cleanup stuff here
    Motor.set(M1, 1000);
    Motor.set(M2, 1000);
    Motor.set(M3, 1000);
    Motor.set(M4, 1000);

}
