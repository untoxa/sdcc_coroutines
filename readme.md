Stackful C coroutines example for the GAME BOY / SEGA MASTER SYSTEM / SEGA GAME GEAR
------------------------------------------------------------------------------------

Written for the GBDK-2020 v4.1.1 and above. May be useful for writing logic for 
your in-game actors using C. Support ROM banks.

This is sort of cooperative multitasking which only save/restore minimal state that 
is required by the SDCC ABI. Very lightweight, switching take all in all about 56 
cycles for the Game Boy.

![game gear example](/screenshot.png)

Also, see https://github.com/untoxa/gameboy_preemptive_multitasking