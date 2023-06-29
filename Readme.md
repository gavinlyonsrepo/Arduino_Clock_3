
Overview
--------------------
* Name : Arduino Clock 3
* Title : Arduino Real Time Alarm Clock DS3231 with TM1638 
* Description : 

Arduino Clock with Battery backup (real time clock), 
Time, Date, Alarm, Temperature, TM1638 seven segment module output and input, Display , Sleep mode.

* Author: Gavin Lyons

Table of contents
---------------------------

  * [Overview](#overview)
  * [Table of contents](#table-of-contents)
  * [Hardware](#hardware)
  * [Schematic](#schematic)
  * [Software](#software)

Hardware
------------------------
The RTC is provided by a DS3231 RTC I2C module.
The DS3231 is a low-cost, extremely accurate I2C
real-time clock (RTC).
The device incorporates a battery input, and maintains
accurate timekeeping when main power to the device
is interrupted. The RTC maintains seconds, minutes, hours, day, date,
month, and year information.  Two programmable time-of-day
alarms and a programmable square-wave output are
provided. 

This project allows saving of an Alarm in the RTC and triggers on the SQW output of DS3231.
Pressing S1 stops the Alarm once it is switched on.
An Buzzer is connected as an alarm. You may wish to modify these modules,
depending on your use case, some users remove the power led, charging circuit and pull up resistors. Schematic  of module in doc sub-folder.
See here for more info [URL link](https://protosupplies.com/product/ds3231-rtc-with-eeprom-module/)

![ScreenShot clock](https://github.com/gavinlyonsrepo/Arduino_Clock_3/blob/master/doc/image/RTC.jpg)

The I/O to user is provided by a TM1638 Module (8 Push buttons 8 LEDS (LED & KEY))
These TM1638 modules are commonly available. 
They consist of an 8-digit seven segment display with decimal points,
8 Leds and 8 Push buttons. 

![ module ](https://github.com/gavinlyonsrepo/pic_16F18446_projects/blob/master/images/TM1638.jpg)

Notes on current consumption found in a file in doc folder.

Schematic
---------------------------

In the doc folder there is an eagle subfolder with the BOM and schematic image.

![ScreenShot schematic](https://github.com/gavinlyonsrepo/Arduino_Clock_3/blob/master/doc/eagle/clock3.png)

Software
--------------------------------

**Menu modes**

A spreadsheet in doc subfolder of this repo shows the button functions(S1 to S8),
on TM1638 module for the various menus. File is called Menus.ods.

**Libraries**

It includes two libraries. Both are found in arduino library manager.
The first one is written by Author.  Note the DS3232RTC library 
has been heavily updated in Version 2.0.0 and is no longer backward compatible.
See [github issue 1](https://github.com/gavinlyonsrepo/Arduino_Clock_3/issues/1)

| Library name | Version | Author | Link |
| --- | --- | --- | --- |
| TM1638plus.h | 1.4.0 | Gavin Lyons | [URL Link to library](https://github.com/gavinlyonsrepo/TM1638plus) |
| DS3232RTC.h  | 1.2.6 | JChristensen | [URL Link to library](https://github.com/JChristensen/DS3232RTC) |

