# PicMicrocontrollerLabPracticals
Experiments and lab practicals using a Pic Microcontroller (C language)

Note: Variable names and words printed on the Display are in Spanish.

This repository contains different experiments and practicals on a PIC microcontroller using C:

1.- 4-Bit walk: This code turns on LEDs sequentially from left to right and thn turns them off from right to left. A potentiometer regulates the speed.

2.- Temperature control: A set point between 0 and 100 is chosen using the push buttons in the circuit. By oushing on the OK button the temperature and set point are shown on the Display. After clicking OK again, the comparison between these values (<, >, =) is shown and a corresponding LED is turned on.

3.- Membrane Swicth Keyboard (Matrix Keyboard): The display shows the key pressed and the number of the key.

4.- Counter from 0-99: By pressing the asterisc on the keyboard, the limit of the counter can be established (between 0 and 99). Once the asterisc is pressed again the counter starts (and shows it to the display) with a delay of 100 ms between the numbers.

5.- Level control: A voltage divider from 0-5V simulates the water level that is shown in the display with integers. A set point is chosen using the keyboard. After measuring and chosing the set point, if the push button is pressed, in the lower right part of the display a "L" is shown (for filling), "V" (for emptying) or "E" (equilibrium)

6.- Counter with memory: A limit of the counter is chosen using the keyboard with a confirmation between the choice of units and tens. Then, the delay between numbers is chosen by using the keyboard. There two push buttons in the circuit that A) save the current count in the EEPROM so that when B) is pressed, the counter is reset to start in the saved value. 

7.- 256 datapoints table in EEPROM: A 3 digit datapoint is chosen to be saved, then, the memory address where it should be saved is chosen. To change between screens the asterisc needs to be pressed. Once that process is concluded, the data and the address are shown. If in that screen the "#" is pressed, the screen "get data" is shown. By entering an adress in that screen, the datapoint is fetched and shown for half a second and goes back to the "get data" screen. If a number greater than 255 is chosen, an "Invalid number" screen is shown.

8.- Unidiricetional Communiction: First, the channel is chosen (between 0-4 with an invalid channel screen if not chosen between 0 and 4) and then the channel and the ADC measure of that channel is sent to another PIC that displays the data
