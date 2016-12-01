#!/usr/bin/env python
#!coding:utf-8

#方案二：奇数小灯和偶数小灯逐个闪烁，用户手离超声波传感器遮挡进入一定范围小灯全灭(20厘米)
#Author: Jiahui Tang
#Time: 2016-11-30

#import the necessary packages
import RPi.GPIO as GPIO
import time

#define the led
led1 = 29
led2 = 31
led3 = 33
led4 = 35
led5 = 37
led6 = 36
led7 = 38
led8 = 40

#the array of the led
led = [led1, led2, led3, led4, led5, led6, led7, led8]
led_jishu = [led1, led3, led5, led7]
led_oushu = [led2, led4, led6, led8]

#the distance detection, by the HC-SR04
def checkdist():
	GPIO.output(11, GPIO.HIGH)
	time.sleep(0.000015)
	GPIO.output(11, GPIO.LOW)
	while not GPIO.input(12):
		pass
	t1 = time.time()
	while GPIO.input(12):
		pass
	t2 = time.time()
	
	return (t2-t1) * 340 / 2

#set the GPIO's mode
GPIO.setmode(GPIO.BOARD)

#initialize the led
for i in led:
	GPIO.setup(i, GPIO.OUT, initial = GPIO.LOW)

	
#the i/o(Trig, Echo) of the HC-SR04
GPIO.setup(11, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(12, GPIO.IN)

#define a temp value
temp = True

#ready
time.sleep(2)

#main
try:
	#loop
	while True:
		if checkdist() < 0.2:
			for i in led:
				GPIO.output(i, GPIO.LOW)
		else:
			for i in led:
				GPIO.output(i, GPIO.LOW)
			
			if temp == True:
				for i in led_jishu:
					GPIO.output(i, GPIO.HIGH)
			else:
				for i in led_oushu:
					GPIO.output(i, GPIO.HIGH)
			
			temp = not temp
		
		#time delay
		time.sleep(0.5)
		
		#print the distance
		print '%0.2f m' %checkdist()

#security measures
except KeyboardInterrupt:
	GPIO.cleanup()
