// Do not remove the include below
#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Utils.h"
#include "Motor.h"
uint8_t recvd_msg;
uint32_t starttime;


//The setup function is called once at PlutoX's hardware startup
void plutoInit()
{
	UART.init(UART3, BAUD_RATE_9600);
	Motor.init(M1);
	Motor.init(M2);
	Motor.init(M3);
	Motor.init(M4);
	Motor.initReversibleMotors();
	Motor.setDirection(M1,CLOCK_WISE);
	Motor.setDirection(M2,CLOCK_WISE);
	Motor.setDirection(M3,CLOCK_WISE);
	Motor.setDirection(M4,CLOCK_WISE);



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
	while(true)
	{
		recvd_msg = UART.read8(UART3);
		switch(recvd_msg){
		case 'a':
			starttime = millis();
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			while(millis() - starttime < 2000)
			{
				Motor.set(M1, 1000);
				Motor.set(M2, 1000);
				Motor.set(M3, 2000);
				Motor.set(M4, 2000);
			}
		case 'b':
			starttime = millis();
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			while(millis() - starttime < 2000)
			{
				Motor.set(M1, 1000);
				Motor.set(M2, 1000);
				Motor.set(M3, 2000);
				Motor.set(M4, 2000);
			}
		case 'c':
			starttime = millis();
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			while(millis() - starttime < 2000)
			{
				Motor.set(M1, 2000);
				Motor.set(M2, 2000);
				Motor.set(M3, 1000);
				Motor.set(M4, 1000);
			}
		case 'd':
			starttime = millis();
			Motor.setDirection(M1, ANTICLOCK_WISE);
		    Motor.setDirection(M2, ANTICLOCK_WISE);
		    Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			while(millis() - starttime < 2000)
			{
				Motor.set(M1, 2000);
				Motor.set(M2, 2000);
				Motor.set(M3, 1000);
				Motor.set(M4, 1000);
			}
		case 'e':
			Motor.set(M1, 1000);
			Motor.set(M2, 1000);
			Motor.set(M3, 1000);
			Motor.set(M4, 1000);
		default:
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


}




