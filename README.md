Sensors
=======
An Arduino library for control systems.

## Example usage
```c++
/*
 * An on-off control, with a sensor on pin A0 and an actuator on pin 1.
 */

#include "Sensors.h"

// Create an AnalogSensor that reads from pin A0
AnalogSensor sensor(A0);
// Create an on-off controller that has an `int` internal state, and relies on the AnalogSensor `sensor`
OnOffController<int, AnalogSensor> controller(sensor);

void setup() { }

void loop() {
  digitalWrite(1, controller.update());
}
```
