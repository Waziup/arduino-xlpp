# Extended Low Power Payload for Arduino

This library allows you to encode and decode light-weight payloads on an Arduino.
XLPP payload format is useful for sending IoT data over a low bandwidth network like LoRaWAN.
It is an extended version of [Cayenne Low Power Payload](https://www.thethingsnetwork.org/docs/devices/arduino/api/cayennelpp.html).

Example
--------
Here is a quick example showing how to encode a temperature, a voltage and a string over XLPP.

```
#include <xlpp.h>

void setup()
{
  Serial.begin(38400);
}

XLPP xlpp(120);

void loop(void)
{
  // Create xlpp payload
  xlpp.reset();
  xlpp.addTemperature(1, 90.0); // °C
  xlpp.addVoltage(2, 2); // Volts
  xlpp.addString(3, "test");

  // Display and use payload
  for (int i = 0; i < xlpp.len ; i++) Serial.print( xlpp.buf[i] , HEX);

```

All the functions that you can use can be found in: https://github.com/Waziup/arduino-xlpp/blob/main/src/xlpp.h
