volatile int counter = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(2), incrementCounter, FALLING);
}

void loop()
{
	Serial.print("foo 0002 ... ");
	Serial.print("counter:");
	Serial.println(counter);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(5000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(100);
}

void incrementCounter()
{
	counter++;
}
