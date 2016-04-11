To get temperature in degC, take the value of the binary number on the LED display and divide by 8.
The second to rightmost LED takes the value 1.

<Front Top of PCB>
_________________________________________________________________________
| LED10 | LED9  | LED8 | LED7 | LED6 | LED5 | LED4 | LED3 | LED2 | LED1 |
| = 256 | = 128 | = 64 | = 32 | = 16 | = 8  | = 4  | = 2  | = 1  | N/A  |
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
<Front Bottom of PCB>

So if LED10 and LED8 are on, the value = 265 + 64, and the temperature = (265 + 64)/8.
Which results in 40degC.
