// Do not remove the include below
#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Utils.h"
#include "Motor.h"
bool c1, c2, c3;
uint32_t starttime;


//The setup function is called once at PlutoX's hardware startup
void plutoInit()
{
	LED.flightStatus(DEACTIVATE);
	GPIO.init(Pin13, INPUT);
	GPIO.init(Pin15, INPUT);
	GPIO.init(Pin14, INPUT);
	Motor.init(M1);
	Motor.init(M2);
	Motor.init(M3);
	Motor.init(M4);
	Motor.initReversibleMotors();
	LED.set(GREEN, ON);
	Motor.setDirection(M1, CLOCK_WISE);
	Motor.setDirection(M2, CLOCK_WISE);
	Motor.setDirection(M3, CLOCK_WISE);
	Motor.setDirection(M4, CLOCK_WISE);
	Motor.set(M1, 1000);
	Motor.set(M2, 1000);
	Motor.set(M3, 1000);
	Motor.set(M4, 1000);




//Add your hardware initialization code here

}




//The function is called once before plutoLoop() when you activate developer mode
void onLoopStart()
{
//Do your one time stuff here

}



//The loop function is called in an endless loop
void plutoLoop()
{
//Add your repeated code here
	LED.set(GREEN, OFF);
	LED.set(BLUE, ON);
	while(true)
	{
		c1 = GPIO.read(Pin13);
		c2 = GPIO.read(Pin15);
		c3 = GPIO.read(Pin14);
		if(c1 == 0 && c2 == 0 && c3 == 0) //stop
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 1000);
			Motor.set(M4, 1000);
		}
		else if(c1 == 0 && c2 == 0 && c3 == 1) //forward
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.set(M1, 2000);
			Motor.set(M2, 2000);
			Motor.set(M3, 1000);
			Motor.set(M4, 1000);
		}
		else if(c1 == 0 && c2 == 1 && c3 == 1)  //backward
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			Motor.set(M1, 2000);
			Motor.set(M2, 2000);
			Motor.set(M3, 1000);
			Motor.set(M4, 1000);
		}
		else if(c1 == 1 && c2 == 0 && c3 == 0)  //left
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 2000);
			Motor.set(M4, 2000);
		}
		else if(c1 == 1 && c2 == 0 && c3 == 1)  //right
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 2000);
			Motor.set(M4, 2000);
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 1000);
			Motor.set(M4, 1000);
		}

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
	LED.set(BLUE, OFF);
	LED.set(RED, TOGGLE);


}




