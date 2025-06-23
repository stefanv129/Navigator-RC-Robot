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

Status Update 09/06/2025:
-long time no see, focused on hardware for a while
-migrated code and testing on the smaller Adafruit STM32F411 blackpill, which will be used in final implementation
-managed to use TIM2 to output PWM signals on its 4 channels, perfect for my movement functions

Status Update 11/06/2025:
-for some reason PA1 and PA5 GPIOS give out VDD instead of TIM2 CH2 even though they are configured for AF01
-had to use PB3 instead for that channel which is asymmetrical
-hopefully no other needed pins have such problems, I will need I2C and UART
-found a way to set and reset PWM outputs consistently
-now the driveFWD function works as intended
-some function and variable names could still be cleaner, more macros are needed
-didnt stick to a writing convention :(((

Status Update 23/06/2025:
-configured 4 PWM channels from TIM2 with success
-created an interrupt based delay using TIMER1 that uses a randomly generated delay value
-tested all driving states
-switched from chloride 9V battery to 4xAA
-should still test everything using external power supply
-will now try to test the car on the ground
-afterwards will try to implement the distance sensor interrupt
-problem is sensor is orientated upwards...




