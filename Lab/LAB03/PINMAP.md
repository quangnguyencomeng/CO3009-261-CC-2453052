# LAB03 working Proteus pin map

Extracted from the demonstrated HEX and cross-checked against the Proteus project.

| Signal | MCU pin | Polarity |
| --- | --- | --- |
| Horizontal red/green/yellow | PA1 / PA2 / PA3 | Low = on |
| Vertical red/yellow/green | PA4 / PA5 / PA6 | Low = on |
| Digit enables en0/en1/en2/en3 | PA7 / PA8 / PA9 / PA10 | Low = enabled |
| Horizontal segments a-g | PB0-PB6 | Low = lit |
| Vertical segments a-g | PB7-PB13 | Low = lit |
| MODE / INCREASE / SET | PA11 / PA12 / PA13 | Low = pressed; pull-up |

The two segment buses are independent. The corresponding horizontal and vertical digits are scanned together. HSI is 8 MHz; TIM2 prescaler 7999, auto-reload 9 gives a 10 ms interrupt.
