# MBH_project
the Respberry project

准备：
    
	    硬件：树莓派，led小灯，杜邦线，300R电阻，超声波测距传感器（HC-SR04）。
        软件：如果使用c语言编程，需要安装wiringPi包；
		如果使用的Python，则是需要RPi.GPIO包，可以通过$sudo apt-get install python-RPi.GPIO安装
		（如果使用较新的debian，就不需要准备了，都自带了）。
开始：
    
	连接HC-SR04：vcc对应raspi的2号针脚，即5v电源口；Trig对应11号；Echo对应12号；Gnd对应6号，即ground接地引脚。
    连接led：1号led正极接29号；2号led正极接31号；3号led正极接33号；4号led正极接35号；
            5号led正极接37号；6号led正极接36号；7号led正极接38号；8号led正极接40号。
            所有led负极一起接到raspi的39号接地引脚。
    电阻：为了防止led短路，电流过大烧坏树莓派，可以在每个led正极处接一个300R电阻。
    
代码：
    
	https://github.com/lsy1020/MBH_project
