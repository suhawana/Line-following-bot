# Line-following-bot
Line following bot follows the line based on the  principle of  reflection and absorption of white light
LFR consists of microcontroller (main brain) Arduino UNO , motor driver L298N , IR sensors
Here, the code in arduino IDE represent different analog and digital pins of microcontroller
A1, A2, A3, A4, A5 are the analog pins in microcintroller 
Array of 5 sensor is used to take the reading of white line on black background 
Digital pins of arduino UNO are connected with motor driver 
PID algorithm is applied o regulate temperature, flow, pressure, speed and other process variables. PID (proportional integral derivative) controllers use a control loop feedback mechanism to control process variables and are the most accurate and stable controller.
To regulate the speed of LFR; constraints has to be given
digitalWrite() is used to write a HIGH or a LOW value to a digital pin
Serial Monitor is used to print the output on desktop 
analogWrite() can be used to light a LED at varying brightnesses or drive a motor at various speeds
analogRead( ) function reads the value from the A0, A1, A2, A3, A4, A5 analog pin present on the Arduino board
pinMode() configures the specified pin to behave either as an input or an output
delay is to provide to reduce the wobbling of the bot 
after implement the connections bot will follow white line on black background
