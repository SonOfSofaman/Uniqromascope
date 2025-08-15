volatile int counter = 0;
volatile bool takeSample = false;
volatile unsigned long data = 0UL;

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, INPUT);
	pinMode(4, INPUT);
	attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);
}

void loop()
{
	// digitalWrite(LED_BUILTIN, HIGH);
	// delay(5000);
	// digitalWrite(LED_BUILTIN, LOW);
	// delay(100);

	if (takeSample)
	{
		bool bit = digitalRead(4);

		data = data << 1;
		data |= bit;

		Serial.print("foo 0003 ... ");
		Serial.print("counter:");
		Serial.print(counter);

		byte r = (data & 0x000000FFUL) >> 0;
		byte g = (data & 0x0000FF00UL) >> 8;
		byte b = (data & 0x00FF0000UL) >> 16;

		Serial.print(" b,g,r:");
		Serial.print(b);
		Serial.print(",");
		Serial.print(g);
		Serial.print(",");
		Serial.print(r);

		Serial.println();

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
