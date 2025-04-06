# Navigator-RC-Robot
Bachelor Final Project - Navigator RC Robot for room cartography (using MCUs and sensors)

Status Update 16/03/2025:
-not much firmware was written recently, was focused on configuring and selecting correct hardware
-caquired all necessary hardware for testing as well as crafting the robot
-final project shall use a smaller "blackpill STM MCU" as it is more compact; firmware written for the Nucleo board is compatible

-now need to write firmware for robot movement (rotation, speed control etc.) will be written first and tested, so Timer drivers are needed for PWM signals
-trying to decide what language to use for the ESP32 board, thinking Arduino is good enough
-after movement is tested will start with sensor drivers

Status Update 19/03/2025:
-polished functions written for clock config, need to check them for bugs too
-looking forward to testing the PWM signal 
-it is expected to have a freq of 50 MHz if clock config was correct
-GPIO and TIMER config can have bugs too

Status Update 25/03/2025:
-succesful PWM output tested today
-RCC didnt need low frequency, Timer frequency can be configured via Period
-now soldering wires to control the motors
-will also need to write some API for motor control

Status Update 27/03/2025:
-soldered wires for the DC motors
-changed timer for PWM outputs to TIM2
-will need to test this too

Status Update 06/03/2025:
-added movement logic in MOVEMENT.c file 






