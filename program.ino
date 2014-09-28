

void program_setup() {
	lcd.setCursor(0,5)
	lcd.print("Program Mode");

}

void program_loop() {
	// Set game mode (A,B,C,D)
	lcd.setCursor(1,0)
	lcd.print("Set game mode (A,B,C,D)")
	char gamemode;

	// Set key cards (on/off)
	int kcard; 

	// Set code method (Automatically generated/manual)
	int codem;

	// Set no. of activation codes (numeric 1-9)
	int ACodeNum;

	// Set no. of deactivation codes (numeric 1-9)
	int DCodeNum;

	// Set strobe (on/off)
	int strobe;

	// Set piezos (on/off)
	int piezos;

	// Commit all variables to EEPROM (byte no, value)
	EEPROM.write(0, gamemode);
	EEPROM.write(1, kcard);
	EEPROM.write(2, codem);
	EEPROM.write(3, ACodeNum);
	EEPROM.write(4, DCodeNum);
	EEPROM.write(5, strobe);
	EEPROM.write(6, piezos);
}
