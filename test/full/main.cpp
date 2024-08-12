#include <stdio.h>
#include <string.h>
#include "../../src/xlpp.h"

int sprintXLPP(char *buffer, XLPP &xlpp);
void printXlPPHex(XLPP &xlpp);
char buffer[1024];

#define XLPP_TEST(FN_ADD, EXPECTED) \
	xlpp.reset(); \
	xlpp.FN_ADD; \
	printf("%s 0x", #FN_ADD); \
	printXlPPHex(xlpp); \
	if(sprintXLPP(buffer, xlpp) < 0) e = 1; \
	printf(" \"%s\"\n", buffer); \
	if (strcmp(buffer, EXPECTED) != 0) \
	{ \
		printf("  expected: %s\n", EXPECTED); \
		e = 1; \
	}

int main() {
	int e = 0;
	XLPP xlpp(120);

	////////////////////////////
	// LPP Types

	// 1 byte, 1 unsigned
	XLPP_TEST(addDigitalInput(0x12), "Digital Input: 18 (0x12)");
	XLPP_TEST(addDigitalInput(0), "Digital Input: 0 (0x00)"); // min
	XLPP_TEST(addDigitalInput(0xff), "Digital Input: 255 (0xff)"); // max
	// 1 byte, 1 unsigned
	XLPP_TEST(addDigitalOutput(0x13), "Digital Output: 19 (0x13)");
	XLPP_TEST(addDigitalOutput(0), "Digital Output: 0 (0x00)"); // min
	XLPP_TEST(addDigitalOutput(0xff), "Digital Output: 255 (0xff)"); // max
	// 2 bytes, 0.01 signed
	XLPP_TEST(addAnalogInput(12.34), "Analog Input: 12.34");
	XLPP_TEST(addAnalogInput(327.67), "Analog Input: 327.67"); // max
	XLPP_TEST(addAnalogInput(-327.68), "Analog Input: -327.68"); // min
	// 2 bytes, 0.01 signed
	XLPP_TEST(addAnalogOutput(56.78), "Analog Output: 56.78");
	XLPP_TEST(addAnalogOutput(327.67), "Analog Output: 327.67"); // max
	XLPP_TEST(addAnalogOutput(-327.68), "Analog Output: -327.68"); // min
	// 2 bytes, 1 unsigned
	XLPP_TEST(addLuminosity(1000), "Luminosity: 1000 lux");
	XLPP_TEST(addLuminosity(0), "Luminosity: 0 lux"); // min
	XLPP_TEST(addLuminosity(0xffff), "Luminosity: 65535 lux"); // max
	// 1 byte
	XLPP_TEST(addPresence(1), "Presence: yes");
	XLPP_TEST(addPresence(0), "Presence: no");
	// 2 bytes, 0.1 signed
	XLPP_TEST(addTemperature(10.2), "Temperature: 10.2 °C");
	XLPP_TEST(addTemperature(3276.7), "Temperature: 3276.7 °C"); // max
	XLPP_TEST(addTemperature(-3276.8), "Temperature: -3276.8 °C"); // min
	// 2 bytes, 0.5 unsigned
	XLPP_TEST(addRelativeHumidity(44.5), "Relative Humidity: 44.5 %");
	XLPP_TEST(addRelativeHumidity(0), "Relative Humidity: 0.0 %"); // min
	XLPP_TEST(addRelativeHumidity(100), "Relative Humidity: 100.0 %"); // max
	// 6 bytes total, 2 bytes each, 0.001 signed
	XLPP_TEST(addAccelerometer(0.024, 1.202, -0.501), "Accelerometer: X 0.024 g, Y 1.202 g, Z -0.501 g");
	XLPP_TEST(addAccelerometer(32.767, 32.767, 32.767), "Accelerometer: X 32.766 g, Y 32.766 g, Z 32.766 g"); // max, (float 32.767 is rounded to 32.766)
	XLPP_TEST(addAccelerometer(-32.768, -32.768, -32.768), "Accelerometer: X -32.768 g, Y -32.768 g, Z -32.768 g"); // min
	// 2 bytes, 0.1 unsigned
	XLPP_TEST(addBarometricPressure(1000), "Barometric Pressure: 1000.0 hPa");
	XLPP_TEST(addBarometricPressure(0), "Barometric Pressure: 0.0 hPa"); // min
	XLPP_TEST(addBarometricPressure(6553.5), "Barometric Pressure: 6553.5 hPa"); // max
	// 6 bytes total, 2 bytes each, 0.01 signed
	XLPP_TEST(addGyrometer(0.24, 1.21, -0.51), "Gyrometer: X 0.24 °/s, Y 1.21 °/s, Z -0.51 °/s");
	XLPP_TEST(addGyrometer(327.67, 327.67, 327.67), "Gyrometer: X 327.67 °/s, Y 327.67 °/s, Z 327.67 °/s"); // max
	XLPP_TEST(addGyrometer(-327.68, -327.68, -327.68), "Gyrometer: X -327.68 °/s, Y -327.68 °/s, Z -327.68 °/s"); // min
	// 9 bytes total, 3 bytes each, 0.0001 signed for Lat+Lon, 0.01 signed for Alt
	XLPP_TEST(addGPS(12.3456, 34.5678, 123.45), "GPS: lat 12.3456, lon 34.5678, alt 123.45");
	XLPP_TEST(addGPS(90, 180, 3276.70), "GPS: lat 90.0000, lon 180.0000, alt 3276.70"); // max
	XLPP_TEST(addGPS(-90, -180, -3276.80), "GPS: lat -90.0000, lon -180.0000, alt -3276.80"); // min

	////////////////////////////
	// XLPP Types

	// 2 bytes, 0.01 unsigned
	XLPP_TEST(addVoltage(1.23), "Voltage: 1.23 V");
	XLPP_TEST(addVoltage(0), "Voltage: 0.00 V"); // min
	XLPP_TEST(addVoltage(655.35), "Voltage: 655.34 V"); // max (float 655.35 is rounded to 655.34)
	// 2 bytes, 0.001 unsigned
	XLPP_TEST(addCurrent(2.312), "Current: 2.312 A");
	XLPP_TEST(addCurrent(0), "Current: 0.000 A"); // min
	XLPP_TEST(addCurrent(65.535), "Current: 65.535 A"); // max
	// 4 bytes, 1 unsigned
	XLPP_TEST(addFrequency(20), "Frequency: 20 Hz");
	XLPP_TEST(addFrequency(20000), "Frequency: 20000 Hz");
	XLPP_TEST(addFrequency(4294967295), "Frequency: 4294967295 Hz"); // max
	XLPP_TEST(addFrequency(0), "Frequency: 0 Hz"); // min
	// 1 byte, 1-100 unsigned
	XLPP_TEST(addPercentage(1), "Percentage: 1 %");
	XLPP_TEST(addPercentage(56), "Percentage: 56 %");
	XLPP_TEST(addPercentage(100), "Percentage: 100 %"); // max
	XLPP_TEST(addPercentage(0), "Percentage: 0 %"); // min
	// 2 bytes, 1 signed
	XLPP_TEST(addAltitude(456), "Altitude: 456 m");
	XLPP_TEST(addAltitude(32767), "Altitude: 32767 m"); // max
	XLPP_TEST(addAltitude(-32768), "Altitude: -32768 m"); // min
	// 2 bytes, 1 unsigned
	XLPP_TEST(addConcentration(1234), "Concentration: 1234 ppm");
	XLPP_TEST(addConcentration(0), "Concentration: 0 ppm"); // min
	XLPP_TEST(addConcentration(65535), "Concentration: 65535 ppm"); // max
	// 2 bytes, 1 unsigned
	XLPP_TEST(addPower(1234), "Power: 1234 W");
	XLPP_TEST(addPower(0), "Power: 0 W"); // min
	XLPP_TEST(addPower(65535), "Power: 65535 W"); // max
	// 4 bytes, 0.001 unsigned
	XLPP_TEST(addDistance(1234.567), "Distance: 1234.567 m");
	XLPP_TEST(addDistance(0), "Distance: 0.000 m"); // min
	XLPP_TEST(addDistance(4294967.040), "Distance: 4294967.000 m"); // max (float rounding)
	// 4 bytes, 0.001 unsigned
	XLPP_TEST(addEnergy(1234.567), "Energy: 1234.567 kWh");
	XLPP_TEST(addEnergy(0), "Energy: 0.000 kWh"); // min
	XLPP_TEST(addEnergy(4294967.040), "Energy: 4294967.000 kWh"); // max (float rounding)
	// 2 bytes, 0.02 unsigned
	XLPP_TEST(addDirection(123.76), "Direction: 123.76 deg");
	XLPP_TEST(addDirection(-25.24), "Direction: -25.24 deg");
	XLPP_TEST(addDirection(0.00), "Direction: 0.00 deg")
	XLPP_TEST(addDirection(-360.00), "Direction: -360.00 deg")
	XLPP_TEST(addDirection(360.00), "Direction: 360.00 deg")
	// 4 bytes
	XLPP_TEST(addUnixTime(1723193923), "Unix Time: 1723193923");
	XLPP_TEST(addUnixTime(946681200), "Unix Time: 946681200"); // year 2000
	XLPP_TEST(addUnixTime(2147483647), "Unix Time: 2147483647"); // max, year 2038
	// 3 bytes, 1 byte per RGB
	XLPP_TEST(addColour(0x12, 0x34, 0x56), "Colour: R 18, G 52, B 86 (#123456)");
	XLPP_TEST(addColour(0x64, 0x95, 0xed), "Colour: R 100, G 149, B 237 (#6495ED)"); // cornflower blue
	XLPP_TEST(addColour(0, 0, 0), "Colour: R 0, G 0, B 0 (#000000)"); // black
	XLPP_TEST(addColour(255, 255, 255), "Colour: R 255, G 255, B 255 (#FFFFFF)"); // white
	// 1 byte, 0/1
	XLPP_TEST(addSwitch(1), "Switch: on");
	XLPP_TEST(addSwitch(0), "Switch: off");

	////////////////////////////
	// XLPP Types

	// max 8 bytes, 1 signed
	XLPP_TEST(addInteger(123456789), "Integer: 123456789");
	XLPP_TEST(addInteger(-123456789), "Integer: -123456789");
	XLPP_TEST(addInteger(0), "Integer: 0");
	XLPP_TEST(addInteger(1), "Integer: 1");
	// max 24 bytes, 0-24 chars
	const char* helloWorld = "Hello, World!";
	char buf[2048];
	sprintf(buf, "String: \"%s\"", helloWorld);
	XLPP_TEST(addString(helloWorld), buf);
	const char* loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt.";
	sprintf(buf, "String: \"%s\"", loremIpsum);
	XLPP_TEST(addString(loremIpsum), buf);

	// TODO: Add Objects test
	// TODO: Add Array test

	// 0 byte, true / false, data is stored in type byte so there is no payload
	XLPP_TEST(addBool(true), "Bool: true");
	XLPP_TEST(addBool(false), "Bool: false");
	// 0 byte, null
	XLPP_TEST(addNull(), "Null");
	// n bytes
	XLPP_TEST(addBinary((const uint8_t*)"\x01\x02\x03\x04\x05", 5), "Binary: 0x0102030405");

	return e;
}

void printXlPPHex(XLPP &xlpp)
{
	for (int i = xlpp.offset; i < xlpp.len; i++)
	{
		printf("%02X", xlpp.buf[i]);
	}
}


int sprintXLPP(char *buffer, XLPP &xlpp)
{
	uint8_t type = xlpp.getType();

	switch (type) {
	case LPP_DIGITAL_INPUT:
	{
		uint8_t v = xlpp.getDigitalInput();
		return sprintf(buffer, "Digital Input: %hu (0x%02x)", v, v);
	}
	case LPP_DIGITAL_OUTPUT:
	{
		uint8_t v = xlpp.getDigitalOutput();
		return sprintf(buffer, "Digital Output: %hu (0x%02x)", v, v);
	}
	case LPP_ANALOG_INPUT:
	{
		float f = xlpp.getAnalogInput();
		return sprintf(buffer, "Analog Input: %.2f", f);
	}
	case LPP_ANALOG_OUTPUT:
	{
		float f = xlpp.getAnalogOutput();
		return sprintf(buffer, "Analog Output: %.2f", f);
	}
	case LPP_LUMINOSITY:
	{
		uint16_t w = xlpp.getLuminosity();
		return sprintf(buffer, "Luminosity: %hu lux", w);
	}
	case LPP_PRESENCE:
	{
		uint8_t v = xlpp.getPresence();
		if(v) return sprintf(buffer, "Presence: yes");
		else return sprintf(buffer, "Presence: no");
	}
	case LPP_TEMPERATURE:
	{
		float f = xlpp.getTemperature();
		return sprintf(buffer, "Temperature: %.1f °C", f);
	}
	case LPP_RELATIVE_HUMIDITY:
	{
		float f = xlpp.getRelativeHumidity();
		return sprintf(buffer, "Relative Humidity: %.1f %%", f);
	}
	case LPP_ACCELEROMETER:
	{
		Accelerometer a = xlpp.getAccelerometer();
		return sprintf(buffer, "Accelerometer: X %.3f g, Y %.3f g, Z %.3f g", a.x, a.y, a.z);
	}
	case LPP_BAROMETRIC_PRESSURE:
	{
		float f = xlpp.getBarometricPressure();
		return sprintf(buffer, "Barometric Pressure: %.1f hPa", f);
	}
	case LPP_VOLTAGE:
	{
		float f = xlpp.getVoltage();
		return sprintf(buffer, "Voltage: %.2f V", f);
	}
	case LPP_CURRENT:
	{
		float f = xlpp.getCurrent();
		return sprintf(buffer, "Current: %.3f A", f);
	}
	case LPP_FREQUENCY:
	{
		uint32_t u = xlpp.getFrequency();
		return sprintf(buffer, "Frequency: %u Hz", u);
	}
	case LPP_PERCENTAGE:
	{
		uint32_t u = xlpp.getPercentage();
		return sprintf(buffer, "Percentage: %d %%", u);
	}
	case LPP_ALTITUDE:
	{
		int16_t u = xlpp.getAltitude();
		return sprintf(buffer, "Altitude: %d m", u);
	}
	case LPP_CONCENTRATION:
	{
		uint16_t w = xlpp.getConcentration();
		return sprintf(buffer, "Concentration: %d ppm", w);
	}
	case LPP_POWER:
	{
		uint16_t w = xlpp.getPower();
		return sprintf(buffer, "Power: %d W", w);
	}
	case LPP_DISTANCE:
	{
		float f = xlpp.getDistance();
		return sprintf(buffer, "Distance: %.3f m", f);
	}
	case LPP_ENERGY:
	{
		float f = xlpp.getEnergy();
		return sprintf(buffer, "Energy: %.3f kWh", f);
	}
	case LPP_DIRECTION:
	{
		float f = xlpp.getDirection();
		return sprintf(buffer, "Direction: %.2f deg", f);
	}
	case LPP_UNIXTIME:
	{
		uint32_t u = xlpp.getUnixTime();
		return sprintf(buffer, "Unix Time: %d", u);
	}
	case LPP_GYROMETER:
	{
		Gyrometer g = xlpp.getGyrometer();
		return sprintf(buffer, "Gyrometer: X %.2f °/s, Y %.2f °/s, Z %.2f °/s", g.x, g.y, g.z);
	}
	case LPP_COLOUR:
	{
		Colour c = xlpp.getColour();
		return sprintf(buffer, "Colour: R %d, G %d, B %d (#%02X%02X%02X)", c.r, c.g, c.b, c.r, c.g, c.b);
	}
	case LPP_GPS:
	{
		GPS p = xlpp.getGPS();
		return sprintf(buffer, "GPS: lat %.4f, lon %.4f, alt %.2f", p.latitude, p.longitude, p.altitude);
	}
	case LPP_SWITCH:
	{
		uint8_t v = xlpp.getSwitch();
		return sprintf(buffer, "Switch: %s", v?"on":"off");
	}
	case XLPP_INTEGER:
	{
		int64_t i = xlpp.getInteger();
		return sprintf(buffer, "Integer: %ld", i);
	}
	case XLPP_STRING:
	{
		char *str;
		xlpp.getString(&str);
		return sprintf(buffer, "String: \"%s\"", str);
	}
	case XLPP_BOOL:
	{
		bool b = xlpp.getBool();
		if (b) return sprintf(buffer, "Bool: true");
		else return sprintf(buffer, "Bool: false");
	}
	case XLPP_BOOL_TRUE:
	{
		return sprintf(buffer, "Bool: true");
	}
	case XLPP_BOOL_FALSE:
	{
		return sprintf(buffer, "Bool: false");
	}
	case XLPP_OBJECT:
	{
		char *key;
		int o = sprintf(buffer, "Object {");
		if (o < 0) return o;
		while (true) {
			xlpp.getObjectKey(&key);
			if (strcmp(key, "") == 0)
				break;
			o += sprintf(buffer+o, "  \"%s\": ", key);
			int p = sprintXLPP(buffer+o, xlpp);
			if (p < 0) return p;
			o += p;
		}
		o += sprintf(buffer+o, "}");
		return o;
	}
	case XLPP_ARRAY:
	{
		int o = sprintf(buffer, "Array [");
		while (true) {
			int p = sprintXLPP(buffer+o, xlpp);
			if (p == -2) break;
			if (p < 0) return p;
			o += p;
		}
		o += sprintf(buffer+o, "]");
		break;
	}
	case XLPP_END_OF_ARRAY:
		return -2;

	case XLPP_FLAGS:
		// TODO
		return -3;

	case XLPP_BINARY:
	{
		uint8_t data[25];
		size_t s = xlpp.getBinary(data);
		int o = sprintf(buffer, "Binary: 0x");
		for (int i = 0; i < s; i++)
		{
			o += sprintf(buffer+o, "%02X", data[i]);
		}
		return o;
	}
	case XLPP_NULL:
		return sprintf(buffer, "Null");
	}
	return -3;
}