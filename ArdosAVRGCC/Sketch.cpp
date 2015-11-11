/* Author: Kizito Nkurikiyeyezu
* Created: 11-Nov-2015
* Compiler:  AVR/GNU C Compiler
* File Version: 0.1
* Status: Initial Release
* Descriptions: 
*			ArdOS is a powerful but compact multitasking operating system for the Arduino series of microcontroller
*			boards centered around the Atmel ATmega 168, 328, 1280 and 2560 microcontrollers. This repository allows user \
*			to use Ardos in Atmel studio (at the moment, it is compiled with AS version 7.0. with AVR8/GNU C Compiler : 4.9.2.
*			ArdOS features: Full compatibility with the Arduino libraries and IDE. A small compact kernel. 
*			A multitasking priority-based scheduler for hard real-time applications. A true sleep function that frees the 
*			microcontroller to perform other tasks. Binary and counting semaphores. Mutex locks and conditional variables.
*			First-in-first-out (FIFO) message queues. Priority message queues. Configurable. You can exclude parts of ArdOS from
*			compilation to minimize memory usage, and control the stack size of each task. For more information, please visit Ardos'
*			repository https://bitbucket.org/ctank/ardos-ide/wiki/Home
  Copyright:
           This program is free software: you can redistribute it and/or modify
           it under the terms of the GNU General Public License as published by
           the Free Software Foundation, either version 3 of the License, or
           (at your option) any later version.
           
           This program is distributed in the hope that it will be useful,
           but WITHOUT ANY WARRANTY; without even the implied warranty of
           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
           GNU General Public License for more details.
           
           You should have received a copy of the GNU General Public License
           along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
*/


#include <Arduino.h>
#include "Ardos/kernel.h"
#include "Ardos/sema.h"


//Function prototypes
void setup();
void loop();

#define LED1 9
#define  LED2 6
TOSSema sema;
unsigned char flag=1;

/* 
	This program is a simple demonstration of how to use the semaphore from ISR.
	It assumes that LEDs are connected to pins 6 and 9, and that a pushbutton has been connected to pull pin 2 high when pressed 
	The LED at pin 9 will flash at a rate of 4 times per second, while the LED at pin 6 will be toggled whenever you press the push button.
	It is based on the Ardos demo.
*/

void task1(void *p)
{
	
	while(1)
	{		
		OSTakeSema(&sema);
		if(flag)
			digitalWrite(LED2, HIGH);
		else
			digitalWrite(LED2, LOW);
	}
}

void task2(void *p)
{
	while(1)
	{
		digitalWrite(LED1, HIGH);
		OSSleep(125);
		digitalWrite(LED1, LOW);
		OSSleep(125);		
	}
}

void int0ISR()
{
  flag=!flag;
  OSGiveSema(&sema);
}

#define NUM_TASKS  2

void setup()
{
	OSInit(NUM_TASKS);
        attachInterrupt(0, int0ISR, RISING);
        
	pinMode(9, OUTPUT);
	pinMode(6, OUTPUT);
	
	// Create a binary semaphore with initial value 0
	OSCreateSema(&sema, 0, 1);		
	OSCreateTask(0, task1, NULL);
	OSCreateTask(1, task2, NULL);
	OSRun();
}

void loop()
{
  // Does nothing

}
