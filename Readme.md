
Overview
--------------------
* Name : clock_number_3
* Title : Arduino Real Time Alarm Clock DS3231 with TM1638
* Description : Arduino Clock with Battery backup (real time clock), 
Time, Date, Alarm, Temperature, TM1638 seven segment module output and input, Sleep mode.
* Author: Gavin Lyons

Libraries
------------------------
In src folder you will find the arduino ino file with the source code.
It includes two libraries. Both are found in arduino library manager.
The first one is written by me. Urls included.

1. <TM1638plus.h> [URL Link to library](https://github.com/gavinlyonsrepo/TM1638plus)
2. <DS3232RTC.h>  [URL Link to library](https://github.com/JChristensen/DS3232RTC)


Operation:
------------------------
The RTC is provided by a DS3231 RTC I2C module.
The DS3231 is a low-cost, extremely accurate I2C
real-time clock (RTC).
The device incorporates a battery input, and maintains
accurate timekeeping when main power to the device
is interrupted. The integration of the crystal resonator
enhances the long-term accuracy of the device as well
as reduces the piece-part count in a manufacturing line.
The DS3231 is available in commercial and industrial
temperature ranges, and is offered in a 16-pin, 300-mil
SO package.

The RTC maintains seconds, minutes, hours, day, date,
month, and year information. The date at the end of the
month is automatically adjusted for months with fewer
than 31 days, including corrections for leap year. The
clock operates in either the 24-hour or 12-hour format
with an AM/PM indicator. Two programmable time-of-day
alarms and a programmable square-wave output are
provided. Address and data are transferred serially
through an I2C bidirectional bus.

This project allows saving of an Alarm in the RTC and triggers on the SQW output of DS3231
An Buzzer is connected as an alarm. You may wish to modify these modules,
depending on your use case, some users remove the power led, charging circuit and pull up resistors.
See here for more info [URL link](https://protosupplies.com/product/ds3231-rtc-with-eeprom-module/)

![ScreenShot clock](https://github.com/gavinlyonsrepo/Arduino_Clock_3/blob/master/doc/image/RTC.jpg)

![ScreenShot clock](https://github.com/gavinlyonsrepo/Arduino_Clock_3/blob/master/doc/image/RTC2.jpg)

The I/O to user is provided by a TM1638 Module (8 Push buttons 8 LEDS (LED & KEY))
These TM1638 modules are commonly available. 
They consist of an 8-digit seven segment display with decimal points,
8 Leds and 8 Push buttons. 

![ module ](https://github.com/gavinlyonsrepo/pic_16F18446_projects/blob/master/images/TM1638.jpg)


![ sch ](https://github.com/gavinlyonsrepo/pic_16F18446_projects/blob/master/images/TM1638_2.jpg)


Menu modes , button function
--------------------------------
A spreadsheet in "doc folder of this repo shows the button functions,
on TM1638 module for the various menus. File is called Menus.gnumeric.

Parts List
------------------------------
In the doc folder there is an eagle subfolder with the BOM and schematic image.


Schematic
---------------------------

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_3/blob/master/doc/eagle/clock3.png)


Copyright
-------------------------------

Copyright (C) 2019 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
