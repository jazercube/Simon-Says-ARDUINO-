The circuit construction includes 4 yellow LEDs, 5 red LEDs, 1 green control LED and 5 pushbuttons. 
Each LED is connected to a 330ohm resistor, and the pushbuttons use the Arduino's internal PULLUP resistor
When the Arduino is connected to power, the control LED will start to flash with a delay of 300ms to indicate that is is operational.
When the initialisation pushbutton is pressed, the control LED will switch off, indicating that the circuit is about to reveal the random pattern
One of the red LED will flash n number of times, where n is the number of randomly generated patterns that is about to be revealed. n can be preset in the code, the default value is n = 3.
The  remaining 4 red LED will start to flash a random pattern 4 bits long. It is the users job to memorise the said pattern on the fly.
The red control LED will flash in sequence with the random pattern flashes, to signal to the user that the next pattern is about to be shown.
Once the pattern reveal stage is completed, the green control LED will start to flash rapidly to indicate to the user to begin inputting the patterns that they recall
The user will then use the 4 pushbuttons to input the recalled pattern. The yellow LEDs will toggle on and off in response
The initialisation pushbutton will be pressed to clear the yellow LEDs and prepare for the input of the next pattern
Once n is reached, the code automatically determines if the user got all patterns right or wrong
If any one pattern is wrong - the user LOOSES, and the red LEDs will blink slowly
If ALL patterns matches - the user WINS and all LEDs will flash rapidly.
The green control LED will flash very slowly to indicate the circuit needs resetting.
