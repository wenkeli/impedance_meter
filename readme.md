Electronics to measure the resistance of multi-channel animal electrodes

This project uses the Analog Devices AD5934 impedance measurement chip with the STM32 micro-controller to measure 32 channel tetrode channel assemblies, and the ability to pass up to 5uA of current through a 2 MOhm electrode, useful for lesioning the tissue surrounding the electrodes.

The firmware folder contains the STM32 MCU code for controlling the AD5934 chip and defines the user interface on the touch screen.

The hardware folder contains the schematics and PCB designs of the electronics.