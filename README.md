# Particle LED Energy Saver

*A small blink pattern library to reduce the energy used by the Particle status LED*

This class is used like any other custom blink pattern class in the Particle environment. (See https://docs.particle.io/reference/firmware/photon/#ledstatus-class)

Special attention has been paid to making this work correctly even when the CPU is severely throttled.

## Description

This custom Status LED pattern will blink ON for about 50ms and OFF for about 100ms for each flash that is specified.

50ms is approximately the optimal on-time to register with maximum brightness in the eye, and 100ms provides enough off-time to easily distinguish the number of flashes.

For example, if `Period` is `1000` and `#Flashes` is `3`, the blink pattern will be:

```
    |--------350ms-------|-------------650ms------------------|
ON  ___      ___      ___
OFF    ______   ______   _____________________________________
    |----------------------1000 ms----------------------------|
```

Caution: This library does not make an effort to filter nonsensical parameters, so make sure at least that

`Period` > 150ms x `#Flashes`.

## Constructors:

`LEDStatusEnergySaver( Priority, Color )`

- Defaults to 1 flash, 1-second period

`LEDStatusEnergySaver( Priority, Color, Period )`

- Defaults to 1 flash

`LEDStatusEnergySaver( Priority, Color, Period, #Flashes )`

- Fully specified by parameters

### Priority

See Particle Documentation on the [LEDPriority Enum](https://docs.particle.io/reference/firmware/photon/#ledpriority-enum).

LEDPriority Value Name    | Description
--------------------------|--------------------------------------
`LED_PRIORITY_BACKGROUND` | long-lasting background indications
`LED_PRIORITY_NORMAL`     | regular, typically short indications
`LED_PRIORITY_IMPORTANT`  | important indications
`LED_PRIORITY_CRITICAL`   | critically important indications

### Color

`uint32_t`

See Particle documentation on the [Color parameter](https://docs.particle.io/reference/firmware/photon/#rgb-colors).

A color value with the red, green, and blue intensities packed in the format `0x00RRGGBB`.

Particle color constants | Description | Value
-------------------------|-------------|--------------
`RGB_COLOR_BLUE`           | blue        | `0x000000ff`
`RGB_COLOR_GREEN`          | green       | `0x0000ff00`
`RGB_COLOR_CYAN`           | cyan        | `0x0000ffff`
`RGB_COLOR_RED`            | red         | `0x00ff0000`
`RGB_COLOR_MAGENTA`        | magenta     | `0x00ff00ff`
`RGB_COLOR_YELLOW`         | yellow      | `0x00ffff00`
`RGB_COLOR_WHITE`          | white       | `0x00ffffff`
`RGB_COLOR_GRAY`           | gray        | `0x001f1f1f`
`RGB_COLOR_ORANGE`         | orange      | `0x00ff6000`

### Period

`uint32_t`

Repetition rate in number of milliseconds.

### Number of Flashes

`uint8_t`

The number of flashes to consecutively blink, separated by 100ms. There is no facility for flashing different colors in a flash repetition.

Using different numbers of flashes for different statuses is encouraged as an accommodation to color-blind users.

## Usage:

```cpp
// Declaration
LEDStatusEnergySaver LEDLowPowerSensorEnabled(
        LED_PRIORITY_NORMAL,    // Special status patterns will take priority
        0x0000ff00,             // Green
        1000,                   // 1-second period
        1);                     // 1 flash per period
LEDStatusEnergySaver LEDLowPowerSensorDisabled(
        LED_PRIORITY_NORMAL,    // Special status patterns will take priority
        0x00ff00ff,             // Magenta
        1000,                   // 1-second period
        2);                     // 2 flashes per period


// Return to default status LED behavior
void stateA() {
  LEDLowPowerSensorEnabled.setActive(false);
  LEDLowPowerSensorDisabled.setActive(false);
}

// Blink 1 green
void stateB() {
  LEDLowPowerSensorEnabled.setActive(true);
}

// Blink 2 magenta
void stateC() {
  LEDLowPowerSensorDisabled.setActive(true);
}
```
