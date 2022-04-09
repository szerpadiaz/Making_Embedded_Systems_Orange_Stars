# Exercise 3: Make Blinky

The application blink an USER-LED while the USER-BUTTON is being pressed. 
Once the button is released, then the LED stops blinking.

To improve the user experience the the button uses and interrupt for debouncing
the button signal.

The figure below shows the software architecture:

![Screenshot](sw_diagram.jpg)

## Implementation details:
- Board: STM32F411E-Disco
- Build environment: STM32CubeMxIDE
- The impelmentation code re-uses some of the HALs provided by the vendor. 

Some of the hardware registers accessed by the code are:

- The Register to turn on and off the LED is at address: 0x40020C18 (See claculation below)
	- LED is located at Pin 12 in GPIO port D, to turn it on or off, the bit 12 in the register_address has to be set/reset.
		- base-address = AHB1PERIPH_BASE + 0x0C00UL = (PERIPH_BASE + 0x00020000UL) + 0x0C00UL = (0x40000000UL + 0x00020000UL) + 0x0C00UL = 0x40020C00
        - register_address = base_address + Address_offset = 0x40020C00 + 0x18 = 0x40020C18

- Registers read in order to find out the state of the button: 0x40020010 (Similar calculation as for the LED)
	- Button is located at Pin 0 in port 4, so bit 0 in the register_address has to be read to find out the state of the button.