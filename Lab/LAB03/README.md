# Lab 3 - Buttons/Switches / Traffic Light

This project follows the cumulative structure of LAB01 and LAB02. It uses one STM32CubeIDE project for Exercises 3-10. The final application is selected by the normal `main.c` flow; the earlier exercises are represented by the modules added along the way.

## Project configuration

- MCU: STM32F103C6Tx, HSI 8 MHz
- TIM2 update interval: selected by `LAB3_TIMER_TICK_MS` (1 ms default; 100 ms for the second Exercise 4 case)
- Traffic lights: horizontal red/green/yellow on PA1/PA2/PA3, vertical red/yellow/green on PA4/PA5/PA6; active low
- Seven-segment horizontal bus: PB0-PB6; vertical bus: PB7-PB13, active low
- Seven-segment digit enables: PA7-PA10, active low
- Buttons: PA11 `MODE`, PA12 `INCREASE`, PA13 `SET`, active low with pull-ups

## Exercise mapping

| Exercise | Code or artifact |
| --- | --- |
| 1 | FSM design belongs in the report/design folder. |
| 2 | Proteus schematic uses the pin map above. |
| 3 | `LAB03.ioc`, generated STM32 project and GPIO/timer setup. |
| 4 | `app_config.h` selects a 1 ms or 100 ms tick; TIM2 uses prescaler 799 and derives ARR from the selected tick. |
| 5 | `button.c/.h` debounces the three buttons and generates one press event. |
| 6 | `traffic_app.c` implements modes and `seven_segment.c` multiplexes the displays. |
| 7-9 | The same edit-mode code changes the red, amber and green duration values. |
| 10 | `traffic_app.c` integrates the normal traffic sequence, editing modes and display. |

## Demo flow

1. Build the project and load `Build/Lab03_TrafficLight_Fitted.hex` into the STM32 component in the working Proteus project. The original Downloads HEX is kept intact.
2. The default mode is Mode 1 (normal traffic-light operation).
3. Press `MODE` to enter red-duration editing (Mode 2), then press `MODE` again for amber (Mode 3), green (Mode 4), and back to normal.
4. In Modes 2-4, `INCREASE` changes the selected duration from 1 to 99 seconds and `SET` saves it and returns to normal mode.
5. The selected colour LEDs blink at 2 Hz while editing. Both two-digit displays show the selected duration.

The normal cycle is horizontal green, horizontal yellow, vertical green, vertical yellow. The other road remains red. Red duration is coupled to green plus yellow. `tools/build.ps1` builds the source with ARM GCC and emits a separate HEX file. Pin details are in `PINMAP.md`.
