# particle-LEDStatusEnergySaver
A small blink pattern library to reduce the energy used by the Particle status LED

This class is used like any other custom blink pattern class in the Particle environment. (See https://docs.particle.io/reference/firmware/photon/#ledstatus-class)

Usage:

```cpp
// Declaration
LEDStatusEnergySaver LEDLowPowerSensorEnabled(LED_PRIORITY_NORMAL, 0x0000ff00, 1000, 1);    // 1 green flash, once per second
LEDStatusEnergySaver LEDLowPowerSensorDisabled(LED_PRIORITY_NORMAL, 0x00ff00ff, 1000, 2);   // 2 magenta flashes, once per second

// Note: Using LED_PRIORITY_NORMAL allows important status events to supercede these normal operating status indications

// Default status LED behavior
void stateA {
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
