//Code for Project Drona, Team AUV-IITB
//Updated for new 6 motor design

// Do not remove the include below
#include "PlutoPilot.h"
#include "Estimate.h"
#include "Motor.h"
#include "Peripheral.h"

int16_t pwm_yaw, yaw, yaw0, yaw_err, yaw_diff, yaw_kd, yaw_kp, pwm_heave, z, z0, z_err, z_diff, z_kd, z_kp, pwm_pitch, pitch, pitch_diff, pitch_kd, pitch_kp, pwm_roll, roll, roll_diff, roll_kd, roll_kp; //PD variables
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
		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		if(pwm_pitch > 0)
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			pwm_pitch = pwm_pitch + 1000;
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			pwm_pitch = -pwm_pitch + 1000;
		}

		Motor.set(M1, pwm_pitch);
		Motor.set(M2, pwm_pitch);

		yaw = Angle.get(AG_YAW);
		yaw_diff = Rate.get(Z);
		yaw_err = yaw - yaw0;
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;
		if(pwm_yaw > 0)
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

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave > 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
		}

	}


	if(message == 'a') //yaw left
	{
		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		if(pwm_pitch > 0)
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			pwm_pitch = pwm_pitch + 1000;
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			pwm_pitch = -pwm_pitch + 1000;
		}

		Motor.set(M1, pwm_pitch);
		Motor.set(M2, pwm_pitch);

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave > 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
		}

		Motor.set(M5, 1500);
		Motor.set(M6, 1000);
		yaw0 = Angle.get(AG_YAW);

	}

	if(message == 'b') //yaw right
	{
		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		if(pwm_pitch > 0)
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			pwm_pitch = pwm_pitch + 1000;
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			pwm_pitch = -pwm_pitch + 1000;
		}

		Motor.set(M1, pwm_pitch);
		Motor.set(M2, pwm_pitch);

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave > 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
		}

		Motor.set(M5, 1000);
		Motor.set(M6, 1500);
		yaw0 = Angle.get(AG_YAW);
	}

	if(message == 'c') //surge forward
	{
		yaw = Angle.get(AG_YAW);
		yaw_diff = Rate.get(Z);
		yaw_err = yaw - yaw0;
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;
		if(pwm_yaw > 0)
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

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave > 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
		}

		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		Motor.setDirection(M1, CLOCK_WISE);
		Motor.setDirection(M2, CLOCK_WISE);
		if(pwm_pitch > 0)
		{
			Motor.set(M1, 1600 - pwm_pitch);
			Motor.set(M2, 1600 + pwm_pitch);
		}
		else
		{
			Motor.set(M1, 1600 + pwm_pitch);
			Motor.set(M2, 1600 - pwm_pitch);
		}

	}

	if(message == 'd')  //surge back
	{
		yaw = Angle.get(AG_YAW);
		yaw_diff = Rate.get(Z);
		yaw_err = yaw - yaw0;
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;
		if(pwm_yaw > 0)
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

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		z = Position.get(Z);
		z_err = z - z0;
		z_diff = Velocity.get(Z);
		pwm_heave = z_kp * z_err + z_kd * z_diff;
		if(pwm_heave > 0)
		{
			pwm_heave = pwm_heave + 1000;
			Motor.setDirection(M3, ANTICLOCK_WISE);
			Motor.setDirection(M4, ANTICLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
		}
		else
		{
			pwm_heave = -pwm_heave + 1000;
			Motor.setDirection(M3, CLOCK_WISE);
			Motor.setDirection(M4, CLOCK_WISE);
			if(pwm_roll > 0)
			{
				Motor.set(M3, pwm_heave + pwm_roll);
				Motor.set(M4, pwm_heave - pwm_roll);
			}
			else
			{
				Motor.set(M3, pwm_heave - pwm_roll);
				Motor.set(M4, pwm_heave + pwm_roll);
			}
		}

		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		Motor.setDirection(M1, ANTICLOCK_WISE);
		Motor.setDirection(M2, ANTICLOCK_WISE);
		if(pwm_pitch > 0)
		{
			Motor.set(M1, 1600 + pwm_pitch);
			Motor.set(M2, 1600 - pwm_pitch);
		}
		else
		{
			Motor.set(M1, 1600 - pwm_pitch);
			Motor.set(M2, 1600 + pwm_pitch);
		}

	}

	if(message == 'e') //descend
	{
		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		if(pwm_pitch > 0)
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			pwm_pitch = pwm_pitch + 1000;
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			pwm_pitch = -pwm_pitch + 1000;
		}

		Motor.set(M1, pwm_pitch);
		Motor.set(M2, pwm_pitch);

		yaw = Angle.get(AG_YAW);
		yaw_diff = Rate.get(Z);
		yaw_err = yaw - yaw0;
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;
		if(pwm_yaw > 0)
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

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		Motor.setDirection(M3, ANTICLOCK_WISE);
		Motor.setDirection(M4, ANTICLOCK_WISE);
		if(pwm_roll > 0)
		{
			Motor.set(M3, 1600 - pwm_roll);
			Motor.set(M4, 1600 + pwm_roll);
		}
		else
		{
			Motor.set(M3, 1600 + pwm_roll);
			Motor.set(M4, 1600 - pwm_roll);
		}
		z0 = Position.get(Z);
	}

	if(message == 'g') //ascend
	{
		pitch = Angle.get(AG_PITCH);
		pitch_diff = Rate.get(Y);
		pwm_pitch = pitch_kp * pitch + pitch_kd * pitch_diff;
		if(pwm_pitch > 0)
		{
			Motor.setDirection(M1, ANTICLOCK_WISE);
			Motor.setDirection(M2, CLOCK_WISE);
			pwm_pitch = pwm_pitch + 1000;
		}
		else
		{
			Motor.setDirection(M1, CLOCK_WISE);
			Motor.setDirection(M2, ANTICLOCK_WISE);
			pwm_pitch = -pwm_pitch + 1000;
		}

		Motor.set(M1, pwm_pitch);
		Motor.set(M2, pwm_pitch);

		yaw = Angle.get(AG_YAW);
		yaw_diff = Rate.get(Z);
		yaw_err = yaw - yaw0;
		pwm_yaw = yaw_kp * yaw_err + yaw_kd * yaw_diff;
		if(pwm_yaw > 0)
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

		roll = Angle.get(AG_ROLL);
		roll_diff = Rate.get(X);
		pwm_roll = roll_kp * roll + roll_kd * roll_diff;
		Motor.setDirection(M3, CLOCK_WISE);
		Motor.setDirection(M4, CLOCK_WISE);
		if(pwm_roll > 0)
		{
			Motor.set(M3, 1600 + pwm_roll);
			Motor.set(M4, 1600 - pwm_roll);
		}
		else
		{
			Motor.set(M3, 1600 - pwm_roll);
			Motor.set(M4, 1600 + pwm_roll);
		}
		z0 = Position.get(Z);
	}


}



//The function is called once after plutoLoop() when you deactivate developer mode
void onLoopFinish()
{
//Do your cleanup stuff here


}






