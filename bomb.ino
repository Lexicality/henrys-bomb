#include <LiquidCrystal.h>

enum Mode {
	Program,
	Play
};

Mode mode;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

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

void loop() {
	byte data = 1, port = 1;
	for (int j = 0; j < 8; j++) {
		sevenseg_write(j, j);
	}
	sevenseg_clear();

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
