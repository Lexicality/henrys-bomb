
enum SetupStage {
	GameMode,
	KeyCard,
	CodeMethod,
	ArmCodeCount,
	DisarmCodeCount,
	Strobe,
	Piezos,
	ArmTime,
	Done
};

SetupStage setupStage;
bool hasShownMessage;
bool isAllDone;

const int maxArmInputs = 4;
char armInput[maxArmInputs];
int numArmInputs;

void setup_setup()
{
	lcd.setCursor(0, 5);
	lcd.print("Program Mode");

	setupStage = GameMode;
	hasShownMessage = false;
	isAllDone = false;

	numArmInputs = 0;
}


void writeMultipleChoice(String message, String a, String b, String c, String d)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message);
	lcd.setCursor(0, 2);
	lcd.print("A: ");
	lcd.print(a);
	lcd.setCursor(11, 2);
	lcd.print("B: ");
	lcd.print(b);
	lcd.setCursor(0, 3);
	lcd.print("C: ");
	lcd.print(c);
	lcd.setCursor(11, 3);
	lcd.print("D: ");
	lcd.print(d);
}

void writeMultipleChoice(String message, String a, String b)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message);
	lcd.setCursor(0, 2);
	lcd.print("A: ");
	lcd.print(a);
	lcd.setCursor(0, 3);
	lcd.print("B: ");
	lcd.print(b);
}


void setup_loop()
{
	if (isAllDone) return;

	char key;
	switch (setupStage) {
	case GameMode: {
		if (!hasShownMessage) {
			lcd.setCursor(0, 0);
			lcd.print("What's yer gamemode");
			hasShownMessage = true;
			return;
		}
		key = customKeypad.getKey();
		if (!key) {
			return;
		}
		if (!isLetterInput(key)) {
			return;
		}
		int gamemode = static_cast<int>(key);
		EEPROM.write(0, gamemode);

		// reset for the next stage
		setupStage = KeyCard;
		hasShownMessage = false;
		// TODO: Clear LCD
		return;
	}
	case KeyCard: {
		// blah  blah blah see above

		// reset for the next stage
		setupStage = CodeMethod;
		hasShownMessage = false;
		// TODO: Clear LCD
		return;
	}
	case ArmTime: {
		if (!hasShownMessage) {
			lcd.setCursor(0, 0);
			lcd.print("What's yer Arrrmtime");
			hasShownMessage = true;
			return;
		}
		key = customKeypad.getKey();
		if (!key) {
			return;
		}
		// Avoid letters
		if (!isNumberInput(key)) {
			return;
		}
		// Add key to current inputs
		armInput[numArmInputs] = key;
		numArmInputs += 1;
		if (numArmInputs < maxArmInputs) {
			return;
		}
		// all done

		// TODO: Transfer array of characters to actual number here
		// TODO: Store number

		// reset for the next stage
		setupStage = CodeMethod;
		hasShownMessage = false;
		// TODO: Clear LCD
		return;
	}
	default: {
		lcd.setCursor(0, 0);
		lcd.print("Finished setup");
		isAllDone = true;
		// do something
	}
	}
	/*
	   FIXME: This is probably no longer necessary. (Probably?)

	   // Set game mode (A,B,C,D)
	   lcd.setCursor(1, 0);
	   lcd.print("Set game mode (A,B,C,D)");
	   char gamemode; // = customKeypad.getkey(); ????? Find out how to make it wait for a keypress

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
	   */
}
