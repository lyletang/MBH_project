//方案二：奇数小灯和偶数小灯逐个闪烁，用户手离超声波传感器遮挡进入一定范围小灯全灭（20厘米）
//Author: Jiahui Tang
//Time: 2016-12-01

//import the necessary packages
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>

//define the HC-SR04/led
#define Trig	0
#define Echo	1
#define led1    21
#define led2    22
#define led3    23
#define led4    24
#define led5    25
#define led6    27
#define led7    28
#define led8    29

//init
void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);

	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	pinMode(led5, OUTPUT);
	pinMode(led6, OUTPUT);
	pinMode(led7, OUTPUT);
	pinMode(led8, OUTPUT);
}

//the distance detection, by the HC-SR04
float disMeasure(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);	 
	digitalWrite(Trig, LOW);
										
	while(!(digitalRead(Echo) == 1));
	//get the time of now
	gettimeofday(&tv1, NULL);		

	while(!(digitalRead(Echo) == 0));
	//get the time of now
	gettimeofday(&tv2, NULL);		 

	//the time(us)
	start = tv1.tv_sec * 1000000 + tv1.tv_usec;   
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	//the distance
	dis = (float)(stop - start) / 1000000 * 34000 / 2;  

	return dis;
}

int main(int argc, char* argv[])
{
	//the array of the led
	int led[8] = {21, 22, 23, 24, 25, 27, 28, 29};
	//define a temp value
	bool temp = true;
	//the distance
	float dis;

	if(wiringPiSetup() == -1)
	{ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ultraInit();
									
	digitalWrite(21, LOW);
	digitalWrite(22, LOW);
	digitalWrite(23, LOW);
	digitalWrite(24, LOW);
	digitalWrite(25, LOW);
	digitalWrite(27, LOW);
	digitalWrite(28, LOW);
	digitalWrite(29, LOW);
	
	//loop
	for(;;)
	{
		dis = disMeasure();
		
		if(dis < 20){
			digitalWrite(led1, LOW);
			digitalWrite(led2, LOW);
			digitalWrite(led3, LOW);
			digitalWrite(led4, LOW);
			digitalWrite(led5, LOW);
			digitalWrite(led6, LOW);
			digitalWrite(led7, LOW);
			digitalWrite(led8, LOW);
		}
		else
		{
			digitalWrite(led1, LOW);
			digitalWrite(led2, LOW);
			digitalWrite(led3, LOW);
			digitalWrite(led4, LOW);
			digitalWrite(led5, LOW);
			digitalWrite(led6, LOW);
			digitalWrite(led7, LOW);
			digitalWrite(led8, LOW);
		
			if(temp == true)
			{
				digitalWrite(led1, HIGH);
				digitalWrite(led3, HIGH);
				digitalWrite(led5, HIGH);
				digitalWrite(led7, HIGH);
			}
			else
			{
				digitalWrite(led2, HIGH);
				digitalWrite(led4, HIGH);
				digitalWrite(led6, HIGH);
				digitalWrite(led8, HIGH);
			}	
			temp = !temp;
		}

		//time delay
		delayMicroseconds(1000000);
		
		//print the distance
		printf("%0.2f m\n", &dis);
	}

	return 0;
}
