#include <LiquidCrystal.h>

enum Mode {
	Setup,
	Play
};

Mode mode;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

byte fontArray[] = {
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
// 0 sinks current for the digit selected
byte digitArray[] = {
	B11111110,
	B11111101,
	B11111011,
	B11110111,
	B11101111,
	B11011111,
	B10111111,
	B01111111,
};

// shift
int latchPin = 9,
	dataPin  = 11,
	clockPin = 12;

void setup() {
	// mode = Setup;
	mode = Play;
	lcd.begin(21, 4);

	// Latch for 7seg
	pinMode(latchPin, OUTPUT);

	lcd.setCursor(0, 1);
	lcd.print("butts");

	// if (mode == Setup) {
	// 	setup_setup();
	// } else {
	// 	play_setup();
	// }
}

void loop() {
	lcd.setCursor(0, 0);
	lcd.print("aaa 0                ");
	// int x = 2;
	for (int x = 0; x < 8; x++) {
		// bring the shift register latch pin low
		digitalWrite(latchPin, LOW);
		// shift out the segment info/ shift out the segment info
		shiftOut(dataPin, clockPin, MSBFIRST, fontArray[x]);
		// shift out the digit select info
		shiftOut(dataPin, clockPin, MSBFIRST, digitArray[x]);
		// bring the shift register latch pin high, moves the data to the outputs
		digitalWrite(latchPin, HIGH);
		// delay to let the data be seen at each digit (there are better ways to create this pause)
		delay(100);
	}

	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 3);
	// print the number of seconds since reset:
	lcd.print(millis() / 1000);

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
