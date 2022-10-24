//Code for Project Drona, Team AUV-IITB
//Updated for new 6 motor design

// Do not remove the include below
#include "PlutoPilot.h"
#include "Estimate.h"
#include "Motor.h"
#include "Peripheral.h"

int16_t pwm_yaw, yaw, yaw0, yaw_err, yaw_diff, yaw_kd, yaw_kp, pwm_heave, z, z0, z_err, z_diff, z_kd, z_kp; //PD variables
uint8_t message; //UART Message
bool uart_status;

//The setup function is called once at PlutoX's hardware startup
void plutoInit()
{
//Add your hardware initialization code here
	setUserLoopFrequency(3.5);  //setting plutoLoop() frequency to the lowest possible limit
	UART.init(UART2, BAUD_RATE_9600); //initializing UART2 to receive control signal
	Motor.initReversibleMotors();
	Motor.init(M1);
	Motor.init(M2);
	Motor.init(M3);
	Motor.init(M4);
	Motor.init(M5);
	Motor.init(M6);
	Motor.setDirection(M1, CLOCK_WISE);
	Motor.setDirection(M2, CLOCK_WISE);
	Motor.setDirection(M3, CLOCK_WISE);
	Motor.setDirection(M4, CLOCK_WISE);
	Motor.set(M1, 1000);
	Motor.set(M2, 1000);
	Motor.set(M3, 1000);
	Motor.set(M4, 1000);
	Motor.set(M5, 1000);
	Motor.set(M6, 1000);


}




//The function is called once before plutoLoop() when you activate developer mode
void onLoopStart()
{
//Do your one time stuff here
	yaw0 = Angle.get(AG_YAW);
	z0 = Position.get(Z);

}



//The loop function is called in an endless loop
void plutoLoop()
{
//Add your repeated code here
	uart_status = UART.rxBytesWaiting(UART2);  //Function to be called before reading data from UART port
	if(uart_status)
	{
	    message = UART.read8(UART2);
	}
	if(message == 'f')   //stable
	{
		yaw = Angle.get(AG_YAW);
		yaw_err = yaw - yaw0;
		yaw_diff = Rate.get(Z);
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;

		if(pwm_yaw >= 0)
		{
			pwm_yaw = pwm_yaw + 1000;
            Motor.set(M5, pwm_yaw);
            Motor.set(M6, 1000);
		}
		else
		{
			pwm_yaw = -pwm_yaw + 1000;
			Motor.set(M5, 1000);
			Motor.set(M6, pwm_yaw);
		}

		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave >= 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
		}

		Motor.set(M3, pwm_heave);
		Motor.set(M4, pwm_heave);

	}

	if(message == 'a') //yaw left
	{
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave >= 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
		}

		Motor.set(M3, pwm_heave);
		Motor.set(M4, pwm_heave);

		Motor.set(M5, 1500);
		Motor.set(M6, 1000);
		yaw0 = Angle.get(AG_YAW);

	}

	if(message == 'b') //yaw right
	{
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave >= 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
		}

		Motor.set(M3, pwm_heave);
		Motor.set(M4, pwm_heave);

		Motor.set(M5, 1000);
		Motor.set(M6, 1500);
		yaw0 = Angle.get(AG_YAW);

	}

	if(message == 'c') //surge forward
	{
		yaw = Angle.get(AG_YAW);
		yaw_err = yaw - yaw0;
		yaw_diff = Rate.get(Z);
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;

		if(pwm_yaw >= 0)
		{
			pwm_yaw = pwm_yaw + 1000;
            Motor.set(M5, pwm_yaw);
            Motor.set(M6, 1000);
		}
		else
		{
			pwm_yaw = -pwm_yaw + 1000;
			Motor.set(M5, 1000);
			Motor.set(M6, pwm_yaw);
		}

		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave >= 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
		}

		Motor.set(M3, pwm_heave);
		Motor.set(M4, pwm_heave);

		Motor.setDirection(M1, CLOCK_WISE);
		Motor.setDirection(M2, CLOCK_WISE);
		Motor.set(M1, 2000);
		Motor.set(M2, 2000);

	}

	if(message == 'd')  //surge back
	{
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave >= 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
		}

		Motor.set(M3, pwm_heave);
		Motor.set(M4, pwm_heave);

		Motor.setDirection(M1, ANTICLOCK_WISE);
		Motor.setDirection(M2, ANTICLOCK_WISE);
		Motor.set(M1, 2000);
		Motor.set(M2, 2000);

	}

	if(message == 'e') //descend
	{

		yaw = Angle.get(AG_YAW);
		yaw_err = yaw - yaw0;
		yaw_diff = Rate.get(Z);
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;

		if(pwm_yaw >= 0)
		{
			pwm_yaw = pwm_yaw + 1000;
            Motor.set(M5, pwm_yaw);
            Motor.set(M6, 1000);
		}
		else
		{
			pwm_yaw = -pwm_yaw + 1000;
			Motor.set(M5, 1000);
			Motor.set(M6, pwm_yaw);
		}

		Motor.setDirection(M3, CLOCK_WISE);
		Motor.setDirection(M4, CLOCK_WISE);
		Motor.set(M3, 1500);
		Motor.set(M4, 1500);
		z0 = Position.get(Z);
	}

	if(message == 'g') //ascend
	{
		yaw = Angle.get(AG_YAW);
		yaw_err = yaw - yaw0;
		yaw_diff = Rate.get(Z);
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;

		if(pwm_yaw >= 0)
		{
			pwm_yaw = pwm_yaw + 1000;
            Motor.set(M5, pwm_yaw);
            Motor.set(M6, 1000);
		}
		else
		{
			pwm_yaw = -pwm_yaw + 1000;
			Motor.set(M5, 1000);
			Motor.set(M6, pwm_yaw);
		}

		Motor.setDirection(M1, ANTICLOCK_WISE);
		Motor.setDirection(M2, ANTICLOCK_WISE);
		Motor.set(M1, 1500);
		Motor.set(M2, 1500);
		z0 = Position.get(Z);
	}


}



//The function is called once after plutoLoop() when you deactivate developer mode
void onLoopFinish()
{
//Do your cleanup stuff here


}






