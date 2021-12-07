# ReadyToWakeClock
Simple ardino code to change LED colors based on time

I put some an adafruit neopixel ring inside an old clock in my kid's bedroom.

![GE Clock with LEDS](clock.gif "GE Clock with LEDS")

The pixels are run by an real time clock running on an Adafruit feather MO.

The only issue is that this Feather does not have an EEPROM so I can't keep track of whether the clock is set to daylight savings or not.

I could just track it in software but it would be confused if the power went out. Maybe I should just add a toggle switch to change the time ahead an hour or not.

