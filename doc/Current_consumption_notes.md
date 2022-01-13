
Current Consumption notes
-----------------

| Brightness level | Current(ma) | Mode | 
| --- | --- | --- |
| 0 | 40 | HH:MM:SS | 
| 0  | 44 | HH:MM:DD:MM | 
| 2  | 66 | HH:MM:SS | 
| 2  | 80 | HH:MM:DD:MM | 
| 7  | 149 | HH:MM:SS| 
| 7  | 195 | HH:MM:DD:MM  | 
| n/a  | 31 | sleep | 

Note: As of first version, Sleep mode does not put micro-controller to sleep just 
turns off display. unit is designed to be powered from Wall mount not battery.

Also there are two power LEDS on TM1638 and RTC modules. which are drawing 
a signifcant amount of current perhaps ~10-20mA, these can be removed but are still on during these measurments. 
