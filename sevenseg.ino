

byte numbers[] = {
	255 - B00111111, // 0
	255 - B00000110, // 1
	255 - B01011011, // 2
	255 - B01001111, // 3
	255 - B01100110, // 4
	255 - B01101101, // 5
	255 - B01111101, // 6
	255 - B00000111, // 7
	255 - B01111111, // 8
	255 - B01101111, // 9
	255 - B01110111, // A
	255 - B01111100, // B like b
	255 - B00111001, // C
	255 - B01011110, // D small like 6 without upper stroke
	255 - B01111001, // E
	255 - B01111000, // F
};
byte digits[] = {
	255 - B11111110,
	255 - B11111101,
	255 - B11111011,
	255 - B11110111,
	255 - B11101111,
	255 - B11011111,
	255 - B10111111,
	255 - B01111111,
};

// shift
int latchPin = 10,
dataPin = 9,
clockPin = 8;

// green/white  latch 9
// orange/brown data  8
// yellow/black clock 7

void sevenseg_setup()
{
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

	digitalWrite(clockPin, LOW);

	digitalWrite(latchPin, LOW);
	// Clear
	shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
	shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
	shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
	digitalWrite(latchPin, HIGH);
}

void sevenseg_write(int which, int what)
{
	byte data = numbers[what];
	byte port = digits[which];
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, port);
	shiftOut(dataPin, clockPin, MSBFIRST, data);
	digitalWrite(latchPin, HIGH);
}

void sevenseg_clear()
{
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, 0);
	shiftOut(dataPin, clockPin, MSBFIRST, 0);
	digitalWrite(latchPin, HIGH);
}
