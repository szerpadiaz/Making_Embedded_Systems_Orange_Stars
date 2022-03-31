# Exercise 2: Investigate Project Boards


## Board 1: The Thunderboard Sense 2 from Silicon Labs(SLTB0004A)

The Thunderboard Sense 2 is a multi-sensor, multi- protocol development platform for IoT applications.
It is energy-friendly, provides several sensors and supports proprietary stacks and standard protocols such as Zigbee, Thread and Bluetooth.
Figure 1 shows a hardware block diagram for the board.

![Screenshot](SLTB004A_Board_BlockDiagram.jpg)

### What kind of processor is it?
The board has a EFR32MG12 Mighty Gecko Wireless SoC. This is an energy-friendly MCU with a highly integrated radio transceiver.
The MCU has a 38.4 MHz operating frequency, 1024 kB flash and 256 kB RAM
 
### How much Flash and RAM does it have? Any other memory types?
- Flash:1024 kB 
- RAM: 256 kB
- External Serial Flash: 8 Mbits (for OTA programming and data logging)

### Does it have any special peripherals?

The board has very interesting set of sensors, such as:
- Relative humidity and temperature sensor
- UV index and ambient light sensor
- Barometric pressure sensor
- Indoor air quality gas sensor
- 6-axis inertial sensor

### If it has an ADC, what are the features?

- Successive Approximation Register (SAR) architecture
- 12 bits resolution
- Up to 1Msps
- Configurable output resolution
- Integrated voltage references
- Integrated temperature sensor
- Support both: single-ended and differential input


### How much does the board cost vs what the processor costs? Is the processor in stock
anywhere?

- Board cost: 19,93 EUR 
- Processor cost: 6,21 EUR
- Availability: currently not available but it might become available in the next 3 weeks at: https://de.rs-online.com/, https://www.silabs.com/, https://www.mouser.de/ and https://www.digikey.de
