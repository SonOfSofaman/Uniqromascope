#include <Adafruit_NeoPixel.h>

volatile int counter = 0;
volatile bool takeSample = false;
volatile unsigned long data = 0UL;

#define NEOPIXELPIN 6
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	// Serial.begin(115200);
	// pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, INPUT);
	pinMode(4, INPUT);
	attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);
	pixels.begin();
}

void loop()
{
	if (takeSample)
	{
		bool bit = digitalRead(4);

		data = data << 1;
		data |= bit;

		byte r = (data & 0x000000FFUL) >> 0;
		byte g = (data & 0x0000FF00UL) >> 8;
		byte b = (data & 0x00FF0000UL) >> 16;

		pixels.clear();
		pixels.setPixelColor(0, pixels.Color(r, g, b));
		pixels.show();

		takeSample = false;
	}
}

void interruptHandler()
{
	counter++;
	if (takeSample == false)
	{
		takeSample = true;
	}
}
