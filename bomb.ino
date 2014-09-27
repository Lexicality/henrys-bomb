#include <LiquidCrystal.h>

enum Mode {
	Setup,
	Play
};

Mode mode;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte numbers[] = {
	255 - B00111111, //0
	255 - B00000110, //1
	255 - B01011011, //2
	255 - B01001111, //3
	255 - B01100110, //4
	255 - B01101101, //5
	255 - B01111101, //6
	255 - B00000111, //7
	255 - B01111111, //8
	255 - B01101111, //9
};

// shift
int latchPin = 9,
	dataPin  = 8,
	clockPin = 7;

void setup() {
	// mode = Setup;
	mode = Play;
	lcd.begin(21, 4);

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

	lcd.setCursor(0, 1);
	lcd.print("butts");

	// if (mode == Setup) {
	// 	setup_setup();
	// } else {
	// 	play_setup();
	// }
}

void loop() {
	// lcd.setCursor(0, 0);
	// lcd.print("aaa 0                ");
	// delay(1000);
	byte data = 1, port = 1;
	for (int j = 0; j < 8; j++) {
		data = numbers[j];
		// lcd.setCursor(4, 0);
		// lcd.print(data, 2);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, MSBFIRST, port);
		shiftOut(dataPin, clockPin, MSBFIRST, data);
		digitalWrite(latchPin, HIGH);
		// delay(1);
		port <<= 1;
	}

	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, 0);
	shiftOut(dataPin, clockPin, MSBFIRST, 0);
	digitalWrite(latchPin, HIGH);

	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 3);
	// print the number of seconds since reset:
	lcd.print(millis()/1000);
	// if (mode == Setup) {
	// 	setup_loop();
	// } else {
	// 	play_loop();
	// }
}


// green/white  latch 9
// orange/brown data  8
// yellow/black clock 7
;
