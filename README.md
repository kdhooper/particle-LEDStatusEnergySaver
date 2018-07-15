# Particle LED Energy Saver

*A small blink pattern library to reduce the energy used by the Particle status LED*

This class is used like any other custom blink pattern class in the Particle environment. (See https://docs.particle.io/reference/firmware/photon/#ledstatus-class)

Special attention has been paid to making this work correctly even when the CPU is severely throttled.

## Description

This custom Status LED pattern will blink ON for about 50ms and OFF for about 100ms for each flash that is specified.

50ms is approximately the optimal on-time to register with maximum brightness in the eye, and 100ms provides enough off-time to easily distinguish the number of flashes.

For example, if `Period` is `1000` and `#Flashes` is `3`, the blink pattern will be:

```
    |--------350ms-------|-----------650ms------------------|
ON  ___      ___      ___
OFF    ______   ______   _____________________________________
    |----------------------1000 ms----------------------------|
```

Caution: This library does not make an effort to filter nonsensical parameters, so make sure at least that

`Period` > 50ms x `#Flashes` + 100ms x `#Flashes`.

Constructor:
`LEDStatusEnergySaver( Priority, Color, Period, #Flashes )`

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
