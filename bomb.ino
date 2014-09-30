#include <LiquidCrystal.h>
#include <Keypad.h>
#include "EEPROM.h"


enum Mode {
	Program,
	Play
};

Mode mode;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
	{1, 2, 3, 10},
	{4, 5, 6, 11},
	{7, 8, 9, 12},
	{0,-1, 0, 13}, // * 0 #
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

bool isSpecialInput(char key) {
	return key == '*' || key == '#';
}

bool isLetterInput(char key) {
	return key == 'a' || key == 'b' || key == 'c' || key == 'd';
}

bool isNumberInput(char key) {
	return ! ( isLetterInput(key) || isSpecialInput(key) );
}


//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
	// mode = Program;
	mode = Play;
	lcd.begin(21, 4);

	sevenseg_setup();

	lcd.setCursor(0, 1);
	lcd.print("butts");

	// if (mode == Program) {
	// 	program_setup();
	// } else {
	// 	play_setup();
	// }
}

char lastKey = 0;

void loop() {
	char customKey = customKeypad.getKey();
	if (customKey) {
		if (customKey < 0)
			customKey = 0;
		lastKey = customKey;
	}
	// lcd.setCursor(0, 0);
	// lcd.print(lastKey);

	sevenseg_write(0, lastKey);
	// sevenseg_clear();

	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 3);
	// print the number of seconds since reset:
	lcd.print(millis()/1000);
	// if (mode == Program) {
	// 	program_loop();
	// } else {
	// 	play_loop();
	// }
}
