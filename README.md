# AMIT-PROJECT
AMIT graduation project

Introduction
	A smart home design which you can control your home lighting and Air-conditioning using a Bluetooth application on smart phone.
        
  
Requirements
        •	Bluetooth application on a smart phone.

        •	An LCD screen to display user information.

        •	A secure login system with blocking for 2 minutes if login credential entered wrong for more than 3 times.

        •	A Led to indicate if login blocked or not.

        •	And 7 segment display to display required air temperature.

        •	A temperature sensor to sense room temperature and turn the AC ON/OFF based on required temperature

        •	A 2 micro controller to interface with each other, the first is to handle use info and run main system (Master) and the other to receive instructions from the main and act based on it (slave).


Required Drivers
        •	LCD-2x16 driver for displaying info

        •	AT-mega32 DIO drivers for displaying temperature 

        •	SPI Driver for micro controller communication 

        •	UART Driver for Bluetooth connection (virtual terminal)

        •	Seven segment driver using BCD decoder

        •	ADC (analog digital converter) for reading temperature

        •	LED driver for Enable and Disable LED as indicators

