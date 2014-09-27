#include <LiquidCrystal.h>
#include <SPI.h>

enum Mode {
	Setup,
	Play
};

Mode mode;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// shift
int latchPin = 9;

void setup() {
	// mode = Setup;
	mode = Play;
	lcd.begin(21, 4);

	// Latch for 7seg
	pinMode(latchPin, OUTPUT);

	// initialize SPI:
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);

	digitalWrite(latchPin, LOW);
	SPI.transfer(B00000000);
	SPI.transfer(B00000000);
	SPI.transfer(B00000000);

	SPI.transfer(B11111000);
	SPI.transfer(B000000010);
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
	lcd.setCursor(0, 0);
	lcd.print("aaa 0                ");
	// digitalWrite(latchPin, LOW);
	// shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
	// shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
	// digitalWrite(latchPin, HIGH);
	// delay(1000);
	// byte data = 1;
	// for (int j = 0; j <= 8; j++) {
	// 	lcd.setCursor(4, 0);
	// 	lcd.print(data, 2);

	// 	digitalWrite(latchPin, LOW);
	// 	shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
	// 	shiftOut(dataPin, clockPin, MSBFIRST, data);
	// 	digitalWrite(latchPin, HIGH);
	// 	delay(1000);
	// 	data <<= 1;
	// }

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
